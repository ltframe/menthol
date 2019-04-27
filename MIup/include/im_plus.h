/** \file
 * \brief Name space for C++ high level API
 *
 * See Copyright Notice in im_lib.h
 */

#ifndef __IM_PLUS_H
#define __IM_PLUS_H


#include "im.h"
#include "im_lib.h"
#include "im_raw.h"
#include "im_image.h"
#include "im_palette.h"
#include "im_kernel.h"
#include "im_capture.h"
#include "im_process.h"
#include "im_counter.h"
#include "im_convert.h"
#include "im_attrib_flat.h"



/** \brief Name space for C++ high level API
 *
 * \par
 * Defines wrapper classes for all C structures.
 *
 * See \ref im_plus.h
 */
namespace im
{
  inline const char* Version() { return imVersion(); }
  inline const char* VersionDate() { return imVersionDate(); }
  inline int VersionNumber() { return imVersionNumber(); }


  class Palette
  {
  protected:
    long* pal;
    int count;

  public:
    Palette(int pal_count = 256) {
      count = pal_count;
      pal = imPaletteNew(count); }
    Palette(long* palette, int pal_count = 256) {
      count = pal_count;
      pal = palette; }
    Palette(const Palette& src_palette) {
      count = src_palette.count;
      pal = imPaletteDuplicate(src_palette.pal, src_palette.count); }
    virtual ~Palette() {
      if (pal)
        imPaletteRelease(pal);
    }

    long* GetData() const { return pal; }
    int Count() const { return count; }

    long& operator [] (int index) {
      static long err = -1;
      if (!pal || index < 0 || index >= count)
        return err;
      return pal[index]; 
    }


    int FindNearest(long color) const {
      return imPaletteFindNearest(pal, count, color); }
    int FindColor(long color, unsigned char tol) {
      return imPaletteFindColor(pal, count, color, tol); }

    static long ColorEncode(unsigned char red, unsigned char green, unsigned char blue) {
      return (((long)red) << 16) | (((long)green) << 8) | ((long)blue); }
    static unsigned char ColorRed(long color) {
      return (unsigned char)(color >> 16); }
    static unsigned char ColorGreen(long color) {
      return (unsigned char)(color >> 8); }
    static unsigned char ColorBlue(long color) {
      return (unsigned char)color; }

    /* pre-defined palettes */
    static Palette Gray() {
      return Palette(imPaletteGray()); }
    static Palette Red() {
      return Palette(imPaletteRed()); }
    static Palette Green() {
      return Palette(imPaletteGreen()); }
    static Palette Blue() {
      return Palette(imPaletteBlue()); }
    static Palette Yellow() {
      return Palette(imPaletteYellow()); }
    static Palette Magenta() {
      return Palette(imPaletteMagenta()); }
    static Palette Cyan() {
      return Palette(imPaletteCyan()); }
    static Palette Rainbow() {
      return Palette(imPaletteRainbow()); }
    static Palette Hues() {
      return Palette(imPaletteHues()); }
    static Palette BlueIce() {
      return Palette(imPaletteBlueIce()); }
    static Palette HotIron() {
      return Palette(imPaletteHotIron()); }
    static Palette BlackBody() {
      return Palette(imPaletteBlackBody()); }
    static Palette HighContrast() {
      return Palette(imPaletteHighContrast()); }
    static Palette Linear() {
      return Palette(imPaletteLinear()); }

    static Palette Uniform() {
      return Palette(imPaletteUniform()); }
    static int UniformIndex(long color) {
      return imPaletteUniformIndex(color); }
    static int UniformIndexHalftoned(long color, int x, int y) {
      return imPaletteUniformIndexHalftoned(color, x, y); }
  };

  class AttribTable
  {
    imAttribTablePrivate* ptable;

    /* forbidden */
    AttribTable() {}

  public:

    AttribTable(int hash_size) {
      ptable = imAttribTableCreate(hash_size); }
    AttribTable(const AttribTable& attrib_table) {
      imAttribTableCopyFrom(ptable, attrib_table.ptable); }
    virtual ~AttribTable() {
      if (ptable)
        imAttribTableDestroy(ptable); 
    }

    int Count() const {
      return imAttribTableCount(ptable); }
    void RemoveAll() {
      imAttribTableRemoveAll(ptable); }

    void MergeFrom(const AttribTable& attrib_table) {
      imAttribTableMergeFrom(ptable, attrib_table.ptable); }

    void Set(const char* name, int data_type, int count, const void* data) {
      imAttribTableSet(ptable, name, data_type, count, data); }
    void SetInteger(const char* name, int data_type, int value) {
      imAttribTableSetInteger(ptable, name, data_type, value); }
    void SetReal(const char* name, int data_type, double value) {
      imAttribTableSetReal(ptable, name, data_type, value); }
    void SetString(const char* name, const char* value) {
      imAttribTableSetString(ptable, name, value); }
    void Reset(const char *name) {
      imAttribTableUnSet(ptable, name); }

    const void* Get(const char *name, int *data_type = 0, int *count = 0) const {
      return imAttribTableGet(ptable, name, data_type, count); }
    int GetInteger(const char *name, int index = 0) const {
      return imAttribTableGetInteger(ptable, name, index); }
    double GetReal(const char *name, int index = 0) const {
      return imAttribTableGetReal(ptable, name, index); }
    const char* GetString(const char *name) const {
      return imAttribTableGetString(ptable, name); }

    void ForEach(void* user_data, imAttribTableCallback attrib_func) const {
      imAttribTableForEach(ptable, user_data, attrib_func); }
  };


  class ImageChannelLine
  {
    imImage* image;
    int lin;
    void* channel_buffer;

  public:
    ImageChannelLine(imImage* ref_image, int ref_lin, void* ref_channel_buffer)
      : image(ref_image), lin(ref_lin), channel_buffer(ref_channel_buffer) { }

    double operator [] (int col) {
      if (image == 0 || col < 0 || col >= image->width)
        return 0;
      else
      {
        int index = lin * image->width + col;

        switch (image->data_type)
        {
        case IM_BYTE:
          {
            unsigned char *bdata = (unsigned char*)channel_buffer;
            return (double)bdata[index];
          }
        case IM_SHORT:
          {
            short *sdata = (short*)channel_buffer;
            return (double)sdata[index];
          }
        case IM_USHORT:
          {
            unsigned short *udata = (unsigned short*)channel_buffer;
            return (double)udata[index];
          }
        case IM_INT:
          {
            int *idata = (int*)channel_buffer;
            return (double)idata[index];
          }
        case IM_FLOAT:
          {
            float *fdata = (float*)channel_buffer;
            return (double)fdata[index];
          }
        case IM_DOUBLE:
          {
            double *fdata = (double*)channel_buffer;
            return fdata[index];
          }
        }

        return 0;
      }
    }
  };


  class ImageChannel
  {
    imImage* image;
    int plane;

  public:
    ImageChannel(imImage* ref_image, int ref_plane)
      : image(ref_image), plane(ref_plane) {
    }

    ImageChannelLine operator [] (int lin) {
      if (image == 0 || lin < 0 || lin >= image->height)
        return ImageChannelLine(0, 0, 0);
      else
        return ImageChannelLine(image, lin, image->data[plane]); 
    }
  };


  class Image
  {
  protected:
    imImage* im_image;

    /* forbidden */
    Image() { im_image = 0; };

    void IncRef() 
    {
      int image_ref = GetAttribInteger("_IMAGE_REF");
      image_ref++;
      SetAttribInteger("_IMAGE_REF", IM_INT, image_ref); 
    }
    bool DecRef() 
    {
      int image_ref = GetAttribInteger("_IMAGE_REF");
      if (image_ref > 0)
      {
        image_ref--;
        SetAttribInteger("_IMAGE_REF", IM_INT, image_ref);
      }
      return image_ref == 0; 
    }

  public:
    Image(int width, int height, int color_space, int data_type) {
      im_image = imImageCreate(width, height, color_space, data_type);
      IncRef(); 
    }
    Image(const Image& src_image, int width, int height, int color_space, int data_type) {
      im_image = imImageCreateBased(src_image.im_image, width, height, color_space, data_type);
      IncRef(); 
    }
    Image(const char* file_name, int index, int &error, bool as_bitmap) {
      if (as_bitmap)
        im_image = imFileImageLoad(file_name, index, &error);
      else
        im_image = imFileImageLoadBitmap(file_name, index, &error);
      IncRef(); 
    }
    Image(const Image& ref_image) {
      im_image = ref_image.im_image;
      IncRef(); 
    }
    Image(imImage* ref_image) {
      im_image = ref_image;
      IncRef(); 
    }
    virtual ~Image() {
      if (im_image)
      {
        if (DecRef())
          imImageDestroy(im_image);
      }
    }

    imImage* GetHandle() const { return im_image; }


    bool Failed() const {
      return im_image == 0; }

    /* image[plane][line][column] */
    ImageChannel operator [] (int plane) {
      int depth = im_image->has_alpha? im_image->depth + 1 : im_image->depth;
      if (plane < 0 || plane >= depth)
        return ImageChannel(0, 0);
      else
        return ImageChannel(im_image, plane); 
    }

    /* image info */
    int Width() const {
      return im_image->width; }
    int Height() const {
      return im_image->height; }
    int ColorSpace() const {
      return im_image->color_space; }
    int DataType() const {
      return im_image->data_type; }
    bool HasAlpha() const {
      return im_image->has_alpha != 0; }
    int Depth() const {
      return im_image->depth; }
    bool IsBitmap() const {
      return imImageIsBitmap(im_image) == 1; }


    /* image io */
    int Save(const char* file_name, const char* format) {
      return imFileImageSave(file_name, format, im_image); }

    void SetValue(int plane, int lin, int col, double value) {
      int depth = im_image->has_alpha ? im_image->depth + 1 : im_image->depth;
      if (plane < 0 || plane >= depth)
        return;
      if (lin < 0 || lin >= im_image->height)
        return;
      if (col < 0 || col >= im_image->width)
        return;

      int index = lin * im_image->width + col;
      void* channel_buffer = im_image->data[plane];

      switch (im_image->data_type)
      {
      case IM_BYTE:
      {
        unsigned char *bdata = (unsigned char*)channel_buffer;
        bdata[index] = (unsigned char)value;
      }
      case IM_SHORT:
      {
        short *sdata = (short*)channel_buffer;
        sdata[index] = (short)value;
      }
      case IM_USHORT:
      {
        unsigned short *udata = (unsigned short*)channel_buffer;
        udata[index] = (unsigned short)value;
      }
      case IM_INT:
      {
        int *idata = (int*)channel_buffer;
        idata[index] = (int)value;
      }
      case IM_FLOAT:
      {
        float *fdata = (float*)channel_buffer;
        fdata[index] = (float)value;
      }
      case IM_DOUBLE:
      {
        double *fdata = (double*)channel_buffer;
        fdata[index] = value;
      }
      }
    }
    double GetValue(int plane, int lin, int col) {
      int depth = im_image->has_alpha ? im_image->depth + 1 : im_image->depth;
      if (plane < 0 || plane >= depth)
        return 0;
      if (lin < 0 || lin >= im_image->height)
        return 0;
      if (col < 0 || col >= im_image->width)
        return 0;

      int index = lin * im_image->width + col;
      void* channel_buffer = im_image->data[plane];

      switch (im_image->data_type)
      {
        case IM_BYTE:
        {
          unsigned char *bdata = (unsigned char*)channel_buffer;
          return (double)bdata[index];
        }
        case IM_SHORT:
        {
          short *sdata = (short*)channel_buffer;
          return (double)sdata[index];
        }
        case IM_USHORT:
        {
          unsigned short *udata = (unsigned short*)channel_buffer;
          return (double)udata[index];
        }
        case IM_INT:
        {
          int *idata = (int*)channel_buffer;
          return (double)idata[index];
        }
        case IM_FLOAT:
        {
          float *fdata = (float*)channel_buffer;
          return (double)fdata[index];
        }
        case IM_DOUBLE:
        {
          double *fdata = (double*)channel_buffer;
          return fdata[index];
        }
      }

      return 0; }

    /* copy utilities */
    Image Duplicate() {
      return Image(imImageDuplicate(im_image)); }
    void Copy(Image& dst_image) const {
      imImageCopy(im_image, dst_image.im_image); }
    void CopyAttributes(Image& dst_image) const {
      imImageCopyAttributes(im_image, dst_image.im_image); }
    void MergeAttributes(Image& dst_image) const {
      imImageMergeAttributes(im_image, dst_image.im_image); }
    void CopyData(Image& dst_image) const {
      imImageCopyData(im_image, dst_image.im_image); }
    void CopyPlane(Image& dst_image, int src_plane, int dst_plane) const {
      imImageCopyPlane(im_image, src_plane, dst_image.im_image, dst_plane); }


    /* initialization utilities */
    void Clear() {
      imImageClear(im_image); }
    void Reshape(int width, int height) {
      imImageReshape(im_image, width, height); }


    /* palette */
    void SetPalette(const Palette& palette) {
      imImageSetPalette(im_image, imPaletteDuplicate(palette.GetData(), palette.Count()), palette.Count()); }
    Palette GetPalette() {
      return Palette(imPaletteDuplicate(im_image->palette, im_image->palette_count), im_image->palette_count); }


    /* alpha */
    void AddAlpha() {
      imImageAddAlpha(im_image); }
    void SetAlpha(double alpha) {
      imImageSetAlpha(im_image, alpha); }
    void RemoveAlpha() {
      imImageRemoveAlpha(im_image); }


    /* color utilities */
    void MakeBinary() {
      imImageMakeBinary(im_image); }
    void MakeGray() {
      imImageMakeGray(im_image); }
    void SetBinary() {
      imImageSetBinary(im_image); }
    void SetGray() {
      imImageSetGray(im_image); }
    void SetMap() {
      imImageSetMap(im_image); }


    /* attributes or metadata */
    void SetAttribute(const char* attrib, int data_type, int count, const void* data) {
      imImageSetAttribute(im_image, attrib, data_type, count, data); }
    void SetAttribInteger(const char* attrib, int data_type, int value) {
      imImageSetAttribInteger(im_image, attrib, data_type, value); }
    void SetAttribReal(const char* attrib, int data_type, double value) {
      imImageSetAttribReal(im_image, attrib, data_type, value); }
    void SetAttribString(const char* attrib, const char* value) {
      imImageSetAttribString(im_image, attrib, value); }

    const void* GetAttribute(const char* attrib, int *data_type = 0, int *count = 0) const {
      return imImageGetAttribute(im_image, attrib, data_type, count); }
    int GetAttribInteger(const char* attrib, int index = 0) const {
      return imImageGetAttribInteger(im_image, attrib, index); }
    double GetAttribReal(const char* attrib, int index = 0) const {
      return imImageGetAttribReal(im_image, attrib, index); }
    const char* GetAttribString(const char* attrib) const {
      return imImageGetAttribString(im_image, attrib); }

    void GetAttributeList(char** attrib, int &attrib_count) const {
      imImageGetAttributeList(im_image, attrib, &attrib_count); }


    /* compare */
    bool operator==(const Image& image2) const {
      return Match(image2); }
    bool Match(const Image& image2) const {
      return imImageMatch(im_image, image2.im_image) == 1; }
    bool MatchColor(const Image& image2) const {
      return imImageMatchColor(im_image, image2.im_image) == 1; }
    bool MatchColorSpace(const Image& image2) const {
      return imImageMatchColorSpace(im_image, image2.im_image) == 1; }
    bool MatchDataType(const Image& image2) const {
      return imImageMatchDataType(im_image, image2.im_image) == 1; }
    bool MatchSize(const Image& image2) const {
      return imImageMatchSize(im_image, image2.im_image) == 1; }


    /* conversion */
    int ConvertDataType(Image& dst_image, int cpx2real, double gamma, bool absolute, int cast_mode) const {
      return imConvertDataType(im_image, dst_image.im_image, cpx2real, gamma, absolute, cast_mode); }
    int ConvertColorSpace(Image& dst_image) const {
      return imConvertColorSpace(im_image, dst_image.im_image); }
    int ConvertToBitmap(Image& dst_image, int cpx2real, double gamma, bool absolute, int cast_mode) {
      return imConvertToBitmap(im_image, dst_image.im_image, cpx2real, gamma, absolute, cast_mode); }

  };


  /********************************************************************/


  class CounterCallback
  {
    void* cc_user_data;

    static int c_callback(int counter, void* user_data, const char* text, int progress) {
      CounterCallback* cc = (CounterCallback*)user_data;
      return cc->Callback(counter, cc->cc_user_data, text, progress); 
    }

  public:
    CounterCallback(void* user_data) {
      cc_user_data = user_data;
      imCounterSetCallback(this, c_callback); 
    }
    virtual ~CounterCallback() { }

    virtual int Callback(int counter, void* user_data, const char* text, int progress) = 0;
  };


  /********************************************************************/


  class File
  {
    friend class Image;

    /* forbidden */
    File(const File&) { }

  protected:
    imFile* im_file;

    File() { im_file = 0; }

  public:
    File(const char* file_name, int &error) {
      im_file = imFileOpen(file_name, &error); }
    File(const char* file_name, const char* format, int &error) {
      im_file = imFileNew(file_name, format, &error); }
    File(imFile* ref_file) {
      im_file = ref_file; }
    virtual ~File() {
      if (im_file) 
        imFileClose(im_file); 
    }

    bool Failed() const {
      return im_file == 0; }


    /* attributes or metadata */
    void SetAttribute(const char* attrib, int data_type, int count, const void* data) {
      imFileSetAttribute(im_file, attrib, data_type, count, data); }
    void SetAttribInteger(const char* attrib, int data_type, int value) {
      imFileSetAttribInteger(im_file, attrib, data_type, value); }
    void SetAttribReal(const char* attrib, int data_type, double value) {
      imFileSetAttribReal(im_file, attrib, data_type, value); }
    void SetAttribString(const char* attrib, const char* value) {
      imFileSetAttribString(im_file, attrib, value); }
    const void* GetAttribute(const char* attrib, int &data_type, int &count) const {
      return imFileGetAttribute(im_file, attrib, &data_type, &count); }
    int GetAttribInteger(const char* attrib, int index) const {
      return imFileGetAttribInteger(im_file, attrib, index); }
    double GetAttribReal(const char* attrib, int index) const {
      return imFileGetAttribReal(im_file, attrib, index); }
    const char* GetAttribString(const char* attrib) {
      return imFileGetAttribString(im_file, attrib); }


    /* file info */
    void GetInfo(char* format, char* compression, int &image_count) {
      imFileGetInfo(im_file, format, compression, &image_count); }
    void SetInfo(const char* compression) {
      imFileSetInfo(im_file, compression); }


    /* image io */
    Image LoadImage(int index, int &error) {
      return Image(imFileLoadImage(im_file, index, &error)); }
    int SaveImage(const Image& im_image) {
      return imFileSaveImage(im_file, im_image.GetHandle()); }
    void LoadFrame(int index, Image& im_image, int &error, bool as_bitmap) {
      if (as_bitmap)
        imFileLoadBitmapFrame(im_file, index, im_image.GetHandle(), &error);
      else
        imFileLoadImageFrame(im_file, index, im_image.GetHandle(), &error); }
  };


  /********************************************************************/


  class FileRaw : public File
  {
    /* forbidden */
    FileRaw() {}
    FileRaw(const FileRaw&) {}

  public:

    FileRaw(const char* file_name, int &error, bool new_file) : File() {
      if (new_file) 
        im_file = imFileNewRaw(file_name, &error);
      else 
        im_file = imFileOpenRaw(file_name, &error); 
    }
  };


  /********************************************************************/


  namespace Format
  {
    inline void RegisterInternal() {
      imFormatRegisterInternal(); }
    inline void RemoveAll() {
      imFormatRemoveAll(); }

    inline void List(char** format_list, int &format_count) {
      imFormatList(format_list, &format_count); }

    inline int Info(const char* format, char* desc, char* ext, int &can_sequence) {
      return imFormatInfo(format, desc, ext, &can_sequence); }
    inline int InfoExtra(const char* format, char* extra) {
      return imFormatInfoExtra(format, extra); }
    inline int Compressions(const char* format, char** comp, int &comp_count, int color_mode, int data_type) {
      return imFormatCompressions(format, comp, &comp_count, color_mode, data_type); }
    inline int CanWriteImage(const char* format, const char* compression, int color_mode, int data_type) {
      return imFormatCanWriteImage(format, compression, color_mode, data_type); }
  }


  /********************************************************************/


  namespace VideoCaptureDevice
  {
    inline void ReloadList() {
      imVideoCaptureReloadDevices(); }
    inline void ReleaseList() {
      imVideoCaptureReleaseDevices(); }

    inline int Count() 
    {
      return imVideoCaptureDeviceCount(); }

    inline const char* DeviceDescription(int device) 
    {
      return imVideoCaptureDeviceDesc(device); }
    inline const char* DeviceExtendedDescription(int device) 
    {
      return imVideoCaptureDeviceExDesc(device); }
    inline const char* DevicePath(int device) 
    {
      return imVideoCaptureDevicePath(device); }
    inline const char* DeviceVendorInfo(int device) 
    {
      return imVideoCaptureDeviceVendorInfo(device); }
  }


  /********************************************************************/


  class VideoCapture
  {
    imVideoCapture* im_vc;

    /* forbidden */
    VideoCapture(const VideoCapture&) {}

  public:
    VideoCapture() {
      im_vc = imVideoCaptureCreate(); }
    VideoCapture(imVideoCapture* ref_vc) {
      im_vc = ref_vc; }
    virtual ~VideoCapture() {
      if (im_vc) 
        imVideoCaptureDestroy(im_vc); }

    bool Failed() const {
      return im_vc == 0; }


    /* capture connection */
    int Connect(int device) {
      return imVideoCaptureConnect(im_vc, device); }
    void Disconnect() {
      imVideoCaptureDisconnect(im_vc); }
    bool SetInOut(int input, int output, int cross) {
      return imVideoCaptureSetInOut(im_vc, input, output, cross) != 0; }
    bool GetLive() const {
      return imVideoCaptureLive(im_vc, -1) == 1; }
    bool SetLive(int live) {
      return imVideoCaptureLive(im_vc, live) != 0; }


    /* configuration dialogs */
    int DialogCount() const {
      return imVideoCaptureDialogCount(im_vc); }
    bool ShowDialog(int dialog, void* parent) {
      return imVideoCaptureShowDialog(im_vc, dialog, parent) != 0; }
    const char* DialogDescription(int dialog) const {
      return imVideoCaptureDialogDesc(im_vc, dialog); }


    /* video format */
    int FormatCount() const {
      return imVideoCaptureFormatCount(im_vc); }
    bool GetFormatInfo(int format, int &width, int &height, char* desc) const {
      return imVideoCaptureGetFormat(im_vc, format, &width, &height, desc) != 0; }
    int GetFormat() const {
      return imVideoCaptureSetFormat(im_vc, -1); }
    bool SetFormat(int format) {
      return imVideoCaptureSetFormat(im_vc, format) != 0; }


    /* image info */
    void GetImageSize(int &width, int &height) const {
      imVideoCaptureGetImageSize(im_vc, &width, &height); }
    bool SetImageSize(int width, int height) {
      return imVideoCaptureSetImageSize(im_vc, width, height) != 0; }


    /* image capture */
    Image CaptureImage(bool as_gray) {
      int width, height;
      GetImageSize(width, height);
      return Image(imImageCreate(width, height, as_gray ? IM_GRAY : IM_RGB, IM_BYTE)); 
    }
    bool CaptureFrame(Image& dst_image, int timeout = -1) {
      imImage* image = dst_image.GetHandle();

      if (image->color_space != IM_GRAY && 
          image->color_space != IM_RGB &&
          image->data_type != IM_BYTE)
        return false;

      return imVideoCaptureFrame(im_vc, (unsigned char*)image->data[0], image->color_space, timeout) != 0; 
    }
    bool CaptureOneFrame(Image& dst_image) {
      imImage* image = dst_image.GetHandle();

      if (image->color_space != IM_GRAY &&
          image->color_space != IM_RGB &&
          image->data_type != IM_BYTE)
        return false;

      return imVideoCaptureOneFrame(im_vc, (unsigned char*)image->data[0], image->color_space) != 0; 
    }


    /* attributes */
    bool ResetAttribute(const char* attrib, int fauto) {
      return imVideoCaptureResetAttribute(im_vc, attrib, fauto) != 0; }
    bool GetAttribute(const char* attrib, double &percent) const {
      return imVideoCaptureGetAttribute(im_vc, attrib, &percent) != 0; }
    bool SetAttribute(const char* attrib, double percent) {
      return imVideoCaptureSetAttribute(im_vc, attrib, percent) != 0; }
    const char** GetAttributeList(int &num_attrib) const {
      return imVideoCaptureGetAttributeList(im_vc, &num_attrib); }
  };


  /********************************************************************/


  namespace Kernel
  {
    /* pre-defined kernels */
    inline Image Sobel() {
      return Image(imKernelSobel()); }
    inline Image Prewitt() {
      return Image(imKernelPrewitt()); }
    inline Image Kirsh() {
      return Image(imKernelKirsh()); }
    inline Image Laplacian4() {
      return Image(imKernelLaplacian4()); }
    inline Image Laplacian8() {
      return Image(imKernelLaplacian8()); }
    inline Image Laplacian5x5() {
      return Image(imKernelLaplacian5x5()); }
    inline Image Laplacian7x7() {
      return Image(imKernelLaplacian7x7()); }
    inline Image Gradian3x3() {
      return Image(imKernelGradian3x3()); }
    inline Image Gradian7x7() {
      return Image(imKernelGradian7x7()); }
    inline Image Sculpt() {
      return Image(imKernelSculpt()); }
    inline Image Mean3x3() {
      return Image(imKernelMean3x3()); }
    inline Image Mean5x5() {
      return Image(imKernelMean5x5()); }
    inline Image CircularMean5x5() {
      return Image(imKernelCircularMean5x5()); }
    inline Image Mean7x7() {
      return Image(imKernelMean7x7()); }
    inline Image CircularMean7x7() {
      return Image(imKernelCircularMean7x7()); }
    inline Image Gaussian3x3() {
      return Image(imKernelGaussian3x3()); }
    inline Image Gaussian5x5() {
      return Image(imKernelGaussian5x5()); }
    inline Image Barlett5x5() {
      return Image(imKernelBarlett5x5()); }
    inline Image TopHat5x5() {
      return Image(imKernelTopHat5x5()); }
    inline Image TopHat7x7() {
      return Image(imKernelTopHat7x7()); }
    inline Image Enhance() {
      return Image(imKernelEnhance()); }
  }


  namespace Process
  {
    inline int GaussianStdDev2KernelSize(double stddev) {
      return imGaussianStdDev2KernelSize(stddev); }
    inline double GaussianKernelSize2StdDev(int kernel_size) {
      return imGaussianKernelSize2StdDev(kernel_size); }
    inline void CalcRotateSize(int width, int height, int &new_width, int &new_height, double cos0, double sin0) {
      imProcessCalcRotateSize(width, height, &new_width, &new_height, cos0, sin0); }
    inline int OpenMPSetMinCount(int min_count) {
      return imProcessOpenMPSetMinCount(min_count); }
    inline int OpenMPSetNumThreads(int thread_count) {
      return imProcessOpenMPSetNumThreads(thread_count); }

    inline int HoughLines(const Image& src_image, Image& dst_image) {
      return imProcessHoughLines(src_image.GetHandle(), dst_image.GetHandle()); }
    inline int HoughLinesDraw(const Image& src_image, const Image& hough, const Image& hough_points, Image& dst_image) {
      return imProcessHoughLinesDraw(src_image.GetHandle(), hough.GetHandle(), hough_points.GetHandle(), dst_image.GetHandle()); }
    inline void CrossCorrelation(const Image& src_image1, const Image& src_image2, Image& dst_image) {
      imProcessCrossCorrelation(src_image1.GetHandle(), src_image2.GetHandle(), dst_image.GetHandle()); }
    inline void AutoCorrelation(const Image& src_image, Image& dst_image) {
      imProcessAutoCorrelation(src_image.GetHandle(), dst_image.GetHandle()); }
    inline void DistanceTransform(const Image& src_image, Image& dst_image) {
      imProcessDistanceTransform(src_image.GetHandle(), dst_image.GetHandle()); }
    inline void RegionalMaximum(const Image& src_image, Image& dst_image) {
      imProcessRegionalMaximum(src_image.GetHandle(), dst_image.GetHandle()); }
    inline void FFT(const Image& src_image, Image& dst_image) {
      imProcessFFT(src_image.GetHandle(), dst_image.GetHandle()); }
    inline void IFFT(const Image& src_image, Image& dst_image) {
      imProcessIFFT(src_image.GetHandle(), dst_image.GetHandle()); }
    inline int UnaryPointOp(const Image& src_image, Image& dst_image, imUnaryPointOpFunc func, double* params, void* userdata, const char* op_name) {
      return imProcessUnaryPointOp(src_image.GetHandle(), dst_image.GetHandle(), func, params, userdata, op_name); }
    inline int UnaryPointColorOp(const Image& src_image, Image& dst_image, imUnaryPointColorOpFunc func, double* params, void* userdata, const char* op_name) {
      return imProcessUnaryPointColorOp(src_image.GetHandle(), dst_image.GetHandle(), func, params, userdata, op_name); }
    inline int MultiPointOp(const Image *src_image_list, int src_image_count, Image& dst_image, imMultiPointOpFunc func, double* params, void* userdata, const char* op_name) {
      imImage** c_src_image_list = new imImage*[src_image_count];
      for (int i = 0; i < src_image_count; i++) c_src_image_list[i] = src_image_list[i].GetHandle();
      int ret = imProcessMultiPointOp((const imImage**)c_src_image_list, src_image_count, dst_image.GetHandle(), func, params, userdata, op_name);
      delete[] c_src_image_list;
      return ret; }
    inline int MultiPointColorOp(const Image *src_image_list, int src_image_count, Image& dst_image, imMultiPointColorOpFunc func, double* params, void* userdata, const char* op_name) {
      imImage** c_src_image_list = new imImage*[src_image_count];
      for (int i = 0; i < src_image_count; i++) c_src_image_list[i] = src_image_list[i].GetHandle();
      int ret = imProcessMultiPointColorOp((const imImage**)c_src_image_list, src_image_count, dst_image.GetHandle(), func, params, userdata, op_name);
      delete[] c_src_image_list;
      return ret; }
    inline void UnArithmeticOp(const Image& src_image, Image& dst_image, int op) {
      imProcessUnArithmeticOp(src_image.GetHandle(), dst_image.GetHandle(), op); }
    inline void ArithmeticOp(const Image& src_image1, const Image& src_image2, Image& dst_image, int op) {
      imProcessArithmeticOp(src_image1.GetHandle(), src_image2.GetHandle(), dst_image.GetHandle(), op); }
    inline void ArithmeticConstOp(const Image& src_image, double src_const, Image& dst_image, int op) {
      imProcessArithmeticConstOp(src_image.GetHandle(), src_const, dst_image.GetHandle(), op); }
    inline void BlendConst(const Image& src_image1, const Image& src_image2, Image& dst_image, double alpha) {
      imProcessBlendConst(src_image1.GetHandle(), src_image2.GetHandle(), dst_image.GetHandle(), alpha); }
    inline void Blend(const Image& src_image1, const Image& src_image2, const Image& alpha_image, Image& dst_image) {
      imProcessBlend(src_image1.GetHandle(), src_image2.GetHandle(), alpha_image.GetHandle(), dst_image.GetHandle()); }
    inline void Compose(const Image& src_image1, const Image& src_image2, Image& dst_image) {
      imProcessCompose(src_image1.GetHandle(), src_image2.GetHandle(), dst_image.GetHandle()); }
    inline void SplitComplex(const Image& src_image, Image& dst_image1, Image& dst_image2, int polar) {
      imProcessSplitComplex(src_image.GetHandle(), dst_image1.GetHandle(), dst_image2.GetHandle(), polar); }
    inline void MergeComplex(const Image& src_image1, const Image& src_image2, Image& dst_image, int polar) {
      imProcessMergeComplex(src_image1.GetHandle(), src_image2.GetHandle(), dst_image.GetHandle(), polar); }
    inline void MultipleMean(const Image *src_image_list, int src_image_count, Image& dst_image) {
      imImage** c_src_image_list = new imImage*[src_image_count];
      for (int i = 0; i < src_image_count; i++) c_src_image_list[i] = src_image_list[i].GetHandle();
      imProcessMultipleMean((const imImage**)c_src_image_list, src_image_count, dst_image.GetHandle());
      delete[] c_src_image_list; 
    }
    inline void MultipleStdDev(const Image *src_image_list, int src_image_count, const Image& mean_image, Image& dst_image) {
      imImage** c_src_image_list = new imImage*[src_image_count];
      for (int i = 0; i < src_image_count; i++) c_src_image_list[i] = src_image_list[i].GetHandle();
      imProcessMultipleStdDev((const imImage**)c_src_image_list, src_image_count, mean_image.GetHandle(), dst_image.GetHandle());
      delete[] c_src_image_list; 
    }
    inline int MultipleMedian(const Image *src_image_list, int src_image_count, Image& dst_image) {
      imImage** c_src_image_list = new imImage*[src_image_count];
      for (int i = 0; i < src_image_count; i++) c_src_image_list[i] = src_image_list[i].GetHandle();
      return imProcessMultipleMedian((const imImage**)c_src_image_list, src_image_count, dst_image.GetHandle());
      delete[] c_src_image_list; 
    }
    inline int AutoCovariance(const Image& src_image, const Image& mean_image, Image& dst_image) {
      return imProcessAutoCovariance(src_image.GetHandle(), mean_image.GetHandle(), dst_image.GetHandle()); }
    inline void MultiplyConj(const Image& src_image1, const Image& src_image2, Image& dst_image) {
      imProcessMultiplyConj(src_image1.GetHandle(), src_image2.GetHandle(), dst_image.GetHandle()); }
    inline void BackSub(const Image& src_image1, const Image& src_image2, Image& dst_image, double tol, int diff) {
      imProcessBackSub(src_image1.GetHandle(), src_image2.GetHandle(), dst_image.GetHandle(), tol, diff); }
    inline void QuantizeRGBUniform(const Image& src_image, Image& dst_image, int do_dither) {
      imProcessQuantizeRGBUniform(src_image.GetHandle(), dst_image.GetHandle(), do_dither); }
    inline void QuantizeRGBMedianCut(const Image& src_image, Image& dst_image) {
      imProcessQuantizeRGBMedianCut(src_image.GetHandle(), dst_image.GetHandle()); }
    inline void QuantizeGrayUniform(const Image& src_image, Image& dst_image, int grays) {
      imProcessQuantizeGrayUniform(src_image.GetHandle(), dst_image.GetHandle(), grays); }
    inline void QuantizeGrayMedianCut(const Image& src_image, Image& dst_image, int grays) {
      imProcessQuantizeGrayMedianCut(src_image.GetHandle(), dst_image.GetHandle(), grays); }
    inline void ExpandHistogram(const Image& src_image, Image& dst_image, double percent) {
      imProcessExpandHistogram(src_image.GetHandle(), dst_image.GetHandle(), percent); }
    inline void EqualizeHistogram(const Image& src_image, Image& dst_image) {
      imProcessEqualizeHistogram(src_image.GetHandle(), dst_image.GetHandle()); }
    inline void SplitYChroma(const Image& src_image, Image& y_image, Image& chroma_image) {
      imProcessSplitYChroma(src_image.GetHandle(), y_image.GetHandle(), chroma_image.GetHandle()); }
    inline void SplitHSI(const Image& src_image, Image& h_image, Image& s_image, Image& i_image) {
      imProcessSplitHSI(src_image.GetHandle(), h_image.GetHandle(), s_image.GetHandle(), i_image.GetHandle()); }
    inline void MergeHSI(const Image& h_image, const Image& s_image, const Image& i_image, Image& dst_image) {
      imProcessMergeHSI(h_image.GetHandle(), s_image.GetHandle(), i_image.GetHandle(), dst_image.GetHandle()); }
    inline void SplitComponents(const Image& src_image, Image *dst_image_list) {
      imImage* c_dst_image_list[4];
      c_dst_image_list[0] = dst_image_list[0].GetHandle();
      c_dst_image_list[1] = dst_image_list[1].GetHandle();
      c_dst_image_list[2] = dst_image_list[2].GetHandle();
      if (src_image.Depth() == 4 || src_image.HasAlpha())
        c_dst_image_list[3] = dst_image_list[3].GetHandle();
      imProcessSplitComponents(src_image.GetHandle(), c_dst_image_list); 
    }
    inline void MergeComponents(const Image *src_image_list, Image& dst_image) {
      imImage* c_src_image_list[4];
      c_src_image_list[0] = src_image_list[0].GetHandle();
      c_src_image_list[1] = src_image_list[1].GetHandle();
      c_src_image_list[2] = src_image_list[2].GetHandle();
      if (dst_image.Depth() == 4 || dst_image.HasAlpha())
        c_src_image_list[3] = src_image_list[3].GetHandle();
      imProcessMergeComponents((const imImage**)c_src_image_list, dst_image.GetHandle()); 
    }
    inline void NormalizeComponents(const Image& src_image, Image& dst_image) {
      imProcessNormalizeComponents(src_image.GetHandle(), dst_image.GetHandle()); }
    inline void PseudoColor(const Image& src_image, Image& dst_image) {
      imProcessPseudoColor(src_image.GetHandle(), dst_image.GetHandle()); }
    inline void FixBGR(const Image& src_image, Image& dst_image) {
      imProcessFixBGR(src_image.GetHandle(), dst_image.GetHandle()); }
    inline void SelectHue(const Image& src_image, Image& dst_image, double hue_start, double hue_end) {
      imProcessSelectHue(src_image.GetHandle(), dst_image.GetHandle(), hue_start, hue_end); }
    inline void SelectHSI(const Image& src_image, Image& dst_image, double hue_start, double hue_end, double sat_start, double sat_end, double int_start, double int_end) {
      imProcessSelectHSI(src_image.GetHandle(), dst_image.GetHandle(), hue_start, hue_end, sat_start, sat_end, int_start, int_end); }
    inline void ReplaceColor(const Image& src_image, Image& dst_image, double* src_color, double* dst_color) {
      imProcessReplaceColor(src_image.GetHandle(), dst_image.GetHandle(), src_color, dst_color); }
    inline void SetAlphaColor(const Image& src_image, Image& dst_image, double* src_color, double dst_alpha) {
      imProcessSetAlphaColor(src_image.GetHandle(), dst_image.GetHandle(), src_color, dst_alpha); }
    inline void BitwiseOp(const Image& src_image1, const Image& src_image2, Image& dst_image, int op) {
      imProcessBitwiseOp(src_image1.GetHandle(), src_image2.GetHandle(), dst_image.GetHandle(), op); }
    inline void BitwiseNot(const Image& src_image, Image& dst_image) {
      imProcessBitwiseNot(src_image.GetHandle(), dst_image.GetHandle()); }
    inline void BitMask(const Image& src_image, Image& dst_image, unsigned char mask, int op) {
      imProcessBitMask(src_image.GetHandle(), dst_image.GetHandle(), mask, op); }
    inline void BitPlane(const Image& src_image, Image& dst_image, int plane, int do_reset) {
      imProcessBitPlane(src_image.GetHandle(), dst_image.GetHandle(), plane, do_reset); }
    inline int RenderAddSpeckleNoise(const Image& src_image, Image& dst_image, double percent) {
      return imProcessRenderAddSpeckleNoise(src_image.GetHandle(), dst_image.GetHandle(), percent); }
    inline int RenderAddGaussianNoise(const Image& src_image, Image& dst_image, double mean, double stddev) {
      return imProcessRenderAddGaussianNoise(src_image.GetHandle(), dst_image.GetHandle(), mean, stddev); }
    inline int RenderAddUniformNoise(const Image& src_image, Image& dst_image, double mean, double stddev) {
      return imProcessRenderAddUniformNoise(src_image.GetHandle(), dst_image.GetHandle(), mean, stddev); }
    inline void ToneGamut(const Image& src_image, Image& dst_image, int op, double* params) {
      imProcessToneGamut(src_image.GetHandle(), dst_image.GetHandle(), op, params); }
    inline void UnNormalize(const Image& src_image, Image& dst_image) {
      imProcessUnNormalize(src_image.GetHandle(), dst_image.GetHandle()); }
    inline void DirectConv(const Image& src_image, Image& dst_image) {
      imProcessDirectConv(src_image.GetHandle(), dst_image.GetHandle()); }
    inline void Negative(const Image& src_image, Image& dst_image) {
      imProcessNegative(src_image.GetHandle(), dst_image.GetHandle()); }
    inline double CalcAutoGamma(const Image& image) {
      return imProcessCalcAutoGamma(image.GetHandle()); }
    inline void ShiftHSI(const Image& src_image, Image& dst_image, double h_shift, double s_shift, double i_shift) {
      imProcessShiftHSI(src_image.GetHandle(), dst_image.GetHandle(), h_shift, s_shift, i_shift); }
    inline void ShiftComponent(const Image& src_image, Image& dst_image, double h_shift, double s_shift, double i_shift) {
      imProcessShiftComponent(src_image.GetHandle(), dst_image.GetHandle(), h_shift, s_shift, i_shift); }
    inline void Threshold(const Image& src_image, Image& dst_image, double level, int value) {
      imProcessThreshold(src_image.GetHandle(), dst_image.GetHandle(), level, value); }
    inline void ThresholdByDiff(const Image& src_image1, const Image& src_image2, Image& dst_image) {
      imProcessThresholdByDiff(src_image1.GetHandle(), src_image2.GetHandle(), dst_image.GetHandle()); }
    inline void HysteresisThreshold(const Image& src_image, Image& dst_image, int low_thres, int high_thres) {
      imProcessHysteresisThreshold(src_image.GetHandle(), dst_image.GetHandle(), low_thres, high_thres); }
    inline void HysteresisThresEstimate(const Image& image, int &low_level, int &high_level) {
      imProcessHysteresisThresEstimate(image.GetHandle(), &low_level, &high_level); }
    inline int UniformErrThreshold(const Image& src_image, Image& dst_image) {
      return imProcessUniformErrThreshold(src_image.GetHandle(), dst_image.GetHandle()); }
    inline void DiffusionErrThreshold(const Image& src_image, Image& dst_image, int level) {
      imProcessDiffusionErrThreshold(src_image.GetHandle(), dst_image.GetHandle(), level); }
    inline int PercentThreshold(const Image& src_image, Image& dst_image, double percent) {
      return imProcessPercentThreshold(src_image.GetHandle(), dst_image.GetHandle(), percent); }
    inline int OtsuThreshold(const Image& src_image, Image& dst_image) {
      return imProcessOtsuThreshold(src_image.GetHandle(), dst_image.GetHandle()); }
    inline double MinMaxThreshold(const Image& src_image, Image& dst_image) {
      return imProcessMinMaxThreshold(src_image.GetHandle(), dst_image.GetHandle()); }
    inline void LocalMaxThresEstimate(const Image& image, int &level) {
      imProcessLocalMaxThresEstimate(image.GetHandle(), &level); }
    inline void SliceThreshold(const Image& src_image, Image& dst_image, double start_level, double end_level) {
      imProcessSliceThreshold(src_image.GetHandle(), dst_image.GetHandle(), start_level, end_level); }
    inline void ThresholdColor(const Image& src_image, Image& dst_image, double *src_color, double tol) {
      imProcessThresholdColor(src_image.GetHandle(), dst_image.GetHandle(), src_color, tol); }
    inline void Pixelate(const Image& src_image, Image& dst_image, int box_size) {
      imProcessPixelate(src_image.GetHandle(), dst_image.GetHandle(), box_size); }
    inline void Posterize(const Image& src_image, Image& dst_image, int level) {
      imProcessPosterize(src_image.GetHandle(), dst_image.GetHandle(), level); }
    inline void BinaryMask(const Image& src_image, Image& dst_image, Image& mask_image) {
      imProcessBinaryMask(src_image.GetHandle(), dst_image.GetHandle(), mask_image.GetHandle()); }
    inline void NormDiffRatio(const Image& image1, const Image& image2, Image& dst_image) {
      imProcessNormDiffRatio(image1.GetHandle(), image2.GetHandle(), dst_image.GetHandle()); }
    inline void AbnormalHyperionCorrection(const Image& src_image, Image& dst_image, int threshold_consecutive, int threshold_percent, Image& image_abnormal) {
      imProcessAbnormalHyperionCorrection(src_image.GetHandle(), dst_image.GetHandle(), threshold_consecutive, threshold_percent, image_abnormal.GetHandle()); }
    inline int ConvertDataType(const Image& src_image, Image& dst_image, int cpx2real, double gamma, int absolute, int cast_mode) {
      return imProcessConvertDataType(src_image.GetHandle(), dst_image.GetHandle(), cpx2real, gamma, absolute, cast_mode); }
    inline int ConvertColorSpace(const Image& src_image, Image& dst_image) {
      return imProcessConvertColorSpace(src_image.GetHandle(), dst_image.GetHandle()); }
    inline int ConvertToBitmap(const Image& src_image, Image& dst_image, int cpx2real, double gamma, int absolute, int cast_mode) {
      return imProcessConvertToBitmap(src_image.GetHandle(), dst_image.GetHandle(), cpx2real, gamma, absolute, cast_mode); }
    inline int Reduce(const Image& src_image, Image& dst_image, int order) {
      return imProcessReduce(src_image.GetHandle(), dst_image.GetHandle(), order); }
    inline int Resize(const Image& src_image, Image& dst_image, int order) {
      return imProcessResize(src_image.GetHandle(), dst_image.GetHandle(), order); }
    inline int ReduceBy4(const Image& src_image, Image& dst_image) {
      return imProcessReduceBy4(src_image.GetHandle(), dst_image.GetHandle()); }
    inline int Crop(const Image& src_image, Image& dst_image, int xmin, int ymin) {
      return imProcessCrop(src_image.GetHandle(), dst_image.GetHandle(), xmin, ymin); }
    inline int Insert(const Image& src_image, const Image& region_image, Image& dst_image, int xmin, int ymin) {
      return imProcessInsert(src_image.GetHandle(), region_image.GetHandle(), dst_image.GetHandle(), xmin, ymin); }
    inline int AddMargins(const Image& src_image, Image& dst_image, int xmin, int ymin) {
      return imProcessAddMargins(src_image.GetHandle(), dst_image.GetHandle(), xmin, ymin); }
    inline int Rotate(const Image& src_image, Image& dst_image, double cos0, double sin0, int order) {
      return imProcessRotate(src_image.GetHandle(), dst_image.GetHandle(), cos0, sin0, order); }
    inline int RotateRef(const Image& src_image, Image& dst_image, double cos0, double sin0, int x, int y, int to_origin, int order) {
      return imProcessRotateRef(src_image.GetHandle(), dst_image.GetHandle(), cos0, sin0, x, y, to_origin, order); }
    inline int Rotate90(const Image& src_image, Image& dst_image, int dir_clockwise) {
      return imProcessRotate90(src_image.GetHandle(), dst_image.GetHandle(), dir_clockwise); }
    inline int Rotate180(const Image& src_image, Image& dst_image) {
      return imProcessRotate180(src_image.GetHandle(), dst_image.GetHandle()); }
    inline int Mirror(const Image& src_image, Image& dst_image) {
      return imProcessMirror(src_image.GetHandle(), dst_image.GetHandle()); }
    inline int Flip(const Image& src_image, Image& dst_image) {
      return imProcessFlip(src_image.GetHandle(), dst_image.GetHandle()); }
    inline int Radial(const Image& src_image, Image& dst_image, double k1, int order) {
      return imProcessRadial(src_image.GetHandle(), dst_image.GetHandle(), k1, order); }
    inline int LensDistort(const Image& src_image, Image& dst_image, double a, double b, double c, int order) {
      return imProcessLensDistort(src_image.GetHandle(), dst_image.GetHandle(), a, b, c, order); }
    inline int Swirl(const Image& src_image, Image& dst_image, double k1, int order) {
      return imProcessSwirl(src_image.GetHandle(), dst_image.GetHandle(), k1, order); }
    inline int InterlaceSplit(const Image& src_image, Image& dst_image1, Image& dst_image2) {
      return imProcessInterlaceSplit(src_image.GetHandle(), dst_image1.GetHandle(), dst_image2.GetHandle()); }
    inline int GrayMorphConvolve(const Image& src_image, Image& dst_image, const Image& kernel, int ismax) {
      return imProcessGrayMorphConvolve(src_image.GetHandle(), dst_image.GetHandle(), kernel.GetHandle(), ismax); }
    inline int GrayMorphErode(const Image& src_image, Image& dst_image, int kernel_size) {
      return imProcessGrayMorphErode(src_image.GetHandle(), dst_image.GetHandle(), kernel_size); }
    inline int GrayMorphDilate(const Image& src_image, Image& dst_image, int kernel_size) {
      return imProcessGrayMorphDilate(src_image.GetHandle(), dst_image.GetHandle(), kernel_size); }
    inline int GrayMorphOpen(const Image& src_image, Image& dst_image, int kernel_size) {
      return imProcessGrayMorphOpen(src_image.GetHandle(), dst_image.GetHandle(), kernel_size); }
    inline int GrayMorphClose(const Image& src_image, Image& dst_image, int kernel_size) {
      return imProcessGrayMorphClose(src_image.GetHandle(), dst_image.GetHandle(), kernel_size); }
    inline int GrayMorphTopHat(const Image& src_image, Image& dst_image, int kernel_size) {
      return imProcessGrayMorphTopHat(src_image.GetHandle(), dst_image.GetHandle(), kernel_size); }
    inline int GrayMorphWell(const Image& src_image, Image& dst_image, int kernel_size) {
      return imProcessGrayMorphWell(src_image.GetHandle(), dst_image.GetHandle(), kernel_size); }
    inline int GrayMorphGradient(const Image& src_image, Image& dst_image, int kernel_size) {
      return imProcessGrayMorphGradient(src_image.GetHandle(), dst_image.GetHandle(), kernel_size); }
    inline int BinMorphConvolve(const Image& src_image, Image& dst_image, const Image& kernel, int hit_white, int iter) {
      return imProcessBinMorphConvolve(src_image.GetHandle(), dst_image.GetHandle(), kernel.GetHandle(), hit_white, iter); }
    inline int BinMorphErode(const Image& src_image, Image& dst_image, int kernel_size, int iter) {
      return imProcessBinMorphErode(src_image.GetHandle(), dst_image.GetHandle(), kernel_size, iter); }
    inline int BinMorphDilate(const Image& src_image, Image& dst_image, int kernel_size, int iter) {
      return imProcessBinMorphDilate(src_image.GetHandle(), dst_image.GetHandle(), kernel_size, iter); }
    inline int BinMorphOpen(const Image& src_image, Image& dst_image, int kernel_size, int iter) {
      return imProcessBinMorphOpen(src_image.GetHandle(), dst_image.GetHandle(), kernel_size, iter); }
    inline int BinMorphClose(const Image& src_image, Image& dst_image, int kernel_size, int iter) {
      return imProcessBinMorphClose(src_image.GetHandle(), dst_image.GetHandle(), kernel_size, iter); }
    inline int BinMorphOutline(const Image& src_image, Image& dst_image, int kernel_size, int iter) {
      return imProcessBinMorphOutline(src_image.GetHandle(), dst_image.GetHandle(), kernel_size, iter); }
    inline int BinMorphThin(const Image& src_image, Image& dst_image) {
      return imProcessBinMorphThin(src_image.GetHandle(), dst_image.GetHandle()); }
    inline int MedianConvolve(const Image& src_image, Image& dst_image, int kernel_size) {
      return imProcessMedianConvolve(src_image.GetHandle(), dst_image.GetHandle(), kernel_size); }
    inline int RangeConvolve(const Image& src_image, Image& dst_image, int kernel_size) {
      return imProcessRangeConvolve(src_image.GetHandle(), dst_image.GetHandle(), kernel_size); }
    inline int RankClosestConvolve(const Image& src_image, Image& dst_image, int kernel_size) {
      return imProcessRankClosestConvolve(src_image.GetHandle(), dst_image.GetHandle(), kernel_size); }
    inline int RankMaxConvolve(const Image& src_image, Image& dst_image, int kernel_size) {
      return imProcessRankMaxConvolve(src_image.GetHandle(), dst_image.GetHandle(), kernel_size); }
    inline int RankMinConvolve(const Image& src_image, Image& dst_image, int kernel_size) {
      return imProcessRankMinConvolve(src_image.GetHandle(), dst_image.GetHandle(), kernel_size); }
    inline int RangeContrastThreshold(const Image& src_image, Image& dst_image, int kernel_size, int min_range) {
      return imProcessRangeContrastThreshold(src_image.GetHandle(), dst_image.GetHandle(), kernel_size, min_range); }
    inline int LocalMaxThreshold(const Image& src_image, Image& dst_image, int kernel_size, int min_level) {
      return imProcessLocalMaxThreshold(src_image.GetHandle(), dst_image.GetHandle(), kernel_size, min_level); }
    inline int Convolve(const Image& src_image, Image& dst_image, const Image& kernel) {
      return imProcessConvolve(src_image.GetHandle(), dst_image.GetHandle(), kernel.GetHandle()); }
    inline int ConvolveSep(const Image& src_image, Image& dst_image, const Image& kernel) {
      return imProcessConvolveSep(src_image.GetHandle(), dst_image.GetHandle(), kernel.GetHandle()); }
    inline int ConvolveDual(const Image& src_image, Image& dst_image, const Image& kernel1, const Image& kernel2) {
      return imProcessConvolveDual(src_image.GetHandle(), dst_image.GetHandle(), kernel1.GetHandle(), kernel2.GetHandle()); }
    inline int ConvolveRep(const Image& src_image, Image& dst_image, const Image& kernel, int rep_count) {
      return imProcessConvolveRep(src_image.GetHandle(), dst_image.GetHandle(), kernel.GetHandle(), rep_count); }
    inline int CompassConvolve(const Image& src_image, Image& dst_image, Image& kernel) {
      return imProcessCompassConvolve(src_image.GetHandle(), dst_image.GetHandle(), kernel.GetHandle()); }
    inline int DiffOfGaussianConvolve(const Image& src_image, Image& dst_image, double stddev1, double stddev2) {
      return imProcessDiffOfGaussianConvolve(src_image.GetHandle(), dst_image.GetHandle(), stddev1, stddev2); }
    inline int LapOfGaussianConvolve(const Image& src_image, Image& dst_image, double stddev) {
      return imProcessLapOfGaussianConvolve(src_image.GetHandle(), dst_image.GetHandle(), stddev); }
    inline int MeanConvolve(const Image& src_image, Image& dst_image, int kernel_size) {
      return imProcessMeanConvolve(src_image.GetHandle(), dst_image.GetHandle(), kernel_size); }
    inline int GaussianConvolve(const Image& src_image, Image& dst_image, double stddev) {
      return imProcessGaussianConvolve(src_image.GetHandle(), dst_image.GetHandle(), stddev); }
    inline int BarlettConvolve(const Image& src_image, Image& dst_image, int kernel_size) {
      return imProcessBarlettConvolve(src_image.GetHandle(), dst_image.GetHandle(), kernel_size); }
    inline int SobelConvolve(const Image& src_image, Image& dst_image) {
      return imProcessSobelConvolve(src_image.GetHandle(), dst_image.GetHandle()); }
    inline int PrewittConvolve(const Image& src_image, Image& dst_image) {
      return imProcessPrewittConvolve(src_image.GetHandle(), dst_image.GetHandle()); }
    inline int SplineEdgeConvolve(const Image& src_image, Image& dst_image) {
      return imProcessSplineEdgeConvolve(src_image.GetHandle(), dst_image.GetHandle()); }
    inline int ZeroCrossing(const Image& src_image, Image& dst_image) {
      return imProcessZeroCrossing(src_image.GetHandle(), dst_image.GetHandle()); }
    inline int Canny(const Image& src_image, Image& dst_image, double stddev) {
      return imProcessCanny(src_image.GetHandle(), dst_image.GetHandle(), stddev); }
    inline int Unsharp(const Image& src_image, Image& dst_image, double stddev, double amount, double threshold) {
      return imProcessUnsharp(src_image.GetHandle(), dst_image.GetHandle(), stddev, amount, threshold); }
    inline int Sharp(const Image& src_image, Image& dst_image, double amount, double threshold) {
      return imProcessSharp(src_image.GetHandle(), dst_image.GetHandle(), amount, threshold); }
    inline int SharpKernel(const Image& src_image, const Image& kernel, Image& dst_image, double amount, double threshold) {
      return imProcessSharpKernel(src_image.GetHandle(), kernel.GetHandle(), dst_image.GetHandle(), amount, threshold); }
    inline int PerimeterLine(const Image& src_image, Image& dst_image) {
      return imProcessPerimeterLine(src_image.GetHandle(), dst_image.GetHandle()); }
    inline int RemoveByArea(const Image& src_image, Image& dst_image, int connect, int start_size, int end_size, int inside) {
      return imProcessRemoveByArea(src_image.GetHandle(), dst_image.GetHandle(), connect, start_size, end_size, inside); }
    inline int FillHoles(const Image& src_image, Image& dst_image, int connect) {
      return imProcessFillHoles(src_image.GetHandle(), dst_image.GetHandle(), connect); }
    inline void RotateKernel(Image& kernel) {
      imProcessRotateKernel(kernel.GetHandle()); }
    inline void FFTraw(Image& image, int inverse, int center, int normalize) {
      imProcessFFTraw(image.GetHandle(), inverse, center, normalize); }
    inline void SwapQuadrants(Image& image, int center2origin) {
      imProcessSwapQuadrants(image.GetHandle(), center2origin); }

    inline int RenderOp(Image& image, imRenderFunc render_func, const char* render_name, double* params, int plus) {
      return imProcessRenderOp(image.GetHandle(), render_func, render_name, params, plus); }
    inline int RenderCondOp(Image& image, imRenderCondFunc render_cond_func, const char* render_name, double* params) {
      return imProcessRenderCondOp(image.GetHandle(), render_cond_func, render_name, params); }
    inline int RenderRandomNoise(Image& image) {
      return imProcessRenderRandomNoise(image.GetHandle()); }
    inline int RenderConstant(Image& image, double* value) {
      return imProcessRenderConstant(image.GetHandle(), value); }
    inline int RenderWheel(Image& image, int internal_radius, int external_radius) {
      return imProcessRenderWheel(image.GetHandle(), internal_radius, external_radius); }
    inline int RenderCone(Image& image, int radius) {
      return imProcessRenderCone(image.GetHandle(), radius); }
    inline int RenderTent(Image& image, int tent_width, int tent_height) {
      return imProcessRenderTent(image.GetHandle(), tent_width, tent_height); }
    inline int RenderRamp(Image& image, int start, int end, int vert_dir) {
      return imProcessRenderRamp(image.GetHandle(), start, end, vert_dir); }
    inline int RenderBox(Image& image, int box_width, int box_height) {
      return imProcessRenderBox(image.GetHandle(), box_width, box_height); }
    inline int RenderSinc(Image& image, double x_period, double y_period) {
      return imProcessRenderSinc(image.GetHandle(), x_period, y_period); }
    inline int RenderGaussian(Image& image, double stddev) {
      return imProcessRenderGaussian(image.GetHandle(), stddev); }
    inline int RenderLapOfGaussian(Image& image, double stddev) {
      return imProcessRenderLapOfGaussian(image.GetHandle(), stddev); }
    inline int RenderCosine(Image& image, double x_period, double y_period) {
      return imProcessRenderCosine(image.GetHandle(), x_period, y_period); }
    inline int RenderGrid(Image& image, int x_space, int y_space) {
      return imProcessRenderGrid(image.GetHandle(), x_space, y_space); }
    inline int RenderChessboard(Image& image, int x_space, int y_space) {
      return imProcessRenderChessboard(image.GetHandle(), x_space, y_space); }
    inline void RenderFloodFill(Image& image, int start_x, int start_y, double* replace_color, double tolerance) {
      imProcessRenderFloodFill(image.GetHandle(), start_x, start_y, replace_color, tolerance); }
  }

  class Histogram
  {
    /* forbidden */
    Histogram() { }

  protected:
    unsigned long* histo;
    int count;

  public:

    Histogram(int image_data_type) {
      count = imHistogramCount(image_data_type);
      histo = new unsigned long[count]; 
    }
    virtual ~Histogram() {
      if (histo)
        delete[] histo; 
    }

    unsigned long* GetData() const { return histo; }
    int Count() const { return count; }

    Histogram(const Histogram& histogram) {
      count = histogram.count;
      histo = new unsigned long[count];
      for (int i = 0; i < count; i++) 
        histo[i] = histogram.histo[i]; 
    }

    unsigned long& operator [](int index) 
    { 
      static unsigned long err = (unsigned long)-1;
      if (!histo || index < 0 || index >= count)
        return err;
      return histo[index]; 
    }
  };


  namespace Calc
  {
    inline int RMSError(const Image& image1, const Image& image2, double& rmserror) {
      return imCalcRMSError(image1.GetHandle(), image2.GetHandle(), &rmserror); }
    inline int SNR(const Image& src_image, const Image& noise_image, double& snr) {
      return imCalcSNR(src_image.GetHandle(), noise_image.GetHandle(), &snr); }
    inline int CountColors(const Image& image, unsigned long &count) {
      return imCalcCountColors(image.GetHandle(), &count); }
    inline int GrayHistogram(const Image& image, im::Histogram& histogram, int cumulative) {
      return imCalcGrayHistogram(image.GetHandle(), histogram.GetData(), cumulative); }
    inline int Histogram(const Image& image, im::Histogram& histogram, int plane, int cumulative) {
      return imCalcHistogram(image.GetHandle(), histogram.GetData(), plane, cumulative); }
    inline int ImageStatistics(const Image& image, imStats& stats) {
      return imCalcImageStatistics(image.GetHandle(), &stats); }
    inline int HistogramStatistics(const Image& image, imStats& stats) {
      return imCalcHistogramStatistics(image.GetHandle(), &stats); }
    inline int HistoImageStatistics(const Image& image, int* median, int* mode) {
      return imCalcHistoImageStatistics(image.GetHandle(), median, mode); }
    inline int PercentMinMax(const Image& image, double percent, int ignore_zero, int &min, int &max) {
      return imCalcPercentMinMax(image.GetHandle(), percent, ignore_zero, &min, &max); }
  }

  class MeasureTable : protected AttribTable
  {
    int region_count;

  public:
    MeasureTable(int _region_count)
      :AttribTable(0), region_count(_region_count) {
    }
    virtual ~MeasureTable() {}

    int RegionCount() const { return region_count; }

    const void* AddMeasure(const char* name, int data_type) {
      const void* data = Get(name);
      if (!data)
      {
        Set(name, data_type, region_count, (const void*)0);
        data = Get(name);
      }
      return data; 
    }
    const void* GetMeasure(const char* name, int *data_type = (int*)0) const {
      return Get(name, data_type); }

    int* AddMeasureInt(const char* name) {
      return (int*)AddMeasure(name, IM_INT); }
    double* AddMeasureDouble(const char* name) {
      return (double*)AddMeasure(name, IM_DOUBLE);
    }
    int* GetMeasureInt(const char* name) const {
      int data_type;
      const void* data = Get(name, &data_type);
      if (!data || data_type != IM_INT)
        return (int*)0;
      else
        return (int*)data; 
    }
    double* GetMeasureDouble(const char* name) const {
      int data_type;
      const void* data = Get(name, &data_type);
      if (!data || data_type != IM_DOUBLE)
        return (double*)0;
      else
        return (double*)data; 
    }
  };

  namespace Analyze
  {
    inline int FindRegions(const Image& image, Image& region_image, int connect, int touch_border, int &region_count) {
      return imAnalyzeFindRegions(image.GetHandle(), region_image.GetHandle(), connect, touch_border, &region_count); }

    inline int MeasureArea(const Image& region_image, MeasureTable& measure_table) {
      return imAnalyzeMeasureArea(region_image.GetHandle(), measure_table.AddMeasureInt("Area"), measure_table.RegionCount()); }
    inline int MeasurePerimArea(const Image& region_image, MeasureTable& measure_table) {
      return imAnalyzeMeasurePerimArea(region_image.GetHandle(), measure_table.AddMeasureDouble("PerimeterArea"), measure_table.RegionCount()); }
    inline int MeasureCentroid(const Image& region_image, MeasureTable& measure_table) {
      return imAnalyzeMeasureCentroid(region_image.GetHandle(), measure_table.GetMeasureInt("Area"), measure_table.RegionCount(),
                                                      measure_table.AddMeasureDouble("CentroidX"), measure_table.AddMeasureDouble("CentroidY")); }
    inline int MeasurePrincipalAxis(const Image& region_image, MeasureTable& measure_table) {
      return imAnalyzeMeasurePrincipalAxis(region_image.GetHandle(), measure_table.GetMeasureInt("Area"),
                                                           measure_table.GetMeasureDouble("CentroidX"), measure_table.GetMeasureDouble("CentroidY"), 
                                                           measure_table.RegionCount(), 
                                                           measure_table.AddMeasureDouble("MajorSlope"), measure_table.AddMeasureDouble("MajorLength"), 
                                                           measure_table.AddMeasureDouble("MinorSlope"), measure_table.AddMeasureDouble("MinorLength")); }
    inline int MeasureHoles(const Image& region_image, int connect, MeasureTable& measure_table) {
      return imAnalyzeMeasureHoles(region_image.GetHandle(), connect, measure_table.RegionCount(),
                                                            measure_table.AddMeasureInt("HolesCount"),
                                                            measure_table.AddMeasureInt("HolesArea"), 
                                                            measure_table.AddMeasureDouble("HolesPerimeter")); }
    inline int MeasurePerimeter(const Image& region_image, MeasureTable& measure_table) {
      return imAnalyzeMeasurePerimeter(region_image.GetHandle(), measure_table.AddMeasureDouble("Perimeter"), measure_table.RegionCount()); }

  }

}

#endif
