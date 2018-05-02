#include <fstream> 
#include "Named.hpp"


Named::Named(std::string const& name_str): m_name(name_str)
{
}

Named::~Named()
{
}

std::string Named::name() const
{
    return m_name;
}