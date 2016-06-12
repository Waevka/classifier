#include <iostream>
#include <list>
#include <vector>
#include <iomanip>
#include <string>
#include <sstream>
#include <fstream>
#include <time.h>
#include "ClassifierObject.h"
#include "Iris.h"
#include "Wine.h"

using namespace std;

bool loadFiles(vector<ClassifierObject*>*, vector<ClassifierObject*>*, int*);
void divide(const vector<ClassifierObject*>*, vector<vector<ClassifierObject*>*>*, int, int);
void kNNmetric(int, int, vector<ClassifierObject*>*, vector<vector<ClassifierObject*>*>*);
int **cross(int);

int main(int argc, char* argv[]) {

	srand((unsigned int)time(NULL));
	int groupCount = 3;
	int *objectCount = new int[2];

	vector<ClassifierObject*> irisRawData;
	vector<ClassifierObject*> wineRawData;

	loadFiles(&irisRawData, &wineRawData, objectCount);

	cout << "Wczytano pliki. Rozpoczynam obliczenia\n";

	vector<vector<ClassifierObject*>*> irisGroups;
	vector<vector<ClassifierObject*>*> wineGroups;

	for (int i = 0; i < groupCount; i++) {
		irisGroups.push_back(new vector<ClassifierObject*>());
		wineGroups.push_back(new vector<ClassifierObject*>());
	}

	divide(&irisRawData, &irisGroups, groupCount, objectCount[0]);
	divide(&wineRawData, &wineGroups, groupCount, objectCount[1]);
	
	int **groups = cross(groupCount);

	for (int i = 0; i < groupCount; i++) {
		int* currentGroup = groups[i];
		vector<ClassifierObject*> *testingGroup = irisGroups.at(currentGroup[0]);
		vector<vector<ClassifierObject*>*> *testGroups = new vector<vector<ClassifierObject*>*>;
		cout << "\nFold " << i << " of " << groupCount;

		for (int j = 1; j < groupCount; j++) {
			(*testGroups).push_back(irisGroups.at(currentGroup[j]));
		}

		kNNmetric(groupCount, 3, testingGroup, testGroups);
	}
	//add loop for deletion
	//delete[] groups;
	cin.get();
	return 0;
}

bool loadFiles(vector<ClassifierObject*> *irisList, vector<ClassifierObject*> *wineList, int *objectsCount) {
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
				irisList->push_back(object);
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
				wineList->push_back(object);
				objectsCount[1] ++;
			}
		}
		success = success & true;
	}

	return success;
}

void divide(const vector<ClassifierObject*> *data, vector<vector<ClassifierObject*>*> *processedData, int parts, int count) {
	int dataSetGroups = 3;
	size_t groupSize = count / dataSetGroups + count % dataSetGroups;
	int i = 0;

	while(i < count) {
		int group = rand() % 3;
		vector<ClassifierObject*> *chosen = (*processedData)[group];
		if (chosen->size() < groupSize) {
			chosen->push_back((*data)[i]);
			i++;
		}
	}
	//for () {
		//int index = data[i];
		//dataSetGroupsProportions[index]++;
	//}

	int *groupAmount = new int[parts];
	delete groupAmount;
}

void kNNmetric(int k, int NN, vector<ClassifierObject*> *testGroup, vector<vector<ClassifierObject*>*> *testingGroups) {
	for (int z = 0; z < (int)(*testGroup).size(); z++) {

		ClassifierObject *findMyFriends = (*testGroup).at(z);
		vector<ClassifierObject*> *bestFriends = new vector<ClassifierObject*>;
		for (int i = 0; i < NN; i++) (*bestFriends).push_back(((*testingGroups).at(0))->at(i)); // init closest neighbours 
		int testingGroupsCount = (int)(*testingGroups).size();
		
		for (int x = 0; x < testingGroupsCount; x++) {
			vector<ClassifierObject*> *currentTestGroup = (*testingGroups).at(x);
			int testingGroupSize = (int)(*currentTestGroup).size();
			for (int y = 0; y < testingGroupSize; y++) {
				ClassifierObject *currentTestSubject = (*currentTestGroup).at(y);
				for (int i = 0; i < NN; i++) {
					bool change = findMyFriends->isNewFriendBetter((*bestFriends).at(i), currentTestSubject);
				}

			}
		}

	}

	
}

int **cross(int k) {
	int **output = new int*[k];
	for (int i = 0; i < k; i++) {
		output[i] = new int[k];
		int index = 1;
		for (int y = 0; y < k; y++) {
			if (y == i) {
				output[i][0] = y;
			}
			else {
				output[i][index] = y;
				index++;
			}
		}
	}
	return output;
}