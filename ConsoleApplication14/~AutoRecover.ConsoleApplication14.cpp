
#include "pch.h"
#include <iostream>
#include <stack> 

using namespace std;

class Sort {
private:
public:
	virtual void sortName() = 0;
	virtual void sort(int* a, int n) = 0;
};


class Quick : public Sort {
public:

	void sortName() override {
		cout << "Quick Sort : " << endl;
	}
	void sort(int* a, int N) override
	{	int i = 0, j = N - 1;
		int temp, p;

		p = a[N >> 1];

		do {
			while (a[i] < p) i++;
			while (a[j] > p) j--;

			if (i <= j) {
				temp = a[i]; a[i] = a[j]; a[j] = temp;
				i++; j--;
			}
		} while (i <= j);

		if (j > 0) sort(a, j);
		if (N > i) sort(a + i, N - i);
	}
};



void printSortedArray(Sort &sortC, int *arr, int n) {
	int *res = new int[n];
	memcpy(res, arr, n * sizeof(int));
	sortC.sortName();
	sortC.sort(arr,n);
	for (int i = 0; i < n; i++)
		cout << " " << res[i];
	cout << endl;
}




int main()
{
	Quick quickSort;

	int n;
	cout << "Enter array values : " << endl;
	cin >> n;
	cout << " Array values: " << endl;
	int *arrUser = new int[n];
	for (size_t i = 0; i < n; i++) {
		arrUser[i] = rand() % 100;
		cout << arrUser[i] << " ";
	}

	cout << endl;
	quickSort.sort(arrUser, n);

	printSortedArray(quickSort, arrUser, n);
	return 0;
}

