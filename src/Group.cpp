#include "Group.h"
#include "Addition.h"
#include "Multiplication.h"
#include "Negation.h"

Group::Group() {
  elements = std::vector<std::shared_ptr<Group>>();
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

std::shared_ptr<Group> Group::formatDeep() const {
  std::vector<std::shared_ptr<Group>> eApplied = std::vector<std::shared_ptr<Group>>();
  for (const auto &element : elements) {
    eApplied.push_back(element->formatDeep());
  }
  std::sort(eApplied.begin(), eApplied.end(), comparison);
  return build(eApplied);
}

bool comparison(std::shared_ptr<Group> g1, std::shared_ptr<Group> g2) {
  if (auto num1 = std::dynamic_pointer_cast<Number>(g1)) {
    return true;
  }
  if (auto num1 = std::dynamic_pointer_cast<Number>(g2)) {
    return false;
  }
  if (auto num1 = std::dynamic_pointer_cast<Variable>(g1)) {
    return true;
  }
  if (auto num1 = std::dynamic_pointer_cast<Variable>(g2)) {
    return false;
  }
  if (auto num1 = std::dynamic_pointer_cast<Power>(g1)) {
    if (auto num2 = std::dynamic_pointer_cast<Power>(g2)) {
      return num1 > num2;
    }
    return true;
  }
  if (auto num1 = std::dynamic_pointer_cast<Power>(g2)) {
    return false;
  }
  std::ostringstream oss1;
  std::ostringstream oss2;
  oss1 << *g1;
  oss2 << *g2;
  return oss1.str().compare(oss2.str()) > 0;
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

bool operator!=(std::shared_ptr<Group> g1, std::shared_ptr<Group> g2) {
  return !(g1 == g2);
}

bool operator==(std::shared_ptr<Group> g1, std::shared_ptr<Group> g2) {
  auto t1 = g1->applyDeep();
  auto t11 = t1->distribute();
  auto t111 = t11->formatDeep();
  auto t2 = g2->applyDeep();
  auto t22 = t2->distribute();
  auto t222 = t22->formatDeep();
  std::ostringstream oss1;
  std::ostringstream oss2;
  oss1 << *t111;
  oss2 << *t222;
  return oss1.str() == oss2.str();
}
