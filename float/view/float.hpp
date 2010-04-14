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
    FloatView::FloatView(void) {}
    
    forceinline
    FloatView::FloatView(const FloatVar& y)
      : VarViewBase<FloatVarImp>(y.var()) {}
    
    forceinline
    FloatView::FloatView(FloatVarImp* y)
      : VarViewBase<FloatVarImp>(y) {}
    
    /*
     * Cloning
     *
     */
  
    forceinline void
    FloatView::update(Space* home, bool share, FloatView& y) {
      varimp = y.varimp->copy(home,share);
    }

    /*
     * Variable information
     *
     */
    
    forceinline bool
    FloatView::assigned(void) const {
      return varimp->assigned();
    }
    
    /*
     * Domain update by value
     *
     */

    forceinline ModEvent
    FloatView::lq(Space* home,double n) {
      return varimp->lq(home,n);
    }

    forceinline ModEvent
    FloatView::le(Space* home,double n) {
      return varimp->le(home,n);
    }

    forceinline ModEvent
    FloatView::gq(Space* home,double n) {
      return varimp->gq(home,n);
    }

    forceinline ModEvent
    FloatView::gr(Space* home,double n) {
      return varimp->gr(home,n);
    }

    /*
     * Value access
     *
     */

    forceinline double
    FloatView::min(void) const {
      return varimp->min();
    }

    forceinline double
    FloatView::max(void) const {
      return varimp->max();
    }

    forceinline double
    FloatView::med(void) const {
      return varimp->med();
    }
  }
}
