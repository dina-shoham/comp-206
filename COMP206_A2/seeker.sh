#!/bin/bash 

usage="Error: missing the pattern argument. \nUsage: ./seeker.sh [-c] [-a] pattern [path]"

#variables to track which arguments are present 
contents=$'\0' #-c
all=$'\0'  #-a
pattern=$'\0' #pattern
path=$'\0'  #path

#0 or more than 4 args 
if [[ $# -eq 0 || $# -gt 4 ]] ; then  
	echo -e "$usage" 
	exit
fi 

#1 arg 
if [[ $# -eq 1 && ! $1 = [-/]* ]] ; then 
	pattern=$1
elif [[ $# -eq 1 ]] ; then 
	echo -e "$usage"
	exit
fi

#2, 3, or 4 args 
#looping through and checking which arguments were entered 
while [[ -n $1 ]] ; do 
	if [[ ! $1 = [-/]* ]] ; then #if a pattern and not a switch or path 
		pattern=$1
		shift 
	elif [[ $1 = [-/]* ]] ; then #if switch or path 	
		case "$1" in
 
		-c) contents=$1
		 ;;
 
		-a) all=$1
		 ;; 

		[/]*) path=$1 
		;; 
	
		*) echo -e "$usage"  	
		exit 
		;; 

		esac
		shift 
	fi
done

#check if there's a pattern 
if [[ -z "$pattern" ]] ; then 
	echo -e "$usage"
	exit
fi

#if there's a path, check if path is valid and cd into directory
#if no path, exit
if [[ ! -z "$path" && ! -d $path ]] ; then  
	echo "Error: $path is not a valid directory" 
	exit
else 
	if [[ -z "$path" ]] ; then 
		path=`pwd` 
	fi 
	cd $path	
fi 

#check for files with pattern in name 
if [[ ! `ls | grep "$pattern"` ]] ; then  
	echo -e "Error: unable to locate any files that have pattern $pattern in its name in $path"
	exit
fi 

#check if -a passed 
files=`ls | grep "$pattern"`	
file=`ls | grep -m 1 "$pattern"`
	

if [[ ! -z "$all" ]] ; then 
	for file in $files  
	do 
		#if only -a passed 
		if [[ -z "$contents" ]] ; then 
			echo -e ""$path"/"$file""
	
		#if -c and -a passed 
		else 
			echo -e "==== Contents of: "$path"/"$file" ===="
			cat "$path/$file" 
		fi 
	done 
#if only -c was passed 
elif [[ ! -z "$contents" ]] ; then 
	echo -e "==== Contents of: "$path"/"$file" ==== "
	cat "$path/$file"
#if neither -a nor -c were passed 
else  
	echo ""$path"/"$file""
fi 	

