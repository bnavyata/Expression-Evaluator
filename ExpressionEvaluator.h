#pragma once
#include "Node.h"
#include <stack>
#include <unordered_map>

class ExpressionEvaluator
{
private:
	vector<Node*> mGraph;
	unordered_map<string, Node*> mNodeDictionary;
	unordered_map<Node*, int> mResult;
	vector<Node*> mNodeOrder;
	unordered_map<Node*, int> mEvals;
	pair<Node*, int> Evaluate(Node* node);
	void TopologicalSortUtil(Node* node, stack<Node*> &Stack);

public:
	ExpressionEvaluator();
	~ExpressionEvaluator();

	void CreateGraph(const char* filename);
	void TopologicalSort();		
	void CommandLineEvaluation();
	void PrintEvalutedResult();
};

