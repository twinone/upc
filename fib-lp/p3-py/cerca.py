import urllib.request
import os
import stat
import time
import xml.etree.ElementTree
import argparse
from datetime import timedelta, datetime
from ast import literal_eval
import unicodedata



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



# see http://stackoverflow.com/questions/517923/what-is-the-best-way-to-remove-accents-in-a-python-unicode-string
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

def out_str(node):
    return ('<span class="name">{0}</span><br>'.format(node.find('name').text) +
            '<div class="address tooltip"><span><a href="#">{0}</a></span></div><br>'.format(node.find('address').text) +
            '<span class="proxdate">{0}</span>'.format(node.find('proxdate').text + " - " +
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


def main():
    items = get('data').findall('.//row/item[address][name]')
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
        content += "<td>{0}</td>".format(out_str(item))
        content += "<td>{0}</td>".format("TODO")
        content += "<td>{0}</td>".format("TODO")
        content += "<td>{0}</td>".format("TODO")
        content += "</tr>"
    content += "</table>"

    out = open('template.tmpl').read()
    out = out.replace('<!-- [[CONTENT]] -->', content)
    print(out)


if __name__ == '__main__':
    main()


#
