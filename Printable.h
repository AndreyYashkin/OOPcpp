#pragma once

#include <string>

class Printable
{
public:
    virtual std::string get_info() const = 0;
protected:
    Printable()
    {
    }
};
