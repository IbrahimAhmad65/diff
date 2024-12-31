#include "Multiplication.h"

Multiplication::Multiplication(const std::vector<std::shared_ptr<Group>> &elems) : Group(elems) {}

Multiplication::Multiplication(const Multiplication *a) : Group(a->get_elements()) {}

Multiplication::Multiplication(std::shared_ptr<Group> &g) : Group(g->get_elements()) {}

std::shared_ptr<Group> Multiplication::apply(std::vector<std::shared_ptr<Group>> &elements) const {
  std::vector<std::shared_ptr<Group>> elems = std::vector<std::shared_ptr<Group>>(); // could be done lazily
  FLOAT_TYPE output = 1;
  bool negate = false;
  for (auto &g : elements) {
    if (auto outer = std::dynamic_pointer_cast<Negation>(g)) {
      negate = !negate;
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

std::shared_ptr<Group> Multiplication::distribute(std::vector<std::shared_ptr<Group>> &elements) const {
  auto t1 = elements[0];
  auto t2 = elements[1];
  std::vector<std::shared_ptr<Group>> sop = std::vector<std::shared_ptr<Group>>();
  for (const auto &e1 : t1->get_elements()) {
    for (const auto &e2 : t2->get_elements()) {
      auto mult = e1 * e2;
      sop.push_back(std::make_shared<Multiplication>(mult));
    }
  }
  auto k = Addition(sop);
  auto j = k.clone();
  std::vector<std::shared_ptr<Group>> answer = std::vector<std::shared_ptr<Group>>();
  for (const auto &temp : sop) {
    std::vector<std::shared_ptr<Group>> local = std::vector<std::shared_ptr<Group>>();
    for (const auto &g : temp->get_elements()) {
      if (auto mult = std::dynamic_pointer_cast<Multiplication>(g)) {
        for (const auto &t : g->get_elements()) {
          local.push_back(t);
        }
      } else {
        local.push_back(g);
      }
    }
    answer.push_back(std::make_shared<Multiplication>(Multiplication(local)));
  }
  if (elements.size() > 2) {
    std::vector<std::shared_ptr<Group>> vec = {std::make_shared<Addition>(Addition(answer)), elements[2]};
    return distribute(vec);
  }
  return std::make_shared<Addition>(Addition(answer));
  return std::make_shared<Addition>(Addition(sop));
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
