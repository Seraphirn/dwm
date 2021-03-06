/* See LICENSE file for copyright and license details. */

#define ONLYTERMINAL "gnome-terminal"
#define TERMINAL "gnome-terminal --hide-menubar --window"
#define EDITOR "nvim"

/* appearance */
//static const unsigned int borderpx  = 1;        [> border pixel of windows <]
static const unsigned int borderpx  = 3;        /* border pixel of windows */
static const unsigned int snap      = 32;       /* snap pixel */
static const unsigned int gappih    = 15;       /* [> horiz inner gap between windows <] */
static const unsigned int gappiv    = 10;       /* [> vert inner gap between windows <] */
static const unsigned int gappoh    = 5;        /* [> horiz outer gap between windows and screen edge <] */
static const unsigned int gappov    = 10;       /* [> vert outer gap between windows and screen edge <] */
static const int smartgaps          = 0;        /* [> 1 means no outer gap when there is only one window <] */

static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */

static const double defaultopacity  = 0.75;

static const char *fonts[]          = { "monospace:size=13" };
static const char dmenufont[]       = "monospace:size=13";
static const char col_gray1[]       = "#222222";
static const char col_gray2[]       = "#444444";
static const char col_gray3[]       = "#bbbbbb";
static const char col_gray4[]       = "#eeeeee";
static const char col_cyan[]        = "#005577";
static const unsigned int baralpha = 0xd0;
static const unsigned int borderalpha = OPAQUE;
static const char *colors[][3]      = {
	/*               fg         bg         border   */
	[SchemeNorm] = { col_gray3, col_gray1, col_gray2 },
	[SchemeSel]  = { col_gray4, col_cyan,  col_cyan  },
};
static const unsigned int alphas[][3]      = {
	/*               fg      bg        border     */
	[SchemeNorm] = { OPAQUE, baralpha, borderalpha },
	[SchemeSel]  = { OPAQUE, baralpha, borderalpha },
};

/* tagging */
static const char *tags[] = { "1", "2", "3", "4", "5" };

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class             instance    title       tags mask     isfloating   opacity,         monitor */
  { "Firefox",         NULL,       NULL,       1 << 3,       0,           1.0,             -1 },
  { ONLYTERMINAL,      NULL,       NULL,       0,            0,           defaultopacity,  -1 },
  //{ "Firefox",  NULL,       NULL,       0,       0,           -1 },
};

/* layout(s) */
static const float mfact     = 0.70; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 1;    /* 1 means respect size hints in tiled resizals */

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[]=",      tile },    /* first entry is default */
	{ "><>",      NULL },    /* no layout function means floating behavior */
	{ "[M]",      monocle },
	{ "TTT",      bstack },
	{ "===",      bstackhoriz },
	{ "|M|",      centeredmaster },
	{ ">M>",      centeredfloatingmaster },
};

/* key definitions */
#define MODKEY Mod1Mask
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

#define STATUSBAR "dwmblocks"

/* commands */
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[] = { "dmenu_run", "-m", dmenumon, "-fn", dmenufont, "-nb", col_gray1, "-nf", col_gray3, "-sb", col_cyan, "-sf", col_gray4, NULL };

static Key keys[] = {
	/* modifier                     key        function        argument */
	{ MODKEY,                       XK_p,      spawn,          {.v = dmenucmd } },
	{ MODKEY|ShiftMask,             XK_Return, spawn,          SHCMD(TERMINAL) },
	{ MODKEY|ShiftMask,             XK_e,      spawn,          SHCMD(TERMINAL " -e " EDITOR) },
	{ MODKEY|ShiftMask,             XK_f,      spawn,          SHCMD("firefox") },
	{ MODKEY|ShiftMask,             XK_l,      spawn,          SHCMD("slock") },
	{ MODKEY,                       XK_b,      togglebar,      {0} },
	{ MODKEY,                       XK_j,      focusstack,     {.i = +1 } },
	{ MODKEY,                       XK_k,      focusstack,     {.i = -1 } },
	{ MODKEY,                       XK_i,      incnmaster,     {.i = +1 } },
	{ MODKEY,                       XK_d,      incnmaster,     {.i = -1 } },
	{ MODKEY,                       XK_h,      setmfact,       {.f = -0.05} },
	{ MODKEY,                       XK_l,      setmfact,       {.f = +0.05} },
  { MODKEY|Mod4Mask,              XK_h,      incrgaps,       {.i = +1 } },
  { MODKEY|Mod4Mask,              XK_l,      incrgaps,       {.i = -1 } },
  { MODKEY|Mod4Mask|ShiftMask,    XK_h,      incrogaps,      {.i = +1 } },
  { MODKEY|Mod4Mask|ShiftMask,    XK_l,      incrogaps,      {.i = -1 } },
  { MODKEY|Mod4Mask|ControlMask,  XK_h,      incrigaps,      {.i = +1 } },
  { MODKEY|Mod4Mask|ControlMask,  XK_l,      incrigaps,      {.i = -1 } },
  { MODKEY|Mod4Mask,              XK_0,      togglegaps,     {0} },
  { MODKEY|Mod4Mask|ShiftMask,    XK_0,      defaultgaps,    {0} },
  { MODKEY,                       XK_y,      incrihgaps,     {.i = +1 } },
  { MODKEY,                       XK_o,      incrihgaps,     {.i = -1 } },
  { MODKEY|ControlMask,           XK_y,      incrivgaps,     {.i = +1 } },
  { MODKEY|ControlMask,           XK_o,      incrivgaps,     {.i = -1 } },
  { MODKEY|Mod4Mask,              XK_y,      incrohgaps,     {.i = +1 } },
  { MODKEY|Mod4Mask,              XK_o,      incrohgaps,     {.i = -1 } },
  { MODKEY|ShiftMask,             XK_y,      incrovgaps,     {.i = +1 } },
  { MODKEY|ShiftMask,             XK_o,      incrovgaps,     {.i = -1 } },
	{ MODKEY,                       XK_Return, zoom,           {0} },
	{ MODKEY,                       XK_Tab,    view,           {0} },
	{ MODKEY|ShiftMask,             XK_d,      killclient,     {0} },
	{ MODKEY,                       XK_t,      setlayout,      {.v = &layouts[0]} },
	{ MODKEY,                       XK_f,      setlayout,      {.v = &layouts[1]} }, // floated
	{ MODKEY,                       XK_m,      setlayout,      {.v = &layouts[2]} }, // monocle
	{ MODKEY,                       XK_u,      setlayout,      {.v = &layouts[3]} }, // bstack
	{ MODKEY,                       XK_o,      setlayout,      {.v = &layouts[4]} }, // bstackhoriz
	{ MODKEY,                       XK_c,      setlayout,      {.v = &layouts[5]} }, // centered master
	{ MODKEY,                       XK_v,      setlayout,      {.v = &layouts[6]} }, // centered master floated
	{ MODKEY,                       XK_space,  setlayout,      {0} },
	{ MODKEY|ShiftMask,             XK_space,  togglefloating, {0} },
	{ MODKEY,                       XK_0,      view,           {.ui = ~0 } },
	{ MODKEY|ShiftMask,             XK_0,      tag,            {.ui = ~0 } },
	{ MODKEY,                       XK_comma,  focusmon,       {.i = -1 } },
	{ MODKEY,                       XK_period, focusmon,       {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_comma,  tagmon,         {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_period, tagmon,         {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_KP_Add, changeopacity,  {.f = +0.1}},
	{ MODKEY|ShiftMask,             XK_KP_Subtract, changeopacity, {.f = -0.1}},
	TAGKEYS(                        XK_1,                      0)
	TAGKEYS(                        XK_2,                      1)
	TAGKEYS(                        XK_3,                      2)
	TAGKEYS(                        XK_4,                      3)
	TAGKEYS(                        XK_5,                      4)
	TAGKEYS(                        XK_6,                      5)
	TAGKEYS(                        XK_7,                      6)
	TAGKEYS(                        XK_8,                      7)
	TAGKEYS(                        XK_9,                      8)
	{ MODKEY|ShiftMask,             XK_q,      quit,           {0} },

// chanhe keyboard layour
	{ MODKEY,                       XK_Escape,     spawn,      SHCMD("setxkbmap -query | grep -q 'us' && setxkbmap ru || setxkbmap us; pkill -RTMIN+2 dwmblocks") },
// change monitor brightness
	{ MODKEY|ShiftMask,             XK_j,          spawn,      SHCMD("light -U 10") },
	{ MODKEY|ShiftMask,             XK_k,          spawn,      SHCMD("light -A 10") },
	{ MODKEY|ShiftMask,             XK_n,          spawn,      SHCMD(TERMINAL " -e nvtop") },
	{ MODKEY|ShiftMask,             XK_h,          spawn,      SHCMD(TERMINAL " -e htop") },
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static Button buttons[] = {
	/* click                event mask      button          function        argument */
	{ ClkLtSymbol,          0,              Button1,        setlayout,      {0} },
	{ ClkLtSymbol,          0,              Button3,        setlayout,      {.v = &layouts[2]} },
	{ ClkWinTitle,          0,              Button2,        zoom,           {0} },
	//{ ClkStatusText,        0,              Button2,        spawn,          SHCMD(TERMINAL) },
	{ ClkStatusText,        0,              Button1,        sigstatusbar,   {.i = 1} },
	{ ClkStatusText,        0,              Button2,        sigstatusbar,   {.i = 2} },
	{ ClkStatusText,        0,              Button3,        sigstatusbar,   {.i = 3} },
	{ ClkStatusText,        0,              Button4,        sigstatusbar,   {.i = 4} },
	{ ClkStatusText,        0,              Button5,        sigstatusbar,   {.i = 5} },
	{ ClkStatusText,        MODKEY,         Button1,        sigstatusbar,   {.i = 6} },

	{ ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
	{ ClkClientWin,         MODKEY,         Button2,        togglefloating, {0} },
	{ ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
	{ ClkTagBar,            0,              Button1,        view,           {0} },
	{ ClkTagBar,            0,              Button3,        toggleview,     {0} },
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
};

