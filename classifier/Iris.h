#pragma once
#include <iostream>
#include "ClassifierObject.h"

class Iris : public ClassifierObject
{
public:
	Iris();
	~Iris();

	std::string getColumnName(int i);
	int getColumnCount();
};

