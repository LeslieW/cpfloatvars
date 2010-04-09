#include <float/float.hh>
#include <float/branch.hh>
#include <gecode/search.hh>

using namespace Gecode;

class Example : public Space {
private:
  FloatVar dom;
public:
  Example() : dom(this , 0.0 , 1.0) {
    branch(this,dom);
  }
  
  Example(bool share,Example& example) : Space(share,example) {
    dom.update(this,share,example.dom);
  }
  
  Example* copy(bool share) {
    return new Example(share,*this);
  }
  
  void print() {
    std::cout<<dom;
  }
};

int main() {
  Example *example = new Example;
  DFS<Example> engine(example);
  delete example;
  while (Example* solution = engine.next()) {
      solution->print();
      delete solution;
  }

  return 0;
}
