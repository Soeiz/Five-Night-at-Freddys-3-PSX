
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
    SpuSetVoiceVolume(0, 0x3500, 0x3500);//sealing vent
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
    SpuSetVoiceVolume(11, 0x2000, 0x2000); //alarm
    SpuSetVoiceVolume(12, 0x2000, 0x2000); //mangle
    SpuSetVoiceVolume(13, 0x2500, 0x2500); //BB1
    SpuSetVoiceVolume(14, 0x2500, 0x2500); //BB2
    SpuSetVoiceVolume(15, 0x2000, 0x2000); //BB3
    SpuSetVoiceVolume(16, 0x3500, 0x3500); //vent
    SpuSetVoiceVolume(17, 0x3000, 0x3000); //Monitor uP 2
    SpuSetVoiceVolume(18, 0x3500, 0x3500); //clickfail
    SpuSetVoiceVolume(19, 0x3500, 0x3500); //Beep from console or when sailing vent
    SpuSetVoiceVolume(20, 0x3500, 0x3500); //Console Opening
    SpuSetVoiceVolume(21, 0x2500, 0x2500); //Cam ambiance
    SpuSetVoiceVolume(22, 0x2500, 0x2500); //Springtrap near....
    SpuSetVoiceVolume(23, 0x2500, 0x2500); //Short puppet noise.
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

// extern VAG files
extern u_char _binary_vag_sealingvent_vag_start;
extern u_char _binary_vag_monitor_down_vag_start;
extern u_char _binary_vag_officesound_vag_start;
extern u_char _binary_vag_click_vag_start;
extern u_char _binary_vag_screamer_vag_start;
extern u_char _binary_vag_honk_vag_start;
extern u_char _binary_vag_moving_vag_start;
extern u_char _binary_vag_monitor_up_vag_start;
extern u_char _binary_vag_monitor_up_2_vag_start;
extern u_char _binary_vag_coin_vag_start;
extern u_char _binary_vag_ventquiet_vag_start;
extern u_char _binary_vag_breathing_vag_start;
extern u_char _binary_vag_alarm_vag_start;
extern u_char _binary_vag_mangle_vag_start;
extern u_char _binary_vag_BB1_vag_start;
extern u_char _binary_vag_BB2_vag_start;
extern u_char _binary_vag_BB3_vag_start;
extern u_char _binary_vag_ventquiet_vag_start;
extern u_char _binary_vag_button_vag_start;
extern u_char _binary_vag_consoleclosing_vag_start;
extern u_char _binary_vag_consoleopening_vag_start;
extern u_char _binary_vag_camambiance_vag_start;
extern u_char _binary_vag_springtrapnear_vag_start;
extern u_char _binary_vag_puppet_vag_start;

// soundBank
VAGsound vagsoundBank[VAG_NBR] = {
      { &_binary_vag_sealingvent_vag_start,
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
      { &_binary_vag_moving_vag_start,
        SPU_06CH, 0 },
      { &_binary_vag_monitor_up_vag_start,
        SPU_07CH, 0 },
      { &_binary_vag_coin_vag_start,
        SPU_08CH, 0 },
      { &_binary_vag_ventquiet_vag_start,
        SPU_09CH, 0 },
      { &_binary_vag_breathing_vag_start,
        SPU_10CH, 0 },
      { &_binary_vag_alarm_vag_start,
        SPU_11CH, 0 },
      { &_binary_vag_mangle_vag_start,
        SPU_12CH, 0 },
      { &_binary_vag_BB1_vag_start,
        SPU_13CH, 0 },
      { &_binary_vag_BB2_vag_start,
        SPU_14CH, 0 },
      { &_binary_vag_BB3_vag_start,
        SPU_15CH, 0 },
      { &_binary_vag_ventquiet_vag_start,
        SPU_16CH, 0 },
      { &_binary_vag_monitor_up_2_vag_start,
        SPU_17CH, 0 },
     { &_binary_vag_button_vag_start,
        SPU_18CH, 0 },
      { &_binary_vag_consoleclosing_vag_start,
        SPU_19CH, 0 },
     { &_binary_vag_consoleopening_vag_start,
        SPU_20CH, 0 },
     { &_binary_vag_camambiance_vag_start,
        SPU_21CH, 0 },     
     { &_binary_vag_springtrapnear_vag_start,
        SPU_22CH, 0 }, 
     { &_binary_vag_puppet_vag_start,
        SPU_23CH, 0 },
};
/*
// soundBank
VAGsound vagsoundBank2[VAG_NBR] = {
      { &_binary_vag_sealingvent_vag_start,
        SPU_23CH, 0 },   
      { &_binary_vag_monitor_down_vag_start,
        SPU_22CH, 0 },
      { &_binary_vag_officesound_vag_start,
        SPU_21CH, 0 },
      { &_binary_vag_click_vag_start,
        SPU_20CH, 0 },
      { &_binary_vag_screamer_vag_start,
        SPU_19CH, 0 },
      { &_binary_vag_honk_vag_start,
        SPU_18CH, 0 },
      { &_binary_vag_moving_vag_start,
        SPU_17CH, 0 },
      { &_binary_vag_monitor_up_vag_start,
        SPU_16CH, 0 },
      { &_binary_vag_coin_vag_start,
        SPU_15CH, 0 },
      { &_binary_vag_ventquiet_vag_start,
        SPU_14CH, 0 },
      { &_binary_vag_breathing_vag_start,
        SPU_13CH, 0 },
      { &_binary_vag_alarm_vag_start,
        SPU_12CH, 0 },
      { &_binary_vag_mangle_vag_start,
        SPU_11CH, 0 },
      { &_binary_vag_BB1_vag_start,
        SPU_10CH, 0 },
      { &_binary_vag_BB2_vag_start,
        SPU_09CH, 0 },
      { &_binary_vag_BB3_vag_start,
        SPU_08CH, 0 },
      { &_binary_vag_clickfail_vag_start,
        SPU_07CH, 0 },
      { &_binary_vag_monitor_up_2_vag_start,
        SPU_06CH, 0 },
     { &_binary_vag_button_vag_start,
        SPU_05CH, 0 },
      { &_binary_vag_consoleclosing_vag_start,
        SPU_04CH, 0 },
     { &_binary_vag_consoleopening_vag_start,
        SPU_03CH, 0 },
     { &_binary_vag_camambiance_vag_start,
        SPU_02CH, 0 },     
     { &_binary_vag_springtrapnear_vag_start,
        SPU_01CH, 0 }, 
     { &_binary_vag_puppet_vag_start,
        SPU_00CH, 0 },
};*/

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

int sample = -1;

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
            {   1,  186880,   1,     5,     7544,   8176,  -1 }, //Beginning of the night.xa
            {   2,  5417184,   1,     5,     9672,   28216,  -1 }, //ambiance.xa
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

void ChangeMusic(int music) {
  sample = music;
  filter.chan = soundBank.samples[sample].channel;
  filter.file = soundBank.samples[sample].file;
  CdControlF(CdlSetfilter, (u_char *)&filter);
  soundBank.samples[sample].cursor = 0;
}

void MusicControl() {
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
}