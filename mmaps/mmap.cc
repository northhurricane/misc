#include <sys/mman.h>
#include <iostream>
#include <string.h>

#ifndef  NULL
#define NULL (0)
#endif

using namespace std;
const int page_size = 128 * 1024 * 1024;

int main(int argc, char *argv[])
{
  void *ptr;
  long long size = 2 * 1024 * 1024 * 1024L;

  ptr = mmap(NULL, size, PROT_READ | PROT_WRITE,
             MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
  if (ptr == 0)
  {
    cout << "fail mmap." << endl;
    return -1;
  }

  //memset(ptr, 0, size);
  int position = 0;
  while (true)
  {
    cout << "press to init next." << endl;
    string press;
    cin >> press;
    if ((position + page_size) > size)
      break;
    cout << position << endl;
    memset((char*)ptr + position, 0, page_size);
    position += page_size;
  }
  cout << "init finished." << endl;
  string ok;
  cin >> ok;

  return 0;
}
