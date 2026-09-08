#ifndef PMERGEME_HPP
# define PMERGEME_HPP

# include <iostream>
# include <vector>
# include <deque>
# include <string>
# include <cstdlib>
# include <stdexcept>
# include <ctime>

class PmergeMe
{
public:
	PmergeMe(void);
	PmergeMe(const PmergeMe &src);
	~PmergeMe(void);

	PmergeMe &operator=(const PmergeMe &rhs);

	void run(int argc, char **argv);

private:
	std::vector<int> _vector;
	std::deque<int> _deque;

	void parseInput(int argc, char **argv);

	void fordJohnsonVector(std::vector<int> &container);
	void fordJohnsonDeque(std::deque<int> &container);

	void binaryInsertVector(std::vector<int> &container, int value);
	void binaryInsertDeque(std::deque<int> &container, int value);

	std::vector<int> generateJacobsthalVector(std::size_t size);
	std::deque<int> generateJacobsthalDeque(std::size_t size);

	void printVector(const std::vector<int> &container) const;
	void printDeque(const std::deque<int> &container) const;

	bool isSortedVector(const std::vector<int> &container) const;
	bool isSortedDeque(const std::deque<int> &container) const;
};

#endif