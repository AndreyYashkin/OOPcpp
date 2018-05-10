#pragma once

#include <string>
#include "Printable.h"


class Named: public Printable
{
public:
    Named(std::string const& name_str): m_name(name_str)
    {
    }
    
    virtual std::string get_info() const
    {
        return m_name;
    }
	
    std::string const& get_name() const
    {
        return m_name;
    }
private:
    std::string const m_name;
};
