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

#ifndef __GECODE_FLOAT_HH__
#define __GECODE_FLOAT_HH__

#include <gecode/kernel.hh>

// linking support
#include <float/config.hh>

// Variable implementation
#include <float/var-imp.hpp>

namespace Gecode {  
  namespace Float {
    class FloatView;
  }

  /**
   * \brief Float variables.
   *
   * \ingroup CpFloatVars
   */  
  class FloatVar : public VarBase<Float::FloatVarImp> {
    friend std::ostream& operator <<(std::ostream& os, const FloatVar& x);
  private:
    using VarBase<Float::FloatVarImp>::varimp;
  public:
    
    /// \name Constructors and initialization
    //@{
    /// Default constructor
    FloatVar(void);
    /// Initialize from graph variable \a x
    FloatVar(const FloatVar& x);
    /// Initialize from graph variable \a x
    FloatVar(const Float::FloatView& x);
    /**
     * \brief Initialize with an empty lower bound and a full upper
     * bound of order \a n.
     *
     * The resulting upper bound will be \f$A\times A \f$, with \f$ A
     * = \{0,\ldots,n\}\f$.
     */
    GECODE_FLOAT_EXPORT
    FloatVar(Space* home, double lb, double ub, float pr=0.01);
    //@}

    /// \name Cloning
    //@{
    /// Update this variable to be a clone of variable \a x
    void update(Space* home, bool share, FloatVar& x);
    //@}
    
    /// \name Value access
    //@{
    // Return minimun of domain 
    double min(void) const;
    // Return maximun of domain
    double max(void) const;
    // Return median of domain
    double med(void) const;
    //@}
  };
  
  /**
   * \brief Branch over variable \a g
   *
   * If \a inc is true then the left decision is to include an edge
   * and the right one is to exclude it. If \a inc is false the left
   * decision is to exclude an edge and the right one is to include
   * it.
   *
   * \ingroup CpRelBranchers
   */
  GECODE_FLOAT_EXPORT void
  branch(Space* home, FloatVar& f);
  //@}
}

#include <float/view.hpp>

#endif
