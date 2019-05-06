/** \file
 * \brief Image Processing - Local Operations
 *
 * See Copyright Notice in im_lib.h
 */

#ifndef __IM_PROCESS_LOC_H
#define __IM_PROCESS_LOC_H

#include "im_image.h"

#if	defined(__cplusplus)
extern "C" {
#endif



/** \defgroup resize Image Resize
 * \par
 * Operations to change the image size. \n
 * All size operations include the alpha channel if any.
 * \par
 * See \ref im_process_loc.h
 * \ingroup process */

/** Only reduze the image size using the given decimation order. \n
 * Supported decimation orders:
 * \li 0 - zero order (mean) [default in Lua for MAP and BINARY]
 * \li 1 - first order (bilinear decimation)  [default in Lua]
 * Images must be of the same type. If image type is IM_MAP or IM_BINARY, must use order=0. \n
 * Returns zero if the counter aborted.
 *
 * \verbatim im.ProcessReduce(src_image: imImage, dst_image: imImage, order: number) -> counter: boolean [in Lua 5] \endverbatim
 * \verbatim im.ProcessReduceNew(image: imImage, width, height[, order]: number) -> counter: boolean, new_image: imImage [in Lua 5] \endverbatim
 * \ingroup resize */
int imProcessReduce(const imImage* src_image, imImage* dst_image, int order);

/** Change the image size using the given interpolation order. \n
 * Supported interpolation orders:
 * \li 0 - zero order (near neighborhood) [default in Lua for MAP and BINARY]
 * \li 1 - first order (bilinear interpolation) [default in Lua] 
 * \li 3 - third order (bicubic interpolation)
 * Images must be of the same type. If image type is IM_MAP or IM_BINARY, must use order=0. \n
 * Returns zero if the counter aborted.
 *
 * \verbatim im.ProcessResize(src_image: imImage, dst_image: imImage, order: number) -> counter: boolean [in Lua 5] \endverbatim
 * \verbatim im.ProcessResizeNew(image: imImage, width, height[, order]: number) -> counter: boolean, new_image: imImage [in Lua 5] \endverbatim
 * \ingroup resize */
int imProcessResize(const imImage* src_image, imImage* dst_image, int order);

/** Reduze the image area by 4 (w/2,h/2). \n
  * Uses a fast average of neighbors. 
 * Images must be of the same type. Target image size must be source image width/2, height/2.
 * Can not operate on IM_MAP nor IM_BINARY images.
 * Returns zero if the counter aborted.
 *
 * \verbatim im.ProcessReduceBy4(src_image: imImage, dst_image: imImage) -> counter: boolean [in Lua 5] \endverbatim
 * \verbatim im.ProcessReduceBy4New(image: imImage) -> counter: boolean, new_image: imImage [in Lua 5] \endverbatim
 * \ingroup resize */
int imProcessReduceBy4(const imImage* src_image, imImage* dst_image);

/** Extract a rectangular region from an image. \n
 * Images must be of the same type. Target image size must be smaller than source image width-xmin, height-ymin. \n
 * ymin and xmin must be >0 and <size.
 * Returns zero if the counter aborted.
 *
 * \verbatim im.ProcessCrop(src_image: imImage, dst_image: imImage, xmin: number, ymin: number) -> counter: boolean [in Lua 5] \endverbatim
 * \verbatim im.ProcessCropNew(image: imImage, xmin, xmax, ymin, ymax: number) -> counter: boolean, new_image: imImage [in Lua 5] \endverbatim
 * \ingroup resize */
int imProcessCrop(const imImage* src_image, imImage* dst_image, int xmin, int ymin);

/** Insert a rectangular region in an image. \n
 * Images must be of the same type. Region image size can be larger than source image. \n
 * ymin and xmin must be >0 and <size. \n
 * Source and target must be of the same size. Can be done in-place.
 * Returns zero if the counter aborted.
 *
 * \verbatim im.ProcessInsert(src_image: imImage, region_image: imImage, dst_image: imImage, xmin: number, ymin: number) -> counter: boolean [in Lua 5] \endverbatim
 * \verbatim im.ProcessInsertNew(image: imImage, region_image: imImage, xmin: number, ymin: number) -> counter: boolean, new_image: imImage [in Lua 5] \endverbatim
 * \ingroup resize */
int imProcessInsert(const imImage* src_image, const imImage* region_image, imImage* dst_image, int xmin, int ymin);

/** Increase the image size by adding pixels with zero value. \n
 * Images must be of the same type. Target image size must be greatter or equal than source image width+xmin, height+ymin.
 * Returns zero if the counter aborted.
 *
 * \verbatim im.ProcessAddMargins(src_image: imImage, dst_image: imImage, xmin: number, ymin: number) -> counter: boolean [in Lua 5] \endverbatim
 * \verbatim im.ProcessAddMarginsNew(image: imImage, xmin, xmax, ymin, ymax: number) -> counter: boolean, new_image: imImage [in Lua 5] \endverbatim
 * \ingroup resize */
int imProcessAddMargins(const imImage* src_image, imImage* dst_image, int xmin, int ymin);



/** \defgroup geom Geometric Operations
 * \par
 * Operations to change the shape of the image. \n
 * All geometric operations include the alpha channel if any.
 * \par
 * See \ref im_process_loc.h
 * \ingroup process */

/** Calculates the size of the new image after rotation.
 *
 * \verbatim im.ProcessCalcRotateSize(width: number, height: number, cos0: number, sin0: number) [in Lua 5] \endverbatim
 * \ingroup geom */
void imProcessCalcRotateSize(int width, int height, int *new_width, int *new_height, double cos0, double sin0);

/** Rotates the image using the given interpolation order (see \ref imProcessResize). \n
 * Images must be of the same type. The target size can be calculated using \ref imProcessCalcRotateSize to fit the new image size, 
 * or can be any size, including the original size. The rotation is relative to the center of the image. \n
 * Returns zero if the counter aborted.
 *
 * \verbatim im.ProcessRotate(src_image: imImage, dst_image: imImage, cos0: number, sin0: number[, order]: number) -> counter: boolean [in Lua 5] \endverbatim
 * \verbatim im.ProcessRotateNew(image: imImage, cos0, sin0, order: number) -> counter: boolean, new_image: imImage [in Lua 5] \endverbatim
 * \ingroup geom */
int imProcessRotate(const imImage* src_image, imImage* dst_image, double cos0, double sin0, int order);

/** Rotates the image using the given interpolation order (see \ref imProcessResize). \n
 * Images must be of the same type. Target can have any size, including the original size. \n
 * The rotation is relative to the reference point. But the result can be shifted to the origin. \n
 * Returns zero if the counter aborted.
 *
 * \verbatim im.ProcessRotateRef(src_image: imImage, dst_image: imImage, cos0: number, sin0: number, x: number, y: number, to_origin: boolean, order: number) -> counter: boolean [in Lua 5] \endverbatim
 * \verbatim im.ProcessRotateRefNew(image: imImage, cos0: number, sin0: number, x: number, y: number, to_origin: boolean[, order]: number) -> counter: boolean, new_image: imImage [in Lua 5] \endverbatim
 * \ingroup geom */
int imProcessRotateRef(const imImage* src_image, imImage* dst_image, double cos0, double sin0, int x, int y, int to_origin, int order);

/** Rotates the image in 90 degrees counterclockwise or clockwise. Swap columns by lines. \n
 * Images must be of the same type. Target width and height must be source height and width. \n
 * Direction can be clockwise (1) or counter clockwise (-1).
 * Returns zero if the counter aborted.
 *
 * \verbatim im.ProcessRotate90(src_image: imImage, dst_image: imImage, dir_clockwise: boolean) -> counter: boolean [in Lua 5] \endverbatim
 * \verbatim im.ProcessRotate90New(image: imImage, dir_clockwise: boolean) -> counter: boolean, new_image: imImage [in Lua 5] \endverbatim
 * \ingroup geom */
int imProcessRotate90(const imImage* src_image, imImage* dst_image, int dir_clockwise);

/** Rotates the image in 180 degrees. Swap columns and swap lines. \n
 * Images must be of the same type and size.
 * Returns zero if the counter aborted.
 *
 * \verbatim im.ProcessRotate180(src_image: imImage, dst_image: imImage) -> counter: boolean [in Lua 5] \endverbatim
 * \verbatim im.ProcessRotate180New(image: imImage) -> counter: boolean, new_image: imImage [in Lua 5] \endverbatim
 * \ingroup geom */
int imProcessRotate180(const imImage* src_image, imImage* dst_image);

/** Mirror the image in a horizontal flip. Swap columns. \n
 * Images must be of the same type and size.
 * Can be done in-place.
 * Returns zero if the counter aborted.
 *
 * \verbatim im.ProcessMirror(src_image: imImage, dst_image: imImage) -> counter: boolean [in Lua 5] \endverbatim
 * \verbatim im.ProcessMirrorNew(image: imImage) -> counter: boolean, new_image: imImage [in Lua 5] \endverbatim
 * \ingroup geom */
int imProcessMirror(const imImage* src_image, imImage* dst_image);

/** Apply a vertical flip. Swap lines. \n
 * Images must be of the same type and size.
 * Can be done in-place.
 * Returns zero if the counter aborted.
 *
 * \verbatim im.ProcessFlip(src_image: imImage, dst_image: imImage) -> counter: boolean [in Lua 5] \endverbatim
 * \verbatim im.ProcessFlipNew(image: imImage) -> counter: boolean, new_image: imImage [in Lua 5] \endverbatim
 * \ingroup geom */
int imProcessFlip(const imImage* src_image, imImage* dst_image);

/** Apply a radial distortion using the given interpolation order (see imProcessResize). \n
 * Images must be of the same type and size.
 * Returns zero if the counter aborted.
 *
 * \verbatim im.ProcessRadial(src_image: imImage, dst_image: imImage, k1: number, order: number) -> counter: boolean [in Lua 5] \endverbatim
 * \verbatim im.ProcessRadialNew(image: imImage, k1: number[, order]: number) -> counter: boolean, new_image: imImage [in Lua 5] \endverbatim
 * \ingroup geom */
int imProcessRadial(const imImage* src_image, imImage* dst_image, double k1, int order);

/** Apply a lens distortion correction using the given interpolation order (see imProcessResize). \n
  * a, b, and c are the lens parameters. \n
  * Images must be of the same type and size.
  * Returns zero if the counter aborted.
  *
  * \verbatim im.ProcessLensDistort(src_image: imImage, dst_image: imImage, a, b, c: number, order: number) -> counter: boolean [in Lua 5] \endverbatim
  * \verbatim im.ProcessLensDistortNew(image: imImage, a, b, c: number[, order]: number) -> counter: boolean, new_image: imImage [in Lua 5] \endverbatim
  * \ingroup geom */
int imProcessLensDistort(const imImage* src_image, imImage* dst_image, double a, double b, double c, int order);

/** Apply a swirl distortion using the given interpolation order (see imProcessResize). \n
 * Images must be of the same type and size.
 * Returns zero if the counter aborted.
 *
 * \verbatim im.ProcessSwirl(src_image: imImage, dst_image: imImage, k: number, order: number) -> counter: boolean [in Lua 5] \endverbatim
 * \verbatim im.ProcessSwirlNew(image: imImage, k: number[, order]: number) -> counter: boolean, new_image: imImage [in Lua 5] \endverbatim
 * \ingroup geom */
int imProcessSwirl(const imImage* src_image, imImage* dst_image, double k1, int order);

/** Split the image in two images, one containing the odd lines and other containing the even lines. \n
 * Images must be of the same type. Height of the output images must be half the height of the input image.
 * If the height of the input image is odd then the first image must have height equals to half+1.
 * Returns zero if the counter aborted.
 *
 * \verbatim im.ProcessInterlaceSplit(src_image: imImage, dst_image1: imImage, dst_image2: imImage) -> counter: boolean [in Lua 5] \endverbatim
 * \verbatim im.ProcessInterlaceSplitNew(image: imImage) -> counter: boolean, new_image1: imImage, new_image2: imImage [in Lua 5] \endverbatim
 * \ingroup geom */
int imProcessInterlaceSplit(const imImage* src_image, imImage* dst_image1, imImage* dst_image2);



/** \defgroup morphgray Morphology Operations for Gray Images
 * \par
 * See \ref im_process_loc.h
 * \ingroup process */

/** Base gray morphology convolution. \n
 * Supports all data types except complex. Can be applied on color images. \n
 * Kernel is always IM_INT. Use kernel size odd for better results. \n
 * Use -1 for don't care positions in kernel. Kernel values are added to image values, then \n
 * you can use the maximum or the minimum within the kernel area. \n
 * No border extensions are used. 
 * All the gray morphology operations use this function. \n
 * Returns zero if the counter aborted.
 *
 * \verbatim im.ProcessGrayMorphConvolve(src_image: imImage, dst_image: imImage, kernel: imImage, ismax: boolean) -> counter: boolean [in Lua 5] \endverbatim
 * \verbatim im.ProcessGrayMorphConvolveNew(image: imImage, kernel: imImage, ismax: boolean) -> counter: boolean, new_image: imImage [in Lua 5] \endverbatim
 * \ingroup morphgray */
int imProcessGrayMorphConvolve(const imImage* src_image, imImage* dst_image, const imImage* kernel, int ismax);

/** Gray morphology convolution with a kernel full of "0"s and use minimum value.
 *
 * \verbatim im.ProcessGrayMorphErode(src_image: imImage, dst_image: imImage, kernel_size: number) -> counter: boolean [in Lua 5] \endverbatim
 * \verbatim im.ProcessGrayMorphErodeNew(image: imImage, kernel_size: number) -> counter: boolean, new_image: imImage [in Lua 5] \endverbatim
 * \ingroup morphgray */
int imProcessGrayMorphErode(const imImage* src_image, imImage* dst_image, int kernel_size);

/** Gray morphology convolution with a kernel full of "0"s and use maximum value.
 * Returns zero if the counter aborted.
 *
 * \verbatim im.ProcessGrayMorphDilate(src_image: imImage, dst_image: imImage, kernel_size: number) -> counter: boolean [in Lua 5] \endverbatim
 * \verbatim im.ProcessGrayMorphDilateNew(image: imImage, kernel_size: number) -> counter: boolean, new_image: imImage [in Lua 5] \endverbatim
 * \ingroup morphgray */
int imProcessGrayMorphDilate(const imImage* src_image, imImage* dst_image, int kernel_size);

/** Erode+Dilate.
 * Returns zero if the counter aborted.
 *
 * \verbatim im.ProcessGrayMorphOpen(src_image: imImage, dst_image: imImage, kernel_size: number) -> counter: boolean [in Lua 5] \endverbatim
 * \verbatim im.ProcessGrayMorphOpenNew(image: imImage, kernel_size: number) -> counter: boolean, new_image: imImage [in Lua 5] \endverbatim
 * \ingroup morphgray */
int imProcessGrayMorphOpen(const imImage* src_image, imImage* dst_image, int kernel_size);

/** Dilate+Erode.
 * Returns zero if the counter aborted.
 *
 * \verbatim im.ProcessGrayMorphClose(src_image: imImage, dst_image: imImage, kernel_size: number) -> counter: boolean [in Lua 5] \endverbatim
 * \verbatim im.ProcessGrayMorphCloseNew(image: imImage, kernel_size: number) -> counter: boolean, new_image: imImage [in Lua 5] \endverbatim
 * \ingroup morphgray */
int imProcessGrayMorphClose(const imImage* src_image, imImage* dst_image, int kernel_size);

/** Open+Difference.
 * Returns zero if the counter aborted.
 *
 * \verbatim im.ProcessGrayMorphTopHat(src_image: imImage, dst_image: imImage, kernel_size: number) -> counter: boolean [in Lua 5] \endverbatim
 * \verbatim im.ProcessGrayMorphTopHatNew(image: imImage, kernel_size: number) -> counter: boolean, new_image: imImage [in Lua 5] \endverbatim
 * \ingroup morphgray */
int imProcessGrayMorphTopHat(const imImage* src_image, imImage* dst_image, int kernel_size);

/** Close+Difference.
 * Returns zero if the counter aborted.
 *
 * \verbatim im.ProcessGrayMorphWell(src_image: imImage, dst_image: imImage, kernel_size: number) -> counter: boolean [in Lua 5] \endverbatim
 * \verbatim im.ProcessGrayMorphWellNew(image: imImage, kernel_size: number) -> counter: boolean, new_image: imImage [in Lua 5] \endverbatim
 * \ingroup morphgray */
int imProcessGrayMorphWell(const imImage* src_image, imImage* dst_image, int kernel_size);

/** Difference(Erode, Dilate).
 * Returns zero if the counter aborted.
 *
 * \verbatim im.ProcessGrayMorphGradient(src_image: imImage, dst_image: imImage, kernel_size: number) -> counter: boolean [in Lua 5] \endverbatim
 * \verbatim im.ProcessGrayMorphGradientNew(image: imImage, kernel_size: number) -> counter: boolean, new_image: imImage [in Lua 5] \endverbatim
 * \ingroup morphgray */
int imProcessGrayMorphGradient(const imImage* src_image, imImage* dst_image, int kernel_size);



/** \defgroup morphbin Morphology Operations for Binary Images
 * \par
 * See \ref im_process_loc.h
 * \ingroup process */

/** Base binary morphology convolution. \n
 * Images are all IM_BINARY. Kernel is IM_INT, but values can be only 1, 0 or -1. Use kernel size odd for better results. \n
 * Hit white means hit=1 and miss=0, or else hit=0 and miss=1. \n
 * Use -1 for don't care positions in kernel. Kernel values are simply compared with image values. \n
 * The operation can be repeated by a number of iterations. 
 * The border is zero extended. \n
 * Almost all the binary morphology operations use this function.\n
 * Returns zero if the counter aborted.
 *
 * \verbatim im.ProcessBinMorphConvolve(src_image: imImage, dst_image: imImage, kernel: imImage, hit_white: boolean, iter: number) -> counter: boolean [in Lua 5] \endverbatim
 * \verbatim im.ProcessBinMorphConvolveNew(image: imImage, kernel: imImage, hit_white: boolean, iter: number) -> counter: boolean, new_image: imImage [in Lua 5] \endverbatim
 * \ingroup morphbin */
int imProcessBinMorphConvolve(const imImage* src_image, imImage* dst_image, const imImage* kernel, int hit_white, int iter);

/** Binary morphology convolution with a kernel full of "1"s and hit white.
 * Returns zero if the counter aborted.
 *
 * \verbatim im.ProcessBinMorphErode(src_image: imImage, dst_image: imImage, kernel_size: number, iter: number) -> counter: boolean [in Lua 5] \endverbatim
 * \verbatim im.ProcessBinMorphErodeNew(image: imImage, kernel_size: number, iter: number) -> counter: boolean, new_image: imImage [in Lua 5] \endverbatim
 * \ingroup morphbin */
int imProcessBinMorphErode(const imImage* src_image, imImage* dst_image, int kernel_size, int iter);

/** Binary morphology convolution with a kernel full of "0"s and hit black.
 * Returns zero if the counter aborted.
 *
 * \verbatim im.ProcessBinMorphDilate(src_image: imImage, dst_image: imImage, kernel_size: number, iter: number) -> counter: boolean [in Lua 5] \endverbatim
 * \verbatim im.ProcessBinMorphDilateNew(image: imImage, kernel_size: number, iter: number) -> counter: boolean, new_image: imImage [in Lua 5] \endverbatim
 * \ingroup morphbin */
int imProcessBinMorphDilate(const imImage* src_image, imImage* dst_image, int kernel_size, int iter);

/** Erode+Dilate.
 * When iteration is more than one it means Erode+Erode+Erode+...+Dilate+Dilate+Dilate+...
 * Returns zero if the counter aborted.
 *
 * \verbatim im.ProcessBinMorphOpen(src_image: imImage, dst_image: imImage, kernel_size: number, iter: number) -> counter: boolean [in Lua 5] \endverbatim
 * \verbatim im.ProcessBinMorphOpenNew(image: imImage, kernel_size: number, iter: number) -> counter: boolean, new_image: imImage [in Lua 5] \endverbatim
 * \ingroup morphbin */
int imProcessBinMorphOpen(const imImage* src_image, imImage* dst_image, int kernel_size, int iter);

/** Dilate+Erode.
 * Returns zero if the counter aborted.
 *
 * \verbatim im.ProcessBinMorphClose(src_image: imImage, dst_image: imImage, kernel_size: number, iter: number) -> counter: boolean [in Lua 5] \endverbatim
 * \verbatim im.ProcessBinMorphCloseNew(image: imImage, kernel_size: number, iter: number) -> counter: boolean, new_image: imImage [in Lua 5] \endverbatim
 * \ingroup morphbin */
int imProcessBinMorphClose(const imImage* src_image, imImage* dst_image, int kernel_size, int iter);

/** Erode+Difference. \n
 * The difference from the source image is applied only once.
 * Returns zero if the counter aborted.
 *
 * \verbatim im.ProcessBinMorphOutline(src_image: imImage, dst_image: imImage, kernel_size: number, iter: number) -> counter: boolean [in Lua 5] \endverbatim
 * \verbatim im.ProcessBinMorphOutlineNew(image: imImage, kernel_size: number, iter: number) -> counter: boolean, new_image: imImage [in Lua 5] \endverbatim
 * \ingroup morphbin */
int imProcessBinMorphOutline(const imImage* src_image, imImage* dst_image, int kernel_size, int iter);

/** Thins the supplied binary image using Rosenfeld's parallel thinning algorithm. \n
 * Reference: \n
 * "Efficient Binary Image Thinning using Neighborhood Maps" \n
 * by Joseph M. Cychosz, 3ksnn64@ecn.purdue.edu              \n
 * in "Graphics Gems IV", Academic Press, 1994               \n
 * Not using OpenMP when enabled.
 * Returns zero if the counter aborted (counter is approximate).
 *
 * \verbatim im.ProcessBinMorphThin(src_image: imImage, dst_image: imImage)-> counter: boolean [in Lua 5] \endverbatim
 * \verbatim im.ProcessBinMorphThinNew(image: imImage) -> counter: boolean, new_image: imImage [in Lua 5] \endverbatim
 * \ingroup morphbin */
int imProcessBinMorphThin(const imImage* src_image, imImage* dst_image);



/** \defgroup rank Rank Convolution Operations
 * \par
 * All the rank convolution use the same base function. Near the border the base function 
 * includes only the real image pixels in the rank. No border extensions are used.
 * \par
 * See \ref im_process_loc.h
 * \ingroup process */

/** Rank convolution using the median value. \n
 * Returns zero if the counter aborted. \n
 * Supports all data types except complex. Can be applied on color images.
 *
 * \verbatim im.ProcessMedianConvolve(src_image: imImage, dst_image: imImage, kernel_size: number) -> counter: boolean [in Lua 5] \endverbatim
 * \verbatim im.ProcessMedianConvolveNew(image: imImage, kernel_size: number) -> counter: boolean, new_image: imImage [in Lua 5] \endverbatim
 * \ingroup rank */
int imProcessMedianConvolve(const imImage* src_image, imImage* dst_image, int kernel_size);

/** Rank convolution using (maximum-minimum) value. \n
 * Returns zero if the counter aborted. \n
 * Supports all data types except complex. Can be applied on color images.
 *
 * \verbatim im.ProcessRangeConvolve(src_image: imImage, dst_image: imImage, kernel_size: number) -> counter: boolean [in Lua 5] \endverbatim
 * \verbatim im.ProcessRangeConvolveNew(image: imImage, kernel_size: number) -> counter: boolean, new_image: imImage [in Lua 5] \endverbatim
 * \ingroup rank */
int imProcessRangeConvolve(const imImage* src_image, imImage* dst_image, int kernel_size);

/** Rank convolution using the closest maximum or minimum value. \n
 * Returns zero if the counter aborted. \n
 * Supports all data types except complex. Can be applied on color images.
 *
 * \verbatim im.ProcessRankClosestConvolve(src_image: imImage, dst_image: imImage, kernel_size: number) -> counter: boolean [in Lua 5] \endverbatim
 * \verbatim im.ProcessRankClosestConvolveNew(image: imImage, kernel_size: number) -> counter: boolean, new_image: imImage [in Lua 5] \endverbatim
 * \ingroup rank */
int imProcessRankClosestConvolve(const imImage* src_image, imImage* dst_image, int kernel_size);

/** Rank convolution using the maximum value. \n
 * Returns zero if the counter aborted. \n
 * Supports all data types except complex. Can be applied on color images.
 *
 * \verbatim im.ProcessRankMaxConvolve(src_image: imImage, dst_image: imImage, kernel_size: number) -> counter: boolean [in Lua 5] \endverbatim
 * \verbatim im.ProcessRankMaxConvolveNew(image: imImage, kernel_size: number) -> counter: boolean, new_image: imImage [in Lua 5] \endverbatim
 * \ingroup rank */
int imProcessRankMaxConvolve(const imImage* src_image, imImage* dst_image, int kernel_size);

/** Rank convolution using the minimum value. \n
 * Returns zero if the counter aborted. \n
 * Supports all data types except complex. Can be applied on color images.
 *
 * \verbatim im.ProcessRankMinConvolve(src_image: imImage, dst_image: imImage, kernel_size: number) -> counter: boolean [in Lua 5] \endverbatim
 * \verbatim im.ProcessRankMinConvolveNew(image: imImage, kernel_size: number) -> counter: boolean, new_image: imImage [in Lua 5] \endverbatim
 * \ingroup rank */
int imProcessRankMinConvolve(const imImage* src_image, imImage* dst_image, int kernel_size);

/** Threshold using a rank convolution with a range contrast function. \n
 * Supports all integer IM_GRAY images as source, and IM_BINARY as target. \n
 * Local variable threshold by the method of Bernsen. \n
 * Extracted from XITE, Copyright 1991, Blab, UiO \n
 * http://www.ifi.uio.no/~blab/Software/Xite/
\verbatim
  Reference:	
    Bernsen, J: "Dynamic thresholding of grey-level images"
		Proc. of the 8th ICPR, Paris, Oct 1986, 1251-1255.
  Author:     Oivind Due Trier
\endverbatim
 * Returns zero if the counter aborted.
 *
 * \verbatim im.ProcessRangeContrastThreshold(src_image: imImage, dst_image: imImage, kernel_size: number, min_range: number) -> counter: boolean [in Lua 5] \endverbatim
 * \verbatim im.ProcessRangeContrastThresholdNew(image: imImage, kernel_size: number, min_range: number) -> counter: boolean, new_image: imImage [in Lua 5] \endverbatim
 * \ingroup threshold */
int imProcessRangeContrastThreshold(const imImage* src_image, imImage* dst_image, int kernel_size, int min_range);

/** Threshold using a rank convolution with a local max function.  \n
 * Returns zero if the counter aborted. \n
 * Supports all integer IM_GRAY images as source, and IM_BINARY as target.
 *
 * \verbatim im.ProcessLocalMaxThreshold(src_image: imImage, dst_image: imImage, kernel_size: number, min_level: number) -> counter: boolean [in Lua 5] \endverbatim
 * \verbatim im.ProcessLocalMaxThresholdNew(image: imImage, kernel_size: number, min_level: number) -> counter: boolean, new_image: imImage [in Lua 5] \endverbatim
 * \ingroup threshold */
int imProcessLocalMaxThreshold(const imImage* src_image, imImage* dst_image, int kernel_size, int min_level);



/** \defgroup convolve Convolution Operations
 * \par
 * See \ref im_process_loc.h
 * \ingroup process */

/** Base Convolution with a kernel. \n
 * Kernel can be IM_INT or IM_FLOAT, but always IM_GRAY. Use kernel size odd for better results. \n
 * Supports all data types. The border is mirrored. \n
 * Returns zero if the counter aborted. Most of the convolutions use this function.\n
 *
 * \verbatim im.ProcessConvolve(src_image: imImage, dst_image: imImage, kernel: imImage) -> counter: boolean [in Lua 5] \endverbatim
 * \verbatim im.ProcessConvolveNew(image: imImage, kernel: imImage) -> counter: boolean, new_image: imImage [in Lua 5] \endverbatim
 * \ingroup convolve */
int imProcessConvolve(const imImage* src_image, imImage* dst_image, const imImage* kernel);

/** Base convolution when the kernel is separable. Only the first line and the first column will be used. \n
 * Returns zero if the counter aborted.\n
 *
 * \verbatim im.ProcessConvolveSep(src_image: imImage, dst_image: imImage, kernel: imImage) -> counter: boolean [in Lua 5] \endverbatim
 * \verbatim im.ProcessConvolveSepNew(image: imImage, kernel: imImage) -> counter: boolean, new_image: imImage [in Lua 5] \endverbatim
 * \ingroup convolve */
int imProcessConvolveSep(const imImage* src_image, imImage* dst_image, const imImage* kernel);

/** Base Convolution with two kernels. The result is the magnitude of the result of each convolution. \n
 * Kernel can be IM_INT or IM_FLOAT, but always IM_GRAY. Use kernel size odd for better results. \n
 * Supports all data types. The border is mirrored. \n
 * Returns zero if the counter aborted. Most of the convolutions use this function.\n
 *
 * \verbatim im.ProcessConvolveDual(src_image: imImage, dst_image: imImage, kernel1, kernel2: imImage) -> counter: boolean [in Lua 5] \endverbatim
 * \verbatim im.ProcessConvolveDualNew(image: imImage, kernel1, kernel2: imImage) -> counter: boolean, new_image: imImage [in Lua 5] \endverbatim
 * \ingroup convolve */
int imProcessConvolveDual(const imImage* src_image, imImage* dst_image, const imImage *kernel1, const imImage *kernel2);

/** Repeats the convolution a number of times. \n
 * Returns zero if the counter aborted.\n
 *
 * \verbatim im.ProcessConvolveRep(src_image: imImage, dst_image: imImage, kernel: imImage, count: number) -> counter: boolean [in Lua 5] \endverbatim
 * \verbatim im.ProcessConvolveRepNew(image: imImage, kernel: imImage, count: number) -> counter: boolean, new_image: imImage [in Lua 5] \endverbatim
 * \ingroup convolve */
int imProcessConvolveRep(const imImage* src_image, imImage* dst_image, const imImage* kernel, int count);

/** Convolve with a kernel rotating it 8 times and getting the absolute maximum value. \n
 * Kernel must be square. \n
 * The rotation is implemented only for kernel sizes 3x3, 5x5 and 7x7. \n
 * Supports all data types except complex.
 * Returns zero if the counter aborted.\n
 *
 * \verbatim im.ProcessCompassConvolve(src_image: imImage, dst_image: imImage, kernel: imImage) -> counter: boolean [in Lua 5] \endverbatim
 * \verbatim im.ProcessCompassConvolveNew(image: imImage, kernel: imImage) -> counter: boolean, new_image: imImage [in Lua 5] \endverbatim
 * \ingroup convolve */
int imProcessCompassConvolve(const imImage* src_image, imImage* dst_image, imImage* kernel);

/** Utility function to rotate a kernel one time.
 *
 * \verbatim im.ProcessRotateKernel(kernel: imImage) [in Lua 5] \endverbatim
 * \ingroup convolve */
void imProcessRotateKernel(imImage* kernel);

/** Difference(Gaussian1, Gaussian2). \n
 * Supports all data types, 
 * but if source is IM_BYTE or IM_USHORT target image must be of type IM_INT.
 * Returns zero if the counter aborted.
 *
 * \verbatim im.ProcessDiffOfGaussianConvolve(src_image: imImage, dst_image: imImage, stddev1: number, stddev2: number) -> counter: boolean [in Lua 5] \endverbatim
 * \verbatim im.ProcessDiffOfGaussianConvolveNew(image: imImage, stddev1: number, stddev2: number) -> counter: boolean, new_image: imImage [in Lua 5] \endverbatim
 * \ingroup convolve */
int imProcessDiffOfGaussianConvolve(const imImage* src_image, imImage* dst_image, double stddev1, double stddev2);

/** Convolution with a laplacian of a gaussian kernel. \n
 * Supports all data types, 
 * but if source is IM_BYTE or IM_USHORT target image must be of type IM_INT.
 * Returns zero if the counter aborted.
 *
 * \verbatim im.ProcessLapOfGaussianConvolve(src_image: imImage, dst_image: imImage, stddev: number) -> counter: boolean [in Lua 5] \endverbatim
 * \verbatim im.ProcessLapOfGaussianConvolveNew(image: imImage, stddev: number) -> counter: boolean, new_image: imImage [in Lua 5] \endverbatim
 * \ingroup convolve */
int imProcessLapOfGaussianConvolve(const imImage* src_image, imImage* dst_image, double stddev);

/** Convolution with a kernel full of "1"s inside a circle. \n
 * Supports all data types.
 * Returns zero if the counter aborted.
 *
 * \verbatim im.ProcessMeanConvolve(src_image: imImage, dst_image: imImage, kernel_size: number) -> counter: boolean [in Lua 5] \endverbatim
 * \verbatim im.ProcessMeanConvolveNew(image: imImage, kernel_size: number) -> counter: boolean, new_image: imImage [in Lua 5] \endverbatim
 * \ingroup convolve */
int imProcessMeanConvolve(const imImage* src_image, imImage* dst_image, int kernel_size);

/** Convolution with a gaussian kernel with floating point values. \n
 * If sdtdev is negative its magnitude will be used as the kernel size. \n
 * Supports all data types.
 * Returns zero if the counter aborted.
 *
 * \verbatim im.ProcessGaussianConvolve(src_image: imImage, dst_image: imImage, stddev: number) -> counter: boolean [in Lua 5] \endverbatim
 * \verbatim im.ProcessGaussianConvolveNew(image: imImage, stddev: number) -> counter: boolean, new_image: imImage [in Lua 5] \endverbatim
 * \ingroup convolve */
int imProcessGaussianConvolve(const imImage* src_image, imImage* dst_image, double stddev);

/** Convolution with a barlett kernel. \n
 * Supports all data types.
 * Returns zero if the counter aborted.
 *
 * \verbatim im.ProcessBarlettConvolve(src_image: imImage, dst_image: imImage, kernel_size: number) -> counter: boolean [in Lua 5] \endverbatim
 * \verbatim im.ProcessBarlettConvolveNew(image: imImage, kernel_size: number) -> counter: boolean, new_image: imImage [in Lua 5] \endverbatim
 * \ingroup convolve */
int imProcessBarlettConvolve(const imImage* src_image, imImage* dst_image, int kernel_size);

/** Magnitude of the sobel convolution. \n
 * Supports all data types.
 * Returns zero if the counter aborted.
 *
 * \verbatim im.ProcessSobelConvolve(src_image: imImage, dst_image: imImage) -> counter: boolean [in Lua 5] \endverbatim
 * \verbatim im.ProcessSobelConvolveNew(image: imImage) -> counter: boolean, new_image: imImage [in Lua 5] \endverbatim
 * \ingroup convolve */
int imProcessSobelConvolve(const imImage* src_image, imImage* dst_image);

/** Magnitude of the prewitt convolution. \n
 * Supports all data types.
 * Returns zero if the counter aborted.
 *
 * \verbatim im.ProcessPrewittConvolve(src_image: imImage, dst_image: imImage) -> counter: boolean [in Lua 5] \endverbatim
 * \verbatim im.ProcessPrewittConvolveNew(image: imImage) -> counter: boolean, new_image: imImage [in Lua 5] \endverbatim
 * \ingroup convolve */
int imProcessPrewittConvolve(const imImage* src_image, imImage* dst_image);

/** Spline edge dectection. \n
 * Supports all data types.
 * Returns zero if the counter aborted.
 *
 * \verbatim im.ProcessSplineEdgeConvolve(src_image: imImage, dst_image: imImage) -> counter: boolean [in Lua 5] \endverbatim
 * \verbatim im.ProcessSplineEdgeConvolveNew(image: imImage) -> counter: boolean, new_image: imImage [in Lua 5] \endverbatim
 * \ingroup convolve */
int imProcessSplineEdgeConvolve(const imImage* src_image, imImage* dst_image);

/** Finds the zero crossings of IM_SHORT, IM_INT, IM_FLOAT and IM_DOUBLE images. Crossings are marked with non zero values
 * indicating the intensity of the edge. It is usually used after a second derivative, laplace. \n
 * Extracted from XITE, Copyright 1991, Blab, UiO \n
 * http://www.ifi.uio.no/~blab/Software/Xite/
 * Returns zero if the counter aborted.
 *
 * \verbatim im.ProcessZeroCrossing(src_image: imImage, dst_image: imImage) -> counter: boolean [in Lua 5] \endverbatim
 * \verbatim im.ProcessZeroCrossingNew(image: imImage) -> counter: boolean, new_image: imImage [in Lua 5] \endverbatim
 * \ingroup convolve */
int imProcessZeroCrossing(const imImage* src_image, imImage* dst_image);

/** First part of the Canny edge detector. Includes the gaussian filtering and the nonmax suppression. \n
 * After using this you could apply a Hysteresis Threshold, see \ref imProcessHysteresisThreshold. \n
 * Image must be IM_BYTE/IM_GRAY. \n
 * Returns zero if the counter aborted.
 * Implementation from the book:
 \verbatim
    J. R. Parker
    "Algorithms for Image Processing and Computer Vision"
    WILEY
 \endverbatim
 *
 * \verbatim im.ProcessCanny(src_image: imImage, dst_image: imImage, stddev: number)-> counter: boolean [in Lua 5] \endverbatim
 * \verbatim im.ProcessCannyNew(image: imImage, stddev: number) -> counter: boolean, new_image: imImage [in Lua 5] \endverbatim
 * \ingroup convolve */
int imProcessCanny(const imImage* src_image, imImage* dst_image, double stddev);

/** Calculates the kernel size given the standard deviation. \n
 * If sdtdev is negative its magnitude will be used as the kernel size.
 *
 * \verbatim im.GaussianStdDev2KernelSize(stddev: number) -> kernel_size: number [in Lua 5] \endverbatim
 * \ingroup convolve */
int imGaussianStdDev2KernelSize(double stddev);

/** Calculates the standard deviation given the kernel size.
 *
 * \verbatim im.GaussianKernelSize2StdDev(kernel_size: number) -> stddev: number [in Lua 5] \endverbatim
 * \ingroup convolve */
double imGaussianKernelSize2StdDev(int kernel_size);

/** Edge enhancement using Unsharp mask. stddev control the gaussian filter, 
 *  amount controls how much the edges will enhance the image (0<amount<1), and
 *  threshold controls which edges will be considered, it compares to twice of the absolute size of the edge.
 *  Although very similar to \ref imProcessSharp, produces better results.
 *
 * \verbatim im.ProcessUnsharp(src_image: imImage, dst_image: imImage, stddev: number, amount: number, threshold: number) [in Lua 5] \endverbatim
 * \verbatim im.ProcessUnsharpNew(image: imImage, stddev: number, amount: number, threshold: number) -> new_image: imImage [in Lua 5] \endverbatim
 * \ingroup convolve */
int imProcessUnsharp(const imImage* src_image, imImage* dst_image, double stddev, double amount, double threshold);

/** Edge enhancement using Laplacian8 mask. 
 *  amount controls how much the edges will enhance the image (0<amount<1), and
 *  threshold controls which edges will be considered, it compares to twice of the absolute size of the edge.
 * Returns zero if the counter aborted.
 *
 * \verbatim im.ProcessSharp(src_image: imImage, dst_image: imImage, amount: number, threshold: number) [in Lua 5] \endverbatim
 * \verbatim im.ProcessSharpNew(image: imImage, amount: number, threshold: number) -> new_image: imImage [in Lua 5] \endverbatim
 * \ingroup convolve */
int imProcessSharp(const imImage* src_image, imImage* dst_image, double amount, double threshold);

/** Edge enhancement using a given kernel.
 *  If kernel has all positive values, then the unsharp technique is used, else sharp is used.
 *  amount controls how much the edges will enhance the image (0<amount<1), and
 *  threshold controls which edges will be considered, it compares to twice of the absolute size of the edge.
 * Returns zero if the counter aborted.
 *
 * \verbatim im.ProcessSharp(src_image: imImage, dst_image: imImage, amount: number, threshold: number) [in Lua 5] \endverbatim
 * \verbatim im.ProcessSharpNew(image: imImage, amount: number, threshold: number) -> new_image: imImage [in Lua 5] \endverbatim
 * \ingroup convolve */
int imProcessSharpKernel(const imImage* src_image, const imImage* kernel, imImage* dst_image, double amount, double threshold);


#if defined(__cplusplus)
}
#endif

#endif
