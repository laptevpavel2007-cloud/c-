#include "class.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <iomanip>
#include <cmath>

Data::Data(int d, int m, int y, double t) {
    day = d;
    month = m;
    year = y;
    time = t;
};

istream& operator >>(istream& in, Data& r) {
    string date_str;
    in >> date_str;
    intDate(date_str, r.day, r.month, r.year, r.time);
    return in;
};

ostream& operator <<(ostream& out, const Data& r) {
    string day_week[] = { "Понедельник", "Вторник", "Среда", "Четверг", "Пятница", "Суббота", "Воскресенье" };
    int w = (day_in_months(r.day, r.month, r.year) + 6) % 7;
    string d_w = day_week[w];

    out << r.year << "-" << (r.month < 10 ? "0" : "") << r.month << "-" << (r.day < 10 ? "0" : "") << r.day;

    if (r.time > 0 || r.time == 0) {
        int hours = (int)(r.time * 24);
        int minutes = (int)((r.time * 24 - hours) * 60);
        int seconds = (int)((((r.time * 24 - hours) * 60) - minutes) * 60);
        out << "T" << (hours < 10 ? "0" : "") << hours << ":" << (minutes < 10 ? "0" : "") << minutes << ":" << (seconds < 10 ? "0" : "") << seconds;
    }
    out << " (" << d_w << ")";
    return out;
};

double Data::operator -(const Data& r) const {
    double d1, d2;

    d1 = day_in_months(day, month, year) + time;
    d2 = day_in_months(r.day, r.month, r.year) + r.time;
    return d1 - d2;
}

double Data::operator -=(const Data& r) {
    Data c(*this);
    double d;
    d = c - r;
    return d;
};

Data Data::operator +(const int a) {
    double num = a;
    day += num;
    int d_in_m[12] = {};
    int  m[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12};
    if ((year % 4 == 0) && (year % 100 != 0)) {
        int d_in_m[] = { 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
    }
    else {
        int d_in_m[] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
    }
    
    while(num != 0){
        for (int i = 0; i < 13; i++) {
            if (m[i] == month) {
                if (day > d_in_m[i]) {
                    day -= d_in_m[i];
                    month++;
                    num -= d_in_m[i];
                    if (month > 12) {
                        year++;
                    }
                }
            }
        }
    }
    return *this;
}

Data Data::operator +=(int a) {
    *this = *this + a;
    return *this;
}

bool Data::operator ==(const Data& r) const {
    return (day_in_months(day, month, year) + time == day_in_months(r.day, r.month, r.year) + r.time);
}

bool Data::operator >(const Data& r) const {
    return (day_in_months(day, month, year) + time > day_in_months(r.day, r.month, r.year) + r.time);
}

bool Data::operator >=(const Data& r) const {
    return (day_in_months(day, month, year) + time >= day_in_months(r.day, r.month, r.year) + r.time);
}

bool Data::operator <(const Data& r) const {
    return (day_in_months(day, month, year) + time < day_in_months(r.day, r.month, r.year) + r.time);
}

bool Data::operator <=(const Data& r) const {
    return (day_in_months(day, month, year) + time <= day_in_months(r.day, r.month, r.year) + r.time);
}

int day_in_months(int d, int m, int y) {
    
    int days_in_month_normal[] = { 0, 31, 59, 90, 120, 151, 181, 212, 243, 273, 304, 334 };
    
    int days_in_month_leap[] = { 0, 31, 60, 91, 121, 152, 182, 213, 244, 274, 305, 335 };

    int* days_in_month;
    if ((y % 4 == 0 && y % 100 != 0) || (y % 400 == 0)) {
        days_in_month = days_in_month_leap;
    }
    else {
        days_in_month = days_in_month_normal;
    }

    int m_d = 0;
    if (m >= 1 && m <= 12) {
        m_d = days_in_month[m - 1];
    }

    int total = d + m_d;

    for (int i = 1; i < y; i++) {
        total += 365;
        if ((i % 4 == 0 && i % 100 != 0) || (i % 400 == 0)) {
            total++;
        }
    }

    return total;
}

int Data::dayOfWeek() {
    return day_in_months(day, month, year) % 7;
}

bool Data::isValid() {
    if (year < 1 || month < 1 || month > 12 || day < 1) {
        return false;
    }

    int days_in_month[] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
    if ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0)) {
        days_in_month[1] = 29;
    }

    if (day > days_in_month[month - 1]) {
        return false;
    }
    if (time < 0 || time >= 1) {
        return false;
    }

    return true;
}

void intDate(const string& date_str, int& day, int& month, int& year, double& time) {
    string year_s, month_s, day_s, time_s;
    int len = date_str.length();
    int cnt_dash = 0;
    bool has_time = false;

    for (int i = 0; i < len; i++) {
        if (date_str[i] == '-') {
            cnt_dash++;
        }
        else if (date_str[i] == 'T' || date_str[i] == 't') {
            has_time = true;
            cnt_dash++;
        }
        else if (cnt_dash == 0) {
            year_s = year_s + date_str[i];
        }
        else if (cnt_dash == 1) {
            month_s = month_s + date_str[i];
        }
        else if (cnt_dash == 2) {
            day_s = day_s + date_str[i];
        }
        else if (cnt_dash == 3) {
            time_s = time_s + date_str[i];
        }
        else if (cnt_dash >= 4) {
            throw Exception();
        }
    }

    year = stoi(year_s);
    month = stoi(month_s);
    day = stoi(day_s);

    time = 0.0;
    if (has_time && !time_s.empty()) {
        int hours = 0, minutes = 0, seconds = 0;
        string h, m, s;
        int cnt_colon = 0;

        for (char c : time_s) {
            if (c == ':') {
                cnt_colon++;
            }
            else if (cnt_colon == 0) {
                h = h + c;
            }
            else if (cnt_colon == 1) {
                m = m + c;
            }
            else if (cnt_colon == 2) {
                s = s + c;
            }
        }

        hours = stoi(h);
        if (!m.empty()) minutes = stoi(m);
        if (!s.empty()) seconds = stoi(s);

        time = hours / 24.0 + minutes / (24.0 * 60.0) + seconds / (24.0 * 3600.0);
    }
}


void moon(int d, int m, int y) {
    struct Record {
        int ymd;
        int hms;
        double t;
        double r;
        double el;      
        double az;
        double fi;
        double lg;
    };
    std::string name_file = "moon" + std::to_string(y) + ".dat";

    ifstream file(name_file);
    if (!file.is_open()) {
        cerr << "Ошибка: не удалось открыть файл " << name_file << endl;
        return;
    }

    vector<Record> records;
    string line;

    getline(file, line);

    while (getline(file, line)) {
        if (line.empty()) continue;
        istringstream iss(line);
        Record rec;
        iss >> rec.ymd >> rec.hms >> rec.t >> rec.r >> rec.el >> rec.az >> rec.fi >> rec.lg;
        records.push_back(rec);
    }
        file.close();
    
        double boof = 0;
        bool rise_found = false;
        bool set_found = false;
        double max_el = -1000;
        int t_data = y * 10000 + m * 100 + d;
        int h_mx = 0, m_mx = 0, s_mx = 0;

        int rise_h = 0, rise_m = 0, rise_s = 0;
        int set_h = 0, set_m = 0, set_s = 0;

        for (int i = 0; i < records.size(); i++) {
            if (records[i].ymd != t_data) continue;

            double el = records[i].el;
            int hms = records[i].hms;
            int h = hms / 10000;
            int min = (hms / 100) % 100;
            int sec = hms % 100;

            if (el > max_el) {
                max_el = el;
                h_mx = h;
                m_mx = min;
                s_mx = sec;
            }

            if (!rise_found && boof < 0 && el >= 0) {
                rise_found = true;
                rise_h = h;
                rise_m = min;
                rise_s = sec;
            }

            if (!set_found && boof > 0 && el <= 0) {
                set_found = true;
                set_h = h;
                set_m = min;
                set_s = sec;
            }
            boof = el;
        }
        
        if (rise_found) {
            cout << "Восход Луны: " << (rise_h < 10 ? "0" : "") << rise_h << ":"
                << (rise_m < 10 ? "0" : "") << rise_m << ":"
                << (rise_s < 10 ? "0" : "") << rise_s << endl;
        }
        else {
            cout << "Восход Луны: ---" << endl;
        }

        cout << "Кульминация Луны: " << (h_mx < 10 ? "0" : "") << h_mx << ":"
            << (m_mx < 10 ? "0" : "") << m_mx << ":"
            << (s_mx < 10 ? "0" : "") << s_mx << endl;

        if (set_found) {
            cout << "Заход Луны: " << (set_h < 10 ? "0" : "") << set_h << ":"
                << (set_m < 10 ? "0" : "") << set_m << ":"
                << (set_s < 10 ? "0" : "") << set_s << endl;
        }
        else {
            cout << "Заход Луны: ---" << endl;
        }

}

void quickSort(Data arr[], int start, int finish) {
    if (start >= finish) return;

    int i = start, j = finish;
    Data pivot = arr[(start + finish) / 2];

    while (i <= j) {
        while (arr[i] < pivot) i++;
        while (pivot < arr[j]) j--;
        if (i <= j) {
            Data temp = arr[i];
            arr[i] = arr[j];
            arr[j] = temp;
            i++;
            j--;
        }
    }

    quickSort(arr, start, j);
    quickSort(arr, i, finish);
}
