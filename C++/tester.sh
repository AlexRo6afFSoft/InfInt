#!/bin/zsh
for i in `ls unit_tests | grep in` ;
do 
	echo $i;
	echo "MAIN:";
	time ./exec/main.exe < unit_tests/$i > /tmp/ans ; 
	echo -e "\nGMP:";
	time ./exec/GMP.exe < unit_tests/$i > unit_tests/`echo $i | sed "s/in/out/g"`;
	diff /tmp/ans unit_tests/`echo $i | sed "s/in/out/g"`; 
	echo "------------------------------------------";
done
