#pragma once
#include <cstdarg>
#include <iostream>
#include <memory>
#include <vector>
class Group{
public:
  Group();
  Group(const std::vector<std::shared_ptr<Group>> &elems);
  Group(const std::shared_ptr<Group> &g);
  Group(const Group *g);

  std::shared_ptr<Group> applyDeep() const;
  virtual std::shared_ptr<Group>
  apply(std::vector<std::shared_ptr<Group>> &elements) const;

  std::vector<std::shared_ptr<Group>> get_elements() const;

  virtual std::ostream &print(std::ostream &stream) const;
  virtual std::ostream &latex(std::ostream &stream) const;

  friend std::ostream &operator<<(std::ostream &stream, const Group &g) {
    return g.print(stream);
  } 
  virtual std::shared_ptr<Group> clone(){
    return std::make_shared<Group>(*this);
  }

  std::ostream &build_latex(std::ostream &stream);

private:
  std::vector<std::shared_ptr<Group>> elements;
};
std::shared_ptr<Group> operator+(Group& g1, Group& g2);
std::shared_ptr<Group> operator+(std::shared_ptr<Group> g1, Group& g2);

template<typename T> requires std::is_arithmetic_v<T>
std::shared_ptr<Group> operator+(std::shared_ptr<Group> g1,T g2);

template<typename T> requires std::is_arithmetic_v<T>
std::shared_ptr<Group> operator+(Group& g1,T g2);


std::shared_ptr<Group> operator*(Group& g1, Group& g2);
std::shared_ptr<Group> operator*(std::shared_ptr<Group> g1, Group& g2);

template<typename T> requires std::is_arithmetic_v<T>
std::shared_ptr<Group> operator*(std::shared_ptr<Group> g1,T g2);

template<typename T> requires std::is_arithmetic_v<T>
std::shared_ptr<Group> operator*(Group& g1,T g2);

std::shared_ptr<Group> operator-(Group& g1);
std::shared_ptr<Group> operator-(std::shared_ptr<Group> g1);
