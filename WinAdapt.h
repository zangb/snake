#ifndef __WINADAPT
#define __WINADAPT

#ifdef _WIN32
#include "windows.h"
extern void Line(int xa, int ya, int xe, int ye);
extern void Text(int xa, int ya, const char txt[]);
extern void Rect(int xa, int ya, int xe, int ye);
extern void Elli(int xa, int ya, int xe, int ye);
extern void LineCol(int r, int g, int b);
extern void FillCol(int r, int g, int b);
extern void PutPixel(int xa, int ya, COLORREF crColora);
extern void FillPoly(int *lpPoint, int nPoints);
#endif

#ifdef __unix__
#include <gdk/gdk.h>
#ifndef RGB
#define  RGB(R,G,B) {(guint32)((R)<<16)|((G)<<8)|(B),(guint16)(((R)*65535)/255),(guint16)(((G)*65535)/255),(guint16)(((B)*65535)/255)}
extern void Line(int xa, int ya, int xe, int ye);
extern void Text(int xa, int ya, const char txt[]);
extern void Rect(int xa, int ya, int xe, int ye);
extern void Elli(int xa, int ya, int xe, int ye);
extern void LineCol(int r, int g, int b);
extern void FillCol(int r, int g, int b);
extern void PutPixel(int xa, int ya, GdkColor crColora);
extern void FillPoly(int *lpPoint, int nPoints);
#endif

#endif

/*    Stand 2.1.2008 */


#endif
