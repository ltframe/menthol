/** \file
 * \brief Palette Generators
 *
 * See Copyright Notice in im_lib.h
 */

#ifndef __IM_PALETTE_H
#define __IM_PALETTE_H

#if	defined(__cplusplus)
extern "C" {
#endif


/** \defgroup palette Palette Generators
 * \par
 * Creates several standard palettes. The palette is just an array of encoded color values.
 * See also \ref colorutl.
 * \par
 * In Lua, to create a palette you can call im.PaletteCreate.
 * \verbatim im.PaletteCreate([count: number]) -> pal: imPalette [in Lua 5] \endverbatim
 * Default count is 256.
 * IMLua and CDLua palettes are 100% compatible. The IM palette metatable name is "imPalette". \n
 * When converted to a string will return "imPalete(%p)" where %p is replaced by the userdata address.
 * If the palette is already destroyed by im.PaletteDestroy, then it will return also the suffix "-destroyed".
 * \par
 * In Lua, to destroy a palette you can call im.PaletteDestroy.
 * If this function is not called, the palette is destroyed by the garbage collector.
 * \verbatim im.PaletteDestroy(pal: imPalette) [in Lua 5] \endverbatim
 * \par
 * In Lua, array access is enabled so you can do:.
 * \verbatim color = pal[index] \endverbatim
 * \verbatim pal[index] = color \endverbatim
 * \verbatim count = #pal \endverbatim
 * \par
 * See \ref im_palette.h
 * \ingroup util */


/** Allocates memory for the palette data.
 * This ensures allocation and release in the same module by the correct functions.
 * \ingroup palette */
long* imPaletteNew(int count);

/** Releases memory for the palette data.
 * This ensures allocation and release in the same module by the correct functions.
 * \ingroup palette */
void imPaletteRelease(long* palette);

/** Duplicate a palette data using imPaletteNew.
 * \ingroup palette */
long* imPaletteDuplicate(const long* palette, int count);


/** Searches for the nearest color on the table and returns the color index if successful. 
 * It looks in all palette entries and finds the minimum euclidian square distance. 
 * If the color matches the given color it returns immediately.
 * See also \ref colorutl.
 *
 * \verbatim im.PaletteFindNearest(pal: imPalette, color: lightuserdata) -> index: number [in Lua 5] \endverbatim
 * \ingroup palette */
int imPaletteFindNearest(const long *palette, int palette_count, long color);

/** Searches for the color on the table and returns the color index if successful. 
 * If the tolerance is 0 search for the exact match in the palette else search for the 
 * first color that fits in the tolerance range.
 * See also \ref colorutl.
 *
 * \verbatim im.PaletteFindColor(pal: imPalette, color: lightuserdata, tol: number) -> index: number [in Lua 5] \endverbatim
 * \ingroup palette */
int imPaletteFindColor(const long *palette, int palette_count, long color, unsigned char tol);

/** Creates a palette of gray scale values.
 * The colors are arranged from black to white.
 *
 * \verbatim im.PaletteGray() -> pal: imPalette [in Lua 5] \endverbatim
 * \ingroup palette */
long* imPaletteGray(void);

/** Creates a palette of a gradient of red colors.
 * The colors are arranged from black to pure red.
 *
 * \verbatim im.PaletteRed() -> pal: imPalette [in Lua 5] \endverbatim
 * \ingroup palette */
long* imPaletteRed(void);

/** Creates a palette of a gradient of green colors.
 * The colors are arranged from black to pure green.
 *
 * \verbatim im.PaletteGreen() -> pal: imPalette [in Lua 5] \endverbatim
 * \ingroup palette */
long* imPaletteGreen(void);

/** Creates a palette of a gradient of blue colors.
 * The colors are arranged from black to pure blue.
 *
 * \verbatim im.PaletteBlue() -> pal: imPalette [in Lua 5] \endverbatim
 * \ingroup palette */
long* imPaletteBlue(void);

/** Creates a palette of a gradient of yellow colors.
 * The colors are arranged from black to pure yellow.
 *
 * \verbatim im.PaletteYellow() -> pal: imPalette [in Lua 5] \endverbatim
 * \ingroup palette */
long* imPaletteYellow(void);

/** Creates a palette of a gradient of magenta colors.
 * The colors are arranged from black to pure magenta.
 *
 * \verbatim im.PaletteMagenta() -> pal: imPalette [in Lua 5] \endverbatim
 * \ingroup palette */
long* imPaletteMagenta(void);

/** Creates a palette of a gradient of cyan colors.
 * The colors are arranged from black to pure cyan.
 *
 * \verbatim im.PaletteCyan() -> pal: imPalette [in Lua 5] \endverbatim
 * \ingroup palette */
long* imPaletteCyan(void);

/** Creates a palette of rainbow colors.
 * The colors are arranged in the light wave length spectrum order (starting from purple).
 *
 * \verbatim im.PaletteRainbow() -> pal: imPalette [in Lua 5] \endverbatim
 * \ingroup palette */
long* imPaletteRainbow(void);

/** Creates a palette of hues with maximum saturation.
 *
 * \verbatim im.PaletteHues() -> pal: imPalette [in Lua 5] \endverbatim
 * \ingroup palette */
long* imPaletteHues(void);

/** Creates a palette of a gradient of blue colors.
 * The colors are arranged from pure blue to white.
 *
 * \verbatim im.PaletteBlueIce() -> pal: imPalette [in Lua 5] \endverbatim
 * \ingroup palette */
long* imPaletteBlueIce(void);

/** Creates a palette of a gradient from black to white passing trough red and orange.
 *
 * \verbatim im.PaletteHotIron() -> pal: imPalette [in Lua 5] \endverbatim
 * \ingroup palette */
long* imPaletteHotIron(void);

/** Creates a palette of a gradient from black to white passing trough red and yellow.
 *
 * \verbatim im.PaletteBlackBody() -> pal: imPalette [in Lua 5] \endverbatim
 * \ingroup palette */
long* imPaletteBlackBody(void);

/** Creates a palette with high contrast colors.
 *
 * \verbatim im.PaletteHighContrast() -> pal: imPalette [in Lua 5] \endverbatim
 * \ingroup palette */
long* imPaletteHighContrast(void);

/** Creates a palette of a sequence of colors from black to white 
 *  with 32 linear intensity values combined with 8 hue variations.
 *
 * \verbatim im.PaletteLinear() -> pal: imPalette [in Lua 5] \endverbatim
 * \ingroup palette */
long* imPaletteLinear(void);

/** Creates a palette of an uniform sub-division of colors from black to white.
*  This is a 2^(2.6) bits per pixel palette.
*
* \verbatim im.PaletteUniform() -> pal: imPalette [in Lua 5] \endverbatim
* \ingroup palette */
long* imPaletteUniform(void);

/** Returns the index of the correspondent RGB color of an uniform palette.
 *
 * \verbatim im.PaletteUniformIndex(color: lightuserdata) -> index: number [in Lua 5] \endverbatim
 * \ingroup palette */
int imPaletteUniformIndex(long color);

/** Returns the index of the correspondent RGB color of an uniform palette.
 * Uses an 8x8 ordered dither to lookup the index in a halftone matrix.
 * The spatial position used by the halftone method.
 *
 * \verbatim im.PaletteUniformIndexHalftoned(color: lightuserdata, x: number, y: number) -> index: number [in Lua 5] \endverbatim
 * \ingroup palette */
int imPaletteUniformIndexHalftoned(long color, int x, int y);


#if defined(__cplusplus)
}
#endif

#endif

