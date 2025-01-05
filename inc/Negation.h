#pragma once
#include <Group.h>
#include <iostream>
#include <memory>
class Negation : public Base<Negation> {
public:
  Negation(std::shared_ptr<Group>& g) { 
    local = g;
    elements.push_back(local);
  }

  Negation(Group& g) { 
    local = g.clone();
    elements.push_back(local);
  }

  Negation(const Negation *n) { 
    local = n->local; 
    elements.push_back(local);
  }

  Negation(std::vector<std::shared_ptr<Group>> &elements) { 
    local = elements[0]; 
    elements.push_back(local);
  }
   
  std::shared_ptr<Group> apply(std::vector<std::shared_ptr<Group>> &elements) const override {
    return std::make_shared<Negation>(elements);
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
    return std::make_shared<Negation>(this);
  };  

  std::shared_ptr<Group> distribute() const override{
    return std::make_shared<Negation>(this);
  };  

private:
  std::shared_ptr<Group> local;
};

inline std::shared_ptr<Group> operator-(Group &g1) {
  return std::make_shared<Negation>(Negation(g1));
}

inline std::shared_ptr<Group> operator-(std::shared_ptr<Group> g1) {
  return std::make_shared<Negation>(Negation(g1));
}
