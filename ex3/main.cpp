#include <iostream>

using namespace std;

int h(int k) {

    return k*k + k + 3;
}


int main() {

    int a = 0;
    int arr[13] = {0};
    int input[12] = {5, 28, 19, 15, 20, 33, 12, 17, 10, 13, 3, 33};
    int used[34] = {0};
    int c = 0;
    for ( auto m : input) {
        int l = h(m) % 13;
        if (arr[l] == 0) {
            arr[l] = m;
            used[m] = 1;
        } else if (used[m])
        {
            continue;
        } else {
            int j = 0;
            while (arr[(h(m) + (++j)) % 13] != 0)
            {

            }
            arr[(h(m) + j) % 13] = m;
            used[m] = 1;
        }
        c++;
    }

    for (size_t i = 0; i < 13; i++)
    {
        cout << i << " " << arr[i] << "\n";
    }



}
