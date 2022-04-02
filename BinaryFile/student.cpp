#include "student.hpp"
#include <cstring>
#include <sstream>
#include <string>

void Student::setAge(int age) { this->age = age; }
void Student::setAge(short age) { this->age = age; }
void Student::setAge(unsigned short age) { this->age = age; }

void Student::setName(std::string &name) {
  if (name.length() < 50) {
    std::strcpy(this->name, name.c_str());
  }
}
void Student::setName(const char *name) {
  if (std::strlen(name) < 50) {
    std::strcpy(this->name, name);
  }
}

std::string Student::whoami() const {
  std::stringstream s;
  s << "I am " << this->name << " and " << this->age << " years old";
  return s.str();
}