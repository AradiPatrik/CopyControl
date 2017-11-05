#pragma once
#include <memory>
#include <string>
#include <utility>

class StrVec
{
public:
	StrVec() : elements(nullptr), firstFree(nullptr), cap(nullptr) { }
	StrVec(const StrVec &other);
	StrVec(std::initializer_list<std::string> initList);
	StrVec &operator=(const StrVec& rhs);
	~StrVec();
	void PushBack (const std::string &element);
	void Reserve(size_t amount);
	void Resize(size_t newSize, const std::string &target = "");
	size_t Size() const { return firstFree - elements; }
	size_t Capacity() const { return cap - elements; }
	std::string *begin() const { return elements; }
	std::string *end() const { return firstFree; }
	
private:
	static std::allocator<std::string> allocator;
	std::string *elements;
	std::string *firstFree;
	std::string *cap;

	void Realloc();
	void Free();
	std::pair<std::string *, std::string *> AllocAndCopy(const std::string *b, const std::string *e);
	void CheckAndAlloc() { if (firstFree == cap) Realloc(); }
};

