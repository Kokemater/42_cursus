#include "PmergeMe.hpp"

int main(int argc, char **argv)
{
	if (argc < 2)
	{
		std::cerr << "Error" << std::endl;
		return (1);
	}

	std::vector<int> vec;
	std::deque<int> deq;

	for (int i = 1; i < argc; i++)
	{
		int num = std::atoi(argv[i]);
		if (num < 0)
		{
			std::cerr << "Error" << std::endl;
			return (1);
		}
		vec.push_back(num);
		deq.push_back(num);
	}

	std::cout << "Before: ";
	for (size_t i = 0; i < vec.size(); i++)
	{
		if (i > 0)
			std::cout << " ";
		std::cout << vec[i];
	}
	std::cout << std::endl;

	std::clock_t startVec = std::clock();
	PmergeMe::sortVector(vec);
	std::clock_t endVec = std::clock();

	std::clock_t startDeq = std::clock();
	PmergeMe::sortDeque(deq);
	std::clock_t endDeq = std::clock();

	std::cout << "After: ";
	for (size_t i = 0; i < vec.size(); i++)
	{
		if (i > 0)
			std::cout << " ";
		std::cout << vec[i];
	}
	std::cout << std::endl;

	double timeVec = static_cast<double>(endVec - startVec) / CLOCKS_PER_SEC * 1000000;
	double timeDeq = static_cast<double>(endDeq - startDeq) / CLOCKS_PER_SEC * 1000000;

	std::cout << "Time to process a range of " << vec.size()
			  << " elements with std::vector : " << timeVec << " us" << std::endl;
	std::cout << "Time to process a range of " << deq.size()
			  << " elements with std::deque : " << timeDeq << " us" << std::endl;

	return (0);
}