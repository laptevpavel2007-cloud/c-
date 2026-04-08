#include <algorithm>
#include <iostream>
#include <clocale>
#include <ctime>
#include <fstream>
#include "Header.h"

using namespace std;

int main(void)
{
    setlocale(LC_ALL, "Russian");

    const int MAX_ITER = 40;
    int time_mass[MAX_ITER] = {};
    int result_mass[MAX_ITER] = {};
    int n_values[MAX_ITER] = {};

    int k;
    cout << "Enter the step of dropping items: ";
    cin >> k;

    int idx = 0;
    for (int N = 1000; N <= 1000000; N += 25000) {
        n_values[idx] = N;

        Array arr(N);
        for (int i = 0; i < N; i++) {
            arr.insert(i + 1);
        }

        int size = N;
        int del_cnt = 1;
        int pos = 0;
        clock_t start = clock();

        while (size > 1) {
            
            for (int step = 0; step < size; step++) {
                if (del_cnt == k) {
                    arr.remove(pos);
                    size--;
                    del_cnt = 1;
                    
                    break;
                }
                else {
                    del_cnt++;
                    pos++;
                    if (pos >= size) {
                        pos = 0;
                    }
                }
            }
        }

        int res = arr[0];
        clock_t end = clock();
        int elapsed_ms = ((end - start) * 1000.0 / CLOCKS_PER_SEC);

        result_mass[idx] = res;
        time_mass[idx] = elapsed_ms;
        idx++;
    }

    ofstream out("results.txt");
    if (!out.is_open()) {
        cerr << "Не удалось открыть файл для записи\n";
        return 1;
    }

    out << "N\ttime(ms)\tresult\n";
    for (int i = 0; i < idx; i++) {
        out << n_values[i] << "\t" << time_mass[i] << "\t" << result_mass[i] << "\n";
    }
    out.close();

    return 0;
}