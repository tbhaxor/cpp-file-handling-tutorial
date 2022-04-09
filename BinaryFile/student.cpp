#include "student.hpp"
#include <cstring>
#include <sstream>
#include <string>

Student::Student() {
  this->name = "";
  this->age = 0;
}

Student::Student(const char *name, unsigned short age) {
  this->name = std::string(name);
  this->age = age;
}

std::string Student::whoami() const {
  std::stringstream s;
  s << "I am " << this->name << " and " << this->age << " years old";
  return s.str();
}