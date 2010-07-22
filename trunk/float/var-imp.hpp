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

#include <boost/numeric/interval.hpp>

namespace Gecode {
  namespace Float {
    
    class FloatVarImp;
    /**
     * \brief Float variable information for advisors
     *
     * \todo This is here because is needed by notify in the tell operations. A
     * proper implementation has to be done when real advisor support becomes
     * implemented.
     */
    class FloatDelta : public Delta {
      friend class FloatVarImp;
    public:
      /// Create set delta as providing no information
      FloatDelta(void);
    };
  }
}

#include <float/var-imp/delta.hpp>

namespace Gecode {
  namespace Float {

    /// Exception: empty domain
    class GECODE_VTABLE_EXPORT EmptyDomain : public Exception {
    public:
      EmptyDomain(const char* l) : Exception(l, "Empty domain") {}
    };
    
    /**
     * \brief Implementation of graph variables.
     */
    class FloatVarImp : public FloatVarImpBase {
    private:
      typedef boost::numeric::interval<double> Interval;

      /// Interval with lower and upper bound
      Interval dom;
      /// Precision of calculation
      float prec;

      // prevent the compiler to generate a default cc
      FloatVarImp(const FloatVarImp& x);
    protected:
      /// Constructor for cloning \a x
      FloatVarImp(Space* home, bool share, FloatVarImp& x);
    public:
      
      /// \name Constructors
      //@{
      /// Creates a variable with \a lb and \a ub
      FloatVarImp(Space* home, double lb, double ub, float pr=0.001);
      //@}

      /// \name Dependencies
      //@{
      /**
       * \brief Subscribe propagator \a p with propagation condition \a pc to
       * variable
       *
       * In case \a process is false, the propagator is just subscribed but
       * not processed for execution (this must be used when creating
       * subscriptions during propagation).
       */
      void subscribe(Space* home, Propagator* p, PropCond pc, bool process=true);
      /// Cancel subscription of propagator \a p with propagation condition \a pc
      void cancel(Space* home, Propagator* p, PropCond pc);
      /// Subscribe advisor \a a to variable
      //void subscribe(Space& home, Advisor& a);
      /// Cancel subscription of advisor \a a
      //void cancel(Space& home, Advisor& a);
      //@}

    private:
      /// Return copy of not-yet copied variable
      GECODE_FLOAT_EXPORT FloatVarImp* perform_copy(Space* home, bool share);

    public:
      
      /// \name Domain test
      //@{
      /// Veriry if Domain is done
      bool assigned(void) const;
      //@}

      /// \name Update domain by value
      //@{
      /// Restrict domain values to be less or equal than \a n
      ModEvent lq(Space* home,double n);
      /// Restrict domain values to be less than \a n
      ModEvent le(Space* home,double n);
      /// Restrict domain values to be great or equal than \a n
      ModEvent gq(Space* home,double n);
      /// Restrict domain values to be great than \a n
      ModEvent gr(Space* home,double n);
      /// Restrict domain values to be equal to \a n
      ModEvent eq(Space* home,double n);
      //@}

      /// \name Value access
      //@{
      /// Return minimun of domain
      double min(void) const;
      /// Return maximun of domain
      double max(void) const;
      /// Return medium of domain
      double med(void) const;
      /// Return precision
      float precision(void) const;
      //@}

      /// \name Cloning
      //@{
      /// Return copy of this variable
      FloatVarImp* copy(Space* home, bool share);
      //@}

      /// \name Reflection
      //@{
      /// Return specification
      GECODE_FLOAT_EXPORT Reflection::Arg*
      spec(const Space* home, Reflection::VarMap& m) const;
      /// Create variable implementation from specification
      //@}

    };
  }
}

#include <float/var-imp/float-imp.hpp>
#include <float/var-imp/iter.hpp>
