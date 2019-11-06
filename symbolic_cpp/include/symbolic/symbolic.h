/*
    SymbolicC++ : An object oriented computer algebra system written in C++

    Copyright (C) 2008 Yorick Hardy and Willi-Hans Steeb

    This library is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    This library is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License along
    with this program; if not, write to the Free Software Foundation, Inc.,
    51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
*/


// symbolic.h

#ifndef SYMBOLIC_CPLUSPLUS_SYMBOLIC

#include <iostream>
#include <typeinfo>
#include <list>
using namespace std;

#ifdef  SYMBOLIC_FORWARD
#ifndef SYMBOLIC_CPLUSPLUS_SYMBOLIC_FORWARD
#define SYMBOLIC_CPLUSPLUS_SYMBOLIC_FORWARD

class CloningSymbolicInterface;
class Expanded;
class Simplified;
class Symbolic;
class SymbolicInterface;
class SymbolicProxy;

#endif
#endif

#ifdef  SYMBOLIC_DECLARE
#ifndef SYMBOLIC_CPLUSPLUS_SYMBOLIC_DECLARE
#define SYMBOLIC_CPLUSPLUS_SYMBOLIC_DECLARE

class SymbolicInterface
{
 public: int simplified, expanded;
         SymbolicInterface();
         SymbolicInterface(const SymbolicInterface&);
         virtual ~SymbolicInterface();

         virtual void print(ostream&) const = 0;
         virtual const type_info &type() const;
         virtual Symbolic subst(const Symbolic&,
                                const Symbolic&,int &n) const = 0;
         virtual Simplified simplify() const = 0;
         virtual int compare(const Symbolic&) const = 0;
         virtual Symbolic df(const Symbolic&) const = 0;
         virtual Symbolic integrate(const Symbolic&) const = 0;
         virtual Symbolic coeff(const Symbolic&) const = 0;
         virtual Expanded expand() const = 0;
         virtual int commute(const Symbolic&) const = 0;
         // match *this (as a pattern) against an expression
         virtual PatternMatches match(const Symbolic&,
                                      const list<Symbolic>&) const = 0;
         // match parts of *this (as an expression) against a pattern
         virtual PatternMatches match_parts(const Symbolic&,
                                            const list<Symbolic>&) const = 0;
};

class CloningSymbolicInterface : public SymbolicInterface, public Cloning
{
 public: CloningSymbolicInterface();
         CloningSymbolicInterface(const CloningSymbolicInterface &);
};

class SymbolicProxy: public SymbolicInterface,
                     public CastPtr<CloningSymbolicInterface>
{
 public: SymbolicProxy(const CloningSymbolicInterface&);
         SymbolicProxy(const SymbolicProxy&);
         SymbolicProxy(const Number<void>&);
         SymbolicProxy();

         void print(ostream&) const;
         const type_info &type() const;
         Symbolic subst(const Symbolic&,const Symbolic&,int &n) const;
         Simplified simplify() const;
         int compare(const Symbolic&) const;
         Symbolic df(const Symbolic&) const;
         Symbolic integrate(const Symbolic&) const;
         Symbolic coeff(const Symbolic&) const;
         Expanded expand() const;
         int commute(const Symbolic&) const;
         PatternMatches match(const Symbolic&, const list<Symbolic>&) const;
         PatternMatches match_parts(const Symbolic&,
                                      const list<Symbolic>&) const;

         SymbolicProxy &operator=(const CloningSymbolicInterface&);
         SymbolicProxy &operator=(const SymbolicProxy&);
};

class Simplified: public SymbolicProxy
{
 public: Simplified(const CloningSymbolicInterface&);
         Simplified(const SymbolicProxy&);
         Simplified(const Number<void>&);
};

class Expanded: public SymbolicProxy
{
 public: Expanded(const CloningSymbolicInterface&);
         Expanded(const SymbolicProxy&);
         Expanded(const Number<void>&);
};

class Symbolic: public SymbolicProxy
{
 public: static int auto_expand;
         static int subst_count;

         Symbolic();
         Symbolic(const Symbolic&);
         Symbolic(const CloningSymbolicInterface&);
         Symbolic(const SymbolicProxy&);
         Symbolic(const Number<void>&);
         Symbolic(const int&);
         Symbolic(const double&);
         Symbolic(const string&);
         Symbolic(const char*);
         Symbolic(const string&,int);
         Symbolic(const char*,int);
         Symbolic(const Symbolic&,int);
         Symbolic(const string&,int,int);
         Symbolic(const char*,int,int);
         Symbolic(const Symbolic&,int,int);
         Symbolic(const list<Symbolic>&);
         Symbolic(const list<list<Symbolic> >&);
         ~Symbolic();

         SymbolicProxy &operator=(const CloningSymbolicInterface&);
         SymbolicProxy &operator=(const SymbolicProxy&);
         SymbolicProxy &operator=(const int&);
         SymbolicProxy &operator=(const double&);
         SymbolicProxy &operator=(const string&);
         SymbolicProxy &operator=(const char*);
         SymbolicProxy &operator=(const list<Symbolic>&);
         SymbolicProxy &operator=(const list<list<Symbolic> >&);
         Symbolic operator[](const Equation&) const;
         Symbolic operator[](const Equations&) const;
         Symbolic operator[](const Symbolic&) const;
         Symbolic operator[](const list<Symbolic>&) const;
         Symbolic &operator()(int);
         Symbolic &operator()(int,int);
         const Symbolic &operator()(int) const;
         const Symbolic &operator()(int,int) const;
         Symbolic subst(const Symbolic&,
                        const Symbolic&,int &n=subst_count) const;
         Symbolic subst(const Symbolic&,
                        const int&,int &n=subst_count) const;
         Symbolic subst(const Symbolic&,
                        const double&,int &n=subst_count) const;
         Symbolic subst(const Equation&,int &n=subst_count) const;
         Symbolic subst(const Equations&,int &n=subst_count) const;
         Symbolic subst_all(const Symbolic&,
                            const Symbolic&,int &n=subst_count) const;
         Symbolic subst_all(const Equation&,int &n=subst_count) const;
         Symbolic subst_all(const Equations&,int &n=subst_count) const;
         Symbolic coeff(const Symbolic&) const;
         Symbolic coeff(const Symbolic&,int) const;
         Symbolic coeff(const int&) const;
         Symbolic coeff(const double&) const;

         Symbolic commutative(int) const;
         Symbolic operator~() const;
         operator int() const;
         operator double() const;

         Symbolic operator|(const Symbolic&) const;
         Symbolic operator%(const Symbolic&) const;

         int rows() const;
         int columns() const;
         Symbolic row(int) const;
         Symbolic column(int) const;
         Symbolic identity() const;
         Symbolic transpose() const;
         Symbolic trace() const;
         Symbolic determinant() const;
         Symbolic vec() const;
         Symbolic kron(const Symbolic&) const;
         Symbolic dsum(const Symbolic&) const;
         Symbolic hadamard(const Symbolic&) const;
         Symbolic inverse() const;
};

#endif
#endif

#define LIBSYMBOLICCPLUSPLUS

#ifdef  SYMBOLIC_DEFINE
#ifndef SYMBOLIC_CPLUSPLUS_SYMBOLIC_DEFINE
#define SYMBOLIC_CPLUSPLUS_SYMBOLIC_DEFINE
#define SYMBOLIC_CPLUSPLUS_SYMBOLIC

///////////////////////////////////////////////////
// Implementation for SymbolicInterface          //
///////////////////////////////////////////////////

inline SymbolicInterface::SymbolicInterface()
{ simplified = expanded = 0; }

inline SymbolicInterface::SymbolicInterface(const SymbolicInterface &s)
{ simplified = s.simplified; expanded = s.expanded; }

inline SymbolicInterface::~SymbolicInterface() {}

inline const type_info &SymbolicInterface::type() const
{ return typeid(*this); }


///////////////////////////////////////////////////
// Implementation for CloningSymbolicInterface   //
///////////////////////////////////////////////////

inline CloningSymbolicInterface::CloningSymbolicInterface()
 : SymbolicInterface(), Cloning() {}

inline CloningSymbolicInterface::CloningSymbolicInterface(
                                       const CloningSymbolicInterface &s)
 : SymbolicInterface(s), Cloning(s) {}

///////////////////////////////////////////////////
// Implementation for SymbolicProxy              //
///////////////////////////////////////////////////

inline SymbolicProxy::SymbolicProxy(const CloningSymbolicInterface &s)
 : CastPtr<CloningSymbolicInterface>(s) {}

inline SymbolicProxy::SymbolicProxy(const SymbolicProxy &s)
 : CastPtr<CloningSymbolicInterface>(s) {}

inline SymbolicProxy::SymbolicProxy(const Number<void> &n)
 : CastPtr<CloningSymbolicInterface>(n) {}

inline SymbolicProxy::SymbolicProxy() {}

inline void SymbolicProxy::print(ostream &o) const
{ (*this)->print(o); }

inline const type_info &SymbolicProxy::type() const
{ return (*this)->type(); }

inline Symbolic SymbolicProxy::subst(const Symbolic &x,
                              const Symbolic &y,int &n) const
{ return (*this)->subst(x,y,n); }

inline Simplified SymbolicProxy::simplify() const
{
 if((*this)->simplified) return *this;
 return (*this)->simplify();
}

inline int SymbolicProxy::compare(const Symbolic &s) const
{ return (*this)->compare(s); }

inline Symbolic SymbolicProxy::df(const Symbolic &s) const
{ return (*this)->df(s); }

inline Symbolic SymbolicProxy::integrate(const Symbolic &s) const
{ return (*this)->integrate(s); }

inline Symbolic SymbolicProxy::coeff(const Symbolic &s) const
{ return (*this)->coeff(s); }

inline Expanded SymbolicProxy::expand() const
{
 if((*this)->expanded) return *this;
 return (*this)->expand();
}

inline int SymbolicProxy::commute(const Symbolic &s) const
{ return (*this)->commute(s); }

inline PatternMatches
SymbolicProxy::match(const Symbolic &s, const list<Symbolic> &p) const
{ return (*this)->match(s,p); }

inline PatternMatches
SymbolicProxy::match_parts(const Symbolic &s, const list<Symbolic> &p) const
{ return (*this)->match_parts(s,p); }

inline SymbolicProxy &SymbolicProxy::operator=(const CloningSymbolicInterface &s)
{
 CastPtr<CloningSymbolicInterface>::operator=(s);
 return *this;
}

inline SymbolicProxy &SymbolicProxy::operator=(const SymbolicProxy &s)
{
 CastPtr<CloningSymbolicInterface>::operator=(s);
 return *this;
}

///////////////////////////////////////////////////
// Implementation for Simplified                 //
///////////////////////////////////////////////////

// these constructors should only be used by
// SymbolicInterface::simplify()

inline Simplified::Simplified(const CloningSymbolicInterface &s) : SymbolicProxy(s)
{ (*this)->simplified = 1; }

inline Simplified::Simplified(const SymbolicProxy &s) : SymbolicProxy(s)
{ (*this)->simplified = 1; }

inline Simplified::Simplified(const Number<void> &n) : SymbolicProxy(n)
{ (*this)->simplified = 1; }

///////////////////////////////////////////////////
// Implementation for Expanded                   //
///////////////////////////////////////////////////

// these constructors should only be used by
// SymbolicInterface::expand()

inline Expanded::Expanded(const CloningSymbolicInterface &s) : SymbolicProxy(s)
{ (*this)->expanded = 1; }

inline Expanded::Expanded(const SymbolicProxy &s) : SymbolicProxy(s)
{ (*this)->expanded = 1; }

inline Expanded::Expanded(const Number<void> &n) : SymbolicProxy(n)
{ (*this)->expanded = 1; }

///////////////////////////////////////////////////
// Implementation for Symbolic                   //
///////////////////////////////////////////////////

inline int Symbolic::auto_expand = 1;
inline int Symbolic::subst_count = 0;

inline Symbolic::Symbolic() : SymbolicProxy(Number<int>(0)) {}

inline Symbolic::Symbolic(const Symbolic &s) : SymbolicProxy(s)
{
 if(s.type() == typeid(SymbolicMatrix))
  // s is presumed const, so indexing via operator()
  // should access a copy
 {
  CastPtr<const SymbolicMatrix> csm(s);
  SymbolicProxy::operator=(*csm);
 }
}

inline Symbolic::Symbolic(const CloningSymbolicInterface &s)
{ *this = s; }

inline Symbolic::Symbolic(const SymbolicProxy &s) : SymbolicProxy(s)
{
 if(s.type() == typeid(SymbolicMatrix))
  // s is presumed const, so indexing via operator()
  // should access a copy
 {
  CastPtr<const SymbolicMatrix> csm(s);
  SymbolicProxy::operator=(*csm);
 }
}

inline Symbolic::Symbolic(const Number<void> &n) : SymbolicProxy(n) {}

inline Symbolic::Symbolic(const int &i)
 : SymbolicProxy(Number<int>(i).simplify()) {}

inline Symbolic::Symbolic(const double &d)
 : SymbolicProxy(Number<double>(d).simplify()) {}

inline Symbolic::Symbolic(const string &s)
 : SymbolicProxy(Symbol(s).simplify()) {}

inline Symbolic::Symbolic(const char *s)
 : SymbolicProxy(Symbol(s).simplify()) {}

inline Symbolic::Symbolic(const string &s,int n)
 : SymbolicProxy(SymbolicMatrix(s,n,1)) {}

inline Symbolic::Symbolic(const char *s,int n)
 : SymbolicProxy(SymbolicMatrix(s,n,1)) {}

inline Symbolic::Symbolic(const Symbolic &s,int n)
 : SymbolicProxy(SymbolicMatrix(s,n,1)) {}

inline Symbolic::Symbolic(const string &s,int n,int m)
 : SymbolicProxy(SymbolicMatrix(s,n,m)) {}

inline Symbolic::Symbolic(const char *s,int n,int m)
 : SymbolicProxy(SymbolicMatrix(s,n,m)) {}

inline Symbolic::Symbolic(const Symbolic &s,int n,int m)
 : SymbolicProxy(SymbolicMatrix(s,n,m)) {}

inline Symbolic::Symbolic(const list<Symbolic> &l)
{
 list<list<Symbolic> > ll;
 ll.push_back(l);
 (*this) = SymbolicMatrix(ll);
}

inline Symbolic::Symbolic(const list<list<Symbolic> > &l)
 : SymbolicProxy(SymbolicMatrix(l)) {}

inline Symbolic::~Symbolic() {}

inline SymbolicProxy &Symbolic::operator=(const CloningSymbolicInterface &s)
{
// cout << "*** " << &s << " " ; /*s.print(cout);*/ cout << endl;
#if 1
 if(auto_expand)
  SymbolicProxy::operator=(s.expand().simplify());
 else
#endif
  SymbolicProxy::operator=(s.simplify());
 return *this;
}

inline SymbolicProxy &Symbolic::operator=(const SymbolicProxy &s)
{ return SymbolicProxy::operator=(s); }

inline SymbolicProxy &Symbolic::operator=(const int &i)
{ return *this = Number<int>(i); }

inline SymbolicProxy &Symbolic::operator=(const double &d)
{ return *this = Number<double>(d); }

inline SymbolicProxy &Symbolic::operator=(const string &s)
{ return *this = Symbolic(s); }

inline SymbolicProxy &Symbolic::operator=(const char *s)
{ return *this = Symbolic(s); }

inline SymbolicProxy &Symbolic::operator=(const list<Symbolic> &l)
{ return *this = Symbolic(l); }

inline SymbolicProxy &Symbolic::operator=(const list<list<Symbolic> > &l)
{ return *this = Symbolic(l); }

inline Symbolic Symbolic::operator[](const Equation &p) const
{ return subst(p); }

inline Symbolic Symbolic::operator[](const Equations &l) const
{ return subst(l); }

inline Symbolic Symbolic::operator[](const Symbolic &p) const
{
 if(type() == typeid(Symbol))
  return CastPtr<const Symbol>(*this)->operator[](p);
 if(type() == typeid(SymbolicMatrix))
 {
  // make a copy of *this
  CastPtr<SymbolicMatrix> m(**this);
  int i, j;
  for(i=m->rows()-1;i>=0;i--)
   for(j=m->cols()-1;j>=0;j--)
    (*m)[i][j] = (*m)[i][j][p];
  return (*m);
 }
 return *this;
}

inline Symbolic Symbolic::operator[](const list<Symbolic> &l) const
{
 Symbolic result(*this);
 for(list<Symbolic>::const_iterator i=l.begin();i!=l.end();++i)
  result = result[*i];
 return result;
}

inline Symbolic &Symbolic::operator()(int i)
{
 if(type() != typeid(SymbolicMatrix))
 {
  if(i != 0)
  {
   cerr << "Attempted to cast " << *this
        << " in operator() to SymbolicMatrix failed." << endl;
   throw SymbolicError(SymbolicError::NotMatrix);
  }
  return *this;
 }
 CastPtr<SymbolicMatrix> m(*this);
 if(m->cols() == 1) return (*m)[i][0];
 if(m->rows() == 1) return (*m)[0][i];

 cerr << "Attempted to cast " << *this
      << " in operator() to SymbolicMatrix (vector) failed." << endl;
 throw SymbolicError(SymbolicError::NotVector);

 return *this;
}

inline Symbolic &Symbolic::operator()(int i,int j)
{
 if(type() != typeid(SymbolicMatrix))
 {
  if(i != 0 || j != 0)
  {
   cerr << "Attempted to cast " << *this
        << " in operator() to SymbolicMatrix failed." << endl;
   throw SymbolicError(SymbolicError::NotMatrix);
  }
  return *this;
 }

 CastPtr<SymbolicMatrix> m(*this);
 return (*m)[i][j];
}

inline const Symbolic &Symbolic::operator()(int i) const
{
 if(type() != typeid(SymbolicMatrix))
 {
  if(i != 0)
  {
   cerr << "Attempted to cast " << *this
        << " in operator() to SymbolicMatrix failed." << endl;
   throw SymbolicError(SymbolicError::NotMatrix);
  }
  return *this;
 }
 CastPtr<const SymbolicMatrix> m(*this);
 if(m->cols() == 1) return (*m)[i][0];
 if(m->rows() == 1) return (*m)[0][i];

 cerr << "Attempted to cast " << *this
      << " in operator() to SymbolicMatrix (vector) failed." << endl;
 throw SymbolicError(SymbolicError::NotVector);

 return *this;
}

inline const Symbolic &Symbolic::operator()(int i,int j) const
{
 if(type() != typeid(SymbolicMatrix))
 {
  if(i != 0 || j != 0)
  {
   cerr << "Attempted to cast " << *this
        << " in operator() to SymbolicMatrix failed." << endl;
   throw SymbolicError(SymbolicError::NotMatrix);
  }
  return *this;
 }

 CastPtr<const SymbolicMatrix> m(*this);
 return (*m)[i][j];
}

inline Symbolic Symbolic::subst(const Symbolic &x,const Symbolic &y,int &n) const
{ return SymbolicProxy::subst(x,y,n); }

inline Symbolic Symbolic::subst(const Symbolic &x,const int &j,int &n) const
{ return subst(x,Number<int>(j),n); }

inline Symbolic Symbolic::subst(const Symbolic &x,const double &d,int &n) const
{ return subst(x,Number<double>(d),n); }

inline Symbolic Symbolic::subst(const Equation &e,int &n) const
{
 int nsubs = 0;
 Symbolic lhs, rhs, r;
 list<Equations>::iterator i;
 // use the existing substitution for equations without binding variables
 if(e.free.empty()) return subst(e.lhs,e.rhs,n);

 PatternMatches eq = this->match_parts(e.lhs, e.free);
 for(i=eq.begin(),r=*this;i!=eq.end();++i)
 {
  lhs = e.lhs.subst(*i, nsubs);
  rhs = e.rhs.subst(*i, nsubs);
  // don't perform identity substitutions => subst_all loops infinitely
  if(lhs != rhs) r = r.subst(lhs,rhs,n);
 }
 return r;
}

inline Symbolic Symbolic::subst(const Equations &l,int &n) const
{
 Symbolic result(*this);
 for(Equations::const_iterator i=l.begin();i!=l.end();++i)
  result = result.subst(*i,n);
 return result;
}

inline Symbolic Symbolic::subst_all(const Symbolic &x,
                             const Symbolic &y,int &n) const
{
 int n1 = n;
 Symbolic r = subst(x,y,n);
 while(n != n1)
 {
  n1 = n;
  r = r.subst(x,y,n);
 }
 return r;
}

inline Symbolic Symbolic::subst_all(const Equation &e,int &n) const
{
 int n1 = n;
 Symbolic r = subst(e,n);
 while(n != n1)
 {
  n1 = n;
  r = r.subst(e,n);
 }
 return r;
}

inline Symbolic Symbolic::subst_all(const Equations &l,int &n) const
{
 int n1;
 Symbolic result(*this);
 do
 {
  n1 = n;
  for(Equations::const_iterator i=l.begin();i!=l.end();++i)
   result = result.subst(*i,n);
 } while(n != n1);

 return result;
}

inline Symbolic Symbolic::coeff(const Symbolic &s) const
{ return SymbolicProxy::coeff(s); }

inline Symbolic Symbolic::coeff(const Symbolic &s,int i) const
{
 if(i == 0) return subst(s,Number<int>(0));
 return SymbolicProxy::coeff(s^i);
}

inline Symbolic Symbolic::coeff(const int &i) const
{ return coeff(Number<int>(i)); }

inline Symbolic Symbolic::coeff(const double &d) const
{ return coeff(Number<double>(d)); }

inline Symbolic Symbolic::commutative(int c) const
{
 if(type() == typeid(Symbol))
  return CastPtr<const Symbol>(*this)->commutative(c);
 if(type() == typeid(SymbolicMatrix))
 {
  // make a copy *this
  CastPtr<SymbolicMatrix> m(**this);
  int i, j;
  for(i=m->rows()-1;i>=0;i--)
   for(j=m->cols()-1;j>=0;j--)
    (*m)[i][j] = ~ (*m)[i][j];
  return (*m);
 }
 return *this;
}

inline Symbolic Symbolic::operator~() const
{
 if(type() == typeid(Symbol))
  return CastPtr<const Symbol>(*this)->operator~();
 if(type() == typeid(SymbolicMatrix))
 {
  // make a copy of *this
  CastPtr<SymbolicMatrix> m(**this);
  int i, j;
  for(i=m->rows()-1;i>=0;i--)
   for(j=m->cols()-1;j>=0;j--)
    (*m)[i][j] = ~ (*m)[i][j];
  return (*m);
 }
 return *this;
}

inline Symbolic::operator int(void) const
{
 if(type() == typeid(Numeric) &&
    Number<void>(*this).numerictype() == typeid(int))
  return CastPtr<const Number<int> >(*this)->n;
 cerr << "Attempted to cast " << *this << " to int failed." << endl;
 throw SymbolicError(SymbolicError::NotInt);
 return 0;
}

inline Symbolic::operator double(void) const
{
 if(type() == typeid(Numeric) &&
    Number<void>(*this).numerictype() == typeid(double))
  return CastPtr<const Number<double> >(*this)->n;
 if(type() == typeid(Numeric) &&
    Number<void>(*this).numerictype() == typeid(int))
  return double(CastPtr<const Number<int> >(*this)->n);
 if(type() == typeid(Numeric) &&
    Number<void>(*this).numerictype() == typeid(Rational<Number<void> >))
 {
  CastPtr<const Number<Rational<Number<void> > > > n(*this);
  Symbolic num = n->n.num();
  Symbolic den = n->n.den();
  return double(num)/double(den);
 }
 cerr << "Attempted to cast " << *this << " to double failed." << endl;
 throw SymbolicError(SymbolicError::NotDouble);
 return 0.0;
}

inline Symbolic Symbolic::operator|(const Symbolic &s) const
{
 if(rows() != s.rows() || columns() != s.columns() ||
    (rows() != 1 && columns() != 1))
 {
  cerr << "Attempt to dot product " << *this
       << " and " << s << " failed." << endl;
  throw SymbolicError(SymbolicError::IncompatibleVector);
 }

 CastPtr<const SymbolicMatrix> m1(*this);
 CastPtr<const SymbolicMatrix> m2(s);

 if(m1->rows() == 1)
  return ((*m1)[0] | (*m2)[0]);
 else
  return ((*m1)(0) | (*m2)(0));
}

inline Symbolic Symbolic::operator%(const Symbolic &s) const
{
 if(rows() != s.rows() || columns() != s.columns() ||
    (rows() != 1 && columns() != 1))
 {
  cerr << "Attempt to cross product " << *this
       << " and " << s << " failed." << endl;
  throw SymbolicError(SymbolicError::IncompatibleVector);
 }

 CastPtr<const SymbolicMatrix> m1(*this);
 CastPtr<const SymbolicMatrix> m2(s);

 if(m1->rows() == 1)
  return SymbolicMatrix((*m1)[0] % (*m2)[0]);
 else
  return SymbolicMatrix((*m1)(0) % (*m2)(0));
}

inline int Symbolic::rows() const
{
 if(type() != typeid(SymbolicMatrix)) return 1;
 return CastPtr<const SymbolicMatrix>(*this)->rows();
}

inline int Symbolic::columns() const
{
 if(type() != typeid(SymbolicMatrix)) return 1;
 return CastPtr<const SymbolicMatrix>(*this)->cols();
}

inline Symbolic Symbolic::row(int i) const
{
 if(type() != typeid(SymbolicMatrix))
 {
   if(i == 0) return *this;
   cerr << "Attempted to cast " << *this
        << " in row() to SymbolicMatrix failed." << endl;
   throw SymbolicError(SymbolicError::NotMatrix);
 }
 Matrix<Symbolic> m = (*CastPtr<const SymbolicMatrix>(*this))[i];
 return SymbolicMatrix(m.transpose());
}

inline Symbolic Symbolic::column(int i) const
{
 if(type() != typeid(SymbolicMatrix))
 {
   if(i == 0) return *this;
   cerr << "Attempted to cast " << *this
        << " in column() to SymbolicMatrix failed." << endl;
   throw SymbolicError(SymbolicError::NotMatrix);
 }
 return SymbolicMatrix((*CastPtr<const SymbolicMatrix>(*this))(i));
}

inline Symbolic Symbolic::identity() const
{
 if(type() != typeid(SymbolicMatrix)) return Symbolic(1);
 return SymbolicMatrix(CastPtr<SymbolicMatrix>(**this)->identity());
}

inline Symbolic Symbolic::transpose() const
{
 if(type() != typeid(SymbolicMatrix)) return *this;
 return SymbolicMatrix(CastPtr<const SymbolicMatrix>(*this)->transpose());
}

inline Symbolic Symbolic::trace() const
{
 if(type() != typeid(SymbolicMatrix)) return *this;
 return CastPtr<const SymbolicMatrix>(*this)->trace();
}

inline Symbolic Symbolic::determinant() const
{
 if(type() != typeid(SymbolicMatrix)) return *this;
 return CastPtr<const SymbolicMatrix>(*this)->determinant();
}

inline Symbolic Symbolic::vec() const
{
 if(type() != typeid(SymbolicMatrix))
 {
   cerr << "Attempted to cast " << *this
        << " in vec() to SymbolicMatrix failed." << endl;
   throw SymbolicError(SymbolicError::NotMatrix);
 }
 return SymbolicMatrix(CastPtr<const SymbolicMatrix>(*this)->vec());
}

inline Symbolic Symbolic::kron(const Symbolic &s) const
{
 if(type() != typeid(SymbolicMatrix) ||
    s.type() != typeid(SymbolicMatrix))
 {
   cerr << "Attempted to cast " << *this << " or " << s
        << " in kron() to SymbolicMatrix failed." << endl;
   throw SymbolicError(SymbolicError::NotMatrix);
 }
 CastPtr<const SymbolicMatrix> m1(*this), m2(s);
 return SymbolicMatrix(m1->kron(*m2));
}

inline Symbolic Symbolic::dsum(const Symbolic &s) const
{
 if(type() != typeid(SymbolicMatrix) ||
    s.type() != typeid(SymbolicMatrix))
 {
   cerr << "Attempted to cast " << *this << " or " << s
        << " in dsum() to SymbolicMatrix failed." << endl;
   throw SymbolicError(SymbolicError::NotMatrix);
 }
 CastPtr<const SymbolicMatrix> m1(*this), m2(s);
 return SymbolicMatrix(m1->dsum(*m2));
}

inline Symbolic Symbolic::hadamard(const Symbolic &s) const
{
 if(type() != typeid(SymbolicMatrix) ||
    s.type() != typeid(SymbolicMatrix))
 {
   cerr << "Attempted to cast " << *this << " or " << s
        << " in hadamard() to SymbolicMatrix failed." << endl;
   throw SymbolicError(SymbolicError::NotMatrix);
 }
 CastPtr<const SymbolicMatrix> m1(*this), m2(s);
 return SymbolicMatrix(m1->hadamard(*m2));
}

inline Symbolic Symbolic::inverse() const
{
 if(type() != typeid(SymbolicMatrix)) return 1/(*this);
 CastPtr<const SymbolicMatrix> m(*this);
 return SymbolicMatrix(m->inverse());
}

#endif
#endif

#undef LIBSYMBOLICCPLUSPLUS

#endif
