/***************************************************************
<John Markey>
<Stack.hpp>
<Project 1>
<Contains the main methods that one would need to make to implement
a basic Stack>
***************************************************************/
#ifndef _STACK_H
#define _STACK_H 1

#include <deque>

#include "StackInterface.h"

template <typename T>
class Stack : public StackInterface<T>
{
protected:
    std::deque<T> _container;

public:

    // TODO

	//DESTRUCTOR
	virtual ~Stack()
	{
		clear();
	}

	//returns the size of the container
	virtual int size() const
	{
		return _container.size();
	}

	//returns true if array is empty, false if full
	bool empty() const
	{
		return _container.empty();
	}

	//pushes item to the top of the stack, returns true upon success
	bool push(const T& val = T{})
	{
		_container.push_front(val);
		if (_container.front() == val)
			return true;
		return false;
	}

	//works exactly as push, theyre synonyms
	bool add(const T& val = T{})
	{
		return push(val);
	}
	
	//sets val to the container front value, pops the front variable out
	//if pop is successful, returns true
	virtual bool pop(T& val = T{})
	{
		if (empty())
			return false;
		val = _container.front();
		_container.pop_front();
		return true;
	}
	
	//sets val to front value
	//returns true if peek not empty, else false
	bool peek(T& val = T{}) const
	{
		if (empty())
			return false;
		val = _container.front();
		return true;
	}

	//clears the deque container
	void clear()
	{
		_container.clear();
	}

	//searches all elements for target value, if found, 
	//returns the number of spaces away from the front
	//otherwise returns an index out of bounds
	int search(const T& target = T{}) const
	{
		for (int i = 0; i < size(); i++)
		{
			if (_container.at(i) == target)
			{
				return i+1;
			}
		}
		return -1;
	}
    // Overloaded output operator
    template <typename U>
    friend std::ostream& operator<<(std::ostream& os, const Stack<U>& s)
    {
        //for (std::vector<U>::const_iterator itr = s._container.begin(); itr != s._container.end(); )
        for (Stack<U>::const_iterator itr = s._begin(); itr != s.end(); )
        {
            os << *itr;
            itr++;
            if (itr != s._container.end()) os << ", ";
        }

        return os;
    }

  public:
    // Consistency check for this container; nothing to verify
    virtual bool check() const { return true; }
};

#endif