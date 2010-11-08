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
      /// Initialize from specification
      FloatView(Space* home, const Reflection::VarMap& vars, Reflection::Arg* arg);
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
      /// Restrict domain values to be equal to \a n
      ModEvent eq(Space* home, double n);
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

      /// \name Reflection
      //@{
      /// Return specification for this view, using variable map \a m
      Reflection::Arg* spec(const Space* home, Reflection::VarMap& m) const;
      static Support::Symbol type(void);
      //@}
    };
  }

  namespace Float {

    /**
     * \brief Expresion view for float variables int hc tree algorith
     * \ingroup TaskActorExpresionView
     */
    class Operation;
    class Equation;

    class Expresion {
    protected:
      typedef boost::numeric::interval<double> Interval;
    public:
      /// \name Value access
      //@{
      // Return minimun of domain
      virtual double min(void) const {};
      // Return maximun of domain
      virtual double max(void) const {};
      // Return median of domain
      virtual double med(void) const {};
      //@}

      virtual void subscribe(Space* home,Propagator* p,PropCond pc,bool process=true) {};
      virtual void update(Space* home,bool share,Expresion& x) {};
      virtual void evaluation() {};
      virtual void propagation(double l,double u) {}
      virtual void show() {};
    };

    class ExpresionView : public VarViewBase<FloatVarImp>,public Expresion {
    protected:
      using VarViewBase<FloatVarImp>::varimp;
    public:

      /// \name Constructor and initialization
      //@{
      /// Default constructor
      ExpresionView(void);
      /// Initialize from float variable x
      ExpresionView(const FloatVar& x);
      /// Initialize from float variable x
      ExpresionView(FloatVarImp* x);
      /// Initialize from specification
      ExpresionView(Space* home, const Reflection::VarMap& vars, Reflection::Arg* arg);
      //@}

      ~ExpresionView() {
        std::cout<<"killed";
      }

      /// \name Subscribe
      //@{
      /// Subscribe this view
      void subscribe(Space* home, Propagator* p,PropCond pc,bool process=true);
      //@}

      /// \name Cloning
      //@{
      /// Update this view to be a clone of view \a x
      void update(Space* home, bool share, ExpresionView& x);
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
      /// Restrict domain values to be equal to \a n
      ModEvent eq(Space* home, double n);
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

      /// \name Reflection
      //@{
      /// Return specification for this view, using variable map \a m
      Reflection::Arg* spec(const Space* home, Reflection::VarMap& m) const;
      static Support::Symbol type(void);
      //@}
    };

    class Operation : public Expresion {
    private:
      Expresion &op1,&op2;
      char type;
      Interval eva;
      Space* home;
    public:
      Operation(Space* home,Expresion &op1,Expresion &op2,char type);
      Operation operator+(FloatVar exp);
      Operation operator+(Operation exp);
      Equation  operator=(FloatVar exp);
      Equation  operator=(Operation exp);

      /// \name Value access
      //@{
      // Return minimun of domain
      double min(void) const;
      // Return maximun of domain
      double max(void) const;
      // Return median of domain
      double med(void) const;
      //@}

      void subscribe(Space* home,Propagator* p,PropCond pc);
      void update(Space* home,bool share,Expresion& x);
      void evaluation();
      void propagation(double l,double u);
      void show();
    };

    class Equation {
    private:
      Space* home;
      Expresion &ex1,&ex2;
    public:
      Equation(Space* home,Expresion &ex1,Expresion &ex2);
      void subscribe(Space* home,Propagator* p,PropCond pc);
      void update(Space* home,bool share,Propagator& p);
      void evaluation();
      void propagation();
      void show();
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

      /// \name Dependencies
      //@{
      // Subscribe propagator
      void subscribe(Space* home, Propagator* p, PropCond pc, bool process=true);
      // Cancel subscription or propagator
      void cancel(Space* home, Propagator* p, PropCond pc);
      //@}
    };

  }

  namespace Float {

      class ZeroView : public ConstViewBase {
      public:

        /// \name Constructor and initialization
        //@{
        /// Default constructor
        ZeroView(void);
        //@}

        /// \name Cloning
        //@{
        /// Update this view to be a clone of view \a x
        void update(Space* home, bool share, ZeroView& x);
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

        /// \name Dependencies
        //@{
        // Subscribe propagator
        void subscribe(Space* home, Propagator* p, PropCond pc, bool process=true);
        // Cancel subscription or propagator
        void cancel(Space* home, Propagator* p, PropCond pc);
        //@}
      };

    }
}

#include <gecode/float/view/float.hpp>
#include <gecode/float/view/print.hpp>
#include <gecode/float/view/minus.hpp>
#include <gecode/float/view/zero.hpp>
#include <gecode/float/view/expresion.hpp>

#include <gecode/float/var/float.hpp>
#include <gecode/float/var/print.hpp>
