#include <iostream>

#include "Serializer.hpp"


int main(void)
{
	Data *heap = new Data;
	heap->name = "Heap Data";
	heap->value = 99;
	heap->amount = -1.5f;

	uintptr_t raw = Serializer::serialize(heap);
	Data *restored = Serializer::deserialize(raw);

	std::cout << "Address: " << heap << " -> " << raw << " -> " << restored << std::endl;
	std::cout << "Contents: " << restored->name << ", "
			  << restored->value << ", " << restored->amount << std::endl;
	std::cout << "RESULT: " << (restored == heap ? "SUCCESS" : "FAILURE") << std::endl;

	delete heap;
	return (0);
}
