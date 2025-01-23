#pragma once
#include "Group.h"
#include "Number.h"
#include "Negation.h"
#include <iostream>
#include <memory>
#include <type_traits>
#include <vector>
#include <unordered_map>
class Addition : public Base<Addition> {
public:
  Addition(const std::vector<std::shared_ptr<Group>> &elems);
  Addition(const Addition *a);

  bool linear() const override{
    return true;
  } 
  
  std::shared_ptr<Group> apply(std::vector<std::shared_ptr<Group>> &elements) const override;
  std::shared_ptr<Group> distribute(std::vector<std::shared_ptr<Group>> &elements) const override;
  std::shared_ptr<Group> distribute() const override;
  std::ostream &print(std::ostream &stream) const override;
  std::ostream &latex(std::ostream &stream) const override;
  std::shared_ptr<Group> sanitize_distribute(const std::shared_ptr<Group> sop) const;
};


template <typename T>
requires std::is_arithmetic_v<T> 

inline std::shared_ptr<Group> operator+(std::shared_ptr<Group> g1, T g2) {
  auto k = std::vector<std::shared_ptr<Group>>{g1, std::make_shared<Number>(Number(g2))};
  return std::make_shared<Addition>(Addition(k));
}
template <typename T>
requires std::is_arithmetic_v<T> 

inline std::shared_ptr<Group> operator+(T g2, std::shared_ptr<Group> g1) {
  auto k = std::vector<std::shared_ptr<Group>>{g1, std::make_shared<Number>(Number(g2))};
  return std::make_shared<Addition>(Addition(k));
}

template <typename T>
requires std::is_arithmetic_v<T> 

inline std::shared_ptr<Group> operator+(Group &g1, T g2) {
  auto k = std::vector<std::shared_ptr<Group>>{g1.clone(), std::make_shared<Number>(Number(g2))};
  return std::make_shared<Addition>(Addition(k));
}

template <typename T>
requires std::is_arithmetic_v<T> 
inline std::shared_ptr<Group> operator+(T g2, Group &g1) {
  auto k = std::vector<std::shared_ptr<Group>>{g1.clone(), std::make_shared<Number>(Number(g2))};
  return std::make_shared<Addition>(Addition(k));
}

inline std::shared_ptr<Group> operator+(Group &g1, Group &g2) {
  auto k = std::vector<std::shared_ptr<Group>>{g1.clone(), g2.clone()};
  return std::make_shared<Addition>(Addition(k));
}

inline std::shared_ptr<Group> operator+(std::shared_ptr<Group> g1, Group &g2) {
  auto k = std::vector<std::shared_ptr<Group>>{g1, g2.clone()};
  return std::make_shared<Addition>(Addition(k));
}

inline std::shared_ptr<Group> operator+(std::shared_ptr<Group> g1, std::shared_ptr<Group> g2) {
  auto k = std::vector<std::shared_ptr<Group>>{g1, g2};
  return std::make_shared<Addition>(Addition(k));
}
