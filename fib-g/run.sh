#!/bin/bash
set -e

qmake-qt5
make
./Gviewer
