#include "Span.hpp"
#include <iostream>
#include <vector>
#include <deque>
#include <list>

int main(void)
{
    std::cout << "=== Vector ===" << std::endl;

    std::vector<int> vec;
    vec.push_back(6);
    vec.push_back(3);
    vec.push_back(17);
    vec.push_back(9);
    vec.push_back(11);

    Span sp1(5);

    try
    {
        sp1.addNumber(vec.begin(), vec.end());

        std::cout <<  sp1.shortestSpan() << std::endl;
        std::cout << sp1.longestSpan() << std::endl;
    }
    catch (std::exception &e)
    {
        std::cout << "Exception: " << e.what() << std::endl;
    }


    std::cout << "\n=== Deque ===" << std::endl;

    std::deque<int> deq;
    deq.push_back(10);
    deq.push_back(20);
    deq.push_back(30);
    deq.push_back(40);

    Span sp2(4);

    try
    {
        sp2.addNumber(deq.begin(), deq.end());

        std::cout << "Shortest span: " << sp2.shortestSpan() << std::endl;
        std::cout << "Longest span: " << sp2.longestSpan() << std::endl;
    }
    catch (std::exception &e)
    {
        std::cout << "Exception: " << e.what() << std::endl;
    }


    std::cout << "\n=== List ===" << std::endl;

    std::list<int> lst;
    lst.push_back(100);
    lst.push_back(250);
    lst.push_back(400);
    lst.push_back(800);

    Span sp3(4);

    try
    {
        sp3.addNumber(lst.begin(), lst.end());

        std::cout << "Shortest span: " << sp3.shortestSpan() << std::endl;
        std::cout << "Longest span: " << sp3.longestSpan() << std::endl;
    }
    catch (std::exception &e)
    {
        std::cout << "Exception: " << e.what() << std::endl;
    }


    std::cout << "\n=== Capacity test ===" << std::endl;

    std::vector<int> many;
    many.push_back(1);
    many.push_back(2);
    many.push_back(3);
    many.push_back(4);

    Span sp4(3);

    try
    {
        sp4.addNumber(many.begin(), many.end());
    }
    catch (std::exception &e)
    {
        std::cout << "Expected exception: " << e.what() << std::endl;
    }


    return (0);
}