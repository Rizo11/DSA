#include <iostream>

using namespace std;

template < typename T >
T Max (T a, T b) {
    cout << a << " " << b << endl;
    return a > b ? a : b;
}

template <unsigned N >
unsigned long Fact (void) {
    if ( N < 2) return 1;
    return N*Fact<N-1>();
}

template<>
unsigned long Fact<1> (void) {
    return 1;
}

template<>
unsigned long Fact<0> (void) {
    return 1;
}

int main() {
    // double a = 4.4;
    // int b = 8;
    // cout << Max (a - 1, b - 0.1) << endl;

    unsigned a = Fact<15>();
    cout << a << endl;
    return 0;
}