#include<iostream>
using namespace std;

class person{
  public:
    string name;
    bool sex;
    string gender;
    void set_gender(){
      if(sex) gender = "male";
      else gender = "female";
    }

};

int main(){
  person Amit;
  Amit.name = "Amit Yadav";
  Amit.sex = 1;
  // Amit.gender = "Male";
  Amit.set_gender();

  cout<<Amit.name<<endl<<Amit.sex<<endl<<Amit.gender<<endl;

}
