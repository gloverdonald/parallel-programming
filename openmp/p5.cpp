#include <iostream>
#include <vector>
#include <omp.h>

using namespace std;

int main() {
    srand((int) time(nullptr));
    vector<vector<int> > a(6, vector<int>(8));
    for (int i = 0; i < a.size(); ++i) {
        for (int j = 0; j < a[i].size(); ++j) {
            a[i][j] = rand() % 100 + 1;
            cout << a[i][j] << " ";
        }
        cout << endl;
    }


#pragma omp parallel sections default(none) shared(a)
    {
#pragma omp section
        {
            int sum = 0;
            for (int i = 0; i < a.size(); ++i) {
                for (int j = 0; j < a[i].size(); ++j) {
                    sum += a[i][j];
                }
            }
            printf("Average: %lu, thread %d of %d\n", (sum / (a.size() * a[0].size())), omp_get_thread_num(),
                   omp_get_num_threads());
        }

#pragma omp section
        {
            int max_d = a[0][0];
            int min_d = a[0][0];
            for (int i = 0; i < a.size(); ++i) {
                for (int j = 0; j < a[i].size(); ++j) {
                    if (max_d < a[i][j]) {
                        max_d = a[i][j];
                    }
                    if (min_d > a[i][j]) {
                        min_d = a[i][j];
                    }
                }
            }
            printf("Max: %d, Min: %d, thread %d of %d\n", max_d, min_d, omp_get_thread_num(), omp_get_num_threads());
        }

#pragma omp section
        {
            int three_divisor_count = 0;
            for (int i = 0; i < a.size(); ++i) {
                for (int j = 0; j < a[i].size(); ++j) {
                    if (a[i][j] % 3 == 0) {
                        three_divisor_count++;
                    }
                }
            }
            printf("Three divisor amount: %d, thread %d of %d\n", three_divisor_count, omp_get_thread_num(), omp_get_num_threads());
        }
    }
    return 0;
}