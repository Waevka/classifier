#include "ClassifierObject.h"

ClassifierObject::~ClassifierObject()
{
}

void ClassifierObject::setDataAt(int i, float d)
{
	ClassifierObject::data[i] = d;
}
