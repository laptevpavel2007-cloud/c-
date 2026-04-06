#include <algorithm>
#include <clocale>
#include <ctime>
#include <iostream>
#include "classes.h"

using namespace std;

int main(void) {
	setlocale(LC_ALL, "Russian");
	LineList<int> list;

	int N, k;
	std::cout << "¬ведите количество элементов:" << endl;
	cin >> N;

	list.insertFirst(1);
	LineListElem<int>* ptr = list.getStart();
	for (int i = 2; i != N+1; i++) {
		list.insertAfter(ptr, i);
		ptr = ptr->getNext();
	}

	std::cout << "¬ведите шаг выбывани€:" << endl;
	cin >> k;
	
	int size = N;
	int del_cnt = 1;
	int t = clock();
	ptr = list.getStart();
	LineListElem<int>* boofer = nullptr;
	while (size > 1) {

		if (del_cnt == k) {

			if (boofer == nullptr) {
				list.deleteFirst();
				ptr = list.getStart();
				boofer = nullptr;
			}

			else {
				list.deleteAfter(boofer);
				ptr = boofer->getNext();

				if (ptr == nullptr) {
					ptr = list.getStart();
					boofer = nullptr;
				}
			}

			size--;
			del_cnt = 1;
		}

		else {
			del_cnt++;
			boofer = ptr;
			ptr = ptr->getNext();

			if (ptr == nullptr) {
				ptr = list.getStart();
				boofer = nullptr;
			}
		}
	}
	std::cout << list << endl;

	std::cout << "time = " << clock() - t << " ms." << " = " << (clock() - t) / 1000 << " sec" << endl;

	return 0;
}