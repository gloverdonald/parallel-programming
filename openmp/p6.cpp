#include <iostream>
#include <vector>
#include <omp.h>


using namespace std;

int main() {
    srand((int) time(nullptr));

    vector<int> a(100);
    for (int i = 0; i < a.size(); ++i) {
        a[i] = rand() % 100 + 1;
    }
    int real_sum = 0;
    int sum1 = 0;
    int sum2 = 0;
    for (int i = 0; i < a.size(); ++i) {
        real_sum += a[i];
    }

#pragma omp parallel for default(none), shared(a, sum1)
    for (int i = 0; i < a.size(); i++) {
        sum1 += a[i];
    }
    printf("\n");
#pragma omp parallel for reduction(+:sum2) default(none), shared(a)
    for (int i = 0; i < a.size(); i++) {
        sum2 += a[i];
        printf("%d ", a[i]);
    }

    printf("\n \nsum1: %d, sum2: %d, real sum: %d", sum1, sum2, real_sum);
    return 0;
}
