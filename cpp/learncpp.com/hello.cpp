#include <iostream>
using namespace std;

class Name {
private:
  string n;

public:
  Name(string name) { n = name; }
  string getName() { return this->n; }
  void setName(string name) { this->n = name; }
  friend ostream &operator<<(std::ostream &os, const Name &n);
};

ostream &operator<<(ostream &os, const Name &na) {
  os << "Name: " << na.n;
  return os;
}

int main() {
  string n;
  cout << "Please enter your name: ";
  cin >> n;
  Name *name = new Name(n);
  cout << *name;
  return 0;
}
