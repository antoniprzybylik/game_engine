.PHONY: clean algebra-tests engine-tests all run

all: algebra-tests engine-tests

algebra-tests:
	g++ algebra_tests.cpp -o algebra_tests -I../ -L../ -lengine

engine-tests:
	g++ engine_tests.cpp -o engine_tests -I../ -L../ -lengine \
		-lsfml-graphics -lsfml-window -lsfml-system

run:
	./algebra_tests
	./engine_tests

clean:
	rm -f algebra_tests
	rm -f engine_tests
