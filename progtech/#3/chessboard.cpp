#include <iostream>
#include <stdexcept>
#include <iomanip>

using namespace std;

class ChessBoardArray {
protected:
  class Row {
  private:
    ChessBoardArray &cba;
    int row;

  public:
    Row(ChessBoardArray &a, int i) : cba(a), row(i) {}

    int & operator [] (int i) const { return cba.select(row, i); }
  };

  class ConstRow {
  private:
    const ChessBoardArray &cba;
    int row;

  public:
    ConstRow(const ChessBoardArray &a, int i) : cba(a), row(i) {}

    const int & operator [] (int i) const { return cba.select(row, i); }
  };

  int *data;
  int Base, Size;

  unsigned loc(int i, int j) const throw(out_of_range) {
    int di = i - Base, dj = j - Base;

    if(di < 0 || di >= Size)
      throw out_of_range("invalid index");
    if(dj < 0 || dj >= Size)
      throw out_of_range("invalid index");
    if((di % 2 == 0) ^ (dj % 2 == 0))
      throw out_of_range("black box");

    return (di * Size + dj) / 2;
  }

public:
  ChessBoardArray(unsigned size = 0, unsigned base = 0) {
    data = new int[(size * size / 2) + (size % 2)];
    for(unsigned i = 0; i < (size * size) / 2 + (size % 2); i++)
      data[i] = 0;
    Size = size;
    Base = base;
  }

  ChessBoardArray(const ChessBoardArray &a) {
    data = new int[(a.Size * a.Size) / 2 + (a.Size % 2)];
    Size = a.Size;
    Base = a.Base;
    for(int i = 0; i < (a.Size * a.Size) / 2 + (a.Size % 2); i++)
      data[i] = a.data[i];
  }

  ~ChessBoardArray() {
    delete[] data;
    Size = Base = 0;
  }

  ChessBoardArray & operator = (const ChessBoardArray &a) {
    delete[] data;
    Size = a.Size;
    Base = a.Base;
    data = new int[(Size * Size) / 2 + (Size % 2)];
    for(int i = 0; i < (Size * Size) / 2 + (Size % 2); i++)
      data[i] = a.data[i];
    return *this;
  }

  int & select(int i, int j) { return data[loc(i, j)]; }

  const int & select(int i, int j) const { return data[loc(i, j)]; }

  const Row operator [] (int i) { return Row(*this, i); }

  const ConstRow operator [] (int i) const { return ConstRow(*this, i); }

  friend ostream & operator << (ostream &out, const ChessBoardArray &a) {
    for(int i = 0; i < a.Size; i++) {
      for(int j = 0; j < a.Size; j++) {
        if((i % 2 == 0) ^ (j % 2 == 0))
          out << setw(4) << 0;
        else
          out << setw(4) << a.data[a.loc(i + a.Base, j + a.Base)];
      }
      out << endl;
    }
    return out;
  }
};
