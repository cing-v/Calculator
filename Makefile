.PHONY: all install uninstall clean dvi dist test gcov_report s21_calc.a clang

GCC = gcc -Wall -Werror -Wextra -std=c11 -g

OS := $(shell uname -s)

ifeq ($(OS), Linux)
	LIB = -lcheck -lrt -lpthread -lsubunit -lm
	OPEN = xdg-open
endif

ifeq ($(OS), Darwin)
	LIB = -lcheck
	OPEN = open
endif

all: clean gcov_report

s21_calc.a: clean
	@$(GCC) -c s21_calculate.c
	@ar rcs s21_calc.a *.o
	@ranlib s21_calc.a
	@rm -rf *.o

test: clean s21_calc.a
	@$(GCC) s21_test.c s21_calc.a $(LIB) -o s21_test
	@./s21_test

gcov_report: clean s21_calc.a
	@$(GCC) s21_calculate.c s21_test.c s21_calc.a --coverage $(LIB) -o s21_test
	@./s21_test
	@mkdir ./report 
	@mv *.g* ./report
	@lcov -c -q -d ./report -o ./report/coverage.info
	@genhtml -q ./report/coverage.info -o ./report
	@$(OPEN) report/index.html

build:
	mkdir calc
	cd calc && cmake -B build "../" && make -C build s21_smartcalc

install: clean
	cmake -B build
	cd build && make

uninstall:
	@rm -rf ./build

dist:
	rm -rf ./SmartCalc
	mkdir ./SmartCalc
	cp s21* ./SmartCalc
	cp main* ./SmartCalc
	cp dvi.html ./SmartCalc
	tar -C ./ -czvf SmartCalc.tgz SmartCalc
	mv SmartCalc.tgz ~/dist
	rm -rf ./SmartCalc

dvi:
	open dvi.html

clang: clean
	@cp ../materials/linters/.clang-format ./.clang-format
	clang-format -style=Google -n ./*.c ./*.cpp ./*.h
	@rm .clang-format

clean:
	@rm -rf s21_calc.a s21_test
	@rm -rf *.gcda *.gcno coverage.info ./report