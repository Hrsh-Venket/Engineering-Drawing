#include <vector>
#include <stdio.h>

struct Point {
    int id;
    int x, y, z;
    std::vector<Line> lines;
};

struct Line {
    int id;
    Point start_point, end_point;
    bool is_visible;
};

struct View_2D {
    int id;
    std::vector<Point> points;
    std::vector<Line> lines;
};

struct View_3D {
    int id;
    std::vector<Point> points;
    std::vector<Line> lines_3d;
};