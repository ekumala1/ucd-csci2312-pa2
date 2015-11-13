#ifndef CLUSTERING_POINT_H
#define CLUSTERING_POINT_H

#include <iostream>

namespace Clustering {
    class Point {
        int dim;
        double *values;

    public:
        static const char POINT_VALUE_DELIM;

        Point(int);
        Point(int, double *);

        Point(const Point &);
        Point &operator=(const Point &);
        ~Point();

        int getDims() const { return dim; }
        void setValue(int, double);
        double getValue(int) const;

        double distanceTo(const Point &) const;

        Point &operator*=(double);
        Point &operator/=(double);
        const Point operator*(double) const;
        const Point operator/(double) const;

        double &operator[](int index) { return values[index-1]; }

        friend Point &operator+=(Point &, const Point &);
        friend Point &operator-=(Point &, const Point &);
        friend const Point operator+(const Point &, const Point &);
        friend const Point operator-(const Point &, const Point &);

        friend bool operator==(const Point &, const Point &);
        friend bool operator!=(const Point &, const Point &);

        friend bool operator<(const Point &, const Point &);
        friend bool operator>(const Point &, const Point &);
        friend bool operator<=(const Point &, const Point &);
        friend bool operator>=(const Point &, const Point &);

        friend std::ostream &operator<<(std::ostream &, const Point &);
        friend std::istream &operator>>(std::istream &, Point &);
    };
}

#endif //CLUSTERING_POINT_H
