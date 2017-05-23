#include "Node.h"

Node::Node()
{
}


Node::~Node()
{
}


void Node::AddAdjNode(Node* node) {
	mAdjList.push_back(node);
}