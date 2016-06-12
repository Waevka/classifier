#pragma once
#include <iostream>

class ClassifierObject
{
public:
	double *data;

	ClassifierObject();
	~ClassifierObject();
	virtual std::string getColumnName(int i);
	virtual int getColumnCount() = 0;
	void setDataAt(int i, double d);
	double getDataAt(int i);
	virtual bool isNewFriendBetter(ClassifierObject*, ClassifierObject*);
};

