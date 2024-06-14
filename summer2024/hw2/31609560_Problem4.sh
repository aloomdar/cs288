#!/bin/bash

touch new.txt name.txt bday.txt temp.txt
echo "Enter a file name:"
read file
grep -E "[a-zA-Z]+ [a-zA-Z]+, [0-9]{4}-[0-9]{2}-[0-9]{2}, [a-zA-Z]+ [a-zA-Z]+, [a-zA-Z]+" "$file" >> new.txt
grep -Eo "^([a-zA-Z]+ [a-zA-Z])" new.txt >> name.txt
grep -Eo "[0-9]{4}" new.txt >> bday.txt	

while read num 
do
	age=$((2024-$num))
	while read name
	do
		echo "$name": "$age" >> temp.txt
		sed -i '1d' name.txt
		break
	done < name.txt
	sed -i '1d' bday.txt
done < bday.txt

sort -k 3 temp.txt >> sorted.txt
cat sorted.txt

rm new.txt name.txt bday.txt temp.txt
