# vector_swap_popback

## Feature   
   * C++ 17.   
   * Header only.   

## How work   

If you are using vector, Maybe you had experience to need deleting specific element of vector.   
if the element isn't last element of vector, you should use vector::erase function.   
This vector::erase delete specific element and need to reallocate(move) elements after deleted element.   
But This reallocation is usally too slow.   
Think if your vector has 100 element and you erase first element of the vector, your vector will reallocate 99 element.   
if vector's element has not well defined move semantic, this reallocation will be really really slow.   

So **my vector_swap_popback function swap erased element with last element and pop last element.***      
This way require just only three reallocation. ( think how swap works )   
vector_swap_popback function will reduce overhead dramatically.   
The more your vector's element count is, the faster this function than vector::erase. 

WARNINGS : If vector's element placement order is important, don't use this function.

## This is how vector::erase works.

1  2  3  4  5   

1  X  3  4  5 ( X is deleted element )   

1  **3  4  5** ( **element '3', '4', '5' is moved, this is sometimes too expensive** )     

--> Move 3 times        

## How my library's vector_swap_popback works

1  **2**  3  4  **5**   

1  **5**  3  4  **2** ( swap erased element ( 2 ) with last element )   

1  5  3  4  ( pop last element )   

--> Move 1 times   

## Result

std::vector_swap_popback : 13 ms.   
std::vector::erase : 163 ms.   

```c++
class A
{
public:
	int a = 10;
	double b = 10.0;
	std::string str1{ "Hello" };
	std::string str2{ "Male" };
	std::string str3{ "Female" };
};
int main()
{
	std::vector<A> A1{};
	std::vector<A> A2{};
	A1.reserve(100);
	A2.reserve(100);
	for (int i = 0; i < 1000; i++)
	{
		A1.emplace_back();
		A2.emplace_back();
	}
	
	{
		auto now = std::chrono::high_resolution_clock::now();
		A1.erase(A1.begin() + 2);
		std::cout << std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::high_resolution_clock::now() - now).count() << std::endl;
	}
	
	{
		auto now = std::chrono::high_resolution_clock::now();
		std::vector_swap_popback(A2, 2);
		std::cout << std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::high_resolution_clock::now() - now).count() << std::endl;
	}
}
```


