#ifndef SET_H
#define SET_H

#include <iostream>
#include <ostream>

template <typename T>
class Set{
    public:
        Set();
        Set(const T& x);
        Set(const Set & other);
        void clear();
        ~Set();
        bool isEmpty() const;
        std::ostream & flush(std::ostream & out) const;
        bool contains(const T& x) const;
        bool isSubsetOf(const Set & other) const;
        void insert(const T& x);
        void remove(const T& x);
        void insertInto(Set & other) const;
        void removeFrom(Set & other) const;
        Set<T>& operator=(const Set & other);
        template <typename U>
        friend Set<U> image(const Set<U> & set, U (*function)(U));
        template <typename U>
        friend Set<U> operator&(const Set<U>& a, const Set<U>& b);
    private:
        class Node {
            public:
                Node(const T& value, Node * next = nullptr);
                ~Node();
                T getValue() const;
                Node * getNext() const;
                void setNext(Node * next);
            private:
                T value;
                Node * next;
        };
        Node * list;
        static Node * remove(Node * list, const T& x);
};

template <typename T>
Set<T>::Set() : list(nullptr) {}

template <typename T>
Set<T>::Set(const T& x) : list(new Node(x)) {}

template <typename T>
Set<T>::Set(const Set & other) : list(nullptr) {
    Node* current = other.list;
    while (current) {
        insert(current->getValue());
        current = current->getNext();
    }
}

template <typename T>
void Set<T>::clear() {
    while (list) {
        Node* temp = list;
        list = list->getNext();
        delete temp;
    }
    list = nullptr;
}

template <typename T>
Set<T>::~Set() {
    clear();
}

template <typename T>
bool Set<T>::isEmpty() const {
    return list == nullptr;
}

template <typename T>
std::ostream & Set<T>::flush(std::ostream & out) const {
    out << "{ ";
    Node* current = list;
    while (current) {
        out << current->getValue();
        current = current->getNext();
        if(current){
            out  << ", ";
        }
    }
    out << "}";
    return out;
}

template <typename T>
bool Set<T>::contains(const T& x) const {
    Node* current = list;
    while (current) {
        if (current->getValue() == x)
            return true;
        current = current->getNext();
    }
    return false;
}

template <typename T>
bool Set<T>::isSubsetOf(const Set & other) const {
    Node* current = list;
    while (current) {
        if (!other.contains(current->getValue()))
            return false;
        current = current->getNext();
    }
    return true;
}

template <typename T>
void Set<T>::insert(const T& x) {
    if (!contains(x)) {
        list = new Node(x, list);
    }
}

template <typename T>
void Set<T>::remove(const T& x) {
    list = remove(list, x);
}

template <typename T>
void Set<T>::insertInto(Set & other) const {
    Node* current = list;
    while (current) {
        other.insert(current->getValue());
        current = current->getNext();
    }
}

template <typename T>
void Set<T>::removeFrom(Set & other) const {
    Node* current = list;
    while (current) {
        other.remove(current->getValue());
        current = current->getNext();
    }
}

template <typename T>
Set<T>& Set<T>::operator=(const Set & other) {
    if (this != &other) {
        clear();
        Node* current = other.list;
        while (current) {
            insert(current->getValue());
            current = current->getNext();
        }
    }
    return *this;
}

template <typename T>
Set<T> image(const Set<T> & set, T (*function)(T)) {
    Set<T> result;
    typename Set<T>::Node* current = set.list;
    while (current != nullptr) {
        result.insert(function(current->getValue()));
        current = current->getNext();
    }
    return result;
}

template <typename T>
Set<T>::Node::Node(const T& value, Node* next) : value(value), next(next) {}

template <typename T>
T Set<T>::Node::getValue() const { return value; }

template <typename T>
typename Set<T>::Node* Set<T>::Node::getNext() const { return next; }

template <typename T>
void Set<T>::Node::setNext(Node* nextNode) { next = nextNode; }

template <typename T>
typename Set<T>::Node* Set<T>::remove(Node* list, const T& x) {
    if (!list) return nullptr;
    if (list->getValue() == x) {
        Node* temp = list->getNext();
        delete list;
        return temp;
    }
    Node* newNext = remove(list->getNext(), x);
    list->setNext(newNext);
    return list;
}

template <typename T>
std::ostream& operator<<(std::ostream& out, const Set<T>& s) {
    return s.flush(out);
}

template <typename T>
Set<T> singleton(const T& x) {
    Set<T> result;
    result.insert(x);
    return result;
}

template <typename T>
Set<T> emptySet() {
    return Set<T>();
}

template <typename T>
bool operator==(const Set<T>& a, const Set<T>& b) {
    return a.isSubsetOf(b) && b.isSubsetOf(a);
}

template <typename T>
bool operator<(const Set<T>& a, const Set<T>& b) {
    return a.isSubsetOf(b) && !(b.isSubsetOf(a));
}

template <typename T>
bool operator>(const Set<T>& a, const Set<T>& b) {
    return b < a;
}

template <typename T>
Set<T> operator|(const Set<T>& a, const Set<T>& b) {
    Set<T> result = a;
    b.insertInto(result);
    return result;
}

template <typename T>
Set<T> operator-(const Set<T>& a, const Set<T>& b) {
    Set<T> result = a;
    b.removeFrom(result);
    return result;
}

template <typename T>
Set<T> operator^(const Set<T>& a, const Set<T>& b) {
    return (a - b) | (b - a);
}

template <typename T>
Set<T> operator&(const Set<T>& a, const Set<T>& b) {
    Set<T> result;
    typename Set<T>::Node* current = a.list;
    while (current) {
        if (b.contains(current->getValue())) {
            result.insert(current->getValue());
        }
        current = current->getNext();
    }
    return result;
}

template <typename T>
Set<T>::Node::~Node() {}

#endif