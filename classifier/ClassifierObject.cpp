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

std::string ClassifierObject::getColumnName(int i) {
	return "none";
}

void ClassifierObject::setDataAt(int i, double d)
{
	ClassifierObject::data[i] = d;
}

double ClassifierObject::getDataAt(int i)
{
	return ClassifierObject::data[i];
}
