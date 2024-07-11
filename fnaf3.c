/*
    TO FIX :   

        Not important : 

        (Really) not important :

    TO MAKE (doing ideas/partially implemented things) :  
        Test the game on different hardware than PC and SCPH-9002 PS1

    TO DO (only ideas) :

    TO FIX ON THE PS1 :

    FIXED ? (it is not doing that anymore but I'm not sure if it's fixed) : 

    FIXED (listed here for help if it happens again) :
      Animatronic's Icon camera going nutz : Try to place ALL of the sprites BEFORE them.
      toy chik hallway or animatronics on vents are breaking the right office's sprite : DON'T SPAM "LoadTexture"

    OTHER (info) :
      FNAF3 is a (heavily) modified version of FNAF2, a (heavily) modified version of FNAF1
      V.0.2
*/

#include "objects/constant.h"
#include "objects/objects.h"
#include "objects/camera.h"

int FrameCounter = 0;
int customAM = 12;

int AM = 12;

int night = 1;

int debug = 3; //1 is for debug without cam, 2 is animatronic debug old, 3 is only little things -- vanilla, 4 is debug for toys, 5 is for office array

//Made all of the var declarations that I won't change alot into constant.h

// extern VAG files
extern u_char _binary_vag_light_vag_start;
extern u_char _binary_vag_monitor_down_vag_start;
extern u_char _binary_vag_officesound_vag_start;
extern u_char _binary_vag_click_vag_start;
extern u_char _binary_vag_screamer_vag_start;
extern u_char _binary_vag_honk_vag_start;
extern u_char _binary_vag_jamlight_vag_start;
extern u_char _binary_vag_monitor_up_vag_start;
extern u_char _binary_vag_monitor_up_2_vag_start;
extern u_char _binary_vag_coin_vag_start;
extern u_char _binary_vag_vent1_vag_start;
extern u_char _binary_vag_vent2_vag_start;
extern u_char _binary_vag_alarm_vag_start;
extern u_char _binary_vag_windup_vag_start;
extern u_char _binary_vag_BB1_vag_start;
extern u_char _binary_vag_BB2_vag_start;
extern u_char _binary_vag_BB3_vag_start;
extern u_char _binary_vag_clickfail_vag_start;
extern u_char _binary_vag_button_vag_start;
extern u_char _binary_vag_consoleclosing_vag_start;
extern u_char _binary_vag_consoleopening_vag_start;

// soundBank
VAGsound vagsoundBank[VAG_NBR] = {
      { &_binary_vag_light_vag_start,
        SPU_00CH, 0 },   
      { &_binary_vag_monitor_down_vag_start,
        SPU_01CH, 0 },
      { &_binary_vag_officesound_vag_start,
        SPU_02CH, 0 },
      { &_binary_vag_click_vag_start,
        SPU_03CH, 0 },
      { &_binary_vag_screamer_vag_start,
        SPU_04CH, 0 },
      { &_binary_vag_honk_vag_start,
        SPU_05CH, 0 },
      { &_binary_vag_jamlight_vag_start,
        SPU_06CH, 0 },
      { &_binary_vag_monitor_up_vag_start,
        SPU_07CH, 0 },
      { &_binary_vag_coin_vag_start,
        SPU_08CH, 0 },
      { &_binary_vag_vent1_vag_start,
        SPU_09CH, 0 },
      { &_binary_vag_vent2_vag_start,
        SPU_10CH, 0 },
      { &_binary_vag_alarm_vag_start,
        SPU_11CH, 0 },
      { &_binary_vag_windup_vag_start,
        SPU_12CH, 0 },
      { &_binary_vag_BB1_vag_start,
        SPU_13CH, 0 },
      { &_binary_vag_BB2_vag_start,
        SPU_14CH, 0 },
      { &_binary_vag_BB3_vag_start,
        SPU_15CH, 0 },
      { &_binary_vag_clickfail_vag_start,
        SPU_16CH, 0 },
      { &_binary_vag_monitor_up_2_vag_start,
        SPU_17CH, 0 },
     { &_binary_vag_button_vag_start,
        SPU_18CH, 0 },
      { &_binary_vag_consoleclosing_vag_start,
        SPU_19CH, 0 },
     { &_binary_vag_consoleopening_vag_start,
        SPU_20CH, 0 },
};

// XA
// SPU attributes
SpuCommonAttr spuSettings;
#define CD_SECTOR_SIZE 1204
// XA
// Sector offset for XA data 4: simple speed, 8: double speed
#define XA_CHANNELS 8
#define XA_CDSPEED XA_CHANNELS >> 2
// Number of XA samples ( != # of XA files )
#define XA_TRACKS 4

typedef struct XAsound {
    u_int id;
    u_int size;
    // We can find size in sector : size / 2336, start value begins at 23, end value is at start + offset ( (size / 2336)-1 * #channels )
    // subsequent start value have an 8 bytes offset (n-1.end + 8)
    u_char file, channel;
    u_int start, end;
    int cursor;
} XAsound;

typedef struct XAbank {
    u_int index;
    int offset;
    XAsound samples[];
} XAbank;

XAbank soundBank = {
        13,
        0,
        {
            // channel 5 (silence.xa = 1496)
            // id   size   file  channel start end cursor
            {   0,  1768352,   1,     5,     0,   6048,  -1 }, //Menu.xa
            {   1,  602688,   1,     5,     7544,   9600,  -1 }, //Beginning of the night.xa
            {   2,  602688,   1,     5,     7544,   9600,  -1 }, //ambiance1.xa
            // channel 6                 
            {   3,  488224,   1,     6 ,   0,   1664, -1  }, //6am.xa
            {   4,  7127136,   1,     6 ,   3160, 27560, -1  }, //Phone Dude Night 1.xa
            //Channel 7
            {   5,  5620416,   1,     7 ,   0, 19240, -1  }, //Phone Dude Night 2.xa 
            {   6, 3333472,   1,     7 ,   20736, 32144, -1  }, //Phone Guy Night 3.xa  
            {   7, 2684064,   1,     7 ,   33640, 42824, -1  }, //Phone Guy Night 4.xa
            {   8, 2373376,   1,     7 ,   44320, 52440, -1  }, //Phone Guy Night 5.xa 
            //Channel 8
            //{   9, 2284608,   1,     8 ,   0, 7816, -1  }, //Music End.xa 
            {   9, 1836096,   1,     8 ,   0, 6280, -1  }, //phone guy Night 6.xa 
            {   10, 1546432,   1,     8 ,   7776, 13064, -1  } //checking.xa 
        }
};
// XA file to load
static char * loadXA = "\\INTER8.XA;1";
// File informations : pos, size, name
CdlFILE XAPos = {0};
// CD filter
CdlFILTER filter;
// File position in m/s/f
CdlLOC  loc;

// Prototypes
void display(void);
void initSnd(void);
u_long sendVAGtoSPU(unsigned int VAG_data_size, u_char *VAG_data);
void setVoiceAttr(unsigned int pitch, long channel, unsigned long soundAddr );
u_long setSPUtransfer(VAGsound * sound);

void resetgame(int hardreset);
void print(int number);
int Ran(int max);
void screamer(void);
void gameoverprint(void);
void printNightInfo(void);
void menuselectionfunc(void);
void debugPrint(void);
void timeFunc(void);
void controllerinput(void);
void CameraFunc(int silent);
void gamevictory(void);
void menuPrint(void);
void animatronicFunc(int init);
void AImoving(void);
void consoleFunc(void);

void LoadTexture(u_long * tim, TIM_IMAGE * tparam){     // This part is from Lameguy64's tutorial series : lameguy64.net/svn/pstutorials/chapter1/3-textures.html login/pw: annoyingmous
        OpenTIM(tim);                                   // Open the tim binary data, feed it the address of the data in memory
        ReadTIM(tparam);                                // This read the header of the TIM data and sets the corresponding members of the TIM_IMAGE structure
        
        LoadImage(tparam->prect, tparam->paddr);        // Transfer the data from memory to VRAM at position prect.x, prect.y
        DrawSync(0);                                    // Wait for the drawing to end

        if (tparam->mode & 0x8){ // check 4th bit       // If 4th bit == 1, TIM has a CLUT
            LoadImage(tparam->crect, tparam->caddr);    // Load it to VRAM at position crect.x, crect.y
            DrawSync(0);                                // Wait for drawing to end
        }
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
    if (VMODE){ SetVideoMode(MODE_PAL);}
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

void display(void) {
    DrawSync(0);                    // Wait for all drawing to terminate
    VSync(0);                       // Wait for the next vertical blank
    PutDispEnv(&disp[db]);          // set alternate disp and draw environnments
    PutDrawEnv(&draw[db]);  
    DrawOTag(&ot[db][OTLEN - 1]);
    db = !db;                       // flip db value (0 or 1)
    nextpri = primbuff[db];
}


// Audio initialisation & functions
void initSnd(void){
    SpuInitMalloc(MALLOC_MAX, spu_malloc_rec);                      // Maximum number of blocks, mem. management table address.
    commonAttributes.mask = (SPU_COMMON_MVOLL | SPU_COMMON_MVOLR);  // Mask which attributes to set
    commonAttributes.mvol.left  = 0x3fff;                           // Master volume left
    commonAttributes.mvol.right = 0x3fff;                           // see libref47.pdf, p.1058
    commonAttributes.cd.volume.left = 0x6000;
    commonAttributes.cd.volume.right = 0x6000;
    // Apply settings
    SpuSetCommonAttr(&commonAttributes);                            // set attributes
    SpuSetIRQ(SPU_OFF);
    SpuSetKey(SpuOff, SPU_ALLCH);
}
void spuSetup(SpuCommonAttr * spuSettings)
{
    // Init Spu
    SpuInit();
    // Set master & CD volume to max
    spuSettings->mask = (SPU_COMMON_MVOLL | SPU_COMMON_MVOLR | SPU_COMMON_CDVOLL | SPU_COMMON_CDVOLR | SPU_COMMON_CDMIX);
    spuSettings->mvol.left  = 0x6000;
    spuSettings->mvol.right = 0x6000;
    spuSettings->cd.volume.left = 0x6000;
    spuSettings->cd.volume.right = 0x6000;
    // Enable CD input ON
    spuSettings->cd.mix = SPU_ON;
    // Apply settings
    SpuSetCommonAttr(spuSettings);
    // Set transfer mode 
    SpuSetTransferMode(SPU_TRANSFER_BY_DMA);
}

void XAsetup()
{   
    u_char param[4];
    // ORing the parameters we need to set ; drive speed,  ADPCM play, Subheader filter, sector size
    // If using CdlModeSpeed(Double speed), you need to load an XA file that has 8 channels.
    // In single speed, a 4 channels XA is to be used.
    param[0] = CdlModeSpeed|CdlModeRT|CdlModeSF|CdlModeSize1;
    // Issue primitive command to CD-ROM system (Blocking-type)
    // Set the parameters above
    CdControlB(CdlSetmode, param, 0);
    // Pause at current pos
    CdControlF(CdlPause,0);
}

u_long sendVAGtoSPU(unsigned int VAG_data_size, u_char *VAG_data){
    u_long transferred;
    SpuSetTransferMode(SpuTransByDMA);                              // DMA transfer; can do other processing during transfer
    transferred = SpuWrite (VAG_data + sizeof(VAGhdr), VAG_data_size);     // transfer VAG_data_size bytes from VAG_data  address to sound buffer
    SpuIsTransferCompleted (SPU_TRANSFER_WAIT);                     // Checks whether transfer is completed and waits for completion
    return transferred;
}

void setVoiceAttr(unsigned int pitch, long channel, unsigned long soundAddr ){
    voiceAttributes.mask=                                   //~ Attributes (bit string, 1 bit per attribute)
    (
      SPU_VOICE_VOLL |
      SPU_VOICE_VOLR |
      SPU_VOICE_PITCH |
      SPU_VOICE_WDSA |
      SPU_VOICE_ADSR_AMODE |
      SPU_VOICE_ADSR_SMODE |
      SPU_VOICE_ADSR_RMODE |
      SPU_VOICE_ADSR_AR |
      SPU_VOICE_ADSR_DR |
      SPU_VOICE_ADSR_SR |
      SPU_VOICE_ADSR_RR |
      SPU_VOICE_ADSR_SL
    );
    voiceAttributes.voice        = channel;                 //~ Voice (low 24 bits are a bit string, 1 bit per voice )
    voiceAttributes.volume.left  = 0x0;                  //~ Volume 
    voiceAttributes.volume.right = 0x0;                  //~ Volume
    voiceAttributes.pitch        = pitch;                   //~ Interval (set pitch)
    voiceAttributes.addr         = soundAddr;               //~ Waveform data start address
    voiceAttributes.a_mode       = SPU_VOICE_LINEARIncN;    //~ Attack rate mode  = Linear Increase - see libref47.pdf p.1091
    voiceAttributes.s_mode       = SPU_VOICE_LINEARIncN;    //~ Sustain rate mode = Linear Increase
    voiceAttributes.r_mode       = SPU_VOICE_LINEARDecN;    //~ Release rate mode = Linear Decrease
    voiceAttributes.ar           = 0x0;                     //~ Attack rate
    voiceAttributes.dr           = 0x0;                     //~ Decay rate
    voiceAttributes.rr           = 0x0;                     //~ Release rate
    voiceAttributes.sr           = 0x0;                     //~ Sustain rate
    voiceAttributes.sl           = 0xf;                     //~ Sustain level
    SpuSetVoiceAttr(&voiceAttributes);                      // set attributes
    SpuSetVoiceVolume(0, 0x3500, 0x3500);//light
    SpuSetVoiceVolume(1, 0x2500, 0x2500);//monitor down
    SpuSetVoiceVolume(2, 0x2500, 0x2500);//officesound
    SpuSetVoiceVolume(3, 0x2000, 0x2000); //click
    SpuSetVoiceVolume(4, 0x4000, 0x4000);//Screamer
    SpuSetVoiceVolume(5, 0x2000, 0x2000);//honk freddy
    SpuSetVoiceVolume(6, 0x1800, 0x1800);//jamlight
    SpuSetVoiceVolume(7, 0x2500, 0x2500);//monitor up
    SpuSetVoiceVolume(8, 0x2500, 0x2500);//mask up
    SpuSetVoiceVolume(9, 0x2500, 0x2500);//mask down
    SpuSetVoiceVolume(10, 0x2000, 0x2000); //coin (blip)
    SpuSetVoiceVolume(11, 0x2000, 0x2000); //vent banging 1
    SpuSetVoiceVolume(12, 0x2000, 0x2000); //vent banging 2
    SpuSetVoiceVolume(13, 0x2500, 0x2500); //alarm
    SpuSetVoiceVolume(14, 0x2000, 0x2000); //wind up
    SpuSetVoiceVolume(15, 0x2000, 0x2000); //BB1
    SpuSetVoiceVolume(16, 0x2000, 0x2000); //BB2
    SpuSetVoiceVolume(17, 0x3000, 0x3000); //Monitor uP 2
    SpuSetVoiceVolume(18, 0x3500, 0x3500); //clickfail
    SpuSetVoiceVolume(19, 0x3500, 0x3500); //Beep from console or when sailing vent
    SpuSetVoiceVolume(20, 0x3500, 0x3500); //Console Opening
    SpuSetVoiceVolume(21, 0x3500, 0x3500); //Console Closing
}

u_long setSPUtransfer(VAGsound * sound){
    // Return spu_address
    u_long transferred, spu_address;
    u_int pitch;
    const VAGhdr * VAGheader = (VAGhdr *) sound->VAGfile;
    pitch = (SWAP_ENDIAN32(VAGheader->samplingFrequency) << 12) / 44100L; 
    spu_address = SpuMalloc(SWAP_ENDIAN32(VAGheader->dataSize));                // Allocate an area of dataSize bytes in the sound buffer. 
    SpuSetTransferStartAddr(spu_address);                                       // Sets a starting address in the sound buffer
    transferred = sendVAGtoSPU(SWAP_ENDIAN32(VAGheader->dataSize), sound->VAGfile);
    setVoiceAttr(pitch, sound->spu_channel, spu_address); 
    // Return 1 if ok, size transferred else.
    //~ if (transferred == SWAP_ENDIAN32(VAGheader->dataSize)){
        //~ return 1;
        //~ }
    //~ return transferred;
    return spu_address;
}

void setRGBALL(int red, int green, int blue, int reason) {

    //For red light (office only) 
    if (reason > 0) {
        setRGB0(polyofficemiddle, red, green, blue);             
        setRGB0(polyofficeleft, red, green, blue);    
        setRGB0(polyofficeright, red, green, blue);     
    }
    //For fadeout and fade in again
    if (reason > 1) {
        setRGB0(poly2ndlayer2, red, green, blue);  
        if (red > 100) {
            setRGB0(polyspringtrapoffice1, red - 20, green - 20, blue - 20);  
            setRGB0(polymaintenance_sprite,red - 20, green - 20, blue - 20);
        } else {
            setRGB0(polyspringtrapoffice1, red, green, blue);  
            setRGB0(polymaintenance_sprite,red,green,blue);
        }
        setRGB0(polyspringtrapoffice2, red, green, blue);

        setRGB0(polymaintenance_camsys,red,green,blue);
        setRGB0(polymaintenance_audevice,red,green,blue);
        setRGB0(polymaintenance_loadco,red,green,blue);
        setRGB0(polymaintenance_text,red,green,blue);
        setRGB0(polymaintenance_text2,red,green,blue);
        setRGB0(polymaintenance_text3,red,green,blue);
    }
    //For the finished night
    if (reason > 2) {
        setRGB0(polyfiveam, 128 - fadeoffice, 128 - fadeoffice, 128 - fadeoffice);    
    }


    if (fivetosixamframes > 1) {         
        if (camera == 1) {
        }
    }
}

void starting(void) {
  resetgame(0);

  setRGBALL(128, 128, 128, 2);

  if (customnightactivated == 0) {
    freddylocationframe = 300;
    bonnielocationframe = 300;
    chicalocationframe = 300;
    foxylocationframe = 300;
    toyfreddylocationframe = 300;
    toybonnielocationframe = 300;
    toychicalocationframe = 300;
    manglelocationframe = 300;
    GFlocationframehallway = 60;
    GFlocationframe = 300;
    convertion = 60;
    customAM = 12;
    doescharlevelup = 1;
  }
  if (initstuff == 1) {
    clearVRAMMenu();
    LoadTexture(_binary_tim_load_tim_start, &load); 
  } else {clearVRAMloading(); clearVRAMScreamer();}

  musicframes = 0;

  if (fastnights == 1) {
      FrameCounterlimit = FrameCounterlimit / 2;
  }

  AM = customAM;
  FrameCounterlimit = convertion;
  FrameCounterlimit = FrameCounterlimit * 60; //60 seconds * 60 fps = 3600 frames, maybe it would cause issues with 30 fps ??
  SpuSetKey(SPU_ON, SPU_03CH);
  if (weirdnight == 0 && customnightactivated == 0) {
    animatronicFunc(1);
  }
}

void lineflicker(void) {
    linesframes++;
    if (linesframes == 4) {
        LoadTexture(_binary_tim_titlemenu_lines_1_tim_start, &lines);
        setUV4(polylines, 0, 0, 0, 142, 128, 0, 128, 142);
    }
    if (linesframes == 8) {
        LoadTexture(_binary_tim_titlemenu_lines_2_tim_start, &lines);
    }
    if (linesframes == 12) {
        LoadTexture(_binary_tim_titlemenu_lines_3_tim_start, &lines);
    }
    if (linesframes == 16) {
        LoadTexture(_binary_tim_titlemenu_lines_4_tim_start, &lines);
    }
    if (linesframes == 20) {
        LoadTexture(_binary_tim_titlemenu_lines_5_tim_start, &lines);
    }
    if (linesframes >= 24) {
        linesactive = 0;
        linesframes = 0;
        setUV4(polylines, 0, 0, 0, 0, 0, 0, 0, 0);
    }
}

void finishednight(void) {
  fivetosixamframes++;
  if (fivetosixamframes == 1) {
    gamevictory();
    mutedcall = 1;
  }
  makepoly(10); 
  if (fadeoffice > 0) {
    fadeoffice--;

    setRGBALL(fadeoffice, fadeoffice, fadeoffice, 3);

  } else {
    setRGB0(polyfiveam, 128, 128, 128);   

    setRGBALL(fadeoffice, fadeoffice, fadeoffice, 2);

    if (camera == 1) {
      CameraFunc(1);
    }
  }
  if (fivetosixamframes == 89){
      LoadTexture(_binary_tim_5am6_5AM1_tim_start, &fiveam);
  }
  if (fivetosixamframes == 101){
      LoadTexture(_binary_tim_5am6_5AM2_tim_start, &fiveam);
  }
  if (fivetosixamframes == 113){
      LoadTexture(_binary_tim_5am6_5AM3_tim_start, &fiveam);
  }
  if (fivetosixamframes == 125){
      LoadTexture(_binary_tim_5am6_5AM4_tim_start, &fiveam);
  }
  if (fivetosixamframes == 137){
      LoadTexture(_binary_tim_5am6_5AM5_tim_start, &fiveam);
  }
  if (fivetosixamframes == 181){
      LoadTexture(_binary_tim_5am6_6AM1_tim_start, &fiveam);
  }
  if (fivetosixamframes == 193){
      LoadTexture(_binary_tim_5am6_6AM2_tim_start, &fiveam);
  }
  if (fivetosixamframes == 205){
      LoadTexture(_binary_tim_5am6_6AM3_tim_start, &fiveam);
  }
  if (fivetosixamframes == 217){
      LoadTexture(_binary_tim_5am6_6AM4_tim_start, &fiveam);
  }
  if (fivetosixamframes == 229){
      LoadTexture(_binary_tim_5am6_6AM5_tim_start, &fiveam);
  }
  if (fivetosixamframes == 241){
      LoadTexture(_binary_tim_5am6_6AM6_tim_start, &fiveam);
  }
}

int main(void) {
    //controller
    TILE * PADL;                    // Tile primitives
    TILE * TRIGGERL;
    TILE * PADR;
    TILE * TRIGGERR;
    TILE * START, * SELECT;

    int sample = -1;

    init();

    //SPU
    u_long spu_address;
    spuSetup(&spuSettings);
    // Init sound settings
    initSnd();

    PadInit(0);                     // Initialize pad.  Mode is always 0

    for (u_short vag = 0; vag < VAG_NBR; vag++ ){
        vagsoundBank[vag].spu_address = setSPUtransfer(&vagsoundBank[vag]);
    }

    // Init CD system
    CdInit();

    // Init heap
    InitHeap((u_long *)ramAddr, sizeof(ramAddr));

    clearVRAM();
    //LoadTexture(_binary_tim_fnt_tim_start, &fontface);
    while (1)
    {   
        if (fivesecondframe > 0) {fivesecondframe--;} else {fivesecondframe = 300;}
        if (demisecondframe > 0) {demisecondframe--;} else {demisecondframe = 30;}
        ClearOTagR(ot[db], OTLEN);
        
        if (linesactive == 1) {
            lineflicker();
        }

        pad = PadRead(0);
        // if sample is set
        if (sample != -1 ){
            // Begin XA file playback...
            // if sample's cursor is 0
            if (soundBank.samples[sample].cursor == 0){
                // Convert sector number to CD position in min/second/frame and set CdlLOC accordingly.
                CdIntToPos( soundBank.samples[sample].start + soundBank.offset , &loc);
                // Send CDROM read command
                CdControlF(CdlReadS, (u_char *)&loc);
                // Set playing flag
            }
            // if sample's cursor is close to sample's end position, stop playback
            if ((soundBank.samples[sample].cursor += XA_CDSPEED) >= soundBank.samples[sample].end - soundBank.samples[sample].start  ){
                CdControlF(CdlStop,0);
                soundBank.samples[sample].cursor = -1;
                sample = -1;
            }
        }
        if (menu == 0) { //Menu Screen
            if (helpwantedposter == 0) {

                menuPrint();
    
                menuselectionfunc();
    
                if (musicframes > 2421){
                    musicframes = 0;
                    sample = 0;
                    filter.chan = soundBank.samples[sample].channel;
                    filter.file = soundBank.samples[sample].file;
                    CdControlF(CdlSetfilter, (u_char *)&filter);
                    soundBank.samples[sample].cursor = 0;
                } else {musicframes++;}
    
                if (menuscreeninit == 0) {
                if (initstuff == 0) {/*
                    loadFile = "\\HWANTED.TIM;1";
                    CdSearchFile( &filePos, loadFile);
                    dataBuffer = malloc( BtoS(filePos.size) * CD_SECTOR_SIZE );
                    CdControl(CdlSetloc, (u_char *)&filePos.pos, CtrlResult);
                    // Read data and load it to dataBuffer
                    CDreadOK = CdRead( (int)BtoS(filePos.size), (u_long *)dataBuffer, CdlModeSpeed );
                    CDreadResult = CdReadSync(0, 0);
                    LoadTexture(dataBuffer, &helpwanted); 
                    free(dataBuffer);
                    
                    loadFile = "\\GJFIV.TIM;1";
                    CdSearchFile( &filePos, loadFile);
                    dataBuffer = malloc( BtoS(filePos.size) * CD_SECTOR_SIZE );
                    CdControl(CdlSetloc, (u_char *)&filePos.pos, CtrlResult);
                    // Read data and load it to dataBuffer
                    CDreadOK = CdRead( (int)BtoS(filePos.size), (u_long *)dataBuffer, CdlModeSpeed );
                    CDreadResult = CdReadSync(0, 0);
                    LoadTexture(dataBuffer, &goodjob); 
                    free(dataBuffer);*/
                    initstuff++;

                }
                loadFile = "\\OFFICE.TIM;1";
                CdSearchFile( &filePos, loadFile);
                dataBuffer = malloc( BtoS(filePos.size) * CD_SECTOR_SIZE );
                CdControl(CdlSetloc, (u_char *)&filePos.pos, CtrlResult);
                // Read data and load it to dataBuffer
                CDreadOK = CdRead( (int)BtoS(filePos.size), (u_long *)dataBuffer, CdlModeSpeed );
                CDreadResult = CdReadSync(0, 0);
                LoadTexture(dataBuffer, &officeMIDDLE); 
                free(dataBuffer);
                loadFile = "\\HWANTED.TIM;1";
                CdSearchFile( &filePos, loadFile);
                dataBuffer = malloc( BtoS(filePos.size) * CD_SECTOR_SIZE );
                CdControl(CdlSetloc, (u_char *)&filePos.pos, CtrlResult);
                // Read data and load it to dataBuffer
                CDreadOK = CdRead( (int)BtoS(filePos.size), (u_long *)dataBuffer, CdlModeSpeed );
                CDreadResult = CdReadSync(0, 0);
                LoadTexture(dataBuffer, &helpwanted); 
                free(dataBuffer);
                loadFile = "\\MENUS1.TIM;1";
                CdSearchFile( &filePos, loadFile);
                dataBuffer = malloc( BtoS(filePos.size) * CD_SECTOR_SIZE );
                CdControl(CdlSetloc, (u_char *)&filePos.pos, CtrlResult);
                // Read data and load it to dataBuffer
                CDreadOK = CdRead( (int)BtoS(filePos.size), (u_long *)dataBuffer, CdlModeSpeed );
                CDreadResult = CdReadSync(0, 0);
                LoadTexture(dataBuffer, &menus1); 
                free(dataBuffer);
                loadFile = "\\MENUS2.TIM;1";
                CdSearchFile( &filePos, loadFile);
                dataBuffer = malloc( BtoS(filePos.size) * CD_SECTOR_SIZE );
                CdControl(CdlSetloc, (u_char *)&filePos.pos, CtrlResult);
                // Read data and load it to dataBuffer
                CDreadOK = CdRead( (int)BtoS(filePos.size), (u_long *)dataBuffer, CdlModeSpeed );
                CDreadResult = CdReadSync(0, 0);
                LoadTexture(dataBuffer, &menus1); 
                free(dataBuffer);
                loadFile = "\\MENUS3.TIM;1";
                CdSearchFile( &filePos, loadFile);
                dataBuffer = malloc( BtoS(filePos.size) * CD_SECTOR_SIZE );
                CdControl(CdlSetloc, (u_char *)&filePos.pos, CtrlResult);
                // Read data and load it to dataBuffer
                CDreadOK = CdRead( (int)BtoS(filePos.size), (u_long *)dataBuffer, CdlModeSpeed );
                CDreadResult = CdReadSync(0, 0);
                LoadTexture(dataBuffer, &menus1); 
                free(dataBuffer);
                loadFile = "\\MENUS4.TIM;1";
                CdSearchFile( &filePos, loadFile);
                dataBuffer = malloc( BtoS(filePos.size) * CD_SECTOR_SIZE );
                CdControl(CdlSetloc, (u_char *)&filePos.pos, CtrlResult);
                // Read data and load it to dataBuffer
                CDreadOK = CdRead( (int)BtoS(filePos.size), (u_long *)dataBuffer, CdlModeSpeed );
                CDreadResult = CdReadSync(0, 0);
                LoadTexture(dataBuffer, &menus1); 
                free(dataBuffer);
                loadFile = "\\MENUS5.TIM;1";
                CdSearchFile( &filePos, loadFile);
                dataBuffer = malloc( BtoS(filePos.size) * CD_SECTOR_SIZE );
                CdControl(CdlSetloc, (u_char *)&filePos.pos, CtrlResult);
                // Read data and load it to dataBuffer
                CDreadOK = CdRead( (int)BtoS(filePos.size), (u_long *)dataBuffer, CdlModeSpeed );
                CDreadResult = CdReadSync(0, 0);
                LoadTexture(dataBuffer, &menus1); 
                free(dataBuffer);/*
                loadFile = "\\LAYOUT.TIM;1";
                CdSearchFile( &filePos, loadFile);
                dataBuffer = malloc( BtoS(filePos.size) * CD_SECTOR_SIZE );
                CdControl(CdlSetloc, (u_char *)&filePos.pos, CtrlResult);
                // Read data and load it to dataBuffer
                CDreadOK = CdRead( (int)BtoS(filePos.size), (u_long *)dataBuffer, CdlModeSpeed );
                CDreadResult = CdReadSync(0, 0);
                LoadTexture(dataBuffer, &layout); 
                free(dataBuffer);*/
                loadFile = "\\STATIC.TIM;1";
                CdSearchFile( &filePos, loadFile);
                dataBuffer = malloc( BtoS(filePos.size) * CD_SECTOR_SIZE );
                CdControl(CdlSetloc, (u_char *)&filePos.pos, CtrlResult);
                // Read data and load it to dataBuffer
                CDreadOK = CdRead( (int)BtoS(filePos.size), (u_long *)dataBuffer, CdlModeSpeed );
                CDreadResult = CdReadSync(0, 0);
                LoadTexture(dataBuffer, &statics); 
                free(dataBuffer);/*
                loadFile = "\\SPRGTRP1.TIM;1";
                CdSearchFile( &filePos, loadFile);
                dataBuffer = malloc( BtoS(filePos.size) * CD_SECTOR_SIZE );
                CdControl(CdlSetloc, (u_char *)&filePos.pos, CtrlResult);
                // Read data and load it to dataBuffer
                CDreadOK = CdRead( (int)BtoS(filePos.size), (u_long *)dataBuffer, CdlModeSpeed );
                CDreadResult = CdReadSync(0, 0);
                LoadTexture(dataBuffer, &springtrapoffice1); 
                free(dataBuffer);
                loadFile = "\\SPRGTRP2.TIM;1";
                CdSearchFile( &filePos, loadFile);
                dataBuffer = malloc( BtoS(filePos.size) * CD_SECTOR_SIZE );
                CdControl(CdlSetloc, (u_char *)&filePos.pos, CtrlResult);
                // Read data and load it to dataBuffer
                CDreadOK = CdRead( (int)BtoS(filePos.size), (u_long *)dataBuffer, CdlModeSpeed );
                CDreadResult = CdReadSync(0, 0);
                LoadTexture(dataBuffer, &springtrapoffice1); 
                free(dataBuffer);*/

                LoadTexture(_binary_tim_titlemenu_NAME_tim_start, &menuselections); 
                LoadTexture(_binary_tim_titlemenu_SLTBUT_tim_start, &menuselections); 
                LoadTexture(_binary_tim_titlemenu_NEWGAME_tim_start, &menuselections); 
                LoadTexture(_binary_tim_titlemenu_LOADGAME_tim_start, &menuselections); 
                LoadTexture(_binary_tim_titlemenu_EXTRA_tim_start, &menuselections); 
                LoadTexture(_binary_tim_office_panelsprite_PANEL0_tim_start, &panel); 
                LoadTexture(_binary_tim_Mpanel_AUDEVICE_tim_start, &maintenance_audevice); 
                LoadTexture(_binary_tim_Mpanel_CAMSYS_tim_start, &maintenance_camsys); 
                //LoadTexture(_binary_tim_Mpanel_console_tim_start, &maintenance_console); 
                LoadTexture(_binary_tim_Mpanel_error_tim_start, &maintenance_error); 
                LoadTexture(_binary_tim_Mpanel_EXIT_tim_start, &maintenance_exit); 
                LoadTexture(_binary_tim_Mpanel_Loadco_tim_start, &maintenance_loadco); 
                LoadTexture(_binary_tim_Mpanel_MENU_tim_start, &maintenance_text); 
                LoadTexture(_binary_tim_Mpanel_REBOOT_tim_start, &maintenance_reboot); 
                LoadTexture(_binary_tim_Mpanel_RESTART_tim_start, &maintenance_text); 
                LoadTexture(_binary_tim_Mpanel_VENTIL_tim_start, &maintenance_ventil); 

                LoadTexture(_binary_tim_office_FREDDYWANDERING_tim_start, &freddyoffice); 
                LoadTexture(_binary_tim_office_SPRINGTRAP1_tim_start, &springtrapoffice1); 
                LoadTexture(_binary_tim_office_SPRINGTRAP2_tim_start, &springtrapoffice2); 



                CdSearchFile( &XAPos, loadXA);
                soundBank.offset = CdPosToInt(&XAPos.pos);
                XAsetup();
                menuscreeninit = 1;

                }
                if (menuscreeninit == 1) {

                seedrandom++;
                if (notoys == 0) {makepoly(1);}
                }
                
            } else {
                if (notoys) {loadingframe = 360;}
                loadingframe++;

                if (loadingframe == 1) {
                    musicframes = 2410;
                    if (ambiancesound > 3) {ambiancesound = 1;}
                }
                if (loadingframe < 360) {

                    //Help wanted bg
                    makepoly(2);

                    if (loadingframe > 100) {
                        if (pad & PADstart) {
                            loadingframe = 360;
                        }
                    }
                }
                if (loadingframe > 240) {
                    if (fadeoffice < 128) {fadeoffice++;}
                } else {
                    if (fadeoffice > 0) {fadeoffice--;}
                }
                setRGB0(polyhelpwanted, 128 - fadeoffice, 128 - fadeoffice, 128 - fadeoffice);   
                if (loadingframe > 360) {
                    menu = 1;
                    helpwantedposter = 0;
                }
            }
        }//Menu Screen
        if (menu == 1) { //Loading/Starting night screen
            loadingframe++;

            if (loadingframe < 360) {loadingframe = 360;}

            if (loadingframe == 362) {
                sample = 1;
                filter.chan = soundBank.samples[sample].channel;
                filter.file = soundBank.samples[sample].file;
                CdControlF(CdlSetfilter, (u_char *)&filter);
                soundBank.samples[sample].cursor = 0;

                if (night == 1) {
                    LoadTexture(_binary_tim_titlemenu_nights_1ST_tim_start, &nights);
                }
                if (night == 2) {
                    LoadTexture(_binary_tim_titlemenu_nights_2ND_tim_start, &nights);
                }
                if (night == 3) {
                    LoadTexture(_binary_tim_titlemenu_nights_3RD_tim_start, &nights);
                }
                if (night == 4) {
                    LoadTexture(_binary_tim_titlemenu_nights_4TH_tim_start, &nights);
                }
                if (night == 5) {
                    LoadTexture(_binary_tim_titlemenu_nights_5TH_tim_start, &nights);
                }
                if (night == 6) {
                    LoadTexture(_binary_tim_titlemenu_nights_6TH_tim_start, &nights);
                }
                if (night == 7) {
                    LoadTexture(_binary_tim_titlemenu_nights_7TH_tim_start, &nights);
                }
            }

            if (loadingframe == 370 && onetime == 0) {
                linesactive = 1;
                starting();
                srand(seedrandom); // "truly" "random"
                Ran(seedrandom * 68574 + seedrandom / 2);
                srand(RAN); //Truly random x2
                Ran(8500);
                if (RAN == 1) {
                  weirdnight = 1;
                  oldnight = night;
                  night = 725255;
                  onetime++;
                }
            }

            if (loadingframe > 370 && loadingframe < 615) {
                printNightInfo();

                if (loadingframe + 64 > 615) {
                    fadeofficenights = fadeofficenights - 2;
                    setRGB0(polynights, fadeofficenights, fadeofficenights, fadeofficenights);
                } else {
                    setRGB0(polynights, 128, 128, 128);
                }
                makepoly(4);
            } else {
                makepoly(13);
            }

            if (loadingframe == 500) {
                Ran(10000);
            }
            if (loadingframe == 616) {
                LoadTexture(_binary_tim_office_mutecall_tim_start, &mutecall);
            }
            if (loadingframe == 626) {
                if (night == 6) {LoadTexture(_binary_tim_GJSIX_tim_start, &goodjob);}
                if (initstuff == 1) {

                    //Here we go, loading all the cameras of the game...
                    //150 KB for the map, 60 for the vent.

                    loadFile = "\\CAM-01.TIM;1";
                    CdSearchFile( &filePos, loadFile);
                    dataBuffer = malloc( BtoS(filePos.size) * CD_SECTOR_SIZE );
                    CdControl(CdlSetloc, (u_char *)&filePos.pos, CtrlResult);
                    // Read data and load it to dataBuffer
                    CDreadOK = CdRead( (int)BtoS(filePos.size), (u_long *)dataBuffer, CdlModeSpeed );
                    CDreadResult = CdReadSync(0, 0);
                    LoadTexture(dataBuffer, &cam01); 
                    free(dataBuffer);

                    loadFile = "\\CAM-02.TIM;1";
                    CdSearchFile( &filePos, loadFile);
                    dataBuffer = malloc( BtoS(filePos.size) * CD_SECTOR_SIZE );
                    CdControl(CdlSetloc, (u_char *)&filePos.pos, CtrlResult);
                    // Read data and load it to dataBuffer
                    CDreadOK = CdRead( (int)BtoS(filePos.size), (u_long *)dataBuffer, CdlModeSpeed );
                    CDreadResult = CdReadSync(0, 0);
                    LoadTexture(dataBuffer, &cam02); 
                    free(dataBuffer);

                    loadFile = "\\CAM-03.TIM;1";
                    CdSearchFile( &filePos, loadFile);
                    dataBuffer = malloc( BtoS(filePos.size) * CD_SECTOR_SIZE );
                    CdControl(CdlSetloc, (u_char *)&filePos.pos, CtrlResult);
                    // Read data and load it to dataBuffer
                    CDreadOK = CdRead( (int)BtoS(filePos.size), (u_long *)dataBuffer, CdlModeSpeed );
                    CDreadResult = CdReadSync(0, 0);
                    LoadTexture(dataBuffer, &cam03); 
                    free(dataBuffer);

                    loadFile = "\\CAM-04.TIM;1";
                    CdSearchFile( &filePos, loadFile);
                    dataBuffer = malloc( BtoS(filePos.size) * CD_SECTOR_SIZE );
                    CdControl(CdlSetloc, (u_char *)&filePos.pos, CtrlResult);
                    // Read data and load it to dataBuffer
                    CDreadOK = CdRead( (int)BtoS(filePos.size), (u_long *)dataBuffer, CdlModeSpeed );
                    CDreadResult = CdReadSync(0, 0);
                    LoadTexture(dataBuffer, &cam04); 
                    free(dataBuffer);

                    loadFile = "\\CAM-05.TIM;1";
                    CdSearchFile( &filePos, loadFile);
                    dataBuffer = malloc( BtoS(filePos.size) * CD_SECTOR_SIZE );
                    CdControl(CdlSetloc, (u_char *)&filePos.pos, CtrlResult);
                    // Read data and load it to dataBuffer
                    CDreadOK = CdRead( (int)BtoS(filePos.size), (u_long *)dataBuffer, CdlModeSpeed );
                    CDreadResult = CdReadSync(0, 0);
                    LoadTexture(dataBuffer, &cam05); 
                    free(dataBuffer);

                    loadFile = "\\CAM-06.TIM;1";
                    CdSearchFile( &filePos, loadFile);
                    dataBuffer = malloc( BtoS(filePos.size) * CD_SECTOR_SIZE );
                    CdControl(CdlSetloc, (u_char *)&filePos.pos, CtrlResult);
                    // Read data and load it to dataBuffer
                    CDreadOK = CdRead( (int)BtoS(filePos.size), (u_long *)dataBuffer, CdlModeSpeed );
                    CDreadResult = CdReadSync(0, 0);
                    LoadTexture(dataBuffer, &cam06); 
                    free(dataBuffer);

                    loadFile = "\\CAM-07.TIM;1";
                    CdSearchFile( &filePos, loadFile);
                    dataBuffer = malloc( BtoS(filePos.size) * CD_SECTOR_SIZE );
                    CdControl(CdlSetloc, (u_char *)&filePos.pos, CtrlResult);
                    // Read data and load it to dataBuffer
                    CDreadOK = CdRead( (int)BtoS(filePos.size), (u_long *)dataBuffer, CdlModeSpeed );
                    CDreadResult = CdReadSync(0, 0);
                    LoadTexture(dataBuffer, &cam07); 
                    free(dataBuffer);

                    loadFile = "\\CAM-08.TIM;1";
                    CdSearchFile( &filePos, loadFile);
                    dataBuffer = malloc( BtoS(filePos.size) * CD_SECTOR_SIZE );
                    CdControl(CdlSetloc, (u_char *)&filePos.pos, CtrlResult);
                    // Read data and load it to dataBuffer
                    CDreadOK = CdRead( (int)BtoS(filePos.size), (u_long *)dataBuffer, CdlModeSpeed );
                    CDreadResult = CdReadSync(0, 0);
                    LoadTexture(dataBuffer, &cam08); 
                    free(dataBuffer);

                    loadFile = "\\CAM-09.TIM;1";
                    CdSearchFile( &filePos, loadFile);
                    dataBuffer = malloc( BtoS(filePos.size) * CD_SECTOR_SIZE );
                    CdControl(CdlSetloc, (u_char *)&filePos.pos, CtrlResult);
                    // Read data and load it to dataBuffer
                    CDreadOK = CdRead( (int)BtoS(filePos.size), (u_long *)dataBuffer, CdlModeSpeed );
                    CDreadResult = CdReadSync(0, 0);
                    LoadTexture(dataBuffer, &cam09); 
                    free(dataBuffer);
                    
                    loadFile = "\\CAM-10.TIM;1";
                    CdSearchFile( &filePos, loadFile);
                    dataBuffer = malloc( BtoS(filePos.size) * CD_SECTOR_SIZE );
                    CdControl(CdlSetloc, (u_char *)&filePos.pos, CtrlResult);
                    // Read data and load it to dataBuffer
                    CDreadOK = CdRead( (int)BtoS(filePos.size), (u_long *)dataBuffer, CdlModeSpeed );
                    CDreadResult = CdReadSync(0, 0);
                    LoadTexture(dataBuffer, &cam10); 
                    free(dataBuffer);

                    loadFile = "\\2NDLYR2.TIM;1";
                    CdSearchFile( &filePos, loadFile);
                    dataBuffer = malloc( BtoS(filePos.size) * CD_SECTOR_SIZE );
                    CdControl(CdlSetloc, (u_char *)&filePos.pos, CtrlResult);
                    // Read data and load it to dataBuffer
                    CDreadOK = CdRead( (int)BtoS(filePos.size), (u_long *)dataBuffer, CdlModeSpeed );
                    CDreadResult = CdReadSync(0, 0);
                    LoadTexture(dataBuffer, &officeRIGHT); 
                    free(dataBuffer);
                }
            } 
            if (loadingframe == 636) {
                if (initstuff == 1) {/*
                    loadFile = "\\FAM.TIM;1";
                    CdSearchFile( &filePos, loadFile);
                    dataBuffer = malloc( BtoS(filePos.size) * CD_SECTOR_SIZE );
                    CdControl(CdlSetloc, (u_char *)&filePos.pos, CtrlResult);
                    // Read data and load it to dataBuffer
                    CDreadOK = CdRead( (int)BtoS(filePos.size), (u_long *)dataBuffer, CdlModeSpeed );
                    CDreadResult = CdReadSync(0, 0);
                    LoadTexture(dataBuffer, &fiveam); 
                    free(dataBuffer);*/
                    initstuff++;
                }
                CdSearchFile( &XAPos, loadXA);
                soundBank.offset = CdPosToInt(&XAPos.pos);
                XAsetup();  
           } 
           if (loadingframe > 650) {
                if (initstuff == 2) {
                    initstuff++;
                }
           }
            if (loadingframe > 651) {
                menu = 2;
                SpuSetKey(SPU_ON, SPU_02CH);
                loadingframe = 0;
            }
        }//Loading/Starting night screen
        if (menu == 2) { //Gameplay Screen
            timeFunc();   

            if (AM == 6 && FrameCounter == 0) {
                nightwon = 1;
                sample = 2;
                filter.chan = soundBank.samples[sample].channel;
                filter.file = soundBank.samples[sample].file;
                CdControlF(CdlSetfilter, (u_char *)&filter);
                soundBank.samples[sample].cursor = 0;
            }

            if (fivetosixamframes < 720 && AM == 6) {
              finishednight();
            }
            if (fivetosixamframes > 719) {
                if (night == 5 || night == 6 || night == 7) {
                    nextnightframes++;
                    if (nextnightframes == 1) {
                        sample = 10; //Sample is for the music playing, 13 normal, 18 funky
                        filter.chan = soundBank.samples[sample].channel;
                        filter.file = soundBank.samples[sample].file;
                        CdControlF(CdlSetfilter, (u_char *)&filter);

                        soundBank.samples[sample].cursor = 0;
                    }
                    makepoly(11);

                    if (pad & PADstart && night != 7 || nextnightframes == 3600 && night != 7) {
                        if (night != 6) {
                            night++;
                        }
                        fivetosixamframes = 0;
                        nextnightframes = 0;
                        menu = 1;
                    } 
                } else {
                    if (night == 725255) {
                      night = oldnight;
                    } else {night++;}
                    fivetosixamframes = 0;
                    nextnightframes = 0;
                    menu = 1; //Load into next night
                }
            }

            if (returnframes == 60 || returnframes == 120 || returnframes == 180) {
                returnbasevolume  = returnbasevolume + 2000;
                SpuSetVoiceVolume(3, returnbasevolume, returnbasevolume);
                SpuSetKey(SPU_ON, SPU_03CH);
            }
            if (returnframes == 210) {
                isingame = 1;
                menuscreeninit = 0;
                SpuSetKey(SPU_OFF, SPU_ALLCH);
                returnbasevolume = 0x1800;
                SpuSetVoiceVolume(3, returnbasevolume, returnbasevolume);
                menuselection = 3;
                menuselectionmax = 2;
                returnframes = 0;
                musicframes = 4430;
                menu = 0;
                notoys = 1;
            }
            if (returnedingame) {
                CdControlF(CdlPause,0);
                SpuSetKey(SPU_ON, SPU_02CH);
                returnedingame = 0;
            }

            if (dead == 1) {
              if (screamersetsound == 0) {
                  sample = 9;
                  filter.chan = soundBank.samples[sample].channel;
                  filter.file = soundBank.samples[sample].file;
                  CdControlF(CdlSetfilter, (u_char *)&filter);
                  soundBank.samples[sample].cursor = 0;
                  screamersetsound++;
              }
              screamer();
            } else {
              if (fivetosixamframes == 0) {
                print(printnumber);
                animatronicFunc(0);
                controllerinput();
              }
            }
            if (activatedmenudebug == 1 && pad & PADR1 && pad & PADRup && pad & PADRright && pad & PADL2) {
                AM = 5;
                FrameCounter = FrameCounterlimit - 60;
            }
            if (camera == 1) { //Cam things
                cameraloc();
            }
            
            if (fivesecondframe == 0) {
                if (phoneguytalking == 0 && AM != 6) {
                    Ran(10);
                    if (ambiancechance > RAN) {
                        if (ambiancesound == 1) {
                            sample = 2;
                            fivesecondframe = 8580;
                        }
                        if (ambiancesound == 2) {
                            sample = 3;
                            fivesecondframe = 3600;
                        }
                        ambiancesound++;
                        ambiancechance = 1;
                        filter.chan = soundBank.samples[sample].channel;
                        filter.file = soundBank.samples[sample].file;
                        CdControlF(CdlSetfilter, (u_char *)&filter);
                        soundBank.samples[sample].cursor = 0;
                    }else {
                        ambiancesound++;
                        ambiancechance++;
                    }   
                    if (ambiancesound > 2) {
                        ambiancesound = 1;
                    }
                }
            }


            if (phoneguytalkingconst - 1620 < phoneguytalking && mutedcall == 0) {
              if (pad & PADselect || pad >> 16 & PADselect) {
                mutedcall = 1;
                CdControlF(CdlPause,0);
                phoneguytalking = 0;
                enablephoneguy = 0;
              }
            }
            if (noisefootstep == 1) {
                framenoisefootstep++;
                int noise;
                if (framenoisefootstep == 1) {
                    if (noisefootstepanimatronic == 1) { //Bonnie
                        noise = noise + bonnielocation * 300;
                    }
                    if (noisefootstepanimatronic == 2) { //Chica
                        noise = noise + chicalocation * 300; // chicalocation == 1 -> +300, == 7 -> +1400
                    }
                    SpuSetVoiceVolume(8, noise, noise);
                    SpuSetKey(SPU_ON, SPU_08CH);
                }
                if (framenoisefootstep == 60) {
                    SpuSetVoiceVolume(8, noise - 600, noise - 600); //For making it quieter
                    SpuSetKey(SPU_ON, SPU_08CH);
                    noisefootstep--;
                    framenoisefootstep = 0;
                    noise = 0;
                }
            }

            if (noisefootstepF == 1) {
                int noisef;
                noisef = 0x800;
                noisef = noisef + freddylocation * 1000;
                SpuSetVoiceVolume(13, noisef, noisef);
                SpuSetKey(SPU_ON, SPU_11CH);
                noisefootstepF--;
                noisef = 0;
            }

            if (fivetosixamframes == 0) {
                if (triggeralarm == 0) {
                    setRGBALL(128, 128, 128, 2);
                } else {
                    if (officefadingout == 1) {
                        if (fadeoffice != 0 && oneway == 0) {fadeoffice--;} else {oneway++;}

                        if (oneway > 30) { 
                            if (fadeoffice != 128) {
                                fadeoffice++;
                            } else {
                                oneway = 0;
                            }
                        }

                        if (fadeoffice > 91) {officefadingoutminus = fadeoffice - 74;} else {officefadingoutminus = 0;}

                        if (alarmcooldown > 15) {
                            setRGBALL(fadeoffice, officefadingoutminus, officefadingoutminus, 1);
                            setRGB0(poly2ndlayer2, fadeoffice, fadeoffice, fadeoffice); 
                        } else {
                            setRGBALL(fadeoffice, fadeoffice, fadeoffice, 2);
                        }
                    } else {
                        if (alarmcooldown > 15) {
                            setRGBALL(128, 37, 37, 1);
                            setRGB0(poly2ndlayer2, 128, 128, 128); 
                        } else {
                            setRGBALL(128, 128, 128, 2);
                        }
                    }
                }
            }

            if (camera == 0 && isalreadydead == 5 && cooldowncamera != 0) {dead = 1;}
            
            if (ventbanging == 1) {
              ventbangingframes++;
              if (ventbangingframes == 1) {
                SpuSetKey(SPU_ON, SPU_09CH);
              }
              if (ventbangingframes == 37) {
                SpuSetKey(SPU_ON, SPU_10CH);
              }
              if (ventbangingframes == 74) {
                SpuSetKey(SPU_ON, SPU_09CH);
              }
              if (ventbangingframes == 111) {
                SpuSetKey(SPU_ON, SPU_10CH);
              }
              if (ventbangingframes == 148) {
                SpuSetKey(SPU_ON, SPU_09CH);
              }
              if (ventbangingframes == 190) {
                ventbanging = 0;
                ventbangingframes = 0;
              }
            }

            if (AM == 12 && FrameCounter == 1) { //Init Gameplay
                CdControlF(CdlPause,0);
            }
            if (phoneguytalking == 0 && enablephoneguy) {
                if (night == 1) {
                    phoneguytalking = 11172;
                    phoneguytalkingconst = 11172;
                    sample = 4;
                }
                if (night == 2) {
                    phoneguytalking = 5544;
                    phoneguytalkingconst = 5544;
                    sample = 5;
                }
                if (night == 3) {
                    phoneguytalking = 5040;
                    phoneguytalkingconst = 5040;
                    sample = 6;
                }
                if (night == 4) {
                    phoneguytalking = 3762;
                    phoneguytalkingconst = 3762;
                    sample = 7;
                }
                if (night == 5) {
                    phoneguytalking = 3036;
                    phoneguytalkingconst = 3036;
                    sample = 8;
                }
                if (night == 6) {
                    phoneguytalking = 3180;
                    phoneguytalkingconst = 3180;
                    sample = 9;
                }
                filter.chan = soundBank.samples[sample].channel;
                filter.file = soundBank.samples[sample].file;
                CdControlF(CdlSetfilter, (u_char *)&filter);
                soundBank.samples[sample].cursor = 0;
            }
            if (phoneguytalking > 0) {phoneguytalking--;}
            if (phoneguytalking == 1) {
              sample = 0;
              CdControlF(CdlPause,0);
              enablephoneguy = 0;
            }

            if (cooldowncamera > 0) {cooldowncamera--;}
            if (cooldowncamera == 5 && camera == 1) {SpuSetKey(SPU_ON, SPU_17CH);}

            if (phoneguytalkingconst - 1620 < phoneguytalking && mutedcall == 0 && enablephoneguy == 1) {

              polymutecall = (POLY_FT4 *)nextpri;                 
                      
              RotMatrix(&RotVectormutecall, &PolyMatrixmutecall);    
              TransMatrix(&PolyMatrixmutecall, &MovVectormutecall);  
              ScaleMatrix(&PolyMatrixmutecall, &ScaleVectormutecall);
              
              SetRotMatrix(&PolyMatrixmutecall);                  
              SetTransMatrix(&PolyMatrixmutecall);                
              
              setClut(polymutecall, 256, 505);
  
                    setRGB0(polymutecall, 128, 128, 128); 

              setPolyFT4(polymutecall);                           
              
              polymutecall->tpage = getTPage(mutecall.mode&0x3, 0, 960, 0); 
              
              
              RotTransPers4(
                          &VertPosmutecall[0],      &VertPosmutecall[1],      &VertPosmutecall[2],      &VertPosmutecall[3],
                          (long*)&polymutecall->x0, (long*)&polymutecall->x1, (long*)&polymutecall->x2, (long*)&polymutecall->x3,
                          &polydepth,
                          &polyflag
                          );                               
              
              setUV4(polymutecall, 0, 189, 0, 216, 121, 189, 121, 216); // 8 diff (normaly 263 but can't go higher than 255, so 263-255 = 8)
                  
              addPrim(ot[db], polymutecall);                       
              
              nextpri += sizeof(POLY_FT4);    
            }

            if (maintenancepanel == true) {
                makepoly(7);
                if (spritemaintenancepanelgo == true && spritemaintenancepanel < 6) {

                    if (spritesheet == 1) {
                        switch(spritemaintenancepanel) {
                            case 0:
                                clearVRAMmaintenancepanel();
                                LoadTexture(_binary_tim_office_panelsprite_PANEL3_tim_start, &panel);
                            break;
                            case 2:
                                clearVRAMmaintenancepanel();
                                LoadTexture(_binary_tim_office_panelsprite_PANEL2_tim_start, &panel);
                            break;
                            case 4:
                                clearVRAMmaintenancepanel();
                                LoadTexture(_binary_tim_office_panelsprite_PANEL1_tim_start, &panel);
                            break;
                            case 6:
                                LoadTexture(_binary_tim_office_panelsprite_PANEL0_tim_start, &panel);
                                spritemaintenancepanelgo = false;
                            break;
                        } 

                    }     

                    if (spritesheetpanel != 0) {spritesheetpanel--;} else {spritesheetpanel = 4; spritemaintenancepanel++;}

                }

                if (spritemaintenancepanel == 6) {
                    if ((pad & PADLdown || pad >> 16 & PADLdown && twoplayermode == 1) && timerepairing == 0 && limiterpanel == 0) {
                        if (maintenancepanelselection < 4) {
                            maintenancepanelselection++;
                        } else {
                            maintenancepanelselection = 0;
                        }
                        SpuSetKey(SPU_ON, SPU_03CH);
                        limiterpanel++;
                    } 

                    if ((pad & PADLup || pad >> 16 & PADLup && twoplayermode == 1) && timerepairing == 0 && limiterpanel == 0) {
                        if (maintenancepanelselection > 0) {
                            maintenancepanelselection--;
                        } else {
                            maintenancepanelselection = 4;
                        }
                        SpuSetKey(SPU_ON, SPU_03CH);
                        limiterpanel++;
                    } 

                    if (!(pad & PADLdown || pad >> 16 & PADLdown && twoplayermode == 1) && !(pad & PADLup || pad >> 16 & PADLup && twoplayermode == 1)) {limiterpanel = 0;}

                    if ((pad & PADRdown || pad >> 16 & PADRdown && twoplayermode == 1) && timerepairing == 0) {
                        if (maintenancepanelselection != 4) {SpuSetKey(SPU_ON, SPU_18CH);}
                        switch (maintenancepanelselection) {
                            case 0:
                                timerepairing = 300;
                                MovVectormaintenance_loadco.vy = -3;
                            break;      

                            case 1:
                                timerepairing = 300;
                                MovVectormaintenance_loadco.vy = 5;
                            break; 

                            case 2:
                                timerepairing = 300; // 5 seconds
                                MovVectormaintenance_loadco.vy = -2;
                            break; 

                            case 3:
                                timerepairing = 540; // 9 seconds
                                MovVectormaintenance_loadco.vy = 14;
                            break; 

                            case 4:
                                maintenancepanel = false;
                            break; 
                        } 
                    }
                }
            }
            if (maintenancepanel == false && spritemaintenancepanelgo == true) {

                if (spritesheet == 0) {
                    switch(spritemaintenancepanel) {
                        case 0:
                            spritemaintenancepanelgo = false;
                        break;
                        case 2:
                            clearVRAMmaintenancepanel();
                            LoadTexture(_binary_tim_office_panelsprite_PANEL3_tim_start, &panel);
                        break;
                        case 4:
                            clearVRAMmaintenancepanel();
                            LoadTexture(_binary_tim_office_panelsprite_PANEL2_tim_start, &panel);
                        break;
                        case 6:
                            clearVRAMmaintenancepanel();
                            LoadTexture(_binary_tim_office_panelsprite_PANEL1_tim_start, &panel);
                        break;
                    }
                }

                if (spritesheetpanel != 0 && spritemaintenancepanel != 1) {spritesheetpanel--;} else {spritesheetpanel = 4; spritemaintenancepanel--;}

            }

            if (timerepairing > 0) {timerepairing--;}

            if (timerepairing % 60 == 0 && timerepairing > 0) {SpuSetKey(SPU_ON, SPU_18CH);}
            if (timerepairing % 30 == 0) {if (reloadingframe < 4) {reloadingframe++;} else {reloadingframe = 0;}}

            if (camera == 0) {
                makepoly(6);

                if (dead == 0 && fivetosixamframes == 0 && maintenancepanel == false) {

                    if (pad & PADRdown || pad >> 16 & PADRdown && twoplayermode == 1) {speedoffice = 6;} else {speedoffice = 3;}

                    if(pad & PADLleft || pad >> 16 & PADLleft && twoplayermode == 1) {
                        if (MovVectorofficemiddle.vx < 100) {
                            MovVectorofficemiddle.vx = MovVectorofficemiddle.vx + speedoffice;
                        }
                    } // left ;)
                    if(pad & PADLright || pad >> 16 & PADLright && twoplayermode == 1) {
                        if (MovVectorofficemiddle.vx > -50) {
                            MovVectorofficemiddle.vx = MovVectorofficemiddle.vx - speedoffice;
                        } else {
                            MovVectorofficemiddle.vx = -50;
                        }
                    } // right :) 
                }
            }
            if (camera == 1) {     
              if (fivetosixamframes == 0) {

                  //camera's grey or green
                  polycamgreyogreen = (POLY_F4 *)nextpri;     
                          
                  RotMatrix(&RotVectorpolycamgreyogreen, &PolyMatrixpolycamgreyogreen);    
                  TransMatrix(&PolyMatrixpolycamgreyogreen, &MovVectorpolycamgreyogreen);
                  ScaleMatrix(&PolyMatrixpolycamgreyogreen, &ScaleVectorpolycamgreyogreen);  
                  
                  SetRotMatrix(&PolyMatrixpolycamgreyogreen);            
                  SetTransMatrix(&PolyMatrixpolycamgreyogreen);          
                  
                  setPolyF4(polycamgreyogreen);                          
                  
                  RotTransPers4(
                              &VertPospolycamgreyogreen[0],      &VertPospolycamgreyogreen[1],      &VertPospolycamgreyogreen[2],      &VertPospolycamgreyogreen[3],
                              (long*)&polycamgreyogreen->x0, (long*)&polycamgreyogreen->x1, (long*)&polycamgreyogreen->x2, (long*)&polycamgreyogreen->x3,
                              &polydepth,
                              &polyflag
                              );                               

                  addPrim(ot[db], polycamgreyogreen);        

                  setRGB0(polycamgreyogreen, 157, 184, 3);    
                  
                  nextpri += sizeof(POLY_F4);                
     
                  //Layout                
                  polylayout = (POLY_FT4 *)nextpri;              
                          
                  RotMatrix(&RotVectorlayout, &PolyMatrixlayout);
                  TransMatrix(&PolyMatrixlayout, &MovVectorlayout);  
                  ScaleMatrix(&PolyMatrixlayout, &ScaleVectorlayout);
                  
                  SetRotMatrix(&PolyMatrixlayout);                   
                  SetTransMatrix(&PolyMatrixlayout);                 
                  
                  setPolyFT4(polylayout);                     
                  setClut(polylayout,960,196);       
                  
                  polylayout->tpage = getTPage(layout.mode&0x3, 0, 640, 0); 
                  
                  if (fivetosixamframes == 0) {
                    setRGB0(polylayout, 128, 128, 128);    
                  }     
                  
                  RotTransPers4(
                              &VertPoslayout[0],      &VertPoslayout[1],      &VertPoslayout[2],      &VertPoslayout[3],
                              (long*)&polylayout->x0, (long*)&polylayout->x1, (long*)&polylayout->x2, (long*)&polylayout->x3,
                              &polydepth,
                              &polyflag
                              );                               
                  
                  setUV4(polylayout, 0, 0, 0, 229, 229, 0, 229, 229);  
                      
                  addPrim(ot[db], polylayout);                  
                  
                  nextpri += sizeof(POLY_FT4);  
                }  
            }

             if (blinkicon < 61) {blinkicon++;}
             if (blinkicon == 60) {blinkicon = 0;}

             if (triggeralarm == 1 && nightwon == 0) {
               if (alarmcooldown < 1) {
                 SpuSetKey(SPU_ON, SPU_11CH);
                 alarmcooldown = 30;
               } else {
                 alarmcooldown--;
               }
             }

             if (BBlolonce && nightwon == 0) {
                 Ran(10);
                 if (RAN < 5) {
                         SpuSetKey(SPU_ON, SPU_13CH);
                 } else {
                         SpuSetKey(SPU_ON, SPU_14CH);
                 }
                 BBlolonce = 0;
             }

             //Don't know any other ways to store that piece of (shit) code
             //PATH


        }//Gameplay Screen
        if (menu == 3) { //Game over screen. ALWAYS BEGIN WITH THE STATIC
            if (staticframes > 1) {
                makepoly(15);
                if (staticframessheet == 8) {
                    staticframessheet = 0;
                    MovVectorstatic.vx = MovVectorstatic.vx - 16;
                } else {
                    MovVectorstatic.vx = MovVectorstatic.vx + 2;
                }
                if (staticframessheet == 0) {
                }
            }
            if (staticframes == 259) {
                SpuSetKey(SPU_OFF, SPU_ALLCH);
            }
            if (staticframes == 2) {
              CdControlF(CdlPause,0);
              sample = 0;
            }
            if (staticframes < 1) {
                seedrandom++; //While testing Freddy, I realized that he took a very long time to CUM. So I put that to prevent having the same seed. Thank you, Freddy, for CUMING very lately (incrementing does not necessarily means taking longer to CUM)

                gameoverprint();

                makepoly(12);

                if (pad & PADstart) {
                    resetgame(0);
                    menu = 1;
                }
            } else{staticframes--;}
        }//Game over screen. ALWAYS BEGIN WITH THE STATIC
        FntFlush(-1); //Draw
        display(); //Always here        
    }
    return 0;
}
void timeFunc(void) {
    if (onesecondvar == 0) {
        onesecondvar = 60;
    } else {onesecondvar--;}
      FrameCounter++;

      seedrandom = seedrandom + FrameCounter + camera; // This gonna be huge //camera for additional random
      srand(seedrandom);

      Glitch++;
      Glitch = Glitch + 3 * 8;
      if (Glitch > 1987) {Glitch = Glitch - 987;}

      if (FrameCounter == FrameCounterlimit) {
          AM++;
          if (AM == 13) {
              AM = 1;
          }
          FrameCounter = 0;
      }
      if (fanframes > 3) {fanframes = 0;} else {fanframes++;}
}
void resetgame(int hardreset) {
  if (debugging == 0) {
    if (hardreset == 1) {
      freddydifficulty = 0;
      bonniedifficulty = 0;
      chicadifficulty = 0;
      foxydifficulty = 0;
      BBdifficulty = 0;
      toyfreddydifficulty = 0;
      toybonniedifficulty = 0;
      toychicadifficulty = 0;
      mangledifficulty = 0;
      GFdifficulty = 0;
      puppetdifficulty = 0;

    }
      freddylocation = 0;
      bonnielocation = 0;
      chicalocation = 0;
      foxylocation = 0;
      toyfreddylocation = 0;
      toybonnielocation = 0;
      toychicalocation = 0;
      manglelocation = 0;
      BBlocation = 0;
      puppetlocation = 0;

    GFactivated = 0;
    GFnotactivatedyet = 0;
    GFactivatedhallway = 0;
    GFscreamerhallway = 0;
    fadeGF = 128;

    officefadingout = 1;
  }
    if (enablephoneguystr[1] == 'N') {enablephoneguy = 1;}

    foxyalterablevalue = 0;

    triggeralarm = 0;

    camera = 0;
    curcam[0] = '0';
    curcam[1] = '9';

    noisefootstep = 0;
    framenoisefootstep = 0;

    fivesecondframe = 300;

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

    deadtoybonnie = 0;
    dead = 0;
    deadfrom = 0;
    spriteframesconst = 4;

    fadeoffice = 128;

    nightwon = 0;
    nextnightframes = 0;
    staticframessheet = 0;
    MovVectorstatic.vx = -40;

    staticframes = 300;

    ventbanging = 0;
    ventbangingframes = 0;

    AM = 12;
    FrameCounter = 0;

    isingame = 0;

    mutedcall = 0;
}
void print(int number) {
    if (camera == 0) {
        if (number == 1) { //Basic debug (without access to camera)
            FntPrint("AM : %d, current RAN : %d", AM, RAN);  // print time

            FntPrint("\n\nphoneguytalking %d, ambiancechance %d, fivesecondframe %d", phoneguytalking, ambiancechance, fivesecondframe); //print cam     
        }
    }
    if (number == 3) { //Vanilla debug (with access to camera)
        if (camera == 0) {
            FntPrint("\n");
        }
        FntPrint("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");  // For the text to go bottom LOL

        FntPrint("%d AM \n, pos %d, console %d \n", AM, MovVectorofficemiddle.vx, spritemaintenancepanel);  // print time
        FntPrint("Night %d \n", night);
    }
    if (camera == 1 && number != 2) {
        FntPrint("Camera :               %s,%s", curcam, curcamname);  // print time
    }
    if (number == 2) { // OLD Animatronic debug (with access to camera)
        FntPrint("%d AM, IAD %d, RAN %d\n",AM, isalreadydead, RAN);
        FntPrint("OLD FlocFrame %d & location %d,",freddylocationframe, freddylocation);
        FntPrint("\nBLocFrame %d & location %d,", bonnielocationframe, bonnielocation);
        FntPrint("\nCLocFrame %d & location %d,\nFOlocFrame %d & location %d.",chicalocationframe, chicalocation, foxylocationframe, foxylocation);
        FntPrint("\nFoxy : alterval %d, flashcount %d, fattackcount %d", foxyalterablevalue, flashlightcounter, foxyattackcounter);
        FntPrint("\nGF : Hlw %d, SCRhlw %d, OFFICE %d, notyet %d", GFactivatedhallway, GFscreamerhallway, GFactivated, GFnotactivatedyet);
        FntPrint("\nOLD AI F %d, B %d, C %d,Fo %d.\nTOY AI F %d, B %d, C %d, M %d.",freddydifficulty, bonniedifficulty, chicadifficulty, foxydifficulty, toyfreddydifficulty, toybonniedifficulty, toychicadifficulty, mangledifficulty);
    }
    if (number == 4) { // TOY Animatronic debug (with access to camera)
        FntPrint("%d AM, IAD %d, RAN %d, pos %d\n",AM, isalreadydead, RAN,MovVectorofficemiddle);
        FntPrint("TOY TFlocFrame %d & loc %d,",toyfreddylocationframe, toyfreddylocation);
        FntPrint("\nTBLocFrame %d & loc %d %d,", toybonnielocationframe, toybonnielocation, toybonnieframevent);
        FntPrint("\nTCLocFrame %d & loc %d,\nMlocFrame %d & loc %d. Mattack %d\n",toychicalocationframe, toychicalocation, manglelocationframe, manglelocation, mangleattack);
        FntPrint("BBLocFrame %d & loc %d sound %d %d\n",BBlocationframe, BBlocation, ambiancesound, ambiancechance);
        FntPrint("OLD AI F %d, B %d, C %d,Fo %d.\nTOY AI F %d, B %d, C %d, M %d.",freddydifficulty, bonniedifficulty, chicadifficulty, foxydifficulty, toyfreddydifficulty, toybonniedifficulty, toychicadifficulty, mangledifficulty);
    }
}
void printNightInfo(void) { //print night information (1st, 2nd, 3rd, etc)
    if (demisecondframe > 14) {
        if (customnightactivated == 1) {FntPrint("\n\n             Custom night");}  // debug time
        if (activatedmenudebug == 1) {FntPrint("\n\n              Debug Mode");}  // debug time
        if (cheating == 1) {FntPrint("\n\n            Cheat Activate");}  // cheat time
    }
}
void menuselectionfunc(void) { //LONG asf lmaoo
    if (pad & PADLup) {
        if (limiterpadup == 0) {
            if (menuselection > 1) {
                menuselection--;
            }
            else {
                menuselection = menuselectionmax;
            }
            SpuSetKey(SPU_ON, SPU_03CH);
            limiterpadup = 1;
        }
    }
    if (pad & PADLdown) {
        if (limiterpaddown == 0) {
            if (menuselection < menuselectionmax) {
                menuselection++;
            }
            else {
                menuselection = 1;
            }
            SpuSetKey(SPU_ON, SPU_03CH);
            limiterpaddown = 1;
        }
    }
    if (!(pad & PADLright)) {limiterpadright = 0;}
    if (!(pad & PADLleft)) {limiterpadleft = 0;}
    if (!(pad & PADLdown)) {limiterpaddown = 0;}
    if (!(pad & PADLup)) {limiterpadup = 0;}
    if (!(pad & PADstart)) {limiterstart = 0;}
    if (!(pad & PADRdown)) {limiterbuttondown = 0;}
    if (menuselection == 1) {
        MovVectormenuselectionbutton.vy = 3;
    }
    if (menuselection == 2) {
       MovVectormenuselectionbutton.vy = 17;
    }
    if (menuselection == 3) {
       MovVectormenuselectionbutton.vy = 30;
    }
    if (menuselection == 4) {
       MovVectormenuselectionbutton.vy = 42;
    }

    if (maincustomnightmenu == 0 && extramenu == 0 && infoscreen == 0 && unlockssubmenu == 0 && AISetmenu == 0 && timermenu == 0) {  
        if (isingame) {
            if (menuselection == 1) {//Continue night
                if (pad & PADstart) {
                    menu = 2;
                    returnedingame = 1;
                } 
            }

            if (menuselection == 2) {//Abandon night
                if (pad & PADstart && limiterstart == 0) {
                    resetgame(0);
                    limiterstart++;
                    menuselection = 3;
                    if (activatedmenudebug == 0) {menuselectionmax = 4;} else {menuselectionmax = 5;}
                    
                } 
            }
        } else {
            if (menuselection == 1) {//"Starting" night
                if (pad & PADstart) {
                    night = 1;
                    helpwantedposter = 1;
                } 
            }

            if (menuselection == 2) { //Continue nights
                if (pad & PADstart) {
                loadingframe = 360;             
                menu = 1;
                }//Or...
                if (pad & PADRup && pad & PADRright && pad & PADR1 && pad & PADL2 && activatedmenudebug == 0) //Activate debug !
                {
                    activatedmenudebug = 1;
                    menuselectionmax = menuselectionmax + 1;
                }
            }

            if (menuselection == 3) { //EXTRA MENU
                if (pad & PADstart) {
                    if (limiterstart == 0) {
                        extramenu = 1;
                        menuselection = 1;
                        limiterstart++;
                        if (activatedmenudebug == 0) {
                            menuselectionmax = 5;
                        }
                        if (activatedmenudebug == 1) {
                            menuselectionmax = 6;
                        }
                    }
                }
            }
            if (menuselection == 4) { //CUSTOM NIGHT MENU
                if (pad & PADstart) {
                    if (limiterstart == 0) {
                        maincustomnightmenu = 1;
                        menuselection = 1;
                        menuselectionmax = 5;
                        limiterstart++;
                    }
                }
            }

            if (activatedmenudebug == 1) {
                if (menuselection == 5) {
                    if (pad & PADLright) {
                        if (limiterpadright == 0) {
                            printnumber++;
                            if (printnumber > 4) {printnumber = 1;}
                            limiterpadright = 1;
                        }
                    }
                    if (pad & PADLleft) {
                        if (limiterpadleft == 0) {
                            printnumber--;
                            if (printnumber < 1) {printnumber = 4;}
                            limiterpadleft = 1;
                        }
                    }
                }
            }
        }
    }

    if (maincustomnightmenu == 1) {
        if (menuselection == 1) {
            if (pad & PADLright) {
                if (limiterpadright == 0) {
                    night++;
                    if (night > 6) {night = 1;}
                    limiterpadright = 1;
                }
            }
            if (pad & PADLleft) {
                if (limiterpadleft == 0) {
                    night--;
                    if (night < 1) {night = 6;}
                    limiterpadleft = 1;
                }
            } //Change night's var
        }

        if (menuselection == 2) { // AI SET MENU
            if (pad & PADstart) {
                if (limiterstart == 0) {
                    maincustomnightmenu = 0;
                    AISetmenu = 1;
                    menuselection = 7;
                    menuselectionmax = 7;
                    limiterstart = 1;
                }
            }
        }
        if (menuselection == 3) { // TIMER ETC MENU
            if (pad & PADstart) {
                if (limiterstart == 0) {
                    maincustomnightmenu = 0;
                    timermenu = 1;
                    menuselection = 5;
                    menuselectionmax = 5;
                    limiterstart = 1;
                }
            }
        }
        if (menuselection == 4) { // LAUNCH NIGHT
            if (pad & PADstart) {
              if (limiterstart == 0) {
                menu = 1;
                customnightactivated = 1;
              }
            }
        }
        if (menuselection == 5) { // RETURN TO MAIN MENU
            if (pad & PADstart) {
                if (limiterstart == 0)  {
                    maincustomnightmenu = 0;
                    menuselection = 4;
                    limiterstart++;
                    if (activatedmenudebug == 0) {menuselectionmax = 4;}
                    else {menuselectionmax = 5;}
                }
            }
        }
    }
    if (AISetmenu == 1) {
        if (animatronicategorie == 1) {
            if (menuselection == 1) {
                if (pad & PADLright) { //Freddy
                    if (limiterpadright == 0) {
                        freddydifficulty++;
                        if (freddydifficulty > 20) {freddydifficulty = 0;}
                        limiterpadright = 1;
                        SpuSetKey(SPU_ON, SPU_08CH);
                    }
                }
                if (pad & PADLleft) { //Freddy
                    if (limiterpadleft == 0) {
                        freddydifficulty--;
                        if (freddydifficulty < 0) {freddydifficulty = 20;}
                        limiterpadleft = 1;
                        SpuSetKey(SPU_ON, SPU_08CH);
                    }
                }
            }
            if (menuselection == 2) {
                if (pad & PADLright) { //Bonnie
                    if (limiterpadright == 0) {
                        bonniedifficulty++;
                        if (bonniedifficulty > 20) {bonniedifficulty = 0;}
                        limiterpadright = 1;
                        SpuSetKey(SPU_ON, SPU_08CH);
                    }
                }
                if (pad & PADLleft) { //Bonnie
                    if (limiterpadleft == 0) {
                        bonniedifficulty--;
                        if (bonniedifficulty < 0) {bonniedifficulty = 20;}
                        limiterpadleft = 1;
                        SpuSetKey(SPU_ON, SPU_08CH);
                    }
                }
            }
            if (menuselection == 3) {
                if (pad & PADLright) { //Chica
                    if (limiterpadright == 0) {
                        chicadifficulty++;
                        if (chicadifficulty > 20) {chicadifficulty = 0;}
                        limiterpadright = 1;
                        SpuSetKey(SPU_ON, SPU_08CH);
                    }
                }
                if (pad & PADLleft) { //Chica
                    if (limiterpadleft == 0) {
                        chicadifficulty--;
                        if (chicadifficulty < 0) {chicadifficulty = 20;}
                        limiterpadleft = 1;
                        SpuSetKey(SPU_ON, SPU_08CH);
                    }
                }
            }
            if (menuselection == 4) {
                if (pad & PADLright) { //Foxy
                    if (limiterpadright == 0) {
                        foxydifficulty++;
                        if (foxydifficulty > 20) {foxydifficulty = 0;}
                        limiterpadright = 1;
                        SpuSetKey(SPU_ON, SPU_08CH);
                    }
                }
                if (pad & PADLleft) { //Foxy
                    if (limiterpadleft == 0) {
                        foxydifficulty--;
                        if (foxydifficulty < 0) {foxydifficulty = 20;}
                        limiterpadleft = 1;
                        SpuSetKey(SPU_ON, SPU_08CH);
                    }
                }
            }
        }

        if (animatronicategorie == 2) {
            if (menuselection == 1) {
                if (pad & PADLright) { //Toy Freddy
                    if (limiterpadright == 0) {
                        toyfreddydifficulty++;
                        if (toyfreddydifficulty > 20) {toyfreddydifficulty = 0;}
                        limiterpadright = 1;
                        SpuSetKey(SPU_ON, SPU_08CH);
                    }
                }
                if (pad & PADLleft) { //Toy Freddy
                    if (limiterpadleft == 0) {
                        toyfreddydifficulty--;
                        if (toyfreddydifficulty < 0) {toyfreddydifficulty = 20;}
                        limiterpadleft = 1;
                        SpuSetKey(SPU_ON, SPU_08CH);
                    }
                }
            }
            if (menuselection == 2) {
                if (pad & PADLright) { //Toy Bonnie
                    if (limiterpadright == 0) {
                        toybonniedifficulty++;
                        if (toybonniedifficulty > 20) {toybonniedifficulty = 0;}
                        limiterpadright = 1;
                        SpuSetKey(SPU_ON, SPU_08CH);
                    }
                }
                if (pad & PADLleft) { //Toy Bonnie
                    if (limiterpadleft == 0) {
                        toybonniedifficulty--;
                        if (toybonniedifficulty < 0) {toybonniedifficulty = 20;}
                        limiterpadleft = 1;
                        SpuSetKey(SPU_ON, SPU_08CH);
                    }
                }
            }
            if (menuselection == 3) {
                if (pad & PADLright) { //Toy Chica
                    if (limiterpadright == 0) {
                        toychicadifficulty++;
                        if (toychicadifficulty > 20) {toychicadifficulty = 0;}
                        limiterpadright = 1;
                        SpuSetKey(SPU_ON, SPU_08CH);
                    }
                }
                if (pad & PADLleft) { //Toy Chica
                    if (limiterpadleft == 0) {
                        toychicadifficulty--;
                        if (toychicadifficulty < 0) {toychicadifficulty = 20;}
                        limiterpadleft = 1;
                        SpuSetKey(SPU_ON, SPU_08CH);
                    }
                }
            }
            if (menuselection == 4) {
                if (pad & PADLright) { //Toy Foxy (mangle)
                    if (limiterpadright == 0) {
                        mangledifficulty++;
                        if (mangledifficulty > 20) {mangledifficulty = 0;}
                        limiterpadright = 1;
                        SpuSetKey(SPU_ON, SPU_08CH);
                    }
                }
                if (pad & PADLleft) { //Toy Foxy (mangle)
                    if (limiterpadleft == 0) {
                        mangledifficulty--;
                        if (mangledifficulty < 0) {mangledifficulty = 20;}
                        limiterpadleft = 1;
                        SpuSetKey(SPU_ON, SPU_08CH);
                    }
                }
            }
        }

        if (animatronicategorie == 3) {
            if (menuselection == 1) {
                if (pad & PADLright) { //BB
                    if (limiterpadright == 0) {
                        BBdifficulty++;
                        if (BBdifficulty > 20) {BBdifficulty = 0;}
                        limiterpadright = 1;
                        SpuSetKey(SPU_ON, SPU_10CH);
                    }
                }
                if (pad & PADLleft) { //BB
                    if (limiterpadleft == 0) {
                        BBdifficulty--;
                        if (BBdifficulty < 0) {BBdifficulty = 20;}
                        limiterpadleft = 1;
                        SpuSetKey(SPU_ON, SPU_10CH);
                    }
                }
            }
            if (menuselection == 2) {
                if (pad & PADLright) { //Golden Freddy
                    if (limiterpadright == 0) {
                        GFdifficulty++;
                        if (GFdifficulty > 20) {GFdifficulty = 0;}
                        limiterpadright = 1;
                        SpuSetKey(SPU_ON, SPU_10CH);
                    }
                }
                if (pad & PADLleft) { //Golden Freddy
                    if (limiterpadleft == 0) {
                        GFdifficulty--;
                        if (GFdifficulty < 0) {GFdifficulty = 20;}
                        limiterpadleft = 1;
                        SpuSetKey(SPU_ON, SPU_10CH);
                    }
                }
            }
            if (menuselection == 3) {
                if (pad & PADRdown) { //Character level up ?
                    if (limiterbuttondown == 0) {
                      if (doescharlevelup == 0) {
                        doescharlevelup = 1;
                        doescharlevelupstr[0] = 'O';
                        doescharlevelupstr[1] = 'n';
                        doescharlevelupstr[2] = ' ';
                      } else {
                        doescharlevelup = 0;
                        doescharlevelupstr[0] = 'O';
                        doescharlevelupstr[1] = 'f';
                        doescharlevelupstr[2] = 'f';
                      }
                      limiterbuttondown = 1;
                        SpuSetKey(SPU_ON, SPU_10CH);
                    }
                }
            }
        }

        if (menuselection == 5) {
            if (pad & PADLleft) {
                if (limiterpadleft == 0) {
                    animatronicategorie--;
                    if (animatronicategorie < 1) {animatronicategorie = 1;}
                    limiterpadleft = 1;
                }
            }
            if (pad & PADLright) {
                if (limiterpadright == 0) {
                    animatronicategorie++;
                    if (animatronicategorie > 3) {animatronicategorie = 3;}
                    limiterpadright = 1;
                }
            }
        }

        if (menuselection == 6) {
            if (pad & PADLleft) {
                if (limiterpadleft == 0) {
                    presetselector--;
                    if (presetselector < 1) {presetselector = 16;}
                    limiterpadleft = 1;
                }
                SpuSetKey(SPU_ON, SPU_10CH);
            }
            if (pad & PADLright) {
                if (limiterpadright == 0) {
                    presetselector++;
                    if (presetselector > 16) {presetselector = 1;}
                    limiterpadright = 1;
                }
                SpuSetKey(SPU_ON, SPU_10CH);
            }
        }

        if (menuselection == 7) {
            if (pad & PADstart) {
                if (limiterstart == 0) {
                    maincustomnightmenu = 1;
                    AISetmenu = 0;
                    menuselection = 2;
                    menuselectionmax = 5;
                    limiterstart++;
                }
            }
        }
        if (presetselector == 1) {
            presetselectorstr[0] = 'C';
            presetselectorstr[1] = 'u';
            presetselectorstr[2] = 's';
            presetselectorstr[3] = 't';
            presetselectorstr[4] = 'o';
            presetselectorstr[5] = 'm';
            presetselectorstr[6] = ' ';
            presetselectorstr[7] = ' ';
            presetselectorstr[8] = ' ';
            presetselectorstr[9] = ' ';
            presetselectorstr[10] = ' ';
            presetselectorstr[11] = ' ';
            presetselectorstr[12] = ' ';

            puppetdifficulty = 15;
        }
        if (presetselector > 1 && presetselector < 7) {
            presetselectorstr[0] = 'N';
            presetselectorstr[1] = 'i';
            presetselectorstr[2] = 'g';
            presetselectorstr[3] = 'h';
            presetselectorstr[4] = 't';
            presetselectorstr[5] = ' ';
            if (presetselector == 2) {
                presetselectorstr[6] = '2';
                freddydifficulty = 0;
                bonniedifficulty = 0;
                chicadifficulty = 0;
                foxydifficulty = 1;
                puppetdifficulty = 5;
                toyfreddydifficulty = 2;
                toybonniedifficulty = 3;
                toychicadifficulty = 3;
                mangledifficulty = 3;
                BBdifficulty = 3;
                GFdifficulty = 0;
                doescharlevelup = 1;

                doescharlevelupstr[0] = 'O';
                doescharlevelupstr[1] = 'N';
                doescharlevelupstr[2] = ' ';
            }
            if (presetselector == 3) {
                presetselectorstr[6] = '3';
                freddydifficulty = 0;
                bonniedifficulty = 1;
                chicadifficulty = 1;
                foxydifficulty = 2;
                puppetdifficulty = 8;
                toyfreddydifficulty = 0;
                toybonniedifficulty = 0;
                toychicadifficulty = 0;
                mangledifficulty = 0;
                BBdifficulty = 1;
                GFdifficulty = 0;
                doescharlevelup = 1;
                doescharlevelupstr[0] = 'O';
                doescharlevelupstr[1] = 'N';
                doescharlevelupstr[2] = ' ';
            }
            if (presetselector == 4) {
                presetselectorstr[6] = '4';
                freddydifficulty = 0;
                bonniedifficulty = 1;
                chicadifficulty = 0;
                foxydifficulty = 7;
                puppetdifficulty = 9;
                toyfreddydifficulty = 0;
                toybonniedifficulty = 0;
                toychicadifficulty = 0;
                mangledifficulty = 5;
                BBdifficulty = 3;
                GFdifficulty = 0;
                doescharlevelup = 1;
                doescharlevelupstr[0] = 'O';
                doescharlevelupstr[1] = 'N';
                doescharlevelupstr[2] = ' ';
            }
            if (presetselector == 5) {
                presetselectorstr[6] = '5';
                freddydifficulty = 2;
                bonniedifficulty = 2;
                chicadifficulty = 2;
                foxydifficulty = 5;
                puppetdifficulty = 10;
                toyfreddydifficulty = 5;
                toybonniedifficulty = 2;
                toychicadifficulty = 2;
                mangledifficulty = 1;
                BBdifficulty = 5;
                GFdifficulty = 0;
                doescharlevelup = 1;
                doescharlevelupstr[0] = 'O';
                doescharlevelupstr[1] = 'N';
                doescharlevelupstr[2] = ' ';
            }
            if (presetselector == 6) {
                presetselectorstr[6] = '6';
                freddydifficulty = 5;
                bonniedifficulty = 5;
                chicadifficulty = 5;
                foxydifficulty = 10;
                puppetdifficulty = 15;
                toyfreddydifficulty = 0;
                toybonniedifficulty = 0;
                toychicadifficulty = 0;
                mangledifficulty = 3;
                BBdifficulty = 5;
                GFdifficulty = 0;
                doescharlevelup = 1;

                doescharlevelupstr[0] = 'O';
                doescharlevelupstr[1] = 'N';
                doescharlevelupstr[2] = ' ';
            }
        } else {
          enablephoneguy = 0;
          enablephoneguystr[0] = 'O';
          enablephoneguystr[1] = 'F';
          enablephoneguystr[2] = 'F';
        }
        if (presetselector == 7) {
            presetselectorstr[0] = '4';
            presetselectorstr[1] = '/';
            presetselectorstr[2] = '2';
            presetselectorstr[3] = '0';
            presetselectorstr[4] = ' ';
            presetselectorstr[5] = ' ';
            presetselectorstr[6] = ' ';
            presetselectorstr[7] = ' ';
            presetselectorstr[8] = ' ';
            presetselectorstr[9] = ' ';
            presetselectorstr[10] = ' ';
            presetselectorstr[11] = ' ';
            presetselectorstr[12] = ' ';
            freddydifficulty = 20;
            bonniedifficulty = 20;
            chicadifficulty = 20;
            foxydifficulty = 20;
            toyfreddydifficulty = 0;
            toybonniedifficulty = 0;
            toychicadifficulty = 0;
            mangledifficulty = 0;
            BBdifficulty = 0;
            GFdifficulty = 0;
            doescharlevelup = 0;
            doescharlevelupstr[0] = 'O';
            doescharlevelupstr[1] = 'F';
            doescharlevelupstr[2] = 'F';
        }
        if (presetselector == 8) {
            presetselectorstr[0] = 'N';
            presetselectorstr[1] = 'e';
            presetselectorstr[2] = 'w';
            presetselectorstr[3] = ' ';
            presetselectorstr[4] = 'a';
            presetselectorstr[5] = 'n';
            presetselectorstr[6] = 'd';
            presetselectorstr[7] = ' ';
            presetselectorstr[8] = 'S';
            presetselectorstr[9] = 'h';
            presetselectorstr[10] = 'i';
            presetselectorstr[11] = 'n';
            presetselectorstr[12] = 'y';
            presetselectorstr[13] = ' ';
            presetselectorstr[14] = ' ';
            freddydifficulty = 0;
            bonniedifficulty = 0;
            chicadifficulty = 0;
            foxydifficulty = 0;
            toyfreddydifficulty = 10;
            toybonniedifficulty = 10;
            toychicadifficulty = 10;
            mangledifficulty = 10;
            BBdifficulty = 10;
            GFdifficulty = 0;
            doescharlevelup = 0;
            doescharlevelupstr[0] = 'O';
            doescharlevelupstr[1] = 'F';
            doescharlevelupstr[2] = 'F';
        }
        if (presetselector == 9) {
            presetselectorstr[0] = 'D';
            presetselectorstr[1] = 'o';
            presetselectorstr[2] = 'u';
            presetselectorstr[3] = 'b';
            presetselectorstr[4] = 'l';
            presetselectorstr[5] = 'e';
            presetselectorstr[6] = ' ';
            presetselectorstr[7] = 'T';
            presetselectorstr[8] = 'r';
            presetselectorstr[9] = 'o';
            presetselectorstr[10] = 'u';
            presetselectorstr[11] = 'b';
            presetselectorstr[12] = 'l';
            presetselectorstr[13] = 'e';
            presetselectorstr[14] = ' ';
            presetselectorstr[15] = ' ';
            bonniedifficulty = 20;
            foxydifficulty = 5;
            toybonniedifficulty = 20;

            freddydifficulty = 0;
            chicadifficulty = 0;
            toyfreddydifficulty = 0;
            toychicadifficulty = 0;
            mangledifficulty = 0;
            BBdifficulty = 0;
            GFdifficulty = 0;
            doescharlevelup = 0;
            doescharlevelupstr[0] = 'O';
            doescharlevelupstr[1] = 'F';
            doescharlevelupstr[2] = 'F';
        }
        if (presetselector == 10) {
            presetselectorstr[0] = 'N';
            presetselectorstr[1] = 'i';
            presetselectorstr[2] = 'g';
            presetselectorstr[3] = 'h';
            presetselectorstr[4] = 't';
            presetselectorstr[5] = ' ';
            presetselectorstr[6] = 'o';
            presetselectorstr[7] = 'f';
            presetselectorstr[8] = ' ';
            presetselectorstr[9] = 'm';
            presetselectorstr[10] = 'i';
            presetselectorstr[11] = 's';
            presetselectorstr[12] = 'f';
            presetselectorstr[13] = 'i';
            presetselectorstr[14] = 't';
            presetselectorstr[15] = 's';
            mangledifficulty = 20;
            GFdifficulty = 10;
            BBdifficulty = 20;

            freddydifficulty = 0;
            bonniedifficulty = 0;
            chicadifficulty = 0;
            foxydifficulty = 0;
            toyfreddydifficulty = 0;
            toybonniedifficulty = 0;
            toychicadifficulty = 0;
            doescharlevelup = 0;
            doescharlevelupstr[0] = 'O';
            doescharlevelupstr[1] = 'F';
            doescharlevelupstr[2] = 'F';
        }
        if (presetselector == 11) {
            presetselectorstr[0] = 'F';
            presetselectorstr[1] = 'o';
            presetselectorstr[2] = 'x';
            presetselectorstr[3] = 'y';
            presetselectorstr[4] = ' ';
            presetselectorstr[5] = 'F';
            presetselectorstr[6] = 'o';
            presetselectorstr[7] = 'x';
            presetselectorstr[8] = 'y';
            presetselectorstr[9] = ' ';
            presetselectorstr[10] = ' ';
            presetselectorstr[11] = ' ';
            presetselectorstr[12] = ' ';
            presetselectorstr[13] = ' ';
            presetselectorstr[14] = ' ';
            presetselectorstr[15] = ' ';
            presetselectorstr[16] = ' ';
            mangledifficulty = 20;
            foxydifficulty = 20;

            freddydifficulty = 0;
            bonniedifficulty = 0;
            chicadifficulty = 0;
            toyfreddydifficulty = 0;
            toybonniedifficulty = 0;
            toychicadifficulty = 0;
            BBdifficulty = 0;
            GFdifficulty = 0;
            doescharlevelup = 0;
            doescharlevelupstr[0] = 'O';
            doescharlevelupstr[1] = 'F';
            doescharlevelupstr[2] = 'F';
        }
        if (presetselector == 12) {
            presetselectorstr[0] = 'L';
            presetselectorstr[1] = 'a';
            presetselectorstr[2] = 'd';
            presetselectorstr[3] = 'i';
            presetselectorstr[4] = 'e';
            presetselectorstr[5] = 's';
            presetselectorstr[6] = ' ';
            presetselectorstr[7] = 'N';
            presetselectorstr[8] = 'i';
            presetselectorstr[9] = 'g';
            presetselectorstr[10] = 'h';
            presetselectorstr[11] = 't';
            presetselectorstr[12] = ' ';
            presetselectorstr[13] = ' ';
            presetselectorstr[14] = ' ';
            mangledifficulty = 20;
            chicadifficulty = 20;
            toychicadifficulty = 20;

            freddydifficulty = 0;
            bonniedifficulty = 0;
            foxydifficulty = 0;
            toyfreddydifficulty = 0;
            toybonniedifficulty = 0;
            BBdifficulty = 0;
            GFdifficulty = 0;
            doescharlevelup = 0;
            doescharlevelupstr[0] = 'O';
            doescharlevelupstr[1] = 'F';
            doescharlevelupstr[2] = 'F';
        }
        if (presetselector == 13) {
            presetselectorstr[0] = 'F';
            presetselectorstr[1] = 'r';
            presetselectorstr[2] = 'e';
            presetselectorstr[3] = 'd';
            presetselectorstr[4] = 'd';
            presetselectorstr[5] = 'y';
            presetselectorstr[6] = '"';
            presetselectorstr[7] = 's';
            presetselectorstr[8] = ' ';
            presetselectorstr[9] = 'C';
            presetselectorstr[10] = 'i';
            presetselectorstr[11] = 'r';
            presetselectorstr[12] = 'c';
            presetselectorstr[13] = 'u';
            presetselectorstr[14] = 's';
            presetselectorstr[15] = ' ';
            presetselectorstr[16] = ' ';
            freddydifficulty = 20;
            toyfreddydifficulty = 20;
            foxydifficulty = 10;
            BBdifficulty = 10;
            GFdifficulty = 10;

            bonniedifficulty = 0;
            chicadifficulty = 0;
            toybonniedifficulty = 0;
            toychicadifficulty = 0;
            mangledifficulty = 0;
            doescharlevelup = 0;
            doescharlevelupstr[0] = 'O';
            doescharlevelupstr[1] = 'F';
            doescharlevelupstr[2] = 'F';
        }
        if (presetselector == 14) {
            presetselectorstr[0] = 'C';
            presetselectorstr[1] = 'u';
            presetselectorstr[2] = 'p';
            presetselectorstr[3] = 'c';
            presetselectorstr[4] = 'a';
            presetselectorstr[5] = 'k';
            presetselectorstr[6] = 'e';
            presetselectorstr[7] = ' ';
            presetselectorstr[8] = 'C';
            presetselectorstr[9] = 'h';
            presetselectorstr[10] = 'a';
            presetselectorstr[11] = 'l';
            presetselectorstr[12] = 'l';
            presetselectorstr[13] = 'e';
            presetselectorstr[14] = 'n';
            presetselectorstr[15] = 'g';
            presetselectorstr[16] = 'e';
            freddydifficulty = 5;
            bonniedifficulty = 5;
            chicadifficulty = 5;
            foxydifficulty = 5;
            toyfreddydifficulty = 5;
            toybonniedifficulty = 5;
            toychicadifficulty = 5;
            mangledifficulty = 5;
            BBdifficulty = 5;
            GFdifficulty = 5;
            doescharlevelup = 0;
            doescharlevelupstr[0] = 'O';
            doescharlevelupstr[1] = 'F';
            doescharlevelupstr[2] = 'F';
        }
        if (presetselector == 15) {
            presetselectorstr[0] = 'F';
            presetselectorstr[1] = 'a';
            presetselectorstr[2] = 'z';
            presetselectorstr[3] = 'b';
            presetselectorstr[4] = 'e';
            presetselectorstr[5] = 'a';
            presetselectorstr[6] = 'r';
            presetselectorstr[7] = ' ';
            presetselectorstr[8] = 'F';
            presetselectorstr[9] = 'e';
            presetselectorstr[10] = 'v';
            presetselectorstr[11] = 'e';
            presetselectorstr[12] = 'r';
            presetselectorstr[13] = ' ';
            presetselectorstr[14] = ' ';
            presetselectorstr[15] = ' ';
            presetselectorstr[16] = ' ';
            freddydifficulty = 10;
            bonniedifficulty = 10;
            chicadifficulty = 10;
            foxydifficulty = 10;
            toyfreddydifficulty = 10;
            toybonniedifficulty = 10;
            toychicadifficulty = 10;
            mangledifficulty = 10;
            BBdifficulty = 10;
            GFdifficulty = 10;
            doescharlevelup = 0;
            doescharlevelupstr[0] = 'O';
            doescharlevelupstr[1] = 'F';
            doescharlevelupstr[2] = 'F';
        }
        if (presetselector == 16) {
            presetselectorstr[0] = 'G';
            presetselectorstr[1] = 'o';
            presetselectorstr[2] = 'l';
            presetselectorstr[3] = 'd';
            presetselectorstr[4] = 'e';
            presetselectorstr[5] = 'n';
            presetselectorstr[6] = ' ';
            presetselectorstr[7] = 'F';
            presetselectorstr[8] = 'r';
            presetselectorstr[9] = 'e';
            presetselectorstr[10] = 'd';
            presetselectorstr[11] = 'd';
            presetselectorstr[12] = 'y';
            freddydifficulty = 20;
            bonniedifficulty = 20;
            chicadifficulty = 20;
            foxydifficulty = 20;
            toyfreddydifficulty = 20;
            toybonniedifficulty = 20;
            toychicadifficulty = 20;
            mangledifficulty = 20;
            BBdifficulty = 20;
            GFdifficulty = 20;
            doescharlevelup = 0;
            doescharlevelupstr[0] = 'O';
            doescharlevelupstr[1] = 'F';
            doescharlevelupstr[2] = 'F';
        }
    }
    if (timermenu == 1) {
        if (menuselection == 1) {
            //AM
            if (pad & PADLright) {
                if (limiterpadright == 0) {
                    customAM++;
                    if (customAM < 12 && customAM > 6) {customAM = 12;}
                    if (customAM > 12) {customAM = 0;}
                    limiterpadright = 1;
                }
            }
            if (pad & PADLleft) {
                if (limiterpadleft == 0) {
                    customAM--;
                    if (customAM < 12 && customAM > 6) {customAM = 6;}
                    if (customAM < 0) {customAM = 12;}
                    limiterpadleft = 1;
                }
            }
        }
        if (menuselection == 2) {
            //FrameCounterlimit (via the convertion var)
            if (pad & PADLright) {
                if (limiterpadright == 0) {
                    convertion++;
                    limiterpadright = 1;
                }
            }
            if (pad & PADLleft) {
                if (limiterpadleft == 0) {
                    convertion--;
                    if (convertion < 0) {convertion = 0;}
                    limiterpadleft = 1;
                }
            }
            //For quick change
            if (pad & PADR1) {
                convertion++;
            }
            if (pad & PADL1) {
                convertion--;
                if (convertion < 0) {convertion = 0;}
            }
            //For reset
            if (pad & PADstart) {
                convertion = 60;
            }
            //For 0
            if (pad & PADselect) {
                convertion = 0;
            }
            //For 120
            if (pad & PADstart && pad & PADselect) {
                convertion = 120;
            }
        }
        if (menuselection == 3) { //Old animatronic's frame lock
            if (pad & PADRright) { //Foxy 
                foxylocationframelock++;
            }
            if (pad & PADRleft) { //Foxy 
                foxylocationframelock--;
                if (foxylocationframelock < 1) {foxylocationframelock = 1;}
            }
            if (pad & PADLright) { //Freddy 
                freddylocationframelock++;
            }
            if (pad & PADLleft) { //Freddy 
                freddylocationframelock--;
                if (freddylocationframelock < 1) {freddylocationframelock = 1;}
            }
            if (pad & PADL1) { //Bonnie 
                bonnielocationframelock--;
                if (bonnielocationframelock < 1) {bonnielocationframelock = 1;}
            }
            if (pad & PADL2) { //Bonnie 
                bonnielocationframelock++;
            }
            if (pad & PADR1) { //Chica 
                chicalocationframelock--;
                if (chicalocationframelock < 1) {chicalocationframelock = 1;}
            }
            if (pad & PADR2) { //Chica 
                chicalocationframelock++;
            }
            if (pad & PADstart) {
                freddylocationframe = 300;
                bonnielocationframe = 300;
                chicalocationframe = 300;
                foxylocationframe = 300;
                freddylocationframelock = 300;
                bonnielocationframelock = 300;
                chicalocationframelock = 300;
                foxylocationframelock = 300;
            }
        }
        if (menuselection == 4) {
            if (pad & PADRright) { //Mangle 
                manglelocationframelock++;
            }
            if (pad & PADRleft) { //Foxy 
                manglelocationframelock--;
                if (manglelocationframelock < 1) {manglelocationframelock = 1;}
            }
            if (pad & PADLright) { //Freddy 
                toyfreddylocationframelock++;
            }
            if (pad & PADLleft) { //Freddy 
                toyfreddylocationframelock--;
                if (toyfreddylocationframelock < 1) {toyfreddylocationframelock = 1;}
            }
            if (pad & PADL1) { //Bonnie 
                toybonnielocationframelock--;
                if (toybonnielocationframelock < 1) {toybonnielocationframelock = 1;}
            }
            if (pad & PADL2) { //Bonnie 
                toybonnielocationframelock++;
            }
            if (pad & PADR1) { //Chica 
                toychicalocationframelock--;
                if (toychicalocationframelock < 1) {toychicalocationframelock = 1;}
            }
            if (pad & PADR2) { //Chica 
                toychicalocationframelock++;
            }
            if (pad & PADstart) {
                toyfreddylocationframe = 300;
                toybonnielocationframe = 300;
                toychicalocationframe = 300;
                manglelocationframe = 300;
                toyfreddylocationframelock = 300;
                toybonnielocationframelock = 300;
                toychicalocationframelock = 300;
                manglelocationframelock = 300;
            }
        }
        if (menuselection == 5) {
            if (pad & PADstart) {
                if (limiterstart == 0) {
                    maincustomnightmenu = 1;
                    timermenu = 0;
                    menuselection = 3;
                    menuselectionmax = 5;
                    limiterstart++;
                }
            }
        }
    }
    if (extramenu == 1) {
        if (menuselection == 1) { //Phone guy
            if (pad & PADRdown) {
                if (limiterbuttondown == 0) {
                    enablephoneguy++;
                    enablephoneguystr[0] = 'O';
                    enablephoneguystr[1] = 'N';
                    enablephoneguystr[2] = ' ';
                    if (enablephoneguy > 1) {
                        enablephoneguy = 0;
                        enablephoneguystr[0] = 'O';
                        enablephoneguystr[1] = 'F';
                        enablephoneguystr[2] = 'F';
                    }
                    limiterbuttondown = 1;
                }
            }
        }
        if (menuselection == 2) { //Unlocks menu
            if (pad & PADstart) {
                if (limiterstart == 0) {
                    extramenu = 0;
                    unlockssubmenu = 1;
                    menuselection = 1;
                    menuselectionmax = 4;
                    limiterstart = 1;
                }
            }
        }
        if (menuselection == 3) { //Informations on the game
            if (pad & PADstart) {
                if (limiterstart == 0) {
                    extramenu = 0;
                    infoscreen = 1;
                    menuselection = 1;
                    menuselectionmax = 1;
                    limiterstart = 1;
                }
            }
        }
        if (menuselection == 4) {//Two players mode
            if (pad & PADRdown) {
                if (limiterbuttondown == 0) {
                    twoplayermode++;
                    if (twoplayermode > 1) {twoplayermode = 0;}
                    
                    if (twoplayermode == 0) {
                        twoplayermodestr[1] = 'F';
                        twoplayermodestr[2] = 'F';
                    } else {
                        twoplayermodestr[1] = 'N';
                        twoplayermodestr[2] = ' ';
                    }
                    limiterbuttondown = 1;
                }
            }
        }
        if (menuselection == 5) { //Return
            if (pad & PADstart) {
                if (limiterstart == 0)  {
                    extramenu = 0;
                    menuselection = 3;
                    limiterstart++;
                    if (activatedmenudebug == 0) {menuselectionmax = 4;}
                    else {menuselectionmax = 5;}
                }
            }
        }
        if (menuselection == 6) { //Toggle Weird night
            if (pad & PADstart) {
                if (limiterstart == 0)  {
                  weirdnight = 1;
                  oldnight = night;
                  night = 725255;
                  onetime++;
                  limiterstart++;
                  menu = 1;
                }
            }
        }
        if (menuselection == 7) { //Toggle debug mode
            if (pad & PADstart) {
                if (limiterstart == 0)  {
                  debugging = 1;
                }
            }
        }
    }
    if (infoscreen == 1) {
        if (menuselection == 1) {
            if (pad & PADstart) {
                if (limiterstart == 0) {
                    extramenu = 1;
                    infoscreen = 0;
                    menuselection = 1;
                    if (activatedmenudebug == 0) {
                        menuselectionmax = 5;
                    }
                    if (activatedmenudebug == 1) {
                        menuselectionmax = 5;
                    }
                    limiterstart = 1;
                }
            }
        }
    }
    if (unlockssubmenu == 1) {
        if (menuselection == 1) {
            if (pad & PADRdown) {
                if (limiterbuttondown == 0) {
                    unlimitedpower++;
                    unlimitedpowerstr[0] = 'O';
                    unlimitedpowerstr[1] = 'N';
                    unlimitedpowerstr[2] = ' ';
                    if (unlimitedpower > 1) {
                        unlimitedpower = 0;
                        unlimitedpowerstr[0] = 'O';
                        unlimitedpowerstr[1] = 'F';
                        unlimitedpowerstr[2] = 'F';
                    }
                    cheating = 1;
                    limiterbuttondown = 1;
                }
            }
        }
        if (menuselection == 2) {
            if (pad & PADRdown) {
                if (limiterbuttondown == 0) {
                    fastnights++;
                    fastnightsstr[0] = 'O';
                    fastnightsstr[1] = 'N';
                    fastnightsstr[2] = ' ';
                    if (fastnights > 1) {
                        fastnights = 0;
                        fastnightsstr[0] = 'O';
                        fastnightsstr[1] = 'F';
                        fastnightsstr[2] = 'F';
                    }
                    cheating = 1;
                    limiterbuttondown = 1;
                }
            }
        }
        if (menuselection == 3) {
            if (pad & PADRdown) {
                if (limiterbuttondown == 0) {
                    radar++;
                    radarstr[0] = 'O';
                    radarstr[1] = 'N';
                    radarstr[2] = ' ';
                    if (radar > 1) {
                        radar = 0;
                        radarstr[0] = 'O';
                        radarstr[1] = 'F';
                        radarstr[2] = 'F';
                    }
                    cheating = 1;
                    limiterbuttondown = 1;
                }
            }
        }
        if (menuselection == 4) {
            if (pad & PADstart) {
                if (limiterstart == 0) {
                    extramenu = 1;
                    unlockssubmenu = 0;
                    menuselection = 1;
                    if (activatedmenudebug == 0) {
                        menuselectionmax = 5;
                    }
                    if (activatedmenudebug == 1) {
                        menuselectionmax = 6;
                    }
                    limiterstart = 1;
                }
            }
        }
    }
}
void menuPrint(void) {
    FntPrint("\n\n\n\n\n\n\n\n\n\n\n\n");  // print time
    if (maincustomnightmenu == 0 && extramenu == 0 && infoscreen == 0 && unlockssubmenu == 0 && AISetmenu == 0 && timermenu == 0) {
        if (isingame) {
            makepoly(1);/*
            FntPrint("   Five\n\n   Nights\n\n   at\n\n   Freddy's\n\n   2 \n\n   Pause Menu\n\n\n");  // print time

            if (menuselection == 1) {FntPrint(">> Continue Night %d\n\n", night);}
            else {FntPrint("   Continue Night %d\n\n", night);}

            if (menuselection == 2) {FntPrint(">> Abandon The Night \n\n");}
            else {FntPrint("   Abandon The Night \n\n");}*/
        }/* else {

            FntPrint("   Five\n\n   Nights\n\n   at\n\n   Freddy's\n\n   2 \n\n\n");  // print time

            if (menuselection == 1) {FntPrint(">> New Game\n\n");}
            else {FntPrint("   New Game\n\n");}

            if (menuselection == 2) {FntPrint(">> Continue Night %d\n\n", night);}
            else {FntPrint("   Continue Night %d\n\n", night);}

            if (menuselection == 3) {FntPrint(">> Extra menu \n\n");}
            else {FntPrint("   Extra menu \n\n");}

            if (menuselection == 4) {FntPrint(">> Custom Night \n\n");}
            else {FntPrint("   Custom Night \n\n");}
        }*/
        if (activatedmenudebug == 1) {
            if (menuselection == 5) {FntPrint(">> Debugprint %d\n\n", printnumber);}
            else {FntPrint("   Debugprint \n\n");}
        }
    }
    if (maincustomnightmenu == 1) {
        if (menuselection == 1) {FntPrint(">> Night : %d\n\n", night);}
        else {FntPrint("   Night : %d\n\n", night);}
        if (menuselection == 2) {FntPrint(">> Set AI levels\n\n");}
        else {FntPrint("   Set AI levels\n\n");}
        if (menuselection == 3) {FntPrint(">> Set Timer, ect.\n\n");}
        else {FntPrint("   Set Timer, ect.\n\n");}
        if (menuselection == 4) {FntPrint(">> Launch custom night\n\n");}
        else {FntPrint("   Launch custom night\n\n");}
        if (menuselection == 5) {FntPrint(">> Return to main menu\n\n");}
        else {FntPrint("   Return to main menu\n\n");}
    }
    if (AISetmenu == 1) {
        if (animatronicategorie == 1) {
            if (menuselection == 1) {FntPrint(">> Freddy : %d\n\n", freddydifficulty );}
            else {FntPrint("   Freddy : %d\n\n", freddydifficulty );}
            if (menuselection == 2) {FntPrint(">> Bonnie : %d\n\n", bonniedifficulty );}
            else {FntPrint("   Bonnie : %d\n\n", bonniedifficulty );}
            if (menuselection == 3) {FntPrint(">> Chica : %d\n\n", chicadifficulty );}
            else {FntPrint("   Chica : %d\n\n", chicadifficulty );}
            if (menuselection == 4) {FntPrint(">> Foxy : %d\n\n", foxydifficulty );}
            else {FntPrint("   Foxy : %d\n\n", foxydifficulty );}
        }
        if (animatronicategorie == 2) {
            if (menuselection == 1) {FntPrint(">> Toy Freddy : %d\n\n", toyfreddydifficulty );}
            else {FntPrint("   Toy Freddy : %d\n\n", toyfreddydifficulty );}
            if (menuselection == 2) {FntPrint(">> Toy Bonnie : %d\n\n", toybonniedifficulty );}
            else {FntPrint("   Toy Bonnie : %d\n\n", toybonniedifficulty );}
            if (menuselection == 3) {FntPrint(">> Toy Chica : %d\n\n", toychicadifficulty );}
            else {FntPrint("   Toy Chica : %d\n\n", toychicadifficulty );}
            if (menuselection == 4) {FntPrint(">> Mangle : %d\n\n", mangledifficulty );}
            else {FntPrint("   Mangle : %d\n\n", mangledifficulty );}
        }
        if (animatronicategorie == 3) {
            if (menuselection == 1) {FntPrint(">> Ballon Boy : %d\n\n", BBdifficulty );}
            else {FntPrint("   Ballon Boy : %d\n\n", BBdifficulty );}
            if (menuselection == 2) {FntPrint(">> Golden Freddy : %d\n\n", GFdifficulty );}
            else {FntPrint("   Golden Freddy : %d\n\n", GFdifficulty );}
            if (menuselection == 3) {FntPrint(">> Character leveling ? : %s \n\n", doescharlevelupstr );}
            else {FntPrint("   Character leveling ? : %s \n\n", doescharlevelupstr );}
            if (menuselection == 4) {FntPrint(">> \n\n");}
            else {FntPrint("   \n\n" );}
        }
        if (menuselection == 5) {FntPrint(">> Categorie %d\n\n",animatronicategorie);}
        else {FntPrint("   Categorie %d \n\n", animatronicategorie);}
        if (menuselection == 6) {FntPrint(">> Preset : %s\n\n", presetselectorstr);}
        else {FntPrint("   Preset : %s\n\n",presetselectorstr);}
        if (menuselection == 7) {FntPrint(">> Return to Custom night menu\n\n");}
        else {FntPrint("   Return to Custom night menu\n\n");}
    }
    if (timermenu == 1) {
        if (menuselection == 1) {FntPrint(">> Set beginning AM %d\n\n", customAM );}
        else {FntPrint("   Set beginning AM %d\n\n", customAM );}
        if (menuselection == 2) {FntPrint(">> 1 Hour = %d seconds in game\n\n", convertion );}
        else {FntPrint("   1 Hour = %d seconds in game\n\n", convertion );}
        if (menuselection == 3) {FntPrint(">> Cooldown FBCFo : %d %d %d %d\n\n", freddylocationframelock, bonnielocationframelock, chicalocationframelock, foxylocationframelock );}
        else {FntPrint("   Cooldown of old animatronics : ...\n\n" );}
        if (menuselection == 4) {FntPrint(">> Cooldown FBCM : %d %d %d %d\n\n", toyfreddylocationframelock, toybonnielocationframelock, toychicalocationframelock, manglelocationframelock );}
        else {FntPrint("   Cooldown of toy animatronics : ...\n\n" );}
        if (menuselection == 5) {FntPrint(">> Return to Custom night menu\n\n");}
        else {FntPrint("   Return to Custom night menu\n\n");}
        //Maybe put end AM
    }
    if (extramenu == 1) {

        if (menuselection == 1) {FntPrint(">> Enable phone guy ? %s\n\n", enablephoneguystr);}
        else {FntPrint("   Enable phone guy ? %s\n\n", enablephoneguystr);}

        if (menuselection == 2) {FntPrint(">> Unlocks menu\n\n");}
        else {FntPrint("   Unlocks menu\n\n");}

        if (menuselection == 3) {FntPrint(">> Info screen\n\n");}
        else {FntPrint("   Info screen\n\n");}

        if (menuselection == 4) {FntPrint(">> Two Player Mode : %s\n\n", twoplayermodestr);}
        else {FntPrint("   Two Player Mode : %s\n\n", twoplayermodestr);}

        if (menuselection == 5) {FntPrint(">> Return to main menu\n\n");}
        else {FntPrint("   Return to main menu\n\n");}

        if (activatedmenudebug == 1) {
            if (menuselection == 6) {FntPrint(">> Toggle weird night\n\n");}
            else {FntPrint("   Toggle weird night\n\n");}

            if (menuselection == 7) {FntPrint(">> Toggle debugging\n\n");}
            else {FntPrint("   Toggle debugging\n\n");}
        }
    }
    if (infoscreen == 1) {
        FntPrint("   Five Night at Freddy's 3 has been \n   released by Scott Cawton on 2015,\nand has been ported on the PS1 by Soeiz.\n         Again, Thank you, Scott, \n       For releasing this beautiful\n               Masterpiece.\n\n");

        FntPrint(">> Back                      V0.1\n"); //Don't even need to do condition, there's only one
    }
    if (unlockssubmenu == 1) {
        if (menuselection == 1) {FntPrint(">> Unlimited Power : %s\n\n", unlimitedpowerstr);}
        else {FntPrint("   Unlimited Power : %s\n\n", unlimitedpowerstr);}

        if (menuselection == 2) {FntPrint(">> Fast Nights : %s\n\n", fastnightsstr);}
        else {FntPrint("   Fast Nights : %s\n\n", fastnightsstr);}

        if (menuselection == 3) {FntPrint(">> Radar Map : %s\n\n", radarstr);}
        else {FntPrint("   Radar Map : %s\n\n", radarstr);}

        if (menuselection == 4) {FntPrint(">> Back \n\n");}
        else {FntPrint("   Back \n\n");}
    }
}
void gameoverprint(void) {
    FntPrint("\n\n      Congrats! You just... Died.\nGo on and press start to try your luck                 again !\n");
    if (activatedmenudebug == 1) {
        FntPrint("             Killer : %d",deadfrom);
    }
}
void controllerinput(void) {
    if (maintenancepanel == false) {
        if(pad & PADLup || pad >> 16 & PADLup && twoplayermode == 1) { //Up
            if (limiterbop == 1) {return;}
            if (MovVectorofficemiddle.vx > 50) {
                SpuSetKey(SPU_ON, SPU_05CH);
                limiterbop = 1;
            }
        }
        if(!(pad & PADLup || pad >> 16 & PADLup && twoplayermode == 1)) {limiterbop = 0;}
    }

    if(pad & PADR1 || pad >> 16 & PADR1 && twoplayermode == 1) { //R1
        if (camlimiter == 1) {return;}
        if (MovVectorofficemiddle.vx < -35) {CameraFunc(0);}
        if (MovVectorofficemiddle.vx > 80 && timerepairing == 0) {consoleFunc(); camlimiter = 1;}
          
    }
    if(!(pad & PADR1 || pad >> 16 & PADR1 && twoplayermode == 1)) {camlimiter = 0;}

    if (pad & PADstart || pad >> 16 & PADstart && twoplayermode == 1) {returnframes++;}

    if (!(pad & PADstart || pad >> 16 & PADstart && twoplayermode == 1)) {
        if (returnframes != 0) {
            returnframes = 0;
            returnbasevolume = 0x1800;
            SpuSetVoiceVolume(4, returnbasevolume, returnbasevolume);
        }
    }
}
void animatronicFunc(int init) {
    if (init == 1) {
        if (night == 1 && FrameCounter == 0) { //Setting difficulties
            toyfreddydifficulty = 0;
            toybonniedifficulty = 0;
            toychicadifficulty = 0;
            mangledifficulty = 0;
            freddydifficulty = 0;
            bonniedifficulty = 0;
            chicadifficulty = 0;
            foxydifficulty = 0;
            BBdifficulty = 0;
            GFdifficulty = 0;
            puppetdifficulty = 1;
        }
        if (night == 2 && FrameCounter == 0) { 
            freddydifficulty = 0;
            bonniedifficulty = 0;
            chicadifficulty = 0;
            GFdifficulty = 0;
            puppetdifficulty = 5;
            toybonniedifficulty = 3;
            toychicadifficulty = 3;
            foxydifficulty = 1;
            mangledifficulty = 3;
            toyfreddydifficulty = 2;
            BBdifficulty = 3;      
        }
        if (night == 3 && FrameCounter == 0) { 
            toyfreddydifficulty = 0;
            toybonniedifficulty = 0;
            toychicadifficulty = 0;
            mangledifficulty = 0;
            freddydifficulty = 0;
            GFdifficulty = 0;
            puppetdifficulty = 8;
            bonniedifficulty = 1;
            BBdifficulty = 1;
            chicadifficulty = 1;
            foxydifficulty = 2;
        }
        if (night == 4 && FrameCounter == 0) { 
            toyfreddydifficulty = 0;
            toybonniedifficulty = 0;
            toychicadifficulty = 0;
            freddydifficulty = 0;
            chicadifficulty = 0;
            GFdifficulty = 0;
            puppetdifficulty = 9;
            bonniedifficulty = 1;
            foxydifficulty = 7;
            BBdifficulty = 3;
            mangledifficulty = 5;
        }
        if (night == 5 && FrameCounter == 0) { 
            GFdifficulty = 0;
            puppetdifficulty = 10;
            freddydifficulty = 2;
            bonniedifficulty = 2;
            chicadifficulty = 2;
            foxydifficulty = 5;
            BBdifficulty = 5;
            toyfreddydifficulty = 5;
            toybonniedifficulty = 2;
            toychicadifficulty = 2;
            mangledifficulty = 1;
        }
        if (night == 6 && FrameCounter == 0) { 
            toyfreddydifficulty = 0;
            toybonniedifficulty = 0;
            toychicadifficulty = 0;
            mangledifficulty = 0;
            GFdifficulty = 0;
            puppetdifficulty = 15;
            freddydifficulty = 5;
            bonniedifficulty = 5;
            chicadifficulty = 5;
            foxydifficulty = 10;
            mangledifficulty = 3;
            BBdifficulty = 5;        
        }
    } else {
    if (debugging == 1) {
      if (FrameCounter == 0) {
        if (AM == 12) {
          toychicalocation = 2;
        }
        if (AM == 1) {
          toychicalocation--;
          freddylocation = 3;
        }
        if (AM == 2) {
          freddylocation--;
          bonnielocation = 2;
        }
        if (AM == 3) {
          bonnielocation--;
          foxylocation = 1;
        }
        if (AM == 4) {
          foxylocation--;
          toyfreddylocation = 2;
        }
      }
    }
    if (doescharlevelup == 1){
        if (FrameCounter == 0) {
          if (AM == 1) {
            if (night == 2) {
              toybonniedifficulty = toybonniedifficulty + 3;
              toychicadifficulty = toychicadifficulty + 3;
              toyfreddydifficulty = toyfreddydifficulty + 2;
              mangledifficulty = mangledifficulty + 3;
              BBdifficulty = BBdifficulty + 3;
              foxydifficulty = foxydifficulty + 1;
            }
            if (night == 3) {
              freddydifficulty = freddydifficulty + 2;
              bonniedifficulty = bonniedifficulty + 2;
              chicadifficulty++;
              foxydifficulty++;
              BBdifficulty++;
              toybonniedifficulty++;
              toychicadifficulty++;
            }
            if (night == 5) {
              freddydifficulty = freddydifficulty + 3;
              bonniedifficulty = bonniedifficulty + 3;
              chicadifficulty = chicadifficulty + 3;
              foxydifficulty = foxydifficulty + 2;
              toyfreddydifficulty = toyfreddydifficulty - 4;
              mangledifficulty = mangledifficulty + 9;
              toybonniedifficulty++;
            }
          }
          if (AM == 2) {
            if  (night == 1) {
              toybonniedifficulty = toybonniedifficulty + 2;
              toychicadifficulty = toychicadifficulty + 2;
            }
            if (night == 4) {
              freddydifficulty = freddydifficulty + 3;
              bonniedifficulty = bonniedifficulty + 3;
              chicadifficulty = chicadifficulty + 4;
              toybonniedifficulty++;
            }
            if (night == 6) {
              toybonniedifficulty = toybonniedifficulty + 5;
              GFdifficulty = GFdifficulty + 3;
              foxydifficulty = foxydifficulty + 5;
              toyfreddydifficulty = toyfreddydifficulty + 5;
              toychicadifficulty = toychicadifficulty + 5;
              mangledifficulty = mangledifficulty + 7;
              BBdifficulty = BBdifficulty + 4;
              freddydifficulty = freddydifficulty + 5;
              bonniedifficulty = bonniedifficulty + 5;
              chicadifficulty = chicadifficulty + 5;
            }
          }
          if (AM == 3) {
            if (night == 1) {
              toybonniedifficulty++;
              toyfreddydifficulty = toyfreddydifficulty + 2;
            }
          }
        }
    }
    if (isalreadydead == 1) {
        lastsecondsframes--;
        if (camera == 0) {lastsecondsframes = 0;}
        if (lastsecondsframes == 1001) {
            //Sound moaning ? 
        }
        if (lastsecondsframes == 480) {
            //Second moaning ?
        }
        if (lastsecondsframes == 0) {
            dead = 1;
        }
    }
    if (isalreadydeadlow == 1) { //Usually for GF only
        if (camera == 0) {
            dead = 1;
            deadfrom = 9;
        }
    }
    if (nightwon == 0) {
      AImoving();
    }
  }
}
void AImoving(void) {

}
void screamer(void) {
    if (camera == 1) {
        CameraFunc(0);
    }  
    screamerframes--;
    
    if (spriteframes == 0) {
        spritesheet++;
        switch(deadfrom) {
            case 1: 
              if (spritesheet > 4) {SpuSetKey(SPU_OFF, SPU_06CH); menu = 3;} break;
            case 9:
                spriteframesconst = 1;
                break;
            default :
                if (spritesheet > 3) {SpuSetKey(SPU_OFF, SPU_06CH); menu = 3;} break;
        } 
        if (spritesheet > 4 && deadfrom == 2 || spritesheet > 4 && deadfrom == 3) {spritesheet = 0;}
        if (deadfrom != 9) {
            clearVRAMScreamer();
        }/*
        if (deadfrom == 10) {
            if (spritesheet == 2) {
                LoadTexture(_binary_tim_screamer_jumpP2_tim_start, &jumpscare);
            }
            if (spritesheet == 3) {
                LoadTexture(_binary_tim_screamer_jumpP3_tim_start, &jumpscare);
            }
            if (spritesheet == 4) {
                LoadTexture(_binary_tim_screamer_jumpP5_tim_start, &jumpscare);
            }
            if (spritesheet == 1) {
                LoadTexture(_binary_tim_screamer_jumpP1_tim_start, &jumpscare);
            } 
        }*/
        spriteframes = 4;
    } else {spriteframes--;}
    makepoly(14);
    if (screamerframes == 46) {
        SpuSetKey(SPU_OFF, SPU_ALLCH);
        SpuSetKey(SPU_ON, SPU_04CH);
    }
    if (screamerframes == 0) {
        menu = 3;
    }
}
void consoleFunc(void) {
    maintenancepanel = !maintenancepanel; 
    spritemaintenancepanelgo = true;
    if (maintenancepanel) {
        makepoly(7);
        SpuSetKey(SPU_ON, SPU_19CH);
    } else {
        SpuSetKey(SPU_ON, SPU_20CH);
    }

}
void CameraFunc(int silent) {
    if (camlimiter == 0) {
        if (cooldowncamera == 0) {
            camera++;
            if (camera == 1) {
                if (toybonnielocation == 5) {
                    deadtoybonnie = 1;
                }
                if (silent == 0) {
                  SpuSetKey(SPU_OFF, SPU_01CH);
                  SpuSetKey(SPU_ON, SPU_07CH);
                }

                SpuSetKey(SPU_OFF, SPU_00CH);

                SpuSetVoiceVolume(2, 0x1800, 0x1800); //Lower down volume of officesound
            }
            if (camera >= 2) {
                camera = 0;
                if (deadtoybonnie == 1) {
                    dead = 1;
                    deadfrom = 6;
                }
                if (silent == 0) {
                  SpuSetKey(SPU_OFF, SPU_07CH);
                  SpuSetKey(SPU_ON, SPU_01CH);
                }

                SpuSetVoiceVolume(2, 0x2500, 0x2500); //Higher up volume of officesound
            }
            cooldowncamera = 15;
        }
    }
    camlimiter = 1;
}

void gamevictory(void) {
  if (camera == 1) {
    camera = 0;
  }
  SpuSetKey(SPU_OFF, SPU_ALLCH);
  FrameCounter++;
}