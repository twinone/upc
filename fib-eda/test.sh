#!/bin/bash

# Exit immediately if a command exits with a non-zero status.
set -e

make all

# Take an optional argument: the basename of the game file.
game="default"          # default game
if [ "$#" -ge 1 ]; then
  game=$1
fi

Player1=Dummy
Player2=Twinone
Player3=Dummy
Player4=Dummy

VIEWER_PATH=$(pwd)/Viewer

./Game $Player1 $Player2 $Player3 $Player4 < ${game} > $VIEWER_PATH/${game}.res
