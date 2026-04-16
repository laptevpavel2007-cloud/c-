#include <iostream>
#include <string>

using namespace std;

class Exception {};

class Data {
private:

public:
    int day;
    int month;
    int year;
    double time;

    Data(int d = 1, int m = 1, int y = 1, double t = 0.0);

    double operator -(const Data& r) const;
    double operator -=(const Data& r);
    Data operator +(int a);
    Data operator +=(int a);

    bool operator ==(const Data& r) const;
    bool operator >(const Data& r) const;
    bool operator <(const Data& r) const;
    bool operator >=(const Data& r) const;
    bool operator <=(const Data& r) const;

    bool isValid();
    int dayOfWeek();

    friend istream& operator >>(istream& in, Data& r);
    friend ostream& operator <<(ostream& out, const Data& r);
};

int day_in_months(int d, int m, int y);
void intDate(const string& date_str, int& day, int& month, int& year, double& time);
void moon(int d, int m, int y);

void quickSort(Data arr[], int left, int right);