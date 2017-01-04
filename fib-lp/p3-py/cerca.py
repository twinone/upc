import urllib.request
import os
import stat
import time
import xml.etree.ElementTree
import argparse
import unicodedata

from math import cos, asin, sqrt
from datetime import timedelta, datetime
from ast import literal_eval


# Time in seconds until a new copy of the data is retrieved
# set to 0 for always
CACHE_TIMEOUT = 60 * 60

ENDPOINTS = {
    'data': "http://www.bcn.cat/tercerlloc/agenda_cultural.xml",
    'stations': "http://wservice.viabicing.cat/getstations.php?v=1",
    'parkings': "http://www.bcn.cat/tercerlloc/Aparcaments.xml",
}


def d(msg):
    """ Print a message to the screen, or do nothing in release """
    print('<!--' + msg + '-->')


def cache_name(name):
    return "." + name + ".cache"


def file_age(path):
    """ Function that returns the age of a file or -1 if it doesn't exist """
    if not os.path.isfile(path):
        return -1
    return time.time() - os.stat(path)[stat.ST_MTIME]


def get(name, cache=True):
    d('getting ' + name + ' endpoint')
    f = cache_name(name)
    age = file_age(f)
    if not cache or age == -1 or age > CACHE_TIMEOUT:
        d('Getting fresh copy')
        data = urllib.request.urlopen(ENDPOINTS[name]).read().decode('utf-8')
        open(f, 'w').write(data)
    else:
        d('Using cached data')
    return xml.etree.ElementTree.parse(f).getroot()


# see
# http://stackoverflow.com/questions/517923/what-is-the-best-way-to-remove-accents-in-a-python-unicode-string
def clean(input_str):
    """ removes accents and returns only lowercase ascii text of a string """
    nfkd_form = unicodedata.normalize('NFKD', input_str)
    only_ascii = nfkd_form.encode('ASCII', 'ignore')
    return only_ascii.lower()


def match_str(node):
    return ''.join([
        node.find('name').text,
        node.find('address').text,
        node.find('proxdate').text + " - " + node.find('proxhour').text
    ])


def out_event(node):
    return ('<span class="name">{0}</span><br>'.format(node.find('name').text) +
            map_span(node.find('address').text, latlong(node)) +
            '<br><span class="proxdate small">{0}</span>'.format(node.find('proxdate').text + " - " +
                                                       node.find('proxhour').text))


def matches(s, q):
    """ returns true if the selected query object q matches the string s """
    if isinstance(q, str):
        return clean(q) in clean(s)
    if isinstance(q, tuple):
        return True in [matches(s, x) for x in q]
    # else isinstance(q, list)
    return False not in [matches(s, x) for x in q]


def parse_args():
    # see https://docs.python.org/3/library/argparse.html
    parser = argparse.ArgumentParser(description='Barcelona event searcher')
    parser.add_argument('--date')
    key_help = ("Search query, combination of nested (), [] and str"
                "where () means union (logical or: true if any matches)"
                "[] means intersection (logical and: true if all match)")
    parser.add_argument('--key', help=key_help)
    return parser.parse_args()


def latlong(node):
    try:
        return tuple([float(node.find(x).text) for x in ['gmapx', 'gmapy']])
    except:
        return None

# see
# http://stackoverflow.com/questions/27928/calculate-distance-between-two-latitude-longitude-points-haversine-formula


def distance(a, b):
    if not a or not b:
        return None
    (a1, a2) = a
    (b1, b2) = b
    p = 0.017453292519943295
    a = 0.5 - cos((b1 - a1) * p) / 2 + cos(a1 * p) * cos(b1 * p) * (1 - cos((b2 - a2) * p)) / 2
    return 12742 * asin(sqrt(a))


def st_pos(node):
    return tuple([float(node.find(x).text) for x in ['lat', 'long']])


def bicing(item, stations, bikes):
    """
    Get the 5 nearest bicing stations to loc with
    If bikes=True: at least 1 available bike
    otherwise: at least 1 free slot
    Returns the station, distance and free bikes/slots
    """

    t = 'bikes' if bikes else 'slots'
    pos = latlong(item)
    distances = [distance(st_pos(s), pos) for s in stations]
    res = [
        (s, d, int(s.find(t).text))
        for (s, d) in zip(stations, distances)
        if d and d < 0.5
        and int(s.find(t).text) >= 1
    ]
    # return closest 5 stations that match
    return sorted(res, key=lambda x: x[1])[:5]

def parking(item, parkings):
    """
    Get the public parkings within 500m of the item
    """
    pos = latlong(item)
    distances = [distance(latlong(p), pos) for p in parkings]
    res = [
        (p, d)
        for (p, d) in zip(parkings, distances)
        if d and d < 0.5
    ]
    # return closest 5 stations that match
    return sorted(res, key=lambda x: x[1])

def map_span(text, coords):
    # '<div class="address tooltip"><span><a href="#">{0}</a></span></div><br>'.format() +
    coords = coords if coords else ('','')
    return (
        ('<div class="tooltip">' +
        '<span class="maptooltip" data-lat="{1}" data-long="{2}">' +
        '<a href="#">{0}</a></span></div>')
        .format(text, coords[0], coords[1]))

def out_st(stdst, bikes):
    t = 'BIKES' if bikes else 'SLOTS'
    return '<br>'.join([
        (map_span(st.find('street').text, st_pos(st)) +
        '<br><span class="green">' + str(free) + ' ' + t + '</span>'
        '<span class="small"> - ' + str(int(dst*1000)) + 'm</span><br>')
        for (st, dst, free) in stdst
    ])

def out_park(pkdst):
    return '<br>'.join([
        (map_span(pk.find('name').text.replace("Aparcament", "Ap."), latlong(pk)) +
        '<span class="small"> - ' + str(int(dst*1000)) + 'm</span>')
        for (pk, dst) in pkdst
    ])

def main():
    items = get('data').findall('.//row/item[address][name]')
    stations = get('stations').findall('station')
    parkings = get('parkings').findall('.//row/item[name]')
    args = parse_args()

    try:
        query = literal_eval(args.key) if args.key else ''
    except:
        print("Invalid query (forgot quotes?)")
        exit(1)

    d("query: " + str(query))

    content = ""
    content += "<table>"
    content += "<tr>"
    content += "<th>{0}</th>".format("Details")
    content += "<th>{0}</th>".format("Bicing Stations<br>with free slots")
    content += "<th>{0}</th>".format("Bicing Stations<br>with available bikes")
    content += "<th>{0}</th>".format("Public Parkings<br>with free spots")
    content += '</tr>'

    res = [x for x in items if matches(match_str(x), query)]
    for item in res:
        content += "<tr>"
        content += "<td>{0}</td>".format(out_event(item))
        content += "<td>{0}</td>".format(out_st(bicing(item, stations, True), True))
        content += "<td>{0}</td>".format(out_st(bicing(item, stations, False), False))
        content += "<td>{0}</td>".format(out_park(parking(item, parkings)))
        content += "</tr>"
    content += "</table>"

    out = open('template.tmpl').read()
    out = out.replace('<!-- [[CONTENT]] -->', content)
    print(out)


if __name__ == '__main__':
    main()


#
