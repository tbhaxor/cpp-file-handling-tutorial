#include "student.hpp"
#include <sstream>
#include <string>

void Student::setAge(int age) { this->age = age; }
void Student::setAge(short age) { this->age = age; }
void Student::setAge(unsigned short age) { this->age = age; }

void Student::setName(std::string &name) { this->name = name; }
void Student::setName(const char *name) { this->name = std::string(name); }

std::string Student::whoami() const {
  std::stringstream s;
  s << "I am " << this->name << " and " << this->age << " years old";
  return s.str();
}