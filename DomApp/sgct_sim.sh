#!/bin/bash

BINARY="Program"
CONFIG=""
SLAVES="NO"
STARTER="xterm -e"

PLATFORM="unknown"
unamestr=`uname`
if [[ "$unamestr" == 'Linux' ]]; then
   PLATFORM='linux'
   BINARY="./"$BINARY
elif [[ "$unamestr" == 'Darwin' ]]; then
   PLATFORM='OSX'
   BINARY="./"$BINARY
elif [[ "$unamestr" == 'MINGW32_NT-6.1' ]]; then
   PLATFORM='Windows'
   STARTER="start cmd /k"
   BINARY=$BINARY".exe"
fi

if [ -z "$1" ]
	then
	CONFIG="data/sgct_config/single.xml"
	if [[ "$unamestr" == 'Darwin' ]]; then
		CONFIG="data/sgct_config/single_mac.xml"
	fi
else
	if [ "$1" = "VR" ]
		then
		CONFIG="data/sgct_config/VRArenaSimCenter.xml"
		SLAVES="YES"
	else
		CONFIG="data/sgct_config/single.xml"
		if [[ "$unamestr" == 'Darwin' ]]; then
			CONFIG="data/sgct_config/single_mac.xml"
		fi
	fi
fi

echo "Current platform is "$PLATFORM
echo "Running program $1"

$STARTER $BINARY" -config "$CONFIG" -local 0" &

if [ "$SLAVES" = "YES" ]
	then
	echo "Waiting for master to start"
	sleep 5
	echo "Starting slaves"
	$STARTER $BINARY" -config "$CONFIG" -local 1 --slave" &
	$STARTER $BINARY" -config "$CONFIG" -local 2 --slave" &
	$STARTER $BINARY" -config "$CONFIG" -local 3 --slave" &
fi

