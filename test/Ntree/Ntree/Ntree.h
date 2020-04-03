/**
 * Attention:用的时候请引用Ntree.hpp，不要引用Ntree.h，模板类不支持分开编译
 */
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
/**
 * class TREE_NODE:树节点类，只提供默认构造函数 
 * init_node(): 由于此类涉及作为vector等容器对象，涉及匹配性问题，因此为简单起见只提供默认构造函数，
 * 				由此接口进行初始化
 * data : 数据内容，可以是标准数据类型，也可以是自定义类，赋值及初始化操作得自行完成
 * 			如果是类的话，得实现拷贝构造函数，重载赋值运算符=
 * symbol: 节点标识，此值须唯一，用于唯一标识节点
 * 
 */
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
	void init_node(const string& symbol_,DATAT *data_=NULL){
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
	virtual int init_tree(const string& symbol_);
	virtual int deinit_tree(bool is_dynamic=false);
	virtual void display(T* showNode);

	int insert(T* insertNode,T* parentNode);

	T * search(const string& symbol_,T* parentNode=NULL) const;
	int erase(const string& symbol_,T* parentNode=NULL,bool is_dynamic=false);
	int get_leavesNum(const string& symbol_);
	int get_sonNum(const string& symbol_);
	bool get_leavesNodes(const string& symbol_,vector<T*>& childNodes);
	bool get_sonNodes(const string& symbol_,vector<T*>& childNodes);
	bool get_allNodes(const string& symbol_,vector<T*>& childNodes);

private:
	T * search_inside(T* searchNode,T* parentNode=NULL) const;
	int erase_inside(T* eraseNode,T* parentNode=NULL,bool is_dynamic=false);
	int get_leavesNum_inside(T& node);
	int get_sonNum_inside(T& node);
	bool get_leavesNodes_inside(T& node,vector<T*>& childNodes);
	bool get_sonNodes_inside(T& node,vector<T*>& childNodes);
	bool get_allNodes_inside(T& node,vector<T*>& childNodes);
};

#endif