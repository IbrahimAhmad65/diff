#pragma once
#include <Group.h>
#include <Number.h>
#include <Variable.h>
#include <Power.h>
#include <Addition.h>
#include <Negation.h>
#include <iostream>
#include <algorithm>
#include <memory>
#include <type_traits>
#include <vector>
#include <unordered_map>
class Multiplication : public Base<Multiplication> {
public:
  Multiplication(const std::vector<std::shared_ptr<Group>> &elems);
  Multiplication(const Multiplication *a);
  Multiplication(const std::shared_ptr<Group>& g);

  bool linear() const override{
    return true;
  } 

  std::shared_ptr<Group> apply(std::vector<std::shared_ptr<Group>> &elements) const override;

  std::shared_ptr<Group> distribute() const override;
  std::shared_ptr<Group> distribute(std::vector<std::shared_ptr<Group>> &elements) const override;
  std::ostream &print(std::ostream &stream) const override;
  std::ostream &latex(std::ostream &stream) const override;

protected:
  std::shared_ptr<Group> sanitize_distribute(const std::shared_ptr<Group> sop) const;
};

inline std::shared_ptr<Group> operator*(Group &g1, Group &g2) {
  auto k = std::vector<std::shared_ptr<Group>>{g1.clone(), g2.clone()};
  return std::make_shared<Multiplication>(Multiplication(k));
}

inline std::shared_ptr<Group> operator*(std::shared_ptr<Group> g1, Group &g2) {
  auto k = std::vector<std::shared_ptr<Group>>{g1, g2.clone()};
  return std::make_shared<Multiplication>(Multiplication(k));
}

inline std::shared_ptr<Group> operator*(Group &g1, std::shared_ptr<Group> g2) {
  auto k = std::vector<std::shared_ptr<Group>>{g1.clone(), g2};
  return std::make_shared<Multiplication>(Multiplication(k));
}

inline std::shared_ptr<Group> operator*(std::shared_ptr<Group> g1, std::shared_ptr<Group> g2) {
  auto k = std::vector<std::shared_ptr<Group>>{g1, g2};
  return std::make_shared<Multiplication>(Multiplication(k));
}

template <typename T> requires std::is_arithmetic_v<T> 
inline std::shared_ptr<Group> operator*(std::shared_ptr<Group> g1, T g2) {
  if (auto n = std::dynamic_pointer_cast<Multiplication>(g1)) {
    std::vector<std::shared_ptr<Group>> elems = n->get_elements();
    elems.push_back(std::make_shared<Number>(Number(g2)));
    return std::make_shared<Multiplication>(Multiplication(elems));
  }
  auto k = std::vector<std::shared_ptr<Group>>{g1, std::make_shared<Number>(Number(g2))};
  return std::make_shared<Multiplication>(Multiplication(k));
}

template <typename T> requires std::is_arithmetic_v<T> 
inline std::shared_ptr<Group> operator*(Group &g1, T g2) {
  auto n1 = g1.clone();
  if (auto n = std::dynamic_pointer_cast<Multiplication>(n1)) {
    std::vector<std::shared_ptr<Group>> elems = n->get_elements();
    elems.push_back(std::make_shared<Number>(Number(g2)));
    return std::make_shared<Multiplication>(Multiplication(elems));
  }
  auto k = std::vector<std::shared_ptr<Group>>{g1.clone(), std::make_shared<Number>(Number(g2))};
  return std::make_shared<Multiplication>(Multiplication(k));
}
