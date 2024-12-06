

const uint8_t notes[] = {
  0, //00 off
  104, //01 DS5
  110, //02 E5
  123, //03 FS5
  165, //04 B5
  208, //05 DS6
  220, //06 E6
  155, //07 AS5
  185, //08 CS6
  62, //09 FS4
  70, //10 GS4
  49, //11 D4
  52, //12 DS4
  16, //13 FS2
  46, //14 CS4
  41, //15 B3
  31, //16 FS3
  35, //17 GS3
  55, //18 E4
  28, //19 E3
  26, //20 DS3
  39 //21 AS3
};



const uint8_t melody[] = {
  notes[1], notes[2], notes[3], notes[0], notes[04], notes[02], notes[01], notes[02], notes[03], notes[4], notes[5], notes[06], notes[05], notes[07], notes[04], notes[0]/
  
  notes[03], notes[0], notes[01], notes[02], notes[03], notes[0], notes[04], notes[8], notes[07], notes[04], notes[8], notes[6], notes[05], notes[06], notes[8], notes[9], 
  notes[10], notes[11], notes[12], notes[13], notes[14], notes[11], notes[14], notes[15], notes[15], notes[14], notes[11], notes[11], notes[14], notes[15], notes[14], notes[12], 
  notes[9], notes[10], notes[12], notes[9], notes[14], notes[12], notes[15], notes[14], notes[15], notes[12], notes[9], notes[10], notes[12], notes[9], notes[14], notes[12], 
  notes[15], notes[11], notes[12], notes[11], notes[14], notes[15], notes[14], notes[11], notes[15], notes[14], notes[12], notes[9], notes[14], notes[11], notes[14], notes[15], 
  notes[14], notes[15], notes[14], notes[9], notes[10], notes[11], notes[12], notes[13], notes[14], notes[11], notes[14], notes[15], notes[15], notes[14], notes[11], notes[11],
  notes[14], notes[15], notes[14], notes[12], notes[9], notes[10], notes[12], notes[9], notes[14], notes[12], notes[15], notes[14], notes[15], notes[12], notes[9], notes[10], 
  notes[12], notes[9], notes[14], notes[12], notes[15], notes[11], notes[12], notes[11], notes[14], notes[15], notes[14], notes[11], notes[15], notes[14], notes[12], notes[9], 
  notes[14], notes[11], notes[14], notes[15], notes[14], notes[15], notes[15], notes[15], notes[16], notes[17], notes[15], notes[16], notes[17], notes[15], notes[14], notes[12], 
  notes[15], notes[18], notes[12], notes[18], notes[9], notes[15], notes[15], notes[16], notes[17], notes[15], notes[16], notes[18], notes[12], notes[14], notes[15], notes[19], 
    
  notes[20], notes[19], notes[16], notes[15], notes[16], notes[17], notes[15], notes[16], notes[17], notes[15], notes[15], notes[14], notes[12], notes[15], notes[16], notes[17], 
  
  notes[16], notes[15], notes[15], notes[21], notes[15], notes[16], notes[17], notes[15], notes[18], notes[12], notes[18], notes[9], notes[15], notes[21], notes[15], notes[16], 
  
  notes[17], notes[15], notes[16], notes[17], notes[15], notes[14], //notes[12], notes[15], notes[18], notes[12], notes[18], notes[9], notes[15], notes[15], notes[16], notes[17], 
  
  /*
  notes[15], notes[16], notes[18], notes[12], notes[14], notes[15], notes[19], notes[20], notes[19], notes[16], notes[15], notes[16], notes[17], notes[15], notes[16], notes[17], 
  notes[15], notes[15], notes[14], notes[12], notes[15], notes[16], notes[17], notes[16], notes[15], notes[15], notes[21], notes[15], notes[16], notes[17], notes[15], notes[18], 
  notes[12], notes[18], notes[9], notes[15], notes[14], notes[9], notes[10], notes[11], notes[12], notes[13], notes[14], notes[11], notes[14], notes[15], notes[15], notes[14],
  notes[11], notes[11], notes[14], notes[15], notes[14], notes[12], notes[9], notes[10], notes[12], notes[9], notes[14], notes[12], notes[15], notes[14], notes[15], notes[12], 
  notes[9], notes[10], notes[12], notes[9], notes[14], notes[12], notes[15], notes[11], notes[12], notes[11], notes[14], notes[15], notes[14], notes[11], notes[15], notes[14], 
  notes[12], notes[9], notes[14], notes[11], notes[14], notes[15], notes[14], notes[15], notes[14], notes[9], notes[10], notes[11], notes[12], notes[13], notes[14], notes[11], 
  
  
  notes[14], notes[15], notes[15], notes[14], notes[11], notes[11], notes[14], notes[15], notes[14], notes[12], notes[9], notes[10], notes[12], notes[9], notes[14], notes[12], 
  
  
  notes[15], notes[14], notes[15], notes[12], notes[9], notes[10], notes[12], notes[9], notes[14], notes[12], notes[15], notes[11], notes[12], notes[11], notes[14], notes[15], 
  notes[14], notes[11], notes[15], notes[14], notes[12], notes[9], notes[14], notes[11], notes[14], notes[15], notes[14], notes[15], notes[15], notes[15], notes[16], notes[17], 
  */

  //////////////////
  //notes[15], notes[16], notes[17], notes[15], notes[14], notes[12], notes[15], notes[18], notes[12], notes[18], notes[9], notes[15], notes[15], notes[16], notes[17], notes[15], 
  //notes[16], notes[18], notes[12], notes[14], notes[15], notes[19], notes[20], notes[19], notes[16], notes[15], notes[16], notes[17], notes[15], notes[16], notes[17], notes[15], 
  //notes[15], notes[14], notes[12], notes[15], notes[16], notes[17], notes[16], notes[15], notes[15], notes[21], notes[15], notes[16], notes[17], notes[15], notes[18], notes[12], 
  //notes[18], notes[9], notes[15], notes[21], notes[15], notes[16], notes[17], notes[15], notes[16], notes[17], notes[15], notes[14], notes[12], notes[15], notes[18], notes[12], 
  //notes[18], notes[9], notes[15], notes[15], notes[16], notes[17], notes[15], notes[16], notes[18], notes[12], notes[14], notes[15], notes[19], notes[20], notes[19], notes[16], 
  //notes[15], notes[16], notes[17], notes[15], notes[16], notes[17], notes[15], notes[15], notes[14], notes[12], notes[15], notes[16], notes[17], notes[16], notes[15], notes[15],
  //notes[21], notes[15], notes[16], notes[17], notes[15], notes[18], notes[12], notes[18], notes[9], notes[15], notes[14]
};

// note durations: 1 = 16th note, 0 = eighth note, etc
const bool noteDurations[] = {
  1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
  1,1,1,1,1,1,0,1,1,1,1,1,1,1,1,
  0,0,1,1,1,1,1,1,0,0,0,
  0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
  0,0,1,1,1,1,1,1,1,1,1,1,1,1,
  0,1,1,1,1,1,1,1,1,0,0,0,
  0,0,1,1,1,1,1,1,0,0,0,
  0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
  0,0,1,1,1,1,1,1,1,1,1,1,1,1,
  0,1,1,1,1,1,1,1,1,0,0,0,
  0,1,1,0,1,1,1,1,1,1,1,1,1,1,
  0,0,1,1,1,1,1,1,1,1,1,1,1,1,
  0,1,1,0,1,1,1,1,1,1,1,1,1,1,
  0,1,1,1,1,1,1,1,1,1,1,0,0,
  0,1,1,0,1,1,1,1,1,1,1,1,1,1,
  0,0,1,1,1,1,1,1,1,1,1,1,1,1,
  0,1,1,0,1,1,1,1,1,1,1,1,1,1,
  0,1,1,1,1,1,1,1,1,1,1,0,0,
  0,0,1,1,1,1,1,1,0,0,0,
  0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
  0,0,1,1,1,1,1,1,1,1,1,1,1,1,
  0,1,1,1,1,1,1,1,1,0,0,0,
  0,0,1,1,1,1,1,1,0,0,0,
  0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
  0,0,1,1,1,1,1,1,1,1,1,1,1,1,
  0,1,1,1,1,1,1,1,1,0,0,0,
  0,1,1,0,1,1,1,1,1,1,1,1,1,1,
  0,0,1,1,1,1,1,1,1,1,1,1,1,1,
  0,1,1,0,1,1,1,1,1,1,1,1,1,1,
  0,1,1,1,1,1,1,1,1,1,1,0,0,
  0,1,1,0,1,1,1,1,1,1,1,1,1,1,
  0,0,1,1,1,1,1,1,1,1,1,1,1,1,
  0,1,1,0,1,1,1,1,1,1,1,1,1,1,
  0,1,1,1,1,1,1,1,1,1,1,0,0,
};
