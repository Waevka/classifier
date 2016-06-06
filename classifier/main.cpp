#include <iostream>
#include "ClassifierObject.h"
#include "Iris.h"
#include "Wine.h"

using namespace std;

int main(int argc, char* argv[]) {
	cout << "top kek" << endl;
	ClassifierObject *c = new Iris();
	cout << c->getColumnCount() << endl;
	c = new Wine();
	cout << c->getColumnCount();
	cin.get();
	return 0;
}