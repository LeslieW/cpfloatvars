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

#ifndef __GECODE_FLOAT_BRANCH_HH__
#define __GECODE_FLOAT_BRANCH_HH__

#include <float/float.hh>

/**
 * \namespace Gecode::Float::Branch
 * \brief %Float branchings
 */
namespace Gecode {
  namespace Float {
    namespace Branch {
      
      /// %Branching description
      class FloatBranchingDesc : public BranchingDesc {
      private:
        /// Value stored in the branching description.
        float value;
      public:
        /**
         * \brief Initialize description from branching \a b 
         * and float \a f.
         */ 
        FloatBranchingDesc(const Branching* b, const unsigned int a, float v);
        /// Returns the float stored by the description
        size_t size(void) const;
        float val(void) const;
      };
      
      template <bool inc>
      class FloatBranching : public Branching {
      private:
        /// Float variable being branched
        FloatView f;
      protected:
        /// Copy constructor
        FloatBranching(Space* home, bool share, FloatBranching& b);
      public:
        /// Initialize from a float view
        FloatBranching(Space* home, FloatView& f);
        /// Returns the status of the branching
        bool status(const Space* home) const;
        /// Returns the description of the branching
        const Gecode::BranchingDesc* description(const Space* home) const;
        /// Commit for branching description \a d
        ExecStatus commit(Space* home, const BranchingDesc* d, unsigned int a);
        /// Perform cloning
        Actor* copy(Space* home, bool share);        
      };
    }
  }
}

#include <float/branch/branch.hpp>
#endif
