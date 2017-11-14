#include<iostream>  
using namespace std;  
template <typename T>  
class Queue  
{  
public:  
    Queue()  
    {  
        Node<T> *node=new Node<T>();  
        node->data=NULL;  
        node->next=NULL;  
        qfront=qrear=node;  
    }  
    template <typename T>  
    struct Node  
    {  
        Node<T> *next;  
        T data;  
    };  
    bool empty() const;  
    void pop();  
    T & front();  
    T & back();  
    void push(const T &);  
    int size() const;  
private:  
    Node<T> *qfront,*qrear;  
};  
template <typename T>  
T &Queue<T>::back()  
{  
    if(!empty())  
        return qrear->data;  
}  
template <typename T>  
T &Queue<T>::front()  
{  
    if(!empty())  
    {  
        Node<T> *p=qfront->next;  
        return p->data;  
    }  
}  
template <typename T>  
bool Queue<T>::empty() const  
{  
    if(qfront==qrear)  
        return true;  
    else  
        return false;  
}  
template <typename T>  
void Queue<T>::pop()  
{  
    if(!empty())  
    {  
        Node<T> *p=qfront->next;  
        qfront->next=p->next;  
        if(p==qrear)  
            qrear=qfront;  
        delete p;  
        p=NULL;  
  
    }  
}  
template<typename T>  
void Queue<T>::push(const T & t)  
{  
    Node<T> *node=new Node<T>;  
    node->data=t;  
    node->next=NULL;  
    qrear->next=node;  
    qrear=node;  
}  
template<typename T>  
int Queue<T>::size() const  
{  
    Node<T> *p=qfront;  
    if(empty())  
        return 0;  
    else  
    {  
        int i=1;  
        while(p->next!=qrear)  
        {  
            p=p->next;  
            i++;  
        }  
        return i;  
    }  
}  