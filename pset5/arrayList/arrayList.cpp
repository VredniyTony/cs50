#include <iostream>
#include <stdio.h>
#include <windows.h>

using namespace std;

class arrayList {
	int* array;
	int numAddToMassive = 0;
	int sizeOfMassive = 10;
public:
	arrayList() {
		array = new int[10];
	}
	~arrayList() {
	}
	void add(int data) {
		if (numAddToMassive > sizeOfMassive) {
			resize();
		}
		array[numAddToMassive] = data;
		numAddToMassive++;
	}

	void resize() {
		sizeOfMassive = sizeOfMassive * 2;
		int* newArray = new int[sizeOfMassive];
		for (int counter = 0; counter < sizeOfMassive; counter++) {
			newArray[counter] = array[counter];
		}
		array = newArray;
	}

	void remove(int numRemove) {
		for (int counter = numRemove; counter <= sizeOfMassive; counter++) {
			array[counter] = array[counter + 1];
		}
		numAddToMassive--;
		realSize();
	}

	void realSize() {
		sizeOfMassive = numAddToMassive;
		int* newArray = new int[sizeOfMassive];
		for (int counter = 0; counter < sizeOfMassive; counter++) {
			newArray[counter] = array[counter];
		}
		array = newArray;
	}

	void print() {
		for (int counter = 0; counter < sizeOfMassive; counter++) {
			std::cout << array[counter] << " ";
		}
	}
};

int main() {
	arrayList inData;
	for (int counter = 1; counter <= 25; counter++) {
		inData.add(counter);
	}
	inData.realSize();
	inData.remove(1);
	inData.print();
	system("pause");
	return 0;
}