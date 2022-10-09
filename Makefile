CC=gcc
CFLAGS=-Wall -Wextra -Wshadow
ifeq ($(shell uname), Linux)
	CHKFLAGS=-pthread -lcheck_pic -pthread -lrt -lm -lsubunit
else
	CHKFLAGS=-lcheck
endif

all: s21_math.a

clean:
	@rm -rf *.o *.gcda *.gcno *.html *.css *.out test.c *.a test gcov_report

s21_math.o: s21_math.c
	gcc -o s21_math.o $^ -c

s21_math.a: s21_math.o
	ar crs $@ $^

test:
	checkmk clean_mode=1 test.check > test.c
	$(CC) $(CFLAGS) s21_math.c -c -o s21_math_test.o
	$(CC) $(CFLAGS) test.c -c -o test_test.o
	$(CC) test_test.o s21_math_test.o -o $@ $(CHKFLAGS)
	./$@

gcov_report:
	checkmk clean_mode=1 test.check > test.c
	$(CC) $(CFLAGS) --coverage s21_math.c -c -o s21_math_coverage.o
	$(CC) $(CFLAGS) test.c -c -o test_coverage.o
	$(CC) s21_math_coverage.o test_coverage.o -o $@ $(CHKFLAGS) -lgcov
	./$@
	gcovr --html --html-details -o report.html
	open report.html

linter:
	@cp ../materials/linters/CPPLINT.cfg ./
	@find . -name "*.c" -exec python3 ../materials/linters/cpplint.py {} \;
	@find . -name "*.h" -exec python3 ../materials/linters/cpplint.py {} \;
	@rm -f CPPLINT.cfg

.PHONY: linter clean test gcov_report
