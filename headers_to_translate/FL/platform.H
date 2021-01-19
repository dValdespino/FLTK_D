//
// Platform header file for the Fast Light Tool Kit (FLTK).
//
// Copyright 1998-2020 by Bill Spitzak and others.
//
// This library is free software. Distribution and use rights are outlined in
// the file "COPYING" which should have been included with this file.  If this
// file is missing or damaged, see the license at:
//
//     https://www.fltk.org/COPYING.php
//
// Please see the following page on how to report bugs and issues:
//
//     https://www.fltk.org/bugs.php
//

// These are FLTK symbols that are necessary or useful for calling
// platform specific functions. This file #include's certain platform
// specific system header files that are necessary to declare platform
// specific FLTK functions, for instance "Windows.h" under Windows.

// You should include this file if (and ONLY if) you need to call
// platform specific functions directly.

// See FLTK documentation: chapter "Operating System Issues" on when
// you need to #include <FL/platform.H>

#if !defined(FL_PLATFORM_H) && !defined(FL_DOXYGEN)
#  define FL_PLATFORM_H

#   include <FL/ .H>
#   include <FL/platform_types.h>
#   include <FL/fl_types.h> // for uchar
class Fl_Window;

#  ifdef _WIN32
#    include "win32.H"
#  elif defined(__APPLE__)
#    include "mac.H"
#  elif defined(__ANDROID__)
#    include "android.H"
#  else // X11
#   include <FL/fl_types.h>
#   include <FL/Enumerations.H>
#    if !defined(USE_X11)
#      define USE_X11 1
#    endif
#    if defined(_ABIN32) || defined(_ABI64) // fix for broken SGI Irix X .h files
#      pragma set woff 3322
#    endif
#    include <X11/Xlib.h>
#    include <X11/Xutil.h>
#    if defined(_ABIN32) || defined(_ABI64)
#      pragma reset woff 3322
#    endif
#    include <X11/Xatom.h>

// constant info about the X server connection:
extern Display* fl_display;
extern int fl_screen;
extern XVisualInfo* fl_visual;
extern Colormap fl_colormap;

// drawing functions:
extern GC fl_gc;
ulong fl_xpixel(Fl_Color i);
ulong fl_xpixel(uchar r, uchar g, uchar b);

// feed events into fltk:
int fl_handle(const XEvent &);

// you can use these in Fl::add_handler() to look at events:
extern const XEvent* fl_xevent;
extern ulong fl_event_time;

#if defined(FL_LIBRARY) || defined(FL_INTERNALS)
extern Window fl_message_window;
extern void* fl_xftfont;

// access to core fonts:
// This class provides a "smart pointer" that returns a pointer to an XFontStruct.
// The global variable fl_xfont can be called wherever a bitmap "core" font is
// needed, e.g. when rendering to a GL context under X11.
// With Xlib / X11 fonts, fl_xfont will return the current selected font.
// With XFT / X11 fonts, fl_xfont will attempt to return the bitmap "core" font most
// similar to (usually the same as) the current XFT font.
class Fl_XFont_On_Demand
{
public:
  Fl_XFont_On_Demand(XFontStruct* p = NULL) : ptr(p) { }
  Fl_XFont_On_Demand &operator=(const Fl_XFont_On_Demand &x)
  { ptr = x.ptr;  return *this; }
  Fl_XFont_On_Demand &operator=(XFontStruct* p)
  { ptr = p;  return *this; }
  XFontStruct* value();
  operator XFontStruct* () { return value(); }
  XFontStruct &operator*() { return *value(); }
  XFontStruct* operator->() { return value(); }
  bool operator==(const Fl_XFont_On_Demand &x) { return ptr == x.ptr; }
  bool operator!=(const Fl_XFont_On_Demand &x) { return ptr != x.ptr; }
private:
  XFontStruct* ptr;
};
extern Fl_XFont_On_Demand fl_xfont;

extern char fl_override_redirect; // hack into Fl_X::make_xid()
extern int fl_background_pixel;  // hack into Fl_X::make_xid()

#endif // FL_LIBRARY || FL_INTERNALS

#  endif // X11

//
// cross-platform declarations
//
#if defined(FL_LIBRARY) || defined(FL_INTERNALS)
#  include <FL/Fl_Window.H>

class Fl_X {
public:
  Window xid;
  Fl_Window* w;
  Fl_Region region;
  Fl_X* next;
  // static variables, static functions and member functions
  static Fl_X* first;
  static Fl_X* i(const Fl_Window* w) {return (Fl_X*)w->i;}
#  if defined(USE_X11) // for backward compatibility
  static void make_xid(Fl_Window*, XVisualInfo* = fl_visual, Colormap = fl_colormap);
  static Fl_X* set_xid(Fl_Window*, Window);
#  endif
};

inline Window fl_xid(const Fl_Window* w) { Fl_X* xTemp = Fl_X::i(w); return xTemp ? xTemp->xid : 0; }
#else
extern Window fl_xid_(const Fl_Window* w);
#  define fl_xid(w) fl_xid_(w)
#endif // FL_LIBRARY || FL_INTERNALS

extern Fl_Window* fl_find(Window xid);
extern void fl_open_display();
extern void fl_close_display();
extern Window fl_window;
extern Fl_Bitmask fl_create_bitmask(int w, int h, const uchar* data);
extern Fl_Bitmask fl_create_alphamask(int w, int h, int d, int ld, const uchar* data);
extern void fl_delete_bitmask(Fl_Bitmask bm);
extern int fl_parse_color(const char* p, uchar &r, uchar &g, uchar &b);
extern void fl_open_callback(void (*)(const char*));

#endif // !FL_PLATFORM_H
