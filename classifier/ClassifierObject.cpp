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
// 3 - Manhattan
bool ClassifierObject::isNewFriendBetter(ClassifierObject *oldF, ClassifierObject *newF, int method) {
	bool result = false;
	int k = getColumnCount();

	if (method == 1) {
		// euclidean
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
		double *oldValues = new double[k-1];
		double *newValues = new double[k-1];

		for (int i = 1; i < k; i++) {
			oldValues[i - 1] = fabs(data[i] - (*oldF).data[i]);
			newValues[i - 1] = fabs(data[i] - (*newF).data[i]);
		}

		int oldMax = 0;
		int newMax = 0;

		for (int i = 0; i < k - 1; i++) {
			if (oldValues[i] < oldValues[oldMax]) oldMax = i;
			if (newValues[i] < newValues[newMax]) newMax = i;
		}

		if (newValues[newMax] < oldValues[oldMax]) result = true;

		delete oldValues, newValues;

	}
	else {
		// Manhattan
		double oldSum = 0;
		double newSum = 0;

		for (int i = 1; i < k; i++) {
			oldSum += fabs(data[i] - (*oldF).data[i]);
			newSum += fabs(data[i] - (*newF).data[i]);
		}
		if (newSum < oldSum) result = true;

	}


	return result;
}
