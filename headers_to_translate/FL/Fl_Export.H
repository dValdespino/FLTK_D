/*
 * Windows DLL export .
 *
 * Copyright 1998-2018 by Bill Spitzak and others.
 *
 * This library is free software. Distribution and use rights are outlined in
 * the file "COPYING" which should have been included with this file.  If this
 * file is missing or damaged, see the license at:
 *
 *     https://www.fltk.org/COPYING.php
 *
 * Please see the following page on how to report bugs and issues:
 *
 *     https://www.fltk.org/bugs.php
 */

#ifndef _H
#  define _H

/*
 * The following is only used when building DLLs under Windows...
 */

#  if defined(FL_DLL)
#    ifdef FL_LIBRARY
#      define __declspec(dllexport)
#    else
#      define __declspec(dllimport)
#    endif /* FL_LIBRARY */
#  elif __GNUC__ >= 4
#    define __attribute__ ((visibility ("default")))
#  else
#    define
#  endif /* FL_DLL */

#endif /* ! _H */
