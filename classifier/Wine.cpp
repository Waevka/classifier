#include "Wine.h"



Wine::Wine()
{
}


Wine::~Wine()
{	
}

std::string Wine::getColumnName(int i) {
	static const std::string wineColumnNames[] = {
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
	return 12;
}
