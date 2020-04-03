#include "tree_node.h"
TREE_NODE::TREE_NODE():
fatherNode(NULL),
symbol("1")
{}
/**
 * 拷贝构造函数，每个继承类如果有新的数据项，都要重写各自的拷贝构造函数
 */
TREE_NODE::TREE_NODE(const TREE_NODE &b)
{
	this->symbol = b.symbol;
	this->fatherNode = b.fatherNode;
	this->childrenNode.assign(b.childrenNode.begin(),b.childrenNode.end()) ;
	
	// for(int i=0;i<b.childrenNode.size();i++)
	// {
	// 	this->childrenNode.push_back(b.childrenNode[i]);
	// }
}
TREE_NODE::~TREE_NODE()
{}
void TREE_NODE::init_node(string symbol_)
{
	symbol = symbol_;
	return;
}