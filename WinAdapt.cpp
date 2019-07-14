/*
   Windows- Adapter- Programm
   PIN3 SS99
   Kn/Bö
   Double buffering Farm 2011.05.03
   DIESE DATEI SOLL NICHT GEAENDERT WERDEN
   Stand 03.05.2011
*/

#ifdef _WIN32

#include <windows.h>
#include <cstring>
#include "WinAdapt.h"

using namespace std;

#define SIMPROTIMER 4711
#define UPDINTERVALL 200  //msec. zwischen updates

HDC Memhdc;

extern void VtlPaint(int, int, int, int);
extern void VtlZyk(void);
extern void VtlMouse(int X, int Y);
extern void VtlKeyHit(int key);
extern void VtlInit(void);

LRESULT CALLBACK WndProc  (IN HWND hwnd, IN UINT message,
                           IN WPARAM wParam, LPARAM lParam);
void Loop();

HPEN hpNewPen=0;
HBRUSH hbNewBrush=0;

int CALLBACK WinMain(
    IN HINSTANCE hInstance,
    IN HINSTANCE hPrevInstance,
    IN LPSTR lpCmdLine,
    IN int nShowCmd
)
{
    static char szAppName[] = "WinAdapt" ;
    HWND        hwnd ;
    MSG         msg ;
    WNDCLASS    wndclass ;
    if (!hPrevInstance)
    {
        wndclass.style         = CS_HREDRAW | CS_VREDRAW ;
        wndclass.lpfnWndProc   = WndProc ;
        wndclass.cbClsExtra    = 0 ;
        wndclass.cbWndExtra    = 0 ;
        wndclass.hInstance     = (HINSTANCE)hInstance ;
        wndclass.hIcon         = LoadIcon(NULL,IDI_APPLICATION);
        wndclass.hCursor       = LoadCursor(NULL,IDC_ARROW);
        wndclass.hbrBackground = NULL;
        wndclass.lpszMenuName  = NULL ;
        wndclass.lpszClassName = szAppName ;
        RegisterClass (&wndclass) ;
    }
    hwnd = CreateWindow (szAppName,        //Fenst.klassenname
                         "WinAdapt", //Titelleiste
                         WS_OVERLAPPEDWINDOW, //Fensterstil
                         CW_USEDEFAULT,       //Fensterpos, x
                         CW_USEDEFAULT,       //Fensterpos, y
                         CW_USEDEFAULT,       //horizontale Groesse
                         CW_USEDEFAULT,       //vertikale   Groesse
                         NULL,                //Parent Window
                         NULL,                //Handle Menue
                         (HINSTANCE)hInstance,           //Handle Instanz
                         NULL) ;              //Spezialparameter
    ShowWindow (hwnd, nShowCmd) ;
    UpdateWindow (hwnd) ;
    while (GetMessage (&msg, NULL, 0, 0))
    {
        TranslateMessage (&msg) ;
        DispatchMessage (&msg) ;
    }
    return (int)msg.wParam ;
}

LRESULT CALLBACK WndProc  (IN HWND hwnd, IN UINT message,
                           IN WPARAM wParam, LPARAM lParam)
{
    PAINTSTRUCT ps;
    RECT rect;
    HBITMAP Membitmap;
    HDC Ghdc;
    int win_width, win_height;
    switch (message)
    {
    case WM_CREATE :
        VtlInit();
        SetTimer(hwnd, SIMPROTIMER, UPDINTERVALL, NULL);
        return 0;
    case WM_TIMER :
        if (wParam == SIMPROTIMER)
        {
            VtlZyk();
            InvalidateRect(hwnd, NULL, TRUE);
        }
        return 0;
    case WM_PAINT :
        GetClientRect(hwnd,&rect);
        win_width = rect.right - rect.left;
        win_height = rect.bottom + rect.left;
        Ghdc = BeginPaint(hwnd, &ps);
        Memhdc = CreateCompatibleDC(Ghdc);
        Membitmap = CreateCompatibleBitmap(Ghdc, win_width, win_height);
        SelectObject(Memhdc, Membitmap);

        FillRect(Memhdc, &rect, (HBRUSH) GetStockObject(WHITE_BRUSH));
        //drawing code goes in here
        VtlPaint(rect.left, rect.top, rect.right, rect.bottom);

        BitBlt(Ghdc, 0, 0, win_width, win_height, Memhdc, 0, 0, SRCCOPY);
        DeleteObject(Membitmap);
        DeleteDC    (Memhdc);
        DeleteDC    (Ghdc);
        EndPaint(hwnd, &ps);
        return 0 ;
    case WM_LBUTTONUP :
        VtlMouse(LOWORD(lParam), HIWORD(lParam));
        InvalidateRect(hwnd, NULL, TRUE);
        return 0;
    case WM_CHAR :
        VtlKeyHit(wParam);
        InvalidateRect(hwnd, NULL, TRUE);
        return 0;
    case WM_DESTROY :
        PostQuitMessage (0) ;
        return 0 ;
    }
    return DefWindowProc (hwnd, message, wParam, lParam) ;
}

void Text(int xa, int ya, const char txt[])
{
    TextOut(Memhdc, xa, ya, txt, (int)strlen(txt));
}

void Line(int xa, int ya, int xe, int ye)
{
    MoveToEx(Memhdc, xa, ya, NULL);
    LineTo(Memhdc, xe, ye);
}

void Rect(int xa, int ya, int xe, int ye)
{
    Rectangle(Memhdc, xa, ya, xe, ye);
}

void Elli(int xa, int ya, int xe, int ye)
{
    Ellipse(Memhdc, xa, ya, xe, ye);
}

void LineCol(int r, int g, int b)
{
    HPEN hp=hpNewPen;
    hpNewPen=CreatePen(PS_SOLID, 1, RGB(r,g,b));
    SelectObject(Memhdc, hpNewPen);
    if (hp)DeleteObject(hp);
}

void FillCol(int r, int g, int b)
{
    HBRUSH hb=hbNewBrush;
    if(r>=0 && g>=0 && b>=0)
    {
        hbNewBrush=CreateSolidBrush(RGB(r,g,b));
        SelectObject(Memhdc, hbNewBrush);
        if (hb)DeleteObject(hb);
    }
    else
    {
        SelectObject(Memhdc, GetStockObject(HOLLOW_BRUSH));
    }
}

void PutPixel(int xa, int ya, COLORREF crColora)
{
    SetPixel(Memhdc, xa, ya, crColora);
}

void FillPoly(int* lpPoint, int nPoints)
{
    Polygon(Memhdc, (LPPOINT)lpPoint, nPoints);
}

#endif

#ifdef __unix__
#include <stdlib.h>
#include <gtk/gtk.h>
#include <pango/pango.h>
#include "WinAdapt.h"


extern void VtlPaint (int, int, int, int);
extern void VtlZyk (void);
extern void VtlMouse (int X, int Y);
extern void VtlKeyHit (int key);
extern void VtlInit (void);

enum {FG, FILL, BLACK};

GtkWidget *drawing_area;
GdkGC *gc;
GdkColor colors[] ={{0,0,0,0},{0, 65535, 65535, 65535},{0, 0, 0, 0}};
PangoLayout *layout;
bool do_fill=false;

void Text(int xa, int ya, const char txt[])
{
    gdk_gc_set_rgb_fg_color(gc, &colors[BLACK]);
    pango_layout_set_text(layout, txt, -1);
    gdk_draw_layout (drawing_area->window, gc, xa, ya, layout);
}

void Line(int xa, int ya, int xe, int ye)
{
    gdk_gc_set_rgb_fg_color(gc, &colors[FG]);
    gdk_draw_line (drawing_area->window, gc, xa, ya, xe, ye);
}

void Rect(int xa, int ya, int xe, int ye)
{
    if (do_fill) {
	gdk_gc_set_rgb_fg_color(gc, &colors[FILL]);
	gdk_draw_rectangle (drawing_area->window, gc, TRUE, xa,ya,xe-xa,ye-ya);
    }
    gdk_gc_set_rgb_fg_color(gc, &colors[FG]);
    gdk_draw_rectangle (drawing_area->window, gc, FALSE, xa,ya,xe-xa,ye-ya);
}

void Elli(int xa, int ya, int xe, int ye)
{
    if (do_fill) {
	gdk_gc_set_rgb_fg_color(gc, &colors[FILL]);
	gdk_draw_arc (drawing_area->window, gc, TRUE, xa, ya, xe-xa, ye-ya, 0, 64 * 360);
    }
    gdk_gc_set_rgb_fg_color(gc, &colors[FG]);
    gdk_draw_arc (drawing_area->window, gc, FALSE, xa, ya, xe-xa, ye-ya, 0, 64 * 360);
}

void LineCol(int r, int g, int b)
{
    colors[FG].red = r * 65535/255;
    colors[FG].green = g * 65535/255;
    colors[FG].blue = b * 65535/255;
}

void FillCol(int r, int g, int b)
{
    if (r==-1 && g==-1 && b==-1) {
	do_fill=false;
    } else {
	do_fill=true;
	colors[FILL].red = r * (65535/255);
	colors[FILL].green = g * (65535/255);
	colors[FILL].blue = b* (65535/255);
    }
}

void PutPixel(int xa, int ya, GdkColor color)
{
    gdk_gc_set_rgb_fg_color(gc, &color);
    gdk_draw_point (drawing_area->window, gc, xa, ya);
}

void FillPoly(int* lpPoint, int nPoints)
{
    if (do_fill) {
	gdk_gc_set_rgb_fg_color(gc, &colors[FILL]);
	gdk_draw_polygon (drawing_area->window, gc, TRUE, (GdkPoint*)lpPoint, nPoints);
    }
    gdk_gc_set_rgb_fg_color(gc, &colors[FG]);
    gdk_draw_polygon (drawing_area->window, gc, FALSE, (GdkPoint*)lpPoint, nPoints);
}

gboolean timeout_callback (gpointer __attribute__((unused))data)
{

    VtlZyk();
    gtk_widget_queue_draw(drawing_area);
    return TRUE;
}


    gboolean
expose_event_callback (GtkWidget __attribute__((unused))*widget, GdkEventExpose __attribute__((unused))*event, gpointer __attribute__((unused))data)
{
    LineCol(0,0,0);
    FillCol(255,255,255);
    VtlPaint(0,0,drawing_area->allocation.width-1,
	    drawing_area->allocation.height-1);
    return TRUE;
}

void realize_event_callback (GtkWidget __attribute__((unused))*widget, gpointer __attribute__((unused))data)
{
    VtlInit();
}

gboolean  key_event_callback( GtkWidget *widget, GdkEventKey *event,
	__attribute__((unused))gpointer data )
{

    if (event->keyval<0xff) { // ignore special keys
	if (event->state & GDK_CONTROL_MASK) { //
	    VtlKeyHit((event->keyval&0x5f)-'A'+1);
	} else {
	    VtlKeyHit(event->keyval);
	}
	gtk_widget_queue_draw(widget);
	return TRUE;
    }
    return FALSE;
}

gboolean mouse_event_callback( GtkWidget *widget, GdkEventButton *event,
	__attribute__((unused))gpointer data )
{
    if  (event->button == 1) {
       	VtlMouse((int)event->x, (int)event->y);
	gtk_widget_queue_draw(widget);
    }
    return TRUE;
}

int main( int   argc,
	char *argv[] )
{
    /* GtkWidget is the storage type for widgets */
    GtkWidget *window;

    GdkColor tmpcol= {0, 65535, 65535, 65535};


    gtk_init (&argc, &argv);

    /* Create a new window */
    window = gtk_window_new (GTK_WINDOW_TOPLEVEL);

    gtk_window_set_default_size(GTK_WINDOW(window), 640,480);
    gtk_window_set_title (GTK_WINDOW (window), "Gadapt");

    /* It's a good idea to do this for all windows. */
    g_signal_connect (G_OBJECT (window), "destroy", G_CALLBACK (gtk_main_quit), NULL);

    g_signal_connect (G_OBJECT (window), "delete_event", G_CALLBACK (gtk_main_quit), NULL);

    drawing_area = gtk_drawing_area_new ();

    g_signal_connect (drawing_area, "expose_event",  G_CALLBACK (expose_event_callback), NULL);
    g_signal_connect (G_OBJECT (drawing_area), "realize", G_CALLBACK (realize_event_callback), NULL);
    g_signal_connect (G_OBJECT (drawing_area), "button-release-event", G_CALLBACK (mouse_event_callback), NULL);
    g_signal_connect (G_OBJECT (window), "key-release-event", G_CALLBACK (key_event_callback), NULL);
    g_timeout_add(100, (GSourceFunc) timeout_callback, NULL);
    gtk_widget_add_events( drawing_area, GDK_BUTTON_RELEASE_MASK | GDK_BUTTON_PRESS_MASK );

    /* Pack and show all our widgets */
    gtk_widget_show (drawing_area);
    gtk_container_add (GTK_CONTAINER (window), drawing_area);
    gtk_widget_show (window);
    gc = gdk_gc_new(drawing_area->window);
    gtk_widget_modify_bg (drawing_area, gtk_widget_get_state(drawing_area), &tmpcol);
    layout = gtk_widget_create_pango_layout (drawing_area, NULL);

    /* Rest in gtk_main and wait for the fun to begin! */
    gtk_main ();

    return 0;
}
#endif


