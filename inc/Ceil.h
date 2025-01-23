#pragma once
#include <Group.h>
#include <iostream>
#include <memory>
class Ceil : public Base<Ceil> {
public:
  Ceil(const std::shared_ptr<Group>& g) { 
    local = g;
    elements.push_back(local);
  }

  Ceil(const Group& g) { 
    local = g.clone();
    elements.push_back(local);
  }

  Ceil(const Ceil *n) { 
    local = n->local; 
    elements.push_back(local);
  }

  Ceil(std::vector<std::shared_ptr<Group>> &elements) { 
    local = elements[0]; 
    elements.push_back(local);
  }
   
  std::shared_ptr<Group> apply(std::vector<std::shared_ptr<Group>> &elements) const override {
    return std::make_shared<Ceil>(elements);
  }
  
  std::shared_ptr<Group> getRaw() { return local; }

  std::ostream &print(std::ostream &stream) const override {
    stream <<"-"<< *local;
    return stream;
  }

  std::ostream &latex(std::ostream &stream) const override {
    print(stream);
    return stream;
  }

  bool linear() const override{
    return true;
  }


  std::shared_ptr<Group> distribute(std::vector<std::shared_ptr<Group>> &elements) const override{
    return std::make_shared<Ceil>(this);
  };  

  std::shared_ptr<Group> distribute() const override{
    return std::make_shared<Ceil>(this);
  };  

private:
  std::shared_ptr<Group> local;
};

