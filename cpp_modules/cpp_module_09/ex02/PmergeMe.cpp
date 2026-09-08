#include "PmergeMe.hpp"

PmergeMe::PmergeMe(void)
{
}

PmergeMe::PmergeMe(const PmergeMe &src)
	: _vector(src._vector), _deque(src._deque)
{
}

PmergeMe::~PmergeMe(void)
{
}

PmergeMe &PmergeMe::operator=(const PmergeMe &rhs)
{
	if (this != &rhs)
	{
		this->_vector = rhs._vector;
		this->_deque = rhs._deque;
	}
	return (*this);
}

void PmergeMe::parseInput(int argc, char **argv)
{
	int i;
	char *end;
	long value;

	if (argc < 2)
		throw std::runtime_error("Error");

	i = 1;
	while (i < argc)
	{
		if (argv[i][0] == '\0')
			throw std::runtime_error("Error");

		end = NULL;
		value = std::strtol(argv[i], &end, 10);

		if (*end != '\0' || value <= 0 || value > 2147483647L)
			throw std::runtime_error("Error");

		this->_vector.push_back(static_cast<int>(value));
		this->_deque.push_back(static_cast<int>(value));

		++i;
	}
}

std::vector<int> PmergeMe::generateJacobsthalVector(std::size_t size)
{
	std::vector<int> sequence;
	std::size_t j0;
	std::size_t j1;
	std::size_t next;

	j0 = 1;
	j1 = 1;

	while (j1 < size)
	{
		next = j1 + 2 * j0;
		sequence.push_back(static_cast<int>(next));
		j0 = j1;
		j1 = next;
	}

	return (sequence);
}

std::deque<int> PmergeMe::generateJacobsthalDeque(std::size_t size)
{
	std::deque<int> sequence;
	std::size_t j0;
	std::size_t j1;
	std::size_t next;

	j0 = 1;
	j1 = 1;

	while (j1 < size)
	{
		next = j1 + 2 * j0;
		sequence.push_back(static_cast<int>(next));
		j0 = j1;
		j1 = next;
	}

	return (sequence);
}

void PmergeMe::binaryInsertVector(std::vector<int> &container, int value)
{
	std::size_t left;
	std::size_t right;
	std::size_t middle;

	left = 0;
	right = container.size();

	while (left < right)
	{
		middle = left + (right - left) / 2;

		if (container[middle] < value)
			left = middle + 1;
		else
			right = middle;
	}

	container.insert(container.begin() + left, value);
}

void PmergeMe::binaryInsertDeque(std::deque<int> &container, int value)
{
	std::size_t left;
	std::size_t right;
	std::size_t middle;

	left = 0;
	right = container.size();

	while (left < right)
	{
		middle = left + (right - left) / 2;

		if (container[middle] < value)
			left = middle + 1;
		else
			right = middle;
	}

	container.insert(container.begin() + left, value);
}

void PmergeMe::fordJohnsonVector(std::vector<int> &container)
{
	std::vector<int> mainChain;
	std::vector<int> pend;
	std::vector<int> pairs;
	std::size_t i;
	std::size_t j;

	if (container.size() <= 1)
		return;

	if (container.size() == 2)
	{
		if (container[0] > container[1])
			std::swap(container[0], container[1]);
		return;
	}

	i = 0;
	while (i + 1 < container.size())
	{
		if (container[i] < container[i + 1])
		{
			pairs.push_back(container[i]);
			pairs.push_back(container[i + 1]);
		}
		else
		{
			pairs.push_back(container[i + 1]);
			pairs.push_back(container[i]);
		}
		i += 2;
	}

	if (i < container.size())
		pend.push_back(container[i]);

	i = 0;
	while (i < pairs.size())
	{
		mainChain.push_back(pairs[i + 1]);
		++i;
		i++;
	}

	fordJohnsonVector(mainChain);

	i = 0;
	while (i < pairs.size())
	{
		pend.push_back(pairs[i]);
		i += 2;
	}

	if (!pend.empty())
	{
		for (j = 0; j < pend.size(); ++j)
			binaryInsertVector(mainChain, pend[j]);
	}

	container = mainChain;
}

void PmergeMe::fordJohnsonDeque(std::deque<int> &container)
{
	std::deque<int> mainChain;
	std::deque<int> pend;
	std::deque<int> pairs;
	std::size_t i;
	std::size_t j;

	if (container.size() <= 1)
		return;

	if (container.size() == 2)
	{
		if (container[0] > container[1])
			std::swap(container[0], container[1]);
		return;
	}

	i = 0;
	while (i + 1 < container.size())
	{
		if (container[i] < container[i + 1])
		{
			pairs.push_back(container[i]);
			pairs.push_back(container[i + 1]);
		}
		else
		{
			pairs.push_back(container[i + 1]);
			pairs.push_back(container[i]);
		}
		i += 2;
	}

	if (i < container.size())
		pend.push_back(container[i]);

	i = 0;
	while (i < pairs.size())
	{
		mainChain.push_back(pairs[i + 1]);
		++i;
		i++;
	}

	fordJohnsonDeque(mainChain);

	i = 0;
	while (i < pairs.size())
	{
		pend.push_back(pairs[i]);
		i += 2;
	}

	if (!pend.empty())
	{
		for (j = 0; j < pend.size(); ++j)
			binaryInsertDeque(mainChain, pend[j]);
	}

	container = mainChain;
}

void PmergeMe::printVector(const std::vector<int> &container) const
{
	std::size_t i;

	for (i = 0; i < container.size(); ++i)
	{
		if (i != 0)
			std::cout << " ";
		std::cout << container[i];
	}
	std::cout << std::endl;
}

void PmergeMe::printDeque(const std::deque<int> &container) const
{
	std::size_t i;

	for (i = 0; i < container.size(); ++i)
	{
		if (i != 0)
			std::cout << " ";
		std::cout << container[i];
	}
	std::cout << std::endl;
}

bool PmergeMe::isSortedVector(const std::vector<int> &container) const
{
	std::size_t i;

	i = 1;
	while (i < container.size())
	{
		if (container[i - 1] > container[i])
			return (false);
		++i;
	}
	return (true);
}

bool PmergeMe::isSortedDeque(const std::deque<int> &container) const
{
	std::size_t i;

	i = 1;
	while (i < container.size())
	{
		if (container[i - 1] > container[i])
			return (false);
		++i;
	}
	return (true);
}

void PmergeMe::run(int argc, char **argv)
{
	clock_t start;
	clock_t end;
	double vectorTime;
	double dequeTime;

	parseInput(argc, argv);

	std::cout << "Before: ";
	printVector(this->_vector);

	start = std::clock();
	fordJohnsonVector(this->_vector);
	end = std::clock();

	vectorTime = static_cast<double>(end - start)
		/ static_cast<double>(CLOCKS_PER_SEC) * 1000000.0;

	start = std::clock();
	fordJohnsonDeque(this->_deque);
	end = std::clock();

	dequeTime = static_cast<double>(end - start)
		/ static_cast<double>(CLOCKS_PER_SEC) * 1000000.0;

	if (!isSortedVector(this->_vector)
		|| !isSortedDeque(this->_deque))
		throw std::runtime_error("Error");

	std::cout << "After: ";
	printVector(this->_vector);

	std::cout << "Time to process a range of "
		<< this->_vector.size()
		<< " elements with std::vector : "
		<< vectorTime << " us" << std::endl;

	std::cout << "Time to process a range of "
		<< this->_deque.size()
		<< " elements with std::deque : "
		<< dequeTime << " us" << std::endl;
}