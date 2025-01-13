#pragma once
#include <Group.h>
#include <iostream>
#include <memory>
class Ln : public Base<Ln> {
public:
  Ln(std::shared_ptr<Group>& g) { 
    local = g;
    elements.push_back(local);
  }
  Ln(Group& g) { 
    local = g.clone();
    elements.push_back(local);
  }
  Ln(const Ln *n) { 
    local = n->local; 
    elements.push_back(local);
  }
  Ln(std::vector<std::shared_ptr<Group>> &elements) { 
    local = elements[0]; 
    this->elements.push_back(local);
  }
   
  std::shared_ptr<Group> 
  apply(std::vector<std::shared_ptr<Group>> &elements) const override {
    return std::make_shared<Ln>(elements);
  }
  std::shared_ptr<Group> getRaw() { return local; }

  std::ostream &print(std::ostream &stream) const override {
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
    return std::make_shared<Ln>(this);
  };  

  std::shared_ptr<Group> distribute() const override{
    return std::make_shared<Ln>(this);
  };  

private:
  std::shared_ptr<Group> local;
};

