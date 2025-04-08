#ifndef FILE_MANAGER_SERIALIZABLE_HEADER
#define FILE_MANAGER_SERIALIZABLE_HEADER

#include "internal/Config.hpp"

#include <fstream>

namespace FILEMANAGER_NAMESPACE
{

template<typename T> void SerializeNumber(T t);
template<typename T> void DeserializeNumber(T& t);

void SerializeData(const char* data, size_t sz);
void DeserializeData(char* data, size_t sz);

class ISerializable
{
public:
	// filestream provided in case of operation requiring it
	virtual void Serialize(std::fstream& fs) const = 0;
	// filestream provided in case of operation requiring it
	virtual void Deserialize(std::fstream& fs) = 0;
};




template<typename T>
void SerializeNumber(T t)
{
	SerializeData(reinterpret_cast<const char*>( &t ), sizeof t);
}

template<typename T>
void DeserializeNumber(T& t)
{
	DeserializeData(reinterpret_cast<char*>( &t ), sizeof t);
}
}

#endif