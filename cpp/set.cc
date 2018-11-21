#include <set>
#include <string>
#include <iostream>

using namespace std;

int id = 0;
class Employee
{
public :
  int idNumber() const { return id_; }
  Employee()
  {
    id_ = id++;
  }
  Employee(int id)
  {
    id_ = id;
  }
  void set_title(const string& title)
  {
    title_ = title;
  }
private:
  int id_;
  string title_;
};

struct IDNumberLess : public binary_function<Employee, Employee, bool>
{
  bool operator() (const Employee& lhs, const Employee&rhs) const
  {
    return lhs.idNumber() < rhs.idNumber();
  }
};


typedef set<Employee, IDNumberLess> EmpIDSet;
EmpIDSet se;

int main(int argc, const char *argv[])
{
  Employee emp1,emp2,emp3;
  se.insert(emp1);
  se.insert(emp2);
  se.insert(emp3);
  Employee selectid(1);
  EmpIDSet::iterator it = se.find(selectid);
  //string title("Deity");
  //it->set_title(title);  //why this is failed
  /*if (emp1 > emp2)
    cout << "o~~" << endl;*/

  return 0;
}
