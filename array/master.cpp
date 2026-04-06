#include <algorithm>
#include <iostream>
#include <clocale>
#include <time.h>
#include "Header.h"

using namespace std;

int main(void)
{

	setlocale(LC_ALL, "Russian");

	int N, k;
	cout << "Enter the number of items" << endl;
	cin >> N;

	Array arr(N);
	for (int i = 0; i < N; i++) {
		arr.insert(i + 1);
	};

	cout << "Enter the step of dropping items" << endl;
	cin >> k;
	
	int size = N;
	int del_cnt = 1;
	int t = clock();
	while (size > 1) {
		for (int i = 0; i < size; i++) {
			if (del_cnt == k) {
				arr.remove(i);
				size--;
				del_cnt = 1;
				i--;
			}
			else {
				del_cnt++;
			}
		}
	}
	cout << arr << endl;


	cout << "time = " << clock() - t << " ms." << " = " << (clock() - t)/1000 << " sec" << endl;
	return 0;
}