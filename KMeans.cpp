//
// Created by Enoch Kumala on 10/31/2015.
//

#include <cmath>
#include <string>
#include <fstream>
#include "KMeans.h"
#include "Cluster.h"
using namespace std;

namespace Clustering {
    const double KMeans::SCORE_DIFF_THRESHOLD = 1;

    Cluster KMeans::minDistance(Point &point) {
        int minDistance = point.distanceTo(cluster_space[0].getCentroid());
        Cluster minDistanceCluster(dim);

        for (int i=0; i<k; i++) {
            if (minDistance > point.distanceTo(cluster_space[i].getCentroid())) {
                minDistance = point.distanceTo(cluster_space[i].getCentroid());
                minDistanceCluster = cluster_space[i];
            }
        }

        return minDistanceCluster;
    }

    KMeans::KMeans(int newK, int dimensions, string inFile, string outFile) : k(newK), dim(dimensions), point_space(dim) {
        ifstream istream(inFile);
        istream >> point_space;

        PointPtr *centroids = new PointPtr[k];
        cluster_space = new Cluster[k];
        point_space.pickPoints(k, centroids);

        cluster_space[0] = point_space;
        for (int i=0; i<k; i++) {
            cluster_space[i] = Cluster(dim);
            cluster_space[i].setCentroid(*centroids[i]);
        }

        double score, scoreDiff = SCORE_DIFF_THRESHOLD;

        while (scoreDiff >= SCORE_DIFF_THRESHOLD) {
            for (int i=0; i<k; i++) {
                for (int j=0; j<cluster_space[0].getSize(); j++) {
                    Cluster minDistanceCluster = minDistance(cluster_space[i][j]);

                    if (&cluster_space[i] != &minDistanceCluster) {
                        Cluster::Move mover(&cluster_space[i][j], &cluster_space[i], &minDistanceCluster);
                        mover.perform();
                    }
                }

                if (cluster_space[i].centroidValid())
                    cluster_space[i].computeCentroid();
            }

            scoreDiff = abs(computeClusteringScore() - score);

            ofstream ostream(outFile);

            for (int i=0; i<k; i++) {
                ostream << cluster_space[i] << endl;
            }
        }
    }

    double KMeans::computeClusteringScore() {
        double dIn, dOut, pIn, pOut;

        for (int i=0; i<k; i++) {
            dIn += cluster_space[i].intraClusterDistance();
            pIn += cluster_space[i].getClusterEdges();
            for (int j=0; j<k; j++) {
                dOut += interClusterDistance(cluster_space[i], cluster_space[j]);
                pOut += interClusterEdges(cluster_space[i], cluster_space[j]);
            }
        }

        return (dIn / pIn) / (dOut / pOut);
    }
}
