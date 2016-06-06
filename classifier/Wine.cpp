#include "Wine.h"



Wine::Wine()
{
	data = new float[13];
}


Wine::~Wine()
{	
	delete[] data;
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
