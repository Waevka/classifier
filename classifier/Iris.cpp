#include "Iris.h"



Iris::Iris()
{
	data = new double[5];
}

Iris::~Iris()
{	
	delete[] data;
}

Iris::Iris(const Iris &toCopy) {
	data = new double[5];
	for (int i = 0; i < 5; i++) {
		data[i] = toCopy.data[i];
	}
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