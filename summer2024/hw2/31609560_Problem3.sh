#!/bin/bash

traverse (){
	if [ ! -d "$1" ]; then
		return
	fi
	if [ `ls "$1" | wc -l` -eq 0 ]; then
		return
	fi
	local entries=("$1"/*)
	local entry
	for entry in "${entries[@]}"
	do
		if [ -f "$entry" ]; then
			grep -Eo "^[a-zA-Z]+@[a-z]+\.[a-z]{2,4}$" "$entry" >> temp.txt
		else
			traverse "$entry"
		fi
	done
}


touch temp.txt
touch unique_emails.txt

traverse "$1"

sort temp.txt | uniq > unique_emails.txt
rm temp.txt

cat unique_emails.txt
