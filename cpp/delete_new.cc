#include <iostream>
#include <malloc.h>

void *(*__MALLOC_HOOK_VOLATILE old_malloc_hook) (size_t __size,
                                                 const __malloc_ptr_t);
void (*__MALLOC_HOOK_VOLATILE old_free_hook) (void *__ptr,
                                            const __malloc_ptr_t);
static void *
my_malloc_hook (size_t size, const void *caller)
{
  void * p = old_malloc_hook(size, caller);
  if (p != 0)
  {
  }
  return p;
}

static void
my_free_hook (void *ptr, const void *caller)
{
  if (ptr != 0)
  {
  }
  old_free_hook(ptr, caller);
}

static void
my_init (void)
{
}
#ifdef _COMPILE_IT_
static void
my_init (void)
{
  return ;
  old_malloc_hook = __malloc_hook;
  old_free_hook = __free_hook;
  __malloc_hook = my_malloc_hook;
  __free_hook = 0;//my_free_hook;
}

static void *
my_malloc_hook (size_t size, const void *caller)
{
  void *result;
  /* Restore all old hooks */
  __malloc_hook = old_malloc_hook;
  __free_hook = old_free_hook;
  /* Call recursively */
  result = malloc (size);
  /* Save underlying hooks */
  old_malloc_hook = __malloc_hook;
  old_free_hook = __free_hook;
  /* printf might call malloc, so protect it too. */
  printf ("malloc (%u) returns %p\n", (unsigned int) size, result);
  /* Restore our own hooks */
  __malloc_hook = my_malloc_hook;
  __free_hook = my_free_hook;
  return result;
}

static void
my_free_hook (void *ptr, const void *caller)
{
  /* Restore all old hooks */
  __malloc_hook = old_malloc_hook;
  __free_hook = old_free_hook;
  /* Call recursively */
  free (ptr);
  /* Save underlying hooks */
  old_malloc_hook = __malloc_hook;
  old_free_hook = __free_hook;
  /* printf might call free, so protect it too. */
  printf ("freed pointer %p\n", ptr);
  /* Restore our own hooks */
  __malloc_hook = my_malloc_hook;
  __free_hook = my_free_hook;
}
#endif

using namespace std;

#include <iostream>
void stop_for_dbg(int i)
{
  cout << i << endl;
}

class X
{
 public :
  X(int i) {i_ = i;stop_for_dbg(1);}
  ~X() {stop_for_dbg(2);}
  void show() {cout << "X show" << endl;}
 private :
  int i_;
};

void *operator new(size_t size, int id)
{
  stop_for_dbg(3);
  return malloc(size);
}

void operator delete(void *p)
{
  stop_for_dbg(4);
  free(p);
}

//for release
//#define new(id) new

int main(int argc, char *argv[])
{
  my_init();
  X *x = new(1) X(1);
  x->show();
  delete x;
  return 0;
}
