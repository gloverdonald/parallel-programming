#include <iostream>
#include <cstdlib>
#include <ctime>
#include <vector>
using namespace std;


int main() {
    srand((int) time(nullptr));

    vector<int> a(10);
    vector<int> b(10);
    for (int i = 0; i < 10; ++i) {
        a[i] = rand() % 100 + 1;
        b[i] = rand() % 100 + 1;
    }
    for (int i = 0; i < a.size(); ++i) {
        cout << a[i] << " " << b[i] << endl;
    }
    int min_a = a[0];
    int max_b = a[0];

#pragma omp parallel sections default(none) num_threads(2) shared(a, b, min_a, max_b)
    {
#pragma omp section
        {

            for (int i = 0; i < b.size(); ++i) {
                if (min_a > a[i]) {
                    min_a = a[i];
                }
            }
        }

#pragma omp section
        {
            for (int i = 0; i < b.size(); ++i) {
                if (max_b < b[i]) {
                    max_b = b[i];
                }
            }
        }
    }

    printf("min A: %d, max B: %d", min_a, max_b);
    return 0;
}
