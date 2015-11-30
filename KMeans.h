//
// Created by Enoch Kumala on 10/31/2015.
//

#ifndef UCD_CSCI2312_PA2_KMEANS_H
#define UCD_CSCI2312_PA2_KMEANS_H

#include "Cluster.h"
using namespace std;

namespace Clustering {
    typedef Cluster *ClusterPtr;

    class KMeans {
        unsigned int k;
        unsigned int dim;
        Cluster point_space;
        ClusterPtr cluster_space;
        Cluster minDistance(Point &);
    public:
        KMeans(int newK, int dimensions, string inFile, string outFile);
        static const double SCORE_DIFF_THRESHOLD;
        double computeClusteringScore();
    };
}

#endif //UCD_CSCI2312_PA2_KMEANS_H
