#include "Multiplication.h"

Multiplication::Multiplication(const std::vector<std::shared_ptr<Group>> &elems) : Group(elems) {}

Multiplication::Multiplication(const Multiplication *a) : Group(a->get_elements()) {}

Multiplication::Multiplication(const std::shared_ptr<Group> &g) : Group(g->get_elements()) {}

// Multiplication::Multiplication(std::shared_ptr<Group> g) : Group(g->get_elements()) {}

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
  if (!(t1->linear() && t2->linear())) {
    if (elements.size() > 2) {
      std::vector<std::shared_ptr<Group>> vec = {t1 * t2, elements[2]};
      return distribute(vec);
    } else {
      return t1 * t2;
    }
  }
  std::vector<std::shared_ptr<Group>> sop = std::vector<std::shared_ptr<Group>>();
  for (const auto &e1 : t1->get_elements()) {
    for (const auto &e2 : t2->get_elements()) {
      auto mult = e1 * e2;
      sop.push_back(std::make_shared<Multiplication>(mult));
    }
  }

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
}

std::shared_ptr<Group> Multiplication::distribute() const {
  auto k = distributeDeep();
  auto out = sanitize_distribute(k);
  return out;
}

std::shared_ptr<Group> Multiplication::sanitize_distribute(const std::shared_ptr<Group> sop) const {
  std::vector<std::shared_ptr<Group>> new_sop = std::vector<std::shared_ptr<Group>>();
  for (const auto &mult : sop->get_elements()) {
    std::unordered_map<CHAR_TYPE, int> map = std::unordered_map<CHAR_TYPE, int>();
    std::vector<std::shared_ptr<Group>> vec = std::vector<std::shared_ptr<Group>>();
    for (const auto &elem : mult->get_elements()) {
      if (auto var = std::dynamic_pointer_cast<Variable>(elem)) {
        if (map.find(var->getRaw()) == map.end()) {
          map[var->getRaw()] = 1;
        } else {
          map[var->getRaw()] = map[var->getRaw()] + 1;
        }
      } else {
        // no idea if needed tbh
        vec.push_back(elem);
      }
    }
    for (const std::pair<const CHAR_TYPE, int> &n : map) {
      CHAR_TYPE c = n.first;
      int i = n.second;
      if (i == 1) {
        vec.push_back(std::make_shared<Variable>(Variable(c)));
      } else {
        vec.push_back(std::make_shared<Power>(Power(std::make_shared<Variable>(Variable(c)), i)));
      }
    }
    if (vec.size() == 1) {
      new_sop.push_back(vec[0]);
    } else {
      new_sop.push_back(std::make_shared<Multiplication>(Multiplication(vec)));
    }
  }
  return std::make_shared<Addition>(Addition(new_sop));
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
