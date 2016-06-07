#pragma once
#include <iostream>

class ClassifierObject
{
public:
	double *data;

	ClassifierObject();
	~ClassifierObject();
	virtual std::string getColumnName(int i);
	virtual int getColumnCount();
	void setDataAt(int i, double d);
};

