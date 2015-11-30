//
// Created by Enoch Kumala on 10/31/2015.
//

#include <sstream>
#include "Point.h"
#include "Cluster.h"
using namespace std;

namespace Clustering {
    bool Cluster::in(const Cluster &cluster, const PointPtr &pointPtr) {
        LNodePtr lNodePtr = cluster.head;
        bool in = false;

        while (lNodePtr != nullptr) {
            if (lNodePtr->p == pointPtr)
                in = true;

            lNodePtr = lNodePtr->next;
        }
        return in;
    }

    Cluster::Cluster(const Cluster &cluster) : __centroid(cluster.__centroid) {
        __centroid = cluster.__centroid;
        size = 0;
        dimensionality = cluster.dimensionality;
        __id = generateId();

        LNodePtr clusterPtr = cluster.head;

        while (clusterPtr != nullptr) {
            add(clusterPtr->p);
            clusterPtr = clusterPtr->next;
        }
    }

    Cluster &Cluster::operator=(const Cluster &cluster) {
        size = 0;
        dimensionality = cluster.dimensionality;
        __centroid = cluster.__centroid;

        LNodePtr thisPtr = new LNode, clusterPtr = cluster.head;
        thisPtr->p = clusterPtr->p;

        while (clusterPtr != nullptr) {
            add(clusterPtr->p);
            clusterPtr = clusterPtr->next;
        }
        return *this;
    }

    Cluster::~Cluster() {
        LNodePtr current=head, cursor=head;

        while (current != nullptr) {
            cursor = cursor->next;
            delete current;
            current = cursor;
        }

        size = 0;
    }

    void Cluster::add(const PointPtr &pointPtr) {
        if (size == 0) {
            head = new LNode;
            head->p = pointPtr;
            head->next = nullptr;
        } else {
            LNodePtr prevPtr, addPtr=new LNode, currPtr=head, nextPtr;
            addPtr->p = pointPtr;

            while (currPtr != nullptr && *(currPtr->p) < *pointPtr) {
                prevPtr = currPtr;
                currPtr = currPtr->next;
            }

            if (currPtr == head) { // if insert position is at beginning of list
                head = addPtr;
                addPtr->next = currPtr;
            } else if (currPtr == nullptr) { // if insert position is at end of list
                prevPtr->next = addPtr;
                addPtr->next = nullptr;
            } else { // if insert position is in middle of list
                nextPtr = currPtr;
                prevPtr->next = addPtr;
                addPtr->next = nextPtr;
            }
        }

        size++;
        __centroidValid = false;
    }

    const PointPtr &Cluster::remove(const PointPtr &pointPtr) {
        if (size != 0) {
            if (in(*this, pointPtr)) {
                LNodePtr prevPtr, currPtr = head;

                while (currPtr != nullptr && currPtr->p != pointPtr) {
                    prevPtr = currPtr;
                    currPtr = currPtr->next;
                }

                if (currPtr == head)// if delete position is at beginning of list
                    head = currPtr->next;
                else if (currPtr == nullptr) // if delete position is at end of list
                    prevPtr->next = nullptr;
                else // if delete position is in middle of list
                    prevPtr->next = currPtr->next;

                size--;
            }
        }

        __centroidValid = false;
        return pointPtr;
    }

    ostream &operator<<(ostream &stream, const Cluster &cluster) {
        const char POINT_CLUSTER_ID_DELIM = ':';
        LNodePtr lNodePtr = cluster.head;

        if (cluster.size != 0) {
            while (lNodePtr != nullptr) {
                stream << *(lNodePtr->p) << " " << POINT_CLUSTER_ID_DELIM << " " << cluster.__id << endl;
                lNodePtr = lNodePtr->next;
            }
        }

        return stream;
    }

    istream &operator>>(istream &stream, Cluster &cluster) {
        string line;

        while (getline(stream, line)) {
            stringstream sstream(line);
            Point *point = new Point(count(line.begin(), line.end(), Point::POINT_VALUE_DELIM) + 1);
            sstream >> *point;

            cluster.add(point);
        }

        return stream;
    }

    bool operator==(const Cluster &lhs, const Cluster &rhs) {
        LNodePtr lhsPtr = lhs.head, rhsPtr = rhs.head;

        if (lhs.size != rhs.size)
            return false;

        while (lhsPtr->next != nullptr && rhsPtr->next != nullptr) {
            if (*(lhsPtr->p) != *(rhsPtr->p))
                return false;

            lhsPtr = lhsPtr->next;
            rhsPtr = rhsPtr->next;
        }

        return true;
    }

    Cluster &Cluster::operator+=(const Cluster &rhs) {
        LNodePtr rhsPtr = rhs.head;

        while (rhsPtr != nullptr) {
            if (!in(*this, rhsPtr->p))
                add(rhsPtr->p);

            rhsPtr = rhsPtr->next;
        }
        return *this;
    }

    Cluster &Cluster::operator-=(const Cluster &rhs) {
        LNodePtr rhsPtr = rhs.head;

        if (size != 0) {
            while (rhsPtr != nullptr) {
                if (in(*this, rhsPtr->p))
                    remove(rhsPtr->p);

                rhsPtr = rhsPtr->next;
            }
        }
        return *this;
    }

    Cluster &Cluster::operator+=(const PointPtr &rhs) {
        add(rhs);
        return *this;
    }

    Cluster &Cluster::operator-=(const PointPtr &rhs) {
        remove(rhs);
        return *this;
    }

    const Cluster operator+(const Cluster &lhs, const Cluster &rhs) {
        Cluster cluster(lhs);
        cluster += rhs;
        return cluster;
    }

    const Cluster operator-(const Cluster &lhs, const Cluster &rhs) {
        Cluster cluster(lhs);
        cluster -= rhs;
        return cluster;
    }

    const Cluster operator+(const Cluster &lhs, const PointPtr &rhs) {
        Cluster cluster(lhs);
        cluster.add(rhs);

        return cluster;
    }

    const Cluster operator-(const Cluster &lhs, const PointPtr &rhs) {
        Cluster cluster(lhs);
        cluster.remove(rhs);

        return cluster;
    }

    Point &Cluster::operator[](int index) {
        LNodePtr lNodePtr = head;

        for (int i=0; i<index; i++)
            lNodePtr = lNodePtr->next;

        return *lNodePtr->p;
    }

    void Cluster::computeCentroid() {
        Point sum(dimensionality);
        LNodePtr nodePtr = head;

        while (nodePtr != nullptr) {
            sum += *nodePtr->p;
            nodePtr = nodePtr->next;
        }

        __centroid = sum;
        __centroidValid = true;
    }

    void Cluster::pickPoints(int k, PointPtr pointArray[]) {
        LNodePtr currPtr = head;
        int skipAmount = size / k;

        for (int i=0; i<size; i++) {
            for (int j=0; j<skipAmount-1; j++)
                currPtr = currPtr->next;
            pointArray[i] = currPtr->p;
        }
    }

    double Cluster::intraClusterDistance() const {
        LNodePtr innerPtr = head, outerPtr = head;
        double sum = 0;

        while (outerPtr != nullptr) {
            while (innerPtr != nullptr) {
                sum += outerPtr->p->distanceTo(*innerPtr->p);
                innerPtr = innerPtr->next;
            }
            innerPtr = head;
            outerPtr = outerPtr->next;
        }

        sum /= 2;
        return sum;
    }

    double interClusterDistance(const Cluster &c1, const Cluster &c2) {
        Cluster cluster = c1 + c2;
        LNodePtr innerPtr = cluster.head, outerPtr = cluster.head;
        double sum = 0;

        while (outerPtr != nullptr) {
            while (innerPtr != nullptr) {
                sum += outerPtr->p->distanceTo(*innerPtr->p);
                innerPtr = innerPtr->next;
            }
            innerPtr = cluster.head;
            outerPtr = outerPtr->next;
        }

        sum /= 2;
        return sum;
    }
}
