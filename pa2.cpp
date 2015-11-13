#include <iostream>
#include "pa2check.h"
#include <fstream>
using namespace std;

int main() {
    cout << "Start Point Class Testing" << endl;
    cout << "----------------------------------------------------------------------------" << endl;
    testPointDimCtor();
    testPointDimValuesCtor();
    testPointCopyCtor();
    testPointAssignOper();
    testPointInputOper();
    testPointGetDims();
    testPointSetValue();
    testPointGetValue();
    testPointDistanceTo();
    testPointArithOpers();
    testPointBracketOper();
    testPointConditionOpers();
    cout << "----------------------------------------------------------------------------" << endl;
    cout << "End Point Class Testing" << endl << endl;

    cout << "Start Cluster Class Testing" << endl;
    cout << "----------------------------------------------------------------------------" << endl;
    /* testClusterDefaultCtor();
    testClusterCopyAssign();
    testClusterAddRemove();
    testClusterConditionalOper();
    testClusterArithOpers(); */
    cout << "----------------------------------------------------------------------------" << endl;
    cout << "End Cluster Class Testing" << endl << endl;

    cout << "Start KMeans Class Testing" << endl;
    cout << "----------------------------------------------------------------------------" << endl;

    cout << "----------------------------------------------------------------------------" << endl;
    cout << "End KMeans Class Testing" << endl;

    return 0;
}
