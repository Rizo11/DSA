#include <iostream>
#include <bits/stdc++.h>


using namespace std;


int main() {

	int n = 0, k = 0;
	cin >> n >> k;
	string* arr_n = new string[n];
	long long* arr_s = new long long[n];

	for(int i = 0; i < n; i++) {
		cin >> *(arr_n + i) >> *(arr_s + i);
	}
	int m2;
	int m1 = m2 = n < k ? n : k;
	bool swapped = true;
	while (swapped && --m1) {
		swapped = false;
		for (int i = 0; i < n - 1; i++) {
			if (*(arr_s + i + 1) > *(arr_s + i) ) {

				long long tmp = *(arr_s + i + 1);
				string tmp_n = *(arr_n + i + 1);

				*(arr_s + i + 1) = *(arr_s + i);
				*(arr_n + i + 1) = *(arr_n + i);
				*(arr_s + i) = tmp;
				*(arr_n + i) = tmp_n;

				swapped = true;
			}	
		}
	}
	for (int i = 0; i < m2; i++) {
		cout << *(arr_n + i) << " " << *(arr_s + i) << endl;
	}
	return 0;
}
