.PHONY: clean algebra-tests engine-tests build all run

all: build
build: algebra-tests engine-tests

algebra-tests: algebra_tests.o
	g++ algebra_tests.o -o algebra_tests -L../ -lengine

algebra_tests.o: algebra_tests.cpp
	g++ algebra_tests.cpp -o algebra_tests.o -c -I../

engine-tests: engine_tests.o
	g++ engine_tests.o -o engine_tests -L../ -lengine \
		-lsfml-graphics -lsfml-window -lsfml-system \

engine_tests.o: engine_tests.cpp
	g++ engine_tests.cpp -o engine_tests.o -c -I../

run: build
	./algebra_tests
	./engine_tests

clean:
	rm -f algebra_tests algebra_tests.o
	rm -f engine_tests engine_tests.o
