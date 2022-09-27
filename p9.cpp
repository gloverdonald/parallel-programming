#include <iostream>
#include <vector>
#include <omp.h>


using namespace std;

int main() {
    srand((int) time(nullptr));

    int n, m;
    cin >> n >> m;

    vector<vector<int>> matrix(n, vector<int>(m));
    vector<int> vec(m);
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            matrix[i][j] = rand() % 100 + 1;
            cout << matrix[i][j] << " ";
        }
        cout << endl;
    }

    for (int i = 0; i < m; ++i) {
        vec[i] = rand() % 100 + 1;
        cout << vec[i] << " ";
    }
    cout << endl;





    vector<int> ans_1(n);
    int time = omp_get_wtime();
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            ans_1[i] += matrix[i][j] * vec[j];
        }
    }
    printf("time: %f\n", omp_get_wtime() - time);

    vector<int> ans(n);
    time = omp_get_wtime();
#pragma omp parallel for default(none) shared(matrix, ans, vec, n, m) schedule(guided, 3)
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            ans[i] += matrix[i][j] * vec[j];
        }
    }
    printf("parallel time: %f\n", omp_get_wtime() - time);

    cout << "parallel result: ";
    for (const auto &item: ans_1) {
        cout << item << " ";
    }

    cout << "result: ";
    for (const auto &item: ans) {
        cout << item << " ";
    }

    return 0;
}