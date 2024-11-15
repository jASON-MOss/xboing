// TODO: typedefs we have to make to get past compiler errors, these all
//       indicate things we need to change
#ifndef FAKETYPES_H
#define FAKETYPES_H

//#include <raylib.h>

typedef int Display;
typedef int Window;
typedef int Colormap;
typedef unsigned long int u_long;
typedef int KeySym;
typedef int uid_t;
typedef int Pixmap;

// Raylib Types
//typedef int Texture2D;

// Boolean macros
#define False 0
#define True 1

// Random macros
#define None 0
#define CWWidth (1<<2)
#define CWHeight (1<<3)
#define CoordModeOrigin 0
#define Always 1
#define ParentRelative 0
#define XBLACK 0
#define XWHITE 0
#define CopyFromParent 0


//SizeHint macros
#define PPosition (1L<<2)
#define PSize (1L<<3)
#define PMinSize (1L<<4)
#define PMaxSize (1L<<5)
#define NormalState 1

//Wm_Hints macros
#define StateHint (1L<<1)
#define InputHint (1L<<0)
#define IconPixmapHint (1L<<2)
#define IconWindowHint (1L<<3)

//Window Attributes
#define CWColormap (1L<<13)
#define CWBackingStore (1L<<6)

// XPM error macros
#define XpmColorError    1
#define XpmSuccess       0
#define XpmOpenFailed   -1
#define XpmFileInvalid  -2
#define XpmNoMemory     -3
#define XpmColorFailed  -4

// Relating to the X11 graphical context
typedef int Display;
typedef int Window;
typedef int GC; // graphics context

// Drawing / graphical manipulations
typedef int Colormap;
typedef int Pixmap;
typedef int Region; // A region of pixels

typedef struct{
    short x, y;
} XPoint;

typedef struct {
    int pixel;
} XColor;

typedef struct{
    int attributes;
    unsigned long valuemask;
    int XpmColormap;
}XpmAttributes;

// GC Values (from X11)
typedef enum {
    LineSolid,
    LineOnOffDash,
    LineDoubleDash
} line_style;
typedef enum {
    CapNotLast,
    CapButt,
    CapRound,
    CapProjecting
} cap_style;
typedef enum{
    JoinMiter,
    JoinRound,
    JoinBevel
} join_style;

// Key Masks

#define KeyPressMask           0
#define KeyReleaseMask         0
#define ButtonPressMask        0
#define ButtonReleaseMask      0 
#define ButtonMotionMask       0
#define ExposureMask           0
#define StructureNotifyMask    0
#define PointerMotionHintMask  0

#define XK_A      65
#define XK_a      97
#define XK_B      66
#define XK_b      98
#define XK_C      67
#define XK_c      99
#define XK_D      68
#define XK_d      100
#define XK_E      69
#define XK_e      101
#define XK_F      70
#define XK_f      102
#define XK_G      71
#define XK_g      103
#define XK_H      72
#define XK_h      104
#define XK_I      73
#define XK_i      105
#define XK_J      74
#define XK_j      106
#define XK_K      75
#define XK_k      107
#define XK_L      76
#define XK_l      108
#define XK_M      77
#define XK_m      109
#define XK_N      78
#define XK_n      110
#define XK_O      79
#define XK_o      111
#define XK_P      80
#define XK_p      112
#define XK_Q      81
#define XK_q      113
#define XK_R      82
#define XK_r      114
#define XK_S      83
#define XK_s      115
#define XK_T      84
#define XK_t      116
#define XK_U      85
#define XK_u      117
#define XK_V      86
#define XK_v      118
#define XK_W      87
#define XK_w      119
#define XK_X      88
#define XK_x      120
#define XK_Y      89
#define XK_y      121
#define XK_Z      90
#define XK_z      122

#define XK_space  32
#define XK_Left   0
#define XK_Right  0
#define XK_asciitilde  126
#define XK_Escape      27
#define XK_Return      013
#define XK_Delete      127
#define XK_BackSpace   8 

#define XK_1      49
#define XK_2      50
#define XK_3      51
#define XK_4      52
#define XK_5      53
#define XK_6      54
#define XK_7      55
#define XK_8      56
#define XK_9      57
#define XK_0      48

#define KeyPress  0
#define Expose    1


// Mouse Events

#define Button1  0
#define Button2  0
#define Button3  0

#define CURSOR_PLUS   0
#define CURSOR_POINT  0

typedef struct {
    int button;
    int subwindow;
} XButtonEvent;

typedef struct {
    int key;
} XKeyEvent;

typedef struct {
    XButtonEvent xbutton;
    XKeyEvent xkey;
    int type;
} XEvent;

// Uncategorized

typedef unsigned long int u_long;

#define EvenOddRule  0

typedef struct {
    int ascent;
    int descent;
    int fid;
} XFontStruct;

typedef struct {
    int x, y;
    int width, height;
    int border_width;
    int sibling;
    int stack_mode;
} XWindowChanges;
typedef struct {
    int width;
    int height;
} XWindowAttributes;

typedef int KeySym;

typedef struct{
    int flags;
    int min_width;
    int min_height;
    int max_width;
    int max_height;
} XSizeHints;
typedef struct{
    char *res_name;
    char *res_class;
} XClassHint;

typedef int XTextProperty;

typedef struct{
    int initial_state;
    int input;
    int icon_pixmap;
    int icon_window;
    int flags;
} XWMHints;
typedef struct{
    Colormap colormap;
    int backing_store;
} XSetWindowAttributes;

typedef struct {
    int compose_index;
} XComposeStatus;

#endif
