#ifndef HASHEDDICTIONARY_H_
#define HASHEDDICTIONARY_H_

#include <unordered_map>
#include <vector>
#include <string>

class HashDict
{
private:
	std::vector<std::string> dict;	//	Array Implementation
	unsigned int maxCapacity;
	HashDict();				//	Not supposed to call this
protected:
	int hashFunc(std::string);	//	Maybe double hashing
public:
	HashDict(unsigned int capacity);
};
#endif
