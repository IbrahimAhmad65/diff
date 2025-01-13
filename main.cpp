#include "Derivative.h"
#include "Division.h"
#include "Ln.h"
#include "Log.h"
#include "Negation.h"
#include "Newton.h"
#include "Power.h"
#include "Substitute.h"
#include "Subtraction.h"
#include "Taylor.h"
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

  auto x_ptr = x.clone_t();
  auto b_ptr = b.clone_t();
  auto pow = Power(x_ptr, 2);
  auto k = x_ptr * pow + pow - x * 2;
  auto g = k->applyDeep();
  std::cout << *g << std::endl;
  auto n = g->distribute();
  std::cout << *n << std::endl;
  auto four = Number(4);
  auto z = Newton::newton(n, x_ptr, four.clone_t());
  std::cout << *z << std::endl;
  // auto tay = Taylor::taylor(x_ptr, 3, {b_ptr, x_ptr});
  // std::cout << *tay << std::endl;
  // std::cout << *tay->applyDeep() << std::endl;
  return 0;
}
