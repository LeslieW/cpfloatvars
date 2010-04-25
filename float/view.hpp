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

#include <iostream>

namespace Gecode { 
  namespace Float {
    
    /**
     * \defgroup TaskActorFloatView Float views
     *
     * Views provides an interface for propagators and branchings to variable
     * implementations.
     */

    /**
     * \brief Float view for float variables
     * \ingroup TaskActorFloatView
     */

    class FloatView : public VarViewBase<FloatVarImp> {
    protected:
      using VarViewBase<FloatVarImp>::varimp;
    public:

      /// \name Constructor and initialization
      //@{
      /// Default constructor
      FloatView(void);
      /// Initialize from float variable x
      FloatView(const FloatVar& x);
      /// Initialize from float variable x
      FloatView(FloatVarImp* x);
      //@}

      /// \name Cloning
      //@{
      /// Update this view to be a clone of view \a x
      void update(Space* home, bool share, FloatView& x);
      //@}

      /// \name Variable information
      //@{
      /// Verify if domain is done
      bool assigned(void) const;
      //@}

      /// \name Domain update by value
      //@{
      /// Restrict domain values to be less or equal than \a n
      ModEvent lq(Space* home, double n);
      /// Restrict domain values to be less than \a n
      ModEvent le(Space* home, double n);
      /// Restrict domain values to be greater or equal than \a n
      ModEvent gq(Space* home, double n);
      /// Restrict domain values to be greater than \a n
      ModEvent gr(Space* home, double n);
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
  }


  template<>
  class ViewVarImpTraits<Float::FloatView> {
  public:
    /// The variable type of an IntView
    typedef Float::FloatVarImp VarImp;
  };

  namespace Float {

    class MinusView : public DerivedViewBase<FloatView> {
    protected:
      using DerivedViewBase<FloatView>::view;
    public:

      /// \name Constructor and initialization
      //@{
      /// Default constructor
      MinusView(void);
      /// Initialize from float variable x
      MinusView(const FloatView& x);
      //@}

      /// \name Cloning
      //@{
      /// Update this view to be a clone of view \a x
      void update(Space* home, bool share, MinusView& x);
      //@}

      /// \name Variable information
      //@{
      /// Verify if domain is done
      bool assigned(void) const;
      //@}

      /// \name Domain update by value
      //@{
      /// Restrict domain values to be less or equal than \a n
      ModEvent lq(Space* home, double n);
      /// Restrict domain values to be less than \a n
      ModEvent le(Space* home, double n);
      /// Restrict domain values to be greater or equal than \a n
      ModEvent gq(Space* home, double n);
      /// Restrict domain values to be greater than \a n
      ModEvent gr(Space* home, double n);
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

  }
}

#include <float/var/float.hpp>
#include <float/view/float.hpp>

#include <float/view/print.hpp>
#include <float/var/print.hpp>

#include <float/view/minus.hpp>
