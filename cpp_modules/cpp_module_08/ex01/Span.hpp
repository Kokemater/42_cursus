#ifndef SPAN_HPP
# define SPAN_HPP

# include <vector>
# include <algorithm>
# include <stdexcept>

class Span
{
public:
    Span(unsigned int n);
    Span(const Span &src);
    ~Span(void);

    Span &operator=(const Span &rhs);

    void addNumber(int number);

    template <typename Iterator>
    void addNumber(Iterator begin, Iterator end);

    int shortestSpan(void) const;
    int longestSpan(void) const;

private:
    Span(void);

    std::vector<int> _numbers;
    unsigned int _maxSize;
};

template <typename Iterator>
void Span::addNumber(Iterator begin, Iterator end)
{
    for (Iterator it = begin; it != end; ++it)
    {
        if (_numbers.size() >= _maxSize)
            throw std::out_of_range("Span is full");

        _numbers.push_back(*it);
    }
}
#endif