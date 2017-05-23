#include <iostream>
#include "Node.h"
#include "ExpressionEvaluator.h"
#include <algorithm>

using namespace std;


ExpressionEvaluator::ExpressionEvaluator()
{
}


ExpressionEvaluator::~ExpressionEvaluator()
{
	for (int i = 0; i < mGraph.size(); i++) {
		delete mGraph[i];
	}
}


void ExpressionEvaluator::CreateGraph(const char* filename) {
	FILE *fp;

	fp = fopen(filename, "r");

	if (fp == 0)
	{
		cout << "Could not open file" << endl;
		return;
	}

	char c;
	string str = "";
	Node* currentNode = nullptr;
	while ((c = fgetc(fp)))
	{
		switch (c)
		{
			// Skip spaces
		case ' ': continue;
		// If = char is found, create a new LHS Node value
		case '=': {
			auto it = mNodeDictionary.find(str);
			if (it == mNodeDictionary.end()) {
				VarNode* vn = new VarNode(str);
				mGraph.push_back(vn);
				currentNode = vn;
				mNodeDictionary.insert(make_pair(str, vn));
			}
			else {
				currentNode = it->second;				
				mGraph.push_back(it->second);
			}
			// Reset string
			str = "";
			
			break;
		}
		// If + is found, then store either an IntNode or VarNode based on the value
		case '+': {
			if (isdigit(str[0]))
			{
				IntNode* in = new IntNode(stoi(str));
				currentNode->AddAdjNode(in);
			}
			else {
				auto it = mNodeDictionary.find(str);
				if (it == mNodeDictionary.end()) {
					VarNode* vn = new VarNode(str);
					currentNode->AddAdjNode(vn);
					mNodeDictionary.insert(make_pair(str, vn));
				}
				else {
					currentNode->AddAdjNode(it->second);
				}
			}
			// Reset string
			str = "";
			break;
		}
		case '\n': {
			if (isdigit(str[0]))
			{
				IntNode* in = new IntNode(stoi(str));
				currentNode->AddAdjNode(in);
			}
			else {
				auto it = mNodeDictionary.find(str);
				if (it == mNodeDictionary.end()) {
					VarNode* vn = new VarNode(str);
					currentNode->AddAdjNode(vn);
					mNodeDictionary.insert(make_pair(str, vn));
				}
				else {
					currentNode->AddAdjNode(it->second);
				}
			}
			// Reset string
			str = "";
			break;
		}

		case EOF: {
			if (isdigit(str[0]))
			{
				IntNode* in = new IntNode(stoi(str));
				currentNode->AddAdjNode(in);
			}
			else {
				auto it = mNodeDictionary.find(str);
				if (it == mNodeDictionary.end()) {
					VarNode* vn = new VarNode(str);
					currentNode->AddAdjNode(vn);
					mNodeDictionary.insert(make_pair(str, vn));
				}
				else {
					currentNode->AddAdjNode(it->second);
				}
			}
			return;
		}

		default:
			str += c;

		}
	}
}


void ExpressionEvaluator::TopologicalSortUtil(Node* node, stack<Node*> &stack) {
	node->SetVisited(true);
	for (auto it = node->mAdjList.begin(); it != node->mAdjList.end(); it++) {
		if ((*it)->IsVisited() != true && dynamic_cast<VarNode*>(*it) != NULL)
			TopologicalSortUtil(*it, stack);
	}
	stack.push(node);
}


void ExpressionEvaluator::TopologicalSort() {
	stack<Node*> stack;
	for (auto it = mGraph.begin(); it != mGraph.end(); it++)
	{
		if ((*it)->IsVisited() != true && dynamic_cast<VarNode*>(*it) != NULL)
			TopologicalSortUtil(*it, stack);
	}

	while (!stack.empty()) {
		mNodeOrder.push_back(stack.top());
		stack.pop();
	}
	reverse(mNodeOrder.begin(), mNodeOrder.end());
}

pair<Node*, int> ExpressionEvaluator::Evaluate(Node* node) {
	int sum = 0;
	for (auto it = node->mAdjList.begin(); it != node->mAdjList.end(); it++) {
		if (dynamic_cast<IntNode*>(*it) != NULL) {
			IntNode* in = dynamic_cast<IntNode*>(*it);
			sum += in->GetVal();
		}
		else {
			auto res = mResult.find(*it);
			if (res != mResult.end()) {
				sum += res->second;
			}

		}
	}

	pair<Node*, int> result = make_pair(node, sum);
	mResult.insert(result);
	return result;
}

void ExpressionEvaluator::CommandLineEvaluation() {
	for (auto it = mNodeOrder.begin(); it != mNodeOrder.end(); it++) {
		mEvals.insert(Evaluate(*it));
	}
}

void ExpressionEvaluator::PrintEvalutedResult() {
	vector <string> nodeNames;
	for (auto it = mGraph.begin(); it != mGraph.end(); it++) {
		VarNode* res = dynamic_cast<VarNode*>(*it);
		if (res != NULL) {
			nodeNames.push_back(res->GetName());
		}		
	}

	sort(nodeNames.begin(), nodeNames.end());

	for (auto it = nodeNames.begin(); it != nodeNames.end(); it++) {
		auto res = mNodeDictionary.find(*it);
		auto val = mEvals.find(res->second);
		cout << *it << " = " << val->second << endl;
	}
}