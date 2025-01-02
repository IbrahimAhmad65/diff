#include "Derivative.h"
#include "Negation.h"
#include "Power.h"
#include <Addition.h>
#include <Multiplication.h>
#include <Number.h>
#include <Variable.h>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <memory>

int main() {
  Variable a = Variable('a');
  Variable b = Variable('b');
  Variable c = Variable('c');
  Variable d = Variable('d');
  Variable x = Variable('x');
  auto x_ptr = std::make_shared<Variable>(x);
  auto pow = Power(x,3);
  auto g = Derivative::diff(pow.clone(), x_ptr);
  std::cout << *g << std::endl;

  auto n1 = (a + c) * (a + c) * a;
  auto n2 = n1->distribute();
  auto n3 = n2->distribute();
  std::cout << *n1 << std::endl;
  std::cout << *n2 << std::endl;
  std::cout << *n3 << std::endl;
  std::cout << *n3->formatDeep() << std::endl;
  return 0;
}
