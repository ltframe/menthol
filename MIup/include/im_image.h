/** \file
 * \brief Image Manipulation
 *
 * See Copyright Notice in im_lib.h
 */

#ifndef __IM_IMAGE_H
#define __IM_IMAGE_H

#if	defined(__cplusplus)
extern "C" {
#endif


/** \defgroup imgclass imImage 
 *
 * \par
 *  Base definitions and functions for image representation. \n
 * Only the image processing operations depends on these definitions, 
 * Image Storage and Image Capture are completely independent.
 * \par
 * You can also initialize a structure with your own memory buffer, see \ref imImageInit.
 * To release the structure without releasing the buffer, 
 * set "data[0]" to NULL before calling imImageDestroy.
 * \par
 * See \ref im_image.h
 * \ingroup imagerep */



/** \brief Image Representation Structure
 *
 * \par
 * An image representation than supports all the color spaces, 
 * but planes are always unpacked and the orientation is always bottom up.
 * \ingroup imgclass */
typedef struct _imImage
{
  /* main parameters */
  int width;          /**< Number of columns. image:Width() -> width: number [in Lua 5]. */
  int height;         /**< Number of lines. image:Height() -> height: number [in Lua 5]. */
  int color_space;    /**< Color space descriptor. See also \ref imColorSpace. image:ColorSpace() -> color_space: number [in Lua 5]. */
  int data_type;      /**< Data type descriptor. See also \ref imDataType. image:DataType() -> data_type: number [in Lua 5]. */
  int has_alpha;      /**< Indicates that there is an extra channel with alpha. image:HasAlpha() -> has_alpha: boolean [in Lua 5]. \n
                           It will not affect the secondary parameters, i.e. the number of planes will be in fact depth+1. \n
                           It is always 0 unless imImageAddAlpha is called. Alpha is automatically added in image loading functions. */

  /* secondary parameters */
  int depth;          /**< Number of planes                      (ColorSpaceDepth)   image:Depth() -> depth: number [in Lua 5].       */
  int line_size;      /**< Number of bytes per line in one plane (width * DataTypeSize)    */
  int plane_size;     /**< Number of bytes per plane.            (line_size * height)      */
  int size;           /**< Number of bytes occupied by the image (plane_size * depth)      */
  int count;          /**< Number of pixels per plane            (width * height)          */

  /* image data */
  void** data;        /**< Image data organized as a 2D matrix with several planes.   \n
                           But plane 0 is also a pointer to the full data.            \n
                           The remaining planes are: "data[i] = data[0] + i*plane_size". \n
                           In Lua, data indexing is possible using: "image[plane][line][column]". \n
                           Also in Lua, is possible to set all pixels using a table calling "image:SetPixels(table)"
                           and get all pixels using "table = image:GetPixels()" (Since 3.9). */

  /* image attributes */
  long *palette;      /**< Color palette. image:GetPalette() -> palette: imPalette [in Lua 5]. \n
                           Used only when depth=1. Otherwise is NULL. */
  int palette_count;  /**< The palette is always 256 colors allocated, but can have less colors used. */

  void* attrib_table; /**< in fact is an imAttribTable, but we hide this here */
} imImage;


/** Creates a new image.
 * See also \ref imDataType and \ref imColorSpace. Image data is cleared as \ref imImageClear. \n
 * In Lua the IM image metatable name is "imImage".
 * When converted to a string will return "imImage(%p) [width=%d,height=%d,color_space=%s,data_type=%s,depth=%d]" where %p is replaced by the userdata address,
 * and other values are replaced by the respective attributes.
 * If the image is already destroyed by im.ImageDestroy, then it will return also the suffix "-destroyed".
 *
 * \verbatim im.ImageCreate(width: number, height: number, color_space: number, data_type: number) -> image: imImage [in Lua 5] \endverbatim
 * \ingroup imgclass */
imImage* imImageCreate(int width, int height, int color_space, int data_type);

/** Initializes the image structure but does not allocates image data.
 * See also \ref imDataType and \ref imColorSpace. 
 * The only addtional flag thar color_mode can has here is IM_ALPHA.
 * To release the image structure without releasing the buffer, 
 * set "data[0]" to NULL before calling imImageDestroy.
 * \ingroup imgclass */
imImage* imImageInit(int width, int height, int color_mode, int data_type, void* data_buffer, long* palette, int palette_count);

/** Creates a new image based on an existing one. \n
 * If the addicional parameters are -1, the given image parameters are used. \n
 * The image atributes always are copied. HasAlpha is copied.
 * See also \ref imDataType and \ref imColorSpace.
 *
 * \verbatim im.ImageCreateBased(image: imImage, [width: number], [height: number], [color_space: number], [data_type: number]) -> image: imImage [in Lua 5] \endverbatim
 * The addicional parameters in Lua can be nil, 
 * and they can also be functions with the based image as a parameter to return the respective value.
 * \ingroup imgclass */
imImage* imImageCreateBased(const imImage* image, int width, int height, int color_space, int data_type);

/** Destroys the image and frees the memory used.
 * image data is destroyed only if its data[0] is not NULL. \n
 * In Lua if this function is not called, the image is destroyed by the garbage collector.
 *
 * \verbatim im.ImageDestroy(image: imImage) [in Lua 5] \endverbatim
 * \verbatim image:Destroy() [in Lua 5] \endverbatim
 * \ingroup imgclass */
void imImageDestroy(imImage* image);

/** Adds an alpha channel plane and sets its value to 0 (transparent).
 *
 * \verbatim image:AddAlpha() [in Lua 5] \endverbatim
 * \ingroup imgclass */
void imImageAddAlpha(imImage* image);

/** Sets the alpha channel plane to a constant.
 *
 * \verbatim image:SetAlpha(alpha: number) [in Lua 5] \endverbatim
 * \ingroup imgclass */
void imImageSetAlpha(imImage* image, double alpha);

/** Removes the alpha channel plane if any.
 *
 * \verbatim image:RemoveAlpha() [in Lua 5] \endverbatim
 * \ingroup imgclass */
void imImageRemoveAlpha(imImage* image);

/** Changes the buffer size. Reallocate internal buffers if the new size is larger than the original.
 *
 * \verbatim image:Reshape(width: number, height: number) [in Lua 5] \endverbatim
 * \ingroup imgclass */
void imImageReshape(imImage* image, int width, int height);

/** Copy image data and attributes from one image to another. \n
 * Images must have the same size and type.
 *
 * \verbatim image:Copy(dst_image: imImage) [in Lua 5] \endverbatim
 * \ingroup imgclass */
void imImageCopy(const imImage* src_image, imImage* dst_image);

/** Copy image data only fom one image to another. \n
 * Images must have the same size and type.
 *
 * \verbatim image:CopyData(dst_image: imImage) [in Lua 5] \endverbatim
 * \ingroup imgclass */
void imImageCopyData(const imImage* src_image, imImage* dst_image);

/** Copies the image attributes from src to dst.
 * Includes the pallete if defined in both images.
 *
 * \verbatim image:CopyAttributes(dst_image: imImage) [in Lua 5] \endverbatim
 * \ingroup imgclass */
void imImageCopyAttributes(const imImage* src_image, imImage* dst_image);

/** Merges the image attributes from src to dst. \n
 * Attributes that exist in dst are not replaced. 
 * Doens NOT include the pallete.
 *
 * \verbatim image:MergeAttributes(dst_image: imImage) [in Lua 5] \endverbatim
 * \ingroup imgclass */
void imImageMergeAttributes(const imImage* src_image, imImage* dst_image);

/** Copy one image plane fom one image to another. \n
 * Images must have the same size and type.
 *
 * \verbatim image:CopyPlane(src_plane: number, dst_image: imImage, dst_plane: number) [in Lua 5] \endverbatim
 * \ingroup imgclass */
void imImageCopyPlane(const imImage* src_image, int src_plane, imImage* dst_image, int dst_plane);

/** Creates a copy of the image.
 *
 * \verbatim image:Duplicate() -> new_image: imImage [in Lua 5] \endverbatim
 * \ingroup imgclass */
imImage* imImageDuplicate(const imImage* image);

/** Creates a clone of the image. i.e. same attributes but ignore contents.
 *
 * \verbatim image:Clone() -> new_image: imImage [in Lua 5] \endverbatim
 * \ingroup imgclass */
imImage* imImageClone(const imImage* image);

/** Changes an extended attribute. \n
 * The data will be internally duplicated. \n
 * If data is NULL and count==0 the attribute is removed. \n
 * If count is -1 and data_type is IM_BYTE then data is zero terminated.
 * See also \ref imDataType.
 *
 * \verbatim image:SetAttribute(attrib: string, data_type: number, data: table of numbers or string) [in Lua 5] \endverbatim
 * If data_type is IM_BYTE, a string can be used as data.
 * \ingroup imgclass */
void imImageSetAttribute(const imImage* image, const char* attrib, int data_type, int count, const void* data);

/** Changes an extended attribute as an integer.
*
* \verbatim image:SetAttribInteger(attrib: string, data_type: number, value: number) [in Lua 5] \endverbatim
* \ingroup imgclass */
void imImageSetAttribInteger(const imImage* image, const char* attrib, int data_type, int value);

/** Changes an extended attribute as a real.
*
* \verbatim image:SetAttribReal(attrib: string, data_type: number, value: number) [in Lua 5] \endverbatim
* \ingroup imgclass */
void imImageSetAttribReal(const imImage* image, const char* attrib, int data_type, double value);

/** Changes an extended attribute as a string.
*
* \verbatim image:SetAttribString(attrib: string, value: string) [in Lua 5] \endverbatim
* \ingroup imgclass */
void imImageSetAttribString(const imImage* image, const char* attrib, const char* value);

/** Returns an extended attribute. \n
 * Returns NULL if not found.
 * See also \ref imDataType.
 *
 * \verbatim image:GetAttribute(attrib: string, [as_string: boolean]) -> data: table of numbers or string, data_type: number [in Lua 5] \endverbatim
 * If data_type is IM_BYTE, as_string can be used to return a string instead of a table.
 * \ingroup imgclass */
const void* imImageGetAttribute(const imImage* image, const char* attrib, int *data_type, int *count);

/** Returns an extended attribute as an integer.
*
* \verbatim image:GetAttribInteger(attrib: string, [index: number]) -> value: number [in Lua 5] \endverbatim
* \ingroup imgclass */
int imImageGetAttribInteger(const imImage* image, const char* attrib, int index);

/** Returns an extended attribute as a real.
*
* \verbatim image:GetAttribReal(attrib: string, [index: number]) -> value: number [in Lua 5] \endverbatim
* \ingroup imgclass */
double imImageGetAttribReal(const imImage* image, const char* attrib, int index);

/** Returns an extended attribute as a string.
*
* \verbatim image:GetAttribString(attrib: string) -> value: string [in Lua 5] \endverbatim
* \ingroup imgclass */
const char* imImageGetAttribString(const imImage* image, const char* attrib);

/** Returns a list of the attribute names. \n
 * "attrib" must contain room enough for "attrib_count" names. Use "attrib=NULL" to return only the count.
 *
 * \verbatim image:GetAttributeList() -> data: table of strings [in Lua 5] \endverbatim
 * \ingroup imgclass */
void imImageGetAttributeList(const imImage* image, char** attrib, int *attrib_count);

/** Sets all image data to zero. But if color space is YCBCR, LAB or LUV, and data type is BYTE or USHORT, then
 * data is initialized with 128 or 32768 accordingly. Alpha is initialized as transparent (0).
 *
 * \verbatim image:Clear() [in Lua 5] \endverbatim
 * \ingroup imgclass */
void imImageClear(imImage* image);

/** Indicates that the image can be viewed in common graphic devices.     
 * Data type must be IM_BYTE. Color mode can be IM_RGB, IM_MAP, IM_GRAY or IM_BINARY.
 *
 * \verbatim image:IsBitmap() -> is_bitmap: boolean [in Lua 5] \endverbatim
 * \ingroup imgclass */
int imImageIsBitmap(const imImage* image);

/** Changes the image palette.
 * This will destroy the existing palette and replace it with the given palette pointer.
 * Only the pointer is stored, so the palette should be a new palette and it can not be a static array.
 *
 * \verbatim image:SetPalette(palette: imPalette) [in Lua 5] \endverbatim
 * \ingroup imgclass */
void imImageSetPalette(imImage* image, long* palette, int palette_count);

/** Returns 1 if the images match width and height. Returns 0 otherwise.
 *
 * \verbatim image:MatchSize(image2: imImage) -> match: boolean [in Lua 5] \endverbatim
 * \ingroup imgclass */
int imImageMatchSize(const imImage* image1, const imImage* image2);

/** Returns 1 if the images match color mode and data type. Returns 0 otherwise.
 *
 * \verbatim image:MatchColor(image2: imImage) -> match: boolean [in Lua 5] \endverbatim
 * \ingroup imgclass */
int imImageMatchColor(const imImage* image1, const imImage* image2);

/** Returns 1 if the images match width, height and data type. Returns 0 otherwise.
 *
 * \verbatim image:MatchDataType(image2: imImage) -> match: boolean [in Lua 5] \endverbatim
 * \ingroup imgclass */
int imImageMatchDataType(const imImage* image1, const imImage* image2);

/** Returns 1 if the images match width, height and color space. Returns 0 otherwise.
 *
 * \verbatim image:MatchColorSpace(image2: imImage) -> match: boolean [in Lua 5] \endverbatim
 * \ingroup imgclass */
int imImageMatchColorSpace(const imImage* image1, const imImage* image2);

/** Returns 1 if the images match in width, height, data type and color space. Returns 0 otherwise.
 *
 * \verbatim image:Match(image2: imImage) -> match: boolean [in Lua 5] \endverbatim
 * \ingroup imgclass */
int imImageMatch(const imImage* image1, const imImage* image2);

/** Changes the image color space to map
 * by just changing color_space. \n
 * Image must be BINARY or GRAY/BYTE.
 *
 * \verbatim image:SetMap() [in Lua 5] \endverbatim
 * \ingroup imgclass */
void imImageSetMap(imImage* image);

/** Changes the image color space to binary 
 * by just changing color_space and the palette.
 * Image must be MAP or GRAY/BYTE.
 *
 * \verbatim image:SetBinary() [in Lua 5] \endverbatim
 * \ingroup imgclass */
void imImageSetBinary(imImage* image);

/** Changes the image color space to gray
 * by just changing color_space and the palette.
 * Image must be BINARY or MAP. Palette is changed only if image was BINARY.
 *
 * \verbatim image:SetGray() [in Lua 5] \endverbatim
 * \ingroup imgclass */
void imImageSetGray(imImage* image);

/** Changes a gray BYTE data (0,255) into a binary data (0,1), done in-place. 
 * Color space is not changed. Data type must be IM_BYTE.
 *
 * \verbatim image:MakeBinary() [in Lua 5] \endverbatim
 * \ingroup imgclass */
void imImageMakeBinary(imImage *image);

/** Changes a binary data (0,1) into a gray BYTE data (0,255), done in-place. 
 * Color space is not changed. Data type must be IM_BYTE.
 *
 * \verbatim image:MakeGray() [in Lua 5] \endverbatim
 * \ingroup imgclass */
void imImageMakeGray(imImage *image);



/** \defgroup imgfile imImage Storage
 *
 * \par
 *  Functions to simplify the process of reading and writting imImage structures. 
 *  Will also load and save the alpha planes when possible.
 * \par
 * See \ref im_image.h
 * \ingroup file */


/** Loads an image from an already open file. Returns NULL if failed. \n
 * This will call \ref imFileReadImageInfo and \ref imFileReadImageData. \n
 * index specifies the image number between 0 and image_count-1. \n
 * The returned image will be of the same color_space and data_type of the image in the file. \n
 * Attributes from the file will be stored at the image.
 * See also \ref imErrorCodes.
 *
 * \verbatim ifile:LoadImage([index: number]) -> image: imImage, error: number [in Lua 5] \endverbatim
 * Default index is 0.
 * \ingroup imgfile */
imImage* imFileLoadImage(imFile* ifile, int index, int *error);

/** Loads an image from an already open file. Returns NULL if failed. \n
 * This function assumes that the image in the file has the same parameters as the given image. \n
 * This will call \ref imFileReadImageInfo and \ref imFileReadImageData. \n
 * index specifies the image number between 0 and image_count-1. \n
 * The returned image will be of the same color_space and data_type of the image in the file. \n
 * Attributes from the file will be stored at the image.
 * See also \ref imErrorCodes.
 *
 * \verbatim ifile:LoadImageFrame(index: number, image: imImage) -> error: number [in Lua 5] \endverbatim
 * Default index is 0.
 * \ingroup imgfile */
void imFileLoadImageFrame(imFile* ifile, int index, imImage* image, int *error);

/** Loads an image from an already open file, but forces the image to be a bitmap.\n
 * The returned imagem will be always a Bitmap image, with color_space RGB, MAP, GRAY or BINARY, and data_type IM_BYTE. \n
 * index specifies the image number between 0 and image_count-1. \n
 * Returns NULL if failed.
 * Attributes from the file will be stored at the image.
 * See also \ref imErrorCodes.
 *
 * \verbatim ifile:LoadBitmap([index: number]) -> image: imImage, error: number [in Lua 5] \endverbatim
 * Default index is 0.
 * \ingroup imgfile */
imImage* imFileLoadBitmap(imFile* ifile, int index, int *error);

/** Loads an image region from an already open file. Returns NULL if failed. \n
 * This will call \ref imFileReadImageInfo and \ref imFileReadImageData. \n
 * index specifies the image number between 0 and image_count-1. \n
 * The returned image will be of the same color_space and data_type of the image in the file, 
 * or will be a Bitmap image. \n
 * Attributes from the file will be stored at the image.
 * See also \ref imErrorCodes. \n
 * For now, it works only for the ECW file format.
 *
 * \verbatim ifile:LoadRegion(index, bitmap, xmin, xmax, ymin, ymax, width, height: number) -> image: imImage, error: number [in Lua 5] \endverbatim
 * Default index is 0.
 * \ingroup imgfile */
imImage* imFileLoadImageRegion(imFile* ifile, int index, int bitmap, int *error, 
                               int xmin, int xmax, int ymin, int ymax, int width, int height);

/** Loads an image from an already open file, but forces the image to be a bitmap.\n
 * This function assumes that the image in the file has the same parameters as the given image. \n
 * The imagem must be a Bitmap image, with color_space RGB, MAP, GRAY or BINARY, and data_type IM_BYTE. \n
 * index specifies the image number between 0 and image_count-1. \n
 * Returns NULL if failed.
 * Attributes from the file will be stored at the image.
 * See also \ref imErrorCodes.
 *
 * \verbatim ifile:LoadBitmapFrame(index: number, image: imImage) -> error: number [in Lua 5] \endverbatim
 * Default index is 0.
 * \ingroup imgfile */
void imFileLoadBitmapFrame(imFile* ifile, int index, imImage* image, int *error);

/** Saves the image to an already open file. \n
 * This will call \ref imFileWriteImageInfo and \ref imFileWriteImageData. \n
 * Attributes from the image will be stored at the file.
 * Returns error code.
 *
 * \verbatim ifile:SaveImage(image: imImage) -> error: number [in Lua 5] \endverbatim
 * \ingroup imgfile */
int imFileSaveImage(imFile* ifile, const imImage* image);

/** Loads an image from file. Open, loads and closes the file. \n
 * index specifies the image number between 0 and image_count-1. \n
 * Returns NULL if failed.
 * Attributes from the file will be stored at the image.
 * See also \ref imErrorCodes.
 *
 * \verbatim im.FileImageLoad(file_name: string, [index: number]) -> image: imImage, error: number [in Lua 5] \endverbatim
 * Default index is 0.
 * \ingroup imgfile */
imImage* imFileImageLoad(const char* file_name, int index, int *error);

/** Loads an image from file, but forces the image to be a bitmap. Open, loads and closes the file. \n
 * index specifies the image number between 0 and image_count-1. \n
 * Returns NULL if failed.
 * Attributes from the file will be stored at the image.
 * See also \ref imErrorCodes.
 *
 * \verbatim im.FileImageLoadBitmap(file_name: string, [index: number]) -> image: imImage, error: number [in Lua 5] \endverbatim
 * Default index is 0.
 * \ingroup imgfile */
imImage* imFileImageLoadBitmap(const char* file_name, int index, int *error);

/** Loads an image region from file. Open, loads and closes the file. \n
 * index specifies the image number between 0 and image_count-1. \n
 * Returns NULL if failed.
 * Attributes from the file will be stored at the image.
 * See also \ref imErrorCodes. \n
 * For now, it works only for the ECW file format.
 *
 * \verbatim im.FileImageLoadRegion(file_name: string, index, bitmap, xmin, xmax, ymin, ymax, width, height: number, ) -> image: imImage, error: number [in Lua 5] \endverbatim
 * Default index is 0.
 * \ingroup imgfile */
imImage* imFileImageLoadRegion(const char* file_name, int index, int bitmap, int *error, 
                               int xmin, int xmax, int ymin, int ymax, int width, int height);

/** Saves the image to file. Open, saves and closes the file. \n
 * Returns error code. \n
 * Attributes from the image will be stored at the file.
 *
 * \verbatim im.FileImageSave(file_name: string, format: string, image: imImage) -> error: number [in Lua 5] \endverbatim
 * \verbatim image:Save(file_name: string, format: string) -> error: number [in Lua 5] \endverbatim
 * \ingroup imgfile */
int imFileImageSave(const char* file_name, const char* format, const imImage* image);



/** Utility macro to draw the image in a CD library canvas.
 * Works only for data_type IM_BYTE, and color spaces: IM_RGB, IM_MAP, IMGRAY and IM_BINARY.
 * \ingroup imgclass */
#define imcdCanvasPutImage(_canvas, _image, _x, _y, _w, _h, _xmin, _xmax, _ymin, _ymax)     \
  {                                                                         \
    if (_image->color_space == IM_RGB)                                      \
    {                                                                       \
      if (_image->has_alpha)                                                \
        cdCanvasPutImageRectRGBA(_canvas, _image->width, _image->height,    \
                          (unsigned char*)_image->data[0],                  \
                          (unsigned char*)_image->data[1],                  \
                          (unsigned char*)_image->data[2],                  \
                          (unsigned char*)_image->data[3],                  \
                          _x, _y, _w, _h, _xmin, _xmax, _ymin, _ymax);      \
      else                                                                  \
        cdCanvasPutImageRectRGB(_canvas, _image->width, _image->height,     \
                          (unsigned char*)_image->data[0],                  \
                          (unsigned char*)_image->data[1],                  \
                          (unsigned char*)_image->data[2],                  \
                          _x, _y, _w, _h, _xmin, _xmax, _ymin, _ymax);      \
    }                                                                       \
    else                                                                    \
      cdCanvasPutImageRectMap(_canvas, _image->width, _image->height,       \
                        (unsigned char*)_image->data[0], _image->palette,   \
                        _x, _y, _w, _h, _xmin, _xmax, _ymin, _ymax);        \
  }                                                                               


#if	defined(__cplusplus)
}
#endif

#endif
