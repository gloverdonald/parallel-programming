#include <iostream>
#include <vector>
#include <omp.h>


using namespace std;

int main() {
    srand((int) time(nullptr));

    vector<int> a(30);

    for (int i = 0; i < 30; ++i) {
        a[i] = rand() % 100 + 1;
        cout << a[i] << " ";
    }

    int count = 0;
#pragma omp parallel for default(none) shared(a, count) num_threads(8)
    for (int i = 0; i < a.size(); ++i) {
        if (a[i] % 9 == 0) {
#pragma omp atomic
            count++;
        }
    }
    cout << endl << count << endl;
    return 0;
}