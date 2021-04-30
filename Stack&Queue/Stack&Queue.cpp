#include <iostream>
using namespace std;

template <class T>
class List;
template <class T>
class Stack;
template <class T>
class Queue;

template <class T>
class Node
{
    friend class List<T>;
    friend class Stack<T>;
    friend class Queue<T>;

public:
    Node(T e)
    {
        data = e;
        link = 0;
    }

private:
    T data;
    Node *link;
};

template <class T>
class List
{
public:
    List() { first = last = 0; }
    bool isEmpty() { return first == 0; } //return true if empty list
    void InsertBack(const T &e);          //insert a node after the last node in the list
    void Delete();                        //delete the first node in the list
    void DeleteBack();                    //delete the last node in the list
protected:
    Node<T> *first, *last;
};

template <class T>
void List<T>::InsertBack(const T &e)
{
    if (first)
    {
        //nonempty list
        //let last points to the last node
        last->link = new Node<T>(e);
        last = last->link;
    }
    else
        first = last = new Node<T>(e);
}

template <class T>
void List<T>::Delete()
{
    Node<T> *temp = first;
    if (!first)
    {
        cout << "empty list" << endl;
        return;
    }
    else
    {
        if (first == last)
        {
            temp = first;
            first = last = 0;
            delete temp;
        }
        else
        {
            temp = first;
            first = temp->link;
            delete temp;
        }
    }
}

template <class T>
void List<T>::DeleteBack()
{
    Node<T> *temp = first;
    if (!first)
    {
        cout << "empty list" << endl;
        return;
    }
    else
    {
        if (first == last)
        {
            temp = first;
            first = last = 0;
            delete temp;
        }
        else
        {
            while (temp->link != last)
            {
                temp = temp->link;
            }
            last = temp;
            temp = temp->link;
            delete temp;
        }
    }
}

//Stack inherited from List
template <class T>
class Stack : public List<T>
{
public:
    Stack() { top = List<T>::last; }
    //bool isEmpty(); //return true if empty stack
    void push(const T &e);
    void pop();
    T Top(); //return top of stack
private:
    Node<T> *top;
};

//Queue inherited from List
template <class T>
class Queue : public List<T>
{
public:
    Queue()
    {
        front = List<T>::first;
        rear = List<T>::last;
    }
    //bool isEmpty(); //return true if empty queue
    void push(const T &e);
    void pop();
    T Front();
    T Rear();

private:
    Node<T> *front, *rear;
};

//******Need to design******//
template <class T>
void Stack<T>::push(const T &e)
{
    List<T>::InsertBack(e);
    top = List<T>::last;
}

template <class T>
void Stack<T>::pop()
{
    List<T>::DeleteBack();
    top = List<T>::last;
}

template <class T>
T Stack<T>::Top()
{
    const T temp = 0;
    if (top)
        return top->data;
    else
        return temp;
}

template <class T>
void Queue<T>::push(const T &e)
{
    List<T>::InsertBack(e);
    rear = List<T>::last;
    front = List<T>::first;
}

template <class T>
void Queue<T>::pop()
{
    List<T>::Delete();
    front = List<T>::first;
}

template <class T>
T Queue<T>::Front()
{
    const T temp = 0;
    if (front)
        return front->data;
    else
        return temp;
}

template <class T>
T Queue<T>::Rear()
{
    const T temp = 0;
    if (rear)
        return rear->data;
    else
        return temp;
}

//******END*******//

int main()
{
    cout << "Test Stack" << endl;
    Stack<int> s;
    s.push(10);
    cout << s.Top() << endl;
    s.pop();
    cout << s.Top() << endl;
    cout << "Test Queue" << endl;
    Queue<int> q;
    q.push(10);
    q.push(20);
    q.push(30);
    cout << q.Front() << endl;
    cout << q.Rear() << endl;
    q.pop();
    cout << q.Front() << endl;
    return 0;
}
