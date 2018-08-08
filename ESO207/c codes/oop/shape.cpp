// https://erlerobotics.gitbooks.io/erle-robotics-cpp-gitbook/object-oriented_programming__oop_and_inheritance/exercises_oop.html

#include<iostream>
using namespace std;

class shape{
protected:
  int height;
  int width;
public:
  void make_shape(int w, int h){
    width = w;
    height = h;
  }
};
class rectangle : public shape{
public:
  int area(){
    return height*width;
  }
};

class traingle : public shape{
public:
  int area(){
    return 1.0/2*height*width;
  }
};



int main(){
  rectangle rect;
  traingle tri;
  rect.make_shape(2,4);
  tri.make_shape(2,4);
  cout<<rect.area()<<endl;
  cout<<tri.area()<<endl;
}
