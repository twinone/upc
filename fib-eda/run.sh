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
Player2=Dummy
Player3=Dummy
Player4=Twinone

VIEWER_PATH=$(pwd)/Viewer

./Game $Player1 $Player2 $Player3 $Player4 < ${game}.cnf > $VIEWER_PATH/${game}.res

#Mac OSX
browser="/Applications/Google Chrome.app/Contents/MacOS/Google Chrome"
browser="/Applications/Firefox.app/Contents/MacOS/firefox"
#Linux
browser=firefox
echo "$browser" "$VIEWER_PATH/viewer.html?game=${game}.res"
"$browser" "file://$VIEWER_PATH/viewer.html?game=${game}.res"
