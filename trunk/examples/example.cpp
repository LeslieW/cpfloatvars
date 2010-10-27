#include <gecode/float/float.hh>
#include <gecode/float/branch.hh>
#include <gecode/float/arith.hh>
#include <gecode/search.hh>

using namespace Gecode;

class Example : public Space {
private:
  FloatVar x,y,z;
public:

  Example() : x(this,0.0,4.0), y(this,2.0,9.0), z(this,1.5,3.5) {
    //hc4(this, x=y );
    addition(this,x,y,z);
    branch(this,x);
    branch(this,y);
    branch(this,z);
  }
  
  Example(bool share,Example& example) : Space(share,example) {
    x.update(this,share,example.x);
    y.update(this,share,example.y);
    z.update(this,share,example.z);
  }
  
  Example* copy(bool share) {
    return new Example(share,*this);
  }
  
  void print() {
    std::cout<<x<<y<<z<<std::endl;
  }

};

int main() {
  Example *example = new Example;
  DFS<Example> engine(example);
  delete example;
  Example* solution = engine.next();
  solution->print();
  delete solution;

  return 0;
}
