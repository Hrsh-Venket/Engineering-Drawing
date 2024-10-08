#include <stdio.h>
#include <vector>
#include "Structures.h"

// int main() {
//     Point temp;

//     temp.id = 1;
//     temp.x = 2;
//     temp.y = 3;

//     Line temp_line;

//     temp_line.id = 1;
//     temp_line.start = temp;
//     temp_line.end.x = 1;
//     temp_line.end.y = 2;
//     temp_line.end.id = 2;

//     // Print temp_line.end.y
//     printf("temp_line.end.y = %d\n", temp_line.end.y);

//     // You can also print other members if needed
//     printf("temp_line.start.x = %d\n", temp_line.start.x);
//     printf("temp_line.start.y = %d\n", temp_line.start.y);

//     return 0;
// }


int main() {
    int num_points, num_edges;
    std::cin >> num_points;

    std::vector<Point> points(num_points);
    for (int i = 0; i < num_points; ++i) {
        Point& p = points[i];
        std::cin >> p.id >> p.x >> p.y >> p.z;
    }

    std::cin >> num_edges;

    std::vector<Line> lines(num_edges);
    for (int i = 0; i < num_edges; ++i) {
        Line& e = lines[i];
        std::cin >> e.id >> e.start >> e.end >> e.is_visible;

        // Update the points' line lists
        points[e.start - 1].lines.push_back(e.id);
        points[e.end - 1].lines.push_back(e.id);
    }

    // Now you can use the 'points' and 'lines' vectors as needed
    // For example, you can access the coordinates of a point like this:
    // int x_coord = points[0].x;

    return 0;
}

