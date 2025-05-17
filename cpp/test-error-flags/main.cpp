#include <cstdint>
#include <iostream>

enum { NOT_EVEN = 0x00000001 };

void isEven(uint64_t num, uint64_t *err);

int main() {
  while (true) {
    std::cout << "Welcome! Enter a number: " << std::endl;
    uint64_t n;
    uint64_t err = 0;
    std::cin >> n;
    isEven(n, &err);
    if (!err) {
      std::cout << n << " is even!" << std::endl;
    } else {
      std::cout << n << " is not even!" << std::endl;
      std::cout << "Error flag: " << err << std::endl;
    }
  }
  return 0;
}

void isEven(uint64_t num, uint64_t *err) {
  if (num % 2 != 0)
    *err = NOT_EVEN;
}
