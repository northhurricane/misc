/*
  g++ static_assert.cc -std=c++11
*/
int main(int argc, const char *argv[])
{
  static_assert(false, "try raising error during compilation.");
  return 0;
}


