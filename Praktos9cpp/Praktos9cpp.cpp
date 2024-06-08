#include <iostream>
#include <vector>
#include <thread>
#include <functional>
using namespace std;

class MergeSort {
public:
    void Sort(vector<int>& array) {
        if (array.size() > 1) {
            mergeSort(array, 0, array.size() - 1);
        }
    }

private:
    void mergeSort(vector<int>& array, int left, int right) {
        if (left < right) {
            int middle = left + (right - left) / 2;
            mergeSort(array, left, middle);
            mergeSort(array, middle + 1, right);
            merge(array, left, middle, right);
        }
    }

    void merge(vector<int>& array, int left, int middle, int right) {
        int n1 = middle - left + 1;
        int n2 = right - middle;
        vector<int> L(n1), R(n2);
        for (int i = 0; i < n1; ++i)
            L[i] = array[left + i];
        for (int j = 0; j < n2; ++j)
            R[j] = array[middle + 1 + j];

        int i = 0, j = 0, k = left;
        while (i < n1 && j < n2) {
            if (L[i] <= R[j]) {
                array[k] = L[i];
                ++i;
            }
            else {
                array[k] = R[j];
                ++j;
            }
            ++k;
        }

        while (i < n1) {
            array[k] = L[i];
            ++i;
            ++k;
        }

        while (j < n2) {
            array[k] = R[j];
            ++j;
            ++k;
        }
    }
};

int main() {
    vector<int> array(10);
    cout << "Введите 10 целых чисел:" << endl;
    for (int i = 0; i < 10; ++i) {
        cin >> array[i];
    }
    MergeSort sorter;
    auto sortFunction = [&sorter](vector<int>& arr) {
        sorter.Sort(arr);
        };
    thread sortThread(sortFunction, ref(array));
    sortThread.join();
    cout << "Отсортированный массив:" << endl;
    for (const int& num : array) {
        cout << num << " ";
    }
    cout << endl;
    return 0;
}
