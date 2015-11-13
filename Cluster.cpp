#include "Cluster.h"

namespace Clustering {
    int idGenerator = 1;

    bool Cluster::in(Cluster &cluster, PointPtr &pointPtr) {
        LNodePtr lNodePtr = cluster.head;
        bool in = false;

        while (lNodePtr != nullptr) {
            if (lNodePtr->p == pointPtr)
                in = true;

            lNodePtr = lNodePtr->next;
        }
        return in;
    }

    Cluster::Cluster(const Cluster &cluster) : dim(cluster.dim), __centroid(cluster.__centroid) {
        size = 0;
        LNodePtr thisPtr = new LNode, clusterPtr = cluster.head;
        thisPtr->p = clusterPtr->p;

        while (clusterPtr != nullptr) {
            add(clusterPtr->p);
            clusterPtr = clusterPtr->next;
        }
    }

    Cluster &Cluster::operator=(const Cluster &cluster) {
        size = 0;
        dim = cluster.dim;
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
    }

    const PointPtr &Cluster::remove(const PointPtr &pointPtr) {
        if (size != 0) {
            LNodePtr prevPtr, delPtr=new LNode, currPtr=head;
            delPtr->p = pointPtr;

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

        return pointPtr;
    }

    std::ostream &operator<<(std::ostream &ostream, const Cluster &cluster) {
        LNodePtr lNodePtr = cluster.head;
        ostream << "{";
        if (cluster.size != 0) {
            while (lNodePtr->next != nullptr) {
                ostream << *(lNodePtr->p) << ", ";
                lNodePtr = lNodePtr->next;
            }
            ostream << *(lNodePtr->p);
        }
        ostream << "}";

        return ostream;
    }

    std::istream &operator>>(std::istream &istream, Cluster &cluster) {
        return istream;
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
}
