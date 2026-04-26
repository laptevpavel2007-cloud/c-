#include "shape_class.h"
#include <fstream>
#include <cmath>

using namespace std;

const double PI = acos(-1.0);

Point::Point(int x, int y) {
    this->x = x;
    this->y = y;
}

double len_vector(const Point& coords1, const Point& coords2) {
    return sqrt((coords2.x - coords1.x) * (coords2.x - coords1.x) + (coords2.y - coords1.y) * (coords2.y - coords1.y));
}

Circle::Circle(double r, Point coords) {
    this->r = r;
    this->coords = coords;
}
void Circle::name() {
    cout << "Circle" << endl;
}
double Circle::calc_area() {
    return PI * r * r; 
}
double Circle::calc_perimetr() {
    return 2 * PI * r; 
}

Ellipse::Ellipse(double r1, double r2, Point coords) {
    this->r1 = r1;
    this->r2 = r2;
    this->coords = coords;
}
void Ellipse::name() {
    cout << "Ellipse" << endl;
}
double Ellipse::calc_area() {
    return PI * r1 * r2; 
}
double Ellipse::calc_perimetr() {
    return PI * sqrt(2 * (r1 * r1 + r2 * r2));
}

Triangle::Triangle(Point coords1, Point coords2, Point coords3) {
    this->coords1 = coords1;
    this->coords2 = coords2;
    this->coords3 = coords3;
    use_sides = false;
}
Triangle::Triangle(double a, double b, double c) {
    side_a = a; side_b = b; side_c = c;
    use_sides = true;
}
void Triangle::name() {
    cout << "Triangle" << endl;
}
double Triangle::calc_perimetr() {
    if (use_sides) {
        return side_a + side_b + side_c; 
    }
    else {
        double a = len_vector(coords1, coords2);
        double b = len_vector(coords2, coords3);
        double c = len_vector(coords3, coords1);
        return a + b + c;
    }
}
double Triangle::calc_area() {
    if (use_sides) {
        double p = (side_a + side_b + side_c) / 2.0;
        return sqrt(p * (p - side_a) * (p - side_b) * (p - side_c));
    }
    else {
        double a = len_vector(coords1, coords2);
        double b = len_vector(coords2, coords3);
        double c = len_vector(coords3, coords1);
        double p = (a + b + c) / 2.0;
        return sqrt(p * (p - a) * (p - b) * (p - c));
    }
}

Rectangle::Rectangle(Point coords1, Point coords2, Point coords3, Point coords4) {
    this->coords1 = coords1;
    this->coords2 = coords2;
    this->coords3 = coords3;
    this->coords4 = coords4;
    use_sides = false;
}
Rectangle::Rectangle(double w, double h) {
    width = w; height = h;
    use_sides = true;
}
void Rectangle::name() { 
    cout << "Rectangle" << endl;
}
double Rectangle::calc_perimetr() {
    if (use_sides) {
        return 2 * (width + height);
    }
    else {
        double s1 = len_vector(coords1, coords2);
        double s2 = len_vector(coords2, coords3);
        double s3 = len_vector(coords3, coords4);
        double s4 = len_vector(coords4, coords1);
        return s1 + s2 + s3 + s4;
    }
}
double Rectangle::calc_area() {
    if (use_sides) {
        return width * height;
    }
    else {
        double w = len_vector(coords1, coords2);
        double h = len_vector(coords2, coords3);
        return w * h;
    }
}

Polygon::Polygon(const vector<Point>& pts) : vertices(pts) {}
Polygon::Polygon(const char* filename) {
    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "Can't open file: " << filename << endl;
        return;
    }
    int x, y;
    while (file >> x >> y) {
        vertices.push_back(Point(x, y));
    }
    file.close();
}
void Polygon::name() { 
    cout << "Polygon" << endl;
}
double Polygon::calc_perimetr() {
    double per = 0;
    for (size_t i = 0; i < vertices.size(); ++i) {
        per += len_vector(vertices[i], vertices[(i + 1) % vertices.size()]);
    }
    return per;
}
double Polygon::calc_area() {
    double area = 0;
    int n = vertices.size();
    for (int i = 0; i < n; ++i) {
        int j = (i + 1) % n;
        area += vertices[i].x * vertices[j].y;
        area -= vertices[j].x * vertices[i].y;
    }
    return fabs(area) / 2.0;
}


bool isShapePixel(char c) {
    return c == '1';
}

bool isRectangle(const vector<Point>& contour) {
    int minX = 1000, maxX = -1, minY = 1000, maxY = -1;
    for (const auto& p : contour) {
        if (p.x < minX) minX = p.x;
        if (p.x > maxX) maxX = p.x;
        if (p.y < minY) minY = p.y;
        if (p.y > maxY) maxY = p.y;
    }
    double w = maxX - minX;
    double h = maxY - minY;
    if (w < 2 || h < 2) {
        return false;
    }
    else {
        double area = contour.size();
        double expectedArea = w * h;
        return (area / expectedArea) > 0.75;
    }
}

bool isCircle(const vector<Point>& contour) {
    if (contour.size() < 10) {
        return false;
    }
    double cx = 0, cy = 0;
    for (const auto& p : contour) {
        cx += p.x;
        cy += p.y;
    }
    cx /= contour.size();
    cy /= contour.size();
    double avgR = 0;
    for (const auto& p : contour) {
        avgR += hypot(p.x - cx, p.y - cy);
    }
    avgR /= contour.size();
    if (avgR < 1.0) {
        return false; 
    }
    double dev = 0;
    for (const auto& p : contour) {
        double r = hypot(p.x - cx, p.y - cy);
        dev += fabs(r - avgR);
    }
    dev /= contour.size();
    double ratio = dev / avgR;
    return ratio < 0.28;
}

bool isTriangle(const vector<Point>& contour) {
    int minX = 1000, maxX = -1, minY = 1000, maxY = -1;
    for (const auto& p : contour) {
        if (p.x < minX) minX = p.x;
        if (p.x > maxX) maxX = p.x;
        if (p.y < minY) minY = p.y;
        if (p.y > maxY) maxY = p.y;
    }
    double w = maxX - minX;
    double h = maxY - minY;
    if (w < 2 || h < 2) {
        return false;
    }
    else {
        double area = contour.size();
        double expectedArea = (w * h) / 2.0;
        return (area / expectedArea) > 0.7 && (area / expectedArea) < 1.3;
    }
}