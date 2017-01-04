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

HEADER = """
<style>

table {
    border-collapse: collapse;
    width: 1000px;
    border: 2px solid #4CAF50;
    margin: 0 auto;
}

th, td {
    width: 400px;
    margin: auto;
    text-align: left;
    padding: 8px;
    border-left: 1px solid #4CAF50;
}


td span.name {
    font-weight: bold;
    margin-bottom: 1em;
    display: inline-block;
}

td span.address {
    font-style: italic;
    font-size: .9em;
}

td span.proxdate {
    font-size: .8em;
    color: #888888;
}

tr:nth-child(even){background-color: #f2f2f2}

th {
    background-color: #4CAF50;
    color: white;
    text-align: center;
}
</style>
"""


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
    return ('<span class="name">' + node.find('name').text + '</span>' +
            '<span class="address">' + node.find('address').text + '</span><br>' +
            '<span class="proxdate">' + node.find('proxdate').text + " - " +
                node.find('proxhour').text + '<br>' + '</span>')

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


def wrap(t, el):
    """ wraps an element el in a tag t """
    return "<"+t+">"+el+"</"+t+">"

def main():
    items = get('data').findall('.//row/item[address][name]')
    args = parse_args()

    try:
        query = literal_eval(args.key) if args.key else ''
    except:
        print("Invalid query (forgot quotes?)")
        exit(1)

    d("query: " + str(query))

    print("<html><body>")
    print(HEADER)
    print("<table>")
    print("<tr>")
    print(wrap('th', "Details"))
    print(wrap('th', "Bicing Stations<br>with free slots"))
    print(wrap('th', "Bicing Stations<br>with available bikes"))
    print(wrap('th', "Public Parkings<br>with free spots"))
    print('</tr>')

    res = [x for x in items if matches(match_str(x), query)]
    for item in res:
        print("<tr>")
        print(wrap('td', out_str(item)))
        print(wrap('td', "TODO"))
        print(wrap('td', "TODO"))
        print(wrap('td', "TODO"))
        print("</tr>")
    print("</table>")
    print("</body></html>")


if __name__ == '__main__':
    main()


#
