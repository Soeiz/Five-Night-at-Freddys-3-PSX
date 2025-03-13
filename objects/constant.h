#include <sys/types.h>
#include <sys/file.h>
#include <stdio.h>
#include <stdbool.h>

#include <kernel.h>
#include <libgte.h>
#include <libetc.h>
#include <libgpu.h>
#include <libsnd.h>
#include <libspu.h>
#include <rand.h>
#include <libapi.h>
#include <string.h>
#include <libmcrd.h>
#include <libpress.h>

#include <libcd.h>
#include <malloc.h>

CVECTOR fntColorBG = { 0, 0, 0 };
CVECTOR fntColor = { 255, 255, 255 };

#define FONTX   992
#define FONTY   0

#define TRUECOL 1               // 0 : 16bpp, 1: 24bpp

#define VMODE 0                 // Video Mode : 0 : NTSC, 1: PAL
#define SCREENXRES 320          // Screen width
#define SCREENYRES 240          // Screen height
#define CENTERX SCREENXRES/2    // Center of screen on x 
#define CENTERY SCREENYRES/2    // Center of screen on y

#define MARGINX 0                // margins for text display
#define MARGINY 40

#define FONTSIZE 25 * 7           // Text Field Height
DISPENV disp[2];                 // Double buffered DISPENV and DRAWENV
DRAWENV draw[2];
short db = 0;                      // index of which buffer is used, values 0, 1

// Number of VAG files to load
#define VAG_NBR 24
#define MALLOC_MAX VAG_NBR            // Max number of time we can call SpuMalloc

// convert Little endian to Big endian
#define SWAP_ENDIAN32(x) (((x)>>24) | (((x)>>8) & 0xFF00) | (((x)<<8) & 0x00FF0000) | ((x)<<24))
// Memory management table ; allow MALLOC_MAX calls to SpuMalloc() - libref47.pdf p.1044

char spu_malloc_rec[SPU_MALLOC_RECSIZ * (MALLOC_MAX + 1)]; 

// Custom struct to handle VAG files
typedef struct VAGsound {
    u_char * VAGfile;        // Pointer to VAG data address
    u_long spu_channel;      // SPU voice to playback to
    u_long spu_address;      // SPU address for memory freeing spu mem
} VAGsound;

// VAG header struct (see fileformat47.pdf, p.209)
typedef struct VAGhdr {                // All the values in this header must be big endian
        char id[4];                    // VAGp         4 bytes -> 1 char * 4
        unsigned int version;          // 4 bytes
        unsigned int reserved;         // 4 bytes
        unsigned int dataSize;         // (in bytes) 4 bytes
        unsigned int samplingFrequency;// 4 bytes
        char  reserved2[12];           // 12 bytes -> 1 char * 12
        char  name[16];                // 16 bytes -> 1 char * 16
        // Waveform data after that
} VAGhdr;

// SPU settings
SpuCommonAttr commonAttributes;          // structure for changing common voice attributes
SpuVoiceAttr  voiceAttributes ;          // structure for changing individual voice attributes   

extern void display(void);

int RAN;
int Ran(int max)
{
    RAN = (rand()%max);
    if (RAN == 0) {RAN++;}
    return 0;
}

int RAN2;
int Ran2(int max)
{
    RAN2 = (rand()%max);
    if (RAN2 == 0) {RAN2++;}
    return 0;
}

//X1 and Y1 are the positions, X2 and Y2 is the size of the rect.
void clearVRAMgeneral(int x1, int y1, int x2, int y2) {
    RECT rectTL;

    setRECT(&rectTL, x1, y1, x2, y2);  
    ClearImage2(&rectTL, 0, 0, 0);
    DrawSync(0);
}

void clearVRAM(void)
{
    RECT rectTL;
    setRECT(&rectTL, 0, 0, 960, 256); //Clear all but the font
    ClearImage2(&rectTL, 0, 0, 0);
    setRECT(&rectTL, 0, 256, 1048, 256);
    ClearImage2(&rectTL, 0, 0, 0);
    DrawSync(0);
}

int currentmenu[2] = {0,0};

//First index, 1 Is main menu, 2 is extra menu, 3 is custom night menu.
/*
    second index (submenu) :

    submenu in extra menu :

    1 : unlocks menu
    2 : Info screen

    submenu in custom night menu :

    1 : AI set menu
    2 : timer menu
    3 : Advanced menu
*/

int initstuff = 0;

int pad = 0;    

int frames = 500;

int menuscreeninit = 0;
int menu = 0;
bool helpwantedposter = false;
int maincustomnightmenu = 0;
int AISetmenu = 0;
int timermenu = 0;
int freddyfacechanged = 0;

bool consolemode = false;
char consolemodestr[3] = "OFF";

int framesforwarning = 0;
bool FFWwarning = false;

int presetselector = 1;
int presetselectorlimiterright = 0;
int presetselectorlimiterleft = 0;
char presetselectorstr[20];
int animatronicategorie = 1;

int linesdeathframes = 0;
bool linesdeathactive = false;

bool freeze = false;
int selectionfreeze = 1;
int menuselectionmaxfreeze = 0;

bool linesactive = false;
int linesframes = 0;
int menuselection = 2;
int menuselectionmax = 3;
int musicframes = 4431;
int limitermenuL = 0;
int limitermenuR = 0;
int springtrapmenuframe = 0;
int springtrapfreakytimes = 0;
int ranmenu = 128;
int activatedmenudebug = 0;
int printnumber = 1;
int FrameCounterlimiterup = 0;
int FrameCounterlimiterdown = 0;
int FrameCounterlimit = 0;
int convertion = 60;
int extramenu = 0;
int infoscreen = 0;
int seedrandom = 0;
int unlimitedpower = 0;
char unlimitedpowerstr[] = "OFF";
char radarstr[] = "OFF";
char fastnightsstr[] = "OFF";
int radar = 0;
int unlockssubmenu = 0;
int limiterunlimitedpower = 0;
int limiterfastnights = 0;
int limiterradar = 0;
bool fastnights = false;
bool cheating = false;
int savemenu = 0;
bool menufadingout = false;

int twoplayermode = 0;
char twoplayermodestr[] = "OFF";
int twoplayermodelimiter = 0;

int loadingframe = 0;
int goldenfreddied = 0;
int goldenfreddiedframes = 0;
int Glitch = 0;

int limiterpadright = 0;
int limiterpadleft = 0;
int limiterpaddown = 0;
int limiterpadup = 0;
int limiterbuttondown = 0;
int limiterstart = 0;

int onesecondvar = 60; //always one second for some random things (vents)

int nolongerincam = 0;

int alarmcooldown = 0;
int officefadingout = -1;
int officefadingoutminus = 0;
int oneway = 0; //NO WAY

int camlimiter = 0;
int limiterbop = 0;

int inactiveframes = 0; //Used to know how long you've not been using camera/maintenance panel
bool camera = false;
bool isonvents = false;
int cooldowncamera = 0;
int curcam[2] = {0,1};
int limitercameraD = 0;
int limitercameraU = 0;
int limitercameraR = 0;
int limitercameraL = 0;
bool springtraponcam = false;
bool abletoplaysound = true;
int camerahealth = 10;
int camerahealthtimer = 720;
int audiodevicehealth = 10;
int BBsoundcooldown = 0;
bool audiolureworked = false;
int timeruntillured = -1;
int audiolureloc[2] = {0,1};
int limitertoggle = 0;
int spritecamerago = false;
int spritecamera = 0;
int spritesheetcamera = 4;
int camerastatic = 100;
bool camerasystemfailure = false;
bool camerastate = false;
bool ventilationfailure = false;
int frameventilbroke = 0;
int ventilhealth = 10;
int ventilhealthtimer = 720;
int ventilhealthtimerconst = 720;
bool blackout = false;

bool ballonboydeactivated = false;
bool ballonboyonscreen = false;
bool ballonboyqueued = false;
int ballonboyseen = 51;
int ballonboyAI = 4;
int ballonboyframes = 1200;

bool mangledeactivated = false;
bool mangleonscreen = false;
bool manglequeued = false;
int mangleseen = 51;
int mangleAI = 4;
int mangleframes = 1200;
int mangleframesdisappear = 780;

bool puppetdeactivated = false;
bool puppetonscreen = false;
bool puppetqueued = false;
int puppetseen = 51;
int puppetAI = 5;
int puppetframes = 1200;
int puppetframesdisappear = 1000;

bool chicadeactivated = false;
bool chicaonscreen = false;
bool ischicaofficehere = false;
bool chicaqueued = false;
int chicaseen = 54;
int chicaAI = 5;
int chicaframes = 1200;

bool ispuppetofficehere = false; 
int puppetleaving = 0;
bool isballonboyofficehere = false;
bool ismangleofficehere = false;

bool jumpscared = false;
bool springtrapskip = false; //When jumpscared, singtip will force move ONCE

bool isfreddyofficehere = false;
bool freddygotu = false;
int freddyAI = 4;
int freddyframes = 3600;
int freddyprogressionframe = 2600; 
int freddytimeseen = 360;
bool freddydeactivated = false;
int UVfreddy = 0;

int isfoxyofficehere = false;
bool foxyscreamer = false;
int foxyAI = 4;
bool foxyseen = false;

bool heavybreathing = false;

bool maintenancepanel = false;
int maintenancepanelselection = 0;
int reloadingframe = 0;
int timerepairing = 0;
bool currentlyrepairing = false;
int limiterpanel = 0;
int spritemaintenancepanelgo = false;
int spritemaintenancepanel = 0;
int spritesheetpanel = 4;

int blinkicon = 0;

int weirdnight = 0;
int fadeoffice = 128;
int fadeofficenights = 128;
int fadeGF = 128;
int inorout = 0;
int oldnight = 0;
bool donewithaggressive = false;
bool night5done, night6done = false;

bool isingame = false;
bool returnedingame = false;
int nospringtrap = 0;
int returnframes = 0;
int returnbasevolume = 0x1800;

int noisefootstep = 0;
int framenoisefootstep = 0;
int noisefootstepanimatronic = 0;

int noisefootstepF = 0;
int framenoisefootstepF = 0;

int fivesecondframe = 300;
int demisecondframe = 30;
int ambianceframe = 300;

int debugambiancesound = 0;

int mascottune = 0;
int musicmascottune = 1248;

bool lockleft = false; //Used for forcing you to move.

bool springtrapinactive = false; //For recording purpose
int springtrapAI = 0;
int springtraplocframe = 360;
int springtraplocation[2] = {1,0};
int OLDspringtraplocation[2] = {0,1};
int springtrapblockcam = 60;
int movecounter = 0;
bool isagressive = false;
int Springstotalturns = 0;
int SpringsAction = 0;
int SpringsAction2 = 0;
int fiveSeconds = 5;
bool isontherightside = false; //If he's on the right side or not, for jumpscare
bool comingfromvent = false;
bool retainspringtrapleaving = false; //Used when player is looking at him when doing a succesful move. Will not move until camera opened up
int isspringtrapleavingframes = 0; //Since it DOESN'T WANT to run, I'll set a timer
int imageindexspringtraprun = 0;
bool isspringtrapvents = false;
bool currentlysealing = false;
int ventlocked = 0; //0 is when nothing is locked, if it is the var will match the cam number
int timertolock = 180; //3 sec
bool isspringtrapinspecialstage1, isspringtrapinspecialstage2, springtrapinviewrange, springtrapsooninviewrange = false;
bool isspringtraprunningtoyou = false;
bool springtrapbehindcamera = false;
int springtraprunningindex = -1;
bool springtrapnoise = false; //Pro tip : Spongetoy make noises when moving.
int stage = 0;
bool springtraprunningoffice = false;
bool springtraphide = false;
bool springtraphidegone = false;
int springtraphideframe = 0;

int alarmstate = 0; //For the weird sound "alarm" thing


int sync= 0;

bool enablephoneguy = false;
char enablephoneguystr[] = "ON";
int limiterphoneguy = 0;
int phoneguytalking = 0;
int phoneguytalkingconst;
bool mutedcall = false;

bool noerrors = false;
char noerrorsstr[] = "OFF";

bool aggressive = false;
char aggressivestr[] = "OFF";

int isalreadydead = 0;
int isalreadydeadlow = 0;
int framedeadpossi = 60;
int lastsecondsframes = 1800;
int screamersetsound = 0;
int screamerframes = 47;
bool dead = false;
int spriteframes = 4;
int spriteframesconst = 4;
int spritesheet = 0;

bool nightwon = false;
int fivetosixamframes = 0;
int nextnightframes = 0;
int staticframessheet = 0;
int flashingAMframes = 0;

int speedoffice = 3;
int fanframes = 0;

int staticframes = 300;

int ventbanging = 0;
int ventbangingframes = 0;

int customnightactivated = 0;

int debugging = 0; //mostly for testing out animatronics on hallway and vents (with debugging their loc will not reset)

int doescharlevelup = 0;
char doescharlevelupstr[3] = "Off";

#define OTLEN 8                    // Ordering Table Length 

u_long ot[2][OTLEN];               // double ordering table of length 8 * 32 = 256 bits / 32 bytes

char primbuff[2][32768];     // double primitive buffer of length 32768 * 8 =  262.144 bits / 32,768 Kbytes

char *nextpri = primbuff[0];       // pointer to the next primitive in primbuff. Initially, points to the first bit of primbuff[0]

#define COUNT_OF(x) (sizeof(x) / sizeof(0[x]))

void consoleFunc(void) {
    maintenancepanel = !maintenancepanel; 
    spritemaintenancepanelgo = true;
    if (maintenancepanel) {
        SpuSetKey(SPU_ON, SPU_19CH);
    } else {
        SpuSetKey(SPU_ON, SPU_20CH);
    }
}
void CameraFunc(bool silent) {
    if (currentlysealing) {return;}
    if (camlimiter == 0) {
        if (cooldowncamera == 0) {
            camera = !camera;
            if (camera) {
                if (!camerastate) {spritecamerago = true;}
                if (!silent) {
                  SpuSetKey(SPU_OFF, SPU_01CH);
                  SpuSetKey(SPU_ON, SPU_07CH);
                }
                SpuSetKey(SPU_OFF, SPU_00CH);
            }
            if (!camera) {
                if (!silent) {
                  SpuSetKey(SPU_OFF, SPU_07CH);
                  SpuSetKey(SPU_ON, SPU_01CH);
                }
                SpuSetKey(SPU_OFF, SPU_21CH);
                if (ballonboyseen > 0) {ballonboyqueued = false;}
                if (chicaseen > 0) {chicaqueued = false;}
                if (puppetseen > 0) {puppetqueued = false;}
                if (mangleseen > 0) {manglequeued = false;}
            }
            cooldowncamera = 15;
        }
    }
    camlimiter = 1;
}

void init(void)
{   
    ResetCallback();
    ResetGraph(0);

    // Initialize and setup the GTE
    
    InitGeom();
    SetGeomOffset(CENTERX,CENTERY);
    SetGeomScreen(CENTERX);

    SetDefDispEnv(&disp[0], 0, 0         , SCREENXRES, SCREENYRES);     // Set display area for both &disp[0] and &disp[1]
    SetDefDispEnv(&disp[1], 0, SCREENYRES, SCREENXRES, SCREENYRES);     // &disp[0] is on top  of &disp[1]
    SetDefDrawEnv(&draw[0], 0, SCREENYRES, SCREENXRES, SCREENYRES);     // Set draw for both &draw[0] and &draw[1]
    SetDefDrawEnv(&draw[1], 0, 0         , SCREENXRES, SCREENYRES);     // &draw[0] is below &draw[1]
    // Set video mode
    if (VMODE){ SetVideoMode(MODE_PAL); disp[0].disp.y = disp[1].disp.y = 8;}
    SetDispMask(1);                 // Display on screen    
    setRGB0(&draw[0], 0, 0, 0); // set color for first draw area
    setRGB0(&draw[1], 0, 0, 0); // set color for second draw area
    draw[0].isbg = 1;               // set mask for draw areas. 1 means repainting the area with the RGB color each frame 
    draw[1].isbg = 1;
    PutDispEnv(&disp[db]);          // set the disp and draw environnments
    PutDrawEnv(&draw[db]);
    //FntLoad(FONTX, FONTY);                // Load font to vram at FONTX,FONTY
    //FntOpen(100, 100, 48, 20, 0, 12 );    // FntOpen(x, y, width, height,  black_bg, max. nbr. chars)
    //FntColor(fntColor, fntColorBG);
    FntLoad(960, 0);
    FntOpen(MARGINX, SCREENYRES - MARGINY - FONTSIZE, SCREENXRES - MARGINX * 2, FONTSIZE, 0, 280 );
}
void gamevictory(void) {
    if (camera) {camera = false;}
    if (maintenancepanel) {maintenancepanel = false;}
    SpuSetKey(SPU_OFF, SPU_ALLCH);
    FrameCounter++;
}
//Other files

#include "musics.h"
#include "objects.h"
#include "camera.h"
#include "AI-related.h"

#include "asc2sjis.h"
#include "memcardthings.h"

void resetgame(int hardreset) {
  if (debugging == 0) {
    if (hardreset == 1) {


    }




    officefadingout = -1;

    isfreddyofficehere = false;
  }
    if (enablephoneguystr[1] == 'N') {enablephoneguy = true;}

    fadeofficenights = 128;

    alarmstate = 0;

    camera = false;
    curcam[0] = 0;
    curcam[1] = 1;

    ventilhealth = 10;
    ventilationfailure = false;

    jumpscared = false;

    ventlocked = 0;

    camerahealth = 10;
    camerahealthtimer = 720;
    audiodevicehealth = 10;

    camerasystemfailure = false;

    noisefootstep = 0;
    framenoisefootstep = 0;

    fivesecondframe = 300;
    ambianceframe = 300;

    mascottune = 0;
    musicmascottune = 1248;

    isalreadydead = 0;
    isalreadydeadlow = 0;
    framedeadpossi = 60;
    lastsecondsframes = 1800;

    screamersetsound = 0;
    screamerframes = 47;
    spriteframes = 2;
    spritesheet = 0;

    dead = false;
    spriteframesconst = 2;

    fadeoffice = 128;

    isonvents = false;
    LoadTexture(_binary_tim_camera_panel_layout_tim_start, &camlayout);

    nightwon = false;
    nextnightframes = 0;
    staticframessheet = 0;
    flashingAMframes = 0;

    staticframes = 300;

    ventbanging = 0;
    ventbangingframes = 0;

    AM = 12;
    FrameCounter = 0;

    isingame = false;

    mutedcall = false;

    stage = 0;
    springtraprunningoffice = false;
    isspringtrapinspecialstage1, isspringtrapinspecialstage2, springtrapinviewrange, springtrapsooninviewrange = false;
    isspringtraprunningtoyou = false;
    springtraprunningindex = -1;
    springtrapnoise = false; //Pro tip : Spongetoy make noises when moving.

    puppetqueued, ballonboyqueued, manglequeued, isfoxyofficehere, chicaqueued = false;
}

#include "menu.h"