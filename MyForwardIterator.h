#pragma once

#include <iterator>

#include "My_forward_list.h"
#include "error_types.h"


//т.к он еще неизвестен 
template <class Type>
class My_forward_list;

template <class Type>
class My_list_element;

//Умеет почти все что forward_iterator должен уметь...
//Можно без опасений пользоваться пока не добавим/удалим элемент в список
template <class Type>
class MyForwardIterator: public std::iterator<std::forward_iterator_tag, Type>
{
    friend class My_forward_list<Type>;
    public:
        MyForwardIterator(const MyForwardIterator &it): m_ptr(it.m_ptr)
        {  
        }
        
        MyForwardIterator operator=(MyForwardIterator const& other)
        {
            m_ptr=other.m_ptr;
            return *this;
        }
        
        bool operator==(MyForwardIterator const& other) const
        {
            return m_ptr==other.m_ptr;
        }
        bool operator!=(MyForwardIterator const& other) const
        {
            return m_ptr!=other.m_ptr;
        }
        
        typename MyForwardIterator::reference operator*() const throw(My_forward_list_errors) //Аналогии для получения константы?
        {
            if(m_ptr==NULL)
                throw(ACCESS_TO_ELEMNT_FROM_EMPTY_LIST);
            return m_ptr->m_element;
        }
        
        operator Type*() const throw(My_forward_list_errors)
        {
            if(m_ptr==NULL)
                throw(ACCESS_TO_ELEMNT_FROM_EMPTY_LIST);
            return &(m_ptr->m_element);
        }
        
        MyForwardIterator& operator++() throw(My_forward_list_errors)//++a
        {
            if(m_ptr->m_next==NULL)
                throw ITERATOR_HAVE_MOVED_OUTSIDE_LIST;
            My_list_element<Type>* temp=m_ptr;
            m_ptr=m_ptr->m_next;
            return *temp;
        }
        
        MyForwardIterator& operator++(int) throw(My_forward_list_errors)//a++ 
        {
            if(m_ptr->m_next==NULL)
                throw ITERATOR_HAVE_MOVED_OUTSIDE_LIST;
            m_ptr=m_ptr->m_next;
            return *this;
        }
        
    protected:
        MyForwardIterator(My_list_element<Type>* p): m_ptr(p)
        {
        }
    private:
        My_list_element<Type>* m_ptr;
};
