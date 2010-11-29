#include <gecode/float/float.hh>
#include <gecode/float/branch.hh>
#include <gecode/float/arith.hh>
#include <gecode/search.hh>

using namespace Gecode;

class Example : public Space {
private:
  FloatVarArray f;
public:

  Example() : f(this, 3 , 1.0 , 2.0) {
      FloatVar x(f[0]), y(f[1]), z(f[2]);
      hc4(this, x+y=z );
//    branch(this,x);
//    branch(this,y);
//    branch(this,z);
  }
  
  Example(bool share,Example& example) : Space(share,example) {
    f.update(this,share,example.f);
  }
  
  Example* copy(bool share) {
    return new Example(share,*this);
  }
  
  void print() {
    std::cout<<f<<std::endl;
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
