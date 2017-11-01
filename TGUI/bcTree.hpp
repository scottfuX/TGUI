#ifndef __BC_TREE_H_
#define __BC_TREE_H_

#ifdef __cplusplus
extern "C"  {
#endif
	
#include "interface_conf/tgui_conf.h"
	
#ifdef __cplusplus
}
#endif
//#include <iostream> 
//using namespace std;

#define MAX 30 //树节点的最大数



template<class T>
class node 
{
public:
	node()
	{
		child  = nextsibling  = NULL;
	}
	T ele; //节点值
	node*child, *nextsibling;//左儿子右兄弟
};
template<class T>
class Mytree 
{
public:
	Mytree()
	{
		tree  = NULL;
	}
	~Mytree()
	{
		delete tree;
	}

	void CreatTree(node<T>**);//构造孩子兄弟表示法的树
	void AddNode(node<T>);
	T GetParent(node<T>*,T t); //返回树的父亲节点
	T GetLeftChild(node<T>*,T); //返回树的最左儿子
	T GetRightsibling(node<T>*,T); //返回树的最右兄弟
	T GetRoot(node<T>*); //返回树的根节点
	node<T>* RetPoint(T, node<T>*); //返回值为t的节点的指针
	node<T>* RetParentPoint(T, node<T>*);//返回值为t的节点父亲指针
	void preTraverseTree(node<T>*); //递归先序遍历
	void InTraverseTree(node<T>*); //递归中序遍历
	void PostTraverseTree(node<T>*); //递归后序遍历
private:
	node<T> *tree;
};


template<class T>
void Mytree<T>::CreatTree(node<T>**tree) //构造左儿子右兄弟表示的树
{
	//以tree为根节点构建 
	if ((*tree) != NULL)
	{
		node<T>*a  = new node<T>;
		node<T>*b  = new node<T>;
	}
}

template<class T>
T Mytree<T>::GetParent(node<T> *tree, T t) //返回节点值为t的父亲
{
	node<T>*p  = RetParentPoint(t, tree);
	if (p)
		return p->ele;

	else 
		return NULL;
}

void AddNode(node<T>)
{

}

template<class T>
T Mytree<T>::GetRoot(node<T>*tree) //返回树的根节点值
{

	return tree->ele;
}

template<class T>
T Mytree<T>::GetLeftChild(node<T>*tree, T t) //返回树的左儿子
{
	node<T>*p = RetPoint(t, tree);

	if (p&&p->child)
		return p->child->ele;

	else
		return NULL;
}

template<class T>
T Mytree<T>::GetRightsibling(node<T>*tree, T t) //得到树tree的右兄弟
{
	node<T>*p = RetPoint(t, tree);
	if (p&&p->nextsibling)
		return p->nextsibling->ele;

	else 
		return NULL;
}


template<class T>
void Mytree<T>::preTraverseTree(node<T>*tree) //先序递归遍历
{
	if (tree)
	{
		cout  << tree->ele  << " ";
		preTraverseTree(tree->child);
		preTraverseTree(tree->nextsibling);
	}
}

template <class T>
void Mytree<T>::InTraverseTree(node<T>*tree) //中序递归遍历
{
	if (tree)
	{
		InTraverseTree(tree->child);
		cout  << tree->ele  << "";
		InTraverseTree(tree->nextsibling);
	}
}

template<class T>
void Mytree<T>::PostTraverseTree(node<T>*tree) //后序递归遍历
{
	if (tree)
	{
		PostTraverseTree(tree->nextsibling);
		PostTraverseTree(tree->child);
		cout  << tree->ele  << " ";
	}
}

template<class T>
node<T>* Mytree<T>::RetPoint(T t, node<T>* tree) //返回树节点值为t的指针
{
	if (tree)
	{
		if (tree->ele  == t)
			return tree;
		else if (RetPoint(t, tree->child) != NULL)
		{
			return RetPoint(t, tree->child);
		}
		else if (RetPoint(t, tree->nextsibling) != NULL)
		{
			return RetPoint(t, tree->nextsibling);
		}
		else 
			return NULL;
	}
	else 
		return NULL;
}

template<class T>
node<T>* Mytree<T>::RetParentPoint(T t, node<T>*tree)
{
	if (tree&&tree->child) {
		if (tree->ele  == t)
			return tree;
		else if (RetParentPoint(t, tree->child))
			return RetParentPoint(t, tree->child);
		else if (RetParentPoint(t, tree->nextsibling))
			return RetParentPoint(t, tree->nextsibling);
		else 
			return NULL;
	}
}


#endif //__BC_TREE_H_