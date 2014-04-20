#! /bin/sh

NUM=64

while [ "$NUM" -le 127 ]; do
	rm log.$NUM
	$NUM=$(($NUM+1))
done
