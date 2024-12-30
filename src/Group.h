#pragma once
#include <cstdarg>
#include <iostream>
#include <memory>
#include <vector>
#include "Addition.h"
class Group {
public:
  Group() {}
  Group(const std::vector<std::shared_ptr<Group>> &elems) { elements = elems; }
  Group(const std::shared_ptr<Group> &g) { elements = g->elements; }
  Group(const Group *g) { elements = g->elements; }

  std::shared_ptr<Group> applyDeep() const {
    std::vector<std::shared_ptr<Group>> eApplied =
        std::vector<std::shared_ptr<Group>>();
    eApplied.reserve(elements.size());
    for (const auto &element : elements) {
      eApplied.push_back(element->applyDeep());
    }
    auto out = apply(eApplied);

    return out;
  }
  virtual std::shared_ptr<Group>
  apply(std::vector<std::shared_ptr<Group>> &elements) const {
    return std::make_shared<Group>(this);
  };

  std::vector<std::shared_ptr<Group>> get_elements() const { return elements; }

  virtual std::ostream &print(std::ostream &stream) const {
    stream << "Unimplemented print";
    return stream;
  }
  virtual std::ostream &latex(std::ostream &stream) const {
    stream << "Unimplemented latex";
    return stream;
  }

  friend std::ostream &operator<<(std::ostream &stream, const Group &g) {
    return g.print(stream);
  }

  virtual std::shared_ptr<Group> operator+(Group& g){
    auto k = std::vector<std::shared_ptr<Addition>>{std::make_shared<Group>(*this),std::make_shared<Group>(g)};
    return std::shared_ptr<Addition>(Addition(k));
  }

  std::ostream &build_latex(std::ostream &stream) {
    stream << "\\documentclass[12pt]{article}" << std::endl;
    stream << "\\usepackage{amsmath}" << std::endl;
    stream << "\\begin{document}" << std::endl;
    stream << "\\begin{equation}" << std::endl;
    latex(stream);
    stream << std::endl;
    stream << "\\end{equation}" << std::endl;
    stream << "\\end{document}" << std::endl;
  }

private:
  std::vector<std::shared_ptr<Group>> elements;
};
