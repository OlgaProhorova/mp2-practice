#pragma once

#include <stdlib.h>

template <typename T>
class TLink
{
	public:
		T data;
		TLink *next;
		TLink(); 
		TLink(T d, TLink<T>* nx = NULL); 				   
		bool operator <(const TLink& lin) const; 	 
		bool operator >(const TLink& lin) const; 
};

template <typename T>
TLink<T>::TLink()
{
	next = NULL;
};

template <typename T>
TLink<T>::TLink(T d, TLink<T>* nx = NULL)
{
	next=nx;
	data=d;
};

template <typename T>
bool TLink<T>::operator <(const TLink& lin) const
{
	return (data<lin.data);
}; 	 

template <typename T>
bool TLink<T>::operator >(const TLink& lin) const
{
	return (data>lin.data);	
}; 

template <typename T>
class TRingList
{
	private:
		TLink <T> *head, *curr;
	public:
		TRingList();
		TRingList(const TRingList<T> &list);
		~TRingList();
		void Insert(T data);
		void InsertTail(T data);
		TRingList<T>& operator =(const TRingList<T> &a);		    
		bool operator ==(const TRingList<T>& sp) const;								
		bool operator !=(const TRingList<T>& sp) const;
		void Reset();
		bool IsNotEnded() const;
		void GetNext();     
		TLink<T>* GetCurr() const;
		void Clean();
};

template <typename T>
TRingList<T>::TRingList()
{
	head=new TLink<T>;
	head->next=head;
	curr=head;
};

template <typename T>
void TRingList<T>::Clean()
{
	TLink<T>* tmp = head->next;   
	while (tmp != head)                   
	{
		TLink<T>* tmp2 = tmp->next;        
		delete tmp;                           
		tmp = tmp2;                                
	}
	head->next = head;                          
};

template <typename T>
TRingList<T>::TRingList(const TRingList<T> &list) 
{	
	head = new TLink<T>;             
	TLink<T>* A = list.head;
	TLink<T>* B = head;
	if ( A->next == list.head)
	{
		head->next = head;
		return;
	}
	while (A->next != list.head)
	{
		A = A->next;
		B->next = new TLink<T>(A->data);
		B = B->next;
	} 
	B->next = head;
	curr = head -> next;
};

template <typename T>
TRingList<T>::~TRingList()
{	 
	Clean();
	delete head;
};

template <typename T>
void TRingList<T>::Insert(T data)
{
	TLink<T>* tmp = head;
	TLink<T>* elem = new TLink<T>(data);    
	while ((tmp->next != head) && (*(tmp->next) < *elem))
		tmp = tmp->next;
	TLink<T>* tmp2 = tmp->next;
	tmp->next = elem;
	tmp->next->next = tmp2;	
};

template <typename T>
void TRingList<T>::Reset()
{
	curr = head->next;
};

template <typename T>
bool TRingList<T>::IsNotEnded() const
{
	return (!(curr == head));
};

template <typename T>
void TRingList<T>::GetNext()
{
	curr = curr->next;
};

template <typename T>
TLink<T>* TRingList<T>::GetCurr() const 
{
	return curr;
};

template <typename T>
TRingList<T>& TRingList<T>::operator =(const TRingList<T> &a)
{
	Clean();
	TLink<T>* A = a.head;
	TLink<T>* B = head;
	while (A->next != a.head)
	{
		A = A->next;
		B->next = new TLink<T>(A->data);
		B = B->next;
	}
	B->next = head;
	curr = head;
	return *this;
};		    

template <typename T>
bool TRingList<T>::operator ==(const TRingList<T>& sp) const 
{
	bool res = true;
	if (this != &sp)
	{
		TLink<T>* a = head->next;
		TLink<T>* b = sp.head->next;		
		while ((a->data == b->data)&&(a != head)&&(b != sp.head))
		{
			a = a->next;
			b = b->next;	
		}
		if ((a != head)||(b != sp.head))
			res = false;
	}
	return res;
};								

template <typename T>
bool TRingList<T>::operator !=(const TRingList<T>& sp) const
{
	return !(*this == sp);
};

template <typename T>
void TRingList<T>::InsertTail(T data)
{
	Reset();
	while (curr ->next != head) GetNext();
	TLink<T>* tmp = curr->next;
	curr->next = new TLink<T>(data);
	curr->next->next = tmp;
};