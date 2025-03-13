/*
    TO FIX :   
        
        MovVectorfreddyoffice.vx, YOU BASTARD !! THE ONLY WEAKNESS OF MY PROGRAM !

        Some Animation of jumpscares not fitting the poly

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
        We need to do 'Ran(number + 1)' apparently, so if you want Ran(5) do Ran(6). Figured this out with singtrap's AI.
        FNAF3 is a (heavily) modified version of FNAF2, a (heavily) modified version of FNAF1
        V.1.0

        Thanks WarriorWatchman for your documentation ! https://docs.google.com/document/d/1rsT1cvuyp7v3G6cyshwVYaP-Hba5XXiKr9gEIVWMJLY/edit?tab=t.0

        This video too from https://www.youtube.com/watch?v=8vaXhulGN_I !
*/

int FrameCounter = 0;
int customAM = 12;

int AM = 12;

int night = 1;

int debug = 3; 

#include "objects/constant.h"

//Made all of the var declarations that I won't change alot into constant.h

//Lot of functions is shared in different files. 

void print(int number) {
    if (number == 1) { //Vanilla debug (with access to camera)
        if (!camera) {
            FntPrint("\n");
        } else {
            FntPrint("Current CAM: %d%d\n", curcam[0],curcam[1]);
            if (!(curcam[0] == 0 || curcam[0] == 1 && curcam[1] == 0)) {
                FntPrint("Is sealed? ");
                // Printing if the current camera is sealed.
                (curcam[0] + curcam[1] + 9 == ventlocked) ? FntPrint("Sealed") : FntPrint("Not Sealed");  
            }
        }
        FntPrint("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");  // For the text to go bottom LOL

        //FntPrint("%d AM \n, pos %d, pPos %d\n", AM, MovVectorofficemiddle.vx, MovVectorpuppet.vx);  // print time
        FntPrint("%d AM\n", ScaleVectorofficemiddle.vx);  // print time
        FntPrint("Night %d \n", night);
    }
    if (number == 2) { // Better debug mode
        FntPrint("%d AM,RAN %d,pos %d,CamS. %d\n",AM, RAN,MovVectorofficemiddle.vx,camerastatic, demisecondframe, fivesecondframe);
        FntPrint("Phoneguy %d,BB. %d,%d,%d,ambS. %d, CCS %d\n", phoneguytalking, ballonboyqueued, ballonboyseen,puppetframesdisappear, ambianceframe, chicaseen);
        FntPrint("Aud.H %d, Cam.H %d + T. %d, V.H %d + T. %d", audiodevicehealth, camerahealth, camerahealthtimer, ventilhealth, ventilhealthtimer);
    }
}

void controllerinput(void) {
    if (currentlysealing) {return;}
    
    if (maintenancepanel == false) {
        if(pad & PADLup || pad >> 16 & PADLup && twoplayermode == 1) { //Up
            if (limiterbop == 1) {return;}
            if (MovVectorofficemiddle.vx > -17) {
                SpuSetKey(SPU_ON, SPU_05CH);
                limiterbop = 1;
            }
        }
        if(!(pad & PADLup || pad >> 16 & PADLup && twoplayermode == 1)) {limiterbop = 0;}
    }

    if(pad & PADR1 || pad >> 16 & PADR1 && twoplayermode == 1) { //R1
        if (camlimiter == 1) {return;}
        if (ispuppetofficehere) {return;}
        if (springtraprunningindex != -1) {return;} //If Pongtrap running, disable the cam
        if (MovVectorofficemiddle.vx < -55) {CameraFunc(false);}
        if (MovVectorofficemiddle.vx > 80 && timerepairing == 0) {consoleFunc(); camlimiter = 1;}  
    }
    if(!(pad & PADR1 || pad >> 16 & PADR1 && twoplayermode == 1)) {camlimiter = 0;}

    if (camera && spritecamera == 5) {
        if(pad & PADRright || pad >> 16 & PADRright && twoplayermode == 1) { //Square - Audio lure

            if (isonvents) {
                currentlysealing = true;
                return;
            }

            if (abletoplaysound && BBsoundcooldown == 0) {
                Ran(4);
                switch(RAN) {
                    case 1: 
                        SpuSetKey(SPU_ON, SPU_13CH);
                    break;
                    case 2: 
                        SpuSetKey(SPU_ON, SPU_14CH);
                    break;
                    case 3: 
                        SpuSetKey(SPU_ON, SPU_15CH);
                    break;
                }
                Ran(3);
                if (!noerrors) {audiodevicehealth -= springtrapAI;}
                Ran(8);
                if (RAN != 1) {
                    audiolureworked = true;
                }



                if (audiodevicehealth == 0) {abletoplaysound = false;}
                BBsoundcooldown = 600;
            }
        }    
        if (pad & PADRdown || pad >> 16 & PADRdown && twoplayermode == 1) { //Cross - Toggle map change
            if (limitertoggle == 1) {return;}
            isonvents = !isonvents; // = true (vents), = false (rooms)

            if (isonvents) {
                curcam[0] = 1;
                curcam[1] = 1;
                LoadTexture(_binary_tim_camera_panel_layoutvent_tim_start, &camlayout);
            } else {
                curcam[0] = 0;
                curcam[1] = 1;
                LoadTexture(_binary_tim_camera_panel_layout_tim_start, &camlayout);
            }

            limitertoggle = 1;
            SpuSetKey(SPU_ON, SPU_03CH); 
        }    
        if(!(pad & PADRdown || pad >> 16 & PADRdown && twoplayermode == 1)) {limitertoggle = 0;}   
    }

    if (pad & PADstart || pad >> 16 & PADstart && twoplayermode == 1) {
        switch(menu) {
            case 0:
                FFWwarning = true;
            break;
            case 3:
                returnframes++;
                if (pad & PADselect) {
                    if (!activatedmenudebug) {return;}
                    freeze = true;

                    /*
                    SpuFree(1000);

                    u_long spu_address;
                    spuSetup(&spuSettings);
                    // Init sound settings
                    initSnd();

                    for (u_short vag = 0; vag < VAG_NBR; vag++ ){
                        vagsoundBank2[vag].spu_address = setSPUtransfer(&vagsoundBank2[vag]);
                    }*/
                }
                if (pad & PADRdown) {
                    springtraphide = true;
                    LoadTexture(_binary_tim_office_springtraphide_1_tim_start, &springtraphideoffice);
                }
            break;
        }
    }

    if (!(pad & PADstart || pad >> 16 & PADstart && twoplayermode == 1)) {
        if (returnframes != 0) {
            returnframes = 0;
            returnbasevolume = 0x1800;
            SpuSetVoiceVolume(4, returnbasevolume, returnbasevolume);
        }
    }
}
void controllerinputfreeze(void) {
    if (menuselectionmaxfreeze == 0) {menuselectionmaxfreeze = 12;} //Set here to be changed dinamically

    if (pad & PADLup) {
        if (limiterpadup == 0) {
            if (selectionfreeze > 1) {
                selectionfreeze--;
            }
            else {
                selectionfreeze = menuselectionmaxfreeze;
            }
            limiterpadup = 1;
        }
    }
    if (pad & PADLdown) {
        if (limiterpaddown == 0) {
            if (selectionfreeze < menuselectionmaxfreeze) {
                selectionfreeze++;
            }
            else {
                selectionfreeze = 1;
            }
            limiterpaddown = 1;
        }
    }
    if (!(pad & PADLright)) {limiterpadright = 0;}
    if (!(pad & PADLleft)) {limiterpadleft = 0;}
    if (!(pad & PADLdown)) {limiterpaddown = 0;}
    if (!(pad & PADLup)) {limiterpadup = 0;}
    if (!(pad & PADstart)) {limiterstart = 0;}
    if (!(pad & PADRdown)) {limiterbuttondown = 0;}

    switch(currentmenu[0]) {
        case 0:
            if (selectionfreeze == 1) {FntPrint("> SpringtrapLoc %d%d\n", springtraplocation[0],springtraplocation[1]);} else {FntPrint("  SpringtrapLoc %d%d\n", springtraplocation[0],springtraplocation[1]);}
            if (selectionfreeze == 2) {FntPrint("> ballonboyqueued %d\n", ballonboyqueued);} else {FntPrint("  ballonboyqueued %d\n", ballonboyqueued);}
            if (selectionfreeze == 3) {FntPrint("> chicaqueued %d\n", chicaqueued);} else {FntPrint("  chicaqueued %d\n", chicaqueued);}
            if (selectionfreeze == 4) {FntPrint("> puppetqueued %d\n", puppetqueued);} else {FntPrint("  puppetqueued %d\n", puppetqueued);}
            if (selectionfreeze == 5) {FntPrint("> isfreddyofficehere %d\n", isfreddyofficehere);} else {FntPrint("  isfreddyofficehere %d\n", isfreddyofficehere);}
            if (selectionfreeze == 6) {FntPrint("> manglequeued %d\n", manglequeued);} else {FntPrint("  manglequeued %d\n", manglequeued);}
            if (selectionfreeze == 7) {FntPrint("> isfoxyofficehere %d\n", isfoxyofficehere);} else {FntPrint("  isfoxyofficehere %d\n", isfoxyofficehere);}
            if (selectionfreeze == 8) {FntPrint("> Springtrap stages %d\n", stage);} else {FntPrint("  Springtrap stages %d\n",stage);}
            if (selectionfreeze == 9) {FntPrint("> Change AM %d\n", AM);} else {FntPrint("  Change AM %d\n", AM);}
            if (selectionfreeze == 10) {FntPrint("> Change FrameCounter %d\n", FrameCounter);} else {FntPrint("  Change FrameCounter %d\n", FrameCounter);}
            if (selectionfreeze == 11) {FntPrint("> springtrapinactive %d \n");} else {FntPrint("  springtrapinactive %d\n");}
            if (selectionfreeze == 12) {FntPrint("> Apply changes \n");} else {FntPrint("  Apply changes\n");}

            switch(selectionfreeze) {
                case 1:
                    if (pad & PADLright) {
                        if (limiterpadright == 0) {
                            springtraplocation[1]++;
                            limiterpadright = 1;
                        }
                    }
                    if (pad & PADLleft) {
                        if (limiterpadleft == 0) {
                            springtraplocation[1]--;
                            limiterpadleft = 1;
                        }
                    }
                    if (springtraplocation[1] > 9) {springtraplocation[1] = 0; springtraplocation[0] = 1;}
                    if (springtraplocation[1] < 0) {springtraplocation[1] = 9; springtraplocation[0] = 0;}
                    if (springtraplocation[0] == 1) {
                        if (springtraplocation[1] != 0) {isspringtrapvents = true;} else {isspringtrapvents = false;}
                    }
                break;
                case 2:
                    if (pad & PADstart) {ballonboyqueued = true;}  
                    if (pad & PADselect) {ballonboyqueued = false;}  
                break;
                case 3:
                    if (pad & PADstart) {chicaqueued = true;} 
                    if (pad & PADselect) {chicaqueued = false;}  
                break;
                case 4:
                    if (pad & PADstart) {puppetqueued = true;} 
                    if (pad & PADselect) {puppetqueued = false;}  
                break;
                case 5:
                    if (pad & PADstart) {isfreddyofficehere = true;} 
                    if (pad & PADselect) {isfreddyofficehere = false;}  
                break;
                case 6:
                    if (pad & PADstart) {manglequeued = true;} 
                    if (pad & PADselect) {manglequeued = false;}  
                break;
                case 7:
                    if (pad & PADstart) {isfoxyofficehere = true;} 
                    if (pad & PADselect) {isfoxyofficehere = false;}  
                break;
                case 8:
                    if (pad & PADLright) {
                        if (limiterpadright == 0) {
                            stage++;
                            if (stage > 5) {stage = 0;}
                            limiterpadright = 1;
                        }
                    }
                    if (pad & PADLleft) {
                        if (limiterpadleft == 0) {
                            stage--;
                            if (stage < 0) {stage = 5;}
                            limiterpadleft = 1;
                        }
                    }
                break;
                case 9:
                    if (pad & PADLright) {
                        if (limiterpadright == 0) {
                            AM++;
                            if (AM > 12) {AM = 1;}
                            FrameCounter = 0;
                            limiterpadright = 1;
                        }
                    }
                    if (pad & PADLleft) {
                        if (limiterpadleft == 0) {
                            AM--;
                            if (AM < 1) {AM = 12;}
                            FrameCounter = 0;
                            limiterpadleft = 1;
                        }
                    }
                break;
                case 10:
                    if (pad & PADLright) {
                        if (FrameCounter == FrameCounterlimit) {FrameCounter = 0;}
                        FrameCounter++;
                    }
                    if (pad & PADLleft) {
                        if (FrameCounter == 0) {FrameCounter = FrameCounterlimit;}
                        FrameCounter--;
                    }
                break;
                case 11:
                    if (pad & PADstart) {springtrapinactive = true;} 
                    if (pad & PADselect) {springtrapinactive = false;}  
                break;
                case 12:
                    if (pad & PADstart) {freeze = false; selectionfreeze = 1;}                
                break;
            }

        break;
    }

}

void starting(void) {
    resetgame(0);

    setRGBALL(128, 128, 128, 2);

    if (initstuff == 1) {
        clearVRAMgeneral(384, 0, 256, 513);
        clearVRAMgeneral(640, 0, 256, 256);
        LoadTexture(_binary_tim_load_tim_start, &load); 
    } else {clearVRAMgeneral(576, 256, 25, 106);}

    musicframes = 0;

    if (fastnights || noerrors) {
        cheating = true;
    } else {
        cheating = false;
    }

    if (aggressive) {
        night = 6;
    }

    if (fastnights) {
        FrameCounterlimit = FrameCounterlimit / 2;
    }

    AM = customAM;
    if (night != 1) {
      FrameCounterlimit = convertion;
    } else {
      FrameCounterlimit = convertion - 20;
    }
    FrameCounterlimit = FrameCounterlimit * 60; //60 seconds * 60 fps = 3600 frames, maybe it would cause issues with 30 fps ??
    SpuSetKey(SPU_ON, SPU_03CH);
    if (weirdnight == 0 && customnightactivated == 0) {
        animatronicFunc(1);
    }
}
int main(void) {
    //controller
    TILE * PADL;                    // Tile primitives
    TILE * TRIGGERL;
    TILE * PADR;
    TILE * TRIGGERR;
    TILE * START, * SELECT;

    init();

    //SPU
    u_long spu_address;
    spuSetup(&spuSettings);
    // Init sound settings
    initSnd();

    MemCardInit(0);
    MemCardStart();

    PadInit(0);                     // Initialize pad.  Mode is always 0

    for (u_short vag = 0; vag < VAG_NBR; vag++ ){
        vagsoundBank[vag].spu_address = setSPUtransfer(&vagsoundBank[vag]);
    }

    // Init CD system
    CdInit();

    // Init heap
    InitHeap((u_long *)ramAddr, sizeof(ramAddr));

    clearVRAM();

    LoadTexture(_binary_tim_titlemenu_WARNING_tim_start, &warning); 

    if (!menuscreeninit) {LoadingMenu();}

    //LoadTexture(_binary_tim_fnt_tim_start, &fontface);
    while (1)
    {  

        //FntPrint("%d", sync);
        ClearOTagR(ot[db], OTLEN);
        
        if (fivesecondframe > 0) {fivesecondframe--;} else {fivesecondframe = 300;}

        if (ambianceframe > 0) {
            if (phoneguytalking == 0) {
                ambianceframe--;
            } else {
                ambianceframe = 300;
            }
        } else {
            ambianceframe = 7380;
        }

        if (demisecondframe > 0) {demisecondframe--;} else {demisecondframe = 30;}
        
        if (linesactive) {
            lineflicker();
        }

        if (linesdeathactive) {
            linesdeath();
        }

        pad = PadRead(0);

        MusicControl(); //Required for the musics

        switch(menu) {
            case 0:
                makepoly(17);

                framesforwarning++;

                if (framesforwarning > 180 || FFWwarning) {
                    fadeoffice--;
                }

                if (fadeoffice == 0) {
                    MemcardSavesInit();

                    MemCardLoad(); //To load nights !

                    SpuSetKey(SPU_ON, SPU_03CH);
                    menu = 1;
                }
            break;
            case 1:
                if (!helpwantedposter) {

                    seedrandom++;

                    menuPrint();
        
                    menuselectionfunc();

                    makepoly(1);
        
                    if (menufadingout) {if (fadeoffice < 127) {fadeoffice++; fadeoffice++;} else {helpwantedposter = true; menufadingout = false;}}
        
                    setRGB0(polymenu,128 - fadeoffice,128 - fadeoffice,128 - fadeoffice);
                    setRGB0(polylines,128 - fadeoffice,128 - fadeoffice,128 - fadeoffice);
                    setRGB0(polystatic,128 - fadeoffice,128 - fadeoffice,128 - fadeoffice);
                    setRGB0(polyname,128 - fadeoffice,128 - fadeoffice,128 - fadeoffice);
                    if (currentmenu[0] == 0) {setRGB0(polymenuselectionbutton,128 - fadeoffice,128 - fadeoffice,128 - fadeoffice);} else {setRGB0(polymenuselectionbutton,0,0,0);}
                    
                } else {
                    if (nospringtrap) {loadingframe = 360;} //Skip if you've returned to menu since there'll be no sprite for help wanted

                    loadingframe++;

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
                        menu = 2;
                    }
                }

                if (musicframes > 2421){
                    musicframes = 0;
                    ChangeMusic(0);
                } else {musicframes++;}
            break;//Menu Screen
            case 2:
                loadingframe++;

                if (loadingframe < 360) {loadingframe = 360; helpwantedposter = false;}

                switch(loadingframe) {
                    case 362:
                        ChangeMusic(1);

                        linesactive = true;
                        starting();
                        PickNightTitle();
                        srand(seedrandom); // "truly" "random"
                        Ran(seedrandom * 68574 + seedrandom / 2);
                        srand(RAN); //Truly random x2
                        Ran(8500);

                        LoadTexture(_binary_tim_office_mutecall_tim_start, &mutecall);
                        LoadTexture(_binary_tim_load_tim_start, &load); 
                
                    break;
                    case 616:
                        if (createsave) {CreateSaveFunc();} //To save nights !
                        LoadTexture(_binary_tim_camera_panel_static_100_tim_start, &statics);
                        if (initstuff == 0) {LoadingAllTexture();}
                    break;
                }

                if (loadingframe > 370 && loadingframe < 614) {
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

                if (loadingframe > 617) {
                    menu = 3;
                    SpuSetKey(SPU_ON, SPU_02CH);
                    loadingframe = 0;
                }

            break;//Loading/Starting night screen
            case 3:
                if (freeze) {

                    controllerinputfreeze();

                    makepoly(6);

                } else {
                    if (phoneguytalkingconst - 1620 < phoneguytalking && !mutedcall && enablephoneguy) {makepoly(16);}

                    timeFunc();   

                    if (!heavybreathing) {SpuSetKey(SPU_OFF, SPU_10CH);}

                    //weird sound "alarm" thing

                    //Full sound
                    if (stage > 1 || (springtraplocation[0] == 0 && springtraplocation[1] == 2 || springtraplocation[1] == 1)) {
                        alarmstate = 2;
                        SpuSetVoiceVolume(22, 0x2500, 0x2500); //Sound amplification
                    } else {
                        //Half sound
                        if (isfreddyofficehere || chicaqueued || (springtraplocation[0] == 0 && springtraplocation[1] == 3 || springtraplocation[0] == 0 && springtraplocation[1] == 4 ||springtraplocation[0] == 0 && springtraplocation[1] == 5)) {
                            alarmstate = 1;
                            SpuSetVoiceVolume(22, 0x1250, 0x1250); //Sound amplification
                        } else {
                            //Mute sound
                            alarmstate = 0;
                        }
                    }

                    if (AM == 12 && FrameCounter == 1) { //Init Gameplay
                        CdControlF(CdlPause,0);
                    }

                    if (AM == 6 && FrameCounter == 0) { //Init victory
                        nightwon = true;
                        ChangeMusic(3);
                    }

                    if (fivetosixamframes < 720 && AM == 6) {finishednight();}

                    if (fivetosixamframes > 719) {
                        if (night == 5 || night == 6) {
                            if (night == 5) {night++; night5done = true;} else {night6done = true;}

                            if (night == 6 && aggressive == true) {donewithaggressive = true;}
                            menu = 1; 
                            nospringtrap = true;
                            menuselection = 3;
                            menuselectionmax = 2;
                            musicframes = 4430;
                            fadeoffice = 0;
                            linesactive = true;
                            fivetosixamframes = 0;
                            nextnightframes = 0;
                            alarmstate = 0;
                        } else {
                            night++;
                            fivetosixamframes = 0;
                            nextnightframes = 0;
                            menu = 2; //Load into next night
                        }
                    }

                    if (returnframes % 60 == 1) {
                        returnbasevolume += 2000;
                        SpuSetVoiceVolume(3, returnbasevolume, returnbasevolume);
                        SpuSetKey(SPU_ON, SPU_03CH);
                    }

                    if (returnframes == 210) {
                        isingame = true;
                        limiterstart = 1;
                        alarmstate = 0;
                        SpuSetKey(SPU_OFF, SPU_ALLCH);
                        returnbasevolume = 0x1800;
                        SpuSetVoiceVolume(3, returnbasevolume, returnbasevolume);
                        menuselection = 3;
                        menuselectionmax = 2;
                        returnframes = 0;
                        musicframes = 4430;
                        menu = 1;
                        nospringtrap = 1;
                        fadeoffice = 0;
                    }

                    if (returnedingame) {
                        CdControlF(CdlPause,0);
                        SpuSetKey(SPU_ON, SPU_02CH);
                        returnedingame = false;
                    }

                    if (activatedmenudebug && pad & PADR1 && pad & PADRup && pad & PADRright && pad & PADL2) {
                        AM = 5;
                        FrameCounter = FrameCounterlimit - 60;
                    }

                    if (ventilhealthtimer > 0) {ventilhealthtimer--;} else {
                        ventilhealthtimer = ventilhealthtimerconst;
                        Ran(3);
                        ventilhealth -= RAN; //Re-add springtrapAI later
                        if (ventilhealth < 1) {ventilationfailure = true;}
                    }

                    if (ambianceframe == 0) {
                        if (phoneguytalking == 0 && AM != 6) {
                            ChangeMusic(2);
                        }
                    }

                    if (phoneguytalkingconst - 1620 < phoneguytalking && !mutedcall) {
                        if (pad & PADselect || pad >> 16 & PADselect) {
                          mutedcall = true;
                          CdControlF(CdlPause,0);
                          phoneguytalking = 0;
                          enablephoneguy = false;
                          sample = 0;
                        }
                    }

                    /*
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
                    }*/

                    if (fivetosixamframes == 0) {
                        switch(officefadingout) {
                            case 1:
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
                            break;

                            case 0:
                                if (alarmcooldown > 15) {
                                    setRGBALL(128, 37, 37, 1);
                                    setRGB0(poly2ndlayer2, 128, 128, 128); 
                                } else {
                                    setRGBALL(128, 128, 128, 2);
                                }
                            break;

                            default:
                                if (fadeoffice != 128) { //Smoothed out transition
                                    fadeoffice++;
                                    setRGBALL(fadeoffice, fadeoffice, fadeoffice, 2);
                                } else {
                                    setRGBALL(128, 128, 128, 2);
                                }
                            break;
                        }
                    }

                    if (fadeoffice == 0) {blackout = true;} else {blackout = false;}

                    if (!camera && isalreadydead == 5 && cooldowncamera != 0) {dead = true;}
                    /*
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
                    */
                    if (phoneguytalking == 0 && enablephoneguy) {
                        switch(night) {
                            case 1:
                                phoneguytalking = 9762;
                                phoneguytalkingconst = 9762;
                            break;
                            case 2:
                                phoneguytalking = 7680;
                                phoneguytalkingconst = 7680;
                            break;
                            case 3:
                                phoneguytalking = 4560;
                                phoneguytalkingconst = 4560;
                            break;
                            case 4:
                                phoneguytalking = 3660;
                                phoneguytalkingconst = 3660;
                            break;
                            case 5:
                                phoneguytalking = 3240;
                                phoneguytalkingconst = 3240;
                            break;
                            case 6:
                                phoneguytalking = 2514;
                                phoneguytalkingconst = 2514;
                            break;
                        }
                        sample = night + 3; //Great arrangement benefits you, and your code.
                        ChangeMusic(sample); //sample = sample....hahahahah.HAHAHAHHAHHAHAHAAHHAHAHAHAHAHA!𝐇𝐀𝐇𝐀𝐇𝐀𝐇𝐀𝐇𝐀𝐇𝐀𝐀𝐇𝐀𝐇𝐀𝐇𝐇𝐀𝐇𝐀𝐇𝐀𝐇𝐀𝐇𝐀𝐇𝐀𝐀𝐇𝐀𝐇𝐀𝐇𝐇𝐀𝐇𝐀𝐇𝐀𝐇𝐀𝐇𝐀𝐇𝐀𝐀𝐇𝐀𝐇𝐀𝐇 *stab* *stab* *stab*
                    }//I'm writing whatever I want that's my code
                    if (phoneguytalking > 0) {phoneguytalking--;}
                    if (phoneguytalking == 1) {
                        sample = 0;
                        CdControlF(CdlPause,0);
                        enablephoneguy = false;
                    }

                    if (jumpscared) {
                        if (screamersetsound == 0 && stage == 5) {
                          ChangeMusic(10);
                          screamersetsound++;
                        }
                    } else {
                        if (fivetosixamframes == 0) {
                          print(printnumber);
                          animatronicFunc(0);
                          controllerinput();
                          AIact();
                        }
                    }

                    MaintenancePanelStuff();

                    CameraMonitorStuff();


                    if (jumpscared) {screamer();}

                    if (fivetosixamframes < 170) {makepoly(6);}

                    if (!dead && fivetosixamframes == 0 && !maintenancepanel) {

                        if (pad & PADRdown || pad >> 16 & PADRdown && twoplayermode == 1) {speedoffice = 6;} else {speedoffice = 3;}

                        if (!camera) {OfficeMove();}
                    }

                    if (blinkicon < 61) {blinkicon++;}
                    if (blinkicon == 60) {blinkicon = 0;}

                    if (ventilationfailure == true && !nightwon) {
                        if (alarmcooldown < 1) {
                            SpuSetKey(SPU_ON, SPU_11CH);
                            alarmcooldown = 30;
                        } else {
                            alarmcooldown--;
                        }
                    }
                }
            break;//Gameplay Screen
            case 4:
                if (staticframes > 1) {
                    makepoly(15);
                    if (staticframessheet == 8) {
                        staticframessheet = 0;
                        MovVectorstatic.vx = MovVectorstatic.vx - 16;
                    } else {
                        staticframessheet++;
                        MovVectorstatic.vx = MovVectorstatic.vx + 2;
                    }
                }
                if (staticframes == 259) {
                    SpuSetKey(SPU_OFF, SPU_ALLCH);
                }
                if (staticframes == 2) {
                  CdControlF(CdlPause,0);
                  sample = 0;
                  linesdeathactive = true;
                }
                if (staticframes < 1) {
                    seedrandom++; //While testing Freddy, I realized that he took the same time to come. So I put that to prevent having the same seed. Thank you, Freddy, for coming very lately (incrementing does not necessarily means taking longer to come) (Omfg I was so unfunny at the time)

                    makepoly(12);

                    if (pad & PADstart) {
                        resetgame(0);
                        menu = 2;
                    }
                } else{staticframes--;}
            break;//Game over screen. ALWAYS BEGIN WITH THE STATIC
        }
        FntFlush(-1); //Draw
        display(); //Always here        
    }
    return 0;
}