/** \file
 * \brief Image Statistics and Analysis
 *
 * See Copyright Notice in im_lib.h
 */

#ifndef __IM_PROC_ANA_H
#define __IM_PROC_ANA_H

#include "im_image.h"

#if	defined(__cplusplus)
extern "C" {
#endif



/** \defgroup stats Image Statistics
 * \par
 * Operations to calculate some statistics over images.
 * \par
 * See \ref im_process_ana.h
 * \ingroup process */

/** Calculates the RMS error between two images (Root Mean Square Error).
* Returns zero if the counter aborted.
*
 * \verbatim im.CalcRMSError(image1: imImage, image2: imImage) -> counter: boolean, rms: number [in Lua 5] \endverbatim
 * \ingroup stats */
int imCalcRMSError(const imImage* image1, const imImage* image2, double *rmserror);

/** Calculates the SNR of an image and its noise (Signal Noise Ratio).
* Returns zero if the counter aborted.
*
 * \verbatim im.CalcSNR(src_image: imImage, noise_image: imImage) -> counter: boolean, snr: number [in Lua 5] \endverbatim
 * \ingroup stats */
int imCalcSNR(const imImage* src_image, const imImage* noise_image, double *snr);

/** Count the number of different colors in an image. \n
 * Image must be IM_BYTE, but can has all color spaces except IM_CMYK.
 * Data type can be also IM_SHORT or IM_USHORT if color space is IM_GRAY, IM_BINARY or IM_MAP.
 * Not using OpenMP when enabled, when color space depth is greater than 1.
 * Returns zero if the counter aborted.
 *
 * \verbatim im.CalcCountColors(image: imImage) -> counter: boolean, count: number [in Lua 5] \endverbatim
 * \ingroup stats */
int imCalcCountColors(const imImage* image, unsigned long *count);

/** Calculates the gray histogram of an image. \n
 * Image must be (IM_BYTE, IM_SHORT or IM_USHORT)/(IM_RGB, IM_GRAY, IM_BINARY or IM_MAP). \n
 * If the image is IM_RGB then the histogram of the luma component is calculated. \n
 * Histogram is always 256 or 65536 positions long. \n
 * When cumulative is different from zero it calculates the cumulative histogram.
 * Returns zero if the counter aborted.
 *
 * \verbatim im.CalcGrayHistogram(image: imImage, cumulative: boolean) -> counter: boolean, histo: table of numbers [in Lua 5] \endverbatim
 * \ingroup stats */
int imCalcGrayHistogram(const imImage* image, unsigned long* histo, int cumulative);

/** Calculates the histogram of an image plane. \n
 * Image can be IM_BYTE, IM_SHORT or IM_USHORT. \n
 * Histogram is always 256 or 65536 positions long. \n
 * Where plane is the depth plane to calculate the histogram. \n
 * When cumulative is different from zero it calculates the cumulative histogram.
 * Returns zero if the counter aborted.
 *
 * \verbatim im.CalcHistogram(image: imImage, plane: number, cumulative: boolean) -> counter: boolean, histo: table of numbers [in Lua 5] \endverbatim
 * The returned table is zero indexed.
 * \ingroup stats */
int imCalcHistogram(const imImage* image, unsigned long* histo, int plane, int cumulative);

/** Calculates the histogram of a IM_BYTE data. \n
 * Histogram is always 256 positions long. \n
 * When cumulative is different from zero it calculates the cumulative histogram.
 * Not available in Lua.
 * \ingroup stats */
void imCalcByteHistogram(const unsigned char* data, int count, unsigned long* histo, int cumulative);

/** Calculates the histogram of a IM_USHORT data. \n
 * Histogram is always 65536 positions long. \n
 * When cumulative is different from zero it calculates the cumulative histogram. \n
 * Not available in Lua.
 * \ingroup stats */
void imCalcUShortHistogram(const unsigned short* data, int count, unsigned long* histo, int cumulative);

/** Calculates the histogram of a IM_SHORT data. \n
 * Histogram is always 65536 positions long. \n
 * Zero is located at 32768 index. \n
 * When cumulative is different from zero it calculates the cumulative histogram. \n
 * Not available in Lua.
 * \ingroup stats */
void imCalcShortHistogram(const short* data, int count, unsigned long* histo, int cumulative);

/** Allocates an histogram data based on the image data type. \n
 * Data type can be IM_BYTE, IM_SHORT or IM_USHORT. \n
 * Not available in Lua.
 * \ingroup stats */
unsigned long* imHistogramNew(int data_type, int *hcount);

/** Releases the histogram data. \n
 * Not available in Lua.
 * \ingroup stats */
void imHistogramRelease(unsigned long* histo);

/** Short data type stores the histogram values of negative indexes starting at 0.
 * So the real level is obtained by shifting the zero based index. \n
 * Not available in Lua.
 * \ingroup stats */
int imHistogramShift(int data_type);

/** Returns the histogram size based on the image data type. \n
 * For IM_IM_USHORT and IM_SHORT returns 65536
 * for others returns 256.\n
 * Not available in Lua.
 * \ingroup stats */
int imHistogramCount(int data_type);


/** \brief Numerical Statistics Structure
 * \ingroup stats */
typedef struct _imStats
{
  double max;                /**< Maximum value              */
  double min;                /**< Minimum value              */
  unsigned long positive;   /**< Number of Positive Values  */
  unsigned long negative;   /**< Number of Negative Values  */
  unsigned long zeros;      /**< Number of Zeros            */
  double mean;               /**< Mean                       */
  double stddev;             /**< Standard Deviation         */
} imStats;

/** Calculates the statistics about the image data. \n
 * There is one stats for each depth plane. For ex: stats[0]=red stats, stats[0]=green stats, ... \n
 * Supports all data types except complex. \n
 * Returns zero if the counter aborted.
 *
 * \verbatim im.CalcImageStatistics(image: imImage) -> counter: boolean, stats: table [in Lua 5] \endverbatim
 * Table contains the following fields: max, min, positive, negative, zeros, mean, stddev. 
 * If image depth > 1 then table contains several tables with the previous fields, one for each plane,
 * starting at 0.
 * The same as the \ref imStats structure.
 * \ingroup stats */
int imCalcImageStatistics(const imImage* image, imStats* stats);

/** Calculates the statistics about the image histogram data.\n
 * There is one stats for each depth plane. For ex: stats[0]=red stats, stats[0]=green stats, ... \n
 * Only IM_BYTE, IM_SHORT and IM_USHORT images are supported.
 * Returns zero if the counter aborted.
 *
 * \verbatim im.CalcHistogramStatistics(image: imImage) -> counter: boolean, stats: table [in Lua 5] \endverbatim
 * \ingroup stats */
int imCalcHistogramStatistics(const imImage* image, imStats* stats);

/** Calculates some extra statistics about the image histogram data.\n
 * There is one stats for each depth plane. \n
 * Only IM_BYTE, IM_SHORT and IM_USHORT images are supported. \n
 * mode will be -1 if more than one max is found.
 * Returns zero if the counter aborted.
 *
 * \verbatim im.CalcHistoImageStatistics(image: imImage) -> counter: boolean, median: number, mode: number [in Lua 5] \endverbatim
 * \ingroup stats */
int imCalcHistoImageStatistics(const imImage* image, int* median, int* mode);

/** Calculates the minimum and maximum levels 
 * ignoring a given percentage of the histogram count.\n
 * Used by \ref imProcessExpandHistogram. \n
 * Only IM_BYTE, IM_SHORT and IM_USHORT images are supported. \n
 * Returns zero if the counter aborted.
 *
 * \verbatim im.CalcPercentMinMax(image: imImage, percent: number, ignore_zero: boolean) -> counter: boolean, min, max: number [in Lua 5] \endverbatim
 * \ingroup stats */
int imCalcPercentMinMax(const imImage* image, double percent, int ignore_zero, int *min, int *max);


/** \defgroup analyze Image Analysis
 * \par
 * See \ref im_process_ana.h
 * \ingroup process */

/** Find white regions in binary image. \n
 * Result is IM_GRAY/IM_USHORT type. Regions can be 4 connected or 8 connected. \n
 * The number of regions found is returned in region_count. Background is marked as 0. \n
 * Regions touching the border are considered only if touch_border=1.
 * Not using OpenMP when enabled.
 * Returns zero if the counter aborted.
 *
 * \verbatim im.AnalyzeFindRegions(src_image: imImage, dst_image: imImage, connect: number, touch_border: boolean) -> counter: boolean, region_count: number [in Lua 5] \endverbatim
 * \verbatim im.AnalyzeFindRegionsNew(image: imImage, connect: number, touch_border: boolean) -> counter: boolean, region_count: number, new_image: imImage [in Lua 5] \endverbatim
 * \ingroup analyze */
int imAnalyzeFindRegions(const imImage* src_image, imImage* dst_image, int connect, int touch_border, int *region_count);

/** Measure the actual area of all regions. Holes are not included. \n
 * This is the number of pixels of each region. \n
 * Source image is IM_GRAY/IM_USHORT type (the result of \ref imAnalyzeFindRegions). \n
 * area has size the number of regions.
 * Returns zero if the counter aborted.
 *
 * \verbatim im.AnalyzeMeasureArea(image: imImage, [region_count: number]) -> counter: boolean, area: table of numbers [in Lua 5] \endverbatim
 * The returned table is zero indexed. 
 * \ingroup analyze */
int imAnalyzeMeasureArea(const imImage* image, int* area, int region_count);

/** Measure the polygonal area limited by the perimeter line of all regions. Holes are not included. \n
 * Notice that some regions may have polygonal area zero. \n
 * Source image is IM_GRAY/IM_USHORT type (the result of \ref imAnalyzeFindRegions). \n
 * perimarea has size the number of regions.
 * Returns zero if the counter aborted.
 *
 * \verbatim im.AnalyzeMeasurePerimArea(image: imImage, [region_count: number]) -> counter: boolean, perimarea: table of numbers [in Lua 5] \endverbatim
 * The returned table is zero indexed. 
 * \ingroup analyze */
int imAnalyzeMeasurePerimArea(const imImage* image, double* perimarea, int region_count);

/** Calculate the centroid position of all regions. Holes are not included. \n
 * Source image is IM_GRAY/IM_USHORT type (the result of \ref imAnalyzeFindRegions). \n
 * area, cx and cy have size the number of regions. If area is NULL will be internally calculated.
 * Returns zero if the counter aborted.
 *
 * \verbatim im.AnalyzeMeasureCentroid(image: imImage, [area: table of numbers], [region_count: number]) -> counter: boolean, cx: table of numbers, cy: table of numbers [in Lua 5] \endverbatim
 * The returned tables are zero indexed. 
 * \ingroup analyze */
int imAnalyzeMeasureCentroid(const imImage* image, const int* area, int region_count, double* cx, double* cy);

/** Calculate the principal major axis slope of all regions. \n
 * Source image is IM_GRAY/IM_USHORT type (the result of \ref imAnalyzeFindRegions). \n
 * data has size the number of regions. If area or centroid are NULL will be internally calculated. \n
 * Principal (major and minor) axes are defined to be those axes that pass through the
 * centroid, about which the moment of inertia of the region is, respectively maximal or minimal.
 * Partially using OpenMP when enabled.
 * Returns zero if the counter aborted.
 *
 * \verbatim im.AnalyzeMeasurePrincipalAxis(image: imImage, counter: boolean, [area: table of numbers], [cx: table of numbers], [cy: table of numbers], [region_count: number]) 
                              -> major_slope: table of numbers, major_length: table of numbers, minor_slope: table of numbers, minor_length: table of numbers [in Lua 5] \endverbatim
 * The returned tables are zero indexed. 
 * \ingroup analyze */
int imAnalyzeMeasurePrincipalAxis(const imImage* image, const int* area, const double* cx, const double* cy,
                                   const int region_count, double* major_slope, double* major_length, 
                                                           double* minor_slope, double* minor_length);

/** Measure the number of holes of all regions. Optionally computes the holes area and holes perimeter of all regions. \n
 * Source image is IM_GRAY/IM_USHORT type (the result of \ref imAnalyzeFindRegions). \n
 * count, area and perim has size the number of regions, if some is NULL it will be not calculated.
 * Not using OpenMP when enabled.
 * Returns zero if the counter aborted.
 *
 * \verbatim im.AnalyzeMeasureHoles(image: imImage, connect: number, [region_count: number])-> counter: boolean, holes_count: number, holes_area: table of numbers, holes_perim: table of numbers [in Lua 5] \endverbatim
 * The returned tables are zero indexed. 
 * \ingroup analyze */
int imAnalyzeMeasureHoles(const imImage* image, int connect, int region_count, int *holes_count, int* holes_area, double* holes_perim);

/** Measure the total perimeter of all regions (external and internal). \n
 * Source image is IM_GRAY/IM_USHORT type (the result of imAnalyzeFindRegions). \n
 * It uses a half-pixel inter distance for 8 neighbors in a perimeter of a 4 connected region. \n
 * This function can also be used to measure line length. \n
 * perim has size the number of regions.
 * Returns zero if the counter aborted.
 *
 * \verbatim im.AnalyzeMeasurePerimeter(image: imImage)-> counter: boolean, perim: table of numbers [in Lua 5] \endverbatim
 * \ingroup analyze */
int imAnalyzeMeasurePerimeter(const imImage* image, double* perim, int region_count);

/** Isolates the perimeter line of gray integer images. Background is defined as being black (0). \n
 * It just checks if at least one of the 4 connected neighbors is non zero. Image borders are extended with zeros.
 * Returns zero if the counter aborted.
 *
 * \verbatim im.ProcessPerimeterLine(src_image: imImage, dst_image: imImage)-> counter: boolean [in Lua 5] \endverbatim
 * \verbatim im.ProcessPerimeterLineNew(image: imImage) -> counter: boolean, new_image: imImage [in Lua 5] \endverbatim
 * \ingroup analyze */
int imProcessPerimeterLine(const imImage* src_image, imImage* dst_image);

/** Eliminates regions that have area size outside or inside the given interval. \n
 * Source and target are a binary images. Regions can be 4 connected or 8 connected. \n
 * Can be done in-place. end_size can be zero to indicate no upper limit or an area with width*height size. \n
 * When searching inside the region the limits are inclusive (<= size >=), when searching outside the limits are exclusive (> size <).
 *
 * \verbatim im.ProcessRemoveByArea(src_image: imImage, dst_image: imImage, connect: number, start_size: number, end_size: number, inside: boolean)-> counter: boolean [in Lua 5] \endverbatim
 * \verbatim im.ProcessRemoveByAreaNew(image: imImage, connect: number, start_size: number, end_size: number, inside: boolean) -> counter: boolean, new_image: imImage [in Lua 5] \endverbatim
 * \ingroup analyze */
int imProcessRemoveByArea(const imImage* src_image, imImage* dst_image, int connect, int start_size, int end_size, int inside);

/** Fill holes inside white regions. \n
 * Source and target are a binary images. Regions can be 4 connected or 8 connected. \n
 * Can be done in-place. 
 * Returns zero if the counter aborted.
 *
 * \verbatim im.ProcessFillHoles(src_image: imImage, dst_image: imImage, connect: number)-> counter: boolean [in Lua 5] \endverbatim
 * \verbatim im.ProcessFillHolesNew(image: imImage, connect: number) -> counter: boolean, new_image: imImage [in Lua 5] \endverbatim
 * \ingroup analyze */
int imProcessFillHoles(const imImage* src_image, imImage* dst_image, int connect);


#if defined(__cplusplus)
}
#endif

#endif
