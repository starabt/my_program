#ifndef NTREE_H
#define NTREE_H
#include <iostream>
#include <vector>
#include <string>
#include <cstring>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <algorithm>
// using namespace std;
using std::vector;
using std::string;
template <class DATAT>
class TREE_NODE
{
public:
	TREE_NODE():fatherNode(NULL),symbol("-1"){
		// this->fatherNode=NULL;
		// this->symbol="-1";
	}
	virtual ~TREE_NODE(){}
	//拷贝构造函数
	TREE_NODE(const TREE_NODE &b){
		this->data = b.data;
		this->symbol = b.symbol;
	    this->fatherNode = b.fatherNode;
	    this->childrenNode.assign(b.childrenNode.begin(),b.childrenNode.end()) ;
	}
	//重载赋值运算符
	TREE_NODE &operator=(TREE_NODE &b){
		this->data = b.data;
		this->symbol = b.symbol;
	    this->fatherNode = b.fatherNode;
	    this->childrenNode.assign(b.childrenNode.begin(),b.childrenNode.end()) ;
		return *this;
	}
	//重载相等运算符
	bool operator==(const TREE_NODE& p)
	{
		return this->symbol==p.symbol?true:false;
	}
	bool operator==(const TREE_NODE* p)
	{
		return this->symbol==p->symbol?true:false;
	}
//user data
	DATAT data;
	//inherit class must rewrite this function
	void init_node(string symbol_,DATAT *data_=NULL){
		if(data_)
			this->data = *data_;
		this->symbol = symbol_;
	}
	
	TREE_NODE *fatherNode;
	vector<TREE_NODE*> childrenNode;
	string symbol;
	typename vector<TREE_NODE*>::iterator it;
private:
	
};

template <class T>
class NTREE
{	
public:
	NTREE();
	virtual ~NTREE();
	class findObj
    {
    public:
        findObj(T whatId):id(whatId)
        {}
        bool operator()(T* node)
        {
            return (*node)==id;
        }
    private:
        T id;
    };
	T *pRoot;
	virtual int init_tree(T* rootNode=NULL);
	virtual int init_tree(string symbol_);
	virtual int deinit_tree(bool is_dynamic=false);
	T * search(T* searchNode,T* parentNode=NULL) const;
	int insert(T* insertNode,T* parentNode);
	int erase(T* eraseNode,T* parentNode=NULL,bool is_dynamic=false);
	int get_leavesNum(T& node);
	int get_sonNum(T& node);
	vector<T*> get_leavesNodes(T& node);
	vector<T*> get_sonNodes(T& node);
	vector<T*> get_allNodes(T& node);
	virtual void display(T* showNode);
};

#endif