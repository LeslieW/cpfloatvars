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

#include <set>

namespace Gecode {
  namespace Float {

    /*
     * Creation of new variable implementations
     *
     */

    forceinline
    FloatVarImp::FloatVarImp(Space* home, float lb,float ub)
      : FloatVarImpBase(home), lb(lb), ub(ub) {
    }

    /*
     * Domain tests
     *
     */

    forceinline bool
    FloatVarImp::assigned(void) const {
      return ub-lb < 0.01;
    }

    /*
     * Update domain value
     *
     */

    forceinline ModEvent
    FloatVarImp::lq(Space* home, float f) {
      if (f >= ub) return ME_FLOAT_NONE;
      if (f < lb) return ME_FLOAT_FAILED;

      ub=f;
      ModEvent me = ME_FLOAT_BND;
      if (assigned())
        me = ME_FLOAT_VAL;
      FloatDelta d;
      return notify(home,me,&d);
    }

    forceinline ModEvent
    FloatVarImp::le(Space* home,float f) {
      assert(false);
      return ME_FLOAT_NONE;
    }

    forceinline ModEvent
    FloatVarImp::gq(Space* home,float f) {
      if (f <= lb) return ME_FLOAT_NONE;
      if (f >  ub) return ME_FLOAT_FAILED;

      lb=f;
      ModEvent me = ME_FLOAT_BND;
      if (assigned())
        me = ME_FLOAT_VAL;
      FloatDelta d;
      return notify(home,me,&d);
    }

    forceinline ModEvent
    FloatVarImp::gr(Space* home,float n) {
      assert(false);
      return ME_FLOAT_NONE;
    }

    /*
     * Value access
     *
     */

    forceinline float
    FloatVarImp::min(void) const {
      return lb;
    }

    forceinline float
    FloatVarImp::max(void) const {
      return ub;
    }

    forceinline float
    FloatVarImp::med(void) const {
      return (lb+ub)/2;
    }

    /*
     * Copying a variable
     *
     */

    forceinline FloatVarImp*
    FloatVarImp::copy(Space* home, bool share) {
      return copied() ?
        static_cast<FloatVarImp*>(forward()) :
        perform_copy(home,share);
    }

    /*
     * Dependencies
     *
     */

    forceinline void
    FloatVarImp::subscribe(Space* home, Propagator* p, PropCond pc, bool process) {
      FloatVarImpBase::subscribe(home,p,pc,assigned(),process);
    }

    forceinline void
    FloatVarImp::cancel(Space* home, Propagator* p, PropCond pc) {
      FloatVarImpBase::cancel(home,p,pc,assigned());
    }
  }
}
