#include <iostream>
using namespace std;
#include <stack>

#ifndef MAZE_H
#define MAZE_H

template <class T>
class Stack
{
public:
    Stack(int stackCapacity = 10)
    {
        capacity = stackCapacity;
        array = new T[capacity];
        top = -1;
    }
    ~Stack(){delete [] array;}
    bool isEmpty(){return top == -1;}
    T& Top() const{return array[top];}
    void Push(const T& x){array[++top] = x;}
    void Pop(){array[top--].~T();}
    friend ostream& operator <<(ostream& os, Stack<T>& s) {
        os << "Total steps = " << s.top + 1 << endl;
        for (int i = 0; i <= s.top; i++) os << i << ": " << s.array[i] << endl;
        return os;
    }
private:
    T *array;
    int top, capacity;
};

class offsets {
public:
    int di, dj;
};
enum directions { N, NE, E, SE, S, SW, W, NW};

offsets movearray[8];

void setmovearray() {
    movearray[N].di = -1;
    movearray[N].dj = 0;
    movearray[NE].di = -1;
    movearray[NE].dj = 1;
    movearray[E].di = 0;
    movearray[E].dj = 1;
    movearray[SE].di = 1;
    movearray[SE].dj = 1;
    movearray[S].di = 1;
    movearray[S].dj = 0;
    movearray[SW].di = 1;
    movearray[SW].dj = -1;
    movearray[W].di = 0;
    movearray[W].dj = -1;
    movearray[NW].di = -1;
    movearray[NW].dj = -1;
}

struct Items {
    int x, y, dir;
    Items() {};
    Items(const int& x, const int& y, const int& dir): x{x}, y{y}, dir{dir} {}
    ~Items() {}
    friend ostream& operator <<(ostream& os, Items& item)
    {
        os << "(" << item.x << "," << item.y << ") ";
        switch (item.dir) {
            case 1:
                os << "move N to ";
                break;
            case 2:
                os << "move NE to ";
                break;
            case 3:
                os << "move E to ";
                break;
            case 4:
                os << "move SE to ";
                break;
            case 5:
                os << "move S to ";
                break;
            case 6:
                os << "move SW to ";
                break;
            case 7:
                os << "move W to ";
                break;
            case 8:
                os << "move NW to ";
                break;
            default:
                break;
        }
        return os;
    }
};




#endif