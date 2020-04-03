#include "tree.h"
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
int NTREE<T>::init_tree(string symbol_)
{
	pRoot = new T();
	if(pRoot )
	{
		pRoot->init_node(symbol_);
		return 0;
	}
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
	// printf("into search:%s,parentNode:%s\n",searchNode->symbol.c_str(),parentNode->symbol.c_str() );
	T *fatherNodeTmp = NULL;
	if(parentNode->childrenNode.empty() && parentNode->fatherNode ==NULL && !(*parentNode==*pRoot))
	{
		fatherNodeTmp = search(parentNode);
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
		for(int i=0;i<fatherNodeTmp->childrenNode.size();i++)
		{
			tmpNode = search(searchNode,fatherNodeTmp->childrenNode[i]);
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
	if(parentNode->childrenNode.empty() && parentNode->fatherNode ==NULL)
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
	T *tmpNode = NULL;
	if(node.childrenNode.empty() && node.fatherNode ==NULL)
	{
		tmpNode = search(&node);
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
vector<T*> NTREE<T>::get_leavesNodes(T& node)
{
	vector<T*> leavesNodes;
	T *tmpNode = NULL;
	if(node.childrenNode.empty() && node.fatherNode ==NULL)
	{
		tmpNode = search(&node);
		if(tmpNode == NULL)
		{
			return leavesNodes;
		}
	}
	else
		tmpNode = &node;
	
	if(tmpNode->childrenNode.empty())
	{
		leavesNodes.push_back(tmpNode);
		return leavesNodes;
	}
	else
	{
		for(int i=0;i<tmpNode->childrenNode.size();i++)
		{
			vector<T*> tmpNodes = get_leavesNodes(*tmpNode->childrenNode[i]);
			leavesNodes.insert(leavesNodes.end(),tmpNodes.begin(),tmpNodes.end());
		}
		return leavesNodes;
	}
}
template <class T>
vector<T*> NTREE<T>::get_sonNodes(T& node)
{
	T *tmpNode = search(&node);
	if(tmpNode == NULL)
		return node.childrenNode;
	return tmpNode->childrenNode;
}
template <class T>
vector<T*> NTREE<T>::get_allNodes(T& node)
{
	vector<T*> leavesNodes;
	T *tmpNode = NULL;
	if(node.childrenNode.empty() && node.fatherNode ==NULL)
	{
		tmpNode = search(&node);
		if(tmpNode == NULL)
		{
			return leavesNodes;
		}
	}
	else
		tmpNode = &node;
	if(!tmpNode->childrenNode.empty())
	{
		leavesNodes.insert(leavesNodes.end(),tmpNode->childrenNode.begin(),tmpNode->childrenNode.end());
		for(int i=0;i<tmpNode->childrenNode.size();i++)
		{
			if(!tmpNode->childrenNode[i]->childrenNode.empty())
			{
				vector<T*> tmpNodes = get_leavesNodes(*tmpNode->childrenNode[i]);
				leavesNodes.insert(leavesNodes.end(),tmpNodes.begin(),tmpNodes.end());
			}
				
		}
		return leavesNodes;
	}
	return leavesNodes;
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