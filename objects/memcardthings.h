
//MEMORY CARD

// Converts strings from 8-bit ASCII characters to 16-bit Shift-JIS character encoding
void asc2sjis(char *asctext, u_short *sjistext) {
    
    // A small function to simplify the use of the ascii2sjis() function in asc2sjis.c
    
    int  i;
    char *ptr;
    
    union {
        u_short code;
        struct {
            char low;
            char high;
        } k_word;
    } kanji;
    
    for (i=0, ptr=(u_char*)sjistext; asctext[i] != 0x00; i++) {
        kanji.code  = ascii2sjis(asctext[i]);
        *ptr++ = kanji.k_word.high;
        *ptr++ = kanji.k_word.low;
    }
    
    sjistext[i] = 0x00;
    
}

bool memorycardmissing = true;//If set to true, no memory card will have to be present. So, no saves !

bool createsave = true;

/*
    Copy-Paste of DDLC create-load saves
*/

#define SAVENAMEMAIN    "FNAF3-33MAIN"
#define SAVETITLEMAIN   "Five Night at Freddy's 3"

// Test save icon's CLUT (or color palette) data
u_short saveIcon_clut[16] = {
    0x0000,0xF999,0xFC1F,0x0000,
    0x0000,0x0000,0x0000,0x0000,
    0x0000,0x0000,0x0000,0x0000,
    0x0000,0x0000,0x0000,0x0000
};

// Test save icon's image data (16x16 4-bit)
u_short saveIcon_image[1][16][4] = {
    // First icon frame
    {{0x0000,0x1110,0x0111,0x0000 },
    { 0x0000,0x1111,0x1111,0x0000 },
    { 0x1000,0x2221,0x1222,0x0001 },
    { 0x1100,0x2222,0x2222,0x0011 },
    { 0x2110,0x2222,0x2222,0x0112 },
    { 0x2211,0x2222,0x2222,0x1122 },
    { 0x2211,0x2222,0x2222,0x1122 },
    { 0x2211,0x2222,0x2222,0x1122 },
    { 0x2211,0x2222,0x2222,0x1122 },
    { 0x2211,0x2222,0x2222,0x1122 },
    { 0x2211,0x2222,0x2222,0x1122 },
    { 0x2110,0x2222,0x2222,0x0112 },
    { 0x1100,0x2222,0x2222,0x0011 },
    { 0x1000,0x2221,0x1222,0x0001 },
    { 0x0000,0x1110,0x0111,0x0000 },
    { 0x0000,0x1110,0x0111,0x0000 }}
}; //I hate doing that

// Save block header structure
typedef struct {
    char    id[2];      // Always 'SC'
    char    type;       // Number of icon frames (0x11 - one frame, 0x12 - two frames, 0x13 - three frames)
    char    size;       // Size of save file in blocks
    u_short title[32];  // Title of save file (encoded in Shift-JIS format)
    char    pad[28];    // Unused
    char    clut[32];   // Color palette of icon frames (16 RGB5X1 16-bit color entries)
} SAVEHDR;

short numCards=0;       // Number of cards detected
short currentCard=0;    // Current card number
long  cardCmd;          // Card command return value
long  slotResult[2];    // Slot result value

long    fileCount[2]={0};
long    blockCount[2]={0};

struct DIRENTRY fileList[2][15];

void MemCardLoad(void) {

    //This function tries to load the data of the current night.

    // Open the created file
    MemCardOpen(16*currentCard, SAVENAMEMAIN, O_RDONLY);

    // Read thingies
    MemCardReadData((u_long*)&night, 128*2, 128);
    while(MemCardSync(0, &cardCmd, &slotResult[0]) == 0);

    MemCardClose();

}

void CreateSaveFunc(void) {
    if (memorycardmissing) {return;}

    SAVEHDR header;

    header.id[0]='S'; header.id[1]='C'; // ID must always say SC
    header.type     = 0x11;                 // 1 frame icon
    header.size     = 1;                    // 1 block
        
    // Convert save title from ASCII to SJIS
    asc2sjis(SAVETITLEMAIN, header.title);
    
    // Copy icon's CLUT to the header
    memcpy(header.clut, saveIcon_clut, 32);

    // Open the created file
    MemCardOpen(16*currentCard, SAVENAMEMAIN, O_WRONLY);

    // Write the header
    MemCardWriteData((u_long*)&header, 128*0, 128);
    while(MemCardSync(1, &cardCmd, &slotResult[0]) == 0);
    
    // Write the icon frames
    MemCardWriteData((u_long*)&saveIcon_image, 128*1, 128);
    while(MemCardSync(1, &cardCmd, &slotResult[0]) == 0);

    // Write thingies
    MemCardWriteData((u_long*)&night, 128*2, 128);
    while(MemCardSync(0, &cardCmd, &slotResult[0]) == 0);

    //Close the created file
    MemCardClose();

    return;
}
void MemcardSavesInit(void) {
    if (memorycardmissing) {return;}

    if (MemCardOpen(16*currentCard, SAVENAMEMAIN, O_WRONLY) == McErrNone) { //If good card + having everything, go on !
    }
}