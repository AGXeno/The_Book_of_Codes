#include <iostream>
#include <cstdio>
#include <cmath>

using namespace std;
class quadraticEquation{
public:
        float a;
        float b;
        float c;
        float total;

        //this function will take an object as an argument
        float calculate (float a, float b, float c) {
        a = a;
        b = b;
        c = c;
        total = ((-(b) + sqrt((b * b) - (4 * a * c))) / (2 * a));

        return total;
        }

};

int main() {
    quadraticEquation quad;

    cout << "Answer: " << quad.calculate(1, 2, -3) << endl;
    cout << "Answer: " << quad.calculate(2, -7, 3) << endl;
    cout << "Answer: " << quad.calculate(1, -12, -28) << endl;

    return 0;
    }

