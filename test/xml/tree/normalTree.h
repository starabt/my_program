#ifndef NORMALTREE_H_
#define NORMALTREE_H_
#include <iostream>
#include <string>
class TREE_NODE
{
public:
	TREE_NODE();
	TREE_NODE(const TREE_NODE &node);
	virtual ~TREE_NODE();

	std::map<string,string> attrs;  
	string nodeName;
	string content;
	TREE_NODE *pFirstChild;
	TREE_NODE *pNextBrother;
};
template <class T>
class NORMAL_TREE
{
public:
	NORMAL_TREE();
	virtual ~NORMAL_TREE();

	T * pCur;
	int initRootNode(T node);
	int insert(  T node );
	int insertBrother(T node);
	T search()
};
#endif