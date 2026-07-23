#include "PmergeMe.hpp"

PmergeMe::PmergeMe(void)
{
}

PmergeMe::PmergeMe(const PmergeMe &src)
{
	(void)src;
}

PmergeMe::~PmergeMe(void)
{
}

PmergeMe &PmergeMe::operator=(const PmergeMe &rhs)
{
	(void)rhs;
	return (*this);
}

void PmergeMe::insertionSortVector(std::vector<int> &vec, int left, int right)
{
	for (int i = left + 1; i <= right; i++)
	{
		int key = vec[i];
		int j = i - 1;
		while (j >= left && vec[j] > key)
		{
			vec[j + 1] = vec[j];
			j--;
		}
		vec[j + 1] = key;
	}
}

void PmergeMe::mergeVector(std::vector<int> &vec, int left, int mid, int right)
{
	int n1 = mid - left + 1;
	int n2 = right - mid;

	std::vector<int> L(n1);
	std::vector<int> R(n2);

	for (int i = 0; i < n1; i++)
		L[i] = vec[left + i];
	for (int j = 0; j < n2; j++)
		R[j] = vec[mid + 1 + j];

	int i = 0, j = 0, k = left;
	while (i < n1 && j < n2)
	{
		if (L[i] <= R[j])
		{
			vec[k] = L[i];
			i++;
		}
		else
		{
			vec[k] = R[j];
			j++;
		}
		k++;
	}

	while (i < n1)
	{
		vec[k] = L[i];
		i++;
		k++;
	}

	while (j < n2)
	{
		vec[k] = R[j];
		j++;
		k++;
	}
}

void PmergeMe::mergeInsertSortVector(std::vector<int> &vec)
{
	int n = vec.size();
	for (int size = 1; size < n; size *= 2)
	{
		for (int left = 0; left < n - 1; left += 2 * size)
		{
			int mid = std::min(left + size - 1, n - 1);
			int right = std::min(left + 2 * size - 1, n - 1);

			if (mid < right)
				mergeVector(vec, left, mid, right);
		}
	}
}

void PmergeMe::insertionSortDeque(std::deque<int> &deq, int left, int right)
{
	for (int i = left + 1; i <= right; i++)
	{
		int key = deq[i];
		int j = i - 1;
		while (j >= left && deq[j] > key)
		{
			deq[j + 1] = deq[j];
			j--;
		}
		deq[j + 1] = key;
	}
}

void PmergeMe::mergeDeque(std::deque<int> &deq, int left, int mid, int right)
{
	int n1 = mid - left + 1;
	int n2 = right - mid;

	std::deque<int> L(n1);
	std::deque<int> R(n2);

	for (int i = 0; i < n1; i++)
		L[i] = deq[left + i];
	for (int j = 0; j < n2; j++)
		R[j] = deq[mid + 1 + j];

	int i = 0, j = 0, k = left;
	while (i < n1 && j < n2)
	{
		if (L[i] <= R[j])
		{
			deq[k] = L[i];
			i++;
		}
		else
		{
			deq[k] = R[j];
			j++;
		}
		k++;
	}

	while (i < n1)
	{
		deq[k] = L[i];
		i++;
		k++;
	}

	while (j < n2)
	{
		deq[k] = R[j];
		j++;
		k++;
	}
}

void PmergeMe::mergeInsertSortDeque(std::deque<int> &deq)
{
	int n = deq.size();
	for (int size = 1; size < n; size *= 2)
	{
		for (int left = 0; left < n - 1; left += 2 * size)
		{
			int mid = std::min(left + size - 1, n - 1);
			int right = std::min(left + 2 * size - 1, n - 1);

			if (mid < right)
				mergeDeque(deq, left, mid, right);
		}
	}
}

void PmergeMe::sortVector(std::vector<int> &vec)
{
	mergeInsertSortVector(vec);
}

void PmergeMe::sortDeque(std::deque<int> &deq)
{
	mergeInsertSortDeque(deq);
}