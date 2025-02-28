#include "Power.h"

Power::Power(std::vector<std::shared_ptr<Group>> elems) : Base(elems) {}

Power::Power(Group &g) : Base(g.get_elements()) {}

Power::Power(Group &g1, Group &g2) : Base() {
  elements.push_back(g1.clone());
  elements.push_back(g2.clone());
}

Power::Power(std::shared_ptr<Group> g1, std::shared_ptr<Group> g2) : Base() {
  elements.push_back(g1);
  elements.push_back(g2);
}

Power::Power(const Power *n) : Power(*n) {}

std::shared_ptr<Group> Power::apply(std::vector<std::shared_ptr<Group>> &elements) const {
  auto base = elements[0];
  auto power = elements[1];
  if (auto num_pow = std::dynamic_pointer_cast<Number>(power)) {
    if (auto num_base = std::dynamic_pointer_cast<Number>(base)) {
      return std::make_shared<Number>(Number(pow(num_base->getRaw(), num_pow->getRaw())));
    }
    if (num_pow->getRaw() == 0) {
      auto n = Number(1);
      return n.clone();
    }
    if (num_pow->getRaw() == 1) {
      return base;
    }
  }
  return std::make_shared<Power>(Power(base, power));
}

std::ostream &Power::print(std::ostream &stream) const {
  stream << "(" << *get_elements()[0];
  stream << " ^ " << *get_elements()[1] << ")";
  return stream;
}

std::ostream &Power::latex(std::ostream &stream) const {
  print(stream);
  return stream;
}

bool operator>(std::shared_ptr<Power> g1, std::shared_ptr<Power> g2) {
  if (auto num1 = std::dynamic_pointer_cast<Number>(g1->get_elements()[1])) {
    if (auto num2 = std::dynamic_pointer_cast<Number>(g2->get_elements()[1])) {
      return num1 > num2;
    }
  }
  if (auto num1 = std::dynamic_pointer_cast<Variable>(g1->get_elements()[1])) {
    if (auto num2 = std::dynamic_pointer_cast<Number>(g2->get_elements()[1])) {
      return true;
    }
  }
  if (auto num1 = std::dynamic_pointer_cast<Number>(g1->get_elements()[1])) {
    if (auto num2 = std::dynamic_pointer_cast<Variable>(g2->get_elements()[1])) {
      return false;
    }
  }
  std::ostringstream oss1;
  std::ostringstream oss2;
  oss1 << *g1;
  oss2 << *g2;
  return oss1.str() > oss2.str();
}

bool operator<(std::shared_ptr<Power> g1, std::shared_ptr<Power> g2) {
  if (auto num1 = std::dynamic_pointer_cast<Number>(g1->get_elements()[1])) {
    if (auto num2 = std::dynamic_pointer_cast<Number>(g2->get_elements()[1])) {
      return num1 < num2;
    }
  }
  if (auto num1 = std::dynamic_pointer_cast<Variable>(g1->get_elements()[1])) {
    if (auto num2 = std::dynamic_pointer_cast<Number>(g2->get_elements()[1])) {
      return false;
    }
  }
  if (auto num1 = std::dynamic_pointer_cast<Number>(g1->get_elements()[1])) {
    if (auto num2 = std::dynamic_pointer_cast<Variable>(g2->get_elements()[1])) {
      return true;
    }
  }
  std::ostringstream oss1;
  std::ostringstream oss2;
  oss1 << *g1;
  oss2 << *g2;
  return oss1.str() < oss2.str();
}
