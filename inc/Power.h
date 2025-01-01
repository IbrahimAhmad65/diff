#pragma once
#include <Group.h>
#include <iostream>
#include <memory>
#include <cmath>
#include "Number.h"
class Power : public Group {
public:
  Power(std::vector<std::shared_ptr<Group>> elems);
  Power(Group& g);
  Power(const Power* p);
  Power(Group& g1, Group& g2);

  Power(std::shared_ptr<Group> g1, std::shared_ptr<Group> g2);

  std::shared_ptr<Group> formatDeep() const override{
    std::vector<std::shared_ptr<Group>> eApplied = std::vector<std::shared_ptr<Group>>();
    for (const auto &element : elements) {
      eApplied.push_back(element->formatDeep());
    }
    return build(eApplied);
  }

  std::shared_ptr<Group> distribute(std::vector<std::shared_ptr<Group>> &elements) const{
    return std::make_shared<Power>(Power(elements));
  }

  std::shared_ptr<Group> build(std::vector<std::shared_ptr<Group>> elems) const override{
    return std::make_shared<Power>(Power(elems));
  }
  Power( Power *n);
  template <typename T>
  requires std::is_arithmetic_v<T> 
  Power(std::shared_ptr<Group> g1,  T g2);

  template <typename T>
  requires std::is_arithmetic_v<T>  
  Power(Group &g1,  T g2);
  
  template <typename T>
  requires std::is_arithmetic_v<T>  
  Power(Group g1,  T g2);


  template <typename T, typename E>
  requires std::is_arithmetic_v<T> && std::is_arithmetic_v<E>  
  Power( T g1,  E g2);
  
  std::shared_ptr<Group> clone() const override;
  std::shared_ptr<Group>
  apply(std::vector<std::shared_ptr<Group>> &elements) const override ;

  std::ostream &print(std::ostream &stream) const override;

  std::ostream &latex(std::ostream &stream) const override;

};
