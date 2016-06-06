#include "Iris.h"



Iris::Iris()
{
}


Iris::~Iris()
{
}

std::string Iris::getColumnName(int i) {
	static const std::string irisColumnNames[] = {
		"sepal length in cm",
		"sepal width in cm",
		"petal length in cm",
		"petal width in cm",
		"class"
	};

	return irisColumnNames[i];
}

int Iris::getColumnCount() {
	return 4;
}