#include <vector>
#include <stdio.h>
#include <iostream>
#include <string>

struct Line; // Forward declaration

// Define the ViewDirection enumeration
enum ViewDirection {
    FRONT,
    TOP,
    SIDE,
    UNKNOWN // Optional value to handle unrecognized input
};

struct Point {
    int id;
    int x, y, z;
    std::vector<Line*> lines; // Use pointers to avoid circular dependency
};

struct Line {
    int id;
    Point* start_point; // Use pointers to avoid copying
    Point* end_point;   // Use pointers to avoid copying
    bool is_visible;
};

struct View_2D {
    int id;
    ViewDirection direction;
    std::vector<Point> points;
    std::vector<Line> lines;
};

struct View_3D {
    int id;
    std::vector<Point> points;
    std::vector<Line> lines;
};



// Overload the >> operator for ViewDirection
std::istream& operator>>(std::istream& is, ViewDirection& direction) {
    std::string input;
    is >> input;

    if (input == "FRONT") {
        direction = ViewDirection::FRONT;
    } else if (input == "TOP") {
        direction = ViewDirection::TOP;
    } else if (input == "SIDE") {
        direction = ViewDirection::SIDE;
    } else {
        direction = ViewDirection::UNKNOWN; // Handle unrecognized input
    }

    return is;
};
