#ifndef MYFORWARDITERATOR_HPP
#define MYFORWARDITERATOR_HPP

#include <iterator>

#include "My_forward_list.hpp"
#include "error_types.hpp"


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
        MyForwardIterator(const MyForwardIterator &it);
        
        MyForwardIterator operator=(MyForwardIterator const& other);
        
        bool operator==(MyForwardIterator const& other) const;
        bool operator!=(MyForwardIterator const& other) const;
        
        class MyForwardIterator::reference operator*() const throw(My_forward_list_errors); //Аналогии для получения константы?
        operator Type*() const throw(My_forward_list_errors);
        
        
        MyForwardIterator& operator++() throw(My_forward_list_errors);//++a
        MyForwardIterator& operator++(int) throw(My_forward_list_errors);//a++ 
    protected:
        MyForwardIterator(My_list_element<Type>* p);
    private:
        My_list_element<Type>* m_ptr;
};



/*
 * Реализация
 */

template <class Type>
MyForwardIterator<Type>::MyForwardIterator(const MyForwardIterator& it): m_ptr(it.m_ptr)
{
}

template <class Type>
MyForwardIterator<Type>::MyForwardIterator(My_list_element<Type>* p): m_ptr(p)
{
}

template <class Type>
MyForwardIterator<Type> MyForwardIterator<Type>::operator=(MyForwardIterator const& other)
{
    m_ptr=other.m_ptr;
    return *this;
}

template <class Type>
bool MyForwardIterator<Type>::operator==(MyForwardIterator const& other) const
{
    return m_ptr==other.m_ptr;
}

template <class Type>
bool MyForwardIterator<Type>::operator!=(MyForwardIterator const& other) const
{
    return m_ptr!=other.m_ptr;
}

template <class Type>
class MyForwardIterator<Type>::reference MyForwardIterator<Type>::operator*() const throw(My_forward_list_errors)
{
    if(m_ptr==NULL)
        throw(ACCESS_TO_ELEMNT_FROM_EMPTY_LIST);
    return m_ptr->m_element;
}

template <class Type>
MyForwardIterator<Type>::operator Type*() const throw(My_forward_list_errors)
{
    if(m_ptr==NULL)
        throw(ACCESS_TO_ELEMNT_FROM_EMPTY_LIST);
    return &(m_ptr->m_element);
}

template <class Type>
MyForwardIterator<Type>& MyForwardIterator<Type>::operator++() throw(My_forward_list_errors)
{
    if(m_ptr->m_next==NULL)
        throw ITERATOR_HAVE_MOVED_OUTSIDE_LIST;
    My_list_element<Type>* temp=m_ptr;
    m_ptr=m_ptr->m_next;
    return *temp;
}

template <class Type>
MyForwardIterator<Type>& MyForwardIterator<Type>::operator++(int) throw(My_forward_list_errors)
{
    if(m_ptr->m_next==NULL)
        throw ITERATOR_HAVE_MOVED_OUTSIDE_LIST;
    m_ptr=m_ptr->m_next;
    return *this;
}


#endif /* MYFORWARDITERATOR_HPP */

