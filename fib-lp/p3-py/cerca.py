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


# Assumptions:
# Since in the statement it's mentioned to "Sort the events by proximity to the
# requested date", but you can request ranges and multiple dates,
# the output is just sorted by date. It would be ugly anyway to now show them
# in order: If the query was 01/01/17, dates could be:
# 02/01/17, 28/12/16, 07/01/17, and that's unnatural to read

# Note:
# A lot of events don't have a 'begindate' node. The 'proxdate' attribute
# will be used in those cases.



# See original (unminified HTML) at
# https://github.com/twinone/fib-lp/blob/master/p3-py/template.tmpl
HTML = """<body><style>table{border-collapse:collapse;width:1000px;border:2px solid #4CAF50;margin:0 auto}td,th{width:400px;margin:auto;text-align:left;padding:8px;border-left:1px solid #4CAF50;vertical-align:top}td span.name{font-weight:700;margin-bottom:1em;display:inline-block}td .tooltip{font-style:italic;font-size:.9em}.small{font-size:.9em;color:#888}.green{font-size:.9em;font-weight:700;color:#4CAF50}tr:nth-child(even){background-color:#f2f2f2}th{background-color:#4CAF50;color:#fff;text-align:center}.tooltip{position:relative;display:inline-block;border-bottom:1px dotted #000}.framecont{position:fixed;top:0;left:0;bottom:0;right:0;text-align:center;width:100%;vertical-align:middle!important;height:100%}.inner{background-color:#4CAF50;text-align:center;border-radius:6px;padding:5px 5px;position:absolute;top:20%;left:20%;width:60%;height:60%;z-index:1}.tooltip .inner::after{content:"";position:absolute;top:50%;right:100%;margin-top:-5px;border-width:5px;border-style:solid;border-color:transparent #000 transparent transparent}</style><table><tr><th>Details<th>Bicing Stations<br>with free slots<th>Bicing Stations<br>with available bikes<th>Public Parkings<br>with free spots<!-- [[CONTENT]] --></table><script>function query(t){return"https://www.google.com/maps/embed/v1/place?key=AIzaSyBNIp87_yb-HNAdRnd-XTH5kWH0Xz0eDss&q="+t}function onClick(t){t.preventDefault();var e=t.target;if(e.tooltip)return setTimeout(function(){e.tooltip.focus()},0),void(e.tooltip.parentNode.style.visibility="visible");console.log("hover over",e);var o=document.createElement("div");o.setAttribute("class","framecont");var n=document.createElement("iframe");n.setAttribute("class","inner"),n.setAttribute("frameborder","0"),n.setAttribute("style","border:0;");var i=e.parentNode.getAttribute("data-lat")+","+e.parentNode.getAttribute("data-long");n.setAttribute("src",query(i)),n.addEventListener("blur",function(){console.log("blurring"),o.style.visibility="hidden"}),o.appendChild(n),setTimeout(function(){n.focus()},0),document.body.appendChild(o),e.tooltip=n}function onLoaded(){document.querySelectorAll(".tooltip").forEach(function(t){console.log("el:",t),t.addEventListener("click",onClick)})}document.addEventListener("DOMContentLoaded",onLoaded)</script>"""


# ###############  HTTP GET CACHE #################
class HttpGetCache:
    """A simple HTTP GET with cache"""

    ENDPOINTS = {
        'data': "http://www.bcn.cat/tercerlloc/agenda_cultural.xml",
        'stations': "http://wservice.viabicing.cat/getstations.php?v=1",
        'parkings': "http://www.bcn.cat/tercerlloc/Aparcaments.xml",
    }

    # Time in seconds until a new copy of the data is retrieved
    # set to 0 for always
    CACHE_TIMEOUT = 60 * 60

    @staticmethod
    def get(name, cache=True):
        """GET ENDPOINTS['name'] and if cache, store it in the cache"""
        d('getting ' + name + ' endpoint')
        f = HttpGetCache.cache_name(name)
        age = HttpGetCache.file_age(f)
        if not cache or age == -1 or age > HttpGetCache.CACHE_TIMEOUT:
            d('Getting fresh copy')
            data = (urllib.request.urlopen(HttpGetCache.ENDPOINTS[name])
                    .read().decode('utf-8'))
            open(f, 'w').write(data)
        else:
            d('Using cached data')
        return xml.etree.ElementTree.parse(f).getroot()

    @staticmethod
    def cache_name(name):
        return "." + name + ".cache"

    @staticmethod
    def file_age(path):
        """ Function that returns the age of a file or -1 if it doesn't exist """
        if not os.path.isfile(path):
            return -1
        return time.time() - os.stat(path)[stat.ST_MTIME]


class Coords:
    """Represents a simple coordinate system as a (lat, long)"""
    def __init__(self, lat, lng):
        self.lat = lat
        self.lng = lng

    @staticmethod
    def from_xml(node):
        """Returns a Coords from an XML node"""
        try:
            if node.tag == 'station':  # stations use lat long nodes
                x = float(node.find('lat').text)
                y = float(node.find('long').text)
                return Coords(x, y)
            else:  # parkings, data use gmapx,y
                x = float(node.find('gmapx').text)
                y = float(node.find('gmapy').text)
                return Coords(x, y)
        except:
            return Coords(0, 0)  # Is not going to be in 500m anyway
    # see
    # http://stackoverflow.com/questions/27928/calculate-distance-between-two-latitude-longitude-points-haversine-formula
    def distance(self, other):
        """Distance from this node to other in km"""
        (a1, a2) = self.lat, self.lng
        (b1, b2) = other.lat, other.lng
        p = 0.017453292519943295
        a = (0.5 - cos((b1 - a1) * p) / 2 + cos(a1 * p) * cos(b1 * p) *
             (1 - cos((b2 - a2) * p)) / 2)
        res = 12742 * asin(sqrt(a))
        return res


class Printer:
    """Class used to format the output of the results"""

    @staticmethod
    def event(node):
        """Prints an event"""
        return """
        <span class="name">{0}</span><br>
        {1}
        <br><span class="proxdate small">{2}</span>
        """.format(
            node.find('name').text,
            map_span(node.find('address').text, Coords.from_xml(node)),
            get_date(node).strftime('%d/%m/%Y')
        )

    @staticmethod
    def stations(stdst, bikes):
        t = 'BIKES' if bikes else 'SLOTS'
        return ''.join([
            """
            {0}<br>
            <span class="green">{1}</span>
            <span class="small"> - {2}m</span><br>
            """.format(
                map_span(st.find('street').text, Coords.from_xml(st)),
                str(free) + ' ' + t,
                str(int(dst*1000)))
            for (st, dst, free) in stdst
        ])

    @staticmethod
    def parking(pkdst):
        return '<br>'.join([
            '{0} <span class="small"> - {1}m</span>'.format(
                map_span(
                    pk.find('name').text.replace("Aparcament", "Ap."),
                    Coords.from_xml(pk)),
                str(int(dst*1000))
            )
            for (pk, dst) in pkdst
        ])

# Event, Parking, Station classes
# are used to only parse the info once, which is much faster
# than traversing the XML every time
class Event:
    def __init__(self, node):
        self.node = node
        self.coords = Coords.from_xml(node)
        self.date = get_date(node)

class Parking:
    def __init__(self, node):

class Station:
    def __init__(self, node):



def matches(s, q):
    """Returns true if the string s matches the query q"""
    if isinstance(q, str):
        return clean(q) in clean(s)
    if isinstance(q, tuple):
        return True in [matches(s, x) for x in q]
    # else isinstance(q, list)
    return False not in [matches(s, x) for x in q]


def get_date(n):
    """Get the date of a node or now()"""
    try:
        return parse_date(n.find('.//begindate').text)
    except:
        try:
            return parse_date(n.find('.//proxdate').text)
        except:
            return datetime.now()

def parse_date(s):
    """Returns the datetime corresponding to s"""
    return datetime.strptime(s, "%d/%m/%Y")


def to_range(o):
    """Returns a halfopen range of dates from a date object (not list)"""
    if isinstance(o, str):
        d = parse_date(o)
        return [d, d+timedelta(days=1)]
    if isinstance(o, tuple):
        d = parse_date(o[0])
        return [d+timedelta(days=o[1]),
                d+timedelta(days=o[2]+1)]

def matches_date(n, q):
    """Returns true if the node n matches the query q"""
    d = get_date(n)
    if q is None: return True
    if d is None: return True
    if not isinstance(q, list): q = [q]
    for o in q:
        [a, b] = to_range(o)
        if a <= d and d < b: return True
    return False





def bicing(item, stations, bikes):
    """
    Get the 5 nearest bicing stations to loc with
    If bikes=True: at least 1 available bike
    otherwise: at least 1 free slot
    Returns the station, distance and free bikes/slots
    """

    t = 'bikes' if bikes else 'slots'
    pos = Coords.from_xml(item)
    distances = [Coords.from_xml(s).distance(pos) for s in stations]
    res = [
        (s, d, int(s.find(t).text))
        for (s, d) in zip(stations, distances)
        if d and d < .5
        and int(s.find(t).text) >= 1
    ]
    # return closest 5 stations that match
    return sorted(res, key=lambda x: x[1])[:5]


def parking(item, parkings):
    """Get the public parkings within 500m of the item"""
    pos = Coords.from_xml(item)
    distances = [Coords.from_xml(p).distance(pos) for p in parkings]
    res = [(p, d) for (p, d) in zip(parkings, distances) if d and d < 0.5]
    # return closest 5 stations that match
    return sorted(res, key=lambda x: x[1])


def map_span(text, coords):
    """Creates a clickable span that load a Google Maps overlay"""
    return """
        <div class="tooltip">
        <span class="maptooltip" data-lat="{1}" data-long="{2}">
        <a href="#">{0}</a></span></div>
        """.format(text, coords.lat, coords.lng)


def d(msg):
    """Functin to print debugging messages, just pass in release"""
    # print('<!--' + msg + '-->')
    pass


# see
# http://stackoverflow.com/questions/517923/what-is-the-best-way-to-remove-accents-in-a-python-unicode-string
def clean(input_str):
    """ removes accents and returns only lowercase ascii text of a string """
    nfkd_form = unicodedata.normalize('NFKD', input_str)
    only_ascii = nfkd_form.encode('ASCII', 'ignore')
    return only_ascii.lower()


def match_str(node):
    """
    The string representation of an item, for matching,
    includes the fields Name, Address, Date, Barri
    """
    return ''.join([
        node.find('name').text,
        node.find('address').text,  # includes Barri
        node.find('begindate').text if node.find('begindate') else ''
    ])


def date_and_query():
    # see https://docs.python.org/3/library/argparse.html
    parser = argparse.ArgumentParser()
    parser.add_argument('--date', help="Date query")
    parser.add_argument('--key', help="Search query")
    args = parser.parse_args()

    try:
        query = literal_eval(args.key) if args.key else ''
    except:
        print("Invalid query (forgot quotes?)")
        exit(1)

    try:
        date = literal_eval(args.date) if args.date else None
    except:
        print("Invalid date specified")
        exit(1)
    return (date, query)

def main():
    items = HttpGetCache.get('data').findall('.//row/item[address][name]')
    stations = HttpGetCache.get('stations').findall('station')
    parkings = HttpGetCache.get('parkings').findall('.//row/item[name]')

    (date, query) = date_and_query()

    c = ""

    res = [
        x for x in items
        if matches_date(x, date)
        and matches(match_str(x), query)
    ]
    res = sorted(res, key=lambda x: get_date(x))

    for item in res:
        c += """
        <tr><td>{0}</td><td>{1}</td><td>{2}</td><td>{3}</td></tr>
        """.format(
            Printer.event(item),
            Printer.stations(bicing(item, stations, True), True),
            Printer.stations(bicing(item, stations, False), False),
            Printer.parking(parking(item, parkings))
        )

    # to read from template file:
    # out = open('template.tmpl').read()
    # out = out.replace('<!-- [[CONTENT]] -->', c)

    # to use the actual template string:
    out = HTML.replace('<!-- [[CONTENT]] -->', c)
    print(out)


if __name__ == '__main__':
    main()
