#include "easyfind.hpp"
#include <vector>
#include <list>
#include <deque>

int main(void)
{
	std::cout << "=== Test 1: Vector - Find existing value ===" << std::endl;
	std::vector<int> vec;
	vec.push_back(1);
	vec.push_back(2);
	vec.push_back(3);
	vec.push_back(4);
	vec.push_back(5);

	try
	{
		std::vector<int>::iterator it = easyfind(vec, 3);
		std::cout << "Found: " << *it << " at index " << (it - vec.begin()) << std::endl;
	}
	catch (std::exception &e)
	{
		std::cout << "Exception: " << e.what() << std::endl;
	}

	std::cout << "\n=== Test 2: Vector - Find non-existing value ===" << std::endl;
	try
	{
		std::vector<int>::iterator it = easyfind(vec, 42);
		std::cout << "Found: " << *it << std::endl;
	}
	catch (std::exception &e)
	{
		std::cout << "Exception: " << e.what() << std::endl;
	}

	std::cout << "\n=== Test 3: List - Find existing value ===" << std::endl;
	std::list<int> lst;
	lst.push_back(10);
	lst.push_back(20);
	lst.push_back(30);
	lst.push_back(40);

	try
	{
		std::list<int>::iterator it = easyfind(lst, 20);
		std::cout << "Found: " << *it << std::endl;
	}
	catch (std::exception &e)
	{
		std::cout << "Exception: " << e.what() << std::endl;
	}

	std::cout << "\n=== Test 4: Deque - Find existing value ===" << std::endl;
	std::deque<int> deq;
	deq.push_back(100);
	deq.push_back(200);
	deq.push_back(300);

	try
	{
		std::deque<int>::iterator it = easyfind(deq, 200);
		std::cout << "Found: " << *it << std::endl;
	}
	catch (std::exception &e)
	{
		std::cout << "Exception: " << e.what() << std::endl;
	}

	std::cout << "\n=== Test 5: Const vector ===" << std::endl;
	const std::vector<int> constVec(vec);
	try
	{
		std::vector<int>::const_iterator it = easyfind(constVec, 4);
		std::cout << "Found: " << *it << std::endl;
	}
	catch (std::exception &e)
	{
		std::cout << "Exception: " << e.what() << std::endl;
	}

	std::cout << "\n=== Test 6: Find first occurrence ===" << std::endl;
	std::vector<int> dup;
	dup.push_back(5);
	dup.push_back(3);
	dup.push_back(5);
	dup.push_back(7);

	try
	{
		std::vector<int>::iterator it = easyfind(dup, 5);
		std::cout << "First occurrence: " << *it << " at index " << (it - dup.begin()) << std::endl;
	}
	catch (std::exception &e)
	{
		std::cout << "Exception: " << e.what() << std::endl;
	}

	return (0);
}