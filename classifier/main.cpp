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

bool loadFiles(list<ClassifierObject>*, list<ClassifierObject>*, int*);
void divide(const list<ClassifierObject>*, vector<vector<ClassifierObject>>*, int, int);

int main(int argc, char* argv[]) {

	int *objectCount = new int[2];
	list<ClassifierObject> *irisRawData = new list<ClassifierObject>;
	list<ClassifierObject> *wineRawData = new list<ClassifierObject>;
	loadFiles(irisRawData, wineRawData, objectCount);

	vector<vector<ClassifierObject>> *irisGroups = new vector<vector<ClassifierObject>>();
	vector<vector<ClassifierObject>> *wineGroups = new vector<vector<ClassifierObject>>();

	divide(irisRawData, irisGroups, 3, objectCount[0]);
	divide(wineRawData, wineGroups, 3, objectCount[1]);

	cin.get();
	return 0;
}

bool loadFiles(list<ClassifierObject> *irisList, list<ClassifierObject> *wineList, int *objectsCount) {
	bool success = false;
	ifstream stream;
	///////////////////////////////// load iris data
	stream.open("bezdekIris.data");
	objectsCount[0] = 0;
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
				objectsCount[0] ++;
			}
		}
		success = true;
	}
	stream.close();
	///////////////////////////////////// load wine data
	stream.open("wine.data");
	objectsCount[1] = 0;
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
				objectsCount[1] ++;
			}
		}
		success = success & true;
	}

	return success;
}

void divide(const list<ClassifierObject>* data, vector<vector<ClassifierObject>>* processedData, int parts, int count) {
	int dataSetGroups = 3;
	int *dataSetGroupsProportions = new int[dataSetGroups] {0};

	//for () {
		//int index = data[i];
		//dataSetGroupsProportions[index]++;
	//}

	int *groupAmount = new int[parts];

	delete dataSetGroupsProportions;
	delete groupAmount;
}
