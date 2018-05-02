#ifndef MY_FORWARD_LIST_HPP
#define MY_FORWARD_LIST_HPP

#include "MyForwardIterator.hpp"
#include "error_types.hpp"

//Чтобы определения шаблонов увидели реализацию

template <class Type>
class MyForwardIterator;

template <class Type>
class My_list_element
{
public:
    My_list_element(Type const& el, My_list_element<Type> *n): m_element(el), m_next(n)
    { 
    }
    virtual ~My_list_element()
    {   
    }
    Type m_element;
    My_list_element<Type>* m_next;
};



template <class Type>
class My_forward_list 
{
public:
    My_forward_list();
    My_forward_list(My_forward_list<Type> const& orig); //throw(My_forward_list_errors) ---
    virtual ~My_forward_list();
   
    MyForwardIterator<Type> m_get_beginning() const;
    MyForwardIterator<Type> m_get_ending() const;
    
    void m_add_in_beginning(Type const& element); //throw(My_forward_list_errors);
    void m_add_in_ending(Type const& element); //throw(My_forward_list_errors);
    void m_delete_first() throw(My_forward_list_errors);//проверка на пустоту
    void m_delete_last() throw(My_forward_list_errors);
    void m_clear_list();
    bool m_is_empty() const;
    int m_get_element_number() const;
private:
    int m_number;
    My_list_element<Type> *m_first, *m_last;
};


        
/*
 * реализация
 */
template <class Type>
My_forward_list<Type>::My_forward_list():m_number(0), m_first(NULL), m_last(NULL)
{
}

template <class Type>
My_forward_list<Type>::My_forward_list(My_forward_list<Type> const& orig):m_number(0), m_first(NULL), m_last(NULL) //throw(My_forward_list_errors)
{
    if(orig.m_is_empty())
        return;
    MyForwardIterator<Type> i=orig.m_get_beginning();
    while(i!=orig.m_get_ending())
    {
        m_add_in_ending(*i);
        i++;
    }
    m_add_in_ending(*i);
}

template <class Type>
My_forward_list<Type>::~My_forward_list()
{
    m_clear_list();
}

template <class Type>
MyForwardIterator<Type> My_forward_list<Type>::m_get_beginning() const 
{
    return MyForwardIterator<Type>(m_first);
}


template <class Type>
MyForwardIterator<Type> My_forward_list<Type>::m_get_ending() const 
{
    return MyForwardIterator<Type>(m_last);
}


template <class Type>
void My_forward_list<Type>::m_add_in_beginning(Type const& element) //throw(My_forward_list_errors)
//try
{
    if(m_number==0)
        m_first=m_last=new My_list_element<Type>(element, NULL); 
    else
        m_first=new My_list_element<Type>(element, m_first);
    m_number++;
}
/*catch(std::bad_alloc& ba)
{
    throw CANT_ALLOCATE_MEMORY;
}*/

template <class Type>
void My_forward_list<Type>::m_add_in_ending(Type const& element) //throw(My_forward_list_errors)
//try
{
    if(m_number==0)
        m_first=m_last=new My_list_element<Type>(element, NULL); 
    else
    {
        m_last->m_next=new My_list_element<Type>(element, NULL);
        m_last=m_last->m_next;
    }
    m_number++;
}
/*catch(std::bad_alloc& ba)
{
    throw CANT_ALLOCATE_MEMORY;
}*/

template <class Type>
void My_forward_list<Type>::m_delete_first() throw(My_forward_list_errors)
{
    if(m_number==0)
        throw ACCESS_TO_ELEMNT_FROM_EMPTY_LIST;
    else if(m_number==1)
    {
        delete m_first;
        m_first=m_last=NULL;
    }
    else
    {
        My_list_element<Type> *temp=m_first->m_next;
        delete m_first;
        m_first=temp;
    }
    m_number--;
}

template <class Type>
void My_forward_list<Type>::m_delete_last() throw(My_forward_list_errors)
{
    if(m_number==0)
        throw ACCESS_TO_ELEMNT_FROM_EMPTY_LIST;
    else if(m_number==1)
    {
        delete m_first;
        m_first=m_last=NULL;
        m_number=0;
    }
    else
    {
        //ищем предпоследний
        My_list_element<Type>* a=m_first;
       
        while(a->m_next->m_next!=NULL)//пока следующий за текущим не послендий 
            a=a->m_next;
        m_last=a;
        delete m_last->m_next;
        m_last->m_next=NULL;
        m_number--;
    }
}

template <class Type>
void My_forward_list<Type>::m_clear_list()
{
    My_list_element<Type> *temp;
    while(m_first!=NULL)//Пока есть что удалять
    {
        temp=m_first;
        m_first=m_first->m_next;
        delete temp;
    }
    m_number=0;
}

template <class Type>
bool My_forward_list<Type>::m_is_empty() const
{
    return m_number==0;
}

template <class Type>
int My_forward_list<Type>::m_get_element_number() const
{
    return m_number;
}

#endif /* MY_FORWARD_LIST_HPP */

