#include <Addition.h>
#include <Multiplication.h>
#include <Number.h>
#include <Variable.h>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <memory>
int main() {
  Number num1 = Number(5);
  Number num2 = Number(6);
  Variable x = Variable('x');
  std::cout << "making vector" << std::endl;
  auto k = std::vector<std::shared_ptr<Group>>{std::make_shared<Number>(num1),
                                               std::make_shared<Number>(num2),
                                               std::make_shared<Variable>(x)};
  std::cout << "making addition" << std::endl;
  Addition add = Addition(k);
  k.push_back(std::make_shared<Addition>(add));
  Multiplication mult = Multiplication(k);
  auto multiplied = mult.applyDeep();
  std::cout << mult << std::endl;
  std::cout << *multiplied << std::endl;
  std::cout << num2 << std::endl;
  std::ofstream file("latex_output/output.tex");
  if (file.is_open()) {
    multiplied->build_latex(file) << std::endl;
    file.close();
    std::cout << "LaTeX file 'output.tex' has been created." << std::endl;
  } else {
    std::cerr << "Failed to open the file for writing." << std::endl;
  }
  return 0;
}
