FILES :=                              \
    .travis.yml                       \
    Darwin.h                          \
    Darwin.c++                        \
    Darwin.log                        \
    RunDarwin.c++                     \
    RunDarwin.out                     \
    html                              \
    TestDarwin.c++                    \
    Darwin.pdf                        \
    TestDarwin.out

CXX        := g++-4.8
CXXFLAGS   := -pedantic -std=c++11 -Wall
LDFLAGS    := -lgtest -lgtest_main -pthread
GCOV       := gcov-4.8
GCOVFLAGS  := -fprofile-arcs -ftest-coverage
VALGRIND   := valgrind

all:
	make test
	
check:
	@not_found=0;                             \
    for i in $(FILES);                            \
    do                                            \
        if [ -e $$i ];                            \
        then                                      \
            echo "$$i found";                     \
        else                                      \
            echo "$$i NOT FOUND";                 \
            not_found=`expr "$$not_found" + "1"`; \
        fi                                        \
    done;                                         \
    if [ $$not_found -ne 0 ];                     \
    then                                          \
        echo "$$not_found failures";              \
        exit 1;                                   \
    fi;                                           \
    echo "success";

html: Doxyfile Darwin.h Darwin.c++ TestDarwin.c++
	doxygen Doxyfile
	
Doxyfile:
	doxygen -g

log:
	git log > Darwin.log

test: TestDarwin.out

darwin-tests:
	cd ..
	git clone https://github.com/cs371p-fall-2015/darwin-tests.git

coverage:
	gcov-4.8 -b Darwin.h Darwin.c++

clean:
	rm -f *.gcda
	rm -f *.gcno
	rm -f *.gcov
	rm -f TestDarwin

TestDarwin: Darwin.h Darwin.c++ TestDarwin.c++
	$(CXX) $(CXXFLAGS) $(GCOVFLAGS) Darwin.h Darwin.c++ TestDarwin.c++ -o TestDarwin $(LDFLAGS)

TestDarwin.out: TestDarwin
	$(VALGRIND) ./TestDarwin						> TestDarwin.out 2>&1
	$(GCOV) -b TestDarwin.c++ 	| grep -A 5 "File 'TestDarwin.c++'" 	>> TestDarwin.out
	cat TestDarwin.out

RunDarwin: Darwin.h Darwin.c++ RunDarwin.c++
	$(CXX) $(CXXFLAGS) $(GCOVFLAGS) Darwin.c++ RunDarwin.c++ -o RunDarwin

RunDarwin.tmp: RunDarwin
	./RunDarwin > RunDarwin.tmp