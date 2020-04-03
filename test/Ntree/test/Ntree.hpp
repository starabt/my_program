#include "Ntree.h"
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
			pRoot->init_node("0");
		return 0;
	}
	return -1;
}
template <class T>
int NTREE<T>::init_tree(const string& symbol_)
{
	pRoot = new T();
	if(pRoot )
	{
		pRoot->init_node(symbol_);
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
			erase_inside(pRoot->childrenNode[pRoot->childrenNode.size()-1],pRoot->childrenNode[pRoot->childrenNode.size()-1]->fatherNode,is_dynamic);
		}
		if(pRoot)
		{
			printf("now is to delete pRoot\n");
			delete pRoot;
			pRoot=NULL;
		}
			
	}
	return 0;
}
/**
 * function:查找某节点是否存在（供外部调用）
 * description：see search_inside，主要改为可通过节点标识修改，方便外部使用
 */
template <class T>
T * NTREE<T>::search(const string& symbol_,T* parentNode) const
{
	T tmpNode;
    tmpNode.init_node(symbol_);
    return search_inside(&tmpNode,parentNode);
}
/**
 * function:释放某个节点（供外部调用）
 * description：see erase_inside，主要改为可通过节点标识修改，方便外部使用
 */
template <class T>
int NTREE<T>::erase(const string& symbol_,T* parentNode,bool is_dynamic)
{
	T tmpNode;
    tmpNode.init_node(symbol_);
    return erase_inside(&tmpNode,parentNode,is_dynamic);
}
/**
 * function:获取某节点下叶子节点数（供外部调用）
 * description：see get_leavesNum_inside，主要改为可通过节点标识修改，方便外部使用
 */
template <class T>
int NTREE<T>::get_leavesNum(const string& symbol_)
{
	T tmpNode;
    tmpNode.init_node(symbol_);
    return get_leavesNum_inside(tmpNode);
}
/**
 * function:获取某节点下子节点数（供外部调用）
 * description：see get_sonNum_inside ，主要改为可通过节点标识修改，方便外部使用
 */
template <class T>
int NTREE<T>::get_sonNum(const string& symbol_)
{
	T tmpNode;
    tmpNode.init_node(symbol_);
    return get_sonNum_inside(tmpNode);
}
/**
 * function:获取某节点下叶子节点集合（供外部调用）
 * description：see get_leavesNodes_inside ，主要改为可通过节点标识修改，方便外部使用
 */
template <class T>
bool NTREE<T>::get_leavesNodes(const string& symbol_,vector<T*>& childNodes)
{
	T tmpNode;
    tmpNode.init_node(symbol_);
    return get_leavesNodes_inside(tmpNode,childNodes);
}
/**
 * function:获取某节点下子节点集合（供外部调用）
 * description：see get_sonNodes_inside ，主要改为可通过节点标识修改，方便外部使用
 */
template <class T>
bool NTREE<T>::get_sonNodes(const string& symbol_,vector<T*>& childNodes)
{
	T tmpNode;
    tmpNode.init_node(symbol_);
    return get_sonNodes_inside(tmpNode,childNodes);
}
/**
 * function:获取某节点下所有节点集合（供外部调用）
 * description：see get_allNodes_inside ，主要改为可通过节点标识修改，方便外部使用
 */
template <class T>
bool NTREE<T>::get_allNodes(const string& symbol_,vector<T*>& childNodes)
{
	T tmpNode;
    tmpNode.init_node(symbol_);
    return get_allNodes_inside(tmpNode,childNodes);
}



/**
 * function:查找节点，如果没输入父节点，则默认从根节点开始遍历
 * description：从上往下递归查找，建议使用方式：search(searchNode,searchNode->fatherNode)，这样是效率最高的
 */
template <class T>
T * NTREE<T>::search_inside(T* searchNode,T* parentNode)const
{
	if(pRoot==NULL)
	{
		printf("pRoot not ever exist \n");
		return NULL;
	}
	if(parentNode==NULL)
		parentNode=pRoot;
	// printf("into search:%s,parentNode:%s\n",searchNode->symbol.c_str(),parentNode->symbol.c_str() );
	T *fatherNodeTmp = NULL;
	if(parentNode->childrenNode.empty() && parentNode->fatherNode ==NULL && !(*parentNode==*pRoot))
	{
		fatherNodeTmp = search_inside(parentNode);
		if(fatherNodeTmp == NULL)
		{
			fatherNodeTmp = parentNode;
		}
	}
	else
		fatherNodeTmp = parentNode;
	// printf("parentNode->symbol:%s,searchNode->symbol:%s\n",parentNode->symbol.c_str(),searchNode->symbol.c_str() );
	if(*fatherNodeTmp==*searchNode)//节点类重载了“==”，此处直接进行指针的比较也是可以的，实际也是重载了
	{
		*searchNode = *fatherNodeTmp;
		return fatherNodeTmp;
	}
	else if(!fatherNodeTmp->childrenNode.empty())
	{
		T * tmpNode=NULL;
		for(unsigned int i=0;i<fatherNodeTmp->childrenNode.size();i++)
		{
			tmpNode = search_inside(searchNode,fatherNodeTmp->childrenNode[i]);
			if(tmpNode!=NULL)
			{
				*searchNode = *tmpNode;
				return tmpNode;
			}
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
	T *fatherNodeTmp = search_inside(parentNode);
	if(fatherNodeTmp!=NULL)
	{
		printf("fatherNodeTmp:%s,size:%d\n", fatherNodeTmp->symbol.c_str(),fatherNodeTmp->childrenNode.size());
		T *insertNodeTmp = search_inside(insertNode,fatherNodeTmp);
		if(insertNodeTmp)
		{
			printf("the node has already exist:%s\n",insertNodeTmp->symbol.c_str() );
			return -2;
		}
		insertNode->fatherNode = fatherNodeTmp;
		T *pnewNode=new T(*insertNode);

		fatherNodeTmp->childrenNode.push_back(pnewNode);
		*insertNode = *pnewNode;//切记不能直接指针赋值，否则insertNode的改变将直接改变树里的相应节点，此处调用了类重载拷贝‘=’
		*parentNode=*fatherNodeTmp;
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
int NTREE<T>::erase_inside(T* eraseNode,T* parentNode,bool is_dynamic)
{
	if(parentNode==NULL)
		parentNode=pRoot;
	printf("\ninto erase_inside node:%s,parentNode:%s,",eraseNode->symbol.c_str(),parentNode->symbol.c_str());
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
	if(parentNode->childrenNode.empty() && parentNode->fatherNode ==NULL)
	{
		fatherNodeTmp = search_inside(parentNode);
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
		T *delNode = search_inside(eraseNode,fatherNodeTmp);
		if(delNode != NULL)
		{
			printf("eraseNode->childrenNode.size():%d\n",delNode->childrenNode.size() );
			while(!delNode->childrenNode.empty())
			{
				erase_inside(delNode->childrenNode[delNode->childrenNode.size()-1],delNode);
			}
			fatherNodeTmp->childrenNode.erase(eraseNode->it);
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
			if(erase_inside(eraseNode,parentNode->childrenNode[i])==0)
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
int NTREE<T>::get_leavesNum_inside(T& node)
{
	T *tmpNode = NULL;
	if(node.childrenNode.empty() && node.fatherNode ==NULL)
	{
		tmpNode = search_inside(&node);
		if(tmpNode == NULL)
		{
			return -1;
		}
	}
	else
		tmpNode = &node;

	int leavesNum = 0;
	if(tmpNode->childrenNode.empty())
		return ++leavesNum;
	else
	{
		for(int i=0;i<tmpNode->childrenNode.size();i++)
		{
			leavesNum+=get_leavesNum_inside(*tmpNode->childrenNode[i]);
		}
		return leavesNum;
	}
}
/**
 * function：获取某节点下一级子节点数
 * return：子节点数
 */
template <class T>
int NTREE<T>::get_sonNum_inside(T& node)
{
	T *tmpNode = search_inside(&node);
	if(tmpNode == NULL)
		return -1;
	if(tmpNode->childrenNode.empty())
		return 0;
	else
		return tmpNode->childrenNode.size();
}
/**
 * function：获取某节点下的叶子节点
 * param node：待获取节点，传入
 * param childNodes：获取到叶子节点集合，传出
 * return：true：成功（包括返回自身），false：找不到节点node
 */
template <class T>
bool NTREE<T>::get_leavesNodes_inside(T& node,vector<T*>& childNodes)
{
	bool bRet = false;
	T *tmpNode = NULL;
	if(node.childrenNode.empty() && node.fatherNode ==NULL)
	{
		tmpNode = search_inside(&node);
		if(tmpNode == NULL)
		{
			return false;
		}
	}
	else
		tmpNode = &node;
	
	if(tmpNode->childrenNode.empty())
	{
		childNodes.push_back(tmpNode);
		return true;
	}
	else
	{
		for(unsigned int i=0;i<tmpNode->childrenNode.size();i++)
		{
			/*只要有一次获取到就返回真*/
			if(get_leavesNodes_inside(*tmpNode->childrenNode[i],childNodes))
				bRet=true;
		}
		return bRet;
	}
}
/**
 * function：获取某节点下的子节点
 * param node：待获取节点，传入
 * param childNodes：获取到子节点集合，传出
 * return：true：成功（包括返回自身），false：找不到节点node
 */
template <class T>
bool NTREE<T>::get_sonNodes_inside(T& node,vector<T*>& childNodes)
{
	T *tmpNode = search_inside(&node);
	if(tmpNode != NULL)
	{
		childNodes.assign(tmpNode->childrenNode.begin(),tmpNode->childrenNode.end()) ;
		return true;
	}
	return false;
}
/**
 * function：获取某节点下的所有节点，包括各级子节点
 * param node：待获取节点，传入
 * param childNodes：获取到的所有节点集合，传出
 * return：true：成功（包括返回自身），false：找不到节点node
 */
template <class T>
bool NTREE<T>::get_allNodes_inside(T& node,vector<T*>& childNodes)
{
	T *tmpNode = NULL;
	if(node.childrenNode.empty() && node.fatherNode ==NULL)
	{
		tmpNode = search_inside(&node);
		if(tmpNode == NULL)
		{
			return false;
		}
	}
	else
		tmpNode = &node;
	if(tmpNode->childrenNode.empty())
	{
		childNodes.push_back(tmpNode);
		return true;
	}
	else
	{
		childNodes.insert(childNodes.end(),tmpNode->childrenNode.begin(),tmpNode->childrenNode.end());
		for(unsigned int i=0;i<tmpNode->childrenNode.size();i++)
		{
			if(!tmpNode->childrenNode[i]->childrenNode.empty())
				get_allNodes_inside(*tmpNode->childrenNode[i],childNodes);
		}
		return true;
	}
	return false;
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
				// showNode->childrenNode[i]->symbol.c_str(),showNode->childrenNode.size() );
			display(showNode->childrenNode[i]);
		}
		
	}
	printf("\n");
}
