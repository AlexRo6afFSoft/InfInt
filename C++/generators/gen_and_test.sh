#!/bin/bash
cd /home/alex/GIT/My/have_repo/Informatics/codes/Alex/templates/big_integer/my/
make build_main
make build_gmp
cd generators
< /dev/urandom tr -dc 0-9 | head -c$2 > num1
< /dev/urandom tr -dc 0-9 | head -c$2 > num2
cat num1
echo
cat num2
echo
echo "------------------------------------";
echo "`cat num1` `cat num2`" > ../unit_tests/inFile$1
echo "GMP:";
time ../exec/GMP.exe < ../unit_tests/inFile$1 > ../unit_tests/outFile$1
echo "My:";
time ../exec/main.exe < ../unit_tests/inFile$1 > /tmp/ans
diff /tmp/ans ../unit_tests/outFile$1
rm num1 num2
cd ..
