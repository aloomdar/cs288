#!/bin/bash

fname="$1"

if [ ${#fname} = 0 ]; then
	echo "Enter a filename"
	read filename
	fname="${filename}"
fi

if [ -f "${fname}" ]; then
	if [ ! -r "${fname}" ]; then
		echo "Warning! You do not have read permissions for this file."
		exit 12
	else
		wordCount=$(sort ${fname} | wc -w)
		echo "Word count ${wordCount}"
		lineCount=$(sort ${fname} | wc -l)
		echo "Line count ${lineCount}"
		charCount=$(sort ${fname} | wc -c)
		echo "Character count ${charCount}"
		if [ $charCount -gt 10000 ]; then
			echo "Text Heavy"
		elif [ $charCount -ge 1000 ] && [ $charCount -le 10000 ]; then
			echo "Moderately Sized"
		else
			echo "Light File"
		fi
	fi	
elif [ -d "${fname}" ]; then
	if [ ! -r "$fname" ] && [ ! -x "${fname}" ]; then
		echo "Warning! You do not have read/execute permissions for this directory."
		exit 12
	else
		cd "${fname}"
		du -b -a
	fi	
fi

