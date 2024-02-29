.PHONY: all clean rebuild tests dist dvi open install uninstall
CXX = g++ -std=c++17
CXXFLAGS = -Wall -Werror -Wextra -g
PROJECT_FILES = backend/*.cc
LIB = calculator
OS = $(shell uname -s)
TEST_FLAGS = -o test.out -lgtest
TEST_FILES = tests/*.cc

ifeq ($(OS), Linux)
	TEST_FLAGS += -lpthread
endif

all: tests gcov_report check_style install open

$(LIB).a: clean
	$(CXX) $(CXXFLAGS) $(PROJECT_FILES) -c
	ar rcs $(LIB).a *.o
	ranlib $(LIB).a

tests: $(LIB).a
	$(CXX) $(CXXFLAGS) $(TEST_FILES) $(LIB).a $(TEST_FLAGS)
	./test.out

leaks: tests
ifeq ($(OS), Darwin)
	CK_FORK=no leaks --atExit -- ./test.out
else
	valgrind --trace-children=yes --track-fds=yes --track-origins=yes --leak-check=full --show-leak-kinds=all ./test.out
endif

dvi:
	open dvi/about.html

dist:
	rm -rf ../archive_smartcalc/
	mkdir ../archive_smartcalc/
	cp -a **/ Makefile ../build/smartcalc.app ../archive_smartcalc
	cd ../ && tar -cvzf archive_smartcalc.tar.gz archive_smartcalc


gcov_report: clean
	$(CXX) $(CXXFLAGS) -fprofile-arcs -ftest-coverage $(TEST_FILES) $(PROJECT_FILES) $(TEST_FLAGS)
	./test.out
	lcov -t "test" -o test.info --no-external --ignore-errors mismatch -c -d .
	genhtml -o report test.info
ifeq ($(OS), Darwin)
	open ./report/index.html
else
	xdg-open ./report/index.html
endif

check_style:
	clang-format -style=google -n */*.cc */*.h */*.cpp


install: uninstall clean
	mkdir ../build
	cd frontend && qmake6 && make && make clean && rm Makefile && cd ../ && mv frontend/smartcalc.app ../build/

uninstall:
	@rm -rf ../build*

clean:
	@rm -rf *.{a,o,dSYM,out,gcda,gcno,info,stash,user}
	@rm -rf */*.{a,o,dSYM,out,gcda,gcno,info,stash,user}
	@rm -rf gcov_report
	@rm -rf report
	@rm -rf .clang-format
	@rm -rf Tests/test
	@rm -rf ../*.gz
	@rm -rf ../Archive_smartcalc
	@rm -rf gcov
	@rm -rf test
	@rm -rf RESULT.txt


open:
	cd ../build && open smartcalc.app

rebuild: clean all
