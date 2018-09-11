#ifndef CUSTOM_CONTAINER_H
#define CUSTOM_CONTAINER_H

#include <memory>

template<class T, class Allocator = std::allocator<T>> 
class CustomContainer
{
 public: 	
    using value_type = T;
    using allocator_type = Allocator;
    using size_type = std::size_t;
    using difference_type = std::ptrdiff_t;
    using reference = value_type&;
    using const_reference = const value_type&;
    using pointer = typename std::allocator_traits<Allocator>::pointer;
    using const_pointer = typename std::allocator_traits<Allocator>::const_pointer;
    using void_pointer = void*;
    using const_void_pointer = const void*;
    using iterator = pointer;
   
    //default ctors
    CustomContainer(){};
    
    CustomContainer(allocator_type& alloc)
         :  allocator_(alloc)         
     {} //initilize container 
    
    
    CustomContainer(allocator_type& alloc, size_type count) 
    {	  
	// allocate for 'count' container's elements
	first_ =  std::allocator_traits<allocator_type>::allocate(alloc, count);
	end_  = first_ + count;
	last_ = first_;
    }


    //this operation is not in homework's task 
    CustomContainer( CustomContainer&& other) = delete;
           

    ~CustomContainer()
    {        
	//std::cout << "using destructor" << std::endl;
	std::allocator_traits<allocator_type>::deallocate(allocator_, first_, capacity());
    }  
     

    size_type capacity() const
    {
	return (end_- first_);
    }


    size_type size() const
    {
	return (last_ - first_);
    }

    
    reference operator[](size_type pos)
    {  
	return (*(first_ + pos));
    }

    
    const_reference operator[](size_t pos) const
    {  
	return (*(first_ + pos));
    }

    
    reference at(size_type  pos)
    {
	if(last_ - first_ <= pos) throw std::out_of_range("error at");
    }


    iterator begin()
    {
	return first_;
    }

    iterator end()
    {
	return last_;
    }
    
    
    void push_back(value_type value)
    {	
	if(first_ == nullptr)
	{
	    reallocate(allocator_, 2);	    
	}

	if (end_ == last_) //condition for allocation
	{
	    int cur_capacity = capacity();
	    unsigned int max_size = std::numeric_limits<value_type>::max();
	    unsigned int new_capacity = cur_capacity * 1.5;
	    if(max_size < new_capacity)
		new_capacity = cur_capacity + 1;
	    reallocate(allocator_, new_capacity);
	}

	std::allocator_traits<allocator_type>::construct(allocator_, last_, value);
	//::new (last_) value_type(value);
	++last_;	
    }  

    
    void reserve(size_type numberObjects)
    {	
	unsigned int quantity_elements = capacity();
	if(quantity_elements >= numberObjects)
	    return;
	unsigned int max_size = std::numeric_limits<value_type>::max();
	if(max_size <  numberObjects)
	{
	    std::cout << "not enouth memory. Command 'reserve' didn't execute" << std::endl;
	}	
	reallocate(allocator_, numberObjects);	
    }	
   
 private:
    allocator_type allocator_;     	

    pointer first_ = nullptr;
    pointer last_ = nullptr;
    pointer end_ = nullptr;

    void reallocate(allocator_type& alloc , long int count)
    {
	pointer new_first =  std::allocator_traits<allocator_type>::allocate(alloc, count);
	pointer old_container_elem = first_;
	pointer new_container_elem = new_first;

	for(; old_container_elem != end_; ++new_container_elem, ++old_container_elem)
	{
	    new(static_cast<void*>(new_container_elem)) value_type{std::move(*old_container_elem)};
	    old_container_elem->~value_type();
	}
	first_ = new_first;
	last_ = new_container_elem;
	end_ = first_ + count;
    }  
};

#endif //CUSTOM_CONTAINER_H

