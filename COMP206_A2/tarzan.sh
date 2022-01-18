#!/bin/bash  

file=$1
tar=$2

#check for correct usage  
if [ ! $# -eq 2 ] ; then  	
	echo "Usage: ./tarzan.sh filename tarfile"  
#check if the tar file can be found 
elif [ ! -f "$tar" ] ; then  
	echo "Error: cannot find tar file $tar"   
#check if the file can be found in the tar file 
else 
        if [[ `tar -tf "$tar" | grep "$file"` ]] ; then
		echo "Success! $file exists in $tar" 
	else 
 		echo "Error: $file does not exist in $tar"  
	fi 
fi

