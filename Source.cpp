#include "ExpressionEvaluator.h"

int main(int argc, char** argv) {

	string filename = "";
	if(argc > 1) {
		filename = argv[1];
	}
	
	ExpressionEvaluator exp;
	exp.CreateGraph(filename.c_str());
	exp.TopologicalSort();	
	exp.CommandLineEvaluation();
	exp.PrintEvalutedResult();

	return 0;
}