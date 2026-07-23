#include "MutantStack.hpp"

int main(void)
{
	std::cout << "=== Test 1: Basic MutantStack operations ===" << std::endl;
	MutantStack<int> mstack;
	mstack.push(5);
	mstack.push(17);
	std::cout << "Top: " << mstack.top() << std::endl;
	mstack.pop();
	std::cout << "Size after pop: " << mstack.size() << std::endl;
	mstack.push(3);
	mstack.push(5);
	mstack.push(737);
	mstack.push(0);

	std::cout << "\n=== Test 2: Iterator traversal ===" << std::endl;
	MutantStack<int>::iterator it = mstack.begin();
	MutantStack<int>::iterator ite = mstack.end();
	++it;
	--it;
	while (it != ite)
	{
		std::cout << *it << std::endl;
		++it;
	}

	std::cout << "\n=== Test 3: Copy to std::stack ===" << std::endl;
	std::stack<int> s(mstack);
	std::cout << "Copy size: " << s.size() << std::endl;

	std::cout << "\n=== Test 4: Const iterator ===" << std::endl;
	const MutantStack<int> constStack(mstack);
	MutantStack<int>::const_iterator cit = constStack.begin();
	MutantStack<int>::const_iterator cite = constStack.end();
	while (cit != cite)
	{
		std::cout << *cit << std::endl;
		++cit;
	}

	std::cout << "\n=== Test 5: Reverse iterator ===" << std::endl;
	MutantStack<int>::reverse_iterator rit = mstack.rbegin();
	MutantStack<int>::reverse_iterator rite = mstack.rend();
	while (rit != rite)
	{
		std::cout << *rit << std::endl;
		++rit;
	}

	std::cout << "\n=== Test 6: String MutantStack ===" << std::endl;
	MutantStack<std::string> strStack;
	strStack.push("Hello");
	strStack.push("World");
	strStack.push("Templates");

	MutantStack<std::string>::iterator sit = strStack.begin();
	MutantStack<std::string>::iterator site = strStack.end();
	while (sit != site)
	{
		std::cout << *sit << std::endl;
		++sit;
	}

	std::cout << "\n=== Test 7: Assignment operator ===" << std::endl;
	MutantStack<int> assigned;
	assigned = mstack;
	MutantStack<int>::iterator ait = assigned.begin();
	MutantStack<int>::iterator aite = assigned.end();
	while (ait != aite)
	{
		std::cout << *ait << std::endl;
		++ait;
	}

	return (0);
}