STD_FLAG = -O2 -Wall -std=c++11
MY_LIBS = -I./include/
GMP_F = -lgmp -lgmpxx

all:  build test run
build: build_main build_gmp build_slow

clean:
	rm *.exe
build_main:
	g++ main.cpp -o exec/main.exe $(STD_FLAG) $(MY_LIBS)
build_gmp:
	g++ GMP.cpp -o exec/GMP.exe $(STD_FLAG) $(MY_LIBS) $(GMP_F)
build_slow:
	g++ slow.cpp -o exec/slow.exe $(STD_FLAG) $(MY_LIBS)
test:
	#./tester.sh
run:
	./main.exe

