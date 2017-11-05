#include "StrVec.h"
#include <vector>
#include <iostream>
#include <chrono>
#include <string>
#include "String.h"

void BenchMark()
{
	for (int i = 0; i < 10; ++i)
	{
		auto start = std::chrono::high_resolution_clock::now();
		for (int i = 0; i < 10000; ++i)
		{
			std::vector<std::string> vec{ "asd", "basd" };
			std::vector<std::string> vec2 = vec;
			std::vector<std::string> vec3;
			vec3 = vec2;
		}
		auto finish = std::chrono::high_resolution_clock::now();
		auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(finish - start);
		std::cout << "Elapsed time: " << elapsed.count() << "\n";
	}
	std::cout << "################################" << std::endl;
	for (int i = 0; i < 10; ++i)
	{
		auto start = std::chrono::high_resolution_clock::now();
		for (int i = 0; i < 10000; ++i)
		{
			StrVec vec{ "asd", "basd" };
			StrVec vec2 = vec;
			StrVec vec3;
			vec3 = vec2;
		}
		auto finish = std::chrono::high_resolution_clock::now();
		auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(finish - start);
		std::cout << "Elapsed time: " << elapsed.count() << "\n";
	}
	std::cout << "################################" << std::endl;
	for (int i = 0; i < 10; ++i)
	{
		auto start = std::chrono::high_resolution_clock::now();
		for (int i = 0; i < 100000; ++i)
		{
			String str = "asd";
			String str1 = str;
			String str2;
			str2 = str1;
		}
		auto finish = std::chrono::high_resolution_clock::now();
		auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(finish - start);
		std::cout << "Elapsed time: " << elapsed.count() << "\n";
	}
	std::cout << "################################" << std::endl;
	for (int i = 0; i < 10; ++i)
	{
		auto start = std::chrono::high_resolution_clock::now();
		for (int i = 0; i < 100000; ++i)
		{
			std::string str = "asd";
			std::string str1 = str;
			std::string str2;
			str2 = str1;
		}
		auto finish = std::chrono::high_resolution_clock::now();
		auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(finish - start);
		std::cout << "Elapsed time: " << elapsed.count() << "\n";
	}
}

int main(int argc, char **argv)
{
	for (int i = 0; i < 10; ++i)
	{
		auto start = std::chrono::high_resolution_clock::now();
		for (int i = 0; i < 100000; ++i)
		{
			String string1 = "valami szoveg";
			String string2 = "Masik szoveg";
			string1 = std::move(string2);
		}
		auto finish = std::chrono::high_resolution_clock::now();
		auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(finish - start);
		std::cout << "Elapsed time: " << elapsed.count() << "\n";
	}
}