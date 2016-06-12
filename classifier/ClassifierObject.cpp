#include "ClassifierObject.h"
#include <math.h>


ClassifierObject::ClassifierObject()
{
}

ClassifierObject::~ClassifierObject()
{
}

int ClassifierObject::getColumnCount() {
	return 0;
}

std::string ClassifierObject::getColumnName(int i) {
	return "none";
}

void ClassifierObject::setDataAt(int i, double d)
{
	ClassifierObject::data[i] = d;
}

double ClassifierObject::getDataAt(int i)
{
	return ClassifierObject::data[i];
}

// method:
// 1 - Euclidean
// 2 - Chebyshev
// 3 - taxi
bool ClassifierObject::isNewFriendBetter(ClassifierObject *oldF, ClassifierObject *newF, int method) {
	bool result = false;

	if (method == 1) {
		// euclidean
		int k = getColumnCount();
		double oldSum = 0;
		double newSum = 0;

		for (int i = 1; i < k; i++) {
			oldSum += pow(data[i] - (*oldF).data[i], 2);
			newSum += pow(data[i] - (*newF).data[i], 2);
		}
		sqrt(oldSum);
		sqrt(newSum);

		if (newSum < oldSum) result = true;
	}
	else if (method == 2) {
		// chebyshev

	}
	else {

	}


	return result;
}
