#include <bits/stdc++.h>

using namespace std;

void printTri(int n) {
    int arr[n][n];
    memset(arr, 0, sizeof(arr));
    for (int i = 0; i < n; i++) {
        arr[i][0] = 1;
        cout << arr[i][0] << " ";
        for (int j = 1; j <= i; j++) {
            arr[i][j] = arr[i - 1][j - 1] + arr[i - 1][j];
            cout << arr[i][j] << " ";
        }
        cout << endl;
    }
}

int main() {
    printTri(20);
    return 0;
}