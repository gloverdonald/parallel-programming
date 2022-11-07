#include <iostream>
#include <vector>
#include <omp.h>


using namespace std;

int main() {
    srand((int) time(nullptr));
    int n = 32000;
    //cin >> n;
    vector<int> a(n);

    for (int i = 0; i < a.size(); ++i) {
        a[i] = rand() % 100 + 1;
        cout << a[i] << " ";
    }
    int max = -1;

#pragma omp parallel default(none) shared(a, max)
    {
        int max_l = -1;
#pragma omp for
        for (int i = 0; i < a.size(); ++i) {
            if (a[i] % 7 == 0 && a[i] > max_l) {
                max_l = a[i];
            }
        }
#pragma omp critical
        if (max < max_l) {
            max = max_l;
        }

    }
    int real_max = -1;

    for (int i = 0; i < a.size(); ++i) {
        if (a[i] % 7 == 0 && a[i] > real_max) {
            real_max = a[i];
        }
    }

    cout << endl << max << " " << real_max << endl;
    return 0;
}