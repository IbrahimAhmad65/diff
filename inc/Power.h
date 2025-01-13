#pragma once
#include <Group.h>
#include <iostream>
#include <memory>
#include <cmath>
#include "Number.h"
#include "Variable.h"
class Power : public Base<Power> {
public:
  Power(std::vector<std::shared_ptr<Group>> elems);
  Power(Group& g);
  Power(const Power* p);
  Power(Group& g1, Group& g2);

  bool linear() const override{
    return false;
  } 

  Power(std::shared_ptr<Group> g1, std::shared_ptr<Group> g2);

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
    auto out = std::make_shared<Power>(Power(elements));
    return out;
  }

  Power( Power *n);
  template <typename T>
  requires std::is_arithmetic_v<T> 
  Power(std::shared_ptr<Group> g1,  T g2) {
    elements.push_back(g1);
    auto two = Number(g2);
    elements.push_back(two.clone());
  }


  template <typename T>
  requires std::is_arithmetic_v<T>  
  Power(Group &g1,  T g2){
    elements.push_back(g1.clone());
    auto two = Number(g2);
    elements.push_back(two.clone());
  }
  
  


  template <typename T, typename E>
  requires std::is_arithmetic_v<T> && std::is_arithmetic_v<E>  
  Power( T g1,  E g2){
    auto one = Number(g1);
    elements.push_back(one.clone());
    auto two = Number(g2);
    elements.push_back(two.clone());
  }
  
  std::shared_ptr<Group>
  apply(std::vector<std::shared_ptr<Group>> &elements) const override ;

  std::ostream &print(std::ostream &stream) const override;

  std::ostream &latex(std::ostream &stream) const override;

};

bool operator >(std::shared_ptr<Power> g1,std::shared_ptr<Power> g2);
bool operator <(std::shared_ptr<Power> g1,std::shared_ptr<Power> g2);
