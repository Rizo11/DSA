#include <iostream>
#include <bits/stdc++.h>
#include "../../../edu/dsa/l1/sort.h"


using namespace std;


int main() {
	
	int size = 15;
	int pa[size];
	
	int t[6] = {123, 678, 789, 678, 789, 567};
	insertionSort(t, 6);
	print_arr(t, 6);

	// int n = 0, k = 0;
	// cin >> n >> k;
	// string* arr_n = new string[n];
	// long long* arr_s = new long long[n];

	// for(int i = 0; i < n; i++) {
	// 	cin >> *(arr_n + i) >> *(arr_s + i);
	// }

	// bool swapped = true;
	// while (swapped) {
	// 	swapped = false;
	// 	for (int i = 0; i < n - 1; i++) {
	// 		if (*(arr_s + i + 1) > *(arr_s + i) ) {

	// 			long long tmp = *(arr_s + i + 1);
	// 			string tmp_n = *(arr_n + i + 1);

	// 			*(arr_s + i + 1) = *(arr_s + i);
	// 			*(arr_n + i + 1) = *(arr_n + i);
	// 			*(arr_s + i) = tmp;
	// 			*(arr_n + i) = tmp_n;

	// 			swapped = true;
	// 		}	
	// 	}
	// }
	// n = n < k ? n : k;
	// for (int i = 0; i < n; i++) {
	// 	cout << *(arr_n + i) << " " << *(arr_s + i) << endl;
	// }
	return 0;
}
