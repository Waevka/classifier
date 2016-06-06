#pragma once
#include <iostream>
#include "ClassifierObject.h"

class Wine : public ClassifierObject
{
public:
	Wine();
	~Wine();

	std::string getColumnName(int i);
	int getColumnCount();
};

