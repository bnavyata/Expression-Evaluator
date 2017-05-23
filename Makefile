#Variables
MYPROG=ExpressionEvaluator

CC=g++ -std=c++11

all: ExpressionEvaluator.o Node.o main

main: ExpressionEvaluator.o Node.o Source.cpp
		$(CC) -o $(MYPROG) ExpressionEvaluator.o Node.o Source.cpp

Node.o: Node.cpp Node.h
		$(CC) -c Node.cpp Node.h

ExpressionEvaluator.o: ExpressionEvaluator.cpp ExpressionEvaluator.h
		$(CC) -c ExpressionEvaluator.cpp ExpressionEvaluator.h

clean:
	rm -f $(MYPROG) ExpressionEvaluator.h.gch Node.h.gch Node.o ExpressionEvaluator.o