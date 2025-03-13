void menuselectionfunc(void) { //LONG asf lmaoo || Still not as long as before
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

    switch(menuselection) {
        case 1:
            MovVectormenuselectionbutton.vy = 3;
        break;
        case 2:
            MovVectormenuselectionbutton.vy = 17;
        break;
        case 3:
            MovVectormenuselectionbutton.vy = 30;
        break;
        case 4:
            MovVectormenuselectionbutton.vy = 42;
        break;
    }

    switch(currentmenu[0]) {
        case 0:
            if (isingame) {
                if (menuselection == 1) {//Continue night
                    if (pad & PADstart) {
                        menu = 3;
                        returnedingame = 1;
                    } 
                }

                if (menuselection == 2) {//Abandon night
                    if (pad & PADstart && limiterstart == 0) {
                        resetgame(0);
                        fadeoffice = 0; //So that we can see the sprites
                        LoadTexture(_binary_tim_titlemenu_lines_1_tim_start, &lines);
                        linesactive = true; //One time to refresh the sprites
                        limiterstart++;
                        menuselection = 3;
                        if (activatedmenudebug == 0) {menuselectionmax = 3;} else {menuselectionmax = 4;}
                        
                    } 
                }
            } else {
                if (menuselection == 1) {//"Starting" night
                    if (pad & PADstart) {
                        night = 1;
                        menufadingout = true;
                    } 
                }

                if (menuselection == 2) { //Continue nights
                    if (pad & PADstart) {
                        loadingframe = 360;
                        menu = 2;
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
                            currentmenu[0] = 1;
                            currentmenu[1] = 0;
                            menuselection = 1;
                            limiterstart++;
                            if (activatedmenudebug == 0) {
                                menuselectionmax = 4;
                            } else {
                                menuselectionmax = 5;
                            }
                        }
                    }
                }/*
                if (menuselection == 4) { //CUSTOM NIGHT MENU
                    if (pad & PADstart) {
                        if (limiterstart == 0) {
                            currentmenu[0] = 2;
                            menuselection = 1;
                            menuselectionmax = 6;
                            limiterstart++;
                        }
                    }
                }*/

                if (activatedmenudebug == 1) {
                    if (menuselection == 4) {
                        if (pad & PADLright) {
                            if (limiterpadright == 0) {
                                printnumber++;
                                if (printnumber > 2) {printnumber = 1;}
                                limiterpadright = 1;
                            }
                        }
                        if (pad & PADLleft) {
                            if (limiterpadleft == 0) {
                                printnumber--;
                                if (printnumber < 1) {printnumber = 2;}
                                limiterpadleft = 1;
                            }
                        }
                    }
                }
            }
        break;
        case 1:
            switch(currentmenu[1]) {
                case 0:
                    if (menuselection == 1) { //Unlocks menu
                        if (pad & PADstart) {
                            if (limiterstart == 0) {
                                currentmenu[1] = 1;
                                menuselection = 1;
                                menuselectionmax = 4;
                                limiterstart = 1;
                            }
                        }
                    }
                    if (menuselection == 2) { //Informations on the game
                        if (pad & PADstart) {
                            if (limiterstart == 0) {
                                currentmenu[1] = 2;
                                menuselection = 1;
                                menuselectionmax = 1;
                                limiterstart = 1;
                            }
                        }
                    }
                    if (menuselection == 3) {//Two players mode
                        if (pad & PADRdown) {
                            if (limiterbuttondown == 0) {
                                twoplayermode++;
                                if (twoplayermode > 1) {twoplayermode = 0;}
                                
                                if (twoplayermode == 0) {
                                    sprintf(twoplayermodestr, "OFF");
                                } else {
                                    sprintf(twoplayermodestr, "ON");
                                }
                                limiterbuttondown = 1;
                            }
                        }
                    }
                    if (menuselection == 4) { //Return
                        if (pad & PADstart) {
                            if (limiterstart == 0)  {
                                currentmenu[0] = 0;
                                menuselection = 3;
                                limiterstart++;
                                if (activatedmenudebug == 0) {menuselectionmax = 3;}
                                else {menuselectionmax = 4;}
                            }
                        }
                    }/*
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
                    }*/
                break;
                case 1:
                    if (menuselection == 1) {//No errors cheats
                        if (pad & PADRdown) {
                            if (limiterbuttondown == 0) {
                                noerrors = !noerrors;

                                if (!noerrors) {sprintf(noerrorsstr, "OFF");} else {sprintf(noerrorsstr, "ON");}
                                
                                limiterbuttondown = 1;
                            }
                        }
                    }
                    if (menuselection == 2) {
                        if (pad & PADRdown) {
                            if (limiterbuttondown == 0) {
                                fastnights = !fastnights;
                                
                                if (!fastnights) {sprintf(fastnightsstr, "OFF");} else {sprintf(fastnightsstr, "ON");}
                                
                                limiterbuttondown = 1;
                            }
                        }
                    }
                    if (menuselection == 3) {
                        if (pad & PADRdown) {
                            if (limiterbuttondown == 0) {
                                aggressive = !aggressive;

                                if (!aggressive) {sprintf(aggressivestr, "OFF");} else {sprintf(aggressivestr, "ON");}

                                limiterbuttondown = 1;
                            }
                        }
                    }
                    if (menuselection == 4) { //return to main menu
                        if (pad & PADstart) {
                            if (limiterstart == 0) {
                                currentmenu[1] = 0;
                                menuselection = 1;
                                menuselectionmax = 4;
                                limiterstart = 1;
                            }
                        }
                    }
                break;
                case 2:
                    if (menuselection == 1) { //Infos on the game
                        if (pad & PADstart) {
                            if (limiterstart == 0) {
                                currentmenu[1] = 0;
                                menuselection = 1;
                                menuselectionmax = 4;
                                limiterstart = 1;
                            }
                        }
                    }
                break;
            }
        break;
    }
}
void menuPrint(void) {
    FntPrint("\n\n\n\n\n\n\n\n\n\n\n\n");  // print time
    switch(currentmenu[0]) {
        case 0:
            if (isingame) {
                if (menuselection == 1) {FntPrint(">> Continue Night %d\n\n", night);}
                else {FntPrint("   Continue Night %d\n\n", night);}

                if (menuselection == 2) {FntPrint(">> Abandon The Night \n\n");}
                else {FntPrint("   Abandon The Night \n\n");}
            } else {
                if (activatedmenudebug == 1) {
                    if (menuselection == 4) {
                        switch(printnumber) {
                            case 1:
                                FntPrint(">> Debugprint %d, Vanilla\n\n", printnumber);
                            break;
                            case 2:
                                FntPrint(">> Debugprint %d, debug\n\n", printnumber);
                            break;
                        }
                    }
                    else {
                        FntPrint("   Debugprint \n\n");
                    }
                }
            }

        break;
        case 1:
            switch(currentmenu[1]) {
                case 0:
                    if (menuselection == 1) {FntPrint(">> Cheats\n\n");}
                    else {FntPrint("   Cheats\n\n");}

                    if (menuselection == 2) {FntPrint(">> Info screen\n\n");}
                    else {FntPrint("   Info screen\n\n");}

                    if (menuselection == 3) {FntPrint(">> Two Player Mode : %s\n\n", twoplayermodestr);}
                    else {FntPrint("   Two Player Mode : %s\n\n", twoplayermodestr);}

                    if (menuselection == 4) {FntPrint(">> Return to main menu\n\n");}
                    else {FntPrint("   Return to main menu\n\n");}

                    if (activatedmenudebug == 1) {
                        if (menuselection == 5) {FntPrint(">> Toggle weird night\n\n");}
                        else {FntPrint("   Toggle weird night\n\n");}

                        if (menuselection == 6) {FntPrint(">> Toggle debugging\n\n");}
                        else {FntPrint("   Toggle debugging\n\n");}
                    }
                break;
                case 1:
                    if (menuselection == 1) {FntPrint(">> No errors : %s\n\n", noerrorsstr);}
                    else {FntPrint("   No errors : %s\n\n", noerrorsstr);}

                    if (menuselection == 2) {FntPrint(">> Fast Nights : %s\n\n", fastnightsstr);}
                    else {FntPrint("   Fast Nights : %s\n\n", fastnightsstr);}

                    if (menuselection == 3) {FntPrint(">> Aggressive : %s (night 6)\n\n", aggressivestr);}
                    else {FntPrint("   Aggressive : %s (night 6)\n\n", aggressivestr);}

                    if (menuselection == 4) {FntPrint(">> Back \n\n");}
                    else {FntPrint("   Back \n\n");}

                break;
                case 2:
                    FntPrint("   Five Night at Freddy's 3 has been \n   released by Scott Cawton on 2015,\n  and has been ported on PS1 by Soeiz.\n\n        Again, Thank you, Scott, \n      For releasing this beautiful\n              Masterpiece.\n\n");

                    FntPrint(">> Back                 EARLY V.1.0\n"); //Don't even need to do condition, there's only one
                break;
            }
        break;
    }
}