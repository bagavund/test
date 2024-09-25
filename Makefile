CC = gcc -Wall -Werror -Wextra -std=c11
TFLAGS = -lcheck
GCOV_FLAGS = --coverage -g -O0

ifeq ($(shell uname -s), Linux)
	TFLAGS = -lcheck -lm -lpthread -lrt -lsubunit
endif

REPORT = ./report/report.html
GCOV = gcovr

SRC = */*.c
OBJ = *.o
LIB = s21_decimal.a

FILE_TEST = FILE_TEST
SRC_TEST = s21_tests.c

all: s21_decimal.a gcov_report

rebuild: clean all

clean:
	make clean_report
	make clean_obj

clean_obj:
	rm -rf *.o *.a *.out *.gcda *.gcno *.info $(FILE_TEST)

clean_report:
	rm -rf report/*.html report/*.css

check:
	cp ../materials/linters/.clang-format .
	find ./ -type f \( -name "*.c" -o -name "*.h" \) -exec clang-format --dry-run --Werror {} \;

format:
	cp ../materials/linters/.clang-format .
	find ./ -type f \( -name "*.c" -o -name "*.h" \) -exec clang-format -i {} \;

test: $(LIB)
	$(CC) $(SRC_TEST) -o $(FILE_TEST) $(LIB) $(TFLAGS)
	./$(FILE_TEST)

s21_decimal.a:
	$(CC) -c $(SRC)
	ar rc $(LIB) $(OBJ)
	ranlib $(LIB)

gcov_report:
	$(CC) $(SRC_TEST) $(TFLAGS) $(GCOV_FLAGS) ${SRC} -o report.out
	./report.out
	mkdir -p report
	$(GCOV) --html --html-details -o $(REPORT)
	rm *.gcda *.gcno
	open $(REPORT)
	make clean_obj
