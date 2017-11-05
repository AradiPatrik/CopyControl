#include "StrVec.h"

std::allocator<std::string> StrVec::allocator;

StrVec::StrVec(const StrVec& vec)
{
	auto newData = AllocAndCopy(vec.begin(), vec.end());
	elements = newData.first;
	cap = firstFree = newData.second;
}

StrVec::StrVec(std::initializer_list<std::string> initList)
{
	elements = allocator.allocate(initList.size());
	auto source = initList.begin();
	auto dest = elements;
	while (source != initList.end())
	{
		allocator.construct(dest++, std::move(*source++));
	}
	firstFree = cap = dest;
}

StrVec &StrVec::operator=(const StrVec& rhs)
{
	auto newData = AllocAndCopy(rhs.begin(), rhs.end());
	Free();
	elements = newData.first;
	cap = firstFree = newData.second;
	return *this;
}

StrVec::~StrVec()
{
	Free();
}

void StrVec::PushBack(const std::string &element)
{
	CheckAndAlloc();
	allocator.construct(firstFree++, element);
}

void StrVec::Reserve(size_t amount)
{
	if (Size() >= amount) return;
	auto newData = allocator.allocate(amount);
	auto target = newData;
	auto elem = elements;
	while (elem != firstFree)
	{
		allocator.construct(target++, std::move(*elem++));
	}
	Free();
	elements = newData;
	firstFree = target;
	cap = newData + amount;
}

void StrVec::Resize(size_t amount, const std::string& target)
{
	if (amount == Size()) return;
	if (amount > Size())
	{
		auto newData = allocator.allocate(amount);
		auto dest = newData;
		auto elem = elements;
		while (elem != firstFree)
		{
			allocator.construct(dest++, std::move(*elem++));
		}
		while (dest != newData + amount)
		{
			allocator.construct(dest++, target);
		}
		Free();
		elements = newData;
		firstFree = dest;
		cap = newData + amount;
	}
	else
	{
		auto element = elements + amount;
		while (element != cap)
		{
			allocator.destroy(element++);
		}
		allocator.deallocate(elements + amount, Capacity() - amount);
		firstFree = cap = elements + amount;
	}
}

std::pair<std::string *, std::string *> StrVec::AllocAndCopy(const std::string *b, const std::string *e)
{
	auto data = allocator.allocate(e - b);
	return { data, std::uninitialized_copy(b, e, data) };
}

void StrVec::Free()
{
	for (auto beg = begin(), e = end(); beg != e; ++beg)
	{
		allocator.destroy(beg);
	}
	allocator.deallocate(begin(), Capacity());
}

void StrVec::Realloc()
{
	auto newCapacity = Size() ? 2 * Size() : 1;
	auto newData = allocator.allocate(newCapacity);
	auto last = std::uninitialized_copy(std::make_move_iterator(begin()), std::make_move_iterator(end()), newData);
	Free();
	elements = newData;
	firstFree = last;
	cap = elements + newCapacity;
}
