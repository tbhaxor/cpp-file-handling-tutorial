#include <string>

class Student {
private:
  std::string name;
  unsigned short age;

public:
  Student();
  Student(const char *name, unsigned short age);
  std::string whoami() const;
};