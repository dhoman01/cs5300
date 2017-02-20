all:
    cd brains;
    cpsl

parser.tab.cc parser.tab.hh: parser.yy
	bison parser.yy

lexer.yy.c: lexer.l parser.tab.hh
	flex brainse/lexer.l

cpsl: lexer.yy.c parser.tab.cc parser.tab.hh
	g++ -o cpslc ../main.cpp lexer.yy.c parser.tab.cc Brain.cpp expressions/Expression.cpp statements/Statements.cpp;
    mv cpslc ../cpslc;
    cd ../;
clean:
	rm cpsl lexer.yy.c parser.tab.cc parser.tab.hh