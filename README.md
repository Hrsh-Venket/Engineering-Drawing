# Engineering-Drawing
Engineering Drawing Software for CS-1350 Design Practices in CS.

This software supports taking information from 3 views under regular engineering drawing conventions to reconstruct the object in 3D. 

The input must have 3 views in order: FRONT, TOP, SIDE.

The format for each view is as follows:

view_id FRONT
num_points
point_id x1 y1 z1
point_id x2 y2 z2
...
num_lines
line_id start end is_visible
...

view_id TOP
num_points
point_id x1 y1 z1
point_id x2 y2 z2
...
num_lines
line_id start end is_visible
...

view_id SIDE
num_points
point_id x1 y1 z1
point_id x2 y2 z2
...
num_lines
line_id start end is_visible
...

I have code that checks for these input specifications.

My code currently is able to find all the points in 3D space correctly. It can also find the edges, according to my testing (including hidden and dashed ones) but currently includes a series of additional edges. I suspect this because I have mismanaged pointers in some way.

I have 3 test cases to demonstrate this functionality. The include the basic cube, a pyramid, and an upside down pyramid (due to the inclusion of dashed lines).