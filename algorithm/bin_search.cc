/*
g++ bin_search.cc -o bin_search
infnum and supnum are included
1、found or not is return
2、last position is returned. last position means biggest less than key
*/
#include <assert.h>
#include <iostream>
#include <string.h>

using namespace std;

bool
bin_search(int *array, int size, int key, int *pos)
{
  assert(size >= 0);

  int high = size + 1;
  int low = 0;
  int mid = 0;
  bool found = false;
  int *array2 = new int[size + 2];
  memcpy(array2 + 1, array, size * sizeof(int));
  array2[0] = array[0] - 1;
  array2[size + 1] = array[size - 1] + 1;
  while ((low + 1) < high)
  {
    mid = (low + high) / 2;
    if (array2[mid] > key)
    {
      high = mid;
    }
    else if (array2[mid] < key)
    {
      low = mid;
    }
    else
    {
      *pos = mid - 1;
      found = true;
      break;
    }
  }
  cout << "low " << low << ".mid " << mid << ".high " << high << endl;
  if (!found)
    *pos = low - 1;
  delete array2;
  return found;
}

void verify()
{
  int arr[] = {8, 34, 87, 98, 122, 366, 985, 1024, 1025};
  bool found = false;
  int pos = -1;
  int key = 88;
  found = bin_search(arr, sizeof(arr) / sizeof(int), key, &pos);
  if (found)
    cout << "found.";
  else
    cout << "not found.";
  cout << "key is " << key << ". pos is " << pos << endl;

  key = 9;
  found = bin_search(arr, sizeof(arr) / sizeof(int), key, &pos);
  if (found)
    cout << "found.";
  else
    cout << "not found.";
  cout << "key is " << key << ". pos is " << pos << endl;

  key = 985;
  found = bin_search(arr, sizeof(arr) / sizeof(int), key, &pos);
  if (found)
    cout << "found.";
  else
    cout << "not found.";
  cout << "key is " << key << ". pos is " << pos << endl;

  key = 1026;
  found = bin_search(arr, sizeof(arr) / sizeof(int), key, &pos);
  if (found)
    cout << "found.";
  else
    cout << "not found.";
  cout << "key is " << key << ". pos is " << pos << endl;

  key = 7;
  found = bin_search(arr, sizeof(arr) / sizeof(int), key, &pos);
  if (found)
    cout << "found.";
  else
    cout << "not found.";
  cout << "key is " << key << ". pos is " << pos << endl;
}

bool
bin_search_no_cp(int *array, int size, int key, int *pos)
{
  assert(size >= 0);

  int high = size;
  int low = -1;
  int mid;

  bool found = false;
  while ((low + 1) < high)
  {
    mid = (low + high) / 2;
    if (array[mid] > key)
    {
      high = mid;
    }
    else if (array[mid] < key)
    {
      low = mid;
    }
    else
    {
      *pos = mid;
      found = true;
      break;
    }
  }
  cout << "low " << low << ".mid " << mid << ".high " << high << endl;
  if (!found)
    *pos = low;
  return found;
}

void
verify_no_cp()
{
  int arr[] = {8, 34, 87, 98, 122, 366, 985, 1024, 1025};
  bool found = false;
  int pos = -1;
  int key = 88;
  found = bin_search_no_cp(arr, sizeof(arr) / sizeof(int), key, &pos);
  if (found)
    cout << "found.";
  else
    cout << "not found.";
  cout << "key is " << key << ". pos is " << pos << endl;

  key = 9;
  found = bin_search_no_cp(arr, sizeof(arr) / sizeof(int), key, &pos);
  if (found)
    cout << "found.";
  else
    cout << "not found.";
  cout << "key is " << key << ". pos is " << pos << endl;

  key = 985;
  found = bin_search_no_cp(arr, sizeof(arr) / sizeof(int), key, &pos);
  if (found)
    cout << "found.";
  else
    cout << "not found.";
  cout << "key is " << key << ". pos is " << pos << endl;

  key = 1026;
  found = bin_search_no_cp(arr, sizeof(arr) / sizeof(int), key, &pos);
  if (found)
    cout << "found.";
  else
    cout << "not found.";
  cout << "key is " << key << ". pos is " << pos << endl;

  key = 7;
  found = bin_search_no_cp(arr, sizeof(arr) / sizeof(int), key, &pos);
  if (found)
    cout << "found.";
  else
    cout << "not found.";
  cout << "key is " << key << ". pos is " << pos << endl;
}

bool
bin_search_no_inf_sup(int *array, int size, int key, int *pos)
{
  //infnum and supnum is convinient, why 
  assert(size >= 0);

  int high = size - 1;
  int low = 0;
  int mid = low;
  bool found = false;

  while (low < high)
  {
    mid = (low + high) / 2;
    if (array[mid] > key)
    {
      high = mid;
    }
    else if (array[mid] < key)
    {
      low = mid;
    }
    else
    {
      *pos = mid;
      found = true;
      break;
    }
  }
  cout << "low " << low << ".mid " << mid << ".high " << high << endl;
  if (!found)
    *pos = low;
  return found;
}

int main(int argc, const char *argv[])
{
  verify();
  cout << "==========" << endl;
  verify_no_cp();

  return 0;
}
