
#ifndef Context_hpp
#define Context_hpp

#include <stdio.h>
#include "Strategy.hpp"

class Context
{
protected:
	Strategy *strategy;

public:
	virtual ~Context() {}
	virtual void useStrategy() = 0;
	virtual void setStrategy(Strategy *strategy) = 0;
};

#endif /* Context_hpp */