/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Named.hpp
 * Author: Andrey
 *
 * Created on 25 марта 2018 г., 21:12
 */

#ifndef NAMED_HPP
#define NAMED_HPP

#include <string>
#include "Printable.hpp"


class Named: public Printable
{
public:
    Named(std::string const& name_str);//от строки должен быть
    virtual ~Named();
    std::string name() const;
private:
    std::string m_name;
};

#endif /* NAMED_HPP */

