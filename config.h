/* PND4's DWM Config
 *
*/

#include <X11/XF86keysym.h>
/* appearance */

/* font */
//static const char font[] = "Inconsolata:style=bold:size=10:antialias=true:hinting=true" ","; 
static const char font[] = "Tamsynmod:style=Regular";

/* colors */
#define NUMCOLORS 4
static const char colors[NUMCOLORS][ColLast][9] = {
    /* ColBorder, ColFG, ColBG          */
    { "#000000", "#bbbbbb", "#000000" }, // normal -> blk border, grey fg, blk bg
    { "#005577", "#000000", "#005577" }, // selected -> blue border, black fg, blue bg
    { "#39ff14", "#dc143c", "#000000" }, // urgent -> grn border, red fg, blk bg
    { "#000000", "#1b8be0", "#000000" }, // occupied -> blk border, blue fg, blk bg
};
static const unsigned int statusmon = 1;        // On which monitor should the status appear
static const unsigned int systrayspacing = 3;   // Systray spacing
static const unsigned int borderpx = 2;         // Border pixel of windows
static const unsigned int gappx = 35;           // Gap pixel between windows
static const unsigned int snap = 25;            // Snap pixel
static const float opacity = 1;             // Opacity of the statusbar (max 0.75)
static const Bool showbar = True;               // False means no bar
static const Bool showsystray = True;           // False means no systray
static const Bool topbar = True;                // False means bottom bar

/* layout(s) */
static const float mfact = 0.60;                // factor of master area size [0.05..0.95]
static const int nmaster = 1;                   // number of clients in master area
static const Bool resizehints = False;          // True means respect size hints in tiled resizals

static const Layout layouts[] = {
    /* symbol   gaps    arrange */
    { " =[]",   True,   tile    },
    { " TTT",   True,   bstack  },
    { " [M]",   False,  monocle },
    { " -F-",   False,  NULL    },
};

/* tagging */
static const Tag tags[] = {
    /*      name         layout mfact   nmaster */
    { " \u00B9 ",   &layouts[1], -1,        -1 },
    { " \u00AD ",   &layouts[1], -1,         1 },
    { " \u00BA ",   &layouts[1], -1,        -1 },
    { " \u00E0 ",   &layouts[1], -1,        -1 },
    { " \u00B5 ",   &layouts[1], -1,        -1 },
};

/* rules */
static const Rule rules[] = {
/* WM_CLASS     WM_CLASS    WM_NAME
 * Monitor '1' is left, '0' is right, '-1' is either 
 * */
    /*class         instance    title   tags mask   isfloating  monitor */
    { NULL,         "DwmTerm",  NULL,   1 << 0,     False,       -1},
    //{ null,         "dwmweb", NULL,   1 << 1,     false,       1},
    { "Chromium",   "Chromium", NULL,   1 << 1,     False,       1},
    { NULL,         "DwmPass",  NULL,   1 << 1,     False,       0},
    { NULL,         "DwmChat",  NULL,   1 << 2,     False,       0},
    { NULL,         "DwmMusic", NULL,   1 << 3,     False,       0},
    { "Smplayer",   "smplayer", NULL,   1 << 3,     False,       0},
    { "Smtube",     "smtube",   NULL,   1 << 3,     False,       0},
    { "feh",        "feh",      NULL,   1 << 4,     True,        0},
    { "Gimp",       NULL,       NULL,   1 << 4,     False,       0},
};

/* key definitions */
#define MODKEY Mod1Mask
#define MONKEY Mod4Mask
#define TAGKEYS(KEY,TAG) \
    { MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
    { MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
    { MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
    { MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* commands */
static const char *dmenu[]          = { "dmenu_run", "-p", "[P!]", "-fn", font, "-nb", colors[0][ColBG], "-nf", colors[0][ColFG], "-sb", colors[2][ColBG], "-sf", colors[2][ColBorder], NULL };
static const char *term[]           = { "urxvtc", "-name", "DwmTerm", NULL };
static const char *browser[]        = { "chromium", "-name", NULL };
static const char *files[]          = { "urxvt", "-name", "DwmRanger", "-depth", "0", "-shading", "0", "-e", "ranger", NULL };
static const char *passlocker[]     = { "urxvtc", "-name", "DwmPass", "-e", "keepassc", NULL };
static const char *music[]          = { "urxvtc", "-name", "DwmMusic", "-e", "ncmpcpp", "-s", "visualizer", "-S", "playlist", NULL };
static const char *irc[]            = { "urxvtc", "-name", "DwmChat", "-e", "weechat-curses", NULL };
static const char *scrot[]          = { "scrot", "-s", NULL };
//static const char *lock[]         = { "slock", NULL };
//static const char *halt[]         = { "dmenu_shutdown", NULL };
static const char *volup[]          = { "amixer", "-q", "sset", "Master", "5%+", "unmute", NULL };
static const char *voldown[]        = { "amixer", "-q", "sset", "Master", "5%-", "unmute", NULL };
static const char *volmute[]        = { "amixer", "-q", "sset", "Master", "toggle", NULL };
static const char *mpdplay[]        = { "mpc", "toggle", NULL };
static const char *mpdnext[]        = { "mpc", "next", NULL };
static const char *mpdprev[]        = { "mpc", "prev", NULL };
static const char *mpdstop[]        = { "mpc", "stop", NULL };

/* key bindings */
static Key keys[] = {
    /* modifier                 key                         function        argument */
    { MODKEY,                   XK_p,                       spawn,          {.v = dmenu } },
    { MODKEY,                   XK_e,                       spawn,          {.v = files } },
    { MODKEY|ShiftMask,         XK_Return,                  spawn,          {.v = term } },
    { MODKEY,                   XK_F1,                      spawn,          {.v = passlocker } },
    { MODKEY,                   XK_F2,                      spawn,          {.v = browser } },
    { MODKEY,                   XK_F3,                      spawn,          {.v = irc } },
    { MODKEY,                   XK_F4,                      spawn,          {.v = music } },
    { MODKEY,                   XK_F5,                      spawn,          {.v = mpdplay } },
    { MODKEY,                   XK_F6,                      spawn,          {.v = mpdnext } },
    { MODKEY,                   XK_F7,                      spawn,          {.v = mpdprev } },
    { MODKEY,                   XK_F8,                      spawn,          {.v = mpdstop } },
    { MODKEY,                   XK_F11,                     spawn,          {.v = voldown } },
    { MODKEY,                   XK_F12,                     spawn,          {.v = volup } },
    { MODKEY,                   XK_Print,                   spawn,          {.v = scrot } },
    { 0,                        XF86XK_AudioMute,           spawn,          {.v = volmute } },
    { 0,                        0x1008ff12,                 spawn,          {.v = volmute } },
    { 0,                        XF86XK_AudioLowerVolume,    spawn,          {.v = voldown } },
    { 0,                        0x1008ff11,                 spawn,          {.v = voldown } },
    { 0,                        XF86XK_AudioRaiseVolume,    spawn,          {.v = volup } },
    { 0,                        0x1008ff13,                 spawn,          {.v = volup } },
    { 0,                        XF86XK_AudioPlay,           spawn,          {.v = mpdplay } },
    { 0,                        0x1008ff14,                 spawn,          {.v = mpdplay } },
    { 0,                        XF86XK_AudioPrev,           spawn,          {.v = mpdprev } },
    { 0,                        0x1008ff16,                 spawn,          {.v = mpdprev } },
    { 0,                        XF86XK_AudioNext,           spawn,          {.v = mpdnext } },
    { 0,                        0x1008ff17,                 spawn,          {.v = mpdnext } },
    { 0,                        XF86XK_AudioStop,           spawn,          {.v = mpdstop } },
    { MODKEY|ShiftMask,         XK_b,                       togglebar,      {0} },
    { MODKEY|ShiftMask,         XK_q,                       quit,           {0} },
    { MODKEY,                   XK_Right,                   focusstack,     {.i = +1 } },
    { MODKEY,                   XK_Left,                    focusstack,     {.i = -1 } },
    { MODKEY,                   XK_space,                   zoom,           {0} },
    { MODKEY,                   XK_Tab,                     view,           {0} },
    { MONKEY,                   XK_Tab,                     focusmon,       {0} },
    { MODKEY,                   XK_c,                       killclient,     {0} },
    { MODKEY,                   XK_bracketleft,             setmfact,       {.f = -0.05} },
    { MODKEY,                   XK_bracketright,            setmfact,       {.f = +0.05} },
    { MODKEY,                   XK_equal,                   incnmaster,     {.i = +1 } },
    { MODKEY,                   XK_minus,                   incnmaster,     {.i = -1 } },
    { MODKEY,                   XK_grave,                   togglefloating, {0} },
    { MODKEY,                   XK_t,                       setlayout,      {.v = &layouts[0] } },
    { MODKEY,                   XK_b,                       setlayout,      {.v = &layouts[1] } },
    { MODKEY,                   XK_m,                       setlayout,      {.v = &layouts[2] } },
    { MODKEY,                   XK_n,                       setlayout,      {.v = &layouts[3] } },
    TAGKEYS(                    XK_1,                               0)
    TAGKEYS(                    XK_2,                               1)
    TAGKEYS(                    XK_3,                               2)
    TAGKEYS(                    XK_4,                               3)
    TAGKEYS(                    XK_5,                               4)
    { MODKEY,                   XK_9,                       view,           {.ui = ~0 } },
    { MODKEY|ShiftMask,         XK_a,                       tag,            {.ui = ~0 } },
    { MONKEY,                   XK_Left,                    focusmon,       {.i = -1 } },
    { MONKEY,                   XK_Right,                   focusmon,       {.i = +1 } },
    { MONKEY|ShiftMask,         XK_Left,                    tagmon,         {.i = -1 } },
    { MONKEY|ShiftMask,         XK_Right,                   tagmon,         {.i = +1 } },
};

/* button definitions */
/* click can be ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static Button buttons[] = {
    /* click            event mask  button      function        argument */
    { ClkLtSymbol,      0,          Button1,    setlayout,          {0} },
    { ClkLtSymbol,      0,          Button3,    setlayout,          {.v = &layouts[3]} },
    { ClkStatusText,    0,          Button2,    spawn,              {.v = term } },
    { ClkClientWin,     MODKEY,     Button1,    movemouse,          {0} },
    { ClkClientWin,     MODKEY,     Button2,    togglefloating,     {0} },
    { ClkClientWin,     MODKEY,     Button3,    resizemouse,        {0} },
    { ClkTagBar,        0,          Button1,    view,               {0} },
    { ClkTagBar,        0,          Button3,    toggleview,         {0} },
    { ClkTagBar,        MODKEY,     Button1,    tag,                {0} },
    { ClkTagBar,        MODKEY,     Button3,    toggletag,          {0} },
};
