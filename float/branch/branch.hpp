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

namespace Gecode { namespace Float { namespace Branch {
  forceinline
  FloatBranchingDesc::FloatBranchingDesc(const Branching* b,const unsigned int a,float v)
    : BranchingDesc(b,a) , value(v) {}

  forceinline size_t
  FloatBranchingDesc::size(void) const {
    return sizeof(FloatBranchingDesc);
  }

  forceinline float
  FloatBranchingDesc::val(void) const {
    return value;
  }

  /*
   * \FloatBranching
   *
   */

  template <bool inc>
  forceinline
  FloatBranching<inc>::FloatBranching(Space* home, bool share, FloatBranching& b)
    : Branching(home, share, b) {
    f.update(home, share, b.f);
  }

  template <bool inc>
  forceinline
  FloatBranching<inc>::FloatBranching(Space* home, FloatView& f)
    : Branching(home), f(f) {
  }

  template <bool inc>
  forceinline bool
  FloatBranching<inc>::status(const Space* home) const {
    return !f.assigned();
  }

  template <bool inc>
  forceinline ExecStatus
  FloatBranching<inc>::commit(Space* home, const BranchingDesc* d, unsigned int a) {
    std::cout<<"Opcion: "<<a;
    const FloatBranchingDesc *bd = dynamic_cast<const FloatBranchingDesc*>(d);
    if ((a == 0) == inc) {
      return me_failed(f.lq(home, bd->val())) ? ES_FAILED : ES_OK;
    }
    return me_failed(f.gq(home, bd->val())) ? ES_FAILED : ES_OK;
  }

  template <bool inc>
      forceinline Actor*
      FloatBranching<inc>::copy(Space* home, bool share) {
        return new (home) FloatBranching(home, share, *this);
      }

      template <bool inc>
      forceinline const Gecode::BranchingDesc*
      FloatBranching<inc>::description(const Space* home) const {
        return new FloatBranchingDesc(this , 2, f.med());
      }

    }
  }

  forceinline void
  branch(Space* home, FloatVar& f) {
    if (home->failed()) return;
    Float::FloatView fv(f);
    (void) new (home) Float::Branch::FloatBranching<true>(home,fv);
  }
}
