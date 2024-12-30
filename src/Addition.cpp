#include "Addition.h"
Addition::Addition(const std::vector<std::shared_ptr<Group>> &elems)
    : Group(elems) {}
Addition::Addition(const Addition *a) : Group(a->get_elements()) {}

std::shared_ptr<Group>
Addition::apply(std::vector<std::shared_ptr<Group>> &elements) const {
  std::vector<std::shared_ptr<Group>> elems =
      std::vector<std::shared_ptr<Group>>(); // could be done lazily
  FLOAT_TYPE output = 0;
  for (const auto &g : elements) {
    if (auto number = std::dynamic_pointer_cast<Number>(g)) {
      output += number->getRaw();
    } else if (auto outer = std::dynamic_pointer_cast<Negation>(g)) {
      if (auto number = std::dynamic_pointer_cast<Number>(outer->getRaw())) {
        output -= number->getRaw();
      } else {
        elems.push_back(g);
      }
    } else {
      elems.push_back(g);
    }
  }
  if (elems.size() == 0) {
    return std::make_shared<Number>(Number(output));
  }
  elems.push_back(std::make_shared<Number>(Number(output)));
  return std::make_shared<Addition>(Addition(elems));
}

std::ostream &Addition::print(std::ostream &stream) const {
  auto elems = get_elements();
  stream << '(';
  for (int i = 0; i < elems.size() - 1; ++i) {
    stream << *elems[i] << " + ";
  }
  stream << *elems[elems.size() - 1] << ")";
  return stream;
}
std::ostream &Addition::latex(std::ostream &stream) const {
  auto elems = get_elements();
  stream << '(';
  for (int i = 0; i < elems.size() - 1; ++i) {
    elems[i]->latex(stream) << " + ";
  }
  elems[elems.size() - 1]->latex(stream) << ")";
  return stream;
}
