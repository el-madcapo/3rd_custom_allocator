#include "CustomAllocator.h"
#include "custom_container.h"

#include <map>
#include <iostream>

int factorial(int number)
{
    if (number == 0 || number == 1)
        return 1;
    int factorial_value = 1;
    for(int i = 1; i <= number; ++i )
    {
        factorial_value *= i;
    }
    return factorial_value;
}


void mapOperations(std::map<int, int>& some_map)
{
    for(int i = 0; i < 10; ++i)
    {
        std::pair<int, int> pair1;
        pair1.first = i;
        pair1.second = factorial(i);
        some_map.emplace(pair1);
    }    
}


void mapOperations(std::map<int, int, std::less<int>,
		   CustomAllocator<std::pair<int, int>>>& some_map)
{
    for(int i = 0; i < 10; ++i)
    {
        std::pair<int, int> pair1;
        pair1.first = i;
        pair1.second = factorial(i);
        some_map.emplace(pair1);
    }
}


void containerFilling(CustomContainer<int>& some_container)
{
    for(auto i = 0; i <10; ++i)
    {
	int fac_value = factorial(i);
	some_container.push_back(fac_value);
    }
}


void containerFilling(CustomContainer<int, CustomAllocator<int>>& some_container)
{
    for(auto i = 0; i <10; ++i)
    {
	int fac_value = factorial(i);
	some_container.push_back(fac_value);
    }
}


int main()
{    
    //std::cout << "default allocator: " << std::endl;w
    std::map<int, int> map1;    
    mapOperations(map1);
    
    //std::cout << "custom allocator: " << std::endl;
    std::map<int, int, std::less<int>, CustomAllocator<std::pair<int,int>>> map2;
    mapOperations(map2);

    //std::cout << "map with default allocator output" << std::endl;
    for(auto & i : map1)
            std::cout << i.first << " " << i.second << std::endl;

    //std::cout << "map with custom output allocator" << std::endl;
    for(auto & i : map2)
            std::cout << i.first << " " << i.second << std::endl;
    

    //std::cout << "container with default allocator" << std::endl;
    CustomContainer<int> contDefAlloc;
    containerFilling(contDefAlloc);

    //std::cout << "container with custom allocator" << std:: endl;
    CustomContainer<int, CustomAllocator<int>> contCustomAlloc;
    containerFilling(contCustomAlloc);

    //std::cout << "container with default allocator output" << std::endl;
    for(auto &i : contDefAlloc)
    	std::cout << i << std::endl;

    //std::cout << "container with custom allocator output" << std::endl;
    for(auto &i : contCustomAlloc)
    	std::cout << i << std::endl;
    
    return 0;   
}
