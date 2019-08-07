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
  old_malloc_hook = __malloc_hook;
  old_free_hook = __free_hook;
  __malloc_hook = my_malloc_hook;
  __free_hook = 0;//my_free_hook;
}

#ifdef _COMPILE_IT_
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

class X
{
 public :
  X(int i) {i_ = i;}
  void show() {cout << "X show" << endl;}
 private :
  int i_;
};

int main(int argc, char *argv[])
{
  my_init();
  X *x = new X(1);
  x->show();
  return 0;
}
