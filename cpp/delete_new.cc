/*
改写delete和new存在的风险在于，stl模板也使用了new/delete的调用方式
因此改写可能会影响到stl的执行结果
如下堆栈展示了从map中删除数据使用重载的delete进行操作
#0  operator delete (ptr=0x606030) at /home/jiangyx/dp-hotdb/dp3/htp_rr/htp_mem.cc:129
#1  0x0000000000402dda in __gnu_cxx::new_allocator<std::_Rb_tree_node<std::pair<void* const, int> > >::deallocate (this=0x605160 <mem_map>, __p=0x606030)
    at /usr/include/c++/4.8.2/ext/new_allocator.h:110
#2  0x0000000000402552 in std::_Rb_tree<void*, std::pair<void* const, int>, std::_Select1st<std::pair<void* const, int> >, std::less<void*>, std::allocator<std::pair<void* const, int> > >::_M_put_node (this=0x605160 <mem_map>, __p=0x606030)
    at /usr/include/c++/4.8.2/bits/stl_tree.h:374
#3  0x000000000040212f in std::_Rb_tree<void*, std::pair<void* const, int>, std::_Select1st<std::pair<void* const, int> >, std::less<void*>, std::allocator<std::pair<void* const, int> > >::_M_destroy_node (this=0x605160 <mem_map>, __p=0x606030)
    at /usr/include/c++/4.8.2/bits/stl_tree.h:396
#4  0x0000000000401e03 in std::_Rb_tree<void*, std::pair<void* const, int>, std::_Select1st<std::pair<void* const, int> >, std::less<void*>, std::allocator<std::pair<void* const, int> > >::_M_erase (this=0x605160 <mem_map>, __x=0x606030)
    at /usr/include/c++/4.8.2/bits/stl_tree.h:1127
#5  0x00000000004031a9 in std::_Rb_tree<void*, std::pair<void* const, int>, std::_Select1st<std::pair<void* const, int> >, std::less<void*>, std::allocator<std::pair<void* const, int> > >::clear (this=0x605160 <mem_map>) at /usr/include/c++/4.8.2/bits/stl_tree.h:860
#6  0x0000000000402d18 in std::_Rb_tree<void*, std::pair<void* const, int>, std::_Select1st<std::pair<void* const, int> >, std::less<void*>, std::allocator<std::pair<void* const, int> > >::_M_erase_aux (this=0x605160 <mem_map>, __first=..., __last=...)
    at /usr/include/c++/4.8.2/bits/stl_tree.h:1757
#7  0x0000000000402455 in std::_Rb_tree<void*, std::pair<void* const, int>, std::_Select1st<std::pair<void* const, int> >, std::less<void*>, std::allocator<std::pair<void* const, int> > >::erase (this=0x605160 <mem_map>, __first=..., __last=...)
    at /usr/include/c++/4.8.2/bits/stl_tree.h:848
#8  0x0000000000401f8c in std::_Rb_tree<void*, std::pair<void* const, int>, std::_Select1st<std::pair<void* const, int> >, std::less<void*>, std::allocator<std::pair<void* const, int> > >::erase (this=0x605160 <mem_map>, __x=@0x7fffffffe360: 0x606010)
    at /usr/include/c++/4.8.2/bits/stl_tree.h:1771
#9  0x0000000000401c9b in std::map<void*, int, std::less<void*>, std::allocator<std::pair<void* const, int> > >::erase (this=0x605160 <mem_map>, __x=@0x7fffffffe360: 0x606010)
    at /usr/include/c++/4.8.2/bits/stl_map.h:727
#10 0x000000000040189f in Mem_map::remove (this=0x605160 <mem_map>, ptr=0x606010)
    at /home/jiangyx/dp-hotdb/dp3/htp_rr/htp_mem.cc:38
#11 0x00000000004015dc in operator delete (ptr=0x606010)
    at /home/jiangyx/dp-hotdb/dp3/htp_rr/htp_mem.cc:129
#12 0x00000000004013dd in main (argc=1, argv=0x7fffffffe4d8)
    at /home/jiangyx/dp-hotdb/dp3/plugin/htp_relayer/htp_mem_test.cc:28

*/

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
  static void operator delete(void* ptr, bool b)
  {
    std::cout << "custom placement delete called, b = " << b << '\n';
    ::operator delete(ptr);
  }
 private :
  int i_;
};

void *operator new(size_t size, int id)
{
  stop_for_dbg(3);
  return malloc(size);
}

void operator delete(void *p, const char *file, int line)
{
  stop_for_dbg(5);
  free(p);
}

void operator delete(void *p, int flag)
{
  if (flag)
    stop_for_dbg(5);
  else
    stop_for_dbg(6);
  free(p);
}

//for release
//#define new(id) new

int main(int argc, char *argv[])
{
  my_init();
  X *x = new(1) X(1);
  x->show();
  ::delete(__LINE__, __FILE__, x);
  //delete (1, x);
  return 0;
}
