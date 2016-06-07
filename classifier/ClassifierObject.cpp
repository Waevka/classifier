#include "ClassifierObject.h"


ClassifierObject::ClassifierObject()
{
}

ClassifierObject::~ClassifierObject()
{
}

int ClassifierObject::getColumnCount() {
	return 0;
}

void ClassifierObject::setDataAt(int i, double d)
{
	ClassifierObject::data[i] = d;
}
