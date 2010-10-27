/* -*- mode: C++; c-basic-offset: 2; indent-tabs-mode: nil -*- */
/*
 *  Main authors:
 *     Yves Jaradin      <yves.jaradin@uclouvain.be>
 *     Gustavo Gutierrez <gutierrez.gustavo@uclouvain.be>
 *     Gonzalo Hernandez <gonzalohernandez@udenar.edu.co>
 *
 *  Copyright:
 *     Yves Jaradin, 2009
 *     Gustavo Gutierrez, 2009
 *     Gonzalo Hernandez, 2010
 *
 *  Last modified:
 *     $Date$ by $Author$
 *     $Revision$
 *
 *  This file is part of CP(Graph), a constraint system on graph veriables for
 *  Gecode: http://www.gecode.org  
 *
 *  Permission is hereby granted, free of charge, to any person obtaining
 *  a copy of this software and associated documentation files (the
 *  "Software"), to deal in the Software without restriction, including
 *  without limitation the rights to use, copy, modify, merge, publish,
 *  distribute, sublicense, and/or sell copies of the Software, and to
 *  permit persons to whom the Software is furnished to do so, subject to
 *  the following conditions:
 *
 *  The above copyright notice and this permission notice shall be
 *  included in all copies or substantial portions of the Software.
 *
 *  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 *  EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 *  MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 *  NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE
 *  LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION
 *  OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION
 *  WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 *
 */

namespace Gecode { 
  namespace Float {
  
    /*
     * Constructors and access
     *
     */
    
    forceinline
    ExpresionView::ExpresionView(void) {}
    
    forceinline
    ExpresionView::ExpresionView(const FloatVar& y)
      : VarViewBase<FloatVarImp>(y.var()) {}
    
    forceinline
    ExpresionView::ExpresionView(FloatVarImp* y)
      : VarViewBase<FloatVarImp>(y) {}

    forceinline
    ExpresionView::ExpresionView(Space* /*home*/, const Reflection::VarMap& vars, Reflection::Arg* arg)
      : VarViewBase<FloatVarImp>(FloatVar(vars.var(arg->toVar())).var()) {}

    /*
     * Subscribe
     *
     */

    forceinline void
    ExpresionView::subscribe(Space* home, Propagator* p, PropCond pc, bool process) {
      varimp->subscribe(home,p,pc,process);
    }

    /*
     * Cloning
     *
     */
  
    forceinline void
    ExpresionView::update(Space* home, bool share, ExpresionView& y) {
      varimp = y.varimp->copy(home,share);
    }

    /*
     * Variable information
     *
     */
    
    forceinline bool
    ExpresionView::assigned(void) const {
      return varimp->assigned();
    }
    
    /*
     * Domain update by value
     *
     */

    forceinline ModEvent
    ExpresionView::lq(Space* home,double n) {
      return varimp->lq(home,n);
    }

    forceinline ModEvent
    ExpresionView::le(Space* home,double n) {
      return varimp->le(home,n);
    }

    forceinline ModEvent
    ExpresionView::gq(Space* home,double n) {
      return varimp->gq(home,n);
    }

    forceinline ModEvent
    ExpresionView::gr(Space* home,double n) {
      return varimp->gr(home,n);
    }

    forceinline ModEvent
    ExpresionView::eq(Space* home,double n) {
      return varimp->eq(home,n);
    }

    /*
     * Value access
     *
     */

    forceinline double
    ExpresionView::min(void) const {
      return varimp->min();
    }

    forceinline double
    ExpresionView::max(void) const {
      return varimp->max();
    }

    forceinline double
    ExpresionView::med(void) const {
      return varimp->med();
    }

    /*
     * Serialization
     *
     */
    forceinline Reflection::Arg*
    ExpresionView::spec(const Space* home, Reflection::VarMap& m) const {
      return varimp->spec(home, m);
    }

    inline Support::Symbol
    ExpresionView::type(void) {
      return Support::Symbol("Gecode::Float::ExpresionView");
    }

    forceinline
    Expresion::Expresion(bool isFloatVar) : isFloatVar(isFloatVar) {
    }

    forceinline
    Operation::Operation(Space* home,Expresion &op1,Expresion &op2,char type) : Expresion(false),op1(op1),op2(op2),type(type),home(home) {
      evaluation();
    }

    forceinline
    Operation Operation::operator+(FloatVar exp) {
      ExpresionView v(exp);
      return Operation(home,*this,v,'+');
    }

    forceinline
    Operation Operation::operator+(Operation exp) {
      return Operation(home,*this,exp,'+');
    }

    forceinline Equation
    Operation::operator=(FloatVar exp) {
      ExpresionView v(exp);
      return Equation(home,*this,v);
    }

    forceinline Equation
    Operation::operator=(Operation exp) {
      return Equation(home,*this,exp);
    }

    forceinline void
    Operation::subscribe(Space* home,Propagator* p,PropCond pc) {
      //op1.subscribe(home,p,pc);
      //op2.subscribe(home,p,pc);
    }

    forceinline void
    Operation::update(Space* home,bool share,Expresion& x) {
      //Operation &o = x;
      //op1.update(home,share,o.op1);
      //op2.update(home,share,o.op2);
    }

    forceinline void
    Operation::evaluation() {
      op1.evaluation();
      op2.evaluation();
      switch(type) {
      case '+':
        eva = Interval( op1.min()+op2.min() , op1.max()+op2.max() );  break;
      }
    }

    forceinline void
    Operation::propagation(double rl,double ru) {
      double l,u;
      switch(type) {
      case '+':
        l = rl-op2.max();
        u = ru-op2.min();
        if (u<l) return;
        op1.propagation(l,u);

        l = rl-op1.max();
        u = ru-op1.min();
        if (u<l) return;
        op2.propagation(l,u);

        break;
      }
    }

    forceinline void Operation::show() {
      std::cout<<" ("; op1.show(); std::cout<<type; op2.show(); std::cout<<"["<<lower(eva)<<","<<upper(eva)<<"]) ";
    }

    /*
     * Value access
     *
     */

    forceinline double
    Operation::min(void) const {
      return lower(eva);
    }

    forceinline double
    Operation::max(void) const {
      return upper(eva);
    }

    forceinline double
    Operation::med(void) const {
      return lower(eva);
    }

    forceinline
    Equation::Equation(Space* home,Expresion& ex1,Expresion& ex2) : ex1(ex1),ex2(ex2),home(home) {
    }

    forceinline void
    Equation::subscribe(Space* home,Propagator* p,PropCond pc) {
      ex1.subscribe(home,p,pc);
      //ex2.subscribe(home,p,pc);
    }

    forceinline void
    Equation::update(Space* home,bool share,Propagator& p) {
      //ex1.update(home,share,p.ex1);
      //ex2.update(home,share,p.ex2);
    }

    forceinline void
    Equation::evaluation() {
      ex1.evaluation();
      ex2.evaluation();
    }

    forceinline void
    Equation::propagation() {
      double l = ex1.min()>ex2.min()?ex1.min():ex2.min();
      double u = ex1.max()<ex2.max()?ex1.max():ex2.max();

      if (u<l) return;

      ex1.propagation(l,u);
      ex2.propagation(l,u);
    }

    forceinline void
    Equation::show() {
      ex1.show(); std::cout<<" = "; ex2.show(); std::cout<<std::endl;
    }

  }
}
