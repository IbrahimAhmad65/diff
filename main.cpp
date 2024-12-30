#include "Negation.h"
#include <Addition.h>
#include <Multiplication.h>
#include <Number.h>
#include <Variable.h>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <memory>
int main() {
  Variable x = Variable('x');
  auto add = (-x * -6) + 2;
  std::cout << *add << std::endl;
  auto applied = add->applyDeep();
  std::cout << *applied << std::endl;
  return 0;
}
