/** \file
 * \brief Math Operations
 *
 * See Copyright Notice in im_lib.h
 */

#ifndef __IM_MATH_OP_H
#define __IM_MATH_OP_H

#include "im_complex.h"


/// Crop value to Byte limit
template <class T>
inline T crop_byte(const T& v)
{
  return v < 0? 0: v > 255? 255: v;
}

////////////////////////////////////////////////////////////////////////////////////

/// Generic Addition with 2 template types
template <class T1, class T2>
inline T1 add_op(const T1& v1, const T2& v2)
{
  return v1 + v2;
}

////////////////////////////////////////////////////////////////////////////////////

/// Generic Subtraction with 2 template types
template <class T1, class T2>
inline T1 sub_op(const T1& v1, const T2& v2)
{
  return v1 - v2;
}

////////////////////////////////////////////////////////////////////////////////////

/// Generic Multiplication with 2 template types
template <class T1, class T2>
inline T1 mul_op(const T1& v1, const T2& v2)
{
  return v1 * v2;
}

////////////////////////////////////////////////////////////////////////////////////

/// Generic Division with 2 template types
template <class T1, class T2>
inline T1 div_op(const T1& v1, const T2& v2)
{
  return v1 / v2;
}

////////////////////////////////////////////////////////////////////////////////////

/// Generic Invert
template <class T>
inline T inv_op(const T& v)
{
  return T(1)/v;
}

////////////////////////////////////////////////////////////////////////////////////

/// Generic Difference with 2 template types
template <class T1, class T2>
inline T1 diff_op(const T1& v1, const T2& v2)
{
  T1 sub = v1 - v2;
  if (sub < T1(0))
    return T1(-1)*sub;
  return sub;
}

////////////////////////////////////////////////////////////////////////////////////

/// Generic Minimum with 2 template types
template <class T1, class T2>
inline T1 min_op(const T1& v1, const T2& v2)
{
  if (v1 < v2)
    return v1;
  return v2;
}

////////////////////////////////////////////////////////////////////////////////////

/// Generic Maximum with 2 template types
template <class T1, class T2>
inline T1 max_op(const T1& v1, const T2& v2)
{
  if (v1 < v2)
    return v2;
  return v1;
}

////////////////////////////////////////////////////////////////////////////////////

inline int ipow(int base, int exp)
{
  int result = 1;
  while (exp)
  {
    if (exp & 1)
      result *= base;
    exp >>= 1;
    base *= base;
  }
  return result;
}

inline imbyte pow_op(const imbyte& v1, const imbyte& v2)
{
  return (imbyte)ipow((int)v1, (int)v2);
}

inline imushort pow_op(const imushort& v1, const imushort& v2)
{
  return (imushort)ipow((int)v1, (int)v2);
}

inline short pow_op(const short& v1, const short& v2)
{
  return (short)ipow((int)v1, (int)v2);
}

inline int pow_op(const int& v1, const int& v2)
{
  return ipow(v1, v2);
}

/// Generic Power with 2 template types
template <class T1, class T2>
inline T1 pow_op(const T1& v1, const T2& v2)
{
  return (T1)pow(v1, v2);
}

////////////////////////////////////////////////////////////////////////////////////

/// Generic Absolute
template <class T>
inline T abs_op(const T& v)
{
  if (v < T(0))
    return T(-1)*v;
  return v;
}

////////////////////////////////////////////////////////////////////////////////////

/// Generic Less
template <class T>
inline T less_op(const T& v)
{
  return T(-1)*v;
}

////////////////////////////////////////////////////////////////////////////////////

/// Generic Square
template <class T>
inline T sqr_op(const T& v)
{
  return v*v;
}

////////////////////////////////////////////////////////////////////////////////////

inline unsigned int isqrt(unsigned int number)
{
#define ISQRT_NEXT(n, i)  (((n) + (i)/(n)) >> 1)
  unsigned int n = 1;
  unsigned int n1 = ISQRT_NEXT(n, number);

  while (imAbs((int)(n1 - n)) > 1) {
    n = n1;
    n1 = ISQRT_NEXT(n, number);
  }
  while (n1*n1 > number)
    n1--;
#undef ISQRT_NEXT
  return n1;
}

inline int sqrt(const int& v)
{
  if (v < 0)
    return 0;
  return (int)isqrt(v);
}

/// Generic Square Root
template <class T>
inline T sqrt_op(const T& v)
{
  return (T)sqrt(v);
}

////////////////////////////////////////////////////////////////////////////////////

inline int exp(const int& v)
{
  return (int)exp((double)v);
}

/// Generic Exponential
template <class T>
inline T exp_op(const T& v)
{
  return (T)exp(v);
}

////////////////////////////////////////////////////////////////////////////////////

inline int log(const int& v)
{
  return (int)log((double)v);
}

/// Generic Logarithm
template <class T>
inline T log_op(const T& v)
{
  return (T)log(v);
}

////////////////////////////////////////////////////////////////////////////////////

// Dummy sin
inline imcfloat sin(const imcfloat& v)
{
  return (v);
}
inline imcdouble sin(const imcdouble& v)
{
  return (v);
}

inline int sin(const int& v)
{
  return (int)sin((double)v);
}

/// Generic Sine
template <class T>
inline T sin_op(const T& v)
{
  return (T)sin(v);
}

////////////////////////////////////////////////////////////////////////////////////

// Dummy cos
inline imcfloat cos(const imcfloat& v)
{
  return (v);
}
inline imcdouble cos(const imcdouble& v)
{
  return (v);
}

inline int cos(const int& v)
{
  return (int)cos((double)v);
}

/// Generic Cosine
template <class T>
inline T cos_op(const T& v)
{
  return (T)cos(v);
}

////////////////////////////////////////////////////////////////////////////////////

/// Sets a bit in an array
inline void imDataBitSet(imbyte* data, int index, int bit)
{
  if (bit)
    data[index / 8] |=  (0x01 << (7 - (index % 8)));
  else
    data[index / 8] &= ~(0x01 << (7 - (index % 8)));
}

/// Gets a bit from an array
inline int imDataBitGet(imbyte* data, int index)
{
  return (data[index / 8] >> (7 - (index % 8))) & 0x01;
}

#endif
