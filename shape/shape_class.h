#pragma once
#include <iostream>
#include <string>
#include <cmath>
#include <vector>

using namespace std;

class Point {
public:
    int x, y;
    Point(int x = 0, int y = 0);
};

double len_vector(const Point& coords1, const Point& coords2);

class Figure {
public:
    virtual void name() = 0;
    virtual double calc_area() = 0;
    virtual double calc_perimetr() = 0;
    virtual ~Figure() {}
};

class Circle : public Figure {
private:
    Point coords;
    double r;
public:
    Circle(double r, Point coords);
    void name();
    double calc_area();
    double calc_perimetr();
};

class Ellipse : public Figure {
private:
    Point coords;
    double r1, r2;
public:
    Ellipse(double r1, double r2, Point coords);
    void name();
    double calc_area();
    double calc_perimetr();
};

class Triangle : public Figure {
private:
    Point coords1, coords2, coords3;
    double side_a, side_b, side_c;
    bool use_sides;
public:
    Triangle(Point coords1, Point coords2, Point coords3);
    Triangle(double a, double b, double c);
    void name();
    double calc_area();
    double calc_perimetr();
};

class Rectangle : public Figure {
private:
    Point coords1, coords2, coords3, coords4;
    double width, height;
    bool use_sides;
public:
    Rectangle(Point coords1, Point coords2, Point coords3, Point coords4);
    Rectangle(double w, double h);
    void name();
    double calc_area();
    double calc_perimetr();
};

class Polygon : public Figure {
private:
    vector<Point> vertices;
public:
    Polygon(const vector<Point>& pts);
    Polygon(const char* filename);
    void name();
    double calc_area();
    double calc_perimetr();
};

bool isShapePixel(char c);
bool isRectangle(const vector<Point>& contour);
bool isCircle(const vector<Point>& contour);
bool isTriangle(const vector<Point>& contour);