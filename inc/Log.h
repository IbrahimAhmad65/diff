#pragma once
#include <Group.h>
#include <iostream>
#include <memory>
#include <cmath>
#include "Number.h"
#include "Variable.h"
class Log : public Group {
public:
  Log(std::vector<std::shared_ptr<Group>> elems);
  Log(Group& g);
  Log(const Log* p);
  Log(Group& g1, Group& g2);

  bool linear() const override{
    return false;
  } 

  Log(std::shared_ptr<Group> g1, std::shared_ptr<Group> g2);

  std::shared_ptr<Group> formatDeep() const override{
    std::vector<std::shared_ptr<Group>> eApplied = std::vector<std::shared_ptr<Group>>();
    for (const auto &element : elements) {
      eApplied.push_back(element->formatDeep());
    }
    return build(eApplied);
  }

  std::shared_ptr<Group> distribute(std::vector<std::shared_ptr<Group>> &elements) const{
    auto out = std::make_shared<Log>(Log(elements));
    return out;
  }

  std::shared_ptr<Group> build(std::vector<std::shared_ptr<Group>> elems) const override{
    return std::make_shared<Log>(Log(elems));
  }

  Log( Log *n);
  template <typename T>
  requires std::is_arithmetic_v<T> 
  Log(std::shared_ptr<Group> g1,  T g2);

  template <typename T>
  requires std::is_arithmetic_v<T>  
  Log(Group &g1,  T g2);
  
  template <typename T>
  requires std::is_arithmetic_v<T>  
  Log(Group g1,  T g2);


  template <typename T, typename E>
  requires std::is_arithmetic_v<T> && std::is_arithmetic_v<E>  
  Log( T g1,  E g2);
  
  std::shared_ptr<Group> clone() const override;
  std::shared_ptr<Group>
  apply(std::vector<std::shared_ptr<Group>> &elements) const override ;

  std::ostream &print(std::ostream &stream) const override;

  std::ostream &latex(std::ostream &stream) const override;

};

bool operator >(std::shared_ptr<Log> g1,std::shared_ptr<Log> g2);
bool operator <(std::shared_ptr<Log> g1,std::shared_ptr<Log> g2);
