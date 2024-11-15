#include <iomanip>
#include <ios>
#include <iostream>
#include <string>
#include <cmath>
#include "../include/Set.h"

using namespace std;
typedef Set<double> SetOfDouble;

int main(int, char *[]){
    SetOfDouble e;
    Set<double> f, g, h;
    for (int i = 1; i <= 10; i++) { e.insert(i); }
    for (int i = 5; i <= 20; i++) { f.insert(i); }
    for (int i = 14; i < 20; i++) { g.insert(i); }
    cout << std::boolalpha; // <ios>
    cout << e.contains(5) << endl;
    cout << f.contains(5) << endl;
    cout << g.contains(5) << endl;
    g.remove(18);
    g.remove(19);
    cout << "e = " << e << endl;
    cout << "f = " << f << endl;
    cout << "g = " << g << endl;
    {
        SetOfDouble dummy = g; // Copy constructor
        cout << " dummy = " << dummy << endl;
        dummy.clear();
        cout << " dummy = " << dummy << endl;
        dummy = h; // Assignment
    }              // Destructor
    
    cout << " e U f = " << (e | f) << endl;
    cout << " e inter f = " << (e & f) << endl;
    cout << " e- f = " << (e- f) << endl;
    cout << " e inter g = " << (e & g) << endl;
    cout << " e diffSym f = " << (e ^ f) << endl;
    cout << " e diffSym g = " << (e ^ g) << endl;
    cout << " e- e = " << (e- e) << endl;
    cout << " e- {40.0} = " << (e- singleton<double>(40.0)) << endl;
    cout << " e U {40} U {50} = " << (e | singleton(40.0) | singleton(50.0)) << endl;
    cout << endl;
    cout << " e = " << e << endl;
    cout << " f = " << f << endl;
    cout << " (e U f)- f " << (e | f)- f << endl;
    cout << " (e U f)- f == e ? " << (((e | f)- f) == e) << endl;
    cout << " En effet, car e inter f = " << (e & f) << endl;
    cout << endl;
    cout << " e == e U {} ? " << ((e | Set<double>()) == e) << endl;
    cout << " e- {5} < e ? " << ((e- Set<double>(5.0)) < e) << endl;
    Set<bool> a, b;
    a.insert(true);
    b.insert(false);
    cout << endl;
    cout << " a = " << a << endl;
    cout << " b = " << b << endl;
    cout << " a U b = " << (a | b) << endl;
    cout << " a U b- {true} = " << ((a | b)- singleton(true)) << endl;
    Set<string> dictionary;
    dictionary.insert("void");
    dictionary.insert("Hello");
    dictionary.insert("world");
    dictionary.insert("!");
    cout << " " << (dictionary- singleton(string("void"))) << endl;
    cout << " image(e&f,std::sin) = " << image(e & f, std::sin) << endl;
    return 0;
}