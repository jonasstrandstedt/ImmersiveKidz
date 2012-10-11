#!/bin/bash

BINARY="Program"
CONFIG=""
SLAVES="NO"
STARTER="xterm -e"

PLATFORM="unknown"
unamestr=`uname`
if [[ "$unamestr" == 'Linux' ]]; then
   PLATFORM='linux'
elif [[ "$unamestr" == 'Darwin' ]]; then
   PLATFORM='OSX'
fi

if [ -z "$1" ]
	then
	CONFIG="sgct_config/single.xml"
else
	if [ "$1" = "VR" ]
		then
		CONFIG="sgct_config/VRArenaSimCenter.xml"
		SLAVES="YES"
	else
		CONFIG="sgct_config/single.xml"
	fi
fi

echo "Current platform is "$PLATFORM
echo "Running program $1"

$STARTER "./"$BINARY" -config "$CONFIG" -local 0" &

if [ "$SLAVES" = "YES" ]
	then
	echo "Waiting for master to start"
	sleep 5
	echo "Starting slaves"
	$STARTER "./"$BINARY" -config "$CONFIG" -local 1 --slave" &
	$STARTER "./"$BINARY" -config "$CONFIG" -local 2 --slave" &
	$STARTER "./"$BINARY" -config "$CONFIG" -local 3 --slave" &
fi

