/**
 * @brief Confusitions around Upcasting in C++.
 *
 * The following code demonstrates how upcasting syntax (#00 & #01) can look similar but have
 * very different behaviours.
 */
#include <iostream>
using namespace std;

class Shape {
public:
  Shape() : m_area(0) { cout << "Shape: Constructor is called." << endl; }
  Shape(const Shape &other) : m_area(other.m_area) { cout << "Shape: Copy Constructor is called." << endl; };
  virtual ~Shape() { cout << "Shape: Destructor is called." << endl; }

private:
  double m_area;
};

class Circle : public Shape {
public:
  Circle() { cout << "Circle: Constructor is called." << endl; }
  ~Circle() { cout << "Circle: Destructor is called." << endl; }
};

int main() {

  // #00: Polymorphism. The address of derived class gets stored in base class ptr.
  // As per polymorphic rules, dervived class's behaviour would get triggered on runtime.
  // This is upcasting. Circle is upcasted to Shape.
  Shape *shapePtr = new Circle();
  delete shapePtr;

  // #01: Object Slicing. The derived class is stripped down & only parent part gets copied "by-value".
  // Polymorphism breaks here without any errors. Often unintentially.
  // This is also upcasting. Circle is converted to Shape.
  Shape shapePtr = Circle();

  return 0;
}