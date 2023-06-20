// Mukhammadrizo Maribjonov DS-AI 4
// reference: https://www.geeksforgeeks.org/cpp-program-for-quicksort/


/*
 * quicksort works faster that bucket sort
 * */
#include <iostream>
#include <vector>
using namespace std;

template <typename T>
void partition(std::vector<T>& arr, T& pivot, int& i, int& j) {

    pivot = arr[(i + j) / 2];
    // Sorting left and right parts of the pivot element
    while (i <= j) {
        while (arr[i] < pivot) {
            i++;
        }
        while (arr[j] > pivot) {
            j--;
        }
        if (i <= j) {
            std::swap(arr[i], arr[j]);
            i++;
            j--;
        }
    }
}

// O(n log n) on average, and O(n^2) in the worst case

template<typename T>
void quicksort(std::vector<T>& arr, int left, int right) {
    int i = left, j = right;

    T pivot;

    // partitioning the array
    partition(arr, pivot, i, j);

    // Sorting left and right parts of the pivot element

    if (left < j) {
        quicksort(arr, left, j);
    }
    if (i < right) {
        quicksort(arr, i, right);
    }
}

int main() {
    long long int a, c, m, seed, n;
    cin >> a >> c >> m >> seed >> n;

    // random int array
    vector<long long int> rand_int_arr = vector<long long int>();
    long long int x_prev = seed % m;
    for (int i = 0; i <= n; i++) {
        rand_int_arr.push_back(x_prev);
        x_prev = (a*x_prev + c) % m;
    }

    // random double array
    vector<pair<double, int>> rand_double_arr = vector<pair<double, int>>();
    vector<double> j = vector<double>();
    for (int i = 1; i <= n; i++) {
        pair<double, int> newPair = {abs(2.0*rand_int_arr[i]/(1.0*m) - 1.0), i};
        rand_double_arr.push_back(newPair);
    }

    // sort elements
    quicksort(rand_double_arr, 0, rand_double_arr.size()-1);

    int midInd = n/2-1;
    cout << rand_double_arr[midInd].second << endl;
    return 0;
}
