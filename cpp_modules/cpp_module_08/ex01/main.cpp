#include "Span.hpp"

int main(void)
{
	std::cout << "=== Test 1: Basic Span ===" << std::endl;
	Span sp = Span(5);
	sp.addNumber(6);
	sp.addNumber(3);
	sp.addNumber(17);
	sp.addNumber(9);
	sp.addNumber(11);
	std::cout << "Shortest span: " << sp.shortestSpan() << std::endl;
	std::cout << "Longest span: " << sp.longestSpan() << std::endl;

	std::cout << "\n=== Test 2: Span full exception ===" << std::endl;
	try
	{
		Span sp2 = Span(2);
		sp2.addNumber(1);
		sp2.addNumber(2);
		sp2.addNumber(3);
	}
	catch (std::exception &e)
	{
		std::cout << "Exception: " << e.what() << std::endl;
	}

	std::cout << "\n=== Test 3: Not enough elements ===" << std::endl;
	try
	{
		Span sp3 = Span(5);
		sp3.addNumber(42);
		std::cout << sp3.shortestSpan() << std::endl;
	}
	catch (std::exception &e)
	{
		std::cout << "Exception: " << e.what() << std::endl;
	}

	std::cout << "\n=== Test 4: Range of iterators ===" << std::endl;
	std::vector<int> vec;
	vec.push_back(100);
	vec.push_back(200);
	vec.push_back(300);
	vec.push_back(400);
	vec.push_back(500);

	Span sp4 = Span(10);
	sp4.addNumber(vec.begin(), vec.end());
	std::cout << "Shortest span: " << sp4.shortestSpan() << std::endl;
	std::cout << "Longest span: " << sp4.longestSpan() << std::endl;

	std::cout << "\n=== Test 5: Large Span (10,000 numbers) ===" << std::endl;
	Span largeSp = Span(10000);
	std::vector<int> largeVec;
	for (int i = 0; i < 10000; i++)
		largeVec.push_back(i * 2);
	largeSp.addNumber(largeVec.begin(), largeVec.end());
	std::cout << "Shortest span: " << largeSp.shortestSpan() << std::endl;
	std::cout << "Longest span: " << largeSp.longestSpan() << std::endl;

	std::cout << "\n=== Test 6: Copy constructor ===" << std::endl;
	Span sp5 = Span(3);
	sp5.addNumber(10);
	sp5.addNumber(20);
	sp5.addNumber(30);
	Span sp6(sp5);
	std::cout << "Copy shortest span: " << sp6.shortestSpan() << std::endl;
	std::cout << "Copy longest span: " << sp6.longestSpan() << std::endl;

	return (0);
}