#pragma once
#include <cstdarg>
#include <vector>
class Group{
public:
  Group(){}
  Group(std::vector<Group>& elems){
    elements = elems;
  }

  Group applyDeep() const{
    std::vector<Group> eApplied = std::vector<Group>();
    eApplied.reserve(elements.size());
    for(const auto& element: elements){
      eApplied.push_back(element.applyDeep());
    }
    Group out = apply(eApplied);
    return out;
  }
  virtual Group apply(std::vector<Group>& elements) const;
private:
  std::vector<Group> elements;
};
