#include <cassert>
#include <sstream>
#include <fstream>
#include "Point.h"
#include "Cluster.h"
#include "KMeans.h"
using namespace std;
using namespace Clustering;

int dim = 3;
double p1[] = {3, 4, 5};
double p2[] = {1, 2, 3};
double p3[] = {-1, 2, 3};
double p4[] = {-1, 1, 3};
double p5[] = {-1, 1, 2};

// Point tests
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
    std::string data = "00002.3  ,  5.6   ,   0,  5.6  ,  7.9";
    std::stringstream stream(data);
    Point point(5);

    cout << "string data: " << data << endl;
    stream >> point;
    cout << "Point read in from data string: " << point << endl;
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
    cout << point << "'s 1st dimension using getValue is: " << point.getValue(1) << endl;
}

void testPointDistanceTo() {
    Point point1(dim, p1), point2(dim, p2);
    cout << point1 << " is " << point1.distanceTo(point2) << " units away from " << point2 << "." << endl;
}

void testPointArithOpers() {
    Point point1(dim, p1), point2(dim, p2);
    cout << "Original: " << point1 << endl;
    point1 *= 2;
    cout << "Multiplied by 2 with *=: " << point1 << endl;
    point1 /= 2;
    cout << "Divided back by 2 with /=: " << point1 << endl;
    point1 += point2;
    cout << "Added " << point2 << " with +=: " << point1 << endl;
    point1 -= point2;
    cout << "Subtracted " << point2 << " back with -=: " << point1 << endl;


    Point point3(point1 * 2), point4(point3 / 2), point5(point4 + point2), point6(point5 - point2);
    cout << "Original: " << point1 << endl;
    cout << "Multiplied by 2 with *: " << point3 << endl;
    cout << "Divided back by 2 with /: " << point4 << endl;
    cout << "Added " << point2 << " with +: " << point5 << endl;
    cout << "Subtracted " << point2 << " back with -: " << point6 << endl;
}

void testPointBracketOper() {
    Point point(dim, p1);
    cout << point << "'s 1st dimension using [] operator: " << point[1] << endl;
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

// Cluster tests

void testClusterCopyAssign() {
    Point point1(dim, p1), point2(dim, p2);
    Cluster cluster(3);
    cluster.add(&point1);
    cluster.add(&point2);

    Cluster c1(cluster);
    cout << "Copied using copy constructor: " << endl << c1;
    Cluster c2 = cluster;
    cout << "Copied using assignment oper: " << endl << c2;
}

void testClusterAddRemove() {
    Point point1(dim, p1), point2(dim, p2), point3(dim, p3), point4(dim, p4), point5(dim, p5);
    Cluster cluster(10);
    cluster.add(&point1);
    cluster.add(&point5);
    cluster.add(&point3);
    cluster.add(&point2);
    cluster.add(&point4);
    cout << "Cluster filled up by add(): " << endl << cluster;

    cluster.remove(&point1);
    cout << point1 << " removed using remove(): " << endl << cluster;
}

void testClusterInputOper() {
    Cluster cluster(5);
    ifstream stream("points.txt");
    stream >> cluster;

    cout << "Cluster read in from data string:" << endl << cluster << endl;
}

void testClusterConditionalOper() {
    Point point(dim, p1);
    Cluster c1(dim);
    c1.add(&point);
    Cluster c2(dim);
    c2.add(&point);
    assert(c1 == c2);
    cout << "== operator works!" << endl;
}

void testClusterArithOpers() {
    Point point1(dim, p1), point2(dim, p2), point3(dim, p3), point4(dim, p4);
    Cluster cluster1(dim), cluster2(dim), cluster3(dim);
    cluster1.add(&point1);
    cluster1.add(&point4);
    cluster2.add(&point2);
    cluster3.add(&point3);

    cout << "Original cluster1: " << cluster1;
    cout << "Original cluster2: " << cluster2;
    cout << "Original cluster3: " << cluster3;

    cluster1 += cluster2;
    cout << "cluster1 += cluster2: " << cluster1;
    cluster1 -= cluster2;
    cout << "cluster1 -= cluster2: " << cluster1;
    cluster1 -= cluster3;
    cout << "cluster1 -= cluster3: " << cluster1;

    cout << "cluster1 + cluster2: " << cluster1 + cluster2;
    cout << "cluster1 - cluster2: " << cluster1 - cluster2;
    cout << "cluster1 - cluster3: " << cluster1 - cluster3;

    cluster1 += &point2;
    cout << "cluster1 += point2: " << cluster1;
    cluster1 -= &point2;
    cout << "cluster1 -= point2: " << cluster1;
    cluster1 -= &point3;
    cout << "cluster1 -= point3: " << cluster1;

    cout << "cluster1 + point2: " << cluster1 + &point2;
    cout << "cluster1 - point2: " << cluster1 - &point2;
    cout << "cluster1 - point3: " << cluster1 - &point3;
}

void testClusterKMeansFuncs() {
    Point point1(dim, p1), point2(dim, p2), point3(dim, p3), point4(dim, p4);
    Cluster cluster1(dim), cluster2(dim);
    cluster1.add(&point1);
    cluster1.add(&point2);
    cluster2.add(&point3);
    cluster2.add(&point4);

    cout << "Original cluster1:" << endl;
    cout << cluster1;

    cout << "Original cluster2:" << endl;
    cout << cluster2;

    cout << "cluster1 intraClusterDistance() returns " << cluster1.intraClusterDistance() << endl;
    cout << "cluster1 interClusterDistance(cluster2) returns " << interClusterDistance(cluster1, cluster2) << endl;

    cout << "cluster1 getClusterEdges() returns " << cluster1.getClusterEdges() << endl;
    cout << "cluster1 interClusterEdges(cluster1, cluster2) returns " << interClusterEdges(cluster1, cluster2) << endl;
}

void testKMeansResults() {
    KMeans kMeans(4, 5, "points.txt", "kMeans.txt");
}
