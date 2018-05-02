#include <cstdlib>
#include <iostream>
#include <random>

#include "My_forward_list.hpp"
#include "MyForwardIterator.hpp"
#include "Shape.hpp"
#include "factory.hpp"

using namespace std;


typedef My_forward_list<Shape*> list;
typedef MyForwardIterator<Shape*> list_iterator;

int main(int argc, char** argv)
{
    Shape * qq = new Square(Point(2, 3), Point(6, 3));
    cout << *qq;
    
    std::random_device rd;
    std::uniform_int_distribution<int> gen_type(0, 5);
    
    try
    {
        list shapes_list;
        for(int i=0; i<20; i++)
        {
            int job=gen_type(rd);
            if(job == 0)
                shapes_list.m_add_in_ending(random_factory(std::string("Point")));
            else if(job == 1)
                shapes_list.m_add_in_ending(random_factory(std::string("Circle")));
            else if(job == 2)
                shapes_list.m_add_in_ending(random_factory(std::string("Rect")));
            else if(job == 3)
                shapes_list.m_add_in_ending(random_factory(std::string("Square")));
            else if(job == 4)
                shapes_list.m_add_in_ending(random_factory(std::string("Polyline")));
            else //if(job == 5)
                shapes_list.m_add_in_ending(random_factory(std::string("Polygon")));
        }
        std::cout << "Shape::GetCount()=" << Shape::m_get_counter() << '\n' << "INFO\n";
        list_iterator i(shapes_list.m_get_beginning());
        while(i != shapes_list.m_get_ending())
        {
            std::cout << (*(i))->m_get_info() << '\n';
            i++;
        }
        std::cout << (*i)->m_get_info() << '\n';    
        //очищаем память ручками т.к у нас список указателей
        i=shapes_list.m_get_beginning();
        while(i != shapes_list.m_get_ending())
        {
            delete *i;
            i++;
        }
        delete *i;
        std::cout << "Shape::GetCount()=" << Shape::m_get_counter() << '\n';    
    }
    catch(My_forward_list_errors err)
    {
        switch(err)
        {
            case CANT_ALLOCATE_MEMORY://она не выкидывается. вместо нее обычный бэд аллок идет...
                cout << "CANT_ALLOCATE_MEMORY\n";
                return -1;
            case ACCESS_TO_ELEMNT_FROM_EMPTY_LIST:
                cout << "ACCESS_TO_ELEMNT_FROM_EMPTY_LIST\n";
                return -1;
            case ITERATOR_HAVE_MOVED_OUTSIDE_LIST:
                cout << "ITERATOR_HAVE_MOVED_OUTSIDE_LIST\n";
                return -1;
        }
    }
    catch(Shape_errors err)
    {
        switch(err)
        {
            case WRONG_PARAMETERS_FOR_CIRCLE:
                cout << "WRONG_PARAMETERS_FOR_CIRCLE\n";
                return -1;
            case WRONG_PARAMETERS_FOR_RECT:
                cout << "WRONG_PARAMETERS_FOR_RECT\n";
                return -1;
            case WRONG_PARAMETERS_FOR_SQUARE:
                cout << "WRONG_PARAMETERS_FOR_SQUARE\n";
                return -1;    
        }
    }
    return 0;
}
