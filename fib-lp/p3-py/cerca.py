import urllib.request
import os
import stat
import time
import xml.etree.ElementTree


# Time in seconds until a new copy of the data is retrieved
# set to 0 for always
CACHE_TIMEOUT = 20 * 60

ENDPOINTS = {
    'data': "http://www.bcn.cat/tercerlloc/agenda_cultural.xml",
    'stations': "http://wservice.viabicing.cat/getstations.php?v=1",
    'parkings': "http://www.bcn.cat/tercerlloc/Aparcaments.xml",
}


def d(msg):
    """ Print a message to the screen, or do nothing in release """
    print(msg)


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


def main():
    print("main")
    root = get('data')
    print("root tag", root.tag)


if __name__ == '__main__':
    main()

























#
