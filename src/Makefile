CC=g++
CFLAGS =-Wall -Werror  -Wextra -std=c++17 -lm
CFLAGS_TEST_UBUNTU =-pthread -lgtest -lgtest_main -lrt
CFLAGS_TEST_MAC =-lgtest -lgtest_main -pthread
SOURCE = 
OBJECTS =$(SOURCE:.cc=.o)
H_SOURCE =./*.h ./lib/*.h ./lib/*.tpp
TEST_SOURCE = ./tests/containers_*_test.cc

ifeq ($(shell uname -s),Linux)
	OUTFILE_TEST =local_test.app
	OS_TYPE=--coverage $(TEST_SOURCE) $(SOURCE) $(CFLAGS_TEST_UBUNTU) -o $(OUTFILE_TEST)
	OPEN = xdg-open
else ifeq ($(shell uname -s),Darwin)
	OUTFILE_TEST =local_test
	OS_TYPE=--coverage $(TEST_SOURCE) $(SOURCE) $(CFLAGS_TEST_MAC) -o $(OUTFILE_TEST)
	OPEN = open
endif

all: test

test_build: $(SOURCE) $(TEST_SOURCE)
	$(CC) $(CFLAGS) $(OS_TYPE)

test: clean test_build
	./$(OUTFILE_TEST)
	rm -f *.gc*

gcov_report: test_build
	./$(OUTFILE_TEST)
	lcov --no-external -t "test" -o $(OUTFILE_TEST).info -c -d .
	genhtml -o report $(OUTFILE_TEST).info
	$(OPEN) report/index.html

leaks: test_build
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes -s ./$(OUTFILE_TEST)

clean:
	rm -rf report *.o *.gc* *.info $(OUTFILE_TEST)

rebuild: all
