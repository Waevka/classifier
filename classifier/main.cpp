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
void shuffle(vector<ClassifierObject*>*, int);
void divide(const vector<ClassifierObject*>*, vector<vector<ClassifierObject*>*>*, int, int);
int kNNmetric(int, int, vector<ClassifierObject*>*, vector<vector<ClassifierObject*>*>*, int);
int **cross(int);

int main(int argc, char* argv[]) {

	srand((unsigned int)time(NULL));
	int groupCount = 3;
	int *objectCount = new int[2];
	int userSelection = 0;
	int userNN = 0;

	vector<ClassifierObject*> irisRawData;
	vector<ClassifierObject*> wineRawData;

	loadFiles(&irisRawData, &wineRawData, objectCount);

	cout << "Wczytano pliki. Wybierz metryke:\n";
	cout << "\n1. Euklidesowa";
	cout << "\n2. Czebyszewa";
	cout << "\n3. Taksowkowa";
	cout << "\n\tWybor: ";

	cin >> userSelection;
	if (userSelection > 3 || userSelection < 1) {
		userSelection = 1;
	}
	cin.ignore();
	cin.clear();
	cout << "\n\nWybierz liczbe sasiadow:";
	cout << "\n1. 1";
	cout << "\n2. 3";
	cout << "\n3. 5";
	cout << "\n4. 10";
	cout << "\nt\tWybor: ";

	cin >> userNN;
	if (userNN > 3 || userNN < 1) {
		userNN = 2;
	}

	int NN;
	switch (NN) {
	case 1:
		NN = 1;
		break;
	case 2:
		NN = 3;
		break;
	case 3:
		NN = 5;
		break;
	case 4:
		NN = 10;
		break;
	default:
		break;
	}


	vector<vector<ClassifierObject*>*> irisGroups;
	vector<vector<ClassifierObject*>*> wineGroups;

	for (int i = 0; i < groupCount; i++) {
		irisGroups.push_back(new vector<ClassifierObject*>());
		wineGroups.push_back(new vector<ClassifierObject*>());
	}

	shuffle(&irisRawData, 150);
	shuffle(&wineRawData, 150);
	divide(&irisRawData, &irisGroups, groupCount, objectCount[0]);
	divide(&wineRawData, &wineGroups, groupCount, objectCount[1]);
	
	int **groups = cross(groupCount);

	cout << "\n\nRozpoczynam test dla probek irysow";
	for (int i = 0; i < groupCount; i++) {
		int* currentGroup = groups[i];
		vector<ClassifierObject*> *testingGroup = irisGroups.at(currentGroup[0]);
		vector<vector<ClassifierObject*>*> *testGroups = new vector<vector<ClassifierObject*>*>;
		cout << "\n\nZbior testowy nr " << i+1 << " z " << groupCount;

		for (int j = 1; j < groupCount; j++) {
			(*testGroups).push_back(irisGroups.at(currentGroup[j]));
		}
		kNNmetric(groupCount, 3, testingGroup, testGroups, userSelection);
	}

	cout << "\n\nRozpoczynam test dla probek wina";
	for (int i = 0; i < groupCount; i++) {
		int* currentGroup = groups[i];
		vector<ClassifierObject*> *testingGroup = wineGroups.at(currentGroup[0]);
		vector<vector<ClassifierObject*>*> *testGroups = new vector<vector<ClassifierObject*>*>;
		cout << "\n\nZbior testowy nr " << i+1 << " z " << groupCount;

		for (int j = 1; j < groupCount; j++) {
			(*testGroups).push_back(wineGroups.at(currentGroup[j]));
		}
		kNNmetric(groupCount, 3, testingGroup, testGroups, userSelection);
	}

	//add loop for deletion
	//delete[] groups;
	cin.ignore();
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
				for (int i = 0; i < 4; i++) {
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

void shuffle(vector<ClassifierObject*>* data, int steps) {
	for (int i = 0; i < steps; i++) {
		int a = rand() % (int)(*data).size();
		int b = rand() % (int)(*data).size();

		ClassifierObject *temp = (*data).at(a);
		(*data).at(a) = (*data).at(b);
		(*data).at(b) = temp;
	}
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

int kNNmetric(int k, int NN, vector<ClassifierObject*> *testGroup, vector<vector<ClassifierObject*>*> *testingGroups, int method) {
	int leader;
	double guessedRight = 0;
	ClassifierObject *currentBestFriend = ((*testingGroups).at(0))->at(0);
	cout << "\nProbka|Znaleziona|Prawdziwa|Poprawne?";
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
					if (currentTestSubject == (*bestFriends).at(i)) continue; // jesli adresy sa takie same
					bool change = findMyFriends->isNewFriendBetter((*bestFriends).at(i), currentTestSubject, method);
					if (change == true) {
						(*bestFriends).at(i) = currentTestSubject;
						break;
					}
					if (findMyFriends->isNewFriendBetter(currentBestFriend, currentTestSubject, method)) {
						currentBestFriend = currentTestSubject;
					}
				}

			}
		}

		int *groupCounter = new int[NN] {0};
		for (int x = 0; x < NN; x++) {
			int p = (int)(*bestFriends).at(x)->getDataAt(0) - 1;
			groupCounter[p] ++;
		}
		leader = 0;
		bool multipleFlag = false;
		for (int x = 0; x < NN; x++) {
			if (groupCounter[x] > groupCounter[leader]) { leader = x; };
			if (groupCounter[x] == groupCounter[leader] && x != leader) { multipleFlag = true; }
		}
		if(multipleFlag){
			leader = (int)(*currentBestFriend).getDataAt(0); 
		}
		else {
			leader += 1;
		}
		if ((leader == (int)(*findMyFriends).getDataAt(0))) { guessedRight += 1; }
		cout << "\nProbka " << z << "  |  " << leader << "  |  " << (*findMyFriends).getDataAt(0) << " |" << ((leader == (int)(*findMyFriends).getDataAt(0))?"tak":"nie");

	}
	cout << "\n Poprawne: " << guessedRight << "/" << (*testGroup).size() << " (" << (guessedRight / (double)(*testGroup).size()) * 100 << "%)";
	return leader;
	
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