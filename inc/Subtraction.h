#pragma once
#include <Group.h>
#include <iostream>
#include <memory>
#include <cmath>
#include "Number.h"
#include "Variable.h"
class Subtraction : public Base<Subtraction> {
public:
  Subtraction(std::vector<std::shared_ptr<Group>> elems);
  Subtraction(Group& g);
  Subtraction(const Subtraction* p);
  Subtraction(Group& g1, Group& g2);

  bool linear() const override{
    return false;
  } 

  Subtraction(std::shared_ptr<Group> g1, std::shared_ptr<Group> g2);

  std::shared_ptr<Group> formatDeep() const override{
    std::vector<std::shared_ptr<Group>> eApplied = std::vector<std::shared_ptr<Group>>();
    for (const auto &element : elements) {
      eApplied.push_back(element->formatDeep());
    }
    return build(eApplied);
  }

  std::shared_ptr<Group> distribute() const{
    auto out = distributeDeep();
    return out;
  }
  std::shared_ptr<Group> distribute(std::vector<std::shared_ptr<Group>> &elements) const{
    auto out = std::make_shared<Subtraction>(Subtraction(elements));
    return out;
  }


  Subtraction( Subtraction *n);
  template <typename T>
  requires std::is_arithmetic_v<T> 
  Subtraction(std::shared_ptr<Group> g1,  T g2);

  template <typename T>
  requires std::is_arithmetic_v<T>  
  Subtraction(Group &g1,  T g2);
  
  template <typename T>
  requires std::is_arithmetic_v<T>  
  Subtraction(Group g1,  T g2);


  template <typename T, typename E>
  requires std::is_arithmetic_v<T> && std::is_arithmetic_v<E>  
  Subtraction( T g1,  E g2);
  
  std::shared_ptr<Group>
  apply(std::vector<std::shared_ptr<Group>> &elements) const override ;

  std::ostream &print(std::ostream &stream) const override;

  std::ostream &latex(std::ostream &stream) const override;

};

bool operator >(std::shared_ptr<Subtraction> g1,std::shared_ptr<Subtraction> g2);
bool operator <(std::shared_ptr<Subtraction> g1,std::shared_ptr<Subtraction> g2);


inline std::shared_ptr<Group> operator-(Group &g1, Group &g2) {
  auto k = std::vector<std::shared_ptr<Group>>{g1.clone(), g2.clone()};
  return std::make_shared<Subtraction>(Subtraction(k));
}

inline std::shared_ptr<Group> operator-(std::shared_ptr<Group> g1, Group &g2) {
  auto k = std::vector<std::shared_ptr<Group>>{g1, g2.clone()};
  return std::make_shared<Subtraction>(Subtraction(k));
}

inline std::shared_ptr<Group> operator-(Group &g1, std::shared_ptr<Group> g2) {
  auto k = std::vector<std::shared_ptr<Group>>{g1.clone(), g2};
  return std::make_shared<Subtraction>(Subtraction(k));
}

inline std::shared_ptr<Group> operator-(std::shared_ptr<Group> g1, std::shared_ptr<Group> g2) {
  auto k = std::vector<std::shared_ptr<Group>>{g1, g2};
  return std::make_shared<Subtraction>(Subtraction(k));
}

template <typename T> requires std::is_arithmetic_v<T> 
inline std::shared_ptr<Group> operator-(std::shared_ptr<Group> g1, T g2) {
  if (auto n = std::dynamic_pointer_cast<Subtraction>(g1)) {
    std::vector<std::shared_ptr<Group>> elems = n->get_elements();
    elems.push_back(std::make_shared<Number>(Number(g2)));
    return std::make_shared<Subtraction>(Subtraction(elems));
  }
  auto k = std::vector<std::shared_ptr<Group>>{g1, std::make_shared<Number>(Number(g2))};
  return std::make_shared<Subtraction>(Subtraction(k));
}

template <typename T> requires std::is_arithmetic_v<T> 
inline std::shared_ptr<Group> operator-(Group &g1, T g2) {
  auto n1 = g1.clone();
  if (auto n = std::dynamic_pointer_cast<Subtraction>(n1)) {
    std::vector<std::shared_ptr<Group>> elems = n->get_elements();
    elems.push_back(std::make_shared<Number>(Number(g2)));
    return std::make_shared<Subtraction>(Subtraction(elems));
  }
  auto k = std::vector<std::shared_ptr<Group>>{g1.clone(), std::make_shared<Number>(Number(g2))};
  return std::make_shared<Subtraction>(Subtraction(k));
}
