void animatronicFunc(int init) {
    if (init == 1) {
        springtrapAI = night;
        springtrapinactive = false;
        switch(night) {
            case 1:
                ventilhealthtimerconst = 999999999; //Not supposed to have this yet
                springtrapAI--; //Equals to 0, not supposed to be here yet
                springtrapinactive = true;
            break;
            case 2: 
                ventilhealthtimerconst = 720;
            break;
            case 3: 
                ventilhealthtimerconst = 600;
            break;
            case 4: 
                ventilhealthtimerconst = 540;
            break;
            case 5:  
                ventilhealthtimerconst = 480;
            break;
            case 6: 
                ventilhealthtimerconst = 420; //Hope I don't make the same bug as him (Scott) (apparently he fucked something up) (Idk a youtuber told me that) (I don't remember his name) (                             e) (<-- Not a bug, it's a feature!) (told by the guy who don't know how to render simple prims) ( bro, why are telling this ?? :( ) (hahahaha I'm Schizophrenic)
                springtrapAI++; //That's my project I can type whatever I want, even if I got dementia ! That's my project, I can type whatever I want, even if I got dementia! That is my project I can type whatever I want, even when I got dementia !
            break; //I think I'll stop doing that
        }
        ventilhealthtimer = ventilhealthtimerconst; //Always set it to the constant


        if (springtrapinactive) {return;}
        
        springtraplocation[0] = 0;
        Ran(5);
        springtraplocation[1] = 6 + RAN; //6 + between 0 and 4; he randomly generates to be anywhere between these cams.

        if (springtraplocation[1] == 10) {springtraplocation[1] = 0; springtraplocation[0]++;}
    }
    if ((AM == 4 || AM == 5) && FrameCounter == 0) {
        isagressive = true; //At 4AM AND 5AM, springtrap become agressive.
    }
}   

void SpringtrapVentCheck(void) {
    if (ventlocked == springtraplocation[0] + springtraplocation[1] + 9) { //If he DON'T pass through,
        switch(springtraplocation[1]) {
            case 1:
                springtraplocation[0] = 0;
                springtraplocation[1] = 9;
            break;
            case 2:
                springtraplocation[0] = 0;
                springtraplocation[1] = 7;
            break;
            case 3:
                springtraplocation[0] = 0;
                springtraplocation[1] = 5;
            break;
            case 4:
                springtraplocation[0] = 1;
                springtraplocation[1] = 0;
            break;
            case 5:
                springtraplocation[0] = 0;
                springtraplocation[1] = 2;
            break;
        }//loser
    } else {//If he pass through,
        switch(springtraplocation[1]) {
            case 1:
                springtraplocation[0] = 0;
                springtraplocation[1] = 1;
            break;
            case 2:
                springtraplocation[0] = 0;
                springtraplocation[1] = 1;
            break;
            case 3:
                springtraplocation[0] = 0;
                springtraplocation[1] = 2;
                stage = 1;
            break;
            case 4:
                springtraplocation[0] = 0;
                springtraplocation[1] = 0;
                stage = 5;
                springtrapbehindcamera = true;
            break;
            case 5:
                springtraplocation[0] = 0;
                springtraplocation[1] = 0;
                stage = 5;
                springtrapbehindcamera = true;
            break;
        }//shit
    }
    isspringtrapvents = false;
    SpringsAction2 = SpringsAction;
    SpringsAction = 0;
    Springstotalturns = 0;
}
void screamer(void) {
    if (camerastate) {
        if (spritecamera == 5) {CameraFunc(0);}
        if (stage != 5) { return; }
    } else {
        screamerframes--;
        
        if (spriteframes == 0) {
            spritesheet++;

            clearVRAMgeneral(576, 256, 30, 106);

            if (stage == 5) {
                if (isontherightside) {
                    switch(spritesheet) {
                        case 1:
                            SpuSetKey(SPU_ON, SPU_04CH);
                            LoadTexture(_binary_tim_screamer_Springtrap2_1_tim_start, &jumpscare);
                        break;
                        case 2:
                            LoadTexture(_binary_tim_screamer_Springtrap2_2_tim_start, &jumpscare);
                        break;
                        case 3:
                            LoadTexture(_binary_tim_screamer_Springtrap2_3_tim_start, &jumpscare);
                        break;
                        case 4:
                            LoadTexture(_binary_tim_screamer_Springtrap2_4_tim_start, &jumpscare);
                        break;
                        case 5:
                            LoadTexture(_binary_tim_screamer_Springtrap2_5_tim_start, &jumpscare);
                        break;
                        case 6:
                            LoadTexture(_binary_tim_screamer_Springtrap2_6_tim_start, &jumpscare);
                        break;
                        case 7:
                            LoadTexture(_binary_tim_screamer_Springtrap2_7_tim_start, &jumpscare);
                        break;
                        case 8:
                            LoadTexture(_binary_tim_screamer_Springtrap2_8_tim_start, &jumpscare);
                        break;
                        case 9:
                            LoadTexture(_binary_tim_screamer_Springtrap2_9_tim_start, &jumpscare);
                        break;
                        case 10:
                            LoadTexture(_binary_tim_screamer_Springtrap2_10_tim_start, &jumpscare);
                        break;
                        case 11:
                            LoadTexture(_binary_tim_screamer_Springtrap2_11_tim_start, &jumpscare);
                        break;
                        case 12:
                            LoadTexture(_binary_tim_screamer_Springtrap2_12_tim_start, &jumpscare);
                        break;
                        case 13:
                            dead = true;
                            jumpscared = false;
                            menu = 4;
                        break;
                    }
                } else {
                    switch(spritesheet) {
                        case 1:
                            SpuSetKey(SPU_ON, SPU_04CH);
                            LoadTexture(_binary_tim_screamer_Springtrap_1_tim_start, &jumpscare);
                        break;
                        case 2:
                            LoadTexture(_binary_tim_screamer_Springtrap_2_tim_start, &jumpscare);
                        break;
                        case 3:
                            LoadTexture(_binary_tim_screamer_Springtrap_3_tim_start, &jumpscare);
                        break;
                        case 4:
                            LoadTexture(_binary_tim_screamer_Springtrap_4_tim_start, &jumpscare);
                        break;
                        case 5:
                            LoadTexture(_binary_tim_screamer_Springtrap_5_tim_start, &jumpscare);
                        break;
                        case 6:
                            LoadTexture(_binary_tim_screamer_Springtrap_6_tim_start, &jumpscare);
                        break;
                        case 7:
                            LoadTexture(_binary_tim_screamer_Springtrap_7_tim_start, &jumpscare);
                        break;
                        case 8:
                            LoadTexture(_binary_tim_screamer_Springtrap_8_tim_start, &jumpscare);
                        break;
                        case 9:
                            LoadTexture(_binary_tim_screamer_Springtrap_9_tim_start, &jumpscare);
                        break;
                        case 10:
                            LoadTexture(_binary_tim_screamer_Springtrap_10_tim_start, &jumpscare);
                        break;
                        case 11:
                            LoadTexture(_binary_tim_screamer_Springtrap_11_tim_start, &jumpscare);
                        break;
                        case 12:
                            LoadTexture(_binary_tim_screamer_Springtrap_12_tim_start, &jumpscare);
                        break;
                        case 13:
                            LoadTexture(_binary_tim_screamer_Springtrap_13_tim_start, &jumpscare);
                        break;
                        case 14:
                            dead = true;
                            jumpscared = false;
                            menu = 4;
                        break;
                    }
                }
                spriteframes = 3;
            }
            if (isballonboyofficehere) {
                switch(spritesheet) {
                    case 1:
                        SpuSetKey(SPU_ON, SPU_04CH);
                        LoadTexture(_binary_tim_screamer_BB_BBJUMP1_tim_start, &jumpscare);
                    break;
                    case 2:
                        LoadTexture(_binary_tim_screamer_BB_BBJUMP2_tim_start, &jumpscare);
                    break;
                    case 3:
                        LoadTexture(_binary_tim_screamer_BB_BBJUMP3_tim_start, &jumpscare);
                    break;
                    case 4:
                        LoadTexture(_binary_tim_screamer_BB_BBJUMP4_tim_start, &jumpscare);
                    break;
                    case 5:
                        LoadTexture(_binary_tim_screamer_BB_BBJUMP5_tim_start, &jumpscare);
                    break;
                    case 6:
                        LoadTexture(_binary_tim_screamer_BB_BBJUMP6_tim_start, &jumpscare);
                    break;
                    case 7:
                        LoadTexture(_binary_tim_screamer_BB_BBJUMP7_tim_start, &jumpscare);
                    break;
                    case 8:
                        LoadTexture(_binary_tim_screamer_BB_BBJUMP8_tim_start, &jumpscare);
                    break;
                    case 9:
                        LoadTexture(_binary_tim_screamer_BB_BBJUMP9_tim_start, &jumpscare);
                    break;
                    case 10:
                        ballonboyqueued = false;
                        isballonboyofficehere = false;
                        jumpscared = false;
                        spritesheet = 0;
                        if (!noerrors) {ventilationfailure = true;}
                        officefadingout = 1;
                        ventilhealth = 0;
                        fadeoffice = 0;
                        ballonboydeactivated = true;
                        heavybreathing = true;
                        SpuSetKey(SPU_ON, SPU_10CH);
                        isagressive = true;
                    break;
                }
                spriteframes = 3;
            }
            if (ischicaofficehere) {
                switch(spritesheet) {
                    case 1:
                        SpuSetKey(SPU_ON, SPU_04CH);
                        LoadTexture(_binary_tim_screamer_Chica_CHJUMP1_tim_start, &jumpscare);
                    break;
                    case 2:
                        LoadTexture(_binary_tim_screamer_Chica_CHJUMP2_tim_start, &jumpscare);
                    break;
                    case 3:
                        LoadTexture(_binary_tim_screamer_Chica_CHJUMP3_tim_start, &jumpscare);
                    break;
                    case 4:
                        LoadTexture(_binary_tim_screamer_Chica_CHJUMP4_tim_start, &jumpscare);
                    break;
                    case 5:
                        LoadTexture(_binary_tim_screamer_Chica_CHJUMP5_tim_start, &jumpscare);
                    break;
                    case 6:
                        LoadTexture(_binary_tim_screamer_Chica_CHJUMP6_tim_start, &jumpscare);
                    break;
                    case 7:
                        chicaqueued = false;
                        ischicaofficehere = false;
                        jumpscared = false;
                        spritesheet = 0;
                        if (!noerrors) {ventilationfailure = true;}
                        officefadingout = 1;
                        ventilhealth = 0;
                        fadeoffice = 0;
                        chicadeactivated = true;
                        heavybreathing = true;
                        SpuSetKey(SPU_ON, SPU_10CH);
                        isagressive = true;
                    break;
                }
                spriteframes = 3;
            }
            if (freddygotu) {  
                switch(spritesheet) {
                    case 1:
                        SpuSetKey(SPU_ON, SPU_04CH);
                        LoadTexture(_binary_tim_screamer_Freddy_FJUMP1_tim_start, &jumpscare);
                    break;
                    case 2:
                        LoadTexture(_binary_tim_screamer_Freddy_FJUMP2_tim_start, &jumpscare);
                    break;
                    case 3:
                        LoadTexture(_binary_tim_screamer_Freddy_FJUMP3_tim_start, &jumpscare);
                    break;
                    case 4:
                        LoadTexture(_binary_tim_screamer_Freddy_FJUMP4_tim_start, &jumpscare);
                    break;
                    case 5:
                        LoadTexture(_binary_tim_screamer_Freddy_FJUMP5_tim_start, &jumpscare);
                    break;
                    case 6:
                        LoadTexture(_binary_tim_screamer_Freddy_FJUMP6_tim_start, &jumpscare);
                    break;
                    case 7:
                        LoadTexture(_binary_tim_screamer_Freddy_FJUMP7_tim_start, &jumpscare);
                    break;
                    case 8:
                        freddygotu = false;
                        freddytimeseen = 360;
                        jumpscared = false;
                        spritesheet = 0;
                        if (!noerrors) {ventilationfailure = true;}
                        officefadingout = 1;
                        ventilhealth = 0;
                        fadeoffice = 0;
                        freddydeactivated = true;
                        heavybreathing = true;
                        SpuSetKey(SPU_ON, SPU_10CH);
                        isagressive = true;
                    break;
                }
                spriteframes = 3;
            }
            if (foxyscreamer) {
                switch(spritesheet) {
                    case 1:
                        isfoxyofficehere = false;
                        SpuSetKey(SPU_ON, SPU_04CH);
                        LoadTexture(_binary_tim_screamer_Foxy_1_tim_start, &jumpscare);
                    break;
                    case 2:
                        LoadTexture(_binary_tim_screamer_Foxy_2_tim_start, &jumpscare);
                    break;
                    case 3:
                        LoadTexture(_binary_tim_screamer_Foxy_3_tim_start, &jumpscare);
                    break;
                    case 4:
                        LoadTexture(_binary_tim_screamer_Foxy_4_tim_start, &jumpscare);
                    break;
                    case 5:
                        LoadTexture(_binary_tim_screamer_Foxy_5_tim_start, &jumpscare);
                    break;
                    case 6:
                        LoadTexture(_binary_tim_screamer_Foxy_6_tim_start, &jumpscare);
                    break;
                    case 7:
                        LoadTexture(_binary_tim_screamer_Foxy_7_tim_start, &jumpscare);
                    break;
                    case 8:
                        LoadTexture(_binary_tim_screamer_Foxy_8_tim_start, &jumpscare);
                    break;
                    case 9:
                        LoadTexture(_binary_tim_screamer_Foxy_9_tim_start, &jumpscare);
                    break;
                    case 10:
                        LoadTexture(_binary_tim_screamer_Foxy_10_tim_start, &jumpscare);
                    break;
                    case 11:
                        LoadTexture(_binary_tim_screamer_Foxy_11_tim_start, &jumpscare);
                    break;
                    case 12:
                        foxyscreamer = false;
                        jumpscared = false;
                        spritesheet = 0;
                        if (!noerrors) {ventilationfailure = true;}
                        officefadingout = 1;
                        ventilhealth = 0;
                        fadeoffice = 0;
                        heavybreathing = true;
                        SpuSetKey(SPU_ON, SPU_10CH);
                        isagressive = true;
                    break;
                }
                spriteframes = 3;
            }
        } else {spriteframes--;}
        makepoly(14);
    }
}

void AIact(void) {
    if (freddyframes < 1) {
        Ran(11);
        if (freddyAI > RAN) {isfreddyofficehere = true;}
        freddyframes = 3600;
    } else {freddyframes--;}

    if (ballonboyframes < 1) {
        if (camera == 0 || !((curcam[0] == 1 && curcam[1] == 0) ||(curcam[0] == 0 && curcam[1] == 1) ||(curcam[0] == 0 && curcam[1] == 7) ||(curcam[0] == 0 && curcam[1] == 9))) {
            Ran(11);
            if (ballonboyAI > RAN) {
                ballonboyqueued = true;
            }
            ballonboyframes = 1200;
        }
    } else {ballonboyframes--;}

    if (mangleframes < 1) {
        if (!(curcam[0] == 0 && curcam[1] == 4)) {
            Ran(11);
            if (mangleAI > RAN) {
                manglequeued = true;
            }
            mangleframes = 1200;
        }
    } else {mangleframes--;}

    if (puppetframes < 1) {
        if (camera == 0 || !(curcam[0] == 0 && curcam[1] == 8)) {
            Ran(11);
            if (puppetAI > RAN) {
                puppetqueued = true;
            }
            puppetframes = 1200;
        }
    } else {puppetframes--;}

    if (chicaframes < 1) {
        if (camera == 0 || !(curcam[0] == 0 && curcam[1] == 7)) {
            Ran(11);
            if (chicaAI > RAN) {
                chicaqueued = true;
            }
            chicaframes = 1200;
        }
    } else {chicaframes--;}

    if (!camerasystemfailure && camerastatic > 85) {
        ballonboyseen = 51;
        puppetseen = 54;
        mangleseen = 54;
        chicaseen = 54;
    } //Because else it's unfair

    if (ballonboyseen < 1 && (chicaqueued == false && curcam[1] == 7)) {
        isballonboyofficehere = true;
        jumpscared = true;
        ballonboyqueued = false;
        ballonboyseen = 51;
    }

    if (puppetseen == 0) {
        if (camera == 1) {CameraFunc(0);}
        ispuppetofficehere = true;
        puppetqueued = false;
        puppetseen = 54;
        MovVectorpuppet.vx = MovVectorofficemiddle.vx + 40; 
        
        officefadingout = 1;
    }

    if (mangleseen == 0) {
        ismangleofficehere = true;
        if (camera == 1) {CameraFunc(0);}
        manglequeued = false;
        mangleseen = 54;

        if (!noerrors) {abletoplaysound = false; audiodevicehealth = 0;} 
    }

    if (chicaseen == 0 && !ballonboyqueued) {
        ischicaofficehere = true;
        jumpscared = true;

        chicaqueued = false;
        chicaseen = 54;
    }

    if (ismangleofficehere) {
        if (MovVectorofficemangle.vy < 25 && MovVectorofficemangle.vy > 15 && mangleframesdisappear > 0) {
            if (FrameCounter % 7 == 1) {
                MovVectorofficemangle.vy--;
            }
        }
        if (mangleframesdisappear < 0) {
            int soundreducing = 0x2500 - MovVectorofficemangle.vy * 200;
            SpuSetVoiceVolume(12,soundreducing,soundreducing);
            if (MovVectorofficemangle.vy < 30) {
                if (FrameCounter % 7 == 1) {
                    MovVectorofficemangle.vy++;
                }
            } else {
                ismangleofficehere = false;
                isagressive = true;
                SpuSetKey(SPU_OFF,SPU_12CH);
                mangleframesdisappear = 780;
                MovVectorofficemangle.vy = 20;
            }
        }
        if (SpuGetKeyStatus(SPU_12CH) == SPU_OFF) {
            SpuSetKey(SPU_ON,SPU_12CH);
        }
    }

    if (ismangleofficehere) {mangleframesdisappear--;}

    if (ispuppetofficehere) {
        if (SpuGetKeyStatus(SPU_23CH) == SPU_OFF) {
            SpuSetKey(SPU_ON,SPU_23CH);
        }

        if (puppetframesdisappear <= 0) {
            ispuppetofficehere = false;
            puppetleaving = 120;
            puppetframesdisappear = 1000;
            officefadingout = -1;
        } else {puppetframesdisappear--;}
    }

    if (isfoxyofficehere) {
        if (MovVectorofficemiddle.vx > -20) {
            jumpscared = true;
            foxyscreamer = true;
        }
    }

    if (puppetleaving > 0) {
        MovVectorpuppet.vx -= 4;
        puppetleaving--;
    }

    if (!ispuppetofficehere && SpuGetKeyStatus(SPU_23CH) == SPU_ON) {SpuSetKey(SPU_OFF, SPU_23CH);}

    if (spritecamerago == 4) {
        switch(night) {
            case 2:
                Ran(1001);
            break;
            case 3:
                Ran(51);
            break;
            case 4:
                Ran(26);
            break;
            case 5:
                Ran(11);
            break;

            default:
                Ran(51);
            break;
        }

        if (RAN == 1) {isfoxyofficehere = true;} else {isfoxyofficehere = false;}
    } //FOXY    

    if (springtrapbehindcamera && !camera) {
        jumpscared = true;
        springtrapbehindcamera = false;
    } 

    if (MovVectorofficemiddle.vx > 50) {springtrapinviewrange = true;} else {springtrapinviewrange = false;}

    if (MovVectorofficemiddle.vx > 20) {springtrapsooninviewrange = true;} else {springtrapsooninviewrange = false;}

    if (retainspringtrapleaving && camerastate) {
        stage = 2;
        retainspringtrapleaving = false;
    } //Used when player is looking at him when doing a succesful move. Will not move until camera opened up

    if (inactiveframes > 600 || ventilationfailure) {//Greater than 10 secs or ventilation error
        isagressive = true;
    }

    if (audiolureworked) {
        switch(timeruntillured) {
            case -1:
                Ran(100);
                timeruntillured = RAN;
                audiolureloc[0] = curcam[0];
                audiolureloc[1] = curcam[1];
            break;
            case 0:
                //2 general conditions, 4 special ones 

                if (springtraplocation[1] - 1 == audiolureloc[1] || //General = If his location is closer to you (mostly)
                    springtraplocation[1] + 1 == audiolureloc[1] || //General = If his location is more distant to you (mostly)
                    springtraplocation[1] == 5 && audiolureloc[1] == 8 || //Special = If his location is 05 and the audiolure is 08
                    (springtraplocation[1] == 2 || springtraplocation[1] == 8 ) && audiolureloc[1] == 5 || //Special = If his location is 02 or 08 and audiolure is 05
                    springtraplocation[0] == 1 && audiolureloc[1] == 9 || //Special = If his location is 10 and audiolure is 09. don't need to check for springtraplocation[1], since he can only go up to cam 10
                    springtraplocation[0] == 0 && springtraplocation[1] == 9 && audiolureloc[0] == 1 ) { //Special = If his location is 09 and audiolure is 10.  

                    if (isspringtrapvents) {return;}//In case he's on the vents
                    if (springtraplocation[0] == 0 && springtraplocation[1] == 1) {return;} //In case he's on cam 01, not supposed to go cam 02

                    springtraplocation[1] = audiolureloc[1];
                    springtraplocation[0] = audiolureloc[0];

                    springtrapnoise = true;

                    if (stage == 1) {springtraplocation[1] = 2; stage = 0;}//When he's looking at you, can come back to cam 02

                    Springstotalturns = 0;
                    movecounter = 0;
                }

                audiolureworked = false;
                timeruntillured = -1;
            break;
            default:
                timeruntillured--;
            break;
        }
    }

    if (jumpscared && !springtrapskip && !isspringtrapvents) {
        if (springtraplocation[1] > 5 && (springtraplocation[1] < 0 && springtraplocation[0] == 1)) {
            Ran(4);
            switch(RAN) {
                case 1:
                    springtraplocation[1] = 4;
                    movecounter = 0;
                break;
                case 2:
                    springtraplocation[1] = 5;
                    movecounter = 0;
                    
                break;
                case 3:
                    springtraplocation[0] = 1;
                    springtraplocation[1] = 0;
                    movecounter = 0;
                break;

            }
        }
        if (springtraplocation[1] == 5) {
            springtraplocation[1] = 2;
            movecounter = 0;
        }
        if (springtraplocation[1] == 2) {
            stage = 1;
            movecounter = 0;
        }
        springtrapskip = true;
    }

    if (springtraplocation[0] != OLDspringtraplocation[0] || springtraplocation[1] != OLDspringtraplocation[1]) {
        if (camera && (curcam[0] == OLDspringtraplocation[0] && curcam[1] == OLDspringtraplocation[1] || curcam[0] == springtraplocation[0] && curcam[1] == springtraplocation[1])) {
            Ran(60);
            springtrapblockcam = 60 + RAN;
        }
        OLDspringtraplocation[0] = springtraplocation[0];
        OLDspringtraplocation[1] = springtraplocation[1];
    } //Static when springtrap move

    if (onesecondvar == 1) {
        //Special for when springtrap is peeking and you're with the camera
        if (stage == 4 && camera) {
            Ran(3);
            if (RAN == 1) {
                stage = 5;
                isspringtraprunningtoyou = true;
            }
        }

        SpringsAction2 = -1; //Not set

        if (!aggressive) {movecounter++;} else {movecounter += 2;}
        
        Springstotalturns++;
        Ran(16);
        if (movecounter > (10 - springtrapAI - isagressive + RAN - Springstotalturns)) {
            if (springtrapinactive) {return;}
            if (isspringtrapvents) {SpringtrapVentCheck();return;}
            movecounter = 0;
            (isagressive) ? Ran2(5) : Ran2(4);
            SpringsAction = RAN2;
        }
    }

    if (springtraphide && springtrapsooninviewrange) {
        springtraphidegone = true;
    }

    if (stage != 3) {springtraphide = false;}

    if (alarmstate > 0) {if (SpuGetKeyStatus(SPU_22CH) == false) {SpuSetKey(SPU_ON, SPU_22CH);}} else {SpuSetKey(SPU_OFF,SPU_22CH);}
    
    if (blackout) {
        if (stage == 1) {stage = 2;}

        if (stage == 3) {
            (isagressive) ? Ran(5) : Ran(4);

            if (RAN > 2) {stage = 4;} else {stage = 0; springtraplocation[1] = 1;} //Stage 0 for Cam 01
        }

        if (stage == 0 && springtraplocation[1] == 1) {stage = 4;}

        if (stage == 4) {stage = 5;}

        return;
    } //Speedrunning during blackout

    if (MovVectorofficemiddle.vx > 50 && stage == 5) {lockleft = true;}

    if (MovVectorofficemiddle.vx > 70 && stage == 5) {jumpscared = true;}

    switch(SpringsAction) {
        default:
            return;
        break;
        case 1:
            SpringsAction2 = SpringsAction;
            SpringsAction = 0; //Loser HAHA U don't do ANY THING
        break;
        case 2:
            if (stage == 1 || stage == 2) {return;}

            springtrapnoise = true;

            switch(springtraplocation[1]) {
                case 0:
                    springtraplocation[1]--;
                    //He must move forward ! Shit !
                break; //Cam 10
                case 5:
                    Ran(3);
                    if (RAN == 1) {
                        springtraplocation[1]++;
                    } else {
                        springtraplocation[1] = 8;
                    }
                break; //Cam 05
                case 2:
                    if (stage == 1 || stage == 2) {return;} //Cannot when in special stages
                    Ran(3);
                    if (RAN == 1) {
                        springtraplocation[1]++;
                    } else {
                        springtraplocation[1] = 5;
                    }
                break; //Cam 02
                case 1:
                    if (stage == 3) {
                        stage = 0; 

                        Ran(60);
                        springtrapblockcam = 60 + RAN;
                    } //If hiding, go to cam 01 (stage 0 in cam 01, yes). If not,

                    if (!maintenancepanel && springtrapinviewrange) {return;}

                    if (stage == 4) { //If he's peeking and you're not looking at him or in maintenance panel,
                        stage = 5; //You're dead.
                        springtrapnoise = false;
                    } else { //If he's not,
                        stage = 4; //He'll look at you. 👁️👁️ And again. 👁️👁️And again. 👁️👁️And again. 👁️👁️And again. 👁️👁️And again. 👁️👁️And again. 👁️👁️
                        springtrapnoise = false;

                        Ran(60);
                        springtrapblockcam = 60 + RAN;
                    }

                break; //Cam 01, must move ;'(
                default:
                    springtraplocation[1]++;
                break;
            }
            SpringsAction2 = SpringsAction;
            SpringsAction = 0;
            Springstotalturns = 0;
            //Go back, ha ha
        break;
        case 3:
            springtrapnoise = true;

            switch(springtraplocation[1]) {
                case 5:
                    Ran(3);
                    if (RAN == 1) {
                        springtraplocation[1]--;
                    } else {
                        springtraplocation[1] = 2;
                    }
                break; //Cam 05
                case 8:
                    Ran(3);
                    if (RAN == 1) {
                        springtraplocation[1]--;
                    } else {
                        springtraplocation[1] = 5;
                    }
                break; //Cam 08
                case 2:
                    if (stage != 1) {
                        stage = 1;            

                        Ran(60);
                        springtrapblockcam = 60 + RAN;
                    } else {
                        if (!camera) {retainspringtrapleaving = true;} else {
                            stage = 2; //Only when going for cam 01.
                            springtrapnoise = false;
                        }
                    }
                break;//Cam 02
                case 1:
                    if (!maintenancepanel && springtrapinviewrange) {return;}

                    if (stage != 4) {
                        stage = 4;
                        springtrapnoise = false;
                    } else {
                        stage = 5;
                        springtrapnoise = false;
                    }
                break; //Cam 01
                case 0:
                    if (springtraplocation[0] == 0) {
                        stage = 5; springtrapnoise = false;
                    } else {
                        springtraplocation[1]--;
                    }
                break;
                default:
                    springtraplocation[1]--;
                break;
            }
            SpringsAction2 = SpringsAction;
            SpringsAction = 0;
            Springstotalturns = 0;
            //Go forward, oh no
        break;
        case 4:
            if (springtraplocation[0] == 0) {
                switch(springtraplocation[1]) {
                    case 9:
                        isspringtrapvents = true;
                        springtraplocation[1] = 1;
                        springtraplocation[0] = 1;
                        SpuSetKey(SPU_ON, SPU_16CH);
                    break;//Cam 09 > 11
                    case 7:
                        isspringtrapvents = true;
                        springtraplocation[0] = 1;
                        springtraplocation[1] = 2;
                        SpuSetKey(SPU_ON, SPU_16CH);
                    break;//Cam 07 > 12
                    case 5:
                        isspringtrapvents = true;
                        springtraplocation[0] = 1;
                        springtraplocation[1] = 3;
                        SpuSetKey(SPU_ON, SPU_16CH);
                    break;//Cam 05 > 13
                    case 2:
                        isspringtrapvents = true;
                        springtraplocation[0] = 1;
                        springtraplocation[1] = 5;
                        SpuSetKey(SPU_ON, SPU_16CH);
                    break;//Cam 02 > 15
                    default :
                        if (springtraplocation[1] == 2) {
                            if (stage != 1) {
                                stage = 1;

                                Ran(60);
                                springtrapblockcam = 60 + RAN;
                                return;
                            } else {
                                if (!camera) {retainspringtrapleaving = true;} else {
                                    stage = 2; //Only when going for cam 01.
                                }
                                return;
                            }   
                        }

                        if (stage == 3) {
                            if (!maintenancepanel && springtrapinviewrange) {return;}
                            stage = 4; 
                            return;
                        } 
                        if (stage == 4) {
                            if (!maintenancepanel && springtrapinviewrange) {return;}
                            stage = 5;
                            springtrapnoise = false;
                        }

                        springtraplocation[1]--;
                        springtrapnoise = true;
                    break; //If there's no vents, move forward
                }
            } else {
                isspringtrapvents = true; 
                springtraplocation[1] = 4;
                SpuSetKey(SPU_ON, SPU_16CH);
            }//Cam 10 > 14

            SpringsAction2 = SpringsAction;
            SpringsAction = 0;
            Springstotalturns = 0;
            //Go vent, oh no no no
        break;
    }

    if (springtraplocation[1] > 9 && !isspringtrapvents) {
        springtraplocation[0]++;
        springtraplocation[1] = 0;
    }

    if (!isspringtrapvents && springtraplocation[0] == 1 && springtraplocation[1] != 0) {
        springtraplocation[0]--;
        springtraplocation[1] = 9;
    }//If Spring Bing is not on the vents, and its second location is another thing than 0 WHEN its first is 1, put it at 09. (Only occuring when transitionning from 10 to 09)

    if (springtrapnoise) {
        Ran(25);
        SpuSetKey(SPU_ON, SPU_06CH);
        springtrapnoise = false;
    }
}

void MaintenancePanelStuff(void) {

    if (stage == 5 && maintenancepanel) {consoleFunc();}

    if (currentlyrepairing) {timerepairing++;}

    if (timerepairing % 60 == 0 && timerepairing > 0) { //Every seconds
        SpuSetKey(SPU_ON, SPU_18CH);
        switch(maintenancepanelselection) {
            case 0:
                Ran(4);
                camerahealth += RAN;
                if (camerahealth > 9) {
                    camerahealth = 10; //Just to make sure !
                    camerasystemfailure = false;
                    currentlyrepairing = false;
                    timerepairing = 0;
                }
            break;
            case 1:
                Ran(4);
                audiodevicehealth += RAN;
                if (audiodevicehealth > 9) {
                    audiodevicehealth = 10; //Just to make sure !
                    abletoplaysound = true;
                    currentlyrepairing = false;
                    timerepairing = 0;
                }
            break;
            case 2:
                Ran(4);
                ventilhealth += RAN;
                if (ventilhealth > 9) {
                    ventilhealth = 10; //Just to make sure !
                    ventilationfailure = false;
                    currentlyrepairing = false;
                    timerepairing = 0;
                    heavybreathing = false;
                    officefadingout = -1;
                }

            break;
        }//Reboot all is separated bcs it's every 2 seconds
    }
    if (timerepairing % 120 == 0 && timerepairing > 0) {
        if (maintenancepanelselection == 3) {
            Ran(4);
            if (camerahealth < 10) {camerahealth += RAN;} else {camerahealth = 10;}
            if (audiodevicehealth < 10) {audiodevicehealth += RAN;} else {audiodevicehealth = 10;}
            if (ventilhealth < 10) {ventilhealth += RAN;} else {ventilhealth = 10;}

            if (ventilhealth == 10 && camerahealth == 10 && audiodevicehealth == 10){
                ventilationfailure = false;
                camerasystemfailure = false;
                abletoplaysound = true;
                timerepairing = 0;
                currentlyrepairing = false;
                heavybreathing = false;
            }

        }
    }

    if (timerepairing % 30 == 0 && currentlyrepairing || timertolock % 30 == 0 && currentlysealing) {if (reloadingframe < 4) {reloadingframe++;} else {reloadingframe = 0;}} //For the animation of the loading dot when REPAIRING and SEALING

    if (spritemaintenancepanel > 0) {makepoly(7);}

    if (maintenancepanel == false && spritemaintenancepanel != 0) {
        if (spritesheet == 0) {
            switch(spritemaintenancepanel) {
                case 1:
                    clearVRAMgeneral(980, 49, 44, 140);
                    LoadTexture(_binary_tim_office_panelsprite_PANEL5_tim_start, &mpanel);
                break;
                case 2:
                    clearVRAMgeneral(980, 49, 44, 140);
                    LoadTexture(_binary_tim_office_panelsprite_PANEL4_tim_start, &mpanel);
                break;
                case 3:
                    clearVRAMgeneral(980, 49, 44, 140);
                    LoadTexture(_binary_tim_office_panelsprite_PANEL3_tim_start, &mpanel);
                break;
                case 4:
                    clearVRAMgeneral(980, 49, 44, 140);
                    LoadTexture(_binary_tim_office_panelsprite_PANEL2_tim_start, &mpanel);
                break;
                case 5:
                    clearVRAMgeneral(980, 49, 44, 140);
                    LoadTexture(_binary_tim_office_panelsprite_PANEL1_tim_start, &mpanel);
                break;
            }
        }

        if (spritesheetpanel != 0 && spritemaintenancepanel != 1) {spritesheetpanel--;} else {spritesheetpanel = 4; spritemaintenancepanel--;}
    }
    if (maintenancepanel) {
        if (spritemaintenancepanelgo && spritemaintenancepanel < 6) {

            if (spritesheet == 0) {
                switch(spritemaintenancepanel) {
                    case 0:
                        clearVRAMgeneral(980, 49, 44, 140);
                        LoadTexture(_binary_tim_office_panelsprite_PANEL5_tim_start, &mpanel);
                    break;
                    case 1:
                        clearVRAMgeneral(980, 49, 44, 140);
                        LoadTexture(_binary_tim_office_panelsprite_PANEL4_tim_start, &mpanel);
                    break;
                    case 2:
                        clearVRAMgeneral(980, 49, 44, 140);
                        LoadTexture(_binary_tim_office_panelsprite_PANEL3_tim_start, &mpanel);
                    break;
                    case 3:
                        clearVRAMgeneral(980, 49, 44, 140);
                        LoadTexture(_binary_tim_office_panelsprite_PANEL2_tim_start, &mpanel);
                    break;
                    case 4:
                        clearVRAMgeneral(980, 49, 44, 140);
                        LoadTexture(_binary_tim_office_panelsprite_PANEL1_tim_start, &mpanel);
                    break;
                    case 5:
                        LoadTexture(_binary_tim_office_panelsprite_PANEL0_tim_start, &mpanel);
                        spritemaintenancepanelgo = false;

                        LoadTexture(_binary_tim_Mpanel_MENU_tim_start, &maintenance_text); 
                        LoadTexture(_binary_tim_Mpanel_RESTART_tim_start, &maintenance_text);  //In case sintrap replaced the VRAM 
                    break;
                } 
            }    
            if (spritesheetpanel != 0) {spritesheetpanel--;} else {spritesheetpanel = 4; spritemaintenancepanel++;}
        }

        if (spritemaintenancepanel == 5) {
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
                if (maintenancepanelselection != 4) {SpuSetKey(SPU_ON, SPU_18CH); currentlyrepairing = true;}
                switch (maintenancepanelselection) {
                    case 0:
                        MovVectormaintenance_loadco.vy = -3;
                    break;      

                    case 1:
                        MovVectormaintenance_loadco.vy = 5;
                    break; 

                    case 2:
                        MovVectormaintenance_loadco.vy = 13;
                    break; 

                    case 3:
                        MovVectormaintenance_loadco.vy = 29;
                    break; 

                    case 4:
                        maintenancepanel = false;
                        SpuSetKey(SPU_ON, SPU_20CH);
                    break; 
                } 
            }
        }
    }
}

void CameraMonitorStuff(void) {
    if (springtrapbehindcamera) {
        if (onesecondvar == 1) {
            Ran(3);
            if (RAN == 2) {
                CameraFunc(0);
            }
        }
    }

    if (spritecamera > 0) {makepoly(8);}

    if (SpuGetKeyStatus(SPU_21CH) == SPU_ON && !camera) {SpuSetKey(SPU_OFF, SPU_21CH);}

    if (camera && spritecamera == 5) { //Cam things
        cameraloc();
        if (camerahealthtimer == 0) {
            camerahealthtimer = 720;
            Ran(3);
            if (!noerrors) {camerahealth -= springtrapAI;}
            if (camerahealth < 1) {camerasystemfailure = true;}
        } else {camerahealthtimer--;}
    }

    if (cooldowncamera > 0) {cooldowncamera--;}
    if (cooldowncamera == 5 && camera) {SpuSetKey(SPU_ON, SPU_17CH);}

    if (BBsoundcooldown > 0) {BBsoundcooldown--;}

    if (camera) {
        if (spritecamerago && spritecamera < 5) {
            if (spritesheetcamera == 0) {
                switch(spritecamera) {
                    case 0:
                        clearVRAMgeneral(914, 94, 46, 142);
                        LoadTexture(_binary_tim_camera_panel_1_tim_start, &panel);
                    break;
                    case 1:
                        clearVRAMgeneral(914, 94, 46, 142);
                        LoadTexture(_binary_tim_camera_panel_2_tim_start, &panel);
                    break;
                    case 2:
                        clearVRAMgeneral(914, 94, 46, 142);
                        LoadTexture(_binary_tim_camera_panel_3_tim_start, &panel);
                    break;
                    case 3:
                        clearVRAMgeneral(914, 94, 46, 142);
                        LoadTexture(_binary_tim_camera_panel_4_tim_start, &panel);
                    break;
                    case 4:
                        clearVRAMgeneral(914, 94, 46, 142);
                        LoadTexture(_binary_tim_camera_panel_5_tim_start, &panel);
                        SpuSetKey(SPU_ON, SPU_21CH);
                        camerastate = true;
                        camerastatic = 100;
                    break;
                    case 5:
                        spritecamerago = false;
                    break;
                }

            }
            if (spritesheetcamera != 0) {spritesheetcamera--;} else {spritesheetcamera = 4; spritecamera++;}
        }
    }
    if (!camera && spritecamera != 0) {
        if (spritesheetcamera == 0) {
            switch(spritecamera) {
                case 1:
                    clearVRAMgeneral(914, 94, 46, 142);
                    LoadTexture(_binary_tim_camera_panel_1_tim_start, &panel);
                break;
                case 2:
                    clearVRAMgeneral(914, 94, 46, 142);
                    LoadTexture(_binary_tim_camera_panel_2_tim_start, &panel);
                break;
                case 3:
                    clearVRAMgeneral(914, 94, 46, 142);
                    LoadTexture(_binary_tim_camera_panel_3_tim_start, &panel);
                break;
                case 4:
                    camerastate = false;
                    clearVRAMgeneral(914, 94, 46, 142);
                    LoadTexture(_binary_tim_camera_panel_4_tim_start, &panel);
                break;
                case 5:
                    clearVRAMgeneral(914, 94, 46, 142);
                    LoadTexture(_binary_tim_camera_panel_5_tim_start, &panel);
                    SpuSetKey(SPU_ON, SPU_21CH);
                    MovVectormaintenance_loadco.vx = 45; //Here so that the icon doesn't teleport
                break;
            }
        }
        if (spritesheetcamera != 0 && spritecamera != 1) {spritesheetcamera--;} else {spritesheetcamera = 4; spritecamera--;}
    }

    if (camerastatic > 30) {camerastatic--;}
    if (camerastatic < 30) {camerastatic++;}

    if (camerastatic == 30 && camera) {
        Ran(21);
        if (RAN == 1) {
            Ran(21);
            camerastatic += RAN;
        } 
        if (RAN == 2) {
            Ran(21);
            camerastatic -= RAN;
        }
    }

    if (springtrapblockcam > 0) {
        camerastatic = 100;
        springtrapblockcam--;
    }

    if (currentlysealing) {timertolock--;}

    if (timertolock % 60 == 0 && currentlysealing) { //Every seconds
        SpuSetKey(SPU_ON, SPU_18CH);
        if (timertolock == 0) {ventlocked = curcam[0] + curcam[1] + 9; currentlysealing = false; timertolock = 180; SpuSetKey(SPU_ON, SPU_00CH);} //exemple for cam 12 : 1 + 2 + 9 = 12.
    }
}

void timeFunc(void) {
    if (onesecondvar == 0) {
        onesecondvar = 60;
    } else {onesecondvar--;}

    if (!camera && !maintenancepanel) {
        inactiveframes++;
    } else {inactiveframes = 0;} //Used for SPOUINGTA's agressiveness

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
    (fanframes > 2 && FrameCounter % 3 == 1) ? fanframes = 0 : fanframes++; // Finally be usin ternary operator like a grown dev !!!§§ (too lazy to change all + Forgot about doing this + Not a lot of cases to do that)

    if (!camerastate && MovVectorofficemiddle.vx < 49 && AM != 6) {
        switch(fanframes) {
          case 0:
              LoadTexture(_binary_tim_office_fan_FAN0_tim_start, &fan);
          break;        
          case 1:
              LoadTexture(_binary_tim_office_fan_FAN1_tim_start, &fan);
          break;        
          case 2:
              LoadTexture(_binary_tim_office_fan_FAN2_tim_start, &fan);
          break;
        }
    } //"!camerastate" and not "!camera" because it stops the fan too early

    if (FrameCounter % 900 == 1) {
        Ran(5); //Actually 4

        if (RAN < springtrapAI) {isagressive = true;} else {isagressive = false;} //If ran is inferior than his AI, he'll get  ̷F̷r̷e̷a̷k̷y̷ Agressive.

    }//Every 15 seconds, The Singtrap will try to go aggresive

    if (ventilationfailure && officefadingout != 1) {frameventilbroke++;} else {frameventilbroke = 0;}

    if (frameventilbroke == 780) {officefadingout = 0;}
}
