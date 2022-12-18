#include <iostream>
using namespace std;

int main() {
    int base_height;
    int base_width;
    int head_width;
    int head_widthCount;

    cin >> base_height;
    cin >> base_width;

    for (int i = 0; i < base_height; i++ ) {
        for (int j = 0; j < base_width; j++) {
            cout << "*";
        }
        cout << endl;
    }

    cin >> head_width;
    head_widthCount = head_width;

    while (head_width <= base_width) {
        cout << "BASE WIDTH: " << base_width << endl;
        cin >> head_width;
        cout << "HEAD WIDTH: " << head_width << endl;
        head_widthCount = head_width;
    }

    for (int k = head_width; k > 0; k--) {
        for (int l = head_widthCount; l > 0; l--) {
            cout << "*";
        }
        head_widthCount -= 1;
        cout << endl;
    }
    return 0;
}
