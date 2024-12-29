#pragma once
#include <Group.h>
#include <vector>
#include <Number.h>
#include <type_traits>
class Addition : public Group{
public:
  Addition(std::vector<Group>& elems) : Group(elems){}

  Group apply(std::vector<Group>& elements){
    std::vector<Group> elems;
    double output = 0;
    for(auto g : elements){
      if(Number* number = dynamic_cast<Number*>(&g)){
        output += number->getRaw();
      }
    }
  }
};
