CFLAGS = -ansi -pedantic -g

qq-- : qqminusminus.o parser_t.o tokenizer_t.o analyzer_t.o
	g++ -o qq-- qqminusminus.o parser_t.o tokenizer_t.o analyzer_t.o

qqminusminus.o : qqminusminus.cpp
	g++ -c $(CFLAGS) qqminusminus.cpp

parser_t.o : parser_t.cpp
	g++ -c $(CFLAGS) parser_t.cpp

tokenizer_t.o : tokenizer_t.cpp
	g++ -c $(CFLAGS) tokenizer_t.cpp

analyzer_t.o : analyzer_t.cpp
	g++ -c $(CFLAGS) analyzer_t.cpp
