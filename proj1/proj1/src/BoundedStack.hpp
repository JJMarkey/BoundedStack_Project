/***************************************************************
<John Markey>
<BoundedStack.hpp>
<Project 1>
<Inherits methods from Stack, while incorporating the BoundedStack interface
to create a BoundedStack>
***************************************************************/
#ifndef BOUNDED_STACK_H
#define BOUNDED_STACK_H 1

#include <vector>

#include "Stack.hpp"
#include "BoundedInterface.hpp"

template <typename T>



class BoundedStack : public Stack<T>, public BoundedInterface
{
  protected:

	//counts how many items have been pushed
	//increments for pushes, decrements for pops
    int count = 0;

  public:
    BoundedStack(int bound = 10) : Stack(), BoundedInterface{abs(bound)}
    {
    }
	

	//push for boundedstack, pushes elements in if not at capacity
	//if at capacity, removes "oldest" element from array
	bool push(const T& val = T{})
	{
		if (atCapacity())
		{
			_container.pop_back();
			return Stack::push(val);
		}
		count++;
		return Stack::push(val);
	}

	//pops element from array, decrements count
	bool pop(T& val = T{})
	{
		count--;
		return Stack::pop(val);		
	}

	//add works exactly like push, so it just calls push
	bool add(const T& val = T{})
	{
		return push(val);
	}

	//returns the max capacity for the container
	int capacity() const
	{
		return _UPPER_BOUND_NUM_ELEMENTS;
	}

	//returns true if full, false if not at full capacity
	bool atCapacity() const
	{
		if (_container.size() == capacity())
			return true;
		return false;
	}

	//returns number of elements able to be added to bounded stack
	int available() const
	{
		return(capacity() - count);
		
	}
  public:
    // Internal consistency check
    virtual bool check() const
    {
        bool superCheck = Stack::check();
        bool sizeConsistent = isSizeConsistent();

        return superCheck && sizeConsistent;
    }

    // Verifies size <= UPPER BOUND
    bool isSizeConsistent() const
    {
        return size() <= _UPPER_BOUND_NUM_ELEMENTS;
    }
};

#endif