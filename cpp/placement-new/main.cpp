#include <iostream>

int main() {
  unsigned int a = 3;
  std::cout << "Initial:" << std::endl;
  std::cout << "\tAddress: " << &a;
  std::cout << "\tCharacter: " << a << std::endl;
  int *mem = new (&a) int(11);
  std::cout << "Placement New:" << std::endl;
  std::cout << "\tAddress: " << &a;
  std::cout << "\tCharacter: " << a;
  std::cout << "\tnew address: " << mem << std::endl;
  return 0;
}
