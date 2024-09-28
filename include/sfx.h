#ifndef _SFX_H_
#define _SFX_H_

/*
 * XBoing - An X11 blockout style computer game
 *
 * (c) Copyright 1993, 1994, 1995, Justin C. Kibell, All Rights Reserved
 *
 * The X Consortium, and any party obtaining a copy of these files from
 * the X Consortium, directly or indirectly, is granted, free of charge, a
 * full and unrestricted irrevocable, world-wide, paid up, royalty-free,
 * nonexclusive right and license to deal in this software and
 * documentation files (the "Software"), including without limitation the
 * rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons who receive
 * copies from any such party to do so.  This license includes without
 * limitation a license to do the foregoing actions under any patents of
 * the party supplying this software to the X Consortium.
 *
 * In no event shall the author be liable to any party for direct, indirect,
 * special, incidental, or consequential damages arising out of the use of
 * this software and its documentation, even if the author has been advised
 * of the possibility of such damage.
 *
 * The author specifically disclaims any warranties, including, but not limited
 * to, the implied warranties of merchantability and fitness for a particular
 * purpose.  The software provided hereunder is on an "AS IS" basis, and the
 * author has no obligation to provide maintenance, support, updates,
 * enhancements, or modifications.
 */

/* 
 * =========================================================================
 *
 * $Id: sfx.h,v 1.1.1.1 1994/12/16 01:36:53 jck Exp $
 * $Source: /usr5/legends/jck/xb/master/xboing/include/sfx.h,v $
 * $Revision: 1.1.1.1 $
 * $Date: 1994/12/16 01:36:53 $
 *
 * $Log: sfx.h,v $
 * Revision 1.1.1.1  1994/12/16  01:36:53  jck
 * The XBoing distribution requires configuration management. This is why the
 * cvs utility is being used. This is the initial import of all source etc..
 *
 *
 * =========================================================================
 */

/*
 *  Dependencies on other include files:
 */

#include <X11/Xlib.h>

/*
 *  Constants and macros:
 */

// [DOXYGEN] Could replace list with enum
#define SFX_NONE        0
#define SFX_SHAKE      	1
#define SFX_FADE  		2
#define SFX_BLIND  		3
#define SFX_SHATTER  	4
#define SFX_STATIC  	5

/*
 *  Function prototypes:
 */

// [DOXYGEN] Accessor for modifying the value of the sfxEndFrame variable
void SetSfxEndFrame(int endFrame);

// [DOXYGEN] Accessor for modifying the value of the modeSfx variable
void changeSfxMode(int newMode);

// [DOXYGEN] Undefined function. Should be removed
int oldSfxMode(void);

// [DOXYGEN] Accessor for modeSfx variable (returns value)
int currentSfxMode(void);

// [DOXYGEN] Effect: Shakes the window (up to 3px x & y)
int WindowShakeEffect(Display *display, Window window);

// [DOXYGEN] Effect: Draws shattering window effect
int WindowShatterEffect(Display *display, Window window);

// [DOXYGEN] Effect: Little doors close over the screen
int WindowBlindEffect(Display *display, Window window);

// [DOXYGEN] Effect: Horizontal and Vertical bars slowely cover the screen (fade)
int WindowFadeEffect(Display *display, Window window, int w, int h);

// [DOXYGEN] Effect: draws static on screen
int WindowStaticEffect(Display *display, Window window, int w, int h);

// [DOXYGEN] Accessor for useSfx variable (returns value)
int getSpecialEffects(Display *display);

// [DOXYGEN] Accessor for modifying the value of the useSfx variable
void useSpecialEffects(int state);

// [DOXYGEN] Resets window border. Could be removed
void ResetBorderGlow(Display *display, Window window);

// [DOXYGEN] Effect: Window border glows red and green
void BorderGlow(Display *display, Window window);

// [DOXYGEN] Effect: Fade away / closing screen transtition
void FadeAwayArea(Display *display, Window window, int x, int y, int w, int h);

#endif