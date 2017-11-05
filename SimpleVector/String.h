#pragma once
#include <memory>
#include <cstring>
#include <utility>
class String
{
public:
	String(const char *data = "");
	String(const String &other);
	String(String &&other);
	String &operator=(const String& rhs);
	String &operator=(String &&other);
	~String();

	size_t Size() const { return firstFree - elements; }
	size_t Capacity() const { return cap - elements; }
	char *begin() const { return elements; }
	char *end() const { return firstFree; }
private:
	static std::allocator<char> allocator;
	char *elements;
	char *firstFree;
	char *cap;

	void Free();
	std::pair<char *, char *> AllocateAndCopy(const char *b, const char *e);
};

