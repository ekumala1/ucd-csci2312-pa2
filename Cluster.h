//
// Created by Enoch Kumala on 10/31/2015.
//

#ifndef CLUSTERING_CLUSTER_H
#define CLUSTERING_CLUSTER_H

#include <iostream>
#include "Point.h"

namespace Clustering {
    typedef Point *PointPtr;
    typedef struct LNode *LNodePtr;

    struct LNode {
        PointPtr p;
        LNodePtr next;
    };

    class Cluster {
        int size;
        int dimensionality;
        unsigned int __id;
        LNodePtr head;
        Point __centroid;
        bool __centroidValid;
        bool in(const Cluster &, const PointPtr &);

    public:
        static const char POINT_CLUSTER_ID_DELIM;

        Cluster() : size(0), dimensionality(5), __id(generateId()), head(nullptr), __centroid(dimensionality) {};
        Cluster(int dims) : size(0), dimensionality(dims), __id(generateId()), head(nullptr), __centroid(dimensionality) {};

        // The big three: cpy ctor, overloaded operator=, dtor
        Cluster(const Cluster &);
        Cluster &operator=(const Cluster &);
        ~Cluster();

        // Set functions: They allow calling c1.add(c2.remove(p));
        void add(const PointPtr &);
        const PointPtr &remove(const PointPtr &);

        // Overloaded operators

        // IO
        friend std::ostream &operator<<(std::ostream &, const Cluster &);
        friend std::istream &operator>>(std::istream &, Cluster &);

        // Set-preserving operators (do not duplicate points in the space)
        // - Friends
        friend bool operator==(const Cluster &lhs, const Cluster &rhs);


        // - Members
        Cluster &operator+=(const Cluster &rhs); // union
        Cluster &operator-=(const Cluster &rhs); // (asymmetric) difference

        Cluster &operator+=(const PointPtr &rhs); // add point
        Cluster &operator-=(const PointPtr &rhs); // remove point

        // Set-destructive operators (duplicate points in the space)
        // - Friends
        friend const Cluster operator+(const Cluster &lhs, const Cluster &rhs);
        friend const Cluster operator-(const Cluster &lhs, const Cluster &rhs);

        friend const Cluster operator+(const Cluster &lhs, const PointPtr &rhs);
        friend const Cluster operator-(const Cluster &lhs, const PointPtr &rhs);

        int getDims() { return dimensionality; }

        int generateId() {
            static int idGenerator = 0; // to make index start from 1
            return idGenerator++;
        }

        Point &operator[](int index);

        // Centroid operations
        void setCentroid(const Point &centroid) { __centroid = centroid; };
        const Point getCentroid() { return __centroid; };
        void computeCentroid();
        const bool centroidValid() { return __centroidValid; };

        class Move {
            const PointPtr &pointPtr;
            Cluster *fromCluster;
            Cluster *toCluster;
        public:
            Move(const PointPtr &p, Cluster *from, Cluster *to) : pointPtr(p), fromCluster(from), toCluster(to) {};
            void perform() {
                toCluster->add(fromCluster->remove(pointPtr));
                fromCluster->__centroidValid = false;
                toCluster->__centroidValid = false;
            };
        };

        void pickPoints(int, PointPtr *);
        int getSize() { return size; }

        double intraClusterDistance() const;
        friend double interClusterDistance(const Cluster &, const Cluster &);
        int getClusterEdges() { return (size * (size - 1)) / 2; };
        friend double interClusterEdges(const Cluster &c1, const Cluster &c2) { return c1.size * c2.size; };
    };
}

#endif //CLUSTERING_CLUSTER_H
