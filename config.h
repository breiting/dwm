/* See LICENSE file for copyright and license details. */

/* appearance */
static const unsigned int borderpx = 1; /* border pixel of windows */
static const unsigned int snap = 32;    /* snap pixel */
static const int swallowfloating
= 0;                      /* 1 means swallow floating windows by default */
static const int showbar = 1; /* 0 means no bar */
static const int topbar = 1;  /* 0 means bottom bar */
static const char* fonts[] = { "monospace:size=10", "JoyPixels:pixelsize=8:antialias=true:autohint=true" };
static const char dmenufont[] = "monospace:size=10";
static const char col_gray1[] = "#222222";
static const char col_gray2[] = "#444444";
static const char col_gray3[] = "#bbbbbb";
static const char col_gray4[] = "#eeeeee";
static const char col_cyan[] = "#005577";

static const char* colors[][3] = {
    /*               fg         bg         border   */
    [SchemeNorm] = { col_gray3, col_gray1, col_gray2 },
    [SchemeSel] = { col_gray4, col_cyan, col_cyan },
};

/* tagging */
static const char* tags[] = { "1", "2", "3", "4", "5", "6", "7", "8", "9" };

static const Rule rules[] = {
    /* xprop(1):
     *  WM_CLASS(STRING) = instance, class
     *  WM_NAME(STRING) = title
     */
    /* class     instance  title           tags mask  isfloating  isterminal
       noswallow  monitor */
    { NULL        , NULL , NULL           , 0      , 0 , 0 , 1  , -1 } ,
    { "Gimp"      , NULL , NULL           , 0      , 1 , 0 , 0  , -1 } ,
    { "Firefox"   , NULL , NULL           , 1 << 8 , 0 , 0 , -1 , -1 } ,
    { "Alacritty" , NULL , NULL           , 0      , 0 , 1 , -1 , -1 } ,
    { "st"        , NULL , NULL           , 0      , 0 , 1 , -1 , -1 } ,
    { NULL        , NULL , "Event Tester" , 0      , 1 , 0 , 1  , -1 } , /* xev */
    { NULL        , NULL , "pview"        , 0      , 1 , 0 , 1  , -1 } ,
    { NULL        , NULL , "pvui"         , 0      , 1 , 0 , 1  , -1 } ,
    { NULL        , NULL , "pbv"          , 0      , 1 , 0 , 1  , -1 } ,
    { NULL        , NULL , "rxv"          , 0      , 1 , 0 , 1  , -1 } ,
};

/* layout(s) */
static const float mfact = 0.55; /* factor of master area size [0.05..0.95] */
static const int nmaster = 1;    /* number of clients in master area */
static const int resizehints
= 1; /* 1 means respect size hints in tiled resizals */

static const char scratchpadname[] = "scratchpad";
static const char* scratchpadcmd[]
= { "st", "-t", scratchpadname, "-g", "120x34", NULL };

static const Layout layouts[] = {
    /* symbol     arrange function */
    { "[]=", tile }, /* first entry is default */
    { "><>", NULL }, /* no layout function means floating behavior */
    { "[M]", monocle },
};

/* key definitions */
#define XF86AudioMute 0x1008ff12
#define XF86AudioLowerVolume 0x1008ff11
#define XF86AudioRaiseVolume 0x1008ff13
#define XF86LaunchB 0x1008ff4b
#define MODKEY Mod1Mask /* Mod4 for Mac Keyboards */
#define WINKEY Mod4Mask
#define TAGKEYS(KEY, TAG)                                                      \
{ MODKEY, KEY, view, { .ui = 1 << TAG } },                                 \
{ MODKEY | ControlMask, KEY, toggleview, { .ui = 1 << TAG } },         \
{ MODKEY | ShiftMask, KEY, tag, { .ui = 1 << TAG } },                  \
{ MODKEY | ControlMask | ShiftMask, KEY, toggletag,                    \
    { .ui = 1 << TAG } },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd)                                                             \
{                                                                          \
    .v = (const char*[]) { "/bin/sh", "-c", cmd, NULL }                    \
}

/* commands */
static char dmenumon[2]                = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char* dmenucmd[]          = { "dmenu_run", "-m", dmenumon, "-fn", dmenufont, "-nb", col_gray1, "-nf", col_gray3, "-sb", col_cyan, "-sf", col_gray4, NULL };
static const char* termcmd[]           = { "alacritty", NULL };
static const char* rangercmd[]         = { "alacritty", "-e", "ranger" };
static const char* muttcmd[]           = { "alacritty", "-e", "neomutt" };
static const char* checkmailcmd[]      = { "/home/breiting/.local/bin/checkmail.sh", NULL };
static const char* togglekeyboardcmd[] = { "/home/breiting/.local/bin/togglekeyboard.sh", NULL };
static const char* cmdlock[]           = { "slock", NULL };
static const char* cmdclipmenu[]       = { "clipmenu", NULL };
static const char* cmdenv[]            = { "environment", NULL };
static const char* cmdsoundup[]        = { "amixer", "-D", "pulse", "-q", "sset", "Master", "5%+", NULL };
static const char* cmdsounddown[]      = { "amixer", "-D", "pulse", "-q", "sset", "Master", "5%-", NULL };
static const char* cmdsoundtoggle[]    = { "amixer", "-D", "pulse", "-q", "sset", "Master", "toggle", NULL };

static Key keys[] = {
    /* modifier                     key                        function
       argument */
    { MODKEY, XK_space, spawn, { .v = dmenucmd } },
    { MODKEY, XK_Return, spawn, { .v = termcmd } },
    { MODKEY, XK_grave, togglescratch, { .v = scratchpadcmd } },
    { MODKEY, XK_F12, spawn, { .v = cmdlock } },
    { MODKEY, XK_F11, fullscreen, { 0 } },
    { WINKEY, XK_j, focusstack, { .i = +1 } },
    { WINKEY, XK_k, focusstack, { .i = -1 } },
    { WINKEY, XK_i, incnmaster, { .i = +1 } },
    { WINKEY, XK_d, incnmaster, { .i = -1 } },
    { WINKEY, XK_h, setmfact, { .f = -0.05 } },
    { WINKEY, XK_l, setmfact, { .f = +0.05 } },
    { MODKEY | ShiftMask, XK_Return, zoom, { 0 } },
    { WINKEY, XK_Tab, view, { 0 } },
    { MODKEY, XK_w, killclient, { 0 } },
    { MODKEY | ShiftMask, XK_t, setlayout, { .v = &layouts[0] } },
    { 0, XF86AudioMute, spawn, { .v = cmdsoundtoggle } },
    { 0, XF86AudioRaiseVolume, spawn, { .v = cmdsoundup } },
    { 0, XF86AudioLowerVolume, spawn, { .v = cmdsounddown } },
    { 0, XF86LaunchB, spawn, { .v = cmdenv } },
    { 0, XK_Print, spawn, { .v = checkmailcmd } },
    { 0, XK_Scroll_Lock, spawn, { .v = togglekeyboardcmd } },
    { MODKEY, XK_Escape, spawn, { .v = cmdclipmenu } },
    { MODKEY | ShiftMask, XK_f, setlayout, { .v = &layouts[1] } },
    { MODKEY | ShiftMask, XK_m, setlayout, { .v = &layouts[2] } },
    { MODKEY, XK_m, spawn, { .v = muttcmd } },
    { MODKEY, XK_r, spawn, { .v = rangercmd } },
    { MODKEY | ShiftMask, XK_p, togglefloating, { 0 } },
    { MODKEY, XK_0, view, { .ui = ~0 } },
    { MODKEY | ShiftMask, XK_0, tag, { .ui = ~0 } },
    { MODKEY, XK_comma, focusmon, { .i = -1 } },
    { MODKEY, XK_period, focusmon, { .i = +1 } },
    { MODKEY | ShiftMask, XK_comma, tagmon, { .i = -1 } },
    { MODKEY | ShiftMask, XK_period, tagmon, { .i = +1 } },
    TAGKEYS(XK_1, 0) TAGKEYS(XK_2, 1) TAGKEYS(XK_3, 2) TAGKEYS(XK_4, 3)
        TAGKEYS(XK_5, 4) TAGKEYS(XK_6, 5) TAGKEYS(XK_7, 6) TAGKEYS(XK_8, 7)
        TAGKEYS(XK_9, 8) { MODKEY | ShiftMask, XK_q, quit, { 0 } },
        { MODKEY | ShiftMask, XK_r, quit, { 1 } },
};

/* button definitions */
/* click can be ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or
 * ClkRootWin */
static Button buttons[] = {
    /* click                event mask      button          function argument
    */
    { ClkLtSymbol, 0, Button1, setlayout, { 0 } },
    { ClkLtSymbol, 0, Button3, setlayout, { .v = &layouts[2] } },
    { ClkWinTitle, 0, Button2, zoom, { 0 } },
    { ClkStatusText, 0, Button2, spawn, { .v = termcmd } },
    { ClkClientWin, MODKEY, Button1, movemouse, { 0 } },
    { ClkClientWin, MODKEY, Button2, togglefloating, { 0 } },
    { ClkClientWin, MODKEY, Button3, resizemouse, { 0 } },
    { ClkTagBar, 0, Button1, view, { 0 } },
    { ClkTagBar, 0, Button3, toggleview, { 0 } },
    { ClkTagBar, MODKEY, Button1, tag, { 0 } },
    { ClkTagBar, MODKEY, Button3, toggletag, { 0 } },
};
