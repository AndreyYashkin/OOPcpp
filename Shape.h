#pragma once

#include <string>
#include <iostream>  
#include <sstream>
#include <cmath>

#include "Printable.h"
#include "My_forward_list.h"
#include "error_types.h"


class Shape: public Printable
{
public:
    virtual ~Shape()
    {
        sm_counter--;
    }
    
    virtual std::string get_info() const = 0;
    
    static int get_counter()
    {
        return sm_counter;
    }
    friend std::ostream& operator << (std::ostream &s,  Shape const &a)
    {
        return s << a.get_info();
    }
protected:
    Shape()
    {
        sm_counter++;
    }
private:
    static int sm_counter;//=0
};


class Point: public Shape
{
public:
    Point(double _x, double _y): m_x(_x), m_y(_y)
    {
    }
    
    Point(Point const& orig): m_x(orig.m_x), m_y(orig.m_y)
    {  
    }
    
    virtual std::string get_info() const
    {
        std::stringstream ss;
        ss << "Point\nCoordinates: (" << m_x << ", " << m_y << ")\n";
        return ss.str();
    }
    
    double get_x() const
    {
        return m_x;
    }
    
    double get_y() const
    {
        return m_y;
    }
    
    friend double get_dist(Point const& a, Point const& b)
    {
        return sqrt((a.m_x-b.m_x)*(a.m_x-b.m_x)+(a.m_y-b.m_y)*(a.m_y-b.m_y));
    }

    friend std::ostream& operator << (std::ostream &s,  Point const &a)
    {
        return s << a.get_info();
    }
private:
    double m_x, m_y;
};

class Circle: public Shape
{
public:
    Circle(Point const& c, double _r) throw(Shape_errors): m_cen(c), m_r(_r) 
    {
        if(m_r<=0)
            throw WRONG_PARAMETERS_FOR_CIRCLE;
    }
    
    virtual std::string get_info() const
    {
        std::stringstream ss;
        ss << "Circle\nCenter coordinates: (" << m_cen.get_x() << ", " << m_cen.get_y() << ")\nR=" << m_r << "\nL=" << 2*M_PI*m_r << "\nS=" << M_PI*m_r*m_r << "\n";
        return ss.str();
    }
    friend std::ostream& operator << (std::ostream &s,  Circle const &a)
    {
        return s << a.get_info();
    }
private:
    Point m_cen;
    double m_r;
};

class Rect: public Shape
{
public:
    Rect(Point const& _a, Point const& _b) throw(Shape_errors): m_a(_a), m_b(_b)
    {
        if(m_a.get_x()==m_b.get_x() || m_a.get_y()==m_b.get_y())
            throw WRONG_PARAMETERS_FOR_RECT;
    }
    
    virtual std::string get_info() const//вывести b, d
    {
        std::stringstream ss;
        ss << "Rect\nCoordinates s: a=(" << m_a.get_x() << ", " << m_a.get_y() << "), c=(" << m_b.get_x() << ", " << m_b.get_y() << ")\n";
        ss << "L=" << 2*fabs(m_a.get_x()-m_b.get_x())+2*fabs(m_a.get_y()-m_b.get_y()) << "\n";
        ss << "S=" << fabs((m_a.get_x()-m_b.get_x())*(m_a.get_y()-m_b.get_y())) << "\n";
        return ss.str();
    }
    
    friend std::ostream& operator << (std::ostream &s,  Rect const &a)
    {
        return s << a.get_info();
    }
private:
    Point m_a, m_b;
};

class Square: public Shape
{
public:
    Square(Point const& _a, Point const& _b) throw(Shape_errors): m_a(_a), m_b(_b)
    {
        if(m_a.get_x()==m_b.get_x() && m_a.get_y()==m_b.get_y())
            throw WRONG_PARAMETERS_FOR_SQUARE;
    }

    virtual std::string get_info() const
    {
        std::stringstream ss;
        /*
         * чисто аналит. геометрия
         * Да, формулы скучные, не отличные от формул в Rect
         */
        ss << "Square\nCoordinates s: a=(" << m_a.get_x() << ", " << m_a.get_y() <<
                "), b=(" << (m_a.get_x()+m_b.get_x())/2 + (m_a.get_y()-m_b.get_y())/2 << ", " << (m_a.get_y()+m_b.get_y())/2 - (m_a.get_x()-m_b.get_x())/2 <<
                "), c=(" << m_b.get_x() << ", " << m_b.get_y() <<
                "), d=(" << (m_a.get_x()+m_b.get_x())/2 - (m_a.get_y()-m_b.get_y())/2 << ", " << (m_a.get_y()+m_b.get_y())/2 + (m_a.get_x()-m_b.get_x())/2 << ")\n";//восстанавливаем еще 2 точки 
        
        ss << "L=" << 2.0/sqrt(0.5)*sqrt(fabs((m_a.get_x()-m_b.get_x())*(m_a.get_x()-m_b.get_x()) + (m_a.get_y()-m_b.get_y())*(m_a.get_y()-m_b.get_y()))) << "\n";
        ss << "S=" << 0.5*((m_a.get_x()-m_b.get_x())*(m_a.get_x()-m_b.get_x()) + (m_a.get_y()-m_b.get_y())*(m_a.get_y()-m_b.get_y())) << "\n";
        return ss.str();
    }
    friend std::ostream& operator << (std::ostream &s,  Square const &a)
    {
        return s << a.get_info();
    }
private:
    Point m_a, m_b;
};

class Polyline : public Shape
{
public:
    Polyline(): m_points()
    {
    }
    Polyline(My_forward_list<Point> const &l): m_points(l)
    {
    }
    
    virtual std::string get_info() const
    {
        std::stringstream ss;
        ss << "Polyline\n";
        if(m_points.is_empty())
        {
            ss  << "Vershin net\nL=0\n";
        }
        else if(m_points.get_element_number()==1)
        {
            ss  << "Vershini:\n(" << (*m_points.get_beginning()).get_x() << ',' << (*m_points.get_beginning()).get_y()<< ')' << "\nL=0\n";
        }
        else
        {
            ss  << "Vershini:\n";
            MyForwardIterator<Point> i=m_points.get_beginning(), j=m_points.get_beginning()++;
            double len=0;
            while(j!=m_points.get_ending())
            {
                ss << '(' << (*i).get_x() << ',' << (*i).get_y()<< ')' << '\n';
                i++;
                j++;
                len+=get_dist(*i, *j);
            }
            ss << '(' << (*i).get_x() << ',' << (*i).get_y()<< ')' << '\n';
            ss << "L=" << len << '\n';
        }
        return ss.str();
    }
    friend std::ostream& operator << (std::ostream &s,  Polyline const &a)
    {
        return s << a.get_info();
    }
    
   void add_point(Point const& p)
   {
       m_points.add_in_ending(p);
   }
private:
    My_forward_list<Point> m_points;
};

class Polygon: public Shape
{
public:
    Polygon(My_forward_list<Point> const &l): m_points(l)
    { 
    }

    virtual std::string get_info() const
    {
        std::stringstream ss;
        ss << "Polygon\n";
        if(m_points.is_empty())
        {
            ss  << "Vershin net\nL=0\n";
        }
        else if(m_points.get_element_number()==1)
        {
            ss  << "Vershini:\n(" << (*m_points.get_beginning()).get_x() << ',' << (*m_points.get_beginning()).get_y()<< ')' << "\nL=0\n";
        }
        else
        {
            ss << "Vershini:\n";
            MyForwardIterator<Point> i=m_points.get_beginning(), j=m_points.get_beginning()++;
            double len=0;
            while(j!=m_points.get_ending())
            {
                ss << '(' << (*i).get_x() << ',' << (*i).get_y()<< ')' << '\n';
                i++;
                j++;
                len+=get_dist(*i, *j);
            }
            len+=get_dist(*m_points.get_beginning(), *m_points.get_ending());
            ss << '(' << (*i).get_x() << ',' << (*i).get_y()<< ')' << '\n';
            ss << "L=" << len << '\n';
        }
        return ss.str();
    }
    friend std::ostream& operator << (std::ostream &s,  Polygon const &a)
    {
        return s << a.get_info();
    }
private:
    My_forward_list<Point> m_points;
};

