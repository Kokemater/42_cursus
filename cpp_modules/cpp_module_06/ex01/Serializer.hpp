#ifndef SERIALIZER_HPP
# define SERIALIZER_HPP

# include <iostream>
# include <string>
# include <stdint.h>

struct Data
{
	std::string name;
	int value;
	float amount;
};

class Serializer
{
public:
	static uintptr_t serialize(Data *ptr);
	static Data *deserialize(uintptr_t raw);

private:
	Serializer(void);
	Serializer(const Serializer &src);
	~Serializer(void);

	Serializer &operator=(const Serializer &rhs);
};

#endif