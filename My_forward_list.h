#pragma once

#include "MyForwardIterator.h"
#include "error_types.h"

//Чтобы определения шаблонов увидели реализацию

template <class Type>
class MyForwardIterator;

template <class Type>
struct My_list_element
{
public:
    My_list_element(Type const& el, My_list_element<Type> *n): m_element(el), m_next(n)
    { 
    }
    
    Type m_element;
    My_list_element<Type>* m_next;
};



template <class Type>
class My_forward_list 
{
public:
    My_forward_list():m_number(0), m_first(NULL), m_last(NULL)
    {
    }
    
    My_forward_list(My_forward_list<Type> const& orig):m_number(0), m_first(NULL), m_last(NULL) //throw(My_forward_list_errors)
    {
        if(orig.is_empty())
            return;
        MyForwardIterator<Type> i=orig.get_beginning();
        while(i!=orig.get_ending())
        {
            add_in_ending(*i);
            i++;
        }
        add_in_ending(*i);
    }
    
    ~My_forward_list()
    {
        clear_list();
    }
   
    MyForwardIterator<Type> get_beginning() const
    {
        return MyForwardIterator<Type>(m_first);
    }
    
    MyForwardIterator<Type> get_ending() const
    {
        return MyForwardIterator<Type>(m_last);
    }
    
    void add_in_beginning(Type const& element) //throw(My_forward_list_errors)
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
    
    void add_in_ending(Type const& element) //throw(My_forward_list_errors)
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
    
    void delete_first() throw(My_forward_list_errors)
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
    
    void delete_last() throw(My_forward_list_errors)
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
            while(a->m_next != m_last)//пока следующий за текущим не послендий 
                a=a->m_next;
            delete m_last;
            m_last=a;
            m_last->m_next=NULL;
            m_number--;
        }
    }
    
    void clear_list()
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
    
    bool is_empty() const
    {
        return m_number==0;
    }
    
    int get_element_number() const
    {
        return m_number;
    }
private:
    int m_number;
    My_list_element<Type> *m_first, *m_last;
};

