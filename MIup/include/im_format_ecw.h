/** \file
 * \brief Register the ECW Format
 *
 * See Copyright Notice in im_lib.h
 */

#ifndef __IM_FORMAT_ECW_H
#define __IM_FORMAT_ECW_H

#if	defined(__cplusplus)
extern "C" {
#endif

/** \defgroup ecw ECW - ECW JPEG 2000
 * \section Description
 * 
 * \par
 * ECW JPEG 2000 Copyright 1998 Earth Resource Mapping Ltd.
 * Two formats are supported with this module. The ECW (Enhanced Compression Wavelet) format and the ISO JPEG 2000 format.
 * \par
 * Access to the ECW format uses the ECW JPEG 2000 SDK version 3.3. 
 * Available in Windows, Linux and Solaris Only. But source code is also available. \n
 * You must link the application with "im_ecw.lib" 
 * and you must call the function \ref imFormatRegisterECW once 
 * to register the format into the IM core library. \n
 * Depends also on the ECW JPEG 2000 SDK libraries (NCSEcw.lib).
 * \par
 * When using other JPEG 2000 libraries the first registered library will be used to guess the file format. 
 * Use the extension *.ecw to shortcut to this implementation of the JPEG 2000 format.
 * \par
 * See \ref im_format_ecw.h
 * \par
 * \par
 * http://www.ermapper.com/ecw/ \n
 * The three types of licenses available for the ECW JPEG 2000 SDK are as follows:
\verbatim
   - ECW JPEG 2000 SDK Free Use License Agreement - This license governs the free use of
     the ECW JPEG 2000 SDK with Unlimited Decompression and Limited Compression (Less
     than 500MB).
   - ECW JPEG 2000 SDK Public Use License Agreement - This license governs the use of the
     ECW SDK with Unlimited Decompression and Unlimited Compression for applications
     licensed under a GNU General Public style license.
   - ECW JPEG 2000 SDK Commercial Use License Agreement - This license governs the use
     of the ECW JPEG 2000 SDK with Unlimited Decompression and Unlimited Compression
     for commercial applications.
\endverbatim
 * 
 * \section Features
 *
\verbatim
    Data Types: Byte, Short, UShort, Float
    Color Spaces: BINARY, GRAY, RGB, YCBCR
    Compressions:
      ECW - Enhanced Compression Wavelet
      JPEG-2000 - ISO JPEG 2000  
    Only one image.
    Can have an alpha channel
    Internally the components are always packed.
    Lines arranged from top down to bottom.
    Handle() returns NCSFileView* when reading, NCSEcwCompressClient* when writing.
 
    Attributes:
      CompressionRatio   IM_FLOAT (1) [example: Ratio=7 just like 7:1]
      OriginX, OriginY   IM_FLOAT (1)
      Rotation           IM_FLOAT (1)
      CellIncrementX, CellIncrementY    IM_FLOAT (1)
      CellUnits (string)
      Datum (string)
      Projection (string)
      ViewWidth, ViewHeight                    IM_INT (1)    [view zoom]
      ViewXmin, ViewYmin, ViewXmax, ViewYmax   IM_INT (1)    [view limits]
      MultiBandCount IM_USHORT (1)    [Number of bands in a multiband gray image.]
      MultiBandSelect IM_USHORT (1)   [Band number to read one band of a multiband gray image. Must be set before reading image info.]

    Comments:
      Only read support is implemented.
      To read a region of the image you must set the View* attributes before reading the image data.
      After reading a partial image the width and height returned in ReadImageInfo is the view size.
      The view limits define the region to be read. 
      The view size is the actual size of the image, so the result can be zoomed.
\endverbatim
 * \ingroup format */
 
/** Register the ECW Format 
 * \ingroup ecw */
void imFormatRegisterECW(void);
               
               
#if defined(__cplusplus)
}
#endif

#endif
