#ifndef SHAPE_HPP
#define SHAPE_HPP

#include <string>
#include <iostream>  
#include <sstream>
#include <cmath>

#include "Named.hpp"
#include "My_forward_list.hpp"
#include "error_types.hpp"


class Shape: public Named
{
public:
    virtual ~Shape()
    {
        sm_counter--;
    }
    virtual std::string m_get_info() const = 0;
    
    static int m_get_counter()
    {
        return sm_counter;
    }
    friend std::ostream& operator << (std::ostream &s,  Shape const &a)
    {
        return s << a.m_get_info();
    }
protected:
    Shape(std::string const& shape_name): Named(shape_name)
    {
        sm_counter++;
    }
private:
    static int sm_counter;//=0
};


class Point: public Shape
{
public:
    Point(double _x, double _y): Shape(std::string("Point")), m_x(_x), m_y(_y)
    {
    }
    
    Point(Point const& orig): Shape(std::string("Point")), m_x(orig.m_x), m_y(orig.m_y)
    {  
    }
    
    virtual ~Point()
    {
    }
    
    virtual std::string m_get_info() const
    {
        std::stringstream ss;
        ss << name().c_str() << "\nCoordinates: (" << m_x << ", " << m_y << ")\n";
        return ss.str();
    }
    
    double m_get_x() const
    {
        return m_x;
    }
    
    double m_get_y() const
    {
        return m_y;
    }

    friend std::ostream& operator << (std::ostream &s,  Point const &a)
    {
        return s << a.m_get_info();
    }
private:
    double m_x, m_y;
};

class Circle: public Shape
{
public:
    Circle(Point const& c, double _r) throw(Shape_errors): Shape(std::string("Circle")), m_cen(c), m_r(_r) 
    {
        if(m_r<=0)
            throw WRONG_PARAMETERS_FOR_CIRCLE;
    }
    
    virtual ~Circle()
    {
    }
    
    virtual std::string m_get_info() const
    {
        std::stringstream ss;
        ss << name().c_str() << "\nCenter coordinates: (" << m_cen.m_get_x() << ", " << m_cen.m_get_y() << ")\nR=" << m_r << "\nL=" << 2*M_PI*m_r << "\nS=" << M_PI*m_r*m_r << "\n";
        return ss.str();
    }
    friend std::ostream& operator << (std::ostream &s,  Circle const &a)
    {
        return s << a.m_get_info();
    }
private:
    Point m_cen;
    double m_r;
};

class Rect: public Shape
{
public:
    Rect(Point const& _a, Point const& _b) throw(Shape_errors):Shape(std::string("Rect")), m_a(_a), m_b(_b)
    {
        if(m_a.m_get_x()==m_b.m_get_x() || m_a.m_get_y()==m_b.m_get_y())
            throw WRONG_PARAMETERS_FOR_RECT;
    }
    virtual ~Rect()
    {
    }

    virtual std::string m_get_info() const//вывести b, d
    {
        std::stringstream ss;
        ss << name().c_str();
        ss << "\nCoordinates s: a=(" << m_a.m_get_x() << ", " << m_a.m_get_y() << "), c=(" << m_b.m_get_x() << ", " << m_b.m_get_y() << ")\n";
        ss << "L=" << 2*fabs(m_a.m_get_x()-m_b.m_get_x())+2*fabs(m_a.m_get_y()-m_b.m_get_y()) << "\n";
        ss << "S=" << fabs((m_a.m_get_x()-m_b.m_get_x())*(m_a.m_get_y()-m_b.m_get_y())) << "\n";
        return ss.str();
    }
    friend std::ostream& operator << (std::ostream &s,  Rect const &a)
    {
        return s << a.m_get_info();
    }
private:
    Point m_a, m_b;
};

class Square: public Shape
{
public:
    Square(Point const& _a, Point const& _b) throw(Shape_errors):Shape(std::string("Rect")), m_a(_a), m_b(_b)
    {
        if(m_a.m_get_x()==m_b.m_get_x() && m_a.m_get_y()==m_b.m_get_y())
            throw WRONG_PARAMETERS_FOR_SQUARE;
    }
    virtual ~Square()
    {
    }

    virtual std::string m_get_info() const
    {
        std::stringstream ss;
        ss << name().c_str();
        //чисто аналит. геометрия
        ss << "\nCoordinates s: a=(" << m_a.m_get_x() << ", " << m_a.m_get_y() <<
                "), b=(" << (m_a.m_get_x()+m_b.m_get_x())/2 + (m_a.m_get_y()-m_b.m_get_y())/2 << ", " << (m_a.m_get_y()+m_b.m_get_y())/2 - (m_a.m_get_x()-m_b.m_get_x())/2 <<
                "), c=(" << m_b.m_get_x() << ", " << m_b.m_get_y() <<
                "), d=(" << (m_a.m_get_x()+m_b.m_get_x())/2 - (m_a.m_get_y()-m_b.m_get_y())/2 << ", " << (m_a.m_get_y()+m_b.m_get_y())/2 + (m_a.m_get_x()-m_b.m_get_x())/2 << ")\n";//восстанавливаем еще 2 точки 
        
        ss << "L=" << 2.0/sqrt(0.5)*sqrt(fabs((m_a.m_get_x()-m_b.m_get_x())*(m_a.m_get_x()-m_b.m_get_x()) + (m_a.m_get_y()-m_b.m_get_y())*(m_a.m_get_y()-m_b.m_get_y()))) << "\n";
        ss << "S=" << 0.5*((m_a.m_get_x()-m_b.m_get_x())*(m_a.m_get_x()-m_b.m_get_x()) + (m_a.m_get_y()-m_b.m_get_y())*(m_a.m_get_y()-m_b.m_get_y())) << "\n";
        return ss.str();
    }
    friend std::ostream& operator << (std::ostream &s,  Square const &a)
    {
        return s << a.m_get_info();
    }
private:
    Point m_a, m_b;
};

class Polyline : public Shape
{
public:
    Polyline():Shape(std::string("Polyline")), m_verh()
    {
    }
    Polyline(My_forward_list<Point> const &l):Shape(std::string("Polyline")), m_verh(l)
    {
    }
    virtual ~Polyline ()
    {
    }
    
    virtual std::string m_get_info() const
    {
        std::stringstream ss;
        ss << name().c_str() << '\n';
        if(m_verh.m_is_empty())
        {
            ss  << "Vershin net\nL=0\n";
        }
        else if(m_verh.m_get_element_number()==1)
        {
            ss  << "Vershini:\n(" << (*m_verh.m_get_beginning()).m_get_x() << ',' << (*m_verh.m_get_beginning()).m_get_y()<< ')' << "\nL=0\n";
        }
        else
        {
            ss  << "Vershini:\n";
            MyForwardIterator<Point> i=m_verh.m_get_beginning(), j=m_verh.m_get_beginning()++;
            double len=0;
            while(j!=m_verh.m_get_ending())
            {
                ss << '(' << (*i).m_get_x() << ',' << (*i).m_get_y()<< ')' << '\n';
                i++;
                j++;
                len+=sqrt(((*i).m_get_x()-(*j).m_get_x())*((*i).m_get_x()-(*j).m_get_x())+((*i).m_get_y()-(*j).m_get_y())*((*i).m_get_y()-(*j).m_get_y()));
            }
            ss << '(' << (*i).m_get_x() << ',' << (*i).m_get_y()<< ')' << '\n';
            ss << "L=" << len << '\n';
        }
        return ss.str();
    }
    friend std::ostream& operator << (std::ostream &s,  Polyline const &a)
    {
        return s << a.m_get_info();
    }
    
   void m_add_point(Point const& p)
   {
       m_verh.m_add_in_ending(p);
   }
private:
    My_forward_list<Point> m_verh;
};

class Polygon: public Shape
{
public:
    Polygon(My_forward_list<Point> const &l):Shape(std::string("Polygon")), m_verh(l)
    {
        
    }
    virtual ~Polygon()
    {
        
    }

    virtual std::string m_get_info() const
    {
        std::stringstream ss;
        ss << name().c_str() << '\n';
        if(m_verh.m_is_empty())
        {
            ss  << "Vershin net\nL=0\n";
        }
        else if(m_verh.m_get_element_number()==1)
        {
            ss  << "Vershini:\n(" << (*m_verh.m_get_beginning()).m_get_x() << ',' << (*m_verh.m_get_beginning()).m_get_y()<< ')' << "\nL=0\n";
        }
        else
        {
            ss << "Vershini:\n";
            MyForwardIterator<Point> i=m_verh.m_get_beginning(), j=m_verh.m_get_beginning()++;
            double len=0;
            while(j!=m_verh.m_get_ending())
            {
                ss << '(' << (*i).m_get_x() << ',' << (*i).m_get_y()<< ')' << '\n';
                i++;
                j++;
                len+=sqrt(((*i).m_get_x()-(*j).m_get_x())*((*i).m_get_x()-(*j).m_get_x())+((*i).m_get_y()-(*j).m_get_y())*((*i).m_get_y()-(*j).m_get_y()));
            }
            i=m_verh.m_get_beginning();
            j=m_verh.m_get_ending();
            len+=sqrt(((*i).m_get_x()-(*j).m_get_x())*((*i).m_get_x()-(*j).m_get_x())+((*i).m_get_y()-(*j).m_get_y())*((*i).m_get_y()-(*j).m_get_y()));
            ss << '(' << (*i).m_get_x() << ',' << (*i).m_get_y()<< ')' << '\n';
            ss << "L=" << len << '\n';
        }
        return ss.str();
    }
    friend std::ostream& operator << (std::ostream &s,  Polygon const &a)
    {
        return s << a.m_get_info();
    }
private:
    My_forward_list<Point> m_verh;
};

#endif /* SHAPE_HPP */

