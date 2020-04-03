#include "normalTree.h"
TREE_NODE::TREE_NODE():
pFirstChild(NULL),
pNextBrother(NULL)
{}
TREE_NODE::TREE_NODE(const TREE_NODE &node):
pFirstChild(NULL),
pNextBrother(NULL)
{
	this->attrs = node.attrs;
	this->nodeName = node.nodeName;
	this->content = node.content;
}
TREE_NODE::~TREE_NODE()
{}
NORMAL_TREE::NORMAL_TREE():
pRoot(NULL)
{}
NORMAL_TREE::~NORMAL_TREE()
{}
template <class T>
int NORMAL_TREE::initRootNode(T node)
{
	pCur = new T(node);
	return 0;
}
template <class T>
int NORMAL_TREE::insert(T node)
{
	if(pCur == NULL)
	{
		printf("the current node is NULL\n");
		return -1;
	}
	T tmpNode = new T(node);


}