#!/bin/bash

function menu24()
{
start=0

currentTime=$(date +%s)
pastDay=$((currentTime - 86400))
echo "Enter the name of a file or subdirectory"
echo "If you wish to exit, press Ctrl+C"
for item in *
do
	modifiedTime=$(stat -c %Y "$item")
	if [ $modifiedTime -ge $pastDay ]; then
		echo "$((start = start + 1))) $item"
	fi
done
}

function traverse()
{
if [ -f "$1" ]; then
	head "$1"
	echo "Would you like to display more? (Y/n)"
	read answer
	start=0
	while [ $answer = "Y" ]; do
		tail -n +$((start = start + 10)) "$1"
		echo "Would you like to display more? If empty, end of file is reached. (Y/n)"
		read answer
	done
	echo "Files modified in the past 24 hours:"
	menu24
	read selection
	traverse "${selection}"
fi
if [ -d "$1" ]; then
	cd "$1"
	menu24
	read selection
	traverse "$selection"
fi
}

echo "Enter a directory name: "
read dirname

if [ ! -e "${dirname}" ]; then
	echo "Directory does not exist. Would you like to create directory? (Y/n)"
	read choice
	if [ $choice == "Y" ]; then
		mkdir "${dirname}"
		exit
	else
		exit
	fi
fi

cd "${dirname}"

start=0
 
echo "Enter the name of a file or subdirectory"
echo "If you wish to exit, press Ctrl+C"
for item in *
do  
	echo "$((start = start + 1))) $item"
done

read selection

traverse "${selection}"
