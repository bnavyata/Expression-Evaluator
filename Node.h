#pragma once
#include <string>
#include <vector>
using namespace std;

class Node
{
	friend class ExpressionEvaluator;
protected:
	vector<Node*> mAdjList;
	bool mVisited;
public:
	Node();
	virtual ~Node();

	void AddAdjNode(Node* node);
	bool IsVisited() const { return mVisited; }
	void SetVisited(bool visited) {	mVisited = visited;	}
};


class IntNode : public Node {
private:
	unsigned int val;
public:
	IntNode(unsigned int n):val(n){
		Node::mVisited = false;
	}

	unsigned int GetVal() const{
		return val;
	}
};


class VarNode : public Node {
private:
	string name;
public:
	VarNode(string _name):name(_name) {
		Node::mVisited = false;
	}

	string GetName() const {
		return name;
	}
};