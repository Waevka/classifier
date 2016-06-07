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

bool loadFiles(list<ClassifierObject>*, list<ClassifierObject>*);
void divide(const list<ClassifierObject>*, vector<vector<ClassifierObject>>*);

int main(int argc, char* argv[]) {

	list<ClassifierObject> *irisRawData = new list<ClassifierObject>;
	list<ClassifierObject> *wineRawData = new list<ClassifierObject>;
	loadFiles(irisRawData, wineRawData);

	vector<vector<ClassifierObject>> *irisGroups = new vector<vector<ClassifierObject>>();
	vector<vector<ClassifierObject>> *wineGroups = new vector<vector<ClassifierObject>>();

	divide(irisRawData, irisGroups);
	divide(wineRawData, wineGroups);

	cin.get();
	return 0;
}

bool loadFiles(list<ClassifierObject> *irisList, list<ClassifierObject> *wineList) {
	bool success = false;
	ifstream stream;
	///////////////////////////////// load iris data
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
			if (!dataVector.empty()) {
				Iris *object = new Iris();
				for (int i = 0; i < 2; i++) {
					object->setDataAt(i+1, dataVector.at(i));
				}
				object->setDataAt(0, dataVector.at(4));
				irisList->push_back(*object);
			}
		}
		success = true;
	}
	stream.close();
	///////////////////////////////////// load wine data
	stream.open("wine.data");
	if(stream.is_open()) {
		string line;
		while (getline(stream, line)) {
			string singleItem;
			stringstream dataString(line);
			vector<double> dataVector;
			while (getline(dataString, singleItem, ',')) {
				double x;
				const char *doubleMe = singleItem.c_str();
				x = atof(doubleMe);
				dataVector.push_back(x);
			}
			if (!dataVector.empty()) {
				Wine *object = new Wine();
				for (int i = 0; i < 13; i++) {
					object->setDataAt(i, dataVector.at(i));
				}
				wineList->push_back(*object);
			}
		}
		success = success & true;
	}

	return success;
}

void divide(const list<ClassifierObject>* data, vector<vector<ClassifierObject>>* processedData) {
	int parts = 3;
}
