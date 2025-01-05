#include "Derivative.h"
#include "Log.h"
#include "Negation.h"
#include "Power.h"
#include "Substitute.h"
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
  Number n1 = Number(3);
  Number n2 = Number(5);
  auto p = Log(n1, n2);
  std::cout << p.name() << std::endl;
  std::cout << *p.applyDeep() << std::endl;

  auto x_ptr = std::make_shared<Variable>(x);
  auto pow = Power(x_ptr, 3);
  auto g = Derivative::diff(pow.clone(), x_ptr);
  std::cout << *g << std::endl;
  auto n = Derivative::diff(g->applyDeep(), x_ptr);
  std::cout << *n << std::endl;
  auto k = substitute(n, x_ptr, std::make_shared<Number>(Number(5)));
  std::cout << *k << std::endl;
  auto j = k->applyDeep();
  std::cout << *j << std::endl;
  /*
  auto n1 = (a + c) * (a + c) * a;
  auto n2 = n1->distribute();
  auto n3 = n2->distribute();
  std::cout << *n1 << std::endl;
  std::cout << *n2 << std::endl;
  std::cout << *n3 << std::endl;
  std::cout << *n3->formatDeep() << std::endl;
  */
  return 0;
}
