/* -*- mode: C++; c-basic-offset: 2; indent-tabs-mode: nil -*- */
/*
 *  Main authors:
 *     Gustavo Gutierrez <gutierrez.gustavo@uclouvain.be>
 *     Gonzalo Hernandez <gonzalohernandez@udenar.edu.co>
 *
 *  Copyright:
 *     Gustavo Gutierrez, 2009
 *     Gonzalo Hernadnez, 2010
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

#include <algorithm>

namespace Gecode {

  /*
   * Constructors and access
   *
   */

  forceinline
  FloatVar::FloatVar(void) {}

  forceinline
  FloatVar::FloatVar(const FloatVar& x)
  : VarBase<Float::FloatVarImp>(x.varimp) {}

  forceinline
  FloatVar::FloatVar(const Float::FloatView& x)
  : VarBase<Float::FloatVarImp>(x.var()) {}

  forceinline
  FloatVar::FloatVar(const Reflection::Var& x)
  : VarBase<Float::FloatVarImp>(x.var<Float::FloatVarImp>()) {}

  /*
   * Cloning
   *
   */

  forceinline void
  FloatVar::update(Space* home, bool share, FloatVar& y) {
    varimp = y.varimp->copy(home,share);
  }

  /*
   * Value access
   *
   */

  forceinline double
  FloatVar::min(void) const {
    return varimp->min();
  }

  forceinline double
  FloatVar::max(void) const {
    return varimp->max();
  }

  forceinline double
  FloatVar::med(void) const {
    return varimp->med();
  }

  forceinline Operation
  FloatVar::operator+(FloatVar exp) {
    return Operation(home,*this,exp,'+');
  }

  forceinline Operation
  FloatVar::operator+(Operation exp) {
    return Operation(home,*this,exp,'+');
  }

  forceinline Equation
  FloatVar::operator=(FloatVar exp) {
    return Equation(home,*this,exp);
  }

  forceinline Equation
  FloatVar::operator=(Operation exp) {
    return Equation(home,*this,exp);
  }

  forceinline void
  FloatVar::propagation(double rl,double ru) {
    //FloatView v(*this);
  }

  forceinline void
  FloatVar::show() {
    std::cout<<*this;
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
    return Operation(home,*this,exp,'+');
  }

  forceinline
  Operation Operation::operator+(Operation exp) {
    return Operation(home,*this,exp,'+');
  }

  forceinline Equation
  Operation::operator=(FloatVar exp) {
    return Equation(home,*this,exp);
  }

  forceinline Equation
  Operation::operator=(Operation exp) {
    return Equation(home,*this,exp);
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
  Equation::Equation(Space* home,Expresion &ex1,Expresion &ex2) : ex1(ex1),ex2(ex2),home(home) {
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
