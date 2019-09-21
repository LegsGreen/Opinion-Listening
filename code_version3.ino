
/*
 * touch play file
 * 
 * not done
 */
 #include <Audio.h>
#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <SerialFlash.h>

AudioPlaySdWav           playSdWav1;
AudioPlaySdWav           playSdWav2;
AudioPlaySdWav           playSdWav3;
AudioPlaySdWav           playSdWav4;
AudioPlaySdWav           playSdWav5;
AudioPlaySdWav           playSdWav6;
AudioPlaySdWav           playSdWav7;
AudioPlaySdWav           playSdWav8;
AudioPlaySdWav           playSdWav9;
AudioPlaySdWav           playSdWav10;
AudioPlaySdWav           playSdWav11;

AudioMixer4              mixer1;   
AudioMixer4              mixer2;
AudioMixer4              mixer3;
AudioMixer4              mixer4;

AudioOutputAnalogStereo  dacs1;   

AudioConnection          patchCord1(playSdWav1, 0, mixer1, 0);
AudioConnection          patchCord2(playSdWav2, 0, mixer1, 1);
AudioConnection          patchCord5(playSdWav3, 0, mixer1, 2);
AudioConnection          patchCord6(playSdWav4, 0, mixer1, 3);

AudioConnection          patchCord7(playSdWav5, 0, mixer2, 0);
AudioConnection          patchCord8(playSdWav6, 0, mixer2, 1);
AudioConnection          patchCord9(playSdWav7, 0, mixer2, 2);
AudioConnection          patchCord10(playSdWav8, 0, mixer2, 3);

AudioConnection          patchCord11(playSdWav9, 0, mixer3, 0);
AudioConnection          patchCord12(playSdWav10, 0, mixer3, 1);
AudioConnection          patchCord13(playSdWav11, 0, mixer3, 2);

AudioConnection          patchCord14(mixer1, 0, mixer4, 0);
AudioConnection          patchCord15(mixer2, 0, mixer4, 1);
AudioConnection          patchCord16(mixer3, 0, mixer4, 2);


AudioConnection          patchCord3(mixer4, 0, dacs1, 0);
AudioConnection          patchCord4(mixer4, 0, dacs1, 1);
// Use these with the Teensy 3.5 & 3.6 SD card
#define SDCARD_CS_PIN    BUILTIN_SDCARD
#define SDCARD_MOSI_PIN  11  // not actually used
#define SDCARD_SCK_PIN   13  // not actually used

 //in e out params
int touchRead_pin_sequ = 0; 
int touchRead_pin_wform1 = 1; 
int touchRead_pin_wform2 = 15; 
int touchRead_pin_env1 = 29; 
int touchRead_pin_env2 = 30; 
int touchRead_pin_env3 = 23; 
int touchRead_pin_fil1 = 22; 
int touchRead_pin_fil2 = 19; 
int touchRead_pin_fil3 = 18;
int touchRead_pin_rev1 = 17;
int touchRead_pin_rev2 = 16;

int pot_seq = 14;
int pot_filter = 38;
int pot_volume = 39;

const int redPin =  3;
const int greenPin =  2;
const int bluePin =  4;

//debounce touch pin waveform
unsigned long currentMillistouch = 0;
unsigned long  previousMillistouch = 0;
//debounce touch pin waveform
unsigned long currentMillis = 0;
unsigned long  previousMillis = 0;
int touchState = 0;

unsigned long debounceDelay = 3000; 

float data1, data2, data3, data4, data5, data6, data7, data8, data9, data10, data11, data12, data13, data14; 
int init_data1, init_data2, init_data3, init_data4, init_data5, init_data6, init_data7, init_data8, init_data9, init_data10, init_data11; 
int data1_new, data1_old,  data2_old, data3_old, data4_new, data4_old, data5_new, data5_old, data6_new, data6_old, data7_old, data8_old,  data9_old;
int data2_new=0; int data3_new=0; int data7_new; int data8_new=0; int data9_new=0; int data10_new=0; int data11_new=0;

int counter7=0;int counter8=0;int counter9=0;int counter10=0;int counter11=0;


void setup() {
 


//----INPUTS-SETUP---------
 //pot
  pinMode(pot_seq, INPUT);
  pinMode(pot_filter, INPUT);
  pinMode(pot_volume, INPUT);
  //touch
  pinMode(touchRead_pin_sequ, INPUT);
  pinMode(touchRead_pin_wform1, INPUT);
  pinMode(touchRead_pin_wform2, INPUT);
  pinMode(touchRead_pin_env1, INPUT);
  pinMode(touchRead_pin_env2, INPUT);
  pinMode(touchRead_pin_env3, INPUT);
  pinMode(touchRead_pin_fil1, INPUT);
  pinMode(touchRead_pin_fil2, INPUT);
  pinMode(touchRead_pin_fil3, INPUT);
  pinMode(touchRead_pin_rev1, INPUT);
  pinMode(touchRead_pin_rev2, INPUT);
  //led rgb
  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin, OUTPUT);
  //init touch pins
  init_data1=touchRead(touchRead_pin_sequ);
  init_data2=touchRead(touchRead_pin_wform1); 
  init_data3=touchRead(touchRead_pin_wform2); 
  init_data4=touchRead(touchRead_pin_env1); 
  init_data5=touchRead(touchRead_pin_env2); 
  init_data6=touchRead(touchRead_pin_env3); 
  init_data7=touchRead(touchRead_pin_fil1); 
  init_data8=touchRead(touchRead_pin_fil2); 
  init_data9=touchRead(touchRead_pin_fil3); 
  init_data10=touchRead(touchRead_pin_rev1); 
  init_data11=touchRead(touchRead_pin_rev2); 
   Serial.begin(9600);
  AudioMemory(100);

  SPI.setMOSI(SDCARD_MOSI_PIN);
  SPI.setSCK(SDCARD_SCK_PIN);
  if (!(SD.begin(SDCARD_CS_PIN))) {
    while (1) {
      Serial.println("Unable to access the SD card");
      delay(500);
    }
  }

  //led on
  delay(1000);
  analogWrite(redPin,0);
 delay(500);
  analogWrite(greenPin,0);
  delay(300);
  analogWrite(bluePin, 0);
delay(300);

data1_new=1; data3_new=1; data5_new=1; data7_new=1; data8_new=1; data9_new=1;
data2_new=1; data4_new=1; data6_new=1; data10_new=1; data11_new=1;
}


void loop() {
  
data1=touchRead(touchRead_pin_sequ);
data2=touchRead(touchRead_pin_wform1); 
data3=touchRead(touchRead_pin_wform2); 
data4=touchRead(touchRead_pin_env1); 
data5=touchRead(touchRead_pin_env2); 
data6=touchRead(touchRead_pin_env3); 
data7=touchRead(touchRead_pin_fil1); 
data8=touchRead(touchRead_pin_fil2); 
data9=touchRead(touchRead_pin_fil3); 
data10=touchRead(touchRead_pin_rev1); 
data11=touchRead(touchRead_pin_rev2); 

    


   soglia(data1,init_data1);
   soglia1(data2,init_data2);
   soglia2(data3,init_data3);
   soglia3(data4,init_data4);   

    soglia4(data5,init_data5); 
    soglia5(data6,init_data6); 
    soglia6(data7,init_data7); 
    soglia7(data8,init_data8);

    soglia8(data9,init_data9);
    soglia9(data10,init_data10);
    soglia10(data11,init_data11);
    
   
 switch (data1_new) {
  case 0: 
  if (playSdWav1.isPlaying() == false) {       
//    if (playSdWav2.isPlaying() == true) {
//    data2_new=1;
//    }
//    if (playSdWav3.isPlaying() == true) {
//    data3_new=1;
//    }
//    if (playSdWav4.isPlaying() == true) {
//    data4_new=1;
//    }
//    if (playSdWav5.isPlaying() == true) {
//    data5_new=1;
//    }
//    if (playSdWav6.isPlaying() == true) {
//    data6_new=1;
//    }
//    if (playSdWav7.isPlaying() == true) {
//    data7_new=1;
//    }
//    if (playSdWav8.isPlaying() == true) {
//    data8_new=1;
//    }    
//    if (playSdWav9.isPlaying() == true) {
//    data9_new=1;
//    }     
//    if (playSdWav10.isPlaying() == true) {
//    data10_new=1;
//    }    
//    if (playSdWav11.isPlaying() == true) {
//    data11_new=1;
//    }    
    playSdWav1.play("1.WAV");
    delay(10);
     // wait for library to parse WAV info
    } else {if (abs(playSdWav1.lengthMillis()-playSdWav1.positionMillis())<=200){
      data1_new=1;
    }} break;
  case 1: //"Min"
    playSdWav1.stop();

} 

 switch (data2_new) {
  case 0: 
  if (playSdWav2.isPlaying() == false) {   
//    if (playSdWav1.isPlaying() == true) {
//    data1_new=1;
//    }
//    if (playSdWav3.isPlaying() == true) {
//    data3_new=1;
//    }
//    if (playSdWav4.isPlaying() == true) {
//    data4_new=1;
//    }
//    if (playSdWav5.isPlaying() == true) {
//    data5_new=1;
//    }
//    if (playSdWav6.isPlaying() == true) {
//    data6_new=1;
//    }
//    if (playSdWav7.isPlaying() == true) {
//    data7_new=1;
//    }
//    if (playSdWav8.isPlaying() == true) {
//    data8_new=1;
//    }    
//    if (playSdWav9.isPlaying() == true) {
//    data9_new=1;
//    }  
//    if (playSdWav10.isPlaying() == true) {
//    data10_new=1;
//    }      
//    if (playSdWav11.isPlaying() == true) {
//    data11_new=1;
//    }     
    playSdWav2.play("2.WAV");
    delay(10);
  } else {if (abs(playSdWav2.lengthMillis()-playSdWav2.positionMillis())<=200){
      data2_new=1;
    }}
     // wait for library to parse WAV info
    break;
  case 1: //"Min"
  
    playSdWav2.stop();  
} 
  
  switch (data3_new) {
  case 0: 
  if (playSdWav3.isPlaying() == false) {   
//    if (playSdWav1.isPlaying() == true) {
//    data1_new=1;
//    }
//    if (playSdWav2.isPlaying() == true) {
//    data2_new=1;
//    }
//    if (playSdWav4.isPlaying() == true) {
//    data4_new=1;
//    }
//    if (playSdWav5.isPlaying() == true) {
//    data5_new=1;
//    }
//    if (playSdWav6.isPlaying() == true) {
//    data6_new=1;
//    }
//    if (playSdWav7.isPlaying() == true) {
//    data7_new=1;
//    }
//    if (playSdWav8.isPlaying() == true) {
//    data8_new=1;
//    }    
//    if (playSdWav9.isPlaying() == true) {
//    data9_new=1;
//    }     
//    if (playSdWav10.isPlaying() == true) {
//    data10_new=1;
//    }      
//    if (playSdWav11.isPlaying() == true) {
//    data11_new=1;
//    }  
    playSdWav3.play("3.WAV");
    delay(10);
  } else {if (abs(playSdWav3.lengthMillis()-playSdWav3.positionMillis())<=200){
      data3_new=1;
    }}
     // wait for library to parse WAV info
    break;
  case 1: //"Min"

    playSdWav3.stop();    
  default:

    break;
} 
   Serial.println(data4_new);
  
  switch (data4_new) {
  case 0: 
  if (playSdWav4.isPlaying() == false) {   
//    if (playSdWav1.isPlaying() == true) {
//    data1_new=1;
//    }
//    if (playSdWav2.isPlaying() == true) {
//    data2_new=1;
//    }
//    if (playSdWav3.isPlaying() == true) {
//    data3_new=1;
//    }
//    if (playSdWav5.isPlaying() == true) {
//    data5_new=1;
//    }
//    if (playSdWav6.isPlaying() == true) {
//    data6_new=1;
//    }
//    if (playSdWav7.isPlaying() == true) {
//    data7_new=1;
//    }
//    if (playSdWav8.isPlaying() == true) {
//    data8_new=1;
//    }    
//    if (playSdWav9.isPlaying() == true) {
//    data9_new=1;
//    }    
//    if (playSdWav10.isPlaying() == true) {
//    data10_new=1;
//    }       
//    if (playSdWav11.isPlaying() == true) {
//    data11_new=1;
//    } 
    playSdWav4.play("4.WAV");
    delay(10);
  } else {
   if (abs(playSdWav4.lengthMillis()-playSdWav4.positionMillis())<=200){
      data4_new=1;
    }}
     // wait for library to parse WAV info
    break;
  case 1: //"Min"
    playSdWav4.stop();  

} 


        
  switch (data5_new) {
  case 0: 
  if (playSdWav5.isPlaying() == false) {   
//    if (playSdWav1.isPlaying() == true) {
//    data1_new=1;
//    }
//    if (playSdWav2.isPlaying() == true) {
//    data2_new=1;
//    }
//    if (playSdWav3.isPlaying() == true) {
//    data3_new=1;
//    }
//    if (playSdWav4.isPlaying() == true) {
//    data4_new=1;
//    }
//    if (playSdWav6.isPlaying() == true) {
//    data6_new=1;
//    }
//    if (playSdWav7.isPlaying() == true) {
//    data7_new=1;
//    }
//    if (playSdWav8.isPlaying() == true) {
//    data8_new=1;
//    }    
//    if (playSdWav9.isPlaying() == true) {
//    data9_new=1;
//    } 
//    if (playSdWav10.isPlaying() == true) {
//    data10_new=1;
//    }      
//    if (playSdWav11.isPlaying() == true) {
//    data11_new=1;
//    }  
    playSdWav5.play("5.WAV");
    delay(10);
  }  else {
 if (abs(playSdWav5.lengthMillis()-playSdWav5.positionMillis())<=200){
      data5_new=1;
    }}
     // wait for library to parse WAV info
    break;
  case 1: //"Min"
    playSdWav5.stop();  


  default:

    break;
}

 switch (data6_new) {
  case 0: 
  if (playSdWav6.isPlaying() == false) {   
//    if (playSdWav1.isPlaying() == true) {
//    data1_new=1;
//    }
//    if (playSdWav2.isPlaying() == true) {
//    data2_new=1;
//    }
//    if (playSdWav3.isPlaying() == true) {
//    data3_new=1;
//    }
//    if (playSdWav4.isPlaying() == true) {
//    data4_new=1;
//    }
//    if (playSdWav5.isPlaying() == true) {
//    data5_new=1;
//    }
//    if (playSdWav7.isPlaying() == true) {
//    data7_new=1;
//    }
//    if (playSdWav8.isPlaying() == true) {
//    data8_new=1;
//    }    
//    if (playSdWav9.isPlaying() == true) {
//    data9_new=1;
//    }     
//    if (playSdWav10.isPlaying() == true) {
//    data10_new=1;
//    }      
//    if (playSdWav11.isPlaying() == true) {
//    data11_new=1;
//    }  
    playSdWav6.play("6.WAV");
    delay(10);
  }
    else {
 if (abs(playSdWav6.lengthMillis()-playSdWav6.positionMillis())<=200){
      data6_new=1;
    }}
     // wait for library to parse WAV info
    break;
  case 1: //"Min"
    playSdWav6.stop();  


  default:

    break;
}

 switch (data7_new) {
  case 0: 
  if (playSdWav7.isPlaying() == false) {   
//    if (playSdWav1.isPlaying() == true) {
//    data1_new=1;
//    }
//    if (playSdWav2.isPlaying() == true) {
//    data2_new=1;
//    }
//    if (playSdWav3.isPlaying() == true) {
//    data3_new=1;
//    }
//    if (playSdWav4.isPlaying() == true) {
//    data4_new=1;
//    }
//    if (playSdWav5.isPlaying() == true) {
//    data5_new=1;
//    }
//    if (playSdWav6.isPlaying() == true) {
//    data6_new=1;
//    }
//    if (playSdWav8.isPlaying() == true) {
//    data8_new=1;
//    }
//    if (playSdWav9.isPlaying() == true) {
//    data9_new=1;
//    } 
//    if (playSdWav10.isPlaying() == true) {
//    data10_new=1;
//    }       
//    if (playSdWav11.isPlaying() == true) {
//    data11_new=1;
//    } 
    playSdWav7.play("7.WAV");
    delay(10);
  }
  else {
 if (abs(playSdWav7.lengthMillis()-playSdWav7.positionMillis())<=200){
      data7_new=1;
    }
}
     // wait for library to parse WAV info
    break;
  case 1: //"Min"
    playSdWav7.stop();  

  default:

    break;
}

 switch (data8_new) {
  case 0: 
  if (playSdWav8.isPlaying() == false) {   
//    if (playSdWav1.isPlaying() == true) {
//    data1_new=1;
//    }
//    if (playSdWav2.isPlaying() == true) {
//    data2_new=1;
//    }
//    if (playSdWav3.isPlaying() == true) {
//    data3_new=1;
//    }
//    if (playSdWav4.isPlaying() == true) {
//    data4_new=1;
//    }
//    if (playSdWav5.isPlaying() == true) {
//    data5_new=1;
//    }
//    if (playSdWav6.isPlaying() == true) {
//    data6_new=1;
//    }
//    if (playSdWav7.isPlaying() == true) {
//    data7_new=1;
//    }
//    if (playSdWav9.isPlaying() == true) {
//    data9_new=1;
//    }   
//    if (playSdWav10.isPlaying() == true) {
//    data10_new=1;
//    }     
//    if (playSdWav11.isPlaying() == true) {
//    data11_new=1;
//    }    

    playSdWav8.play("8.WAV");
    delay(10);

  }else {
 if (abs(playSdWav8.lengthMillis()-playSdWav8.positionMillis())<=200){
      data8_new=1;
    }
}
     // wait for library to parse WAV info
    break;
  case 1: //"Min"
    playSdWav8.stop();  
  default:

    break;
}

 switch (data9_new) {
  case 0: 
  if (playSdWav9.isPlaying() == false) {   
//    if (playSdWav1.isPlaying() == true) {
//    data1_new=1;
//    }
//    if (playSdWav2.isPlaying() == true) {
//    data2_new=1;
//    }
//    if (playSdWav3.isPlaying() == true) {
//    data3_new=1;
//    }
//    if (playSdWav4.isPlaying() == true) {
//    data4_new=1;
//    }
//    if (playSdWav5.isPlaying() == true) {
//    data5_new=1;
//    }
//    if (playSdWav6.isPlaying() == true) {
//    data6_new=1;
//    }
//    if (playSdWav7.isPlaying() == true) {
//    data7_new=1;
//    }
//    if (playSdWav8.isPlaying() == true) {
//    data8_new=1;
//    }
//    if (playSdWav10.isPlaying() == true) {
//    data10_new=1;
//    }    
//    if (playSdWav11.isPlaying() == true) {
//    data11_new=1;
//    } 
//    
    playSdWav9.play("9.WAV");
    delay(10);
   
  }else {
 if (abs(playSdWav9.lengthMillis()-playSdWav9.positionMillis())<=200){
      data9_new=1;
    }
}
     // wait for library to parse WAV info
    break;
  case 1: //"Min"
    playSdWav9.stop();  

  default:

    break;
}

 switch (data10_new) {
  case 0: 
  if (playSdWav10.isPlaying() == false) {   
//    if (playSdWav1.isPlaying() == true) {
//    data1_new=1;
//    }
//    if (playSdWav2.isPlaying() == true) {
//    data2_new=1;
//    }
//    if (playSdWav3.isPlaying() == true) {
//    data3_new=1;
//    }
//    if (playSdWav4.isPlaying() == true) {
//    data4_new=1;
//    }
//    if (playSdWav5.isPlaying() == true) {
//    data5_new=1;
//    }
//    if (playSdWav6.isPlaying() == true) {
//    data6_new=1;
//    }
//    if (playSdWav7.isPlaying() == true) {
//    data7_new=1;
//    }
//    if (playSdWav8.isPlaying() == true) {
//    data8_new=1;
//    }
//    if (playSdWav9.isPlaying() == true) {
//    data9_new=1;
//    }    
//    if (playSdWav11.isPlaying() == true) {
//    data11_new=1;
//    }       
//    
    playSdWav10.play("10.WAV");
    delay(10);

  }else {
 if (abs(playSdWav10.lengthMillis()-playSdWav10.positionMillis())<=200){
      data10_new=1;
    }
}
     // wait for library to parse WAV info
    break;
  case 1: //"Min"
    playSdWav10.stop();  


  default:

    break;
}

 switch (data11_new) {
  case 0: 
  if (playSdWav11.isPlaying() == false) {   
//    if (playSdWav1.isPlaying() == true) {
//    data1_new=1;
//    }
//    if (playSdWav2.isPlaying() == true) {
//    data2_new=1;
//    }
//    if (playSdWav3.isPlaying() == true) {
//    data3_new=1;
//    }
//    if (playSdWav4.isPlaying() == true) {
//    data4_new=1;
//    }
//    if (playSdWav5.isPlaying() == true) {
//    data5_new=1;
//    }
//    if (playSdWav6.isPlaying() == true) {
//    data6_new=1;
//    }
//    if (playSdWav7.isPlaying() == true) {
//    data7_new=1;
//    }
//    if (playSdWav8.isPlaying() == true) {
//    data8_new=1;
//    }
//    if (playSdWav9.isPlaying() == true) {
//    data9_new=1;
//    }  
//    if (playSdWav10.isPlaying() == true) {
//    data10_new=1;
//    }       
    playSdWav11.play("11.WAV");
    delay(10);
  } else {
 if (abs(playSdWav11.lengthMillis()-playSdWav11.positionMillis())<=200){
      data11_new=1;
    }
}

     // wait for library to parse WAV info
    break;
  case 1: //"Min"
    playSdWav11.stop();  

  default:

    break;
}


}
  
 

void soglia(int _data2, int _init_data2){
  
  
if ((_data2 > 1.6*_init_data2)||(_data2 < 0.4*init_data2)) {
  currentMillistouch = millis();
}
 if (currentMillistouch - previousMillistouch >= debounceDelay) {

    previousMillistouch = currentMillistouch;

  
    if (touchState == LOW) {
      touchState = HIGH;
    } else {
      touchState = LOW;
    }
    if ((_data2 > 1.6*init_data2)||(_data2 < 0.4*init_data2)&&(touchState)) {
     data1_new=(data1_new+1)%2; 
    }
     
    }
    }
 
void soglia1(int _data2, int _init_data2){
  
  
if ((_data2 > 1.6*_init_data2)||(_data2 < 0.4*init_data2)) {
  currentMillistouch = millis();
}
 if (currentMillistouch - previousMillistouch >= debounceDelay) {

    previousMillistouch = currentMillistouch;

  
    if (touchState == LOW) {
      touchState = HIGH;
    } else {
      touchState = LOW;
    }
    if ((_data2 > 1.6*init_data2)||(_data2 < 0.4*init_data2)&&(touchState)) {
     data2_new=(data2_new+1)%2; 
    }

     
    }
    }
 
void soglia2(int _data2, int _init_data2){
  
  
if ((_data2 > 1.6*_init_data2)||(_data2 < 0.4*init_data2)) {
  currentMillistouch = millis();
}
 if (currentMillistouch - previousMillistouch >= debounceDelay) {

    previousMillistouch = currentMillistouch;

  
    if (touchState == LOW) {
      touchState = HIGH;
    } else {
      touchState = LOW;
    }
    if ((_data2 > 1.6*init_data2)||(_data2 < 0.4*init_data2)&&(touchState)) {
     data3_new=(data3_new+1)%2; 
    }
     
    }
    }

void soglia3(int _data2, int _init_data2){
  
  
if ((_data2 > 1.6*_init_data2)||(_data2 < 0.4*init_data2)) {
  currentMillistouch = millis();
}
 if (currentMillistouch - previousMillistouch >= debounceDelay) {

    previousMillistouch = currentMillistouch;

  
    if (touchState == LOW) {
      touchState = HIGH;
    } else {
      touchState = LOW;
    }
    if ((_data2 > 1.6*init_data2)||(_data2 < 0.4*init_data2)&&(touchState)) {
     data4_new=(data4_new+1)%2; 
    }
     
    }
    }


void soglia4(int _data2, int _init_data2){
if ((_data2 > 1.6*_init_data2)||(_data2 < 0.4*init_data2)) {
  currentMillistouch = millis();
}
 if (currentMillistouch - previousMillistouch >= debounceDelay) {

    previousMillistouch = currentMillistouch;

  
    if (touchState == LOW) {
      touchState = HIGH;
    } else {
      touchState = LOW;
    }
    if ((_data2 > 1.6*init_data2)||(_data2 < 0.4*init_data2)&&(touchState)) {
     data5_new=(data5_new+1)%2; 
    }
     
    }
    }
    
void soglia5(int _data2, int _init_data2){
if ((_data2 > 1.6*_init_data2)||(_data2 < 0.4*init_data2)) {
  currentMillistouch = millis();
}
 if (currentMillistouch - previousMillistouch >= debounceDelay) {

    previousMillistouch = currentMillistouch;

  
    if (touchState == LOW) {
      touchState = HIGH;
    } else {
      touchState = LOW;
    }
    if ((_data2 > 1.6*init_data2)||(_data2 < 0.4*init_data2)&&(touchState)) {
     data6_new=(data6_new+1)%2; 
    }
     
    }
    }

 void soglia6(int _data2, int _init_data2){
if ((_data2 > 1.6*_init_data2)||(_data2 < 0.4*init_data2)) {
  currentMillistouch = millis();
}
 if (currentMillistouch - previousMillistouch >= debounceDelay) {

    previousMillistouch = currentMillistouch;

  
    if (touchState == LOW) {
      touchState = HIGH;
    } else {
      touchState = LOW;
    }
    if ((_data2 > 1.6*init_data2)||(_data2 < 0.4*init_data2)&&(touchState)) {
     data7_new=(data7_new+1)%2; 
    }
     
    }
    }
 void soglia7(int _data2, int _init_data2){
if ((_data2 > 1.6*_init_data2)||(_data2 < 0.4*init_data2)) {
  currentMillistouch = millis();
}
 if (currentMillistouch - previousMillistouch >= debounceDelay) {

    previousMillistouch = currentMillistouch;

  
    if (touchState == LOW) {
      touchState = HIGH;
    } else {
      touchState = LOW;
    }
    if ((_data2 > 1.6*init_data2)||(_data2 < 0.4*init_data2)&&(touchState)) {
     data8_new=(data8_new+1)%2; 
    }
     
    }
    }

 void soglia8(int _data2, int _init_data2){
if ((_data2 > 1.6*_init_data2)||(_data2 < 0.4*init_data2)) {
  currentMillistouch = millis();
}
 if (currentMillistouch - previousMillistouch >= debounceDelay) {

    previousMillistouch = currentMillistouch;

  
    if (touchState == LOW) {
      touchState = HIGH;
    } else {
      touchState = LOW;
    }
    if ((_data2 > 1.6*init_data2)||(_data2 < 0.4*init_data2)&&(touchState)) {
     data9_new=(data9_new+1)%2; 
    }
     
    }
    }


 void soglia9(int _data2, int _init_data2){
if ((_data2 > 1.6*_init_data2)||(_data2 < 0.4*init_data2)) {
  currentMillistouch = millis();
}
 if (currentMillistouch - previousMillistouch >= debounceDelay) {

    previousMillistouch = currentMillistouch;

  
    if (touchState == LOW) {
      touchState = HIGH;
    } else {
      touchState = LOW;
    }
    if ((_data2 > 1.6*init_data2)||(_data2 < 0.4*init_data2)&&(touchState)) {
     data10_new=(data10_new+1)%2; 
    }
     
    }
    }
    
 void soglia10(int _data2, int _init_data2){
if ((_data2 > 1.6*_init_data2)||(_data2 < 0.4*init_data2)) {
  currentMillistouch = millis();
}
 if (currentMillistouch - previousMillistouch >= debounceDelay) {

    previousMillistouch = currentMillistouch;

  
    if (touchState == LOW) {
      touchState = HIGH;
    } else {
      touchState = LOW;
    }
    if ((_data2 > 1.6*init_data2)||(_data2 < 0.4*init_data2)&&(touchState)) {
     data11_new=(data11_new+1)%2; 
    }
     
    }
    }
