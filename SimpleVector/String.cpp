#include "String.h"
#include <iostream>

std::allocator<char> String::allocator;

String::String(const char *data) : elements(nullptr), firstFree(nullptr), cap(nullptr)
{
	auto newData = AllocateAndCopy(data, data + strlen(data));
	elements = newData.first;
	firstFree = cap = newData.second;
}

String::String(const String &string)
{
	auto newData = AllocateAndCopy(string.begin(), string.end());
	elements = newData.first;
	firstFree = cap = newData.second;
}

String::String(String && other)
{
	if (&other != this)
	{
		elements = other.elements;
		cap = other.cap;
		firstFree = other.firstFree;
		other.elements = other.cap = other.firstFree = nullptr;
	}
}

String& String::operator=(const String &rhs)
{
	auto newData = AllocateAndCopy(rhs.begin(), rhs.end());
	Free();
	elements = newData.first;
	firstFree = cap = newData.second;
	return *this;
}

String & String::operator=(String && other)
{
	if (&other != this)
	{
		Free();
		elements = other.elements;
		cap = other.cap;
		firstFree = other.firstFree;
		other.elements = other.cap = other.firstFree = nullptr;
	}
	return *this;
}

String::~String()
{
	Free();
}

std::pair<char *, char *> String::AllocateAndCopy(const char *b, const char *e)
{
	auto data = allocator.allocate(e - b);
	return { data, std::uninitialized_copy(b, e, data) };
}

void String::Free()
{
	for (auto beg = begin(), e = end(); beg != e; ++beg)
	{
		allocator.destroy(beg);
	}
	allocator.deallocate(begin(), Size());
}