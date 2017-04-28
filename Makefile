all: compile

compile: setup parser copy
	echo "Compiling final executable";
	cd build/brains; \
	g++ ../main.cpp Brain.cpp expressions/Expressions.cpp statements/Statements.cpp utils/RegPool.cpp parser/*.cc --std=c++14 -o ../cpslc -g3

setup:
	mkdir -p build
	mkdir -p build/brains
	mkdir -p build/brains/parser
	mkdir -p build/brains/expressions
	mkdir -p build/brains/statements
	mkdir -p build/brains/utils

parser:
	cd project/brains/parser; \
	ls ./; \
	flex -o ../../../build/brains/parser/lexex.yy.cc lexer.l; \
	bison parser.yy; \
	mv parser.tab.* ../../../build/brains/parser/; \
	mv *.hh ../../../build/brains/parser/; \
	cp scanner.hpp ../../../build/brains/parser

copy:	
	cd project/brains; \
	cp expressions/* ../../build/brains/expressions; \
	cp statements/* ../../build/brains/statements; \
	cp utils/* ../../build/brains/utils; \
	cp Brain.* ../../build/brains
	cd project; \
	cp main.cpp ../build

clean:
	rm -r build/

test:
	cd project/tests/integration/; \
	./test.sh;