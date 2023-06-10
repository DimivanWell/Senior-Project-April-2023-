#include <UTFT.h> 
#include <URTouch.h>
#include <TEA5767N.h>

UTFT    myGLCD(ILI9341_16,38,39,40,41); //Parameters should be adjusted to your Display/Schield model
URTouch  myTouch( 6, 5, 4, 3, 2);

TEA5767N radio = TEA5767N();

extern unsigned char BigNumbers[];
extern unsigned char TinyFont[];

extern uint8_t splash[];
extern uint8_t signal5[];
extern uint8_t signal4[];
extern uint8_t signal3[];
extern uint8_t signal2[];
extern uint8_t signal1[];

extern uint8_t SmallFont[];
extern uint8_t BigFont[];
extern uint8_t SevenSegNumFont[];
extern uint8_t SevenSegmentFull[];

int x, y;
String frequency = " "; //printed freqency
float freq = 0; //radio frequency
char currentPage, selectedUnit;
int auxWasOn = 3;
int radioOn = 0;
int xTOU = 244; //75 start volume at power on
int yTOU = 208; //Start Location
int volENT = 3;
int volRAD = 6; 



void setup() {
  myGLCD.InitLCD();
  myGLCD.clrScr();
  myTouch.InitTouch();
  myTouch.setPrecision(PREC_MEDIUM);

  pinMode(13, OUTPUT);
  digitalWrite(13, HIGH);
  pinMode(8, OUTPUT);
  pinMode(9, OUTPUT);
  radio.mute();
  radio.setMonoReception();
  radio.setStereoNoiseCancellingOn();
  Serial.begin(9600);
  
  drawHomeScreen();  // Draws the Home Screen
  currentPage = '0'; // Indicates that we are at Home Screen
}

void loop() {
  if (myTouch.dataAvailable()) {
      myTouch.read();
      x=myTouch.getX(); // X coordinate where the screen has been pressed
      y=myTouch.getY(); // Y coordinates where the screen has been pressed

        if((x>=2) && (x<=75) && (y>=2) && (y<=30)){
          //Preset 1
          radioOn = 1;
          frequency = "95.5";
          freq = 95.5;
          selectStation();
          volumeCNTRL();
        }
        if((x>=77) && (x<=150) && (y>=2) && (y<=30)){
          //Preset 2
          radioOn = 1;
          frequency  = "98.7";
          freq = 98.7;
          selectStation();
          volumeCNTRL();
        }
        if((x>=152) && (x<=225) && (y>=2) && (y<=30)){
          //Preset 3
          radioOn = 1;
          frequency  = "90.9";
          freq = 90.9;
          selectStation();
          volumeCNTRL();
        }
        if((x>=227) && (x<=299) && (y>=2) && (y<=30)){
          //Preset 4
          radioOn = 1;
          frequency  = "97.9";
          freq = 97.9;
          selectStation();
          volumeCNTRL();
        }
        if((x>=0) && (x<=50) && (y>=100) && (y<=125)){
          activAUX();
          volumeCNTRL();
          }
        if((x>=110)&&(x<=290)&&(y>=200)&&(y<=216)){
          volENT = 1;
          volumeCNTRL();
          }
   }
}
void drawHomeScreen() {
  // Title
  myGLCD.fillScr(0,71,171); //background color => cobalt
  myGLCD.setBackColor(0,71,171); // Sets the background color of text
  //_______________________________
  // Hz to be printed on the screen
    //myGLCD.setColor(255,255,255); // Sets color to white
    //myGLCD.setFont(BigFont); // Sets font to big
    //myGLCD.print("Hz", 270, 110); // Prints the string on the screen
  //_______________________________
  //Create the Squares for the preset press
 
  //_______________________________
  //Preset wording
  myGLCD.setColor(255,255,255);
  myGLCD.setFont(SmallFont);
  myGLCD.drawRect(2,2,75,25);//preset 1 box
  myGLCD.print("Preset 1", 10, 10);
  myGLCD.drawRect(77,2,150,25);//preset 2 box
  myGLCD.print("Preset 2", 80, 10);
  myGLCD.drawRect(152,2,225,25);//preset 3 box
  myGLCD.print("Preset 3", 160, 10);
  myGLCD.drawRect(227,2,299,25);//preset 4 box
  myGLCD.print("Preset 4", 235, 10);
  //_______________________________
  //Volume Wording
  myGLCD.setFont(BigFont);
  myGLCD.print("Volume", 150, 170);
  //_______________________________
  //Volume Slider
  volumeBASE();
  //_______________________________
  //AUX Button
  myGLCD.drawRoundRect(0,100,50,125);
  myGLCD.print("AUX", 2, 105);
  //_______________________________
  
}

void volumeBASE(){
  myGLCD.setColor(0,0,0);
  myGLCD.fillRoundRect(110,200,290,216);
  myGLCD.setColor(255,255,255);
  myGLCD.drawRoundRect(110,200,290,216);
  myGLCD.fillRect(113,206,287,210);
  if(volENT == 3){
    volumeCNTRL();//executes for the start of the program
  }
  if(volENT == 0){
    volENT = 5;//set the volume enter to only print the new circle
    volumeCNTRL();
    }
}
void volumeCNTRL(){
  //myGLCD.fillCircle(xTOU,yTOU,volRAD);
  while(volENT == 1){
      if (myTouch.dataAvailable()) {
          myTouch.read();
          x=myTouch.getX();
          y=myTouch.getY();
          if((y>=200) && (y<=216)){
            xTOU=x;
            if(xTOU<=113){
              xTOU = 113;
              }
            if(xTOU>=287){
              xTOU = 287;
              }  
            }
           //MAP FUNC
           
           //myGLCD.fillCircle(xTOU,yTOU,volRAD);
           if(myTouch.dataAvailable() == false){
              volENT = 0; //EXIT THE VOLUME CHANGE SECTION
              volumeBASE();
            }
        }
    
    }
  if(volENT == 5){//VOLUME CIRCLE WAS SET SO THE PREVIOUS VALUE ARE CLEARED
    myGLCD.fillCircle(xTOU,yTOU,volRAD);
    }
  if(volENT == 3){
      myGLCD.fillCircle(xTOU,yTOU,volRAD); //On start up the volume circle will set here
    }
  int vol = map(xTOU, 113,287,0, 255);
  analogWrite(9, vol);
  Serial.println(vol);
}



void selectStation() {
  myGLCD.clrScr();
  drawHomeScreen();
  digitalWrite(8, LOW);
  delay(500);
  if (auxWasOn == 1 or radioOn == 1){
    auxWasOn = 0;
    radioOn == 0;
    radio.turnTheSoundBackOn();
    }
  //radio.turnTheSoundBackOn();
  radio.selectFrequency(freq); // set radio frequency
  myGLCD.setColor(255,255,255);
  myGLCD.setFont(SevenSegmentFull);
  myGLCD.print(frequency, 100, 80); //Print Station to screen
  // Hz to be printed on the screen
  myGLCD.setFont(BigFont); // Sets font to big
  myGLCD.print("Hz", 270, 110); // Prints the string on the screen
  //_______________________________
}

void activAUX(){
  digitalWrite(8, HIGH);
  auxWasOn = 1;
  radio.mute();
  myGLCD.clrScr();
  drawHomeScreen();
  myGLCD.setFont(SevenSegmentFull);
  myGLCD.print("AUX", 130, 80);
  }

void frqChoose(){
  
}
}
  
