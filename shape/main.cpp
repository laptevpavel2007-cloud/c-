#include <iostream>
#include <vector>
#include <fstream>
#include "shape_class.h"

using namespace std;

const int MIN_PIXELS = 30;
const double M_PI = 3.14;

int main() {
    int totalRect = 0, totalCircle = 0, totalTriangle = 0, totalNoise = 0;
    double totalRectArea = 0, totalCircleArea = 0, totalTriangleArea = 0;

    const int dx8[] = { -1,-1,-1,0,0,1,1,1 };
    const int dy8[] = { -1,0,1,-1,1,-1,0,1 };

    for (int fileIdx = 1; fileIdx <= 3; ++fileIdx) {
        string filename = "input" + to_string(fileIdx) + ".dat";
        ifstream fin(filename);
        if (!fin.is_open()) {
            cerr << "Can't open " << filename << endl;
            return 1;
        }

        vector<string> grid(200);
        for (int i = 0; i < 200; ++i) {
            getline(fin, grid[i]);
            if (grid[i].size() < 200)
                grid[i].append(200 - grid[i].size(), ' ');
        }
        fin.close();

        vector<vector<bool>> visited(200, vector<bool>(200, false));
        int rectCount = 0, circleCount = 0, triangleCount = 0, noiseCount = 0;
        double rectArea = 0, circleArea = 0, triangleArea = 0;

        for (int y = 0; y < 200; ++y) {
            for (int x = 0; x < 200; ++x) {
                if (isShapePixel(grid[y][x]) && !visited[y][x]) {

                    vector<Point> frontier;
                    frontier.push_back(Point(x, y));
                    visited[y][x] = true;
                    size_t head = 0;
                    vector<Point> contour;

                    while (head < frontier.size()) {
                        Point p = frontier[head++];
                        contour.push_back(p);
                        for (int d = 0; d < 8; ++d) {
                            int nx = p.x + dx8[d];
                            int ny = p.y + dy8[d];
                            if (nx >= 0 && nx < 200 && ny >= 0 && ny < 200 &&
                                isShapePixel(grid[ny][nx]) && !visited[ny][nx]) {
                                visited[ny][nx] = true;
                                frontier.push_back(Point(nx, ny));
                            }
                        }
                    }

                    if ((int)contour.size() < MIN_PIXELS) {
                        noiseCount++;
                        continue;
                    }

                    if (isCircle(contour)) {
                        circleCount++;
                        double cx = 0, cy = 0;
                        for (auto& p : contour) {
                            cx += p.x;
                            cy += p.y;
                        }
                        cx /= contour.size();
                        cy /= contour.size();
                        double avgR = 0;
                        for (auto& p : contour) {
                            avgR += hypot(p.x - cx, p.y - cy);
                        }
                        avgR /= contour.size();
                        circleArea += M_PI * avgR * avgR;
                    }
                    else if (isRectangle(contour)) {
                        rectCount++;
                        int minX = 200, maxX = 0, minY = 200, maxY = 0;
                        for (auto& p : contour) {
                            if (p.x < minX) minX = p.x;
                            if (p.x > maxX) maxX = p.x;
                            if (p.y < minY) minY = p.y;
                            if (p.y > maxY) maxY = p.y;
                        }
                        rectArea += (maxX - minX) * (maxY - minY);
                    }
                    else if (isTriangle(contour)) {
                        triangleCount++;
                        int minX = 200, maxX = 0, minY = 200, maxY = 0;
                        for (auto& p : contour) {
                            if (p.x < minX) minX = p.x;
                            if (p.x > maxX) maxX = p.x;
                            if (p.y < minY) minY = p.y;
                            if (p.y > maxY) maxY = p.y;
                        }
                        triangleArea += ((maxX - minX) * (maxY - minY)) / 2.0;
                    }
                    else {
                        noiseCount++;
                    }
                }
            }
        }

        totalRect += rectCount;
        totalCircle += circleCount;
        totalTriangle += triangleCount;
        totalNoise += noiseCount;
        totalRectArea += rectArea;
        totalCircleArea += circleArea;
        totalTriangleArea += triangleArea;
    }

    cout << "Rectangle = " << totalRect << endl;
    cout << "Circle = " << totalCircle << endl;
    cout << "Triangle = " << totalTriangle << endl;
    cout << "Noise = " << totalNoise << endl;
    cout << "Total rectangle area = " << totalRectArea << endl;
    cout << "Total circle area = " << totalCircleArea << endl;
    cout << "Total triangle area = " << totalTriangleArea << endl;

    return 0;
}