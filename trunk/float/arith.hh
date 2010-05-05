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

#include <float/float.hh>
#include <gecode/int.hh>

namespace Gecode {
  namespace Float {

    using namespace Gecode::Int;

    /*
     * Generic propagator
     *
     */

    template <class View0,class View1,class View2>
    class Generic : public MixTernaryPropagator<View0,PC_FLOAT_BND,View1,PC_FLOAT_BND,View2,PC_FLOAT_BND> {
    protected:
      using MixTernaryPropagator<View0,PC_FLOAT_BND,View1,PC_FLOAT_BND,View2,PC_FLOAT_BND>::x0;
      using MixTernaryPropagator<View0,PC_FLOAT_BND,View1,PC_FLOAT_BND,View2,PC_FLOAT_BND>::x1;
      using MixTernaryPropagator<View0,PC_FLOAT_BND,View1,PC_FLOAT_BND,View2,PC_FLOAT_BND>::x2;
    public:
      Generic(Space* home, View0 x0, View1 x1, View2 x2);
      Generic(Space* home, bool share, Generic& pr);
      virtual Actor* copy(Space* home, bool share);
      virtual ExecStatus propagate(Space* home, ModEventDelta med);
      static  ExecStatus post(Space* home, View0 x0, View1 x1, View2 x2);
    };
  }
}

#include <float/arith.hpp>
