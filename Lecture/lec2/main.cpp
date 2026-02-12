#include "console.h"
#include <cmath>
#include <iostream>
using namespace std;

void quadratic(int a, int b, int c, double& root1, double& root2);

int main(void) {
    int a, b, c;
    double x1, x2;
    cin >> a >> b >> c;
    quadratic(a, b, c, x1, x2);
    cout << x1 << endl << x2 << endl;
    return 0;
}

void quadratic(int a, int b, int c, double& root1, double& root2) {
    root1 = (- b - sqrt(b * b - 4 * a * c)) / (2 * a);
    root2 = (- b + sqrt(b * b - 4 * a * c)) / (2 * a);
}
