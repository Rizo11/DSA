#include <iostream>
#include <bits/stdc++.h>

using namespace std;

int main() {
    
    int size = 0;
    scanf("%d", &size);

    int arr[size];
    for (int i = 0; i < size; i++) {
		int current_el = 0;
        scanf("%d", &current_el);

        int j = i - 1;
        while (j >= 0 && arr[j] > current_el)
        {
            arr[j+1] = arr[j];
            --j;
        }
        arr[j + 1] = current_el;
        
	}
    for (int i = 0; i < size; i++) {
        printf("%d ", arr[i]);
	}
    printf("\n");

    return 0;
}
