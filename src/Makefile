CC = g++ -Wall -Werror -Wextra -std=c++17
OBJ = tests/*cc
TEST = -lgtest -coverage
CLP = array/*.tpp list/*.tpp map/*.tpp multiset/*.tpp queue/*.tpp set/*.tpp tree_key_and_value/*.tpp vector/*.tpp tests/*.cc
CLH = list/*.h map/*.h multiset/*.h queue/*.h set/*.h stack/*.h tree_key_and_value/*.h vector/*.h tests/*h

ifeq ($(shell uname),Linux)
    det_OS = -lrt -lpthread -lm
    for_lcov = --ignore-errors mismatch
else
    det_OS = -lpthread
    for_lcov = --ignore-errors inconsistent
endif

all: clean test

test: clean
	$(CC) $(OBJ) -o test $(TEST) $(det_OS)
	./test

gcov_report: test
	lcov -t "result" -o res.info --no-external $(for_lcov) -c -d . 
	genhtml -o report res.info 
	open report/index.html

clean:
	rm -rf *.gcno *.gcda test *.o *.a *.info report

valgrind: clean test
	valgrind -s --tool=memcheck --leak-check=yes ./test

leak: test
	leaks -atExit -- ./test

clang_i: clang_n
	clang-format -style=Google -i $(CLP)
	clang-format -style=Google -i $(CLH)

clang_n:
	clang-format -style=Google -n $(CLP)
	clang-format -style=Google -n $(CLH)

