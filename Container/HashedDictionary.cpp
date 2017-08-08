#include "HashedDictionary.h"

HashDict::HashDict(unsigned int capacity)
{
	dict.reserve(capacity);
}

int HashDict::hashFunc(std::string)
{
	return 0;
}