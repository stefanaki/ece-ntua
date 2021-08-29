#include <iostream>

using namespace std;

template <typename T>
class stack {
private:
  int top;
  int maxSize;
  T *array;

public:
  stack(int size) {
    array = new T[size];
    maxSize = size;
    top = -1;
  }

  stack(const stack &s) {
    int i;
    array = new T[s.maxSize];

    top = s.top;
    maxSize = s.maxSize;

    for(i=0;i<s.top+1;i++) {
      array[i] = s.array[i];
    }
  }

  ~stack() {
    delete[] array;
    top = -1;
    maxSize = 0;
  }

  const stack & operator = (const stack &s) {
    int i;

    delete[] array;
    array = new T[s.maxSize];

    top = s.top;
    maxSize = s.maxSize;

    for(i=0;i<s.top+1;i++) {
      array[i] = s.array[i];
    }

    return *this;
  }

  bool empty() const {
    return top == -1;
  }

  void push(const T &x) {
    array[++top] = x;
    return;
  }

  T pop() {
    return array[top--];
  }

  int size() const {
    return top + 1;
  }

  friend ostream & operator << (ostream &out, const stack &s) {
    int i;  

    out << "[";
    for(i=0;i<s.top+1;i++) {
      out << s.array[i];
      if(i < s.top) {
        out << ", ";
      }
    }
    out << "]";

    return out;
  }
};

#ifndef CONTEST

int main() {
  stack<int> s(10);
  cout << "s is empty: " << s << endl;
  s.push(42);
  cout << "s has one element: " << s << endl;
  s.push(17);
  s.push(34);
  cout << "s has more elements: " << s << endl;
  cout << "How many? " << s.size() << endl;
  stack<int> t(5);
  t.push(7);
  cout << "t: " << t << endl;
  t = s;
  cout << "popping from s: " << s.pop() << endl;
  s.push(8);
  stack<int> a(s);
  t.push(99);
  a.push(77);
  cout << "s: " << s << endl;
  cout << "t: " << t << endl;
  cout << "a: " << a << endl;
  stack<double> c(4);
  c.push(3.14);
  c.push(1.414);
  cout << "c contains doubles " << c << endl;
  stack<char> k(4);
  k.push('$');
  cout << "k contains a character " << k << endl;
  return 0;
}

#endif
