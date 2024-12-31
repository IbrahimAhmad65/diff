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
  auto mult = (a + c) * (a + c) * (a + c);
  std::cout << *mult << std::endl;
  auto applied = mult->distributeDeep();
  std::cout << *applied << std::endl;
  return 0;
}
