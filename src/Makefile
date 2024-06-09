STDFLAGS = -Wall -Werror -Wextra
STD = -std=c++17
CHECKLIBS = -lgtest
LIB = s21_matrix_oop.a
TESTS = ./tests/unit_tests.cc
OS := $(shell uname -s)

ifeq ($(OS), Linux)
    CHECKLIBS += -lm -lsubunit --coverage  
endif

all: clean s21_matrix_oop.a test

build:
	g++ -c $(STDFLAGS) $(STD) lib/s21_matrix_oop.cc

s21_matrix_oop.a: build
	ar rcs $(LIB) s21_matrix_oop.o
	ranlib $(LIB)

test:
	g++ $(STDFLAGS) $(STD) $(TESTS) $(LIB) $(CHECKLIBS) -o unit_test 
	./unit_test

gcov_report: clean
	g++ $(STDFLAGS) $(TESTS) lib/s21_matrix_oop.cc $(CHECKLIBS) -o unit_test
	./unit_test
	lcov -t "gcov" -o gcov.info -c -d .  
	genhtml -o report gcov.info

clang:
	clang-format -style=Google -n lib/*.cc lib/*.h tests/unit_tests.cc

clean:
	rm -rf a.out *.o *.a
	rm -rf unit_test *.gcda *.gcno
	rm -rf report *.info

leak:
	leaks -atExit -- ./unit_test

valgrind:
	valgrind ./unit_test