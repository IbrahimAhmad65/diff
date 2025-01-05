#include "Log.h"

Log::Log(std::vector<std::shared_ptr<Group>> elems) : Base(elems) {}

Log::Log(Group &g) : Base(g.get_elements()) {}

Log::Log(Group &g1, Group &g2) : Base() {
  elements.push_back(g1.clone());
  elements.push_back(g2.clone());
}

Log::Log(std::shared_ptr<Group> g1, std::shared_ptr<Group> g2) : Base() {
  elements.push_back(g1);
  elements.push_back(g2);
}

Log::Log(const Log *n) : Log(*n) {}

std::shared_ptr<Group> Log::apply(std::vector<std::shared_ptr<Group>> &elements) const {
  auto base = elements[0];
  auto exp = elements[1];
  if (auto num_base = std::dynamic_pointer_cast<Number>(base)) {
    if (auto num_exp = std::dynamic_pointer_cast<Number>(exp)) {
      double num = log2(num_exp->getRaw()) / log2(num_base->getRaw());
      return std::make_shared<Number>(Number(num));
    }
  }
  return std::make_shared<Log>(Log(base, exp));
}

std::ostream &Log::print(std::ostream &stream) const {
  // stream << "log_" << *get_elements()[0];
  stream << "ln";
  stream << "(" << *get_elements()[1] << ")";
  return stream;
}

std::ostream &Log::latex(std::ostream &stream) const {
  print(stream);
  return stream;
}

template <typename T>

requires std::is_arithmetic_v<T> Log::Log(std::shared_ptr<Group> g1, T g2) {
  elements.push_back(g1);
  auto two = Number(g2);
  elements.push_back(two.clone());
}

template <typename T>

requires std::is_arithmetic_v<T> Log::Log(T g2, std::shared_ptr<Group> g1) {
  auto two = Number(g2);
  elements.push_back(two.clone());
  elements.push_back(g1);
}

template Log::Log<int>(std::shared_ptr<Group> g1, int g2);
template Log::Log<double>(std::shared_ptr<Group> g1, double g2);

template Log::Log<int>(int g2, std::shared_ptr<Group> g1);
template Log::Log<double>(double g2, std::shared_ptr<Group> g1);

template <typename T>

requires std::is_arithmetic_v<T> Log::Log(Group &g1, T g2) {
  elements.push_back(g1.clone());
  auto two = Number(g2);
  elements.push_back(two.clone());
}

template <typename T>

requires std::is_arithmetic_v<T> Log::Log(T g2, Group &g1) {
  elements.push_back(g1.clone());
  auto two = Number(g2);
  elements.push_back(two.clone());
}

template Log::Log<int>(int g2, Group &g1);
template Log::Log<double>(double g2, Group &g1);

template Log::Log<int>(Group &g1, int g2);
template Log::Log<double>(Group &g1, double g2);
/*
template <typename T>

requires std::is_arithmetic_v<T> Log::Log(Group g1, T g2) {
  elements.push_back(g1.clone());
  auto two = Number(g2);
  elements.push_back(two.clone());
}

template Log::Log<int>(Group g1, int g2);
template Log::Log<double>(Group g1, double g2);
*/
template <typename T, typename E>

requires std::is_arithmetic_v<T> && std::is_arithmetic_v<E> Log::Log(T g1, E g2) {
  auto one = Number(g1);
  elements.push_back(one.clone());
  auto two = Number(g2);
  elements.push_back(two.clone());
}

template Log::Log<int, int>(int g1, int g2);
template Log::Log<double, int>(double g1, int g2);
template Log::Log<int, double>(int g1, double g2);
template Log::Log<double, double>(double g1, double g2);

bool operator>(std::shared_ptr<Log> g1, std::shared_ptr<Log> g2) {
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

bool operator<(std::shared_ptr<Log> g1, std::shared_ptr<Log> g2) {
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
