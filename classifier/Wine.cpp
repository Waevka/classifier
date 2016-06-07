#include "Wine.h"



Wine::Wine()
{
	data = new double[13];
}


Wine::~Wine()
{	
	delete[] data;
}

Wine::Wine(const Wine &toCopy) {
	data = new double[13];
	for (int i = 0; i < 13; i++) {
		data[i] = toCopy.data[i];
	}
}

std::string Wine::getColumnName(int i) {
	static const std::string wineColumnNames[] = {
		"Class",
		"Alcohol",
		"Malic acid",
		"Ash",
		"Alcalinity of ash",
		"Magnesium",
		"Total phenols",
		"Flavanoids",
		"Nonflavanoid phenols",
		"Proanthocyanins",
		"Color intensity",
		"Hue",
		"OD280/OD315 of diluted wines",
		"Proline",
	};

	return wineColumnNames[i];
}

int Wine::getColumnCount() {
	return 13;
}
