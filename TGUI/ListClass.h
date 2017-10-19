#ifndef __LISTCLASS_H_
#define __LISTCLASS_H_

#include "TGUIConfig/tgui_drv_conf.h"

template <class Type> class CircularList;  
template <class Type> class ListNode  
{  
private:  
    Type* m_data;  
    ListNode *m_pnext;  
private:  
    friend class CircularList<Type>;//因为构造newhead的时候需要调用ListNode的私有构造函数  
    ListNode():m_pnext(NULL){};  
		ListNode( Type* item,ListNode<Type> *next){m_data = item ,m_pnext = next;}
    //ListNode(const Type *item,ListNode<Type> *next=NULL):m_data(item),m_pnext(next){};  
    ~ListNode(){m_pnext=NULL;}  
public:  
    Type* Getdata()//留一个接口，使用户能够访问ListNode的数据  
    {return m_data;}  
};  

template<class Type> class CircularList{  
public:  
    CircularList():head(new ListNode<Type>()){  
        head->m_pnext=head; 
				length = 0;		
				currPtr	= head;		
    }  
    ~CircularList(){  
        MakeEmpty();  
        delete head;  
    }  
public:  
    void MakeEmpty();   //clear the list  
		int getLength();		//获取长度
		Type* Next();  
    bool Insert(Type* item);    //insert the data into the nth data of the list  
		bool Remove(Type* item);	  //delete the nth data  
    Type* Get(int n);    				//get the nth data  
  
private:  
    ListNode<Type> *head;  
		int length;
		ListNode<Type> *currPtr;
};

  
template <class Type> void CircularList<Type>::MakeEmpty()  
{  
    ListNode<Type>* pdel=head;  
    while(head->m_pnext != head)   
        {
					pdel=head->m_pnext;  
					head->m_pnext=pdel->m_pnext;  
					delete (pdel->m_data);//-----------------------------删除---------------有疑问
					delete pdel;
				} 
		length = 0;
}  

template <class Type> int CircularList<Type>::getLength()
{
	return length;
}
  
template <class Type> Type* CircularList<Type>::Next()  
{  
    ListNode<Type>* pmove= currPtr->m_pnext;
		currPtr	 = pmove;
    return pmove->m_data;  
}  
 
template <class Type> bool CircularList<Type>::Insert(Type* item)  
{  
    
    ListNode<Type>* pmove=head;   
    pmove=pmove->m_pnext;  
  
    ListNode<Type>* newnode=new ListNode<Type>(item,NULL);  
    if(newnode==NULL)  
    { return false;}  
    newnode->m_pnext=pmove->m_pnext;  
    pmove->m_pnext=newnode;
		length ++;
    return true;  
}  
  

template <class Type> bool CircularList<Type>::Remove(Type* item)  
{  
    ListNode<Type>* pmove=head;  
    ListNode<Type>* pdel=head->m_pnext;  
    while(pdel!=head)  
    {  
        if(pdel->m_data == item)  
        {  
            pmove->m_pnext=pdel->m_pnext;    
            delete pdel;  
            pdel=pmove->m_pnext;//主要要重新给pdel赋值，因为前面delete了
						length --;					
            return true;  
					
        }  
        pmove=pmove->m_pnext;  
        pdel=pdel->m_pnext;  
    }  
		return false;
      
}  
  
  
template <class Type> Type* CircularList<Type>::Get(int n)  
{  
    if(n<0||n>length)  
    {  return NULL;}  
    ListNode<Type>* pmove=head->m_pnext;  
    for(int i=0;i<n;i++)  
        pmove=pmove->m_pnext;  
      
    return pmove->m_data;  
}  

#endif //!__LISTCLASS_H_
