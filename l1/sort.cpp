#include <iostream>
#include "sort.h"
using namespace std;





int main() {
	int size = 15;
	int pa[size];
	
	int t[6] = {123, 678, 789, 678, 789, 567};
	insertionSort(t, 6);
	print_arr(t, 6);
}

void bubbleSort_2(int* arr, int size) {
	bool swapped = true;
	while (swapped) {
		swapped = false;
		for (int i = 0; i < size - 1; i++) {
			if (*(arr + i + 1) > *(arr + i) ) {
				int tmp = *(arr + i + 1);
				*(arr + i + 1) = *(arr + i);
				*(arr + i) = tmp;
				swapped = true;
			}	
		}
	}
}
void bubbleSort(int* arr, int size) {

	for(int i = 0; i < size; i++) {
		for(int j = 0; j < size - i - 1; j++) {
			if(*(arr + j) > *(arr + j+1)) {
				int tmp = *(arr + j);
				*(arr + j) = *(arr + j + 1);
				*(arr + j + 1) = tmp;
			}
		}
	}

}

void bubbleSort_c(int* arr, int size) {
	for (int i = 0; i < size; i++) {
		for(int j = size - 1; j >= i + 1; j--) {
			if (*(arr + j) < *(arr + j - 1)) {
				swap((arr + j), (arr + j - 1));
			}
		}
	}
}

void insertionSort(int* arr, int size) {
	for(int i = 1; i < size; i++) {

		int current_el = *(arr + i);
		
		int j = i - 1;
		while (j >= 0 && *(arr + j) > current_el)
		{
			*(arr + j + 1) = *(arr + j);
			--j;
		}
		*(arr + j + 1) = current_el;
	}
}

void selectionSort(int* arr, int size) {
	// int n = 10;
	// int arr[n] = {0};
	// srand(time(0));
	// int random = (rand() % 9);
	// for(int i = 0; i < n; i++) {
    //             arr[i] =  (rand() % 10);
    //     }
	// for(int j = 0; j < n; j++){
    //             cout<<arr[j]<< " ";
    //     }

    //     cout << endl;
	// for(int i = 0; i < n - 1; i++) {
	// 	int current = i;
	// 	for (int j = i + 1; j < n; j++) {
	// 		if(arr[current] > arr[j]) {
	// 			current = j;
	// 		}
	// 	}
	// 	int tmp = arr[i];
	// 	arr[i] = arr[current];
	// 	arr[current] = tmp;

	// }
	// for(int j = 0; j < n; j++){
    //             cout<<arr[j]<< " ";
    //     }

    //     cout << endl;


}


void rn_arr(int* arr, int size) {

	srand(time(0));
        int random = (rand() % 9);
        for(int i = 0; i < size; i++) {
                *(arr + i) =  (rand() % 10);
        }
}

void print_arr(int* arr, int size) {
	for(int i = 0; i < size; i++) {
		cout << *(arr + i) << " ";
	}

	cout << endl;
}

void swap(int* a, int* b) {
	int tmp = *a;
	*a = *b;
	*b = tmp;
}
