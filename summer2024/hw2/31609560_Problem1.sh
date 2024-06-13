#!/bin/bash

threeAmin=$(grep -hio 'a*.*a.*a.*a.*a*' dictionary.txt | wc -l)

echo "Number of words with at least three a's:" $threeAmin

v1=$(grep -E '^[^e]+e[^e]+e[^e]+e[^e]*$' dictionary.txt | wc -l)
v2=$(grep -E '^E[^e]+e[^e]+e[^e]*$' dictionary.txt | wc -l)
total=$(($v1 + $v2))
echo "Number of words with exactly three e's:" $total

touch doubleE.txt
grep -Eh '[a-zA-Z]*e{2,}[a-zA-Z]*' dictionary.txt > doubleE.txt

touch mostCommonThree.txt
grep -Eo '.{4}$' doubleE.txt > mostCommonThree.txt

touch sorting.txt
sort mostCommonThree.txt | uniq -cd > sorting.txt
touch sorted.txt
sort -nr sorting.txt > sorted.txt

echo "Most Common Final Three Letters and the Number of Occurrences:"
head -3 sorted.txt

rm doubleE.txt mostCommonThree.txt sorting.txt sorted.txt
