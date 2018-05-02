/* 
 * File:   Printable.hpp
 * Author: Andrey
 *
 * Created on 25 марта 2018 г., 20:06
 */

#ifndef PRINTABLE_HPP
#define PRINTABLE_HPP

#include <string>

class Printable
{
public:
    virtual ~Printable();
    
    virtual std::string m_get_info() const = 0;
protected:
    Printable();
};

#endif /* PRINTABLE_HPP */

