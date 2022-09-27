#include <iostream>
#include <vector>
#include <omp.h>

using namespace std;

int main() {
    double time;
    vector<int> a(31000);
    for (int i = 0; i < a.size(); ++i) {
        a[i] = i;
    }
    omp_set_num_threads(8);

    vector<double> b(31000);

    for (int j = 100; j <= 400; j+=100) {
        time = omp_get_wtime();
#pragma omp parallel for default(none) shared(b, a, j) schedule(static, j)
        for (int i = 1; i < b.size() - 1; ++i) {
            b[i] = (a[i - 1] + a[i] + a[i + 1]) / 3.0;
        }
        printf("static: %f\n", omp_get_wtime() - time);
    }
    for (int j = 1; j <= 8; ++j) {
        time = omp_get_wtime();
#pragma omp parallel for default(none) shared(b, a, j) schedule(dynamic, j)
        for (int i = 1; i < b.size() - 1; ++i) {
            b[i] = (a[i - 1] + a[i] + a[i + 1]) / 3.0;
        }
        printf("dynamic: %f\n", omp_get_wtime() - time);
    }


    for (int j = 1; j <= 8; ++j) {
        time = omp_get_wtime();
#pragma omp parallel for default(none) shared(b, a, j) schedule(guided, j)
        for (int i = 1; i < b.size() - 1; ++i) {
            b[i] = (a[i - 1] + a[i] + a[i + 1]) / 3.0;
        }
        printf("guided: %f\n", omp_get_wtime() - time);
    }


    time = omp_get_wtime();
#pragma omp parallel for default(none) shared(b, a) schedule(auto)
    for (int i = 1; i < b.size() - 1; ++i) {
        b[i] = (a[i - 1] + a[i] + a[i + 1]) / 3.0;
    }
    printf("auto: %f\n", omp_get_wtime() - time);

    return 0;
}