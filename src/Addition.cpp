#include "Addition.h"
#include "Multiplication.h"

Addition::Addition(const std::vector<std::shared_ptr<Group>> &elems) : Group(elems) {}

Addition::Addition(const Addition *a) : Group(a->get_elements()) {}

std::shared_ptr<Group> Addition::apply(std::vector<std::shared_ptr<Group>> &elements) const {
  std::vector<std::shared_ptr<Group>> elems = std::vector<std::shared_ptr<Group>>(); // could be done lazily
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
  if (output != 0) {
    elems.push_back(std::make_shared<Number>(Number(output)));
  }
  return std::make_shared<Addition>(Addition(elems));
}

std::shared_ptr<Group> Addition::distribute(std::vector<std::shared_ptr<Group>> &elements) const {
  std::vector<std::shared_ptr<Group>> elems = std::vector<std::shared_ptr<Group>>();
  for (const auto &g : elements) {
    if (auto number = std::dynamic_pointer_cast<Addition>(g)) {
      for (const auto &k : number->get_elements()) {
        elems.push_back(k);
      }
    } else {
      elems.push_back(g);
    }
  }
  return std::make_shared<Addition>(Addition(elems));
}

std::shared_ptr<Group> Addition::distribute() const {
  auto k = distributeDeep();
  auto out = sanitize_distribute(k);
  return out;
}

std::shared_ptr<Group> Addition::sanitize_distribute(std::shared_ptr<Group> sop) const {
  std::vector<std::shared_ptr<Group>> new_sop = std::vector<std::shared_ptr<Group>>();
  std::unordered_map<std::shared_ptr<Group>, int> map = std::unordered_map<std::shared_ptr<Group>, int>();
  for (const auto &elem : sop->get_elements()) {
    if (map.find(elem) == map.end()) {
      map[elem] = 1;
    } else {
      map[elem]++;
    }
  }
  std::vector<std::shared_ptr<Group>> sop_vec = sop->get_elements();
  for (const std::pair<const std::shared_ptr<Group>, int> &n : map) {
    std::shared_ptr<Group> elem = n.first;
    int num = n.second;
    if (num == 1) {
      new_sop.push_back(elem);
    } else {
      new_sop.push_back(elem * num);
    }
  }
  return std::make_shared<Addition>(Addition(new_sop));
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
