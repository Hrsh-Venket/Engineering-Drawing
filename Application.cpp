#include <iostream>
#include <vector>
#include "Structures.h"
#include <stdio.h>
#include <unordered_set>
#include <boost/functional/hash.hpp>

// Exception classes for input errors
class InputException : public std::runtime_error {
public:
    InputException(const std::string& msg) : std::runtime_error(msg) {}
};


void readPoint(Point& p) {
    if (!(std::cin >> p.id >> p.x >> p.y >> p.z)) {
        throw InputException("Invalid point format. Expected: point_id x y z");
    }
}

void readLine(Line& e, std::vector<Point>& points) {
    int start_idx, end_idx;
    if (!(std::cin >> e.id >> start_idx >> end_idx >> e.is_visible)) {
        throw InputException("Invalid line format. Expected: line_id start_point_id end_point_id is_visible");
    }

    if (start_idx <= 0 || start_idx > points.size() || end_idx <= 0 || end_idx > points.size()) {
        throw InputException("Line references an invalid point ID.");
    }

    e.start_point = &points[start_idx - 1];
    e.end_point = &points[end_idx - 1];

    points[start_idx - 1].lines.push_back(&e);
    points[end_idx - 1].lines.push_back(&e);
}

void read2DView(View_2D& view) {
    if (!(std::cin >> view.id >> view.direction)) {
        throw InputException("Invalid view format. Expected: view_id direction");
    }

    if (view.direction == ViewDirection::UNKNOWN) {
        throw InputException("Invalid direction. Must be FRONT, TOP, or SIDE.");
    }

    int num_points, num_edges;
    if (!(std::cin >> num_points) || num_points < 0) {
        throw InputException("Invalid number of points. It must be a non-negative integer.");
    }

    view.points.resize(num_points);
    for (int i = 0; i < num_points; ++i) {
        readPoint(view.points[i]);
    }

    if (!(std::cin >> num_edges) || num_edges < 0) {
        throw InputException("Invalid number of lines. It must be a non-negative integer.");
    }

    view.lines.resize(num_edges);
    for (int i = 0; i < num_edges; ++i) {
        readLine(view.lines[i], view.points);
    }
}

void readOrthViews(View_2D& front, View_2D& top, View_2D& side) {
    try {
        read2DView(front);
        if (front.direction != ViewDirection::FRONT) {
            throw InputException("Expected FRONT direction for the front view.");
        }

        read2DView(top);
        if (top.direction != ViewDirection::TOP) {
            throw InputException("Expected TOP direction for the top view.");
        }

        read2DView(side);
        if (side.direction != ViewDirection::SIDE) {
            throw InputException("Expected SIDE direction for the side view.");
        }
    } catch (const InputException& e) {
        std::cerr << "Error reading view: " << e.what() << std::endl;
        throw;
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
    // std::cout << "View ID: " << view.id << std::endl;

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

View_3D conv2D_to_3D(View_2D& front, View_2D& top, View_2D& side) {
    View_3D view;
    int point_id = 0;

    // Temporary storage for matched 3D points
    std::vector<Point_3D> threeD_points;
    std::unordered_set<std::pair<int, int>, boost::hash<std::pair<int, int>>> line_set;  // To avoid duplicates

    // Step 1: Create 3D points by matching corresponding points across all views
    for (size_t i = 0; i < top.points.size(); ++i) {
        for (size_t j = 0; j < front.points.size(); ++j) {
            for (size_t k = 0; k < side.points.size(); ++k) {
                Point& top_point = top.points[i];
                Point& front_point = front.points[j];
                Point& side_point = side.points[k];

                // Match points based on shared coordinates
                if (top_point.x == front_point.x &&
                    front_point.y == side_point.y &&
                    top_point.z == side_point.z) {

                    Point_3D new_point;
                    new_point.id = point_id++;
                    new_point.x = top_point.x;
                    new_point.y = front_point.y;
                    new_point.z = side_point.z;

                    new_point.front_point = &front_point;
                    new_point.top_point = &top_point;
                    new_point.side_point = &side_point;

                    threeD_points.push_back(new_point);

                    top_point.three_d_points.push_back(&threeD_points.back());
                    front_point.three_d_points.push_back(&threeD_points.back());
                    side_point.three_d_points.push_back(&threeD_points.back());
                }
            }
        }
    }

    // Step 2: Create 3D lines from 2D lines, with printed output of contributing 2D point IDs
    for (size_t p_idx = 0; p_idx < threeD_points.size(); ++p_idx) {
        Point_3D& p3D = threeD_points[p_idx];

        // Check lines in the front view
        for (Line* line : p3D.front_point->lines) {
            Point* other_front = (line->start_point == p3D.front_point) ? line->end_point : line->start_point;

            // Find corresponding 3D point
            Point_3D* other_3D = nullptr;
            for (Point_3D& point : threeD_points) {
                if (other_front->id == point.front_point->id) {
                    other_3D = &point;
                    break;
                }
            }

            if (other_3D) {
                int id1 = std::min(p3D.id, other_3D->id);
                int id2 = std::max(p3D.id, other_3D->id);

                if (line_set.find({id1, id2}) == line_set.end()) {
                    line_set.insert({id1, id2});

                    // USED TO TRY DEBUGGING
                    // std::cout << "3D Line created from FRONT view with Point IDs: "
                    //           << p3D.front_point->id << " - " << other_3D->front_point->id << std::endl;
                }
            }
        }

        // Check lines in the top view
        for (Line* top_line : p3D.top_point->lines) {
            Point* other_top = (top_line->start_point == p3D.top_point) ? top_line->end_point : top_line->start_point;

            Point_3D* other_3D = nullptr;
            for (Point_3D& point : threeD_points) {
                if (other_top->id == point.top_point->id) {
                    other_3D = &point;
                    break;
                }
            }

            if (other_3D) {
                int id1 = std::min(p3D.id, other_3D->id);
                int id2 = std::max(p3D.id, other_3D->id);

                if (line_set.find({id1, id2}) == line_set.end()) {
                    line_set.insert({id1, id2});

                    // USED TO TRY DEBUGGING
                    // std::cout << "3D Line created from TOP view with Point IDs: "
                    //           << p3D.top_point->id << " - " << other_3D->top_point->id << std::endl;
                }
            }
        }

        // Check lines in the side view
        for (Line* side_line : p3D.side_point->lines) {
            Point* other_side = (side_line->start_point == p3D.side_point) ? side_line->end_point : side_line->start_point;

            Point_3D* other_3D = nullptr;
            for (Point_3D& point : threeD_points) {
                if (other_side->id == point.side_point->id) {
                    other_3D = &point;
                    break;
                }
            }

            if (other_3D) {
                int id1 = std::min(p3D.id, other_3D->id);
                int id2 = std::max(p3D.id, other_3D->id);

                if (line_set.find({id1, id2}) == line_set.end()) {
                    line_set.insert({id1, id2});

                    // USED TO TRY DEBUGGING
                    // std::cout << "3D Line created from SIDE view with Point IDs: "
                    //           << p3D.side_point->id << " - " << other_3D->side_point->id << std::endl;
                }
            }
        }
    }

    // Step 3: Construct the 3D view
    for (const auto& p : threeD_points) {
        Point point_2D;
        point_2D.id = p.id;
        point_2D.x = p.x;
        point_2D.y = p.y;
        point_2D.z = p.z;
        view.points.push_back(point_2D);
    }

    for (const auto& line_pair : line_set) {
        int start_id = line_pair.first;
        int end_id = line_pair.second;

        Line line_2D;
        line_2D.id = view.lines.size();
        line_2D.is_visible = true;
        line_2D.start_point = &view.points[start_id];
        line_2D.end_point = &view.points[end_id];

        view.lines.push_back(line_2D);
    }

    return view;
}
 

int main() {
    View_2D front;
    View_2D top;
    View_2D side;

    readOrthViews(front, top, side);
    
    View_3D view_3D = conv2D_to_3D(front, top, side);

    write3DView(view_3D);

    return 0;
}


