#!/bin/bash

export LC_ALL="C"

function loop() {
	total=0
	total_diff=0
	files=("$@")
	for f in "${files[@]}"
	do
		total=$(expr $total + 1)
		echo $total $f
		nm "$f" &> ori
		./ft_nm "$f" &> rep
		out=$(diff ori rep)
		if [[ ! -z "$out" ]]
		then
			total_diff=$(expr $total_diff + 1)
			echo -e "\tDIFF:\033[1;31m" $f "\033[m"
			echo $f >> files_diff
		fi
	done
	echo -e "\tDiff/Total:\033[1;32m" $total_diff "/" $total "\033[m"
}

echo -e "Test: \033[1;34m\"tests/*32.o\"\033[m"
arr=( $(find tests/ -type f -name '*32.o' 2> /dev/null) )
loop "${arr[@]}"
read
rm -f files_diff

echo -e "Test: \033[1;34m\"tests/*64.o\"\033[m"
arr=( $(find tests/ -type f -name '*64.o' 2> /dev/null) )
loop "${arr[@]}"
read
rm -f files_diff

echo -e "Test: \033[1;34m\"tests/*32\"\033[m"
arr=( $(find tests/ -type f -name '*32' 2> /dev/null) )
loop "${arr[@]}"
read
rm -f files_diff

echo -e "Test: \033[1;34m\"tests/*64\"\033[m"
arr=( $(find tests/ -type f -name '*64' 2> /dev/null) )
loop "${arr[@]}"
read
rm -f files_diff

echo -e "Test: \033[1;34m\"ft_nm\"\033[m"
arr=( "ft_nm" )
loop "${arr[@]}"
read
rm -f files_diff

echo -e "Test: \033[1;34m\"./*.o\"\033[m"
arr=( $(find . -type f -name '*.o' 2> /dev/null) )
loop "${arr[@]}"
read
rm -f files_diff

echo -e "Test: \033[1;34m\"corrupted elf32 && elf64\"\033[m"
cp tests/test_facile32 test_facile32_corrupted && sed -i '$d' test_facile32_corrupted
cp tests/test_moins_facile32 test_moins_facile32_corrupted && sed -i '$d' test_moins_facile32_corrupted
cp tests/test_facile64 test_facile64_corrupted && sed -i '$d' test_facile64_corrupted
cp tests/test_moins_facile64 test_moins_facile64_corrupted && sed -i '$d' test_moins_facile64_corrupted
arr=( $(find . -type f -name '*_corrupted' 2> /dev/null) )
loop "${arr[@]}"
read
rm -f files_diff *_corrupted

echo -e "Test: \033[1;34m\"minitalk && push_swap\"\033[m"
git clone https://github.com/acoudert/minitalk
git clone https://github.com/acoudert/push_swap
make -C minitalk all
make -C push_swap all
arr=( $(find . -type f \( -executable -o -name '*.o' \) 2> /dev/null) )
loop "${arr[@]}"
read
rm -rf files_diff minitalk push_swap

rm rep ori
