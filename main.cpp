#include <iostream>
#include "string.h"

using namespace std;

class Sort {
private:
public:
    virtual string sortName() = 0;

    virtual void sort(int *a, int n) = 0;
};


class Quick : public Sort {
public:

    string sortName() override {
        return "QuickSort";
    }

    void sort(int *mas, int n) {
        int f = 0;
        int l = n - 1;
        int mid = mas[n / 2];
        do {
            while (mas[f] < mid) {
                f++;
            }
            while (mas[l] > mid) {
                l--;
            }
            if (f <= l) {
                int count = mas[f];
                mas[f] = mas[l];
                mas[l] = count;
                f++;
                l--;
            }

        } while (f <= l);

        if (l > 0) {
            sort(mas, l + 1);
        }
        if (f < n) {
            sort(&mas[f], n - f);
        }
    }
};


void printSortedArray(Sort &sortC, int *arr, int n) {
    int *res = new int[n];
    memcpy(res, arr, n * sizeof(int));
    cout << sortC.sortName();
    sortC.sort(res, n);
    for (int i = 0; i < n; i++)
        cout << " " << res[i];
    cout << endl;
}


int main() {
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


    printSortedArray(quickSort, arrUser, n);
    return 0;
}