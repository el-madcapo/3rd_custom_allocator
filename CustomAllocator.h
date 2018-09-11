#ifndef CUSTOMALLOCATOR_H
#define CUSTOMALLOCATOR_H

#include <limits>
#include <memory>
#include <iostream> 

template<class T>
class CustomAllocator
{
    public:
        using value_type = T;
        using pointer = T*;
        using reference = value_type&;
        using const_pointer = const T*;
        using void_pointer = void*;
        using const_void_pointer = const void*;
        using size_type = size_t;
        using difference_type = std::ptrdiff_t;

        CustomAllocator() = default;
        ~CustomAllocator() = default;

        template<class U>
        CustomAllocator(const CustomAllocator<U>& other) {}

        template<class U>
        struct rebind
        {
           using other = CustomAllocator<U>;
        };

        pointer allocate(size_type numberObjects)
        {            
	    //std::cout << "using allocate" << std::endl;
	    return static_cast<pointer>(operator new(sizeof(value_type)*numberObjects));
        }
                
        void deallocate(pointer p, [[maybe_unused]] size_type numberObjects)
        {
            operator delete(p);
        }

        template<class U, class... Args>
        void construct(U* ptr, Args&&... args)	  
        {
	    //std::cout << "construct" << std::endl;
	    new(ptr) U(std::forward<Args>(args)...);
        }
        
        size_type max_size() const
        {
            return std::numeric_limits<size_type>::max();
        }
};

template<class T>
inline bool operator==(const CustomAllocator<T>&, const CustomAllocator<T>&) 
{
    return true;
}

template<class T>
inline bool operator!=(const CustomAllocator<T>&, const CustomAllocator<T>&) 
{
    return false;
}

#endif // CUSTOMALLOCATOR_H
