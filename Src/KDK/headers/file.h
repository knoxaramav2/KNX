#ifndef KDK_FILE
#define KDK_FILE

#include <stdio.h>
#include <string.h>

#ifdef __WINDOWS
//#include <windows.h>
//#define fchar wchar_t
#define fchar char
#else
#define fchar char
#endif

#include "config.h"

typedef enum {
    AUTO_ENCODING,
    US_ASCII,
    UTF_8,
    UTF_16,
    UTF_32,
} fileEncoding;

typedef struct _page{
    fchar * memory;
    fchar * index;

    size_t size;//bytes
} _page;

typedef struct fileBuffer {

    _page   *   _buffer;
    _page   *   _select;
    size_t      _numPages;
    FILE    *   _handle;

    fileEncoding encoding;

} fileBuffer;

char * localizePath(char *);

int initFileBuffer(fileBuffer*, Config *);
int clearFileBuffer(fileBuffer*);

int openFile(fileBuffer *, char *, fileEncoding);
int closeFile(fileBuffer *, char *);

fchar * fReadLine(fileBuffer*);
fchar fReadChar(fileBuffer*);

#endif