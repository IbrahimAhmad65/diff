#include "Multiplication.h"
Multiplication::Multiplication(const std::vector<std::shared_ptr<Group>> &elems)
    : Group(elems) {}
Multiplication::Multiplication(const Multiplication *a)
    : Group(a->get_elements()) {}

std::shared_ptr<Group>
Multiplication::apply(std::vector<std::shared_ptr<Group>> &elements) const {
  std::vector<std::shared_ptr<Group>> elems =
      std::vector<std::shared_ptr<Group>>(); // could be done lazily
  FLOAT_TYPE output = 1;
  bool negate = false;
  for (auto &g : elements) {
    if (auto outer = std::dynamic_pointer_cast<Negation>(g)) {
      negate = !negate;
      std::cout << "here" << std::endl;
      g = outer->getRaw();
    }
    if (auto number = std::dynamic_pointer_cast<Number>(g)) {
      auto num = number->getRaw();
      if (num < 0) {
        negate = !negate;
        num = -num;
      }
      output *= num;
    } else {
      elems.push_back(g);
    }
  }
  if (elems.size() == 0) {
    Number num(output);
    if (negate) {
      return std::make_shared<Negation>(num);
    }
    return std::make_shared<Number>(num);
  }
  if (output == 0) {
    return std::make_shared<Number>(Number(0));
  }
  if (output != 1) {
    elems.push_back(std::make_shared<Number>(Number(output)));
  }
  Multiplication mult(elems);
  if (negate) {
    return -mult;
  }
  return std::make_shared<Multiplication>(mult);
}

std::ostream &Multiplication::print(std::ostream &stream) const {

  auto elems = get_elements();
  stream << '(';
  for (int i = 0; i < elems.size() - 1; ++i) {
    stream << *elems[i] << " * ";
  }
  stream << *elems[elems.size() - 1] << ")";
  return stream;
}
std::ostream &Multiplication::latex(std::ostream &stream) const {
  auto elems = get_elements();
  stream << '(';
  for (int i = 0; i < elems.size() - 1; ++i) {
    stream << *elems[i] << " \\cdot ";
  }
  stream << *elems[elems.size() - 1] << ")";
  return stream;
}
