#include <iostream>
#include <vector>
#include <omp.h>


using namespace std;

int main() {
    srand((int) time(nullptr));

    vector<int> a(12), b(12), c(12);

    omp_set_num_threads(3);
#pragma omp parallel for default(none) shared(a, b, c) schedule(static, 4)
    for (int i = 0; i < 12; ++i) {
        a[i] = rand() % 100 + 1;
        b[i] = rand() % 100 + 1;
        printf("[%d]  %d of %d\n", i, omp_get_thread_num(), omp_get_num_threads());
    }
    cout << endl;

    omp_set_num_threads(4);
#pragma omp parallel for default(none) shared(a, b, c) schedule(dynamic, 3)
    for (int i = 0; i < 12; ++i) {
        c[i] = a[i] + b[i];
        printf("[%d]  %d of %d\n", i, omp_get_thread_num(), omp_get_num_threads());
    }


    for (int i = 0; i < a.size(); ++i) {
        cout << a[i] << " ";
    }
    cout << endl;
    for (int i = 0; i < b.size(); ++i) {
        cout << b[i] << " ";
    }
    cout << endl;
    for (int i = 0; i < c.size(); ++i) {
        cout << c[i] << " ";
    }
    cout << endl;
}