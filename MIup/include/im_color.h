/** \file
 * \brief Color Manipulation
 *
 * See Copyright Notice in im_lib.h
 */

#ifndef __IM_COLOR_H
#define __IM_COLOR_H

#include "im_math.h"

/** \defgroup color Color Manipulation
 *
 * \par
 * Functions to convert from one color space to another, 
 * and color gamut utilities.
 * \par
 * See \ref im_color.h
 *
 * \section s1 Some Color Science
 * \par
 * Y is luminance, a linear-light quantity. 
 * It is directly proportional to physical intensity
 * weighted by the spectral sensitivity of human vision.
 * \par
 * L* is lightness, a nonlinear luminance
 * that approximates the perception of brightness. 
 * It is nearly perceptual uniform.
 * It has a range of 0 to 100.
 * \par
 * Y' is luma, a nonlinear luminance that approximates lightness.
 * \par
 * Brightness is a visual sensation according to which an area
 * appears to exhibit more or less light. 
 * It is a subjective quantity and can not be measured.
 * \par
 * One unit of Euclidian distance in CIE L*u*v* or CIE L*a*b* corresponds
 * roughly to a just-noticeable difference (JND) of color.
 * \par
\verbatim
 ChromaUV = sqrt(u*u + v*v)       
 HueUV = atan2(v, u)
 SaturationUV = ChromaUV / L      (called psychometric saturation) 
 (the same can be calculated for Lab)
\endverbatim
 * \par
 * IEC 61966-2.1 Default RGB color space - sRGB
 * \li ITU-R Recommendation BT.709 (D65 white point).
 * \li D65 White Point (X,Y,Z) = (0.9505 1.0000 1.0890)
 * \par
 * Documentation extracted from  Charles Poynton - Digital Video and HDTV - Morgan Kaufmann - 2003.
 *
 * \section Links
 * \li www.color.org - ICC
 * \li www.srgb.com - sRGB
 * \li www.poynton.com - Charles Poynton
 * \li www.littlecms.com - A free Color Management System (use this if you need precise color conversions)
 *
 * \section cci Color Component Intervals
 * \par
 * When minimum and maximum values must be pre-defined values,
 * the following values are used:
 * \par
\verbatim
 byte   [0,255]              (1 byte)
 short  [-32768,32767]       (2 bytes)
 ushort [0,65535]            (2 bytes)
 int    [-8388608,+8388607]  (3 bytes of 4 possible)
 float  [0,1]                (4 bytes)
 double [0,1]                (8 bytes)
 \endverbatim
 * Usually this intervals are used when converting from real to integer,
 * and when demoting an integer data type.  
 * \ingroup util */

/** Returns the zero value for YCbCr color conversion. \n
 * When data type is unsigned Cb and Cr are shifted to 0-max.
 * So before they can be used in conversion equations 
 * Cb and Cr values must be shifted back to fix the zero position.
 * \ingroup color */
inline double imColorZeroShift(int data_type)
{
  double zero[] = { 128.0,     // [-128,+127]
                    0,      
                    32768.0,   // [-32768,+32767]
                    0, 
                    0, 
                    0,
                    0,
                    0 };
  return zero[data_type];
}

/** Returns the maximum value for pre-defined color conversion purposes. \n
 * See \ref cci.
 * \ingroup color */
inline int imColorMax(int data_type)
{
  int max[] = {255,      
               32767,    
               65535,    
               8388607,  
               1,        
               1,
               0,
               0 };
  return max[data_type];
}

/** Returns the minimum value for pre-defined color conversion purposes. \n
 * See \ref cci.
 * \ingroup color */
inline int imColorMin(int data_type)
{
  int min[] = {0,        
               -32768,   
               0,        
               -8388608, 
               0,        
               0,
               0,
               0 };
  return min[data_type];
}

/** Quantize 0-1 values into min-max. \n
 * Value are usually integers,
 * but the dummy quantizer uses real values.
 * See also \ref math.
 * \ingroup color */
template <class T, class R> 
inline T imColorQuantize(const R& value, const T& min, const T& max)
{
  if (max == 1) return (T)value; // to allow a dummy quantizer
  if (value >= 1) return max;
  if (value <= 0) return min;
  R range = (R)max - (R)min + (R)1;
  return (T)imRound(value*range - (R)0.5) + min;
}                               

/** Reconstruct min-max values into 0-1. \n
 * Values are usually integers,
 * but the dummy re-constructor uses real values.
 * See also \ref math.
 * \ingroup color */
template <class T>
inline double imColorReconstruct(const T& value, const T& min, const T& max)
{
  if (max == 1) return (double)value;  // to allow a dummy re-constructor
  if (value <= min) return 0;
  if (value >= max) return 1;
  double range = (double)max - (double)min + 1.0;
  return (((double)value - (double)min + 0.5) / range);
}

/** Converts Y'CbCr to R'G'B' (all nonlinear). \n
 * ITU-R Recommendation 601-1 with no headroom/footroom.
\verbatim
 0 <= Y <= 1 ; -0.5 <= CbCr <= 0.5 ; 0 <= RGB <= 1 

 R'= Y' + 0.000 *Cb + 1.402 *Cr
 G'= Y' - 0.344 *Cb - 0.714 *Cr
 B'= Y' + 1.772 *Cb + 0.000 *Cr
\endverbatim
 * \ingroup color */
template <class T> 
inline void imColorYCbCr2RGB(const T Y, const T Cb, const T Cr, 
                             T& R, T& G, T& B,
                             const T& zero, const T& min, const T& max)
{
  double r = double(Y                        + 1.402 * (Cr - zero));
  double g = double(Y - 0.344 * (Cb - zero) - 0.714 * (Cr - zero));
  double b = double(Y + 1.772 * (Cb - zero));

  // now we should enforce min <= rgb <= max
  R = (T)IM_CROPMINMAX(r, min, max);
  G = (T)IM_CROPMINMAX(g, min, max);
  B = (T)IM_CROPMINMAX(b, min, max);
}

/** Converts R'G'B' to Y'CbCr (all nonlinear). \n
 * ITU-R Recommendation 601-1 with no headroom/footroom.
\verbatim
 0 <= Y <= 1 ; -0.5 <= CbCr <= 0.5 ; 0 <= RGB <= 1 

 Y' =  0.299 *R' + 0.587 *G' + 0.114 *B'
 Cb = -0.169 *R' - 0.331 *G' + 0.500 *B'
 Cr =  0.500 *R' - 0.419 *G' - 0.081 *B'
\endverbatim
 * \ingroup color */
template <class T> 
inline void imColorRGB2YCbCr(const T R, const T G, const T B, 
                             T& Y, T& Cb, T& Cr,
                             const T& zero)
{
  Y  = (T)( 0.299 *R + 0.587 *G + 0.114 *B);
  Cb = (T)(-0.169 *R - 0.331 *G + 0.500 *B + (double)zero);
  Cr = (T)( 0.500 *R - 0.419 *G - 0.081 *B + (double)zero);
}

/** Converts C'M'Y'K' to R'G'B' (all nonlinear). \n
 * This is a poor conversion that works for a simple visualization.
\verbatim
  0 <= CMYK <= 1 ; 0 <= RGB <= 1 

  R = (1 - K) * (1 - C)
  G = (1 - K) * (1 - M)
  B = (1 - K) * (1 - Y)
\endverbatim
 * \ingroup color */
template <class T>
inline void imColorCMYK2RGB(const T C, const T M, const T Y, const T K, 
                            T& R, T& G, T& B, const T& max)
{
  T W = max - K;
  R = (T)((W * (max - C)) / max);
  G = (T)((W * (max - M)) / max);
  B = (T)((W * (max - Y)) / max);
}

/** Converts CIE XYZ to Rec 709 RGB (all linear). \n
 * ITU-R Recommendation BT.709 (D65 white point). \n
\verbatim
  0 <= XYZ <= 1 ; 0 <= RGB <= 1    

  R =  3.2406 *X - 1.5372 *Y - 0.4986 *Z
  G = -0.9689 *X + 1.8758 *Y + 0.0415 *Z
  B =  0.0557 *X - 0.2040 *Y + 1.0570 *Z
\endverbatim
 * \ingroup color */
template <class T>
inline void imColorXYZ2RGB(const T X, const T Y, const T Z, 
                           T& R, T& G, T& B)
{
  double r =  3.2406 *X - 1.5372 *Y - 0.4986 *Z;
  double g = -0.9689 *X + 1.8758 *Y + 0.0415 *Z;
  double b =  0.0557 *X - 0.2040 *Y + 1.0570 *Z;

  // we need to crop because not all XYZ colors are visible
  R = (T)IM_FLOATCROP(r);
  G = (T)IM_FLOATCROP(g);
  B = (T)IM_FLOATCROP(b);
}

/** Converts Rec 709 RGB to CIE XYZ (all linear). \n
 * ITU-R Recommendation BT.709 (D65 white point). \n
\verbatim
  0 <= XYZ <= 1 ; 0 <= RGB <= 1    

  X = 0.4124 *R + 0.3576 *G + 0.1805 *B
  Y = 0.2126 *R + 0.7152 *G + 0.0722 *B
  Z = 0.0193 *R + 0.1192 *G + 0.9505 *B
\endverbatim
 * \ingroup color */
template <class T>
inline void imColorRGB2XYZ(const T R, const T G, const T B, 
                           T& X, T& Y, T& Z)
{
  X = (T)(0.4124 *R + 0.3576 *G + 0.1805 *B);
  Y = (T)(0.2126 *R + 0.7152 *G + 0.0722 *B);
  Z = (T)(0.0193 *R + 0.1192 *G + 0.9505 *B);
}

#define IM_FWLAB(_w) (_w > 0.008856?               \
                        pow(_w, 1.0/3.0):        \
                        7.787 * _w + 0.16/1.16)

/** Converts CIE XYZ (linear) to CIE L*a*b* (nonlinear). \n
 * The white point is D65. \n
\verbatim
  0 <= L <= 1 ; -0.5 <= ab <= +0.5 ; 0 <= XYZ <= 1 

  if (t > 0.008856)
    f(t) = pow(t, 1/3)
  else
    f(t) = 7.787*t + 16/116

  fX = f(X / Xn)      fY = f(Y / Yn)      fZ = f(Z / Zn)

  L = 1.16 * fY - 0.16
  a = 2.5 * (fX - fY)
  b = (fY - fZ)

\endverbatim
 * \ingroup color */
inline void imColorXYZ2Lab(const double X, const double Y, const double Z, 
                           double& L, double& a, double& b)
{
  double fX = X / 0.9505;  // white point D65
  double fY = Y / 1.0;
  double fZ = Z / 1.0890;

  fX = IM_FWLAB(fX);
  fY = IM_FWLAB(fY);
  fZ = IM_FWLAB(fZ);

  L = 1.16 * fY - 0.16;
  a = 2.5 * (fX - fY);
  b = (fY - fZ);
}

#define IM_GWLAB(_w)  (_w > 0.20689?                     \
                         pow(_w, 3.0):                  \
                         0.1284 * (_w - 0.16/1.16))

/** Converts CIE L*a*b* (nonlinear) to CIE XYZ (linear). \n
 * The white point is D65. \n
 * 0 <= L <= 1 ; -0.5 <= ab <= +0.5 ; 0 <= XYZ <= 1 
 * \ingroup color */
inline void imColorLab2XYZ(const double L, const double a, const double b, 
                           double& X, double& Y, double& Z)

{
  double fY = (L + 0.16) / 1.16;
  double gY = IM_GWLAB(fY);

  double fgY = IM_FWLAB(gY);
  double gX = fgY + a / 2.5;
  double gZ = fgY - b;
  gX = IM_GWLAB(gX);
  gZ = IM_GWLAB(gZ);

  X = gX * 0.9505;     // white point D65
  Y = gY * 1.0;
  Z = gZ * 1.0890;
}

/** Converts CIE XYZ (linear) to CIE L*u*v* (nonlinear). \n
 * The white point is D65. \n
\verbatim
  0 <= L <= 1 ; -1 <= uv <= +1 ; 0 <= XYZ <= 1

  Y = Y / 1.0      (for D65)
  if (Y > 0.008856)
    fY = pow(Y, 1/3)
  else
    fY = 7.787 * Y + 0.16/1.16
  L = 1.16 * fY - 0.16

  U(x, y, z) = (4 * x)/(x + 15 * y + 3 * z)
  V(x, y, z) = (9 * x)/(x + 15 * y + 3 * z)
  un = U(Xn, Yn, Zn) = 0.1978      (for D65)
  vn = V(Xn, Yn, Zn) = 0.4683      (for D65)
  fu = U(X, Y, Z) 
  fv = V(X, Y, Z) 

  u = 13 * L * (fu - un)
  v = 13 * L * (fv - vn)
\endverbatim
 * \ingroup color */
inline void imColorXYZ2Luv(const double X, const double Y, const double Z, 
                           double& L, double& u, double& v)
{
  double XYZ = (double)(X + 15 * Y + 3 * Z);
  double fY = Y / 1.0;

  if (XYZ != 0)
  {
    L = 1.16 * IM_FWLAB(fY) - 0.16;
    u = 6.5 * L * ((4 * X)/XYZ - 0.1978);
    v = 6.5 * L * ((9 * Y)/XYZ - 0.4683);
  }
  else
  {
    L = u = v = 0;
  }
}

/** Converts CIE L*u*v* (nonlinear) to CIE XYZ (linear). \n
 * The white point is D65.
 * 0 <= L <= 1 ; -0.5 <= uv <= +0.5 ; 0 <= XYZ <= 1 \n
 * \ingroup color */
inline void imColorLuv2XYZ(const double L, const double u, const double v, 
                           double& X, double& Y, double& Z)

{
  double fY = (L + 0.16) / 1.16;
  Y = IM_GWLAB(fY) * 1.0;

  double ul = 0.1978, vl = 0.4683;
  if (L != 0)
  {
    ul = u / (6.5 * L) + 0.1978;
    vl = v / (6.5 * L) + 0.4683;
  }

  X = ((9 * ul) / (4 * vl)) * Y;
  Z = ((12 - 3 * ul - 20 * vl) / (4 * vl)) * Y;
}

/** Converts nonlinear values to linear values. \n
 * We use the sRGB transfer function. sRGB uses ITU-R 709 primaries and D65 white point. \n
\verbatim
  0 <= l <= 1 ; 0 <= v <= 1 

  if (v < 0.03928)
    l = v / 12.92
  else
    l = pow((v + 0.055) / 1.055, 2.4)
\endverbatim
 * \ingroup color */                           
inline double imColorTransfer2Linear(const double& nonlinear_value)
{
  if (nonlinear_value < 0.03928)
    return nonlinear_value / 12.92;
  else
    return pow((nonlinear_value + 0.055) / 1.055, 2.4);
}

/** Converts linear values to nonlinear values. \n
 * We use the sRGB transfer function. sRGB uses ITU-R 709 primaries and D65 white point. \n
\verbatim
  0 <= l <= 1 ; 0 <= v <= 1 

  if (l < 0.0031308)
    v = 12.92 * l
  else
    v = 1.055 * pow(l, 1/2.4) - 0.055
\endverbatim
 * \ingroup color */                           
inline double imColorTransfer2Nonlinear(const double& value)
{
  if (value < 0.0031308)
    return 12.92 * value;
  else
    return 1.055 * pow(value, 1.0/2.4) - 0.055;
}

/** Converts RGB (linear) to R'G'B' (nonlinear).
 * \ingroup color */
inline void imColorRGB2RGBNonlinear(const double RL, const double GL, const double BL,
                                    double& R, double& G, double& B)
{
  R = imColorTransfer2Nonlinear(RL);
  G = imColorTransfer2Nonlinear(GL);
  B = imColorTransfer2Nonlinear(BL);
}

/** Converts R'G'B' to Y' (all nonlinear). \n
\verbatim
 Y'  =  0.299 *R' + 0.587 *G' + 0.114 *B'
\endverbatim
 * \ingroup color */
template <class T> 
inline T imColorRGB2Luma(const T R, const T G, const T B)
{
  return (T)((299 * R + 587 * G + 114 * B) / 1000);
}

/** Converts Luminance (CIE Y) to Lightness (CIE L*) (all linear). \n
 * The white point is D65.
\verbatim
  0 <= Y <= 1 ; 0 <= L* <= 1

  Y = Y / 1.0      (for D65)
  if (Y > 0.008856)
    fY = pow(Y, 1/3)
  else
    fY = 7.787 * Y + 0.16/1.16
  L = 1.16 * fY - 0.16
\endverbatim
 * \ingroup color */
inline double imColorLuminance2Lightness(const double& Y)
{
  return 1.16 * IM_FWLAB(Y) - 0.16;
}

/** Converts Lightness (CIE L*) to Luminance (CIE Y) (all linear). \n
 * The white point is D65.
\verbatim
  0 <= Y <= 1 ; 0 <= L* <= 1

  fY = (L + 0.16)/1.16
  if (fY > 0.20689)
    Y = pow(fY, 3)
  else
    Y = 0.1284 * (fY - 0.16/1.16)
  Y = Y * 1.0      (for D65)
\endverbatim
 * \ingroup color */
inline double imColorLightness2Luminance(const double& L)
{
  double fY = (L + 0.16) / 1.16;
  return IM_GWLAB(fY);
}

#undef IM_FWLAB
#undef IM_GWLAB
#undef IM_CROPL
#undef IM_CROPC

#endif
