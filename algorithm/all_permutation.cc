#include <vector>
#include <iostream>

using namespace std;

typedef vector<int> ivct;
typedef vector<ivct> prmut_vct;

prmut_vct
gen_prmut(vector<int> v)
{
  int size = v.size();
  prmut_vct result;
  if (size == 2)
  {
    //递归终止
    ivct row1, row2;
    row1.push_back(v[0]);
    row1.push_back(v[1]);
    row2.push_back(v[1]);
    row2.push_back(v[0]);
    result.push_back(row1);
    result.push_back(row2);
    return result;
  }

  for (int i = 0; i < size; i++)
  {
    ivct v2 = v;
    //构造递归数组
    v2.erase(v2.begin() + i);
    prmut_vct r = gen_prmut(v2);
    int size2 = r.size();
    for (int j = 0; j < size2; j++)
    {
      vector<int> row;
      row.push_back(v[i]);
      row.insert(row.end(),r[j].begin(), r[j].end());
      result.push_back(row);
    }
  }

  return result;
}

void test_gen_prmut()
{
  ivct v;
  v.push_back(1); v.push_back(2); v.push_back(3); v.push_back(4);
  prmut_vct r = gen_prmut(v);
  int size = r.size();
  for (int i = 0; i < size; i++)
  {
    ivct row = r[i];
    for (int j = 0; j < row.size(); j++)
    {
      cout << row[j] << " ";
    }
    cout << endl;
  }
}

/*
  任何递归都可以通过for的方式进行优化，避免函数调用所产生的开销
*/
void
gen_prmut_opt(int v[], int size)
{
  //
}

int main(int argc, char *argv[])
{
  test_gen_prmut();
  return 0;
}
