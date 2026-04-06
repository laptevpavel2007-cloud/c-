#include <iostream>

const int DEFAULT_CAPACITY = 10;

class Exception {};

class Array {
private:
	int* ptr;
	int size;
	int capacity;
public:
	explicit Array(int startCapacity = DEFAULT_CAPACITY);
	~Array();
	Array(const Array& arr);

	void insert(int elem, int index);
	void insert(int elem);

	void remove(int index);

	int getSize() const;

	void increaseCapacity(int newCapacity);

	Array& operator =(const Array& arr);

	int& operator[](int index);

	friend std::ostream& operator <<(std::ostream& out, const Array& arr);
};

void f(int k);
int g(int n);

template <class T> const T& getMax(const T& a, const T& b);
