#pragma once

class ClassifierObject
{
public:
	double *data;

	ClassifierObject();
	~ClassifierObject();
	virtual int getColumnCount();
	void setDataAt(int i, double d);
};

