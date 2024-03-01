CC= g++
CFLAGS= -Wall -Wextra -Werror -pedantic -std=c++17
GCOVFLAGS= -fprofile-arcs -ftest-coverage -std=c++17
SOURSES_TEST= ./tests/test*.cc
OS= $(shell uname -s)

ifeq ($(OS), Linux)
	CFLAGS+= -D OS_LINUX
	GTESTFLAGS= -lgtest -pthread -lpthread -lm
	PATHFORINSTALL= $(HOME)/SmartCalc
	APP= build/SmartCalc
	LCOFFLAGS=
endif
ifeq ($(OS), Darwin)
	CFLAGS+= -D OS_MAC
	GTESTFLAGS= -lgtest
	PATHFORINSTALL= $(HOME)/Desktop/SmartCalc
	APP= build/SmartCalc.app
	LCOFFLAGS= --ignore-errors mismatch
endif

all: smart_calc

build: clean
	mkdir build
	cd ./build/ && qmake6 ../qtproject/ &&	make

smart_calc: clean build
	build/SmartCalc.app/Contents/MacOS/SmartCalc

install: uninstall build
	@mkdir $(PATHFORINSTALL)
	@cp -rf $(APP) $(PATHFORINSTALL)
	make clean

uninstall:
	@rm -rf $(PATHFORINSTALL)

dvi:
	texi2dvi SmartCalc.tex
	rm SmartCalc.aux SmartCalc.log SmartCalc.out

dist:
ifeq ($(OS), Darwin)
	make build
	rm -rf ./build/*.dmg
	hdiutil create -volname "SmartCalcV2.0" -srcfolder $(APP) -ov -format UDRW SmartCalc2.0.dmg
	mv SmartCalc2.0.dmg $(PATHFORINSTALL)
endif
ifeq ($(OS), Linux)
	tar -cf SmartCalcV2.0.tar controller/* model/* qtproject/* view/* Makefile
endif

tests: clean
	$(CC) ./model/*.cc -c $(CFLAGS)
	$(CC) $(SOURSES_TEST) -o test *.o $(CFLAGS) $(GTESTFLAGS)
	@./test

gcov_report: clean
	$(CC) ./model/*.cc -c $(CFLAGS)
	$(CC) $(SOURSES_TEST) -o GcovReport ./model/*.cc $(GCOVFLAGS) $(GTESTFLAGS)
	@./GcovReport
	@lcov $(LCOFFLAGS) -no-external -t "GcovReport" -o GcovReport.info -c -d .
	@genhtml -o report GcovReport.info
	@open ./report/index-sort-f.html
	@rm -rf ./*.gcno ./*gcda ./GcovReport.*

clang:
	@cp ../materials/linters/.clang-format .clang-format
	clang-format -n controller/* model/* view/* tests/*
	@rm -rf .clang-format

cppcheck:
	cppcheck --enable=all --suppress=missingIncludeSystem controller/* model/* view/* tests/*

valgrind: tests
	valgrind --tool=memcheck --leak-check=yes ./test

leaks: tests
	leaks -atExit -- ./test

clean:
	rm -rf ./a.out ./test ./GcovReport ./report ./*.o ./smartCalc.a build

single_test: clean
	$(CC) ./model/maincalc.cc -c -std=c++17
	$(CC) ./tests/single_test.cc -o test maincalc.o -std=c++17
	@./test