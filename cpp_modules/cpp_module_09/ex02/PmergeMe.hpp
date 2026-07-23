#ifndef PMERGEME_HPP
# define PMERGEME_HPP

# include <iostream>
# include <string>
# include <vector>
# include <deque>
# include <algorithm>
# include <cstdlib>
# include <ctime>

class PmergeMe
{
public:
	PmergeMe(void);
	PmergeMe(const PmergeMe &src);
	~PmergeMe(void);

	PmergeMe &operator=(const PmergeMe &rhs);

	static void sortVector(std::vector<int> &vec);
	static void sortDeque(std::deque<int> &deq);

private:
	static void mergeInsertSortVector(std::vector<int> &vec);
	static void mergeInsertSortDeque(std::deque<int> &deq);
	static void insertionSortVector(std::vector<int> &vec, int left, int right);
	static void insertionSortDeque(std::deque<int> &deq, int left, int right);
	static void mergeVector(std::vector<int> &vec, int left, int mid, int right);
	static void mergeDeque(std::deque<int> &deq, int left, int mid, int right);
};

#endif