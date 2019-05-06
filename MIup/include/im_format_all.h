/** \file
 * \brief All the Internal File Formats.
 * They are all automatically registered by the library.
 * The signatures are in C, but the functions are C++.
 * Header for internal use only.
 *
 * See Copyright Notice in im_lib.h
 */

#ifndef __IM_FORMAT_ALL_H
#define __IM_FORMAT_ALL_H

#if	defined(__cplusplus)
extern "C" {
#endif

/** \defgroup tiff TIFF - Tagged Image File Format
 * \section Description
 *
 * \par
 * Copyright (c) 1986-1988, 1992 by Adobe Systems Incorporated. \n
 * Originally created by a group of companies,
 * the Aldus Corporation keeped the copyright until Aldus was aquired by Adobe. \n
 * TIFF Revision 6.0 Final — June 3, 1992 \n
 * http://www.adobe.com/Support/TechNotes.html
 * \par
 * Access to the TIFF file format uses libTIFF version 4.0.3 \n
 * http://www.remotesensing.org/libtiff/                     \n
 * Copyright (c) 1988-1997 Sam Leffler                      \n
 * Copyright (c) 1991-1997 Silicon Graphics, Inc.           \n
 *
 * \section Features
 *
\verbatim
    Data Types: <all>
    Color Spaces: Gray, RGB, CMYK, YCbCr, Lab, XYZ, Map and Binary.
    Compressions:
      NONE - no compression  [default for IEEE Floating Point Data]
      CCITTRLE - CCITT modified Huffman RLE (binary only) [default for Binary]
      CCITTFAX3 - CCITT Group 3 fax         (binary only)
      CCITTFAX4 - CCITT Group 4 fax         (binary only)
      LZW - Lempel-Ziv & Welch  [default]
      JPEG - ISO JPEG    [default for YCBCR]
      NEXT - NeXT 2-bit RLE (2 bpp only)
      CCITTRLEW - CCITT modified Huffman RLE with word alignment (binary only)
      RLE - Packbits (Macintosh RLE) [default for MAP]
      THUNDERSCAN - ThunderScan 4-bit RLE (only for 2 or 4 bpp)
      PIXARLOG - Pixar companded 11-bit ZIP (only byte, ushort and float)
      DEFLATE - LZ77 variation (ZIP)
      ADOBE_DEFLATE - Adobe LZ77 variation
      SGILOG - SGI Log Luminance RLE for L and Luv (only byte, ushort and float) [default for XYZ]
      SGILOG24 - SGI Log 24-bit packed for Luv (only byte, ushort and float)
    Can have more than one image.
    Can have an alpha channel.
    Components can be packed or not.
    Lines arranged from top down to bottom or bottom up to top.
    Handle(1) returns a TIFF* libTIFF structure.

    Attributes:
      Photometric IM_USHORT (1) (when writing this will complement the color_mode information, for Mask, MinIsWhite, ITULab and ICCLab)
      ExtraSampleInfo IM_USHORT (1) (description of alpha channel: 0- uknown, 1- pre-multiplied, 2-normal)
      JPEGQuality IM_INT (1) [0-100, default 75] (write only)
      ZIPQuality IM_INT (1) [1-9, default 6] (write only)
      ResolutionUnit (string) ["DPC", "DPI"]
      XResolution, YResolution IM_FLOAT (1)
      Description, Author, Copyright, DateTime, DocumentName,
      PageName, TargetPrinter, Make, Model, Software, HostComputer (string)
      InkNames (strings separated by '0's)
      InkSet IM_USHORT (1)
      NumberOfInks IM_USHORT (1)
      DotRange IM_USHORT (2)
      TransferFunction0, TransferFunction1, TransferFunction3 IM_USHORT [gray=0, rgb=012]
      ReferenceBlackWhite IMFLOAT (6)
      WhitePoint IMFLOAT (2)
      PrimaryChromaticities  IMFLOAT (6)
      YCbCrCoefficients IM_FLOAT (3)
      YCbCrSubSampling IM_USHORT (2)
      YCbCrPositioning IM_USHORT (1)
      PageNumber IM_USHORT (2)
      StoNits IM_DOUBLE (1)
      XPosition, YPosition IM_FLOAT (1)
      SMinSampleValue, SMaxSampleValue IM_FLOAT (1)
      HalftoneHints IM_USHORT (2)
      SubfileType IM_INT (1)
      ICCProfile IM_BYTE (N)
      MultiBandCount IM_USHORT (1)    [Number of bands in a multiband gray image.]
      MultiBandSelect IM_USHORT (1)   [Band number to read one band of a multiband gray image. Must be set before reading image info.]
      and other TIFF tags as they are described in the TIFF documentation.
      GeoTIFF tags:
        GeoTiePoints, GeoTransformationMatrix, "Intergraph TransformationMatrix", GeoPixelScale, GeoDoubleParams IM_DOUBLE (N)
        GeoASCIIParams (string)
      Read-only support for EXIF tags as they are described in the EXIF 2.2 documentation. See http://www.exif.org/
      DNG tags as they are described in the DNG documentation. See http://www.adobe.com/br/products/dng/
        Tags BlackLevel, DefaultCropOrigin and DefaultCropSize are incorrectly interpreted by libTIFF so they are ignored.
        Raw image is loaded in place of the thumbnail image in the main IFD.
        SubIFDCount IM_USHORT (1)    [Number of subifds of the current image.]
        SubIFDSelect IM_USHORT (1)   [Subifd number to be read. Must be set before reading image info.]
      (other attributes can be obtained by using libTIFF directly using the Handle(1) function)

    Comments:
      LogLuv is in fact Y'+CIE(u,v), so we choose to always convert it to XYZ.
      SubIFD is handled only for DNG.
      Since LZW patent expired, LZW compression is enabled. LZW Copyright Unisys.
      libGeoTIFF can be used without XTIFF initialization. Use Handle(1) to obtain a TIFF*.

    Changes:
      "tiff_jpeg.c" - commented "downsampled_output = TRUE" and downsampled_input = TRUE.
      "tiff_fax3.c" - replaced "inline" by "INLINE"
      "tif_strip.c" - fixed scanline_size
      New files "tif_config.h" and "tifconf.h" to match our needs.
      New file "tiff_binfile.c" that implement I/O rotines using imBinFile.
      Search for "IMLIB" to see the changes.
\endverbatim
 * \ingroup format */
void imFormatRegisterTIFF(void);


/** \defgroup jpeg JPEG - JPEG File Interchange Format
 * \section Description
 *
 * \par
 * ISO/IEC 10918 (1994, 1995, 1997, 1999)\n
 * http://www.jpeg.org/
 * \par
 * Access to the JPEG file format uses libjpeg version 8c. \n
 * http://www.ijg.org                                      \n
 * Copyright (C) 1994-2011, Thomas G. Lane, Guido Vollbeding  \n
 *   from the Independent JPEG Group.
 * \par
 * Access to the EXIF attributes uses libEXIF version 0.6.20. \n
 * http://sourceforge.net/projects/libexif                    \n
 * Copyright (C) 2001-2010, Lutz Müller
 *
 * \section Features
 *
\verbatim
    Data Types: Byte
    Color Spaces: Gray, RGB, CMYK and YCbCr (Binary Saved as Gray)
    Compressions:
      JPEG - ISO JPEG  [default]
    Only one image.
    No alpha channel.
    Internally the components are always packed.
    Internally the lines are arranged from top down to bottom.
    Handle(1) returns jpeg_decompress_struct* when reading, and
                      jpeg_compress_struct* when writing (libJPEG structures).

    Attributes:
      AutoYCbCr IM_INT (1) (controls YCbCr auto conversion) default 1
      JPEGQuality IM_INT (1) [0-100, default 75] (write only)
      ResolutionUnit (string) ["DPC", "DPI"]
      XResolution, YResolution IM_FLOAT (1)
      Interlaced (same as Progressive) IM_INT (1 | 0) default 0
      Description (string)
      (lots of Exif tags)

    Changes to libJPEG:
      jdatadst.c - fflush and ferror replaced by macros JFFLUSH and JFERROR.
      jinclude.h - standard JFFLUSH and JFERROR definitions, and new macro HAVE_JFIO.
      new file created: jconfig.h from jconfig.txt

    Changes to libEXIF:
      new files config.h and _stdint.h
      small fixes in exif-entry.c, exif-loader.c, exif-tag.c, mnote-fuji-tag.h and mnote-olympus-tag.h

    Comments:
      Other APPx markers are ignored.
      No thumbnail support.
      RGB images are automatically converted to YCbCr when saved.
      Also YcbCr are automatically converted to RGB when loaded. Use AutoYCbCr=0 to disable this behavior.
\endverbatim
 * \ingroup format */
void imFormatRegisterJPEG(void);


/** \defgroup png PNG - Portable Network Graphic Format
 * \section Description
 *
 * \par
 * Access to the PNG file format uses libpng version 1.6.23. \n
 * http://www.libpng.org                                    \n
 * Copyright (c) 2000-2002, 2004, 2006-2015 Glenn Randers-Pehrson
 *
 * \section Features
 *
\verbatim
    Data Types: Byte and UShort
    Color Spaces: Gray, RGB, MAP and Binary
    Compressions:
      DEFLATE - LZ77 variation (ZIP) [default]
    Only one image.
    Can have an alpha channel.
    Internally the components are always packed.
    Internally the lines are arranged from top down to bottom.
    Handle(1) returns png_structp libPNG structure.

    Attributes:
      ZIPQuality IM_INT (1) [1-9, default 6] (write only)
      ResolutionUnit (string) ["DPC", "DPI"]
      XResolution, YResolution IM_FLOAT (1)
      Interlaced (same as Progressive) IM_INT (1 | 0) default 0
      Gamma IM_FLOAT (1)
      WhitePoint IMFLOAT (2)
      PrimaryChromaticities  IMFLOAT (6)
      XPosition, YPosition IM_FLOAT (1)
      sRGBIntent IM_INT (1) [0: Perceptual, 1: Relative colorimetric, 2: Saturation, 3: Absolute colorimetric]
      TransparencyMap IM_BYTE (N) (for MAP images is the alpha value of the corresponding palette index)
      TransparencyIndex IM_BYTE (1) (for MAP images is the first index that has minimum alpha in TransparencyMap, for GRAY images is the index that it is fully transparent)
      TransparencyColor IM_BYTE (3) (for RGB images is the color that is full transparent)
      CalibrationName, CalibrationUnits (string)
      CalibrationLimits IM_INT (2)
      CalibrationEquation IM_BYTE (1) [0-Linear,1-Exponential,2-Arbitrary,3-HyperbolicSine)]
      CalibrationParam (string) [params separated by '\\n']
      Title, Author, Description, Copyright, DateTime (string)
      Software, Disclaimer, Warning, Source, Comment, ...       (string)
      DateTimeModified (string) [when writing uses the current system time]
      ICCProfile IM_BYTE (N)
      ScaleUnit (string) ["meters", "radians"]
      XScale, YScale IM_FLOAT (1)

    Comments:
      When saving PNG image with TransparencyIndex or TransparencyMap, TransparencyMap has precedence, 
        so set it to NULL if you changed TransparencyIndex.
      Attributes set after the image are ignored.
\endverbatim
 * \ingroup format */
void imFormatRegisterPNG(void);


/** \defgroup gif GIF - Graphics Interchange Format
 * \section Description
 *
 * \par
 * Copyright (c) 1987,1988,1989,1990 CompuServe Incorporated. \n
 * GIF is a Service Mark property of CompuServe Incorporated. \n
 * Graphics Interchange Format Programming Reference, 1990. \n
 * LZW Copyright Unisys.
 * \par
 * Patial Internal Implementation. \n
 * Decoding and encoding code were extracted from GIFLib 1.0. \n
 * Copyright (c) 1989 Gershon Elber.
 *
 * \section Features
 *
\verbatim
    Data Types: Byte
    Color Spaces: MAP only, (Gray and Binary saved as MAP)
    Compressions:
      LZW - Lempel-Ziv & Welch      [default]
    Can have more than one image.
    No alpha channel.
    Internally the lines are arranged from top down to bottom.

    Attributes:
      ScreenHeight, ScreenWidth IM_USHORT (1) screen size [default to the first image size]
      Interlaced IM_INT (1 | 0) default 0
      Description (string)
      TransparencyIndex IM_BYTE (1)
      XScreen, YScreen IM_USHORT (1) screen position
      UserInput IM_BYTE (1) [1, 0]
      Disposal (string) [UNDEF, LEAVE, RBACK, RPREV]
      Delay IM_USHORT (1) [time to wait betweed frames in 1/100 of a second]
      Iterations IM_USHORT (1) (NETSCAPE2.0 Application Extension) [The number of times to repeat the animation. 0 means to repeat forever. ]

    Comments:
      Attributes after the last image are ignored.
      Reads GIF87 and GIF89, but writes GIF89 always.
      Ignored attributes: Background Color Index, Pixel Aspect Ratio,
                          Plain Text Extensions, Application Extensions...
\endverbatim
 * \ingroup format */
void imFormatRegisterGIF(void);


/** \defgroup bmp BMP - Windows Device Independent Bitmap
 * \section Description
 *
 * \par
 * Windows Copyright Microsoft Corporation.
 * \par
 * Internal Implementation.
 *
 * \section Features
 *
\verbatim
    Data Types: Byte
    Color Spaces: RGB, MAP and Binary (Gray saved as MAP)
    Compressions:
      NONE - no compression [default]
      RLE  - Run Lenght Encoding (only for MAP and Gray)
    Only one image.
    Can have an alpha channel (only for RGB)
    Internally the components are always packed.
    Lines arranged from top down to bottom or bottom up to top. But are saved always as bottom up.

    Attributes:
      ResolutionUnit (string) ["DPC", "DPI"]
      XResolution, YResolution IM_FLOAT (1)

    Comments:
      Reads OS2 1.x and Windows 3, but writes Windows 3 always.
      Version 4 and 5 BMPs are not supported.
\endverbatim
 * \ingroup format */
void imFormatRegisterBMP(void);


/** \defgroup ras RAS - Sun Raster File
 * \section Description
 *
 * \par
 * Copyright Sun Corporation.
 * \par
 * Internal Implementation.
 *
 * \section Features
 *
\verbatim
    Data Types: Byte
    Color Spaces: Gray, RGB, MAP and Binary
    Compressions:
      NONE - no compression   [default]
      RLE  - Run Lenght Encoding
    Only one image.
    Can have an alpha channel (only for IM_RGB)
    Internally the components are always packed.
    Internally the lines are arranged from top down to bottom.

    Attributes:
      none
\endverbatim
 * \ingroup format */
void imFormatRegisterRAS(void);


/** \defgroup led LED - IUP image in LED
 * \section Description
 *
 * \par
 * Copyright Tecgraf/PUC-Rio and PETROBRAS/CENPES.
 * \par
 * Internal Implementation.
 *
 * \section Features
 *
\verbatim
    Data Types: Byte
    Color Spaces: MAP only (Gray and Binary saved as MAP)
    Compressions:
      NONE - no compression  [default]
    Only one image.
    No alpha channel.
    Internally the lines are arranged from top down to bottom.

    Attributes:
      none

    Comments:
      LED file must start with "LEDImage = IMAGE[".
\endverbatim
 * \ingroup format */
void imFormatRegisterLED(void);


/** \defgroup sgi SGI - Silicon Graphics Image File Format
 * \section Description
 *
 * \par
 * SGI is a trademark of Silicon Graphics, Inc.
 * \par
 * Internal Implementation.
 *
 * \section Features
 *
\verbatim
    Data Types: Byte and UShort
    Color Spaces: Gray and RGB (Binary saved as Gray, MAP with fixed palette when reading only)
    Compressions:
      NONE - no compression  [default]
      RLE  - Run Lenght Encoding
    Only one image.
    Can have an alpha channel (only for IM_RGB)
    Internally the components are always packed.
    Internally the lines are arranged from bottom up to top.

    Attributes:
      Description (string)
\endverbatim
 * \ingroup format */
void imFormatRegisterSGI(void);


/** \defgroup pcx PCX - ZSoft Picture
 * \section Description
 *
 * \par
 * Copyright ZSoft Corporation. \n
 * ZSoft (1988) PCX Technical Reference Manual.
 * \par
 * Internal Implementation.
 *
 * \section Features
 *
\verbatim
    Data Types: Byte
    Color Spaces: RGB, MAP and Binary (Gray saved as MAP)
    Compressions:
      NONE - no compression
      RLE  - Run Lenght Encoding [default - since uncompressed PCX is not well supported]
    Only one image.
    No alpha channel.
    Internally the components are always packed.
    Internally the lines are arranged from top down to bottom.

    Attributes:
      ResolutionUnit (string) ["DPC", "DPI"]
      XResolution, YResolution IM_FLOAT (1)
      XScreen, YScreen IM_USHORT (1) screen position

    Comments:
      Reads Versions 0-5, but writes Version 5 always.
\endverbatim
 * \ingroup format */
void imFormatRegisterPCX(void);


/** \defgroup tga TGA - Truevision Graphics Adapter File
 * \section Description
 *
 * \par
 * Truevision TGA File Format Specification Version 2.0 \n
 * Technical Manual Version 2.2 January, 1991           \n
 * Copyright 1989, 1990, 1991 Truevision, Inc.
 * \par
 * Internal Implementation.
 *
 * \section Features
 *
\verbatim
    Data Types: Byte
    Color Spaces: Gray, RGB and MAP (Binary saved as Gray)
    Compressions:
      NONE - no compression [default]
      RLE  - Run Lenght Encoding
    Only one image.
    Can have an alpha channel (only for RGB)
    Internally the components are always packed.
    Internally the lines are arranged from bottom up to top or from top down to bottom.

    Attributes:
      XScreen, YScreen IM_USHORT (1) screen position
      Title, Author, Description, JobName, Software (string)
      SoftwareVersion (read only) (string)
      DateTimeModified (string) [when writing uses the current system time]
      Gamma IM_FLOAT (1)
\endverbatim
 * \ingroup format */
void imFormatRegisterTGA(void);


/** \defgroup pnm PNM - Netpbm Portable Image Map
 * \section Description
 *
 * \par
 * PNM formats Copyright Jef Poskanzer
 * \par
 * Internal Implementation.
 *
 * \section Features
 *
\verbatim
    Data Types: Byte and UShort
    Color Spaces: Gray, RGB and Binary
    Compressions:
      NONE - no compression [default]
      ASCII (textual data)
    Can have more than one image, but sequencial access only.
    No alpha channel.
    Internally the components are always packed.
    Internally the lines are arranged from top down to bottom.

    Attributes:
      Description (string)

    Comments:
      In fact ASCII is an expansion, not a compression, because the file will be larger than binary data.
\endverbatim
 * \ingroup format */
void imFormatRegisterPNM(void);


/** \defgroup pfm PFM - Portable FloatMap Image Format
* \section Description
*
* \par
* Internal Implementation.
*
* \section Features
*
\verbatim
Data Types: Float
Color Spaces: Gray and RGB
Compressions:
  NONE - no compression [default]

No alpha channel.
Internally the components are always packed.
Internally the lines are arranged from bottom to top.

\endverbatim
* \ingroup format */
void imFormatRegisterPFM(void);


/** \defgroup ico ICO - Windows Icon
 * \section Description
 *
 * \par
 * Windows Copyright Microsoft Corporation.
 * \par
 * Internal Implementation.
 *
 * \section Features
 *
\verbatim
    Data Types: Byte
    Color Spaces: RGB, MAP and Binary (Gray saved as MAP)
    Compressions:
      NONE - no compression [default]
    Can have more than one image. But reading and writing is limited to 10 images max,
      and all images must have different sizes and bpp.
    Can have an alpha channel (only for RGB)
    Internally the components are always packed.
    Internally the lines are arranged from bottom up to top.

    Attributes:
      TransparencyIndex IM_BYTE (1)

    Comments:
      If the user specifies an alpha channel, the AND mask is loaded as alpha if
        the file color mode does not contain the IM_ALPHA flag.
      For MAP imagens, if the user does not specifies an alpha channel
        the TransparencyIndex is used to initialize the AND mask when writing,
        and if the user does specifies an alpha channel
        the most repeated index with transparency will be the transparent index.
      Although any size and common bpp can be used is recomended to use the typical configurations:
        16x16, 32x32, 48x48, 64x64 or 96x96
        2 colors, 16 colors, 256 colors, 24bpp or 32bpp
\endverbatim
 * \ingroup format */
void imFormatRegisterICO(void);


/** \defgroup krn KRN - IM Kernel File Format
 * \section Description
 *
 * \par
 * Textual format to provied a simple way to create kernel convolution images.
 * \par
 * Internal Implementation.
 *
 * \section Features
 *
\verbatim
    Data Types: Int, Float
    Color Spaces: Gray
    Compressions:
      NONE - no compression [default]
    Only one image.
    No alpha channel.
    Internally the lines are arranged from top down to bottom.

    Attributes:
      Description (string)

    Comments:
      The format is very simple, inspired by PNM.
      It was developed because PNM does not have support for INT and FLOAT.
      Remeber that usually convolution operations use kernel size an odd number.

    Format Model:
      IMKERNEL
      Description up to 512 characters
      width height
      type (0 - IM_INT, 1 - IM_FLOAT)
      data...

    Example:
      IMKERNEL
      Gradian
      3 3
      0
      0 -1 0
      0  1 0
      0  0 0
\endverbatim
 * \ingroup format */
void imFormatRegisterKRN(void);


#if defined(__cplusplus)
}
#endif

#endif
