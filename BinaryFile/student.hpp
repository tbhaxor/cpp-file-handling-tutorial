#include <string>

class Student {
private:
  std::string name;
  unsigned short age;

public:
  void setAge(int age);
  void setAge(short age);
  void setAge(unsigned short age);

  void setName(std::string &name);
  void setName(const char *name);

  std::string whoami() const;
};