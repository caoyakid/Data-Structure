#include <iostream>
using namespace std;

#ifndef POLY_LINKEDLIST
#define POLY_LINKEDLIST

#include <math.h>

template <class T> class List;
class Polynomial;

struct Term{
    double coef;
    int exp;
    void Set(double c, int e) { coef = c; exp = e;}
    //Term Set(double c, int e) { coef=c; exp=e; return *this;}
};

template<class T>
class Node{
    friend class List<T>;
    friend class Polynomial;
    friend istream& operator>>(istream& is, Polynomial& p);
    friend ostream& operator<<(ostream& os, const Polynomial& p);

private:
    T data;
    Node* link;
public:
    Node(){link = NULL;}
    Node(const T& e, Node<T>* ptr){
        data = e;
        link = ptr;
    }
    void Set(T d, Node<T>* l){
        data = d; 
        link = l;
    }
};

template<class T>
class List{
    friend class Polynomial;
    friend istream& operator>>(istream& is, Polynomial& p);
    friend ostream& operator<<(ostream& os, const Polynomial& p);
public:
    List(){
        first = NULL;
        av = NULL;
    }
    ~List(){
        Node<T>* temp = first;
        while(first != NULL){
            first = first->link;
            delete temp;
            temp = first;
        }
    }
    friend ostream& operator<<(ostream& os, const List& list){
        if(list.first == 0){
            cout << "Empty List!" <<endl;
        }else {
            for(List<T>::Iterator i = list.Begin(); i!=list.End(); i++){
                os << *i << " ";
            }
        }
        cout << endl;
        return os;
    }
    void InsertBack(const T& e);
    Node<T>* GetNode();
    Node<T>* GetNode(const T& e, Node<T>* ptr);
    void RetNode(Node<T>*& x);

    class Iterator{
    friend class List;
    public: //typedefs required by C++ for a forward iterator
        //constructor
        Iterator(Node<T>* startNode = 0){
            current = startNode;
        }
        //Dereferencing operators
        T& operator *() const {return current -> data;}
        T* operator ->() const {return &current -> data;}
        //Increment
        Iterator& operator ++() // preincrement
        {current = current -> link;
        return *this;}
        Iterator& operator ++(int) // postincrement
        {Iterator& old = *this;
        current = current->link;
        return old;}
        //Equality test
        bool operator !=(const Iterator r)
        {return current != r.current;}
        bool operator ==(const Iterator r)
        {return current == r.current;}
    private:
        Node<T>* current;
    };
    Iterator Begin() const{return Iterator(first);}
    Iterator End() const{return Iterator(0);}
private:
    Node<T> *first, *av; //av:available 
};

template<class T>
Node<T>* List<T>::GetNode()
{   // Provide a node for use 
    Node<T>* x; 
    if(av != NULL){
        x = av;
        av = av->link;
    }else{ // out of available nodes
        x = new Node<T>;
    }
    return x;
}

template<class T>
Node<T>* List<T>::GetNode(const T& e, Node<T>* ptr)
{
    Node<T>* x;
    if(av != NULL){
        x = av;
        av = av->link;
        x->data = e;
        x->link = ptr;
    }else{ //out of available nodes
        x = new Node<T>(e, ptr);
    }
    return x;
}

template<class T>
void List<T>::RetNode(Node<T>*& x) //*& means: reference to a pointer
{  //Free the node pointed to by x
    x->link = av;
    av = x;
    x = 0; // not delete x 
    // x is cleared after being returned. This could prevent a freed node from 
    // still being used 
}

template<class T>
void List<T>::InsertBack(const T& e)
{
    if(first == 0){
        first = new Node<T>(e, first);
    }else{
        Node<T> *temp = first;
        while(temp->link != first){
            temp = temp->link;
        }
        Node<T> *tp = new Node<T>(e, first);
        temp->link = tp;
    }
}

/* ------------------------Class Polynomial------------------------ */
class Polynomial
{
public:
    Polynomial();
    ~Polynomial();
    Polynomial(const Polynomial& a);
    Polynomial operator=(const Polynomial& a);
    Polynomial operator+(const Polynomial& b);
    Polynomial operator-(const Polynomial& b);
    Polynomial operator*(const Polynomial& b);
    double Evaluate(double x);
    void Reset(){
        Node<Term> *x = poly.first;
        Node<Term> *temp = poly.first;
        while(x->link != poly.first){
            x = x->link;
            poly.RetNode(temp);
            temp = x;
        }
        poly.RetNode(temp);
        poly.first->link = poly.first;
        cout << "Reset End" << endl;
    }
    friend istream& operator>>(istream& is, Polynomial& p){
        cout<<"How many terms in the polynomial:" << endl;
        double n;
        is >> n;
        p.poly.first->link = p.poly.GetNode();
        p.poly.first->data.coef = n;

        cout << "Please enter the coef and the exp respectively in the descending order:"<< endl;
        Node<Term> *temp = p.poly.first;
        Term temp_term;
        double temp_coef;
        int temp_exp;
        for(int i=0; i<n-1; i++){
            temp = temp->link;
            is >> temp_coef >> temp_exp;
            temp_term.Set(temp_coef, temp_exp);
            temp->Set(temp_term, p.poly.GetNode());
        }
        // Noted*****
        temp = temp->link;
        is >> temp_coef >> temp_exp;
        temp_term.Set(temp_coef, temp_exp);
        temp->Set(temp_term, p.poly.first);
        return is;
    }
    friend ostream& operator<<(ostream& os, const Polynomial& p){
        if(p.poly.first == NULL){
            cout << "Empty list.";
            return os;
        }
        os << p.poly.first->data.coef << ", ";
        Node<Term> *temp = p.poly.first->link;
        while(temp->link != p.poly.first){
            os << temp->data.coef <<", " << temp->data.exp << ", ";
            temp = temp->link;
        }
        os << temp->data.coef <<", " << temp->data.exp;
        return os;
    }
private:
    List<Term> poly;
};

Polynomial::Polynomial()
{
    poly.av = NULL;
    poly.first = poly.GetNode();
    poly.first->data.coef = 0;
    poly.first->data.exp = 0;
    poly.first->link = poly.first;
}

Polynomial::~Polynomial()
{
    Node<Term> *x = poly.first;
    Node<Term> *p_del = x; 
    while(x->link != poly.first){
        x = x->link;
        poly.RetNode(p_del);
        p_del = x;
    }
}

//copy constructor 
Polynomial::Polynomial(const Polynomial& a){
    poly.first = poly.GetNode(a.poly.first->data, a.poly.first->link);
    Node<Term> *x1 = a.poly.first;
    Node<Term> *x2 = poly.first;
    while(x1->link != a.poly.first){
        x1 = x1->link;
        x2->link = poly.GetNode(x1->data, x1->link);
        x2 = x2->link;
    }
    x2->link = poly.first;
}

Polynomial Polynomial::operator=(const Polynomial& a){
    poly.first = poly.GetNode(a.poly.first->data, a.poly.first->link);
    Node<Term> *x1 = a.poly.first;
    Node<Term> *x2 = poly.first;
    while(x1->link != a.poly.first){
        x1 = x1->link;
        x2->link = poly.GetNode(x1->data, x1->link);
        x2 = x2->link;
    }
    x2->link = poly.first;
    return *this;
}
Polynomial Polynomial::operator+(const Polynomial& b){
    Term temp;
    double cterm = 0;
    List<Term>::Iterator ai = poly.Begin(), bi = b.poly.Begin();
    ai++;
    bi++;
    Polynomial c;
    while((ai != poly.Begin()) && (bi != b.poly.Begin())){
        if(ai->exp == bi->exp){
            double sum = ai->coef + bi->coef;
            temp.Set(sum, ai->exp);
            c.poly.InsertBack(temp);
            ai++;
            bi++;
            cterm++;
        }
        else if(ai->exp < bi->exp){
            temp.Set(bi->coef, bi->exp);
            c.poly.InsertBack(temp);
            bi++;
            cterm++;
        }
        else{
            temp.Set(ai->coef, ai->exp);
            c.poly.InsertBack(temp);
            ai++;
            cterm++;
        }
    }

    while(ai != poly.Begin()){
        temp.Set(ai->coef, ai->exp);
        c.poly.InsertBack(temp);
        ai++;
        cterm++;
    }
    while(bi != b.poly.Begin()){
        temp.Set(bi->coef, bi->exp);
        c,poly.InsertBack(temp);
        bi++;
        cterm++;
    }
    c.poly.first->data.coef = cterm;
    return c;
}

Polynomial Polynomial::operator-(const Polynomial& b){
    Term temp;
  double cterm = 0;
  List<Term>::Iterator ai = poly.Begin(), bi = b.poly.Begin();
  ai++;
  bi++;
  Polynomial c;
  while((ai != poly.Begin()) && (bi != b.poly.Begin())){
    if(ai->exp == bi->exp){
      double sum = ai->coef - bi->coef;
      temp.Set(sum, ai->exp);
      c.poly.InsertBack (temp);
      ai++;
      bi++;
      cterm++;
    }
    else if (ai->exp < bi->exp) {
      temp.Set(-(bi->coef), bi->exp);
      c.poly.InsertBack(temp);
      bi++;
      cterm++;
    }
    else {
      temp.Set(ai->coef , ai->exp);
      c.poly.InsertBack(temp) ;
      ai++;
      cterm++;
    }
  }
  while (ai != poly.Begin()){
    temp.Set(ai->coef,ai->exp);
    c.poly.InsertBack(temp);
    ai++;
    cterm++;
  }
  while (bi != b.poly.Begin()){
    temp.Set(-(bi->coef),bi->exp);
    c.poly.InsertBack (temp);
    bi++;
    cterm++;
  }
  c.poly.first->data.coef = cterm;

  return c;
}

Polynomial Polynomial::operator*(const Polynomial& b){
    Polynomial c;

    Node<Term> *ax = poly.first;
    Node<Term> *bx = b.poly.first;

    while(ax->link != poly.first){
        ax = ax->link;
        Polynomial temp;
        while(bx->link != b.poly.first){
            bx = bx->link;
            float temp_coef = ax->data.coef * bx->data.coef;
            int temp_exp = ax->data.exp + bx->data.exp;
            Term temp_term;
            temp_term.coef = temp_coef;
            temp_term.exp = temp_exp;
            temp.poly.InsertBack(temp_term);
        }
        c = c + temp;
        bx = b.poly.first;
    }
    return c;
}
double Polynomial::Evaluate(double x){
    double y = 0;
    Node<Term> *temp = poly.first;
    while(temp->link != poly.first){
        temp = temp->link;
        y += temp->data.coef * pow(x, temp->data.exp);
    }
    return y;
}


#endif 