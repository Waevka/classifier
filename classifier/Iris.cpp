#include "Iris.h"



Iris::Iris()
{
	data = new float[5];
}

Iris::~Iris()
{	
	delete[] data;
}

std::string Iris::getColumnName(int i) {
	static const std::string irisColumnNames[] = {
		"class",
		"sepal length in cm",
		"sepal width in cm",
		"petal length in cm",
		"petal width in cm"
	};

	return irisColumnNames[i];
}

int Iris::getColumnCount() {
	return 4;
}