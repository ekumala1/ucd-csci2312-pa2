# ucd-csci2312-pa2

# Point class
The Point class is a class that represent points of any number of dimensions (e.g. (1, 2), (1, 2, 4), (2, 3, ..., 5, 6), etc.)  The operators ==, !=, <, >, <=, and >= are overloaded to support comparison of the points.  The points are compared in a lexicographic order, which means that the smallest dimension is compared first.  The arithmetic operators (+, -, *, /, +=. -=, *= and /=) are also overloaded.  The points are performed arithmetic on in a dimension-wise way.

# Cluster class
The Cluster class is a class that holds Point objects using a linked list.  It keeps all Points sorted in the lexicographic order explained previously.  The operator + is overloaded to find the union of 2 clusters.  The - operator is used to find which points are in the left hand Cluster that are not in the right hand cluster.  There are add and remove functions to add and remove a Point object, respectively.

# Compiler
I use CMake as the compiler for this assignment.