#include <iostream>
#include <list>
#include <vector>
#include <iomanip>
#include <string>
#include <sstream>
#include <fstream>
#include "ClassifierObject.h"
#include "Iris.h"
#include "Wine.h"

using namespace std;

bool loadFiles(list<Iris> *irisList, list<Wine> *wineList);

int main(int argc, char* argv[]) {

	list<Iris> irisList;
	list<Wine> wineList;
	loadFiles(&irisList, &wineList);

	cin.get();
	return 0;
}

bool loadFiles(list<Iris> *irisList, list<Wine> *wineList) {
	bool success = false;
	ifstream stream;
	ClassifierObject *object;

	stream.open("bezdekIris.data");
	if (stream.is_open()) {
		string line;
		while (getline(stream, line)) {
			string singleItem;
			stringstream dataString(line);
			vector<double> dataVector;
			while (getline(dataString, singleItem, ',')) {
				double x;
				if (singleItem.compare("Iris-setosa") == 0) {
					x = 1;
				} else if (singleItem.compare("Iris-versicolor") == 0) {
					x = 2;
				} else if (singleItem.compare("Iris-virginica") == 0) {
					x = 3;
				}
				else {
					const char *doubleMe = singleItem.c_str();
					x = atof(doubleMe);
				}
				dataVector.push_back(x);
			}
			if(!dataVector.empty())
			cout << dataVector.at(0) << "\n";
		}
		success = true;
	}
	stream.close();

	return success;
}