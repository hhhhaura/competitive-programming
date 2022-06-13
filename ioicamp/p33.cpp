#include <cassert>
#include <iostream>

#define meow(this_is_the_first_param, this_is_the_second_param,    \
             this_is_the_third_param, yes_this_is_the_fifth_param) \
  std::string this_is_the_first_param##                             \
      this_is_the_second_param =                                   \
          this_is_the_third_param yes_this_is_the_fifth_param;

int main() {
  meow(hello,world, "hello ", "world!");
  std::cout << helloworld << std::endl;
  assert(helloworld == "hello world!");
  assert(helloworld == "hello world!");
  assert(helloworld == "hello world!");
  assert(helloworld == "hello world!");
  assert(helloworld == "hello world!");
}

