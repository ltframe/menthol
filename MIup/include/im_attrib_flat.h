/** \file
 * \brief Attributes Table Flat API.
 * This will simplify the DLL export, and can be used for C aplications.
 *
 * See Copyright Notice in im_lib.h
 */

#ifndef __IM_ATTRIB_FLAT_H_
#define __IM_ATTRIB_FLAT_H_

#if	defined(__cplusplus)
extern "C" {
#endif

struct imAttribTablePrivate;

/** Definition of the callback used in ForEach function. */
typedef int (*imAttribTableCallback)(void* user_data, int index, const char* name, int data_type, int count, const void* data);

imAttribTablePrivate* imAttribTableCreate(int hash_size);
void imAttribTableDestroy(imAttribTablePrivate* ptable);
int imAttribTableCount(imAttribTablePrivate* ptable);
void imAttribTableRemoveAll(imAttribTablePrivate* ptable);
const void* imAttribTableGet(const imAttribTablePrivate* ptable, const char *name, int *data_type, int *count);
int imAttribTableGetInteger(imAttribTablePrivate* ptable, const char *name, int index);
double imAttribTableGetReal(imAttribTablePrivate* ptable, const char *name, int index);
const char* imAttribTableGetString(imAttribTablePrivate* ptable, const char *name);
void imAttribTableSet(imAttribTablePrivate* ptable, const char* name, int data_type, int count, const void* data);
void imAttribTableSetInteger(imAttribTablePrivate* ptable, const char* name, int data_type, int value);
void imAttribTableSetReal(imAttribTablePrivate* ptable, const char* name, int data_type, double value);
void imAttribTableSetString(imAttribTablePrivate* ptable, const char* name, const char* value);
void imAttribTableUnSet(imAttribTablePrivate* ptable, const char *name);
void imAttribTableCopyFrom(imAttribTablePrivate* ptable_dst, const imAttribTablePrivate* ptable_src);
void imAttribTableMergeFrom(imAttribTablePrivate* ptable_dst, const imAttribTablePrivate* ptable_src);
void imAttribTableForEach(const imAttribTablePrivate* ptable, void* user_data, imAttribTableCallback attrib_func);

imAttribTablePrivate* imAttribArrayCreate(int hash_size);
const void* imAttribArrayGet(const imAttribTablePrivate* ptable, int index, char *name, int *data_type, int *count);
void imAttribArraySet(imAttribTablePrivate* ptable, int index, const char* name, int data_type, int count, const void* data);
void imAttribArrayCopyFrom(imAttribTablePrivate* ptable_dst, const imAttribTablePrivate* ptable_src);

#if defined(__cplusplus)
}
#endif

#endif
