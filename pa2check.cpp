#include <cassert>
#include <fstream>
#include <sstream>
#include "pa2check.h"
#include "Point.h"
#include "Cluster.h"
using namespace std;
using namespace Clustering;

int dim = 3;
double p1[] = {3, 4, 5};
double p2[] = {1, 2, 3};
double p3[] = {-1, 2, 3};
double p4[] = {-1, 1, 3};
double p5[] = {-1, 1, 2};

void testPointDimCtor() {
    Point point(dim);
    cout << "Created by dim constructor: " << point << endl;
}

void testPointDimValuesCtor() {
    Point point(dim, p1);
    cout << "Created by dim and values constructor: " << point << endl;
}

void testPointCopyCtor() {
    Point point(dim, p1), copy(point);
    cout << "Copied using copy constructor: " << copy << endl;
}

void testPointAssignOper() {
    Point point(dim, p1), copy=point;
    cout << "Copied using = operator: " << copy << endl;
}

void testPointInputOper() {
    cout << "Reading in Point with dimension 5 from points.txt..." << endl;
    Point point(5);
//    ifstream stream("points.txt");
    std::string data =  {"4.5, 6.7, 2.3, 0, 1"};
    std::stringstream stream(data);
    stream >> point;

    cout << "Point read in from points.txt: " << point << endl;
}

void testPointGetDims() {
    Point point(dim);
    assert(point.getDims() == dim);

    cout << "getDims() function returns Point dimension." << endl;
}

void testPointSetValue() {
    Point point(dim, p1);
    cout << "Before: " << point << endl;
    point.setValue(1, 5);
    cout << "After: " << point << endl;
}

void testPointGetValue() {
    Point point(dim, p1);
    cout << "(3, 4, 5)'s 1st dimension using getValue is: " << point.getValue(1) << endl;
}

void testPointDistanceTo() {
    Point point1(dim, p1), point2(dim, p2);
    cout << "(3, 4, 5) is " << point1.distanceTo(point2) << " units away from (1, 2, 3)." << endl;
}

void testPointArithOpers() {
    Point point1(dim, p1), point2(dim, p2);
    cout << "Original: " << point1 << endl;
    point1 *= 2;
    cout << "Multiplied by 2 with *=: " << point1 << endl;
    point1 /= 2;
    cout << "Divided back by 2 with /=: " << point1 << endl;
    point1 += point2;
    cout << "Added (1, 2, 3) with +=: " << point1 << endl;
    point1 -= point2;
    cout << "Subtracted (1, 2, 3) back with -=: " << point1 << endl;


    Point point3(point1 * 2), point4(point3 / 2), point5(point4 + point2), point6(point5 - point2);
    cout << "Original: " << point1 << endl;
    cout << "Multiplied by 2 with *: " << point3 << endl;
    cout << "Divided back by 2 with /: " << point4 << endl;
    cout << "Added (1, 2, 3) with +: " << point5 << endl;
    cout << "Subtracted (1, 2, 3) back with -: " << point6 << endl;
}

void testPointBracketOper() {
    Point point(dim, p1);
    cout << "(3, 4, 5)'s 1st dimension using [] operator: " << point[1] << endl;
}

void testPointConditionOpers() {
    Point point1(dim, p1), point2(dim, p2), point3(dim, p3), point4(dim, p4), point5(dim, p5);
    assert(point1 > point2);
    assert(point2 > point3);
    assert(point3 > point4);
    assert(point4 > point5);
    // since the other operators use the same logic as the > operator, they would work too.

    cout << "Conditional operators work!" << endl;
}

/* void testClusterDefaultCtor() {
    Cluster cluster;
    cout << "Cluster produced with default constructor: " << cluster << endl;
}

void testClusterCopyAssign() {
    Point point1(dim, p1), point2(dim, p2);
    Cluster cluster;
    cluster.add(&point1);
    cluster.add(&point2);
    cout << "Original cluster: " << cluster << endl;

    Cluster c1(cluster);
    cout << "Copy using copy ctor: " << c1 << endl;
    Cluster c2 = cluster;
    cout << "Copy using assignment oper: " << c2 << endl;
}

void testClusterAddRemove() {
    Point point1(dim, p1), point2(dim, p2), point3(dim, p3), point4(dim, p4), point5(dim, p5);
    Cluster cluster;
    cluster.add(&point1);
    cout << "Added " << point1 << ", now " << cluster << endl;
    cluster.add(&point3);
    cout << "Added " << point3 << ", now " << cluster << endl;
    cluster.add(&point5);
    cout << "Added " << point5 << ", now " << cluster << endl;
    cluster.add(&point2);
    cout << "Added " << point2 << ", now " << cluster << endl;
    cluster.add(&point4);
    cout << "Cluster filled up by add(): " << cluster << endl;

    cluster.remove(&point1);
    cout << "(3, 4, 5) removed using remove(): " << cluster << endl;
}

void testClusterConditionalOper() {
    Point point(dim, p1);
    Cluster c1;
    c1.add(&point);
    Cluster c2;
    c2.add(&point);
    assert(c1 == c2);
    cout << "== operator works!" << endl;
}

void testClusterArithOpers() {
    Point point1(dim, p1), point2(dim, p2), point3(dim, p3), point4(dim, p4);
    Cluster cluster1, cluster2, cluster3;
    cluster1.add(&point1);
    cluster1.add(&point4);
    cluster2.add(&point2);
    cluster3.add(&point3);

    cout << "Original cluster1: " << cluster1 << endl;
    cout << "Original cluster2: " << cluster2 << endl;
    cout << "Original cluster3: " << cluster3 << endl;

    cluster1 += cluster2;
    cout << "cluster1 += cluster2: " << cluster1 << endl;
    cluster1 -= cluster2;
    cout << "cluster1 -= cluster2: " << cluster1 << endl;
    cluster1 -= cluster3;
    cout << "cluster1 -= cluster3: " << cluster1 << endl;

    cout << "cluster1 + cluster2: " << cluster1 + cluster2 << endl;
    cout << "cluster1 - cluster2: " << cluster1 - cluster2 << endl;
    cout << "cluster1 - cluster3: " << cluster1 - cluster3 << endl;

    cluster1 += &point2;
    cout << "cluster1 += point2: " << cluster1 << endl;
    cluster1 -= &point2;
    cout << "cluster1 -= point2: " << cluster1 << endl;
    cluster1 -= &point3;
    cout << "cluster1 -= point3: " << cluster1 << endl;

    cout << "cluster1 + point2: " << cluster1 + &point2 << endl;
    cout << "cluster1 - point2: " << cluster1 - &point2 << endl;
    cout << "cluster1 - point3: " << cluster1 - &point3 << endl;
} */
