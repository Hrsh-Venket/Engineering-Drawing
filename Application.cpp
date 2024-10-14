#include <iostream>
#include <vector>
#include "Structures.h"
#include <stdio.h>
// #include <Eigen/Dense>

void readPoint(Point& p) {
    std::cin >> p.id >> p.x >> p.y >> p.z;
    }

void readLine(Line& e, std::vector<Point>& points) {
    int start_idx, end_idx;
    std::cin >> e.id >> start_idx >> end_idx >> e.is_visible;

    // Convert 1-based index to 0-based
    e.start_point = &points[start_idx - 1];
    e.end_point = &points[end_idx - 1];

    // Update the points' line lists
    points[start_idx - 1].lines.push_back(&e);
    points[end_idx - 1].lines.push_back(&e);
    }

void read2DView(View_2D& view) {
    std::cin >> view.id;
    
    std::cin >> view.direction;

    int num_points, num_edges;

    std::cin >> num_points;

    view.points.resize(num_points);
    for (int i = 0; i < num_points; ++i) {
        readPoint(view.points[i]);
        }

    std::cin >> num_edges;
    view.lines.resize(num_edges);

    for (int i = 0; i < num_edges; ++i) {
        readLine(view.lines[i], view.points);
        }
    }

void read3DView(View_3D& view) {
    std::cin >> view.id;

    int num_points, num_edges;

    std::cin >> num_points;

    view.points.resize(num_points);
    for (int i = 0; i < num_points; ++i) {
        readPoint(view.points[i]);
        }

    std::cin >> num_edges;
    view.lines.resize(num_edges);

    for (int i = 0; i < num_edges; ++i) {
        readLine(view.lines[i], view.points);
        }
    }

void write2DView(const View_2D& view) {
    std::cout << "View ID: " << view.id << std::endl;

    std::cout << "Points:" << std::endl;
    for (const auto& p : view.points) {
        std::cout << "  Point ID: " << p.id << ", Coordinates: (" 
                  << p.x << ", " << p.y << ", " << p.z << ")" << std::endl;
    }

    // Output the lines
    std::cout << "Lines:" << std::endl;
    for (const auto& l : view.lines) {
        std::cout << "  Line ID: " << l.id << ", Start Point ID: " 
                  << l.start_point->id << ", End Point ID: " 
                  << l.end_point->id << ", Is Visible: " 
                  << (l.is_visible ? "Yes" : "No") << std::endl;
    }
}

void write3DView(const View_3D& view) {
    std::cout << "View ID: " << view.id << std::endl;

    std::cout << "Points:" << std::endl;
    for (const auto& p : view.points) {
        std::cout << "  Point ID: " << p.id << ", Coordinates: (" 
                  << p.x << ", " << p.y << ", " << p.z << ")" << std::endl;
    }

    // Output the lines
    std::cout << "Lines:" << std::endl;
    for (const auto& l : view.lines) {
        std::cout << "  Line ID: " << l.id << ", Start Point ID: " 
                  << l.start_point->id << ", End Point ID: " 
                  << l.end_point->id << ", Is Visible: " 
                  << (l.is_visible ? "Yes" : "No") << std::endl;
    }
}

void readOrthViews(View_2D& front, View_2D& top, View_2D& side) {
    read2DView(front);
    read2DView(top);
    read2DView(side);
}

int main() {
    View_2D front;
    View_2D top;
    View_2D side;

    readOrthViews(front, top, side);
`
    return 0;
}
