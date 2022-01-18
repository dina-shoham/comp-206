#!/bin/bash

# Dina Shoham 
# 260823582
# COMP 206 A3 EX.2 - finder.sh

#checking if a3config exists
if [[ -e a3config ]] ; then 
	. a3config 
else 
	echo "Error: cannot find a3config"
	exit 1
fi

#if DIRNAME doesn't exist or if empty
if [[ -z "$DIRNAME" ]] ; then  
        echo "Error: DIRNAME and EXTENSION must be set"
	exit 2       
fi 

#if EXTENSION doesn't exist or if empty
if [[ -z "$EXTENSION" ]] ; then 
        echo "Error: DIRNAME and EXTENSION must be set"
	exit 2       
fi 

#if DIRNAME doesn't exist 
if [[ ! -d $DIRNAME ]] ; then 
	echo "Error: directory $DIRNAME does not exist"
	exit 3
else 
	cd $DIRNAME
fi 

#if no files w/ specified extension exist  
if [[ ! `ls | grep ".$EXTENSION"` ]] ; then  
	echo "Unable to locate any files with extension $EXTENSION in $DIRNAME"
	exit 0
fi

#if it obtains results do the following  
RESULTS=`ls | grep ".$EXTENSION"`

for result in $RESULTS
do 
	if [[ "$SHOW" == "true" ]] ; then
		echo "$DIRNAME/$result"
		cat "$result"
	else 
		echo "$DIRNAME/$result"
	fi
done 

exit 0


