#!/bin/bash

if [ "$#" = 0 ]; then
	echo "Error! No filenames provided."
	exit 12
elif [ "$#" -lt 3 ]; then
	echo "Error! Must provide at least 3 filenames"
	exit 12
fi

mkdir backup_$(date '+%Y-%m-%d')
touch log.txt

for arg in "$@"
do
	if [ ! -e "${arg}" ]; then
		echo "Warning! The file ${arg} does not exist."
		continue
	else
		cp "${arg}" "${arg}"_$(date '+%Y-%m-%d')
		mv "${arg}"_$(date '+%Y-%m-%d') ./backup_$(date '+%Y-%m-%d')
		echo -e "Original file: ${arg} \t New filename: ${arg}_$(date '+%Y-%m-%d')" >> log.txt
	fi	
done

echo "Back up completed. Back up location is $(pwd)/backup_$(date '+%Y-%m-%d')"
mv log.txt ./backup_$(date '+%Y-%m-%d')
