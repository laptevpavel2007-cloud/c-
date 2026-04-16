#include "class.h"
#include <ctime>
#include <fstream>
#include <vector>
#include <iostream>
#include <sstream>
#include <string>
#include <iomanip>

using namespace std;

int main()
{
    setlocale(LC_ALL, "Russian");

    clock_t start = clock();

    Data dt;
    cout << "Введите дату в формате yyyy-MM-dd или yyyy-MM-ddThh:mm:ss:\n";
    do {
        cin >> dt;
        if (!dt.isValid()) {
            cout << "Некорректная дата! Введите дату заново.\n";
        }
    } while (!dt.isValid());
    cout << "Вы ввели: " << dt << "\n";


    //struct Record {
    //    string data_in_f;
    //};

    //ifstream file("data.txt");
    //if (!file.is_open()) {
    //    cerr << "Ошибка: не удалось открыть файл data.txt" << endl;
    //    return 1;
    //}

    //vector<Record> dates_in;
    //string line;

    //while (getline(file, line)) {
    //    if (line.empty()) continue;
    //    istringstream iss(line);
    //    Record rec;
    //    iss >> rec.data_in_f;
    //    dates_in.push_back(rec);
    //}
    //file.close();

    //vector<Data> dates;
    //for (int i = 0; i < dates_in.size(); i++) {
    //    int day, month, year;
    //    double time;
    //    intDate(dates_in[i].data_in_f, day, month, year, time);
    //    dates.push_back(Data(day, month, year, time));
    //}

    //Data* arr = dates.data();
    //quickSort(arr, 0, dates.size() - 1);

    //cout << "Отсортированные даты:\n";
    //for (const auto& d : dates) {
    //    cout << d << endl;
    //}
    //cout << endl;


    moon(dt.day, dt.month, dt.year);

    clock_t end = clock();
    double cpu_time = double(end - start) / CLOCKS_PER_SEC;
    cout << "\nВремя выполнения программы: " << cpu_time << " секунд" << endl;

    return 0;
}