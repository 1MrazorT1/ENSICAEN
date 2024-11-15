#ifndef SETOFDOUBLE_H
#define SETOFDOUBLE_H

#include <iostream>
#include <ostream>

class SetOfDouble {
    public:
        SetOfDouble();
        SetOfDouble(double x);
        void clear();
        ~SetOfDouble();
        bool isEmpty() const;
        std::ostream & flush(std::ostream & out) const;
        bool contains(double x) const;
        bool isSubsetOf(const SetOfDouble & other) const;
        void insert(double x);
        void remove(double x);
        void insertInto(SetOfDouble & other) const;
        void removeFrom(SetOfDouble & other) const;
        SetOfDouble & operator=(const SetOfDouble & other);
        SetOfDouble(const SetOfDouble & other);
        friend SetOfDouble image(const SetOfDouble & set, double (*function)(double));
    private:
        class Node {
            public:
                Node(double value, Node * next = nullptr);
                ~Node();
                double getValue() const;
                Node * getNext() const;
                void setNext(Node * next);
            private:
                double value;
                Node * next;
        };
        Node * list;
        static Node * remove(Node * list, double x);
};

std::ostream & operator<<(std::ostream & out, const SetOfDouble & s);
SetOfDouble singleton(double x);
SetOfDouble emptySet();
bool operator==(const SetOfDouble & a, const SetOfDouble & b);
bool operator<(const SetOfDouble & a, const SetOfDouble & b);
bool operator>(const SetOfDouble & a, const SetOfDouble & b);
SetOfDouble operator|(const SetOfDouble & a, const SetOfDouble & b);
SetOfDouble operator-(const SetOfDouble & a, const SetOfDouble & b);
SetOfDouble operator^(const SetOfDouble & a, const SetOfDouble & b);
SetOfDouble operator&(const SetOfDouble & a, const SetOfDouble & b);

#endif