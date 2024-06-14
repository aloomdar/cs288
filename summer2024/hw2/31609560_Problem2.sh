#!/bin/bash 

file=$1
if [[ $file =~ .*[.c]$ ]]; then
	printCount=`grep 'printf' $file | wc -l`
	scanCount=`grep 'scanf' $file | wc -l`
	totalLines=`wc -l < $file`
	printPercent=$((($printCount * 100) / $totalLines))
	scanPercent=$((($scanCount * 100) / $totalLines))
	echo "Number of printf:" $printCount
	echo "Number of scanf:" $scanCount
	echo "Number of total lines:" $totalLines
	echo "Percentage of lines containing printf:" $printPercent "%"
	echo "Percentage of lines containing scanf:" $scanPercent "%"
	if [ -e "scanf_log.txt" ]; then
		sed -n '/scanf/p' $file >> scanf_log.txt
	else
		touch scanf_log.txt
		sed -n '/scanf/p' $file >> scanf_log.txt
	fi
	if [ -e "printf_log.txt" ]; then
		sed -n '/printf/p' $file >> printf_log.txt
	else
		touch printf_log.txt
		sed -n '/printf/p' $file >> printf_log.txt
	fi
else
	echo "You did not enter a C file"
fi


