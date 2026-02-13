/**
 * @brief Demonstrates the function overloading for insertion (<<) & extraction operators (>>).
 *
 * Overloading the the stream operator allows custom classes to interact with cin/cout types making the input/output
 * operations more intuitive.
 *
 * @note This was asked in FlexTrade interview on 21st January 2026.
 */
#include <iostream>
using namespace std;

class Point {
public:
  Point(int x = 0, int y = 0) : x(x), y(y) { cout << "Point created\n"; }
  ~Point() { cout << "Point destroyed\n"; }

  /**
   * @brief Overload the insertion stream operator (<<).
   * @param out: Represents the `cout` keyword when we write `cout << pt`.
   * @param pt: Represents the Point object when we write `cout << pt`.
   * @return ostream: Output stream
   *
   * @note `cout` is the left operands of the `<<` & it cannot be made a member of this class. Thus we declare this
   * function as friend so it can access the class members.
   */
  friend ostream &operator<<(ostream &out, const Point &pt);

  /**
   * @brief Overload the insertion stream operator (>>).
   * @param in: Represents the `cin` keyword when we write `cin >> pt`.
   * @param pt: Represents the Point object when we write `cin >> pt`.
   * @return istream: Input stream
   *
   * @note `cin` is the left operands of the `>>` & it cannot be made a member of this class. Thus we declare this
   * function as friend so it can access the class members.
   */
  friend istream &operator>>(istream &in, Point &pt);

private:
  int x, y;
};

ostream &operator<<(ostream &out, const Point &pt) {
  out << "Point(" << pt.x << ", " << pt.y << ")" << endl;
  return out;
}

istream &operator>>(istream &in, Point &pt) {
  cout << "Enter x: ";
  in >> pt.x;
  cout << "Enter y: ";
  in >> pt.y;
  return in;
}

int main() {
  Point pt;
  cout << "Enter 2 values to initiate the Point object." << endl;
  cin >> pt;
  cout << pt;
  return 0;
}