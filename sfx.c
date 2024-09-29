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
 * $Id: sfx.c,v 1.1.1.1 1994/12/16 01:36:45 jck Exp $
 * $Source: /usr5/legends/jck/xb/master/xboing/sfx.c,v $
 * $Revision: 1.1.1.1 $
 * $Date: 1994/12/16 01:36:45 $
 *
 * $Log: sfx.c,v $
 * Revision 1.1.1.1  1994/12/16  01:36:45  jck
 * The XBoing distribution requires configuration management. This is why the
 * cvs utility is being used. This is the initial import of all source etc..
 *
 *
 * =========================================================================
 */

/*
 *  Include file dependencies:
 */

#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <X11/Xos.h>
#include <xpm.h>

#include "error.h"
#include "init.h"
#include "stage.h"
#include "score.h"
#include "blocks.h"
#include "ball.h"
#include "main.h"
#include "mess.h"
#include "misc.h"
#include "intro.h"

#include "sfx.h"

/*
 *  Internal macro definitions:
 */

#define SHAKE_DELAY			5
#define NUM_SCAT 			10 
#define RANDY(range) 		(rand() % (range))

/*
 *  Internal variable declarations:
 */

static int sfxEndFrame, useSfx;
int modeSfx;
static int xscat[NUM_SCAT] = { 1, 9, 3, 6, 2, 4, 0, 7, 5, 8 };
static int yscat[NUM_SCAT] = { 2, 1, 0, 8, 6, 4, 9, 3, 7, 5 };


/**
 * Accesor used for modyfying the state of special effects.
 *
 * @param int state True to enable special effects, False to disable.
 * 
 */
void useSpecialEffects(int state)
{
	/* Set the state of the special effects - True = use */
	/* Of course - if the sfx are not possible then no effect */
	useSfx = state;
}


/**
 * Accessor for useSfx variable (return value)
 *
 * @param Display *display The display of the X11 window
 * 
 */
int getSpecialEffects(Display *display)
{
	/* Only shake around if the server has backing store on */
	if (DoesBackingStore(XDefaultScreenOfDisplay(display)) != Always)
		return -1;

	/* Return special effects state - on or off */
	return useSfx;
}


/**
 * Accessor for modifying the value of the modeSfx variable
 *
 * @param int newMode The new mode for the special effects.
 * 
 */
void changeSfxMode(int newMode)
{
	modeSfx = newMode;
}


/**
 * Accessor for the current state of modeSfx variable
 * 
 * @return int The current special effects mode
 * 
 */
int currentSfxMode(void)
{
	/* Return the current special effects mode */
	return modeSfx;
}

/**
 * Resets the sfx-mode and recenters the window
 *
 * @param Display *display The display of the X11 window
 * 
 */
static void resetEffect(Display *display)
{
	/* Just re-centre window return */
	modeSfx = SFX_NONE;
	XMoveWindow(display, playWindow, 35, 60);
}


/**
 * Creates a window blind closing effect on the screen.
 *
 * @param Display *display The display of the X11 window
 * @param Window window The X11 window to draw on
 * 
 */
int WindowBlindEffect(Display *display, Window window)
{
	int x, i;

	/* Does the user want special effects */
	if (useSfx == False)
	{
		/* No - Just return out */
		resetEffect(display);
		return False;
	}

	XSetBackground(display, gcsfx, black);

	/* Draw a blinds effect where little doors close over screen */
	for (i = 0; i <= (PLAY_WIDTH / 8); i++)
		for (x = 0; x <= PLAY_WIDTH; x += (PLAY_WIDTH / 8))
			XCopyArea(display, bufferWindow, window, gc, 
				x+i, 0, 1, PLAY_HEIGHT, x+i, 0);

	/* End of special effect - reset off */
	resetEffect(display);
	return False;
}


/**
 * Creates a static effect on the screen.
 *
 * @param Display *display The display of the X11 window
 * @param Window window The X11 window to draw on
 * @param int w The width of the window.
 * @param int h The height of the window.
 * @return int True while the effect is going, False when the effect is done.
 */
int WindowStaticEffect(Display *display, Window window, int w, int h)
{
	static int start = True;

	if (start)
	{
		SetSfxEndFrame(frame + 50);
		start = False;
	}

	/* Do somehting in here */

	if (frame >= sfxEndFrame) 
	{
		/* End of special effect - reset off */
		resetEffect(display);
		start = True;
		return False;
	}

	return True;
}


/**
 * Creates a window shattering effect.
 *
 * @param Display *display The display of the x11 window
 * @param Window window The X11 window to draw on.
 *  
 * @return int False when done.
 * 
 */
int WindowShatterEffect(Display *display, Window window)
{
    int offx, offy, sizeWidth, sizeHeight;
    int srcx, srcy, destx, desty;

	/* Does the user want special effects */
	if (useSfx == False)
	{
		/* No - Just return out */
		resetEffect(display);
		return False;
	}


    offx = RANDY(NUM_SCAT);
    offy = RANDY(NUM_SCAT);
	sizeWidth = 200;
	sizeHeight = 200;

	/* Spend a bit of time scattering new pixmap into view */
	/* Original idea for this effect from xjewel */
    for (srcx = 0; srcx < NUM_SCAT; srcx++)
    {
    	for (srcy = 0; srcy < NUM_SCAT; srcy++)
        {
            for (destx = 0; destx <= 4; destx++)
			{
            	for (desty = 0; desty <= 5; desty++)
                {
					XCopyArea(display, bufferWindow, window, gc, 
                    	(destx * sizeWidth) + 
                        	xscat[(srcx + srcy + offx) % NUM_SCAT] 
							* (sizeWidth / NUM_SCAT),

                    	(desty * sizeHeight) + 
                        	yscat[(srcy + offy) % NUM_SCAT] 
							* (sizeHeight / NUM_SCAT),

                    	(sizeWidth  / NUM_SCAT), 
						(sizeHeight / NUM_SCAT),

                    	(destx * sizeWidth) + 
                        	xscat[(srcx + srcy + offx) % NUM_SCAT] 
							* (sizeWidth / NUM_SCAT),

                    	(desty * sizeHeight) + 
                        	yscat[(srcy + offy) % NUM_SCAT] 
							* (sizeHeight / NUM_SCAT));
               	}
			}
        }
    }

	/* End of special effect - reset off */
	resetEffect(display);
	return False;
}


/**
 * Creates a window fade effect using horizontal and vertical bars.
 *
 * @param Display *display The displat to the X11 window
 * @param Window window The X11 window to draw on
 * @param int w The width of the window.
 * @param int h The height of the window.
 *  
 * @return int True while the effect is going, False when the effect is finished.
 * 
 */
int WindowFadeEffect(Display *display, Window window, int w, int h)
{
	static int done = False;
	static int first = True;
	int y;
	int x;
	static int i = 0;

	/* Does the user want special effects */
	if (useSfx == False)
	{
		/* No - Just return out */
		resetEffect(display);
		return False;
	}

	if (first == True)
	{
		first = False;
		XSetForeground(display, gcsfx, black);
		XSetBackground(display, gcsfx, black);
		XSetWindowBorder(display, window, red);
	}

	/* Draw vertical lines */
	for (x = i; x <= w; x += 12)
		XDrawLine(display, window, gcsfx, x, 0, x, h);

	/* Draw horizontal lines */
	for (y = i; y <= h; y += 12)
		XDrawLine(display, window, gcsfx, 0, y, w, y);

	/* Fill in grid slowly */
	i++;
	if (i > 12) done = True;

	if (done == True)
	{
		/* End of special effect - reset off */
		done = False;
		first = True;
		i = 0;
		resetEffect(display);
		return False;
	}

	/* Keep efect going please */
	return True;
}



/**
 * Creates a window shake effect.
 *
 * @param Display *display The display of the X11 window
 * @param Window window The X11 window to draw on
 *  
 * @return int True while the effect is going, False when the effect is finished.
 * 
 */
int WindowShakeEffect(Display *display, Window window)
{
	static int x = 35;
	static int y = 60;
	int xi, yi;

	/* Does the user want special effects */
	if (useSfx == False)
	{
		/* No - Just return out */
		resetEffect(display);
		return False;
	}

	/* Only shake around if the server has backing store on */
	if (DoesBackingStore(XDefaultScreenOfDisplay(display)) != Always)
	{
		resetEffect(display);
		return False;
	}

	if (frame >= sfxEndFrame) 
	{
		/* End of special effect - reset off */
		resetEffect(display);
		return False;
	}
	
	if ((frame % SHAKE_DELAY) != 0) return True;

	XMoveWindow(display, window, x, y);
	XFlush(display);

	xi = (rand() % 6) - 3; 
	yi = (rand() % 6) - 3; 
	x = xi + 35; y = yi + 60;

	return True;
}


/**
 * Accessor for modifying the value of the sfxEndFrame variable.
 *
 * @param int endFrame The frame where the special effects should end.
 *  
 * 
 */
void SetSfxEndFrame(int endFrame)
{
	sfxEndFrame = endFrame;
}



/**
 * Creates a glowing border effect.
 *
 * @param Display *display The display of the X11 window
 * @param Window window The X11 window to draw on
 * 
 */
void BorderGlow(Display *display, Window window)
{
    static int i = 0;
    static int d = 1;
    static int t = 1;

	/* Does the user want special effects */
	if (useSfx == False)
	{
		/* No - Just return out */
		return;
	}

	/* Only update every n frames */
    if ((frame % 40) == 0)
    {
		/* Alternate between the red and the green ranges */
        if (t > 0)
            XSetWindowBorder(display, playWindow, reds[i]);
        else
            XSetWindowBorder(display, playWindow, greens[i]);

		/* Ok change range or fade down again */
        if (i == 6)
        {
            d = -1;
            t *= -1;
        }

        if (i == 0)
            d = 1;

		/* Next range index */
        i += d;
     }
}



/**
 * Resets the window border.
 *
 * @param Display *display The display of the X11 window
 * @param Window window The X11 window to draw on
 * 
 */
void ResetBorderGlow(Display *display, Window window)
{
    XSetWindowBorder(display, playWindow, red);
}


/**
 * Creates a fade-away effect in specified area.
 *
 * @param Display *display The display of the X11 window
 * @param Window window The X11 window to draw on
 * @param int x The x coordinate of the area.
 * @param int y The y coordinate of the area
 * @param int w The width of the area.
 * @param int h The height of hte area.
 * 
 */
void FadeAwayArea(Display *display, Window window, int x, int y, int w, int h)
{
	int i, x1, y1, step;

	step = w / 15;

	/* Fade away an area slowly so it looks good */
	for (i = 0; i <= step; i++)
	{
		/* Draw vertical lines */
		for (x1 = i; x1 <= w; x1 += 15)
			XClearArea(display, window, x + x1, y, 1, h, False);
	
		/* Draw horizontal lines */
		for (y1 = i; y1 <= h; y1 += 15)
			XClearArea(display, window,  x, y + y1, w, 1, False);
	}
}
