/** \file
 * \brief Math Utilities
 *
 * See Copyright Notice in im_lib.h
 */

#ifndef __IM_MATH_H
#define __IM_MATH_H

#include <math.h>
#include "im_util.h"

#ifdef IM_DEFMATHFLOAT
inline float acosf(float _X) {return ((float)acos((double)_X)); }
inline float asinf(float _X) {return ((float)asin((double)_X)); }
inline float atanf(float _X) {return ((float)atan((double)_X)); }
inline float atan2f(float _X, float _Y) {return ((float)atan2((double)_X, (double)_Y)); }
inline float ceilf(float _X) {return ((float)ceil((double)_X)); }
inline float cosf(float _X)  {return ((float)cos((double)_X)); }
inline float coshf(float _X) {return ((float)cosh((double)_X)); }
inline float expf(float _X) {return ((float)exp((double)_X)); }
inline float fabsf(float _X) {return ((float)fabs((double)_X)); }
inline float floorf(float _X) {return ((float)floor((double)_X)); }
inline float fmodf(float _X, float _Y) {return ((float)fmod((double)_X, (double)_Y)); }
inline float logf(float _X) {return ((float)log((double)_X)); }
inline float log10f(float _X) {return ((float)log10((double)_X)); }
inline float powf(float _X, float _Y) {return ((float)pow((double)_X, (double)_Y)); }
inline float sinf(float _X) {return ((float)sin((double)_X)); }
inline float sinhf(float _X) {return ((float)sinh((double)_X)); }
inline float sqrtf(float _X) {return ((float)sqrt((double)_X)); }
inline float tanf(float _X) {return ((float)tan((double)_X)); }
inline float tanhf(float _X) {return ((float)tanh((double)_X)); }
#endif

/** \defgroup math Math Utilities
 * \par
 * When converting between continuous and discrete use: \n
 * Continuous = Discrete + 0.5         [Reconstruction/Interpolation] \n
 * Discrete = Round(Continuous - 0.5)  [Sampling/Quantization] \n
 * \par
 * Notice that must check min-max limits when converting from Continuous to Discrete.
 * \par
 * When converting between discrete and discrete use: \n
 * integer src_size, dst_len, src_i, dst_i            \n
 * real factor = (real)(dst_size)/(real)(src_size)    \n
 * dst_i = Round(factor*(src_i + 0.5) - 0.5)
 * \par
 * See \ref im_math.h
 * \ingroup util */


/** Round a real to the nearest integer.
 * \ingroup math */
inline int imRound(float x) 
{
  return (int)(x < 0? x-0.5f: x+0.5f);
}
inline int imRound(double x) 
{
  return (int)(x < 0? x-0.5: x+0.5);
}

template <class T>
inline T imAbs(const T& v)
{
  if (v < 0)
    return -1*v;
  return v;
}

/** Converts between two discrete grids.
 * factor is "dst_size/src_size".
 * \ingroup math */
inline int imResampleInt(int x, double factor)
{
  double xr = factor*(x + 0.5) - 0.5;
  return (int)(xr < 0? xr-0.5: xr+0.5);  /* Round */
}

/** Does Zero Order Decimation (Mean).
 * \ingroup math */
template <class T, class TU>
inline T imZeroOrderDecimation(int width, int height, T *map, double xl, double yl, double box_width, double box_height, TU Dummy)
{
  int x0,x1,y0,y1;
  (void)Dummy;

  x0 = (int)floor(xl - box_width/2.0 - 0.5) + 1;
  y0 = (int)floor(yl - box_height/2.0 - 0.5) + 1;
  x1 = (int)floor(xl + box_width/2.0 - 0.5);
  y1 = (int)floor(yl + box_height/2.0 - 0.5);

  if (x0 == x1) x1++;
  if (y0 == y1) y1++;

  x0 = x0<0? 0: x0>width-1? width-1: x0;
  y0 = y0<0? 0: y0>height-1? height-1: y0;
  x1 = x1<0? 0: x1>width-1? width-1: x1;
  y1 = y1<0? 0: y1>height-1? height-1: y1;

  TU Value;
  int Count = 0;

  Value = 0;

  for (int y = y0; y <= y1; y++)
  {
    for (int x = x0; x <= x1; x++)
    {
      Value += map[y*width+x];
      Count++;
    }
  }

  if (Count == 0)
  {
    Value = 0;
    return (T)Value;
  }

  return (T)(Value/double(Count));
}

/** Does Bilinear Decimation.
 * \ingroup math */
template <class T, class TU>
inline T imBilinearDecimation(int width, int height, T *map, double xl, double yl, double box_width, double box_height, TU Dummy)
{
  int x0,x1,y0,y1;
  (void)Dummy;

  x0 = (int)floor(xl - box_width/2.0 - 0.5) + 1;
  y0 = (int)floor(yl - box_height/2.0 - 0.5) + 1;
  x1 = (int)floor(xl + box_width/2.0 - 0.5);
  y1 = (int)floor(yl + box_height/2.0 - 0.5);

  if (x0 == x1) x1++;
  if (y0 == y1) y1++;

  x0 = x0<0? 0: x0>width-1? width-1: x0;
  y0 = y0<0? 0: y0>height-1? height-1: y0;
  x1 = x1<0? 0: x1>width-1? width-1: x1;
  y1 = y1<0? 0: y1>height-1? height-1: y1;

  TU Value, LineValue;
  double dxr, dyr;
  double LineNorm, Norm;

  Value = 0;
  Norm = 0;

  for (int y = y0; y <= y1; y++)
  {
    dyr = yl - (y+0.5);
    if (dyr < 0) dyr *= -1;

    LineValue = 0;
    LineNorm = 0;

    for (int x = x0; x <= x1; x++)
    {
      dxr = xl - (x+0.5);
      if (dxr < 0) dxr *= -1;

      LineValue += map[y*width+x] * dxr;
      LineNorm += dxr;
    }

    Value += LineValue * dyr;
    Norm += dyr * LineNorm;
  }

  if (Norm == 0)
  {
    Value = 0;
    return (T)Value;
  }

  return (T)(Value/Norm);
}

/** Does Zero Order Interpolation (Nearest Neighborhood).
 * \ingroup math */
template <class T>
inline T imZeroOrderInterpolation(int width, int height, T *map, double xl, double yl)
{
  int x0 = imRound(xl-0.5);
  int y0 = imRound(yl-0.5);
  x0 = x0<0? 0: x0>width-1? width-1: x0;
  y0 = y0<0? 0: y0>height-1? height-1: y0;
  return map[y0*width + x0];
}

/** Does Bilinear Interpolation.
 * \ingroup math */
template <class T>
inline T imBilinearInterpolation(int width, int height, T *map, double xl, double yl)
{
  int x0, y0, x1, y1;
  double t, u;

  if (xl < 0.5)
  {
    x1 = x0 = 0; 
    t = 0;
  }
  else if (xl >= width-0.5)
  {
    x1 = x0 = width-1;
    t = 0;
  }
  else
  {
    x0 = (int)(xl-0.5);
    x1 = x0+1;
    t = xl - (x0+0.5);
  }

  if (yl < 0.5)
  {
    y1 = y0 = 0; 
    u = 0;
  }
  else if (yl >= height-0.5)
  {
    y1 = y0 = height-1;
    u = 0;
  }
  else
  {
    y0 = (int)(yl-0.5);
    y1 = y0+1;
    u = yl - (y0+0.5);
  }

  T fll = map[y0*width + x0];
  T fhl = map[y0*width + x1];
  T flh = map[y1*width + x0];
  T fhh = map[y1*width + x1];

  return (T)((fhh - flh - fhl + fll) * u * t +
                         (fhl - fll) * t +
                         (flh - fll) * u +
                                fll);
}

/** Does Bicubic Interpolation.
 * \ingroup math */
template <class T, class TU>
inline T imBicubicInterpolation(int width, int height, T *map, double xl, double yl, TU Dummy)
{
  int X[4], Y[4];
  double t, u;
  (void)Dummy;

  if (xl >= width-0.5)
  {
    X[3] = X[2] = X[1] = width-1;
    X[0] = X[1]-1;
    t = 0;
  }
  else
  {
    X[1] = (int)(xl-0.5);
    if (X[1] < 0) X[1] = 0;

    X[0] = X[1]-1;
    X[2] = X[1]+1;
    X[3] = X[1]+2;

    if (X[0] < 0) X[0] = 0;
    if (X[3] > width-1) X[3] = width-1;

    t = xl - (X[1]+0.5);
  }

  if (yl >= height-0.5)
  {
    Y[3] = Y[2] = Y[1] = height-1;
    Y[0] = Y[1]-1;
    u = 0;
  }
  else
  {
    Y[1] = (int)(yl-0.5);
    if (Y[1] < 0) Y[1] = 0;

    Y[0] = Y[1]-1;
    Y[2] = Y[1]+1;
    Y[3] = Y[1]+2;

    if (Y[0] < 0) Y[0] = 0;
    if (Y[3] > height-1) Y[3] = height-1;

    u = yl - (Y[1]+0.5);
  }

  double CX[4], CY[4];

  // Optimize calculations
  {
    double c, c2, c3;

#define C0 (-c3 + 2.0f*c2 - c)
#define C1 ( c3 - 2.0f*c2 + 1.0)
#define C2 (-c3 + c2 + c)
#define C3 ( c3 - c2)

    c = t;
    c2 = c*c; c3 = c2*c;
    CX[0] = C0; CX[1] = C1; CX[2] = C2; CX[3] = C3;

    c = u;
    c2 = c*c; c3 = c2*c;
    CY[0] = C0; CY[1] = C1; CY[2] = C2; CY[3] = C3;

#undef C0
#undef C1
#undef C2
#undef C3
  }

  TU LineValue, Value;
  double LineNorm, Norm;

  Value = 0;
  Norm = 0;

  for (int y = 0; y < 4; y++)
  {
    LineValue = 0;
    LineNorm = 0;

    for (int x = 0; x < 4; x++)
    {
      LineValue += map[Y[y]*width+X[x]] * CX[x];
      LineNorm += CX[x];
    }

    Value += LineValue * CY[y];
    Norm += CY[y] * LineNorm;
  }

  if (Norm == 0)
  {
    Value = 0;
    return (T)Value;
  }

  Value = (Value/Norm);

  int size = sizeof(T); 
  if (size == 1)
    return (T)(Value<=(TU)0? (TU)0: Value<=(TU)255? Value: (TU)255);
  else
    return (T)(Value);
}

/** Calculates minimum and maximum values.
 * \ingroup math */
template <class T> 
inline void imMinMax(const T *map, int count, T& min, T& max, int absolute = 0)
{
  if (absolute)
    min = imAbs(map[0]);
  else
    min = map[0];

  max = min;
  for (int i = 1; i < count; i++)
  {
    T value;
    if (absolute)
      value = imAbs(map[i]);
    else
      value = map[i];

    if (value > max)
      max = value;
    else if (value < min)
      min = value;
  }
}

/** Calculates minimum and maximum values 
 * with additional considerations for data type conversion and normalized operations.
 * \ingroup math */
template <class T> 
inline void imMinMaxType(const T *map, int count, T& min, T& max, int absolute = 0)
{
  int size_of = sizeof(imbyte);
  if (sizeof(T) == size_of)
  {
    /* for imbyte is always the maximum interval */
    min = 0;
    max = 255;
  }
  else
  {
    imMinMax(map, count, min, max, absolute);

    /* if equal define a minimum interval */
    if (min == max)
    {
      max = min + 1;

      if (min != 0)
        min = min - 1;
    }
  }
}

#endif
