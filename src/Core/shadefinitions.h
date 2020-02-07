#ifndef DEFINITIONS_H
#define DEFINITIONS_H
#include <vector>
#include <utility>

/*
 * Removes copy and assignment operators
 * explicitly from a class definition
 */
#define NO_COPY_ASSIGNMENT_CTORS(THIS_CLASS)\
   THIS_CLASS( const       THIS_CLASS&  src ) = delete;\
   THIS_CLASS& operator= ( THIS_CLASS&  src ) = delete;\
   THIS_CLASS(             THIS_CLASS&& src ) = delete;\
   THIS_CLASS& operator= ( THIS_CLASS&& src ) = delete;

typedef long double ldouble;
typedef std::pair<ldouble, ldouble> pairLDouble;
typedef std::vector<double> vecD;
typedef std::vector<std::vector<double> > matD;

#endif // DEFINITIONS_H
