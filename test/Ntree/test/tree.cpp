#include "tree.h"
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

typedef enum FILE_TYPE_
{
	TYPE_FILE=0,
	TYPE_DIR,
	UNKNOWN_FILE_TYPE=0xff,
}FILE_TYPE;
class FILE_NODE:public TREE_NODE
{
public:
	FILE_NODE();
	~FILE_NODE();
	FILE_NODE(const FILE_NODE& b);
	// FILE_NODE &operator=(FILE_NODE &b)
	// {

	// }
	FILE_TYPE file_type;
	std::string name;
	std::string path;
	long int size;
	void init_file_msg(std::string name_,std::string path_,FILE_TYPE file_type_=UNKNOWN_FILE_TYPE,long int size_=0);

};

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
    //  this->childrenNode.push_back(b.childrenNode[i]);
    // }
}
TREE_NODE::~TREE_NODE()
{}
void TREE_NODE::init_node(string symbol_)
{
    symbol = symbol_;
    return;
}


FILE_NODE::FILE_NODE():
file_type(UNKNOWN_FILE_TYPE)
{

}
FILE_NODE::~FILE_NODE()
{}
FILE_NODE::FILE_NODE(const FILE_NODE& b):TREE_NODE(b)
{
    this->file_type = b.file_type;
    this->name = b.name;
    this->path = b.path;
    this->size = b.size;
}
template <class T>
NTREE<T>::NTREE():
pRoot(NULL)
{}
template <class T>
NTREE<T>::~NTREE()
{}
template <class T>
int NTREE<T>::init_tree(T* rootNode)
{
	if(rootNode)
		pRoot = new T(*rootNode);
	else
		pRoot = new T();
	if(pRoot )
	{
		if(!rootNode)
			pRoot->symbol = "0";
		return 0;
	}
	return -1;
}
/**
 * function：树去初始化，每个树实例化对象都要调用这个函数回收线程
 * description：每删除一个节点，大小缩小，因此每次从最后面那个节点开始回收
 */
template <class T>
int NTREE<T>::deinit_tree(bool is_dynamic)
{
	if(pRoot)
	{
		while(!pRoot->childrenNode.empty())
		{
			erase(pRoot->childrenNode[pRoot->childrenNode.size()-1],pRoot->childrenNode[pRoot->childrenNode.size()-1]->fatherNode,is_dynamic);
			// int sizeTmp = pRoot->childrenNode.size();
			// for(int i=0;i<sizeTmp;i++)
			// {
			// 	erase(pRoot->childrenNode[i],pRoot->childrenNode[i]->fatherNode,is_dynamic);
			// }
		}
		printf("now is to delete pRoot\n");
		delete pRoot;
		pRoot=NULL;
	}
	return 0;
}
/**
 * function:查找节点，如果没输入父节点，则默认从根节点开始遍历
 * description：从上往下递归查找，建议使用方式：search(searchNode,searchNode->fatherNode)，这样是效率最高的
 */
template <class T>
T * NTREE<T>::search(T* searchNode,T* parentNode)const
{

	if(pRoot==NULL)
	{
		printf("pRoot not ever exist \n");
		return NULL;
	}
	if(parentNode==NULL)
		parentNode=pRoot;
	// printf("parentNode->symbol:%s,searchNode->symbol:%s\n",parentNode->symbol.c_str(),searchNode->symbol.c_str() );
	if(*parentNode==*searchNode)//节点类重载了“==”，此处直接进行指针的比较也是可以的，实际也是重载了
		return parentNode;
	else if(!parentNode->childrenNode.empty())
	{
		T * tmpNode=NULL;
		for(int i=0;i<parentNode->childrenNode.size();i++)
		{
			tmpNode = search(searchNode,parentNode->childrenNode[i]);
			if(tmpNode!=NULL)
				return tmpNode;
		}
		return NULL;
	}
	return NULL;
}
/**
 * function：插入节点接口，此处必须指明父节点，新插入的节点会新申请对象分配内存
 * description：插入成功后，该节点所指向的父节点指针信息会更新
 * return：0：成功 -1：失败 -2：已存在
 */
template <class T>
int NTREE<T>::insert(T* insertNode,T* parentNode)
{
	printf("into insert insertNode:%s,parentNode,%s,",insertNode->symbol.c_str(),parentNode->symbol.c_str());
	if(pRoot==NULL)
	{
		printf("pRoot not ever exist \n");
		return -1;
	}
	T *fatherNodeTmp = search(parentNode);
	if(fatherNodeTmp!=NULL)
	{
		printf("fatherNodeTmp:%s,size:%d\n", fatherNodeTmp->symbol.c_str(),fatherNodeTmp->childrenNode.size());
		T *insertNodeTmp = search(insertNode,fatherNodeTmp);
		if(insertNodeTmp)
		{
			printf("the node has already exist:%s\n",insertNodeTmp->symbol.c_str() );
			return -2;
		}
		insertNode->fatherNode = fatherNodeTmp;
		T *pnewNode=new T(*insertNode);
		
		// T *pnewNode=insertNode;
		// T *pnewNode=new T();
		// *pnewNode = *insertNode;
		
		
		fatherNodeTmp->childrenNode.push_back(pnewNode);
		*insertNode = *pnewNode;//切记不能直接指针赋值，否则insertNode的改变将直接改变树里的相应节点，此处调用了类重载拷贝‘=’
		return 0;
	}
	else
	{
		printf("fatherNodeTmp is NULL,%s\n",parentNode->symbol.c_str() );
		return -1;
	}
}
/**
 * function：删除某个节点，
 * description：在父节点下搜索该节点，进行删除并回收资源，
 * 				如果该节点下还有子节点，将先递归删除其下节点，最后再将其删除
 */
template <class T>
int NTREE<T>::erase(T* eraseNode,T* parentNode,bool is_dynamic)
{
	if(parentNode==NULL)
		parentNode=pRoot;
	printf("\ninto erase node:%s,parentNode:%s,",eraseNode->symbol.c_str(),parentNode->symbol.c_str());
	// printf("parentNode:%s,size:%d\n",parentNode->symbol.c_str(),parentNode->childrenNode.size() );
	if(pRoot==NULL)
	{
		printf("pRoot not ever exist \n");
		return -1;
	}
	if(eraseNode==pRoot)
	{
		printf("pRoot cannot be erase\n");
		return -1;
	}
	T *fatherNodeTmp = NULL;
	if(parentNode->childrenNode.empty())
	{
		fatherNodeTmp = search(parentNode);
		if(fatherNodeTmp == NULL)
		{
			fatherNodeTmp = parentNode;
		}
	}
	else
		fatherNodeTmp = parentNode;
	int sizeTmp = 0;
	 eraseNode->it = find_if(fatherNodeTmp->childrenNode.begin(),fatherNodeTmp->childrenNode.end(),findObj(*eraseNode));

	if(eraseNode->it != fatherNodeTmp->childrenNode.end())
	{
		T *delNode = search(eraseNode,fatherNodeTmp);
		if(delNode != NULL)
		{
			printf("eraseNode->childrenNode.size():%d\n",delNode->childrenNode.size() );
			while(!delNode->childrenNode.empty())
			{
				erase(delNode->childrenNode[delNode->childrenNode.size()-1],delNode);
				// sizeTmp = delNode->childrenNode.size();
				// for(int i=0;i<sizeTmp;i++)
				// {
				// 	// printf("into erase again\n");
				// 	erase(delNode->childrenNode[i],delNode);
				// }
			}
			

			fatherNodeTmp->childrenNode.erase(eraseNode->it);
			// if(is_dynamic)
			
			
			printf("\nnow is to delete eraseNode:%s\n",delNode->symbol.c_str());
			delete delNode;
			
			return 0;
		}
			
		else
		{
			printf("delNode is NULL\n");
			return -1;
		}
	}
	else if(!parentNode->childrenNode.empty())
	{
		sizeTmp = parentNode->childrenNode.size();
		for(int i=0;i<sizeTmp;i++)
		{
			if(erase(eraseNode,parentNode->childrenNode[i])==0)
				return 0;
		}
		return -1;
	}
	return -1;
}
/**
 * function：获取节点下最终有多少树叶（没有子节点）
 * return：子节点数
 */
template <class T>
int NTREE<T>::get_leavesNum(T& node)
{
	T *tmpNode = search(&node);
	if(tmpNode == NULL)
		return -1;

	int leavesNum = 0;
	if(tmpNode->childrenNode.empty())
		return ++leavesNum;
	else
	{
		for(int i=0;i<tmpNode->childrenNode.size();i++)
		{
			leavesNum+=get_leavesNum(*tmpNode->childrenNode[i]);
		}
		return leavesNum;
	}
}
/**
 * function：获取某节点下一级子节点数
 * return：子节点数
 */
template <class T>
int NTREE<T>::get_sonNum(T& node)
{
	T *tmpNode = search(&node);
	if(tmpNode == NULL)
		return -1;
	if(tmpNode->childrenNode.empty())
		return 0;
	else
		return tmpNode->childrenNode.size();
}
template <class T>
void NTREE<T>::display(T* showNode)
{
	if(pRoot==NULL)
	{
		printf("pRoot not ever exist \n");
		return ;
	}
	int sizeTmp = 0;
	// printf("%s:%d",showNode->symbol.c_str(),showNode->testNum );
	// printf("showNode.symbol:%s,size:%d\n",showNode->symbol.c_str() ,showNode->childrenNode.size());
	if(showNode->childrenNode.empty())
	{
		printf("\t");
		printf("%s\n",showNode->symbol.c_str() );
		return;
	}
	else
	{
		printf("%s\n",showNode->symbol.c_str() );
		sizeTmp = showNode->childrenNode.size();
		for(int i = 0;i<sizeTmp;i++)
		{
			printf("\t");
			// printf("%s:%d\n",showNode->symbol.c_str(),showNode->testNum );
			// printf("showNode->childrenNode[i].symbol:%s,showNode->childrenNode.size:%d\n",\
				showNode->childrenNode[i]->symbol.c_str(),showNode->childrenNode.size() );
			display(showNode->childrenNode[i]);
		}
		
	}
	printf("\n");
}


#if 1
int main()
{
	#if 0
	int ret = -2;
	NTREE<TREE_NODE> nTree;
	TREE_NODE root; 
	root.init_node("1");
	nTree.init_tree(&root);
	// printf("1111111111111111\n");
	// TREE_NODE node1("1",1);
	TREE_NODE node2;node2.init_node("2");
	TREE_NODE node3;node3.init_node("3");
	TREE_NODE node4;node4.init_node("4");
	TREE_NODE node5;node5.init_node("5");
	TREE_NODE node6;node6.init_node("6");
	TREE_NODE node7;node7.init_node("7");
	TREE_NODE node8;node8.init_node("8");
	TREE_NODE node9;node9.init_node("9");
	TREE_NODE nodea;nodea.init_node("a");
	TREE_NODE nodeb;nodeb.init_node("b");
	TREE_NODE nodec;nodec.init_node("c");

	// TREE_NODE node8("8",8);
	// printf("333333333333333\n");
	ret=nTree.insert(&node2,nTree.pRoot);
	// printf("4444444444ret=%d\n",ret);
	ret=nTree.insert(&node3,nTree.pRoot);
	// printf("5555555555555555ret=%d\n",ret);
	ret=nTree.insert(&node4,&node2);
	// printf("66666666666666ret=%d\n",ret);
	ret=nTree.insert(&node5,&node2);
	TREE_NODE *tmpNode = nTree.search(&node2);
	if(tmpNode == NULL)
	{
		printf("tmpNode is NULL\n");
		return -1;
	}
	printf("tmpNode:%s,size:%d\n",tmpNode->symbol.c_str(),tmpNode->childrenNode.size() );
	nTree.insert(&node6,&node3);
	nTree.insert(&node7,&node3);
	nTree.insert(&node6,&node3);
	tmpNode = nTree.search(&node3);
	if(tmpNode == NULL)
	{
		printf("tmpNode is NULL\n");
		return -1;
	}
	printf("tmpNode:%s,size:%d\n",tmpNode->symbol.c_str(),tmpNode->childrenNode.size() );
	
	nTree.insert(&node8,&node6);
	nTree.insert(&node9,&node6);
	nTree.insert(&nodea,&node6);
	nTree.insert(&nodeb,&node6);
	nTree.insert(&nodec,&node6);
	tmpNode = nTree.search(&node6);
	if(tmpNode == NULL)
	{
		printf("tmpNode is NULL\n");
		return -1;
	}
	printf("tmpNode:%s,size:%d\n",tmpNode->symbol.c_str(),tmpNode->childrenNode.size() );
	// nTree.erase(&node7,&node3);
	
	// nTree.erase(nTree.pRoot);
	nTree.display(nTree.pRoot);
	// nTree.display(&node6);
	nTree.erase(&node6,&node3);
	// nTree.display(&node3);
	
	printf("leaves:%d\n",nTree.get_leavesNum(*nTree.pRoot) );
	printf("leaves:%d\n",nTree.get_leavesNum(node3) );
	printf("sons:%d\n",nTree.get_sonNum(node3) );
	printf("sons:%d\n",nTree.get_sonNum(node6) );
	TREE_NODE nodex = nodec;
	printf("nodex:%s\n", nodex.symbol.c_str());
	nodex.symbol = "x";

	printf("nodex:%s\n", nodex.symbol.c_str());
	printf("nodec:%s\n", nodec.symbol.c_str());
	nTree.deinit_tree();
	#endif
	NTREE<FILE_NODE> fileTree2;
	// delete &node2;
	return 0;
}
#endif