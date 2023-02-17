#include <iostream>
#include <vector>
#include "../vector_swap_popback.h"

class A
{
public:
	int value;

	A(int k) : value{ k }
	{
		std::cout << "default contructor\n";

	}
	A(const A& a)
	{
	}
	A(A&& a) noexcept
	{
		value = a.value;
		std::cout << "move contructor\n";
	}

	~A()
	{
	}

	A& operator=(A&& a) noexcept
	{
		value = a.value;
		std::cout << "move assignmnet\n";
		return *this;
	}
};
int main()
{
	std::vector<int> b{ 1,5,3,2,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20 };


	std::cout << "Original Vector" << '\n';
	for (auto& bb : b)
	{
		std::cout << bb << " ";
	}
	
	std::cout << '\n';
	std::cout << '\n';

	/////////////////////

	std::cout << "Remove 16" << '\n';
	std::vector_find_swap_popback(b, (int)16);

	for (auto& bb : b)
	{
		std::cout << bb << " ";
	}
	std::cout << '\n';
	std::cout << '\n';

	/////////////////////

	std::cout << "Remove First Element with iterator" << '\n';
	std::vector_swap_popback(b, b.begin());

	for (auto& bb : b)
	{
		std::cout << bb << " ";
	}
	std::cout << '\n';
	std::cout << '\n';

	/////////////////////

	std::cout << "Remove element with value 10" << '\n';
	std::vector_find_swap_popback(b, 10);

	for (auto& bb : b)
	{
		std::cout << bb << " ";
	}
	std::cout << '\n';
	std::cout << '\n';

	/////////////////////

	std::cout << "Remove element with value 12 with predicate" << '\n';
	std::vector_find_if_swap_popback(b, [](int value) -> bool { return value == 12; });

	for (auto& bb : b)
	{
		std::cout << bb << " ";
	}
	std::cout << '\n';
	std::cout << '\n';

	std::cout << '\n';
	std::cout << '\n';
	std::cout << '\n';
}