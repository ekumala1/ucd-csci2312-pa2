#include <iostream>
#include "pa2check.h"
#include <fstream>
using namespace std;

int main() {
    cout << "Start Point Class Testing" << endl;
    cout << "----------------------------------------------------------------------------" << endl;
    testPointDimCtor();
    cout << "-----------------------------------------------------" << endl;
    testPointDimValuesCtor();
    cout << "-----------------------------------------------------" << endl;
    testPointCopyCtor();
    cout << "-----------------------------------------------------" << endl;
    testPointAssignOper();
    cout << "-----------------------------------------------------" << endl;
    testPointInputOper();
    cout << "-----------------------------------------------------" << endl;
    testPointGetDims();
    cout << "-----------------------------------------------------" << endl;
    testPointSetValue();
    cout << "-----------------------------------------------------" << endl;
    testPointGetValue();
    cout << "-----------------------------------------------------" << endl;
    testPointDistanceTo();
    cout << "-----------------------------------------------------" << endl;
    testPointArithOpers();
    cout << "-----------------------------------------------------" << endl;
    testPointBracketOper();
    cout << "-----------------------------------------------------" << endl;
    testPointConditionOpers();
    cout << "----------------------------------------------------------------------------" << endl;
    cout << "End Point Class Testing" << endl << endl;

    cout << "Start Cluster Class Testing" << endl;
    cout << "----------------------------------------------------------------------------" << endl;
    testClusterCopyAssign();
    cout << "-----------------------------------------------------" << endl;
    testClusterAddRemove();
    cout << "-----------------------------------------------------" << endl;
    testClusterInputOper();
    cout << "-----------------------------------------------------" << endl;
    testClusterConditionalOper();
    cout << "-----------------------------------------------------" << endl;
    testClusterArithOpers();
    cout << "-----------------------------------------------------" << endl;
    testClusterKMeansFuncs();
    cout << "----------------------------------------------------------------------------" << endl;
    cout << "End Cluster Class Testing" << endl << endl;

    cout << "Start KMeans Class Testing" << endl;
    cout << "----------------------------------------------------------------------------" << endl;
    testKMeansResults();
    cout << "----------------------------------------------------------------------------" << endl;
    cout << "End KMeans Class Testing" << endl;

    return 0;
}
