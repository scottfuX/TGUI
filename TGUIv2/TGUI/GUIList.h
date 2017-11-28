#ifndef _GUILIST_H_
#define _GUILIST_H_ 


#ifdef __cplusplus
extern "C"  {
#endif

#include "interface_conf/tgui_conf.h"
#include "includes_all.h"
	
extern uint16_t win_id;
extern uint8_t win_buffer[];	
extern uint8_t LCD_BUFADDR[];
#ifdef __cplusplus
}
#endif

//链表Node
template <class T>
class GUINode
{
public:
	GUINode(T* data)
	{
		this->data = data;
		this->nextNode = NULL;
	}
	~GUINode(){}
	T* getData(){return data;}
	void setData(T* data){this->data = data;}
	
	GUINode* getNextNode(){return nextNode;}
	void setNextNode(GUINode* node){this->nextNode = node;}
	
private:
	T* data;
	GUINode* nextNode;
};

template <class T>
class GUIList
{
public:
	GUIList(){
			head = new GUINode<T>(NULL);
			currNode = head;
			num = 0;
	}
	~GUIList(){}
	GUINode<T>* getHead(){return head;}
	uint16_t getNum(){return num;}
		
	
	//重制当前结点 
	void resetCurrNode(){this->currNode = head;}
	//设置当前节点
	void setCurrNode(GUINode<T>* node){currNode = node;}
	//获取当前节点
	GUINode<T>* getCurrNode(){return currNode;}
	//获取当前节点的数据
	T* getCurrData()
	{
		if(currNode->getData() != NULL)
			return currNode->getData();
		return NULL;
	}
	//获取下一个节点的数据
	T* getNextData()
	{
		if(currNode->getNextNode() != NULL)
		{
			T* temp =  currNode->getNextNode()->getData();
			currNode = currNode->getNextNode();
			return temp;
		}
		else
		{
			return NULL;
		}
	}
	
	void addNode(T* t)
	{
		GUINode<T>* node = new GUINode<T>(t);
		node->setNextNode(head->getNextNode());
		head->setNextNode(node);
		num ++;
	}
	
	T* getNode(uint16_t n)
	{
		if(n>num || n<=0)
		{return NULL;}
		GUINode<T>* temp = head;
		for(int i=1;i < n;i++)
		{
			temp = temp->getNextNode();
		}
		return temp->getNextNode()->getData();
	}
	
	
	void delNode(T* data)
	{
		GUINode<T>* temp = head;
		for(int i=1;temp->getNextNode() != NULL && i < num;i++)
		{
			if(temp->getNextNode()->getData() == data)
			{
				break;
			}
			temp = temp->getNextNode();
		}
		if(temp->getNextNode()->getData() == data)
		{
			GUINode<T>* del = temp->getNextNode();
			temp->setNextNode(del->getNextNode());
			del->setNextNode(NULL);
			delete del;///---------------问题出在这
			num--;
		}	
	}
	
	void destroyList()
	{
		GUINode<T>* temp = head;
		GUINode<T>* del;
		while(temp->getNextNode()!= NULL)
		{
			del = temp;
			temp = temp->getNextNode();
			del->setNextNode(NULL);
			delete del->getData();
			delete del;
		}
		delete temp->getData();
		delete temp;
		delete this;
	}
private:
	GUINode<T>* head;
	uint16_t num;
	GUINode<T>* currNode;
};


#endif //! _GUILIST_H_ 
