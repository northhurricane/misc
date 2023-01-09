#include <iostream>
#include <cstddef>
 
// objects of type S can be allocated at any address
// because both S.a and S.b can be allocated at any address
struct S
{
  char a; // size: 1, alignment: 1
  char b; // size: 1, alignment: 1
  char c;
}; // size: 2, alignment: 1
 
// objects of type X must be allocated at 4-byte boundaries
// because X.n must be allocated at 4-byte boundaries
// because int's alignment requirement is (usually) 4
struct X
{
  int n;  // size: 4, alignment: 4
  char c; // size: 1, alignment: 1
  // three bytes of padding bits
}; // size: 8, alignment: 4 

struct Y
{
  char c;
  int n ;
};

struct Z
{
  char c;
  int n ;
  double dbl;
};

int main()
{
  std::cout << "sizeof(S) = " << sizeof(S)
            << " alignof(S) = " << alignof(S) << '\n';
  std::cout << "sizeof(X) = " << sizeof(X)
            << " alignof(X) = " << alignof(X) << '\n';
  std::cout << "sizeof(Y) = " << sizeof(Y)
            << " alignof(Y) = " << alignof(Y) << '\n';
  std::cout << "sizeof(Z) = " << sizeof(Z)
            << " alignof(Z) = " << alignof(Z) << '\n';
  std::cout << "alignof(std::max_align_t) = " << alignof(std::max_align_t) << '\n';

  S s;
  std::cout << "address s1 of S is " << &s << '\n';
  S s2;
  std::cout << "address s2 of S is " << &s2 << '\n';
  X x;
  std::cout << "address x of X is " << &x << '\n';
}
