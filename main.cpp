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

  auto n1 = (a + c) * (a + c);
  std::cout << *n1->applyDeep() << std::endl;
  // auto n2 = std::dynamic_pointer_cast<Addition>(n1->distribute());
  // auto n3 = n2->sanitize_distribute(n2);
  auto n3 = n1->distribute()->distribute();
  std::cout << *n3 << std::endl;
  return 0;
}
