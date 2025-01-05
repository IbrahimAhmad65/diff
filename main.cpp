#include "Derivative.h"
#include "Division.h"
#include "Ln.h"
#include "Log.h"
#include "Negation.h"
#include "Power.h"
#include "Taylor.h"
#include "Substitute.h"
#include "Subtraction.h"
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
  auto pow = Power(x, x);
  auto ln = Ln(x);
  std::cout << ln << std::endl;
  auto z = Derivative::diff(pow.clone(), x_ptr);
  std::cout << *z << std::endl;
  auto g = z->applyDeep();
  std::cout << *g << std::endl;
  return 0;
}
