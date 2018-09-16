/***************************************************************
<John Markey>
<TimedStack.hpp>
<Project 1>
<Inherits from methods from Stack, while implementing the TimedStack interface
to create a TimedStack>
***************************************************************/
#ifndef _TIMED_STACK_H
#define _TIMED_STACK_H 1

#include <deque>

#include "Stack.hpp"
#include "TimedInterface.hpp"

template <typename T>
class TimedStack : public Stack<T>, public TimedInterface
{
	std::deque<T> _times;
  public:
    TimedStack() : Stack<T>{}
    {
    }

	//DESTRUCTOR
    virtual ~TimedStack()
    {
       clear();
    }

    // Pushes an item onto the top of this stack.
    // Increments the time
    virtual bool push(const T& value = T{})
    {
		_container.push_front(value);
		if (_container.front() == value)
		{
			_times.push_front(_currentTime);
			increment();
			return true;
		}
		return false;
		
    }

    // Removes the object at the top of this stack and returns that
    // object as the value of this function.
    // Increments the time
    bool pop(T& value = T{})
	{
		if (empty())
		{
			return false;
		}
		value = _container.front();
		_times.pop_front();
		_container.pop_front();
		increment();
		return true;
    }

    // Remove all values older than (given) time t (equal times remain)
	// returns total number of items removed
    virtual int sweep(unsigned lowerBoundTime)
    {
		//creates an int to hold the container's size before
		//removing elements
		int originalSize = _container.size();

		for (int i = 0; i < _times.size(); i++)
		{
			if (_times.at(i) < lowerBoundTime)
			{
				_times.erase(_times.begin() + i, _times.end());
				_container.erase(_container.begin() + i, _container.end());
				return (originalSize - _times.size());
			}
		}
		return 0;
    }
    // Removes all elements from the stack and resets the time.
    virtual void clear()
    {
		_container.clear();
		_times.clear();
		_currentTime = _START_TIME;
    }

public:
    // Internal consistency check
    virtual bool check() const
    {
        bool superCheck = Stack::check();
        bool sizeConsistent = isSizeConsistent();
        bool decreasing = isDecreasingTime();

        return superCheck && sizeConsistent && decreasing;
    }

    // Verifies size consistency with times and values
    bool isSizeConsistent() const
    {
        return _times.size() == _container.size();
    }

    // Verifies that all times are "as expected": everywhere decreasing
    bool isDecreasingTime() const
    {
        if (size() <= 1) return true;

        for (unsigned int index = 0; index < _times.size() - 1; index++)
        {
            if (_times[index] <= _times[index + 1]) return false;
        }

        return true;
    }
};

#endif