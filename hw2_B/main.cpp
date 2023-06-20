// Mukhammadrizo Maribjono DS-AI 4
// reference: https://www.geeksforgeeks.org/bucket-sort-2/
// reference: https://www.geeksforgeeks.org/merge-sort/


#include <bits/stdc++.h>

using namespace std;

template <typename T>
void merge(vector<T>& arr, int left, int mid, int right) {
    int i = left, j = mid + 1, k = 0;
    vector<pair<double, int>> temp(right - left + 1);

    while (i <= mid && j <= right) {
        if (arr[i].first < arr[j].first) {
            temp[k++] = arr[i++];
        } else {
            temp[k++] = arr[j++];
        }
    }

    while (i <= mid) {
        temp[k++] = arr[i++];
    }

    while (j <= right) {
        temp[k++] = arr[j++];
    }

    for (i = left, k = 0; i <= right; i++, k++) {
        arr[i] = temp[k];
    }
}

// merge sort O(n log n)
template <typename T>
void mergeSort(vector<T>& arr, int left, int right) {
    if (left >= right) {
        return;
    }

    int mid = (left + right) / 2;

    mergeSort(arr, left, mid);
    mergeSort(arr, mid + 1, right);

    merge(arr, left, mid, right);
}


// O(n) in the best case, O(n log n) in the average case, to O(n^2) in the worst case
template <typename T>
void bucketSort(vector<T>& arr) {
        int n = arr.size();
        vector<vector<T>> buckets(n);

        // Assign elements to buckets based on their key value
        for (int i = 0; i < n; i++) {
            int bucketIndex = n * arr[i].first;
            bucketIndex = bucketIndex >= n ? bucketIndex-1 : bucketIndex;
            buckets[bucketIndex].push_back(arr[i]);
        }

        // Sort each bucket
        for (auto& bucket : buckets) {
            if (bucket.size() <= 1) continue;
            mergeSort(bucket, 0, bucket.size()-1);
        }

        // Concatenate the buckets into the original array
        int index = 0;
        arr.clear();
        for (auto& bucket : buckets) {
            if (bucket.empty()) continue;
            for (auto& s : bucket) {
                arr.push_back(s);
            }
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
    bucketSort(rand_double_arr);

    int midInd = n/2-1;
    cout << rand_double_arr[midInd].second << endl;






    return 0;
}
