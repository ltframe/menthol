/** \file
 * \brief Complex Data Type.
 *
 * See Copyright Notice in im_lib.h
 */

#ifndef __IM_COMPLEX_H
#define __IM_COMPLEX_H

#include "im_math.h"

/** \defgroup cpx Complex Numbers
 * \par
 * See \ref im_complex.h
 * \ingroup util
 */

/** \brief Complex Float Data Type Class 
 *         
 * \par
 * Complex class using two floats, one for real part, one for the imaginary part.
 * \par
 * It is not a complete complex class, we just implement constructors inside the class.
 * All the other operators and functions are external to the class.
 * \ingroup cpx */
template<class T>
class imComplex
{
public:
	T real;  ///< Real part.
	T imag;  ///< Imaginary part.

  ///	Default Constructor (0,0).
	imComplex():real(0), imag(0) {}

  ///	Constructor from (real, imag)
	imComplex(const T& r, const T& i):real(r),imag(i) {}

  ///	Constructor from (real)
	imComplex(const T& r):real(r),imag(0) {}
};

/** \addtogroup cpx
 * Complex numbers operators.
 * @{ 
 */

template<class T>
inline int operator <= (const imComplex<T>& C1, const imComplex<T>& C2)
{
  return ((C1.real <= C2.real) && (C1.imag <= C2.imag));
}

template<class T>
inline int operator <= (const imComplex<T>& C, const float& R)
{
  return ((C.real <= (T)R) && (C.imag <= 0));
}

template<class T>
inline int operator <= (const imComplex<T>& C, const double& R)
{
  return ((C.real <= (T)R) && (C.imag <= 0));
}

template<class T>
inline int operator < (const imComplex<T>& C1, const imComplex<T>& C2)
{
  return ((C1.real < C2.real) && (C1.imag < C2.imag));
}

template<class T>
inline int operator < (const imComplex<T>& C, const T& R)
{
  return ((C.real < R) && (C.imag < 0));
}

template<class T>
inline int operator > (const imComplex<T>& C1, const imComplex<T>& C2)
{
  return ((C1.real > C2.real) && (C1.imag > C2.imag));
}

template<class T>
inline int operator > (const imComplex<T>& C, const T& R)
{
  return ((C.real > R) && (C.imag > 0));
}

template<class T>
inline imComplex<T> operator + (const imComplex<T>& C1, const imComplex<T>& C2)
{
  return imComplex<T>(C1.real + C2.real, C1.imag + C2.imag);
}

template<class T>
inline imComplex<T> operator + (const imComplex<T>& C, const T& R)
{
  return imComplex<T>(C.real + R, C.imag);
}

template<class T>
inline imComplex<T> operator += (const imComplex<T>& C1, const imComplex<T>& C2)
{
  return imComplex<T>(C1.real + C2.real, C1.imag + C2.imag);
}

template<class T>
inline imComplex<T> operator - (const imComplex<T>& C1, const imComplex<T>& C2)
{
  return imComplex<T>(C1.real - C2.real, C1.imag - C2.imag);
}

template<class T>
inline imComplex<T> operator - (const imComplex<T>& C, const T& R)
{
  return imComplex<T>(C.real - R, C.imag);
}

template<class T>
inline imComplex<T> operator * (const imComplex<T>& C1, const imComplex<T>& C2)
{
  return imComplex<T>(C1.real * C2.real - C1.imag * C2.imag, 
                      C1.imag * C2.real + C1.real * C2.imag);
}

template<class T>
inline imComplex<T> operator / (const imComplex<T>& C1, const imComplex<T>& C2)
{
  T den = C2.real * C2.real - C2.imag * C2.imag;
  return imComplex<T>((C1.real * C2.real + C1.imag * C2.imag) / den, 
                      (C1.imag * C2.real - C1.real * C2.imag) / den);
}

template<class T>
inline imComplex<T> operator / (const imComplex<T>& C, const float& R)
{
  return imComplex<T>(C.real / (T)R, C.imag / (T)R);
}

template<class T>
inline imComplex<T> operator / (const imComplex<T>& C, const double& R)
{
  return imComplex<T>(C.real / (T)R, C.imag / (T)R);
}

template<class T>
inline imComplex<T> operator /= (const imComplex<T>& C, const float& R)
{
  return imComplex<T>(C.real / (T)R, C.imag / (T)R);
}

template<class T>
inline imComplex<T> operator /= (const imComplex<T>& C, const double& R)
{
  return imComplex<T>(C.real / (T)R, C.imag / (T)R);
}

template<class T>
inline imComplex<T> operator * (const imComplex<T>& C, const float& R)
{
  return imComplex<T>(C.real * (T)R, C.imag * (T)R);
}

template<class T>
inline imComplex<T> operator * (const imComplex<T>& C, const double& R)
{
  return imComplex<T>(C.real * (T)R, C.imag * (T)R);
}

template<class T>
inline int operator == (const imComplex<T>& C1, const imComplex<T>& C2)
{
  return ((C1.real == C2.real) && (C1.imag == C2.imag));
}

template<class T>
inline T cpxreal(const imComplex<T>& C)
{
  return C.real;
}

template<class T>
inline T cpximag(const imComplex<T>& C)
{
  return C.imag;
}

template<class T>
inline T cpxmag(const imComplex<T>& C)
{
  return sqrt(C.real*C.real + C.imag*C.imag);
}

template<class T>
inline T cpxphase(const imComplex<T>& C)
{
  return atan2(C.real, C.imag);
}

template<class T>
inline imComplex<T> cpxconj(const imComplex<T>& C)
{
  return imComplex<T>(C.real, -C.imag);
}

template<class T>
inline imComplex<T> cpxpolar(const T& mag, const T& phase)
{
  return imComplex<T>(mag * cos(phase), mag * sin(phase));
}

template<class T>
inline imComplex<T> log(const imComplex<T>& C)
{
  return imComplex<T>(log(cpxmag(C)), atan2(C.real, C.imag));
}

template<class T>
inline imComplex<T> exp(const imComplex<T>& C)
{
  T mag = exp(C.real);
  return imComplex<T>(mag * cos(C.imag), mag * sin(C.imag));
}

template<class T>
inline imComplex<T> pow(const imComplex<T>& C1, const imComplex<T>& C2)
{
  return exp(C1 * log(C2));
}

template<class T>
inline imComplex<T> pow(const imComplex<T>& C1, const T& R)
{
  imComplex<T> C2(R);
  return pow(C1, C2);
}

template<class T>
inline imComplex<T> sqrt(const imComplex<T>& C)
{
  T mag = sqrt(sqrt(C.real*C.real + C.imag*C.imag));
  T phase = atan2(C.real, C.imag) / 2;
  return imComplex<T>(mag * cos(phase), mag * sin(phase));
}

/** @} */

/** complex numbers usign 2 floats
* \ingroup cpx */
typedef imComplex<float> imcfloat;

/** complex numbers usign 2 doubles
* \ingroup cpx */
typedef imComplex<double> imcdouble;


#endif
