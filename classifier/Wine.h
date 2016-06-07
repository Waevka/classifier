#pragma once
#include <iostream>
#include "ClassifierObject.h"

class Wine : public ClassifierObject
{
public:
	Wine();
	~Wine();
	Wine(const Wine &toCopy);

	std::string getColumnName(int i);
	int getColumnCount();
};

