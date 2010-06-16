/* -*- mode: C++; c-basic-offset: 2; indent-tabs-mode: nil -*- */
/*
 *  Main authors:
 *     Gustavo Gutierrez <gutierrez.gustavo@uclouvain.be>
 *     Gonzalo Hernandez <gonzalohernandez@udenar.edu.co>
 *
 *  Copyright:
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
     * Generic propagator
     *
     */

    template <class View0,class View1,class View2>
    Generic<View0,View1,View2>::Generic(Space* home, View0 x0, View1 x1, View2 x2)
      : MixTernaryPropagator<View0,PC_FLOAT_BND,View1,PC_FLOAT_BND,View2,PC_FLOAT_BND>(home,x0,x1,x2) {
    }

    template <class View0,class View1,class View2>
    Generic<View0,View1,View2>::Generic(Space* home, bool share, Generic& pr)
      : MixTernaryPropagator<View0,PC_FLOAT_BND,View1,PC_FLOAT_BND,View2,PC_FLOAT_BND>(home,share,pr) {
    }

    template <class View0,class View1,class View2>
    Actor* Generic<View0,View1,View2>::copy(Space* home, bool share) {
      return new (home) Generic(home,share,*this);
    }

    template <class View0,class View1,class View2>
    ExecStatus Generic<View0,View1,View2>::propagate(Space* home, ModEventDelta med) {
      GECODE_ME_CHECK(x0.lq(home,x2.max()-x1.min()));
      GECODE_ME_CHECK(x0.gq(home,x2.min()-x1.max()));

      GECODE_ME_CHECK(x1.lq(home,x2.max()-x0.min()));
      GECODE_ME_CHECK(x1.gq(home,x2.min()-x0.max()));

      GECODE_ME_CHECK(x2.lq(home,x0.max()+x1.max()));
      GECODE_ME_CHECK(x2.gq(home,x0.min()+x1.min()));

      if (x0.assigned() && x1.assigned() && x2.assigned())
        return ES_SUBSUMED(this,home);
      return ES_NOFIX;
    }

    template <class View0,class View1,class View2>
    ExecStatus Generic<View0,View1,View2>::post(Space* home, View0 x, View1 y, View2 z) {
      new (home) Generic(home,x,y,z);
      return ES_OK;
    }

    /*
     * Times propagator
     *
     */

    template <class View>
    Times<View>::Times(Space* home, View x0, View x1, View x2)
      : TernaryPropagator<View,PC_FLOAT_BND>(home,x0,x1,x2) {
    }

    template <class View>
    Times<View>::Times(Space* home, bool share, Times& pr)
      : TernaryPropagator<View,PC_FLOAT_BND>(home,share,pr) {
    }

    template <class View>
    Actor* Times<View>::copy(Space* home, bool share) {
      return new (home) Times(home,share,*this);
    }

    template <class View>
    ExecStatus Times<View>::propagate(Space* home, ModEventDelta med) {
      GECODE_ME_CHECK(x0.lq(home,x2.max()/x1.min()));
      GECODE_ME_CHECK(x0.gq(home,x2.min()/x1.max()));

      GECODE_ME_CHECK(x1.lq(home,x2.max()/x0.min()));
      GECODE_ME_CHECK(x1.gq(home,x2.min()/x0.max()));

      GECODE_ME_CHECK(x2.lq(home,x0.max()*x1.max()));
      GECODE_ME_CHECK(x2.gq(home,x0.min()*x1.min()));

      if (x0.assigned() && x1.assigned() && x2.assigned())
        return ES_SUBSUMED(this,home);
      return ES_NOFIX;
    }

    template <class View>
    ExecStatus Times<View>::post(Space* home, View x, View y, View z) {
      new (home) Times(home,x,y,z);
      return ES_OK;
    }

    /*
     * Division propagator
     *
     */

    template <class View>
    Division<View>::Division(Space* home, View x0, View x1, View x2)
      : TernaryPropagator<View,PC_FLOAT_BND>(home,x0,x1,x2) {
    }

    template <class View>
    Division<View>::Division(Space* home, bool share, Division& pr)
      : TernaryPropagator<View,PC_FLOAT_BND>(home,share,pr) {
    }

    template <class View>
    Actor* Division<View>::copy(Space* home, bool share) {
      return new (home) Division(home,share,*this);
    }

    template <class View>
    ExecStatus Division<View>::propagate(Space* home, ModEventDelta med) {
      GECODE_ME_CHECK(x0.lq(home,x2.max()*x1.min()));
      GECODE_ME_CHECK(x0.gq(home,x2.min()*x1.max()));

      GECODE_ME_CHECK(x1.lq(home,x2.max()*x0.min()));
      GECODE_ME_CHECK(x1.gq(home,x2.min()*x0.max()));

      GECODE_ME_CHECK(x2.lq(home,x0.max()/x1.max()));
      GECODE_ME_CHECK(x2.gq(home,x0.min()/x1.min()));

      if (x0.assigned() && x1.assigned() && x2.assigned())
        return ES_SUBSUMED(this,home);
      return ES_NOFIX;
    }

    template <class View>
    ExecStatus Division<View>::post(Space* home, View x, View y, View z) {
      new (home) Division(home,x,y,z);
      return ES_OK;
    }

    /*
     * Power propagator
     *
     */

    template <class View>
    Power<View>::Power(Space* home, View x0, int e, View x1)
      : BinaryPropagator<View,PC_FLOAT_BND>(home,x0,x1), exp(e) {
    }

    template <class View>
    Power<View>::Power(Space* home, bool share, Power& pr)
      : BinaryPropagator<View,PC_FLOAT_BND>(home,share,pr) {
    }

    template <class View>
    Actor* Power<View>::copy(Space* home, bool share) {
      return new (home) Power(home,share,*this);
    }

    template <class View>
    ExecStatus Power<View>::propagate(Space* home, ModEventDelta med) {
      GECODE_ME_CHECK(x0.lq(home,pow(x1.max(),1.0/exp)));
      GECODE_ME_CHECK(x0.gq(home,pow(x1.min(),1.0/exp)));

      GECODE_ME_CHECK(x1.lq(home,pow(x0.max(),exp)));
      GECODE_ME_CHECK(x1.gq(home,pow(x0.min(),exp)));

      if (x0.assigned() && x1.assigned())
        return ES_SUBSUMED(this,home);
      return ES_NOFIX;
    }

    template <class View>
    ExecStatus Power<View>::post(Space* home, View x, int y, View z) {
      new (home) Power(home,x,y,z);
      return ES_OK;
    }

  }

  /*
   * Constraints
   *
   */

  void addition(Space* home, FloatVar x, FloatVar y, FloatVar z) {
    if (home->failed()) return;
    if (Float::Generic<Float::FloatView,Float::FloatView,Float::FloatView>::post(home,x,y,z) != ES_OK)
      home->fail();
  }

  void subtraction(Space* home, FloatVar x, FloatVar y, FloatVar z) {
    if (home->failed()) return;
    if (Float::Generic<Float::FloatView,Float::MinusView,Float::FloatView>::post(home,x,Float::MinusView(y),z) != ES_OK)
      home->fail();
  }

  void equal(Space* home, FloatVar x, FloatVar y) {
    if (home->failed()) return;
    if (Float::Generic<Float::ZeroView,Float::FloatView,Float::FloatView>::post(home,Float::ZeroView(),x,y) != ES_OK)
      home->fail();
  }

  void times(Space* home, FloatVar x, FloatVar y, FloatVar z) {
    if (home->failed()) return;
    if (Float::Times<Float::FloatView>::post(home,x,y,z) != ES_OK)
      home->fail();
  }

  void division(Space* home, FloatVar x, FloatVar y, FloatVar z) {
    if (home->failed()) return;
    if (Float::Division<Float::FloatView>::post(home,x,y,z) != ES_OK)
      home->fail();
  }

  void power(Space* home, FloatVar x, int y, FloatVar z) {
    if (home->failed()) return;
    if (Float::Power<Float::FloatView>::post(home,x,y,z) != ES_OK)
      home->fail();
  }

}

