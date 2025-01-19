/* See LICENSE file for copyright and license details. */
#define TERMINAL "st"
#define SESSION_FILE "/tmp/dwm-session"

/* appearance */
static const unsigned int borderpx  = 1;        /* border pixel of windows */
static const unsigned int snap      = 2;       /* snap pixel */
static const unsigned int gappih    = 0;       /* horiz inner gap between windows */
static const unsigned int gappiv    = 0;       /* vert inner gap between windows */
static const unsigned int gappoh    = 0;       /* horiz outer gap between windows and screen edge */
static const unsigned int gappov    = 0;       /* vert outer gap between windows and screen edge */
static       int smartgaps          = 0;        /* 1 means no outer gap when there is only one window */
static const int swallowfloating    = 0;        /* 1 means swallow floating windows by default */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 0;        /* 0 means bottom bar */
static const char *fonts[]          = { "monospace:size=12", "JoyPixels:style=Regular:pixelsize=14:antialias=true:autohint=true"  };
static const char dmenufont[]       = "monospace:style=SemiBold:pixelsize=14";

static const char col_gray1[]       = "#222222";
static const char col_gray2[]       = "#444444";
static const char col_gray3[]       = "#bbbbbb";
static const char col_gray4[]       = "#eeeeee";
static const char col_red[]         = "#770000";
static const char col_cyan[]         = "#005577";
//static const char col_cyan[]         = "#5294E2";
static const char *colors[][3]      = {
	/*               fg         bg         border   */
	[SchemeNorm] = { col_gray3, col_gray1, col_gray2 },
	[SchemeSel]  = { col_gray4, col_cyan,  col_cyan },
};

typedef struct {
	const char *name;
	const void *cmd;
} Sp;
const char *spcmd1[] = {"st", "-n", "spterm", "-g", "90x25", "-e", "pulsemixer", NULL };
const char *spcmd2[] = {"st", "-n", "spfm", "-g", "60x20", "-e", "ncmpcpp", NULL };
// const char *spcmd3[] = {TERMINAL, "-n", "spterm", "-f", "monospace:si-g", "50x20", "-e", "bc", "-lq", NULL };
const char *spcmd3[] = {"st", "-n", "spt", "-g", "65x20", NULL };
static Sp scratchpads[] = {
	/* name          cmd  */
	{"spterm",      spcmd1},
	{"spranger",    spcmd2},
	// {"spcalc",      spcmd3},
	{"spt",         spcmd3},
};

/* tagging */
static const char *tags[] = { "1", "2", "3", "4", "5", "6", "7", "8", "9"};
static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class     instance  title             tags mask  isfloating  isterminal  noswallow  monitor */
    { "firefox", NULL,     NULL,             0, 	    0,       	0,			 0,	       -1 },
	{ "St",      NULL,     NULL,             0,         0,          1,           0,        -1 },
	{ "st",      NULL,     NULL,             0,         0,          1,           0,        -1 },
	{ NULL,      NULL,     "Event Tester",   0,         0,          0,           1,        -1 }, /* xev */
	{ NULL,	   "spterm",	NULL,		SPTAG(0),		1,			 -1 },
	{ NULL,	   "spfm",  	NULL,		SPTAG(1),		1,			 -1 },
	// { NULL,	   "spterm",	NULL,		SPTAG(2),		1,			 -1 },
	{ NULL,	   "spt",   	NULL,		SPTAG(2),		1,			 -1 },
};

/* layout(s) */
static const float mfact     = 0.55; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 0;    /* 1 means respect size hints in tiled resizals */
static const int lockfullscreen = 1; /* 1 will force focus on the fullscreen window */

#define FORCE_VSPLIT 1  /* nrowgrid layout: force two clients to always split vertically */
#include "vanitygaps.c"

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[]=",      tile },    /* first entry is default */
	{ "><>",      NULL },    /* no layout function means floating behavior */
	{ "[M]",      monocle },
	{ "[@]",      spiral },
	{ "[\\]",     dwindle },
	{ "H[]",      deck },
	{ "TTT",      bstack },
	{ "===",      bstackhoriz },
	{ "HHH",      grid },
	{ "###",      nrowgrid },
	{ "---",      horizgrid },
	{ ":::",      gaplessgrid },
	{ "|M|",      centeredmaster },
	{ ">M>",      centeredfloatingmaster },
	{ "><>",      NULL },    /* no layout function means floating behavior */
	{ NULL,       NULL },
};

/* key definitions */
#define MODKEY Mod4Mask
#define TAGKEYS(KEY,TAG) \
{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

#include <X11/XF86keysym.h>
/* commands */
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[] = { "dmenu_run", NULL };
static const char *termcmd[]  = { "st", NULL };

static const Key keys[] = {
	/* modifier                     key        function        argument */
	// { MODKEY,                       XK_d,      spawn,          {.v = dmenucmd } },
	{ MODKEY,                       XK_d,      spawn,          SHCMD("rofi -show drun") },
	{ MODKEY,						XK_Return, spawn,          {.v = termcmd } },
	{ MODKEY|ShiftMask,             XK_b,      togglebar,      {0} },
	{ MODKEY,                       XK_j,      focusstack,     {.i = +1 } },
	{ MODKEY,                       XK_k,      focusstack,     {.i = -1 } },
	{ MODKEY,                       XK_i,      incnmaster,     {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_i,      incnmaster,     {.i = -1 } },
	{ MODKEY,                       XK_h,      setmfact,       {.f = -0.03} },
	{ MODKEY,                       XK_l,      setmfact,       {.f = +0.03} },
	{ MODKEY|ShiftMask,             XK_h,      setcfact,       {.f = +0.20} },
	{ MODKEY|ShiftMask,             XK_l,      setcfact,       {.f = -0.20} },
	{ MODKEY|ShiftMask,             XK_o,      setcfact,       {.f =  0.00} },
	{ MODKEY,                       XK_space,  zoom,           {0} },
	{ MODKEY,                       XK_Tab,    view,           {0} },
	{ MODKEY,						XK_q,      killclient,     {0} },
	{ MODKEY,                       XK_t,      setlayout,      {.v = &layouts[0]} },
	{ MODKEY|ShiftMask,				XK_f,      setlayout,      {.v = &layouts[1]} },
	{ MODKEY|ShiftMask,             XK_t,      setlayout,      {.v = &layouts[2]} },
	{ MODKEY|ShiftMask,             XK_Return,  setlayout,      {0} },
	{ MODKEY|ShiftMask,             XK_space,  togglefloating, {0} },
	{ MODKEY,						XK_f,      togglefullscr,  {0} },
	{ MODKEY,                       XK_0,      view,           {.ui = ~0 } },
	{ MODKEY|ShiftMask,             XK_0,      tag,            {.ui = ~0 } },
	{ MODKEY,                       XK_comma,  focusmon,       {.i = -1 } },
	{ MODKEY,                       XK_period, focusmon,       {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_comma,  tagmon,         {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_period, tagmon,         {.i = +1 } },
	{ MODKEY,						XK_o,  	   togglescratch,  {.ui = 0 } },
	{ MODKEY,						XK_m,	   togglescratch,  {.ui = 1 } },
	{ MODKEY|ShiftMask,				XK_m,	   togglescratch,  {.ui = 2 } },
	TAGKEYS(                        XK_1,                      0)
		TAGKEYS(                        XK_2,                      1)
		TAGKEYS(                        XK_3,                      2)
		TAGKEYS(                        XK_4,                      3)
		TAGKEYS(                        XK_5,                      4)
		TAGKEYS(                        XK_6,                      5)
		TAGKEYS(                        XK_7,                      6)
		TAGKEYS(                        XK_8,                      7)
		TAGKEYS(                        XK_9,                      8)
		{ MODKEY|ControlMask,			XK_b, 		spawn, SHCMD("bookmarkthis") },

		{ MODKEY,						XK_c,		spawn, SHCMD("emacsclient -c") },
		{ MODKEY,						XK_Delete,	spawn, SHCMD("dm-kill -r")},
		{ MODKEY,						XK_r, 		spawn, SHCMD("dm-dox")},
		{ MODKEY|ShiftMask,				XK_x, 		spawn, SHCMD("dm-shutdown") },
		{ MODKEY,						XK_End,  	spawn, SHCMD("maimpick")},
		{ MODKEY,						XK_Insert, 	spawn, SHCMD("dm-bm") },
		{ MODKEY,						XK_semicolon,   spawn, SHCMD("dm-web") },
		{ MODKEY|ShiftMask,				XK_e, 		spawn, SHCMD("dm-emoji") },
		{ MODKEY|ShiftMask,				XK_n, spawn, SHCMD(TERMINAL "-e newsboat") },
		{ MODKEY,						XK_b, spawn, SHCMD("brave") },
		{ MODKEY,				        XK_e, 		spawn, SHCMD("pcmanfm") },

		{ MODKEY,   XK_minus, spawn, 
			SHCMD("wpctl set-volume @DEFAULT_AUDIO_SINK@ 5%-; kill -44 $(pidof dwmblocks)") },
		{ MODKEY|ShiftMask, XK_minus, spawn, 
			SHCMD("wpctl set-volume @DEFAULT_AUDIO_SINK@ 15%-; kill -44 $(pidof dwmblocks)") },
		{ MODKEY,    XK_equal, spawn, 
			SHCMD("wpctl set-volume @DEFAULT_AUDIO_SINK@ 5%+; kill -44 $(pidof dwmblocks)") },
		{ MODKEY|ShiftMask, XK_equal, spawn, 
			SHCMD("wpctl set-volume @DEFAULT_AUDIO_SINK@ 15%+; kill -44 $(pidof dwmblocks)") },

		{ MODKEY,				XK_p,	spawn,		{.v = (const char*[]){ "mpc", "toggle", NULL } } },
		{ MODKEY,		XK_bracketleft,	 spawn,	{.v = (const char*[]){ "mpc", "seek", "-10", NULL } } },
		{ MODKEY|ShiftMask,	XK_bracketleft,	 spawn,	{.v = (const char*[]){ "mpc", "seek", "-60", NULL } } },
		{ MODKEY,		XK_bracketright, spawn,	{.v = (const char*[]){ "mpc", "seek", "+10", NULL } } },
		{ MODKEY|ShiftMask,	XK_bracketright, spawn,	{.v = (const char*[]){ "mpc", "seek", "+60", NULL } } },

		{ 0, XF86XK_AudioRaiseVolume, spawn, 
			SHCMD("wpctl set-volume @DEFAULT_AUDIO_SINK@ 3%+; kill -44 $(pidof dwmblocks)") },
		{ 0, XF86XK_AudioMute, spawn, 
			SHCMD("wpctl set-volume @DEFAULT_AUDIO_SINK@ 0%") },
		{ 0, XF86XK_AudioLowerVolume, spawn, 
			SHCMD("wpctl set-volume @DEFAULT_AUDIO_SINK@ 3%-; kill -44 $(pidof dwmblocks)") },
		{ 0, XF86XK_AudioMute,			spawn,	SHCMD("wpctl set-mute @DEFAULT_AUDIO_SINK@ toggle") },
		{ 0, XF86XK_AudioPlay,			spawn,	{.v = (const char*[]){ "mpc", "toggle", NULL } } },
		{ 0, XF86XK_AudioPrev,			spawn,	{.v = (const char*[]){ "mpc", "prev", NULL } } },
		{ 0, XF86XK_AudioNext,			spawn,	{.v = (const char*[]){ "mpc",  "next", NULL } } },
		{ 0, XF86XK_AudioMedia,			spawn,	{.v = (const char*[]){ TERMINAL, "-e", "ncmpcpp", NULL } } },
		{ 0, XF86XK_MonBrightnessUp,	spawn,	{.v = (const char*[]){ "xbacklight", "-inc", "5", NULL } } },
		{ 0, XF86XK_MonBrightnessDown,	spawn,	{.v = (const char*[]){ "xbacklight", "-dec", "5", NULL } } },

		{ MODKEY,						XK_F2,	   spawn,		SHCMD("vpn -r") },
		{ MODKEY,						XK_F11,	   spawn,		SHCMD("webcam") },
		{ MODKEY|ShiftMask,             XK_Delete,  quit,           {0} },
		{ MODKEY|ShiftMask,				XK_r,       quit,           {1} }, 

		{ MODKEY|Mod1Mask,              XK_u,      incrgaps,       {.i = +1 } },
		{ MODKEY|Mod1Mask|ShiftMask,    XK_u,      incrgaps,       {.i = -1 } },
		{ MODKEY|Mod1Mask,              XK_i,      incrigaps,      {.i = +1 } },
		{ MODKEY|Mod1Mask|ShiftMask,    XK_i,      incrigaps,      {.i = -1 } },
		{ MODKEY|Mod1Mask,              XK_o,      incrogaps,      {.i = +1 } },
		{ MODKEY|Mod1Mask|ShiftMask,    XK_o,      incrogaps,      {.i = -1 } },
		{ MODKEY|Mod1Mask,              XK_6,      incrihgaps,     {.i = +1 } },
		{ MODKEY|Mod1Mask|ShiftMask,    XK_6,      incrihgaps,     {.i = -1 } },
		{ MODKEY|Mod1Mask,              XK_7,      incrivgaps,     {.i = +1 } },
		{ MODKEY|Mod1Mask|ShiftMask,    XK_7,      incrivgaps,     {.i = -1 } },
		{ MODKEY|Mod1Mask,              XK_8,      incrohgaps,     {.i = +1 } },
		{ MODKEY|Mod1Mask|ShiftMask,    XK_8,      incrohgaps,     {.i = -1 } },
		{ MODKEY|Mod1Mask,              XK_9,      incrovgaps,     {.i = +1 } },
		{ MODKEY|Mod1Mask|ShiftMask,    XK_9,      incrovgaps,     {.i = -1 } },
		{ MODKEY|Mod1Mask,              XK_0,      togglegaps,     {0} },
		{ MODKEY|Mod1Mask|ShiftMask,    XK_0,      defaultgaps,    {0} },
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static const Button buttons[] = {
	/* click                event mask      button          function        argument */
	{ ClkLtSymbol,          0,              Button1,        setlayout,      {0} },
	{ ClkLtSymbol,          0,              Button3,        setlayout,      {.v = &layouts[2]} },
	{ ClkWinTitle,          0,              Button2,        zoom,           {0} },
	{ ClkStatusText,        0,              Button1,        sigdwmblocks,   {.i = 1} },
	{ ClkStatusText,        0,              Button2,        sigdwmblocks,   {.i = 2} },
	{ ClkStatusText,        0,              Button3,        sigdwmblocks,   {.i = 3} },
	{ ClkStatusText,        0,              Button4,        sigdwmblocks,   {.i = 4} },
	{ ClkStatusText,        0,              Button5,        sigdwmblocks,   {.i = 5} },
	{ ClkStatusText,        ShiftMask,      Button1,        sigdwmblocks,   {.i = 6} },
	{ ClkClientWin,         MODKEY,         Button1,        moveorplace,    {.i = 0} },
	{ ClkClientWin,         MODKEY,         Button2,        togglefloating, {0} },
	{ ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
	{ ClkTagBar,            0,              Button1,        view,           {0} },
	{ ClkTagBar,            0,              Button3,        toggleview,     {0} },
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
};

