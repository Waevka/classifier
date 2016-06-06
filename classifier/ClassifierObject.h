#pragma once

class ClassifierObject
{
public:
	double *data;
	virtual ~ClassifierObject();
	virtual int getColumnCount() = 0;
	void setDataAt(int i, double d);
};

