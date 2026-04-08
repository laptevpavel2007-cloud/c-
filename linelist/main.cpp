#include <algorithm>
#include <clocale>
#include <ctime>
#include <iostream>
#include <fstream>
#include "classes.h"

using namespace std;

int main(void) {
    setlocale(LC_ALL, "Russian");

    const int MAX_ITER = 100;
    int time_mass[MAX_ITER] = {};
    int result_mass[MAX_ITER] = {};
    int n_values[MAX_ITER] = {};

    int k;
    cout << "Enter the step of dropping items: ";
    cin >> k;
    if (k <= 0) {
        cerr << "Step must be positive" << endl;
        return 1;
    }

    int idx = 0;
    for (int N = 1000; N <= 1000001 && idx < MAX_ITER; N += 10000) {
        n_values[idx] = N;

        LineList<int> list;

        list.insertFirst(1);
        LineListElem<int>* ptr = list.getStart();
        for (int i = 2; i <= N; ++i) {
            list.insertAfter(ptr, i);
            ptr = ptr->getNext();
        }

        list.makeCircular();

        int size = N;
        clock_t start_time = clock();

        ptr = list.getStart();
        LineListElem<int>* prev = nullptr;

        if (size > 1) {
            prev = ptr;
            while (prev->next != ptr)
                prev = prev->next;
        }

        while (size > 1) {
            for (int i = 1; i < k; ++i) {
                prev = ptr;
                ptr = ptr->next;
            }
            if (ptr == list.getStart()) {
                
                list.deleteAfter(prev);
            
                list.start = prev->next;
                ptr = prev->next;
            }
            else {
                list.deleteAfter(prev);
                ptr = prev->next;
            }
            --size;
        }

        int res = ptr->data;
        clock_t end_time = clock();
        int elapsed_ms = static_cast<int>((end_time - start_time) * 1000.0 / CLOCKS_PER_SEC);


        result_mass[idx] = res;
        time_mass[idx] = elapsed_ms;
        ++idx;

        ptr->next = nullptr;

    }

    ofstream out("results.txt");

    out << "N\ttime(ms)\tresult\n";
    for (int i = 0; i < idx; ++i) {
        out << n_values[i] << "\t" << time_mass[i] << "\t" << result_mass[i] << "\n";
    }
    out.close();

    return 0;
}