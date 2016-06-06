#include "ClassifierObject.h"

ClassifierObject::~ClassifierObject()
{
}

void ClassifierObject::setDataAt(int i, double d)
{
	ClassifierObject::data[i] = d;
}
