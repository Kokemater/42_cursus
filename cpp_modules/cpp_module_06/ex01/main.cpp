#include "Serializer.hpp"

int main(void)
{
	Data data;
	data.name = "Test Data";
	data.value = 42;
	data.amount = 3.14f;

	std::cout << "=== Original Data ===" << std::endl;
	std::cout << "Address: " << &data << std::endl;
	std::cout << "Name: " << data.name << std::endl;
	std::cout << "Value: " << data.value << std::endl;
	std::cout << "Amount: " << data.amount << std::endl;

	std::cout << "\n=== Serialization ===" << std::endl;
	uintptr_t raw = Serializer::serialize(&data);
	std::cout << "Serialized value: " << raw << std::endl;

	std::cout << "\n=== Deserialization ===" << std::endl;
	Data *deserialized = Serializer::deserialize(raw);
	std::cout << "Deserialized address: " << deserialized << std::endl;
	std::cout << "Name: " << deserialized->name << std::endl;
	std::cout << "Value: " << deserialized->value << std::endl;
	std::cout << "Amount: " << deserialized->amount << std::endl;

	std::cout << "\n=== Verification ===" << std::endl;
	if (deserialized == &data)
		std::cout << "SUCCESS: Pointers are equal!" << std::endl;
	else
		std::cout << "FAILURE: Pointers are not equal!" << std::endl;

	return (0);
}