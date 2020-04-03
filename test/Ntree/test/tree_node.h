#ifndef TREE_NODE_H_
#define TREE_NODE_H_
#include <iostream>
#include <vector>
#include <string>
#include <cstring>
#include <algorithm>
using namespace std;
class TREE_NODE
{
public:
	TREE_NODE();
	virtual ~TREE_NODE();
	//inherit class must rewrite this function
	TREE_NODE(const TREE_NODE &b);
	//inherit class must rewrite this function
	TREE_NODE &operator=(TREE_NODE &b){
		this->symbol = b.symbol;
		this->fatherNode = b.fatherNode;
		this->childrenNode.assign(b.childrenNode.begin(),b.childrenNode.end()) ;
		
		// for(int i=0;i<b.childrenNode.size();i++)
		// {
		// 	this->childrenNode.push_back(b.childrenNode[i]);
		// }
		return *this;
	}
	// TREE_NODE *operator=(TREE_NODE *b){
	// 	return this;
	// }

	bool operator==(const TREE_NODE& p)
	{
		return this->symbol==p.symbol?true:false;
	}
	bool operator==(const TREE_NODE* p)
	{
		return this->symbol==p->symbol?true:false;
	}
	//inherit class must rewrite this function
	void init_node(string symbol_);
	// int testNum;
	TREE_NODE *fatherNode;
	std::vector<TREE_NODE*> childrenNode;
	string symbol;
	std::vector<TREE_NODE*>::iterator it;
private:
	
};
/*typedef struct TREE_NODE_
{
	int testNum;
	TREE_NODE_ *fatherNode;
	std::vector<TREE_NODE_*> childrenNode;
	string symbol;
	TREE_NODE_(string symbol_,int num)
	{
		testNum=num;
		symbol=symbol_;
		fatherNode=NULL;
	}
}TREE_NODE;*/
#endif