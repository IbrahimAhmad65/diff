#include "Power.h"

Power::Power(std::vector<std::shared_ptr<Group>> elems) : Group(elems) {}

Power::Power(Group &g) : Group(g.get_elements()) {}

Power::Power(Group &g1, Group &g2) : Group() {
  elements.push_back(g1.clone());
  elements.push_back(g2.clone());
}

Power::Power(std::shared_ptr<Group> g1, std::shared_ptr<Group> g2) : Group() {
  elements.push_back(g1);
  elements.push_back(g2);
}

Power::Power(const Power *n) : Power(*n) {}

std::shared_ptr<Group> Power::clone() const {
  return std::make_shared<Power>(*this);
}

std::shared_ptr<Group> Power::apply(std::vector<std::shared_ptr<Group>> &elements) const {
  auto base = elements[0];
  auto power = elements[1];
  if (auto num_base = std::dynamic_pointer_cast<Number>(base)) {
    if (auto num_pow = std::dynamic_pointer_cast<Number>(power)) {
      return std::make_shared<Number>(Number(pow(num_base->getRaw(), num_pow->getRaw())));
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

template <typename T>

requires std::is_arithmetic_v<T> Power::Power(std::shared_ptr<Group> g1, T g2) {
  elements.push_back(g1);
  auto two = Number(g2);
  elements.push_back(two.clone());
}

template Power::Power<int>(std::shared_ptr<Group> g1, int g2);
template Power::Power<double>(std::shared_ptr<Group> g1, double g2);

template <typename T>

requires std::is_arithmetic_v<T> Power::Power(Group &g1, T g2) {
  elements.push_back(g1.clone());
  auto two = Number(g2);
  elements.push_back(two.clone());
}

template Power::Power<int>(Group &g1, int g2);
template Power::Power<double>(Group &g1, double g2);

template <typename T>

requires std::is_arithmetic_v<T> Power::Power(Group g1, T g2) {
  elements.push_back(g1.clone());
  auto two = Number(g2);
  elements.push_back(two.clone());
}

template Power::Power<int>(Group g1, int g2);
template Power::Power<double>(Group g1, double g2);

template <typename T, typename E>

requires std::is_arithmetic_v<T> && std::is_arithmetic_v<E> Power::Power(T g1, E g2) {
  auto one = Number(g1);
  elements.push_back(one.clone());
  auto two = Number(g2);
  elements.push_back(two.clone());
}

template Power::Power<int, int>(int g1, int g2);
template Power::Power<double, int>(double g1, int g2);
template Power::Power<int, double>(int g1, double g2);
template Power::Power<double, double>(double g1, double g2);

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
