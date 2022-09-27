#include <iostream>
#include <vector>
#include <omp.h>


using namespace std;

int main() {
    srand((int) time(nullptr));

    vector<vector<int>> d(6, vector<int>(8));

    for (int i = 0; i < 6; ++i) {
        for (int j = 0; j < 8; ++j) {
            d[i][j] = rand() % 100 + 1;
            cout << d[i][j] << " ";
        }
        cout << endl;
    }
    int max = 0;
    int min = 101;
    double time = omp_get_wtime();


#pragma omp parallel default(none) shared(d, max, min) num_threads(8)
    {
        int min_l = 101, max_l = 0;
#pragma omp for
        for (int i = 0; i < 48; i++) {
            if (max_l < d[i / 8][i % 8])
                max_l = d[i / 8][i % 8];
            if (min_l > d[i / 8][i % 8])
                min_l = d[i / 8][i % 8];
        }

#pragma omp critical
        {
            if (max < max_l) {
                max = max_l;
            }
        }

#pragma omp critical
        {
            if (min < min_l) {
                min = min_l;
            }
        }

    }
    cout << min << " " << max << endl;
    return 0;
}