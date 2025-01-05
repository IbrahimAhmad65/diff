#pragma once
#include <cstdarg>
#include <memory>
#include <vector>
#include <iostream>
#include <sstream>
#include <string>
#include <cxxabi.h>

class Group{
public:
  Group();
  Group(const std::vector<std::shared_ptr<Group>> &elems);
  Group(const std::shared_ptr<Group> &g);
  Group(const Group *g);

  virtual std::shared_ptr<Group> build(std::vector<std::shared_ptr<Group>> elems) const;
  virtual std::shared_ptr<Group> distributeDeep() const;
  virtual std::shared_ptr<Group> apply(std::vector<std::shared_ptr<Group>> &elements) const;
  virtual std::shared_ptr<Group> distribute(std::vector<std::shared_ptr<Group>> &elements) const;
  virtual std::shared_ptr<Group> distribute() const{
   std::cout <<"Unimplemented entry distribute" << std::endl;
   return std::make_shared<Group>(*this);
  }

  virtual std::shared_ptr<Group> formatDeep() const;
  virtual std::vector<std::shared_ptr<Group>> get_elements() const;

  virtual std::ostream &print(std::ostream &stream) const;
  virtual std::ostream &latex(std::ostream &stream) const;

  friend std::ostream &operator<<(std::ostream &stream, const Group &g) {
    return g.print(stream);
  } 
   
  std::ostream &build_latex(std::ostream &stream);
  std::shared_ptr<Group> applyDeep() const;
  virtual bool linear() const{
    return false;
  } 
  virtual std::shared_ptr<Group> clone() const{
    return std::make_shared<Group>(*this);
  }   

protected:
  std::vector<std::shared_ptr<Group>> elements;
};
bool comparison(std::shared_ptr<Group> g1, std::shared_ptr<Group> g2);
std::shared_ptr<Group> operator+(Group& g1, Group& g2);
std::shared_ptr<Group> operator+(std::shared_ptr<Group> g1, Group& g2);
std::shared_ptr<Group> operator+(std::shared_ptr<Group> g1, std::shared_ptr<Group> g2);

template<typename T> requires std::is_arithmetic_v<T>
std::shared_ptr<Group> operator+(std::shared_ptr<Group> g1,T g2);

template<typename T> requires std::is_arithmetic_v<T>
std::shared_ptr<Group> operator+(Group& g1,T g2);


std::shared_ptr<Group> operator*(Group& g1, Group& g2);
std::shared_ptr<Group> operator*(std::shared_ptr<Group> g1, Group& g2);
std::shared_ptr<Group> operator*(Group &g1, std::shared_ptr<Group> g2);
std::shared_ptr<Group> operator*(std::shared_ptr<Group> g1, std::shared_ptr<Group> g2);

template<typename T> requires std::is_arithmetic_v<T>
std::shared_ptr<Group> operator*(std::shared_ptr<Group> g1,T g2);

template<typename T> requires std::is_arithmetic_v<T>
std::shared_ptr<Group> operator*(Group& g1,T g2);

std::shared_ptr<Group> operator-(Group& g1);
std::shared_ptr<Group> operator-(std::shared_ptr<Group> g1);

bool operator==(std::shared_ptr<Group> g1, std::shared_ptr<Group> g2);
bool operator!=(std::shared_ptr<Group> g1, std::shared_ptr<Group> g2);

namespace std {
  template <>
  struct hash<std::shared_ptr<Group>> {
    size_t operator()(const std::shared_ptr<Group>& p) const {
      auto k = p->formatDeep();   
      ostringstream oss;
      oss << *k;
      string s = oss.str();
      return std::hash<string>()(s);
    }
  };
}
