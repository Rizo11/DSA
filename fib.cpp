
#include <iostream>

using namespace std;

// n-th fibonacci number using recursion
// 1 1 2 3 5 8
// T(n) = 1 + T(n-1) + T(n-2)

int fib(int index) {
    
    if ( index <= 2) {
        return 1;
    }
    
    return fib(index-1) + fib(index-2);
}

int res[300] = {0};

int faster_fib(int index) {
    if (res[index] != 0) {
        return res[index];
    }

    if (index <= 2) {
        res[index] = 1;
    } else {
        res[index] = faster_fib(index-1) + faster_fib(index-2);
    }

    return res[index];

    
}

int main() {

    int index = 0;

    cout << "Enter index: ";
    cin >> index;
    cout << index << "th fibonacci number is: " << faster_fib(index) << endl;

    return 0;
}