//This function take in charge the cameras.
//Why ? It's Simple, because the game.c was LONG ASF. Longer than my life savings I'd say. (10 rubies) 
//(and also because it was harder to look for a specific thing and having to scroll like 100000 times to pass by the thing we want. Here, you know you are at the cam func.)
// *copy-paste old comment and change three-four words* "Yeah, That'll work"
// *change euros to rubies* "Yeah, I'm original"
// *copy-paste old comment about changing euros to rubies* "I've done what's called a programmer move"
// I had to change everything to accomodate to the pingtrap var :( He Shouldn't have killed those kids

void cameraloc(void) {

    if (currentlysealing) {return;}

    //Gosh, This is gonna be long
    if (curcam[0] == 0 && curcam[1] == 1) {
        MovVectorpolycamgreyogreen.vx = 34;
        MovVectorpolycamgreyogreen.vy = 81;  

        if (limitercameraR == 0 && pad & PADLright || limitercameraR == 0 && pad >> 16 & PADLright && twoplayermode == 1) { 
            curcam[1]++;
            SpuSetKey(SPU_ON, SPU_03CH);
            limitercameraR = 1;
            camerastatic = 100;

            ballonboyqueued = false; ballonboyseen = 51;
        }
        if (limitercameraU == 0 && pad & PADLup || limitercameraU == 0 && pad >> 16 & PADLup && twoplayermode == 1) { 
            curcam[1] = 6;
            SpuSetKey(SPU_ON, SPU_03CH);
            limitercameraU = 1;
            camerastatic = 100;

            ballonboyqueued = false; ballonboyseen = 51;
        }
        if (ballonboyqueued) {if (ballonboyseen > 0) {ballonboyseen--;}}
    }

    if (curcam[0] == 0 && curcam[1] == 2) {      
        MovVectorpolycamgreyogreen.vx = 95;
        MovVectorpolycamgreyogreen.vy = 71;

        if (limitercameraU == 0 && pad & PADLup || limitercameraU == 0 && pad >> 16 & PADLup && twoplayermode == 1) { 
            curcam[1] = 5;
            SpuSetKey(SPU_ON, SPU_03CH);
            limitercameraU = 1;
            camerastatic = 100;
        }
        if (limitercameraL == 0 && pad & PADLleft || limitercameraL == 0 && pad >> 16 & PADLleft && twoplayermode == 1) { 
            curcam[1]--;
            SpuSetKey(SPU_ON, SPU_03CH);
            limitercameraL = 1;
            camerastatic = 100;
        }
        if (limitercameraR == 0 && pad & PADLright || limitercameraR == 0 && pad >> 16 & PADLright && twoplayermode == 1) {  
            curcam[1]++;
            SpuSetKey(SPU_ON, SPU_03CH);
            limitercameraR = 1;
            camerastatic = 100;
        }
    }

    if (curcam[0] == 0 && curcam[1] == 3) {   
        MovVectorpolycamgreyogreen.vx = 118;
        MovVectorpolycamgreyogreen.vy = 56;

        if (limitercameraL == 0 && pad & PADLleft || limitercameraL == 0 && pad >> 16 & PADLleft && twoplayermode == 1) { 
            curcam[1]--;
            SpuSetKey(SPU_ON, SPU_03CH);
            limitercameraL = 1;
            camerastatic = 100;
        }
        if (limitercameraD == 0 && pad & PADLdown || limitercameraD == 0 && pad >> 16 & PADLdown && twoplayermode == 1) { 
            curcam[1]--;
            SpuSetKey(SPU_ON, SPU_03CH);
            limitercameraD = 1;
            camerastatic = 100;
        }
        if (limitercameraU == 0 && pad & PADLup || limitercameraU == 0 && pad >> 16 & PADLup && twoplayermode == 1) { 
            curcam[1]++;
            SpuSetKey(SPU_ON, SPU_03CH);
            limitercameraU = 1;
            camerastatic = 100;
        }
    }

    if (curcam[0] == 0 && curcam[1] == 4) {     
        MovVectorpolycamgreyogreen.vx = 118;
        MovVectorpolycamgreyogreen.vy = 41;  

        if (limitercameraU == 0 && pad & PADLup || limitercameraU == 0 && pad >> 16 & PADLup && twoplayermode == 1) { 
            curcam[0] = 1;
            curcam[1] = 0;
            SpuSetKey(SPU_ON, SPU_03CH);
            limitercameraU = 1;
            camerastatic = 100;

            manglequeued = false; mangleseen = 51;
        }
        if (limitercameraL == 0 && pad & PADLleft || limitercameraL == 0 && pad >> 16 & PADLleft && twoplayermode == 1) { 
            curcam[1]++;
            SpuSetKey(SPU_ON, SPU_03CH);
            limitercameraL = 1;
            camerastatic = 100;

            manglequeued = false; mangleseen = 51;
        }
        if (limitercameraD == 0 && pad & PADLdown || limitercameraD == 0 && pad >> 16 & PADLdown && twoplayermode == 1) { 
            curcam[1]--;
            SpuSetKey(SPU_ON, SPU_03CH);
            limitercameraD = 1;
            camerastatic = 100;
            
            manglequeued = false; mangleseen = 51;
        }
        if (manglequeued) {if (mangleseen > 0) { mangleseen--;}}
    }

    if (curcam[0] == 0 && curcam[1] == 5) {   
        MovVectorpolycamgreyogreen.vx = 72;
        MovVectorpolycamgreyogreen.vy = 41; 

        if (limitercameraL == 0 && pad & PADLleft || limitercameraL == 0 && pad >> 16 & PADLleft && twoplayermode == 1) { 
            curcam[1]++;
            SpuSetKey(SPU_ON, SPU_03CH);
            limitercameraL = 1;
            camerastatic = 100;
        }
        if (limitercameraR == 0 && pad & PADLright || limitercameraR == 0 && pad >> 16 & PADLright && twoplayermode == 1) { 
            curcam[1]--;
            SpuSetKey(SPU_ON, SPU_03CH);
            limitercameraR = 1;
            camerastatic = 100;
        }
        if (limitercameraU == 0 && pad & PADLup || limitercameraU == 0 && pad >> 16 & PADLup && twoplayermode == 1) { 
            curcam[0] = 0;
            curcam[1] = 8;
            SpuSetKey(SPU_ON, SPU_03CH);
            limitercameraU = 1;
            camerastatic = 100;
        }
        if (limitercameraD == 0 && pad & PADLdown || limitercameraD == 0 && pad >> 16 & PADLdown && twoplayermode == 1) { 
            curcam[0] = 0;
            curcam[1] = 2;
            SpuSetKey(SPU_ON, SPU_03CH);
            limitercameraD = 1;
            camerastatic = 100;
        }
    }

    if (curcam[0] == 0 && curcam[1] == 6) {    
        MovVectorpolycamgreyogreen.vx = 31;
        MovVectorpolycamgreyogreen.vy = 44; 

        if (limitercameraR == 0 && pad & PADLright || limitercameraR == 0 && pad >> 16 & PADLright && twoplayermode == 1) { 
            curcam[1]--;
            SpuSetKey(SPU_ON, SPU_03CH);
            limitercameraR = 1;
            camerastatic = 100;
        }
        if (limitercameraU == 0 && pad & PADLup || limitercameraU == 0 && pad >> 16 & PADLup && twoplayermode == 1) { 
            curcam[1]++;
            SpuSetKey(SPU_ON, SPU_03CH);
            limitercameraU = 1;
            camerastatic = 100;
        }
        if (limitercameraD == 0 && pad & PADLdown || limitercameraD == 0 && pad >> 16 & PADLdown && twoplayermode == 1) { 
            curcam[0] = 0;
            curcam[1] = 1;
            SpuSetKey(SPU_ON, SPU_03CH);
            limitercameraD = 1;
            camerastatic = 100;
        }
    }

    if (curcam[0] == 0 && curcam[1] == 7) {       
        MovVectorpolycamgreyogreen.vx = 31;
        MovVectorpolycamgreyogreen.vy = 25; 

        if (limitercameraD == 0 && pad & PADLdown || limitercameraD == 0 && pad >> 16 & PADLdown && twoplayermode == 1) { 
            curcam[1]--;
            SpuSetKey(SPU_ON, SPU_03CH);
            limitercameraD = 1;
            camerastatic = 100;

            ballonboyqueued = false; ballonboyseen = 51;
            chicaqueued = false; chicaseen = 54;
        }
        if (limitercameraR == 0 && pad & PADLright || limitercameraR == 0 && pad >> 16 & PADLright && twoplayermode == 1) { 
            curcam[1]++;
            SpuSetKey(SPU_ON, SPU_03CH);
            limitercameraR = 1;
            camerastatic = 100;

            ballonboyqueued = false; ballonboyseen = 51;
            chicaqueued = false; chicaseen = 54;
        }
        if (ballonboyqueued) {if (ballonboyseen > 0) {ballonboyseen--;}}
        if (chicaqueued) {if (chicaseen > 0 ) {chicaseen--;}}
    }

    if (curcam[0] == 0 && curcam[1] == 8) {    
        MovVectorpolycamgreyogreen.vx = 61;
        MovVectorpolycamgreyogreen.vy = 17; 

        if (limitercameraL == 0 && pad & PADLleft || limitercameraL == 0 && pad >> 16 & PADLleft && twoplayermode == 1) { 
            curcam[1]--;
            SpuSetKey(SPU_ON, SPU_03CH);
            limitercameraL = 1;
            camerastatic = 100;
            puppetqueued = false; puppetseen = 51;
        }
        if (limitercameraR == 0 && pad & PADLright || limitercameraR == 0 && pad >> 16 & PADLright && twoplayermode == 1) { 
            curcam[1]++;
            SpuSetKey(SPU_ON, SPU_03CH);
            limitercameraR = 1;
            camerastatic = 100;
            puppetqueued = false; puppetseen = 51;
        }
        if (limitercameraD == 0 && pad & PADLdown || limitercameraD == 0 && pad >> 16 & PADLdown && twoplayermode == 1) { 
            curcam[0] = 0;
            curcam[1] = 5;
            SpuSetKey(SPU_ON, SPU_03CH);
            limitercameraD = 1;
            camerastatic = 100;
            puppetqueued = false; puppetseen = 51;
        }
        if (puppetqueued) {puppetseen--;}
    }

    if (curcam[0] == 0 && curcam[1] == 9) { 
        MovVectorpolycamgreyogreen.vx = 81;
        MovVectorpolycamgreyogreen.vy = 3; 

        if (limitercameraR == 0 && pad & PADLright || limitercameraR == 0 && pad >> 16 & PADLright && twoplayermode == 1) { 
            curcam[0] = 1;
            curcam[1] = 0;
            SpuSetKey(SPU_ON, SPU_03CH);
            limitercameraR = 1;
            camerastatic = 100;

            ballonboyqueued = false; ballonboyseen = 51;
        }
        if (limitercameraD == 0 && pad & PADLdown || limitercameraD == 0 && pad >> 16 & PADLdown && twoplayermode == 1) { 
            curcam[0] = 0;
            curcam[1] = 5;
            SpuSetKey(SPU_ON, SPU_03CH);
            limitercameraD = 1;
            camerastatic = 100;

            ballonboyqueued = false; ballonboyseen = 51;
        }
        if (limitercameraL == 0 && pad & PADLleft || limitercameraL == 0 && pad >> 16 & PADLleft && twoplayermode == 1) { 
            curcam[1]--;
            SpuSetKey(SPU_ON, SPU_03CH);
            limitercameraL = 1;
            camerastatic = 100;

            ballonboyqueued = false; ballonboyseen = 51;
        }
        if (ballonboyqueued) {ballonboyseen--;}
    }

    if (curcam[0] == 1 && curcam[1] == 0) {    
        MovVectorpolycamgreyogreen.vx = 112;
        MovVectorpolycamgreyogreen.vy = 17; 

        if (limitercameraD == 0 && pad & PADLdown || limitercameraD == 0 && pad >> 16 & PADLdown && twoplayermode == 1) { 
            curcam[0] = 0;
            curcam[1] = 4;
            SpuSetKey(SPU_ON, SPU_03CH);
            limitercameraD = 1;
            camerastatic = 100;

            ballonboyqueued = false; ballonboyseen = 51;
        }
        if (limitercameraL == 0 && pad & PADLleft || limitercameraL == 0 && pad >> 16 & PADLleft && twoplayermode == 1) { 
            curcam[0] = 0;
            curcam[1] = 9;
            SpuSetKey(SPU_ON, SPU_03CH);
            limitercameraL = 1;
            camerastatic = 100;

            ballonboyqueued = false; ballonboyseen = 51;
        }
        if (ballonboyqueued) {ballonboyseen--;}
    }

    if (curcam[0] == 1 && curcam[1] == 1) {    
        MovVectorpolycamgreyogreen.vx = 33;
        MovVectorpolycamgreyogreen.vy = 3;  

        if (limitercameraD == 0 && pad & PADLdown || limitercameraD == 0 && pad >> 16 & PADLdown && twoplayermode == 1) { 
            curcam[1]++;
            SpuSetKey(SPU_ON, SPU_03CH);
            limitercameraD = 1;
            camerastatic = 100;
        }
    }

    if (curcam[0] == 1 && curcam[1] == 2) {    
        MovVectorpolycamgreyogreen.vx = 51;
        MovVectorpolycamgreyogreen.vy = 38;  

        if (limitercameraR == 0 && pad & PADLright || limitercameraR == 0 && pad >> 16 & PADLright && twoplayermode == 1) { 
            curcam[1] = 4;
            SpuSetKey(SPU_ON, SPU_03CH);
            limitercameraR = 1;
            camerastatic = 100;
        }
        if (limitercameraU == 0 && pad & PADLup || limitercameraU == 0 && pad >> 16 & PADLup && twoplayermode == 1) { 
            curcam[1]--;
            SpuSetKey(SPU_ON, SPU_03CH);
            limitercameraU = 1;
            camerastatic = 100;
        }
        if (limitercameraD == 0 && pad & PADLdown || limitercameraD == 0 && pad >> 16 & PADLdown && twoplayermode == 1) { 
            curcam[1]++;
            SpuSetKey(SPU_ON, SPU_03CH);
            limitercameraD = 1;
            camerastatic = 100;
        }
    }

    if (curcam[0] == 1 && curcam[1] == 3) {    
        MovVectorpolycamgreyogreen.vx = 79;
        MovVectorpolycamgreyogreen.vy = 55;  

        if (limitercameraR == 0 && pad & PADLright || limitercameraR == 0 && pad >> 16 & PADLright && twoplayermode == 1) { 
            curcam[1]++;
            SpuSetKey(SPU_ON, SPU_03CH);
            limitercameraR = 1;
            camerastatic = 100;
        }
        if (limitercameraU == 0 && pad & PADLup || limitercameraU == 0 && pad >> 16 & PADLup && twoplayermode == 1) { 
            curcam[1]--;
            SpuSetKey(SPU_ON, SPU_03CH);
            limitercameraU = 1;
            camerastatic = 100;
        }
        if (limitercameraL == 0 && pad & PADLleft || limitercameraL == 0 && pad >> 16 & PADLleft && twoplayermode == 1) { 
            curcam[1]--;
            SpuSetKey(SPU_ON, SPU_03CH);
            limitercameraU = 1;
            camerastatic = 100;
        }
        if (limitercameraD == 0 && pad & PADLdown || limitercameraD == 0 && pad >> 16 & PADLdown && twoplayermode == 1) { 
            curcam[1] = 5;
            SpuSetKey(SPU_ON, SPU_03CH);
            limitercameraD = 1;
            camerastatic = 100;
        }
    }
    if (curcam[0] == 1 && curcam[1] == 4) {    
        MovVectorpolycamgreyogreen.vx = 106;
        MovVectorpolycamgreyogreen.vy = 31;  

        if (limitercameraU == 0 && pad & PADLup || limitercameraU == 0 && pad >> 16 & PADLup && twoplayermode == 1) { 
            curcam[1] = 1;
            SpuSetKey(SPU_ON, SPU_03CH);
            limitercameraU = 1;
            camerastatic = 100;
        }
        if (limitercameraD == 0 && pad & PADLdown || limitercameraD == 0 && pad >> 16 & PADLdown && twoplayermode == 1) { 
            curcam[1]++;
            SpuSetKey(SPU_ON, SPU_03CH);
            limitercameraD = 1;
            camerastatic = 100;
        }
        if (limitercameraL == 0 && pad & PADLleft || limitercameraL == 0 && pad >> 16 & PADLleft && twoplayermode == 1) { 
            curcam[1]--;
            SpuSetKey(SPU_ON, SPU_03CH);
            limitercameraL = 1;
            camerastatic = 100;
        }
    }
    if (curcam[0] == 1 && curcam[1] == 5) {    
        MovVectorpolycamgreyogreen.vx = 114;
        MovVectorpolycamgreyogreen.vy = 74;  

        if (limitercameraU == 0 && pad & PADLup || limitercameraU == 0 && pad >> 16 & PADLup && twoplayermode == 1) { 
            curcam[1]--;
            SpuSetKey(SPU_ON, SPU_03CH);
            limitercameraU = 1;
            camerastatic = 100;
        }
        if (limitercameraL == 0 && pad & PADLleft || limitercameraL == 0 && pad >> 16 & PADLleft && twoplayermode == 1) { 
            curcam[1] = 3;
            SpuSetKey(SPU_ON, SPU_03CH);
            limitercameraL = 1;
            camerastatic = 100;
        }
    }

    if(pad & PADR1 || pad >> 16 & PADR1 && twoplayermode == 1) { //R1
        if (camlimiter == 1) {return;}
        camera = false;
        SpuSetKey(SPU_OFF, SPU_01CH);
        SpuSetKey(SPU_ON, SPU_07CH);
    }
    if(!(pad & PADR1 || pad >> 16 & PADR1 && twoplayermode == 1)) {camlimiter = 0;}

    if (!(pad & PADLdown || pad >> 16 & PADLdown) && limitercameraD == 1) {
        limitercameraD = 0;
    }
    if (!(pad & PADLup || pad >> 16 & PADLup) && limitercameraU == 1) {
        limitercameraU = 0;
        camerastatic = 100;
    }
    if (!(pad & PADLright || pad >> 16 & PADLright) && limitercameraR == 1) {
        limitercameraR = 0;
    }
    if (!(pad & PADLleft || pad >> 16 & PADLleft) && limitercameraL == 1) {
        limitercameraL = 0;
    }

}