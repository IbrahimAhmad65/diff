#include "Group.h"
#include "Addition.h"
#include "Multiplication.h"
#include "Negation.h"

Group::Group() {
  elements = std::vector<std::shared_ptr<Group>>(); // can be split into a seperate
                                                    // constructor where elements is
                                                    // not made to save mem
}

Group::Group(const std::vector<std::shared_ptr<Group>> &elems) {
  elements = elems;
}

Group::Group(const std::shared_ptr<Group> &g) {
  elements = g->elements;
}

Group::Group(const Group *g) {
  elements = g->elements;
}

std::shared_ptr<Group> Group::applyDeep() const {
  std::vector<std::shared_ptr<Group>> eApplied = std::vector<std::shared_ptr<Group>>();
  eApplied.reserve(elements.size());
  for (const auto &element : elements) {
    eApplied.push_back(element->applyDeep());
  }
  auto out = apply(eApplied);

  return out;
}

std::shared_ptr<Group> Group::apply(std::vector<std::shared_ptr<Group>> &elements) const {
  return std::make_shared<Group>(this);
};

std::shared_ptr<Group> Group::distributeDeep() const {
  std::vector<std::shared_ptr<Group>> eApplied = std::vector<std::shared_ptr<Group>>();
  eApplied.reserve(elements.size());
  for (const auto &element : elements) {
    auto e = element->distributeDeep();
    eApplied.push_back(e);
  }

  auto out = distribute(eApplied);

  return out;
}

std::shared_ptr<Group> Group::distribute(std::vector<std::shared_ptr<Group>> &elements) const {
  return std::make_shared<Group>(this);
};

std::vector<std::shared_ptr<Group>> Group::get_elements() const {
  return elements;
}

std::ostream &Group::print(std::ostream &stream) const {
  stream << "Unimplemented print";
  return stream;
}

std::ostream &Group::latex(std::ostream &stream) const {
  stream << "Unimplemented latex";
  return stream;
}

std::ostream &Group::build_latex(std::ostream &stream) {
  stream << "\\documentclass[12pt]{article}" << std::endl;
  stream << "\\usepackage{amsmath}" << std::endl;
  stream << "\\begin{document}" << std::endl;
  stream << "\\begin{equation}" << std::endl;
  latex(stream);
  stream << std::endl;
  stream << "\\end{equation}" << std::endl;
  stream << "\\end{document}" << std::endl;
  return stream;
}

std::shared_ptr<Group> operator+(Group &g1, Group &g2) {
  auto k = std::vector<std::shared_ptr<Group>>{g1.clone(), g2.clone()};
  return std::make_shared<Addition>(Addition(k));
}

std::shared_ptr<Group> operator+(std::shared_ptr<Group> g1, Group &g2) {
  auto k = std::vector<std::shared_ptr<Group>>{g1, g2.clone()};
  return std::make_shared<Addition>(Addition(k));
}

std::shared_ptr<Group> operator+(std::shared_ptr<Group> g1, std::shared_ptr<Group> g2) {
  auto k = std::vector<std::shared_ptr<Group>>{g1, g2};
  return std::make_shared<Addition>(Addition(k));
}

template <typename T>
requires std::is_arithmetic_v<T> std::shared_ptr<Group>

operator+(std::shared_ptr<Group> g1, T g2) {
  auto k = std::vector<std::shared_ptr<Group>>{g1, std::make_shared<Number>(Number(g2))};
  return std::make_shared<Addition>(Addition(k));
}

template <typename T>
requires std::is_arithmetic_v<T> std::shared_ptr<Group>

operator+(Group &g1, T g2) {
  auto k = std::vector<std::shared_ptr<Group>>{g1.clone(), std::make_shared<Number>(Number(g2))};
  return std::make_shared<Addition>(Addition(k));
}

template std::shared_ptr<Group> operator+<int>(std::shared_ptr<Group> g1, int g2);
template std::shared_ptr<Group> operator+<double>(std::shared_ptr<Group> g1, double g2);
template std::shared_ptr<Group> operator+<int>(Group &g1, int g2);
template std::shared_ptr<Group> operator+<double>(Group &g1, double g2);

std::shared_ptr<Group> operator*(Group &g1, Group &g2) {
  auto k = std::vector<std::shared_ptr<Group>>{g1.clone(), g2.clone()};
  return std::make_shared<Multiplication>(Multiplication(k));
}

std::shared_ptr<Group> operator*(std::shared_ptr<Group> g1, Group &g2) {
  auto k = std::vector<std::shared_ptr<Group>>{g1, g2.clone()};
  return std::make_shared<Multiplication>(Multiplication(k));
}

std::shared_ptr<Group> operator*(std::shared_ptr<Group> g1, std::shared_ptr<Group> g2) {
  auto k = std::vector<std::shared_ptr<Group>>{g1, g2};
  return std::make_shared<Multiplication>(Multiplication(k));
}

template <typename T>
requires std::is_arithmetic_v<T> std::shared_ptr<Group>

operator*(std::shared_ptr<Group> g1, T g2) {
  auto k = std::vector<std::shared_ptr<Group>>{g1, std::make_shared<Number>(Number(g2))};
  return std::make_shared<Multiplication>(Multiplication(k));
}

template <typename T>
requires std::is_arithmetic_v<T> std::shared_ptr<Group>

operator*(Group &g1, T g2) {
  auto k = std::vector<std::shared_ptr<Group>>{g1.clone(), std::make_shared<Number>(Number(g2))};
  return std::make_shared<Multiplication>(Multiplication(k));
}

template std::shared_ptr<Group> operator*<int>(std::shared_ptr<Group> g1, int g2);
template std::shared_ptr<Group> operator*<double>(std::shared_ptr<Group> g1, double g2);
template std::shared_ptr<Group> operator*<int>(Group &g1, int g2);
template std::shared_ptr<Group> operator*<double>(Group &g1, double g2);

std::shared_ptr<Group> operator-(Group &g1) {
  return std::make_shared<Negation>(Negation(g1));
}

std::shared_ptr<Group> operator-(std::shared_ptr<Group> g1) {
  return std::make_shared<Negation>(Negation(g1));
}
