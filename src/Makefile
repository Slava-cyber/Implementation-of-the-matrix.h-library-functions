OS := $(shell uname -s)

# CFLAGS = -c -Wall -Werror -Wextra

all: clean s21_matrix.a test

test: s21_matrix.a s21_test.o
ifeq ($(OS), Darwin)
	gcc s21_test.o s21_matrix.a -lcheck -o Test
	./Test
else
	gcc s21_test.o s21_matrix.a -lcheck -lm -lrt -lpthread -lsubunit -o Test
	./Test
endif

gcov_report: s21_decimal_gcov.o s21_test_gcov.o
ifeq ($(OS), Darwin)
	gcc -fprofile-arcs -ftest-coverage -lcheck s21_test_gcov.o s21_matrix_gcov.o -o Test
else
	gcc s21_test_gcov.o s21_matrix_gcov.o -fprofile-arcs -ftest-coverage -lcheck -lm -lrt -lpthread -lsubunit -o Test
endif
	./Test
	gcov s21_matrix_gcov
	gcov s21_test_gcov
	lcov -t "s21_matrix" -o s21_matrix.info -c -d .
	genhtml -o report s21_matrix.info

s21_test.o: s21_test.c
	gcc $(CFLAGS) s21_test.c -o s21_test.o

s21_decimal.o: s21_matrix.c s21_matrix.h
	gcc $(CFLAGS) s21_matrix.c -o s21_matrix.o 

s21_test_gcov.o: s21_test.c
	gcc -fprofile-arcs -ftest-coverage $(CFLAGS) s21_test.c -o s21_test_gcov.o

s21_matrix_gcov.o: s21_matrix.c s21_decimal.h
	gcc $(CFLAGS) -fprofile-arcs -ftest-coverage s21_matrix.c -o s21_matrix_gcov.o 

clean:
	rm -f *.o Test *.out *.gcov *.gcda *.gcno *.info *.a
	rm -rf ./report

rebuild: clean all

s21_decimal.a: s21_matrix.o
	ar rcs s21_matrix.a s21_matrix.o
	ranlib s21_matrix.a

check:
	cp ../materials/linters/CPPLINT.cfg CPPLINT.cfg
	python3 ../materials/linters/cpplint.py --extension=c *.c
	CK_FORK=no leaks --atExit -- ./Test
