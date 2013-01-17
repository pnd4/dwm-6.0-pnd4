/* See LICENSE file for copyright and license details. */
#include <X11/XF86keysym.h>

/* appearance */

/* font */
static const char font[]			= "Inconsolata:style=bold:size=10:antialias=true:hinting=true";

/* colors */
#define NUMCOLORS 4
static const char colors[NUMCOLORS][ColLast][9] = {
	/* border   foreground  background */
	{ "#000000", "#bbbbbb", "#000000" }, // 1 = normal -> grey text, black border on black
	{ "#005577", "#000000", "#005577" }, // 2 = selected -> black text, blue border, on black
	{ "#39ff14", "#dc143c", "#000000" }, // 3 = urgent -> red text, black border, on black
	{ "#000000", "#1b8be0", "#000000" }, // 4 = occupied -> blue text, black border, on black
};
static const unsigned int statusmon = 0; // On which monitor should the status appear
static const unsigned int systrayspacing	= 1;	// Systray spacing
static const unsigned int borderpx				= 2;	// Border pixel of windows
static const unsigned int gappx						= 2;	// Gap pixel between windows
static const unsigned int snap						= 10;	// Snap pixel
//static const float opacity							= 0.75;	// Opacity of the statusbar (max 0.75)
static const Bool showbar									= True;	// False means no bar
static const Bool showsystray							= True;	// False means no systray
static const Bool topbar									= True;	// False means bottom bar

/* layout(s) */
static const float mfact									= 0.60;		// factor of master area size [0.05..0.95]
static const int nmaster 									= 1;		// number of clients in master area
static const Bool resizehints							= False;	// True means respect size hints in tiled resizals

static const Layout layouts[] 						= {
	/* symbol	gaps	arrange */
	{ " =[]",	True,	tile	},
	{ " TTT",	True,	bstack	},
	{ " [M]",	False,	monocle	},
	{ " -F-",	False,	NULL	},
};

/* tagging */
static const Tag tags[] = {
	/* name		layout       mfact	nmaster */
	{ "term",	&layouts[1], -1,		-1 },
	{ "webb",	&layouts[2], -1,		1 },
	{ "irsi",	&layouts[1], -1,		1 },
	{ "mpvi",	&layouts[0], -1,		1 },
	{ "code",	&layouts[1], -1,		2 },
};

/* rules */
static const Rule rules[] = {
	/*WM_CLASS		WM_CLASS	WM_NAME													Monitor '1' is left, '0' is right, '-1' is either */
	/*class			instance	title				tags mask	isfloating	monitor */ 
	{ "Chromium",	"chromium",	NULL,				1 << 1,			False,		 0},
	{ "Navigator","Iceweasel",NULL,				1 << 2,			False,		 0},
	{ NULL,				"weechat",  NULL,				1 << 2,			False,		 1},
	{ NULL,  			"ncmpcpp",	NULL,				1 << 3,			False,		 1},
	{ "MPlayer",	NULL,				NULL,				1 << 3,			False,		 0},
	{ "Gimp",			NULL,				NULL,				1 << 4,			False,		 0},
	{ "Evince",		NULL,				NULL,				1 << 4,			False,		 0},
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
static const char *dmenu[]			= { "dmenu_run", "-p", "(!)", "-fn", font, "-nb", colors[0][ColBG], "-nf", colors[0][ColFG], "-sb", colors[1][ColBG], "-sf", colors[1][ColFG], NULL };
static const char *term[]				= { "urxvtc", NULL };
static const char *browser[]		= { "chromium", NULL };
static const char *files[]			= { "spacefm", NULL };
static const char *music[]			= { "urxvtc", "-name", "ncmpcpp", "-e", "ncmpcpp", NULL };
static const char *weechat[]		= { "urxvtc", "-name", "weechat", "-e", "weechat-curses", NULL };
static const char *scrot[]			= { "xfce4-screenshooter", NULL };
//static const char *lock[]			= { "slock", NULL };
//static const char *halt[]			= { "dmenu_shutdown", NULL };
static const char *volup[]			= { "amixer", "-q", "sset", "Master", "5%+", "unmute", NULL };
static const char *voldown[]		= { "amixer", "-q", "sset", "Master", "5%-", "unmute", NULL };
static const char *volmute[]		= { "amixer", "-q", "sset", "Master", "toggle", NULL };
static const char *mpdplay[]		= { "ncmpcpp", "toggle", NULL };
static const char *mpdnext[]		= { "ncmpcpp", "next", NULL };
static const char *mpdprev[]		= { "ncmpcpp", "prev", NULL };
static const char *mpdstop[]		= { "ncmpcpp", "stop", NULL };

/* key bindings */
static Key keys[] = {
	/* modifier					key				 			function		argument */
	{ MODKEY,								XK_p,								spawn,				{.v = dmenu } },
	{ MODKEY,								XK_e,								spawn,				{.v = files } },
	{ MODKEY,								XK_Return,					spawn,				{.v = term } },
	{ MODKEY,								XK_F2,							spawn,				{.v = browser } },
	{ MODKEY,								XK_F3,							spawn,				{.v = weechat } },
	{ MODKEY,								XK_F4,							spawn,				{.v = music } },
	{ MODKEY,								XK_Print,						spawn,				{.v = scrot } },
	{ 0,						XF86XK_AudioRaiseVolume,		spawn,				{.v = volup } },
	{ 0,						XF86XK_AudioLowerVolume,		spawn,				{.v = voldown } },
	{ 0,						XF86XK_AudioMute,						spawn,				{.v = volmute } },
	{ 0,						XF86XK_AudioPlay,						spawn,				{.v = mpdplay } },
	{ 0,						XF86XK_AudioNext,						spawn,				{.v = mpdnext } },
	{ 0,						XF86XK_AudioPrev,						spawn,				{.v = mpdprev } },
	{ 0,						XF86XK_AudioStop,						spawn,				{.v = mpdstop } },
	{ MODKEY|ShiftMask,			XK_b,								togglebar,		{0} },
	{ MODKEY|ShiftMask,			XK_q,								quit,					{0} },
	{ MODKEY,								XK_Right,						focusstack,		{.i = +1 } },
	{ MODKEY,								XK_Left,						focusstack,		{.i = -1 } },
	{ MODKEY,								XK_F11,							zoom,					{0} },
	{ MODKEY,								XK_Tab,							view,					{0} },
	{ MODKEY,								XK_c,								killclient,		{0} },
	{ MODKEY,								XK_bracketleft,			setmfact,			{.f = -0.05} },
	{ MODKEY,								XK_bracketright,		setmfact,			{.f = +0.05} },
	{ MODKEY,								XK_equal,						incnmaster,		{.i = +1 } },
	{ MODKEY,								XK_minus,						incnmaster,		{.i = -1 } },
	{ MODKEY,								XK_space,						setlayout,		{0} },	// toggle last layout
	{ MODKEY,								XK_f,								togglefloating,{0} },
	{ MODKEY,								XK_t,								setlayout,		{.v = &layouts[0] } },
	{ MODKEY,								XK_b,								setlayout,		{.v = &layouts[1] } },
	{ MODKEY,								XK_m,								setlayout,		{.v = &layouts[2] } },
	{ MODKEY,								XK_n,								setlayout,		{.v = &layouts[3] } },
	TAGKEYS(								XK_1,								0)
	TAGKEYS(								XK_2,								1)
	TAGKEYS(								XK_3,								2)
	TAGKEYS(								XK_4,								3)
	TAGKEYS(								XK_5,								4)
	{ MODKEY,								XK_o,								view,					{.ui = ~0 } },
	{ MODKEY|ShiftMask,			XK_a,								tag,					{.ui = ~0 } },
	{ MONKEY,								XK_Left,						focusmon,			{.i = -1 } },
	{ MONKEY,								XK_Right,						focusmon,			{.i = +1 } },
	{ MONKEY|ShiftMask,			XK_Left,						tagmon,				{.i = -1 } },
	{ MONKEY|ShiftMask,			XK_Right,						tagmon,				{.i = +1 } },
};

/* button definitions */
/* click can be ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static Button buttons[] = {
	/* click			event mask	button		function		argument */
	{ ClkLtSymbol,		0,			Button1,	setlayout,			{0} },
	{ ClkLtSymbol,		0,			Button3,	setlayout,			{.v = &layouts[4]} },
	{ ClkStatusText,	0,			Button2,	spawn,					{.v = term } },
	{ ClkClientWin,		MODKEY,	Button1,	movemouse,			{0} },
	{ ClkClientWin,		MODKEY,	Button2,	togglefloating,	{0} },
	{ ClkClientWin,		MODKEY,	Button3,	resizemouse,		{0} },
	{ ClkTagBar,			0,			Button1,	view,						{0} },
	{ ClkTagBar,			0,			Button3,	toggleview,			{0} },
	{ ClkTagBar,			MODKEY,	Button1,	tag,						{0} },
	{ ClkTagBar,			MODKEY, Button3,	toggletag,			{0} },
};
