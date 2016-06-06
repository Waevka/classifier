#pragma once

class ClassifierObject
{
public:
	float *data;
	virtual ~ClassifierObject();
	virtual int getColumnCount() = 0;
	void setDataAt(int i, float d);
};

