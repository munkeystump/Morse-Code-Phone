#include <Keypad.h> //http://www.arduino.cc/playground/uploads/Code/Keypad.zip  //tells to use keypad library
const byte ROWS = 3; // Three rows
const byte COLS = 3; // columns

char keys[ROWS][COLS] = {
  {'9', '6', '3'},
  {'8', '5', '2'},
  {'7', '4', '1'},
};

byte rowPins[ROWS] = { 9, 8, 7 };// Connect keypad COL0, COL1 and COL2 to these Arduino pins.
byte colPins[COLS] = { 5, 4, 3 };

int speaker = 11; //phone speaker pin
String guess; //string of current guess
String pass = "999"; //correct password
int dotLen = 210; // length of dash in morse code
int dashLen = dotLen * 3;
int hz = 500; // pitch of morse code tone
char stringToMorseCode[] = "message"; // message to be played by morse code
int handset = 2;

//Password password = Password( pass ); 

Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );


void setup() {
  // put your setup code here, to run once:
  pinMode(speaker, OUTPUT);
  pinMode(handset, INPUT);
  keypad.addEventListener(keypadEvent);
  Serial.begin(9600);
  //tone(speaker, 90); // Make call ready tone
}

void loop() {
  // put your main code here, to run repeatedly:
  if(!digitalRead(handset)){
    tone(speaker, 90); // Make call ready tone
    keypad.getKey();
  //Serial.println(digitalRead(handset));
  }
  else{
  noTone(speaker);
  }
}

void keypadEvent(KeypadEvent eKey) {
  switch (keypad.getState()) {
    case PRESSED:

      Serial.print("Enter:");
      Serial.println(eKey);
      delay(10);    
      //password.append(eKey);//add keypressed to current password;
      guess += eKey;
      if (guess.length()== pass.length()){
        if(guess == pass){ //check if full/correct password entered
          guess = "";
          playSuccessTone(); // tell playtone to play success tone/failure message
         }
        else{
          guess = "";
          playFailTone();
          } 
      }
  }
      noTone(speaker);
      tone(speaker, 90);
}
void playSuccessTone() {
    Serial.println("Accepted");
    noTone(speaker);
    tone(speaker, 1500, 100); 
      delay (100); 
      noTone (speaker);
      delay (180); 
      tone(speaker, 1500, 100); 
      delay (100); 
      noTone (speaker);
      delay (80); 
      tone(speaker, 1800, 650); 
      delay (650); 
      noTone (speaker); // this section makes the "you made it" beeps 

      noTone (speaker);
      delay (1000); // pause before morse codes
      morseEncoder();
}
void playFailTone() {
    Serial.println("Denied");
    noTone (speaker);
    delay (150); 
    tone(speaker, 180, 450); 
    delay (450); // this section makes the busy signal (wrong number)
}

void morseEncoder(){
for (int i = 0; i < sizeof(stringToMorseCode) - 1; i++)
  {
    // Get the character in the current position
  char tmpChar = stringToMorseCode[i];
  // Set the case to lower case
  tmpChar = toLowerCase(tmpChar);
  // Call the subroutine to get the morse code equivalent for this character
  GetChar(tmpChar);
  delay(dashLen);
  }
}
void MorseDash(){
  tone(speaker, hz, dashLen);  // start playing a tone
  delay(dashLen+dotLen);               // hold in this position
}
void MorseDot(){
  tone(speaker, hz, dotLen);  // start playing a tone
  delay(dotLen+dotLen);               // hold in this position
}

// *** Characters to Morse Code Conversion *** //
void GetChar(char tmpChar)
{
  // Take the passed character and use a switch case to find the morse code for that character
  switch (tmpChar) {
    case 'a': 
    MorseDot();
    MorseDash();
    break;
    case 'b':
    MorseDash();
    MorseDot();
    MorseDot();
    MorseDot();
    break;
    case 'c':
      MorseDash();
    MorseDot();
    MorseDash();
    MorseDot();
    break;
    case 'd':
    MorseDash();
    MorseDash();
    MorseDot();
    break;
    case 'e':
    MorseDot();
    break;
    case 'f':
      MorseDot();
    MorseDot();
    MorseDash();
    MorseDot();
    break;
    case 'g':
    MorseDash();
    MorseDash();
    MorseDot();
    break;
    case 'h':
      MorseDot();
    MorseDot();
    MorseDot();
    MorseDot();
    break;
    case 'i':
      MorseDot();
    MorseDot();
    break;
    case 'j':
      MorseDot();
    MorseDash();
    MorseDash();
    MorseDash();
    break;
      case 'k':
      MorseDash();
    MorseDot();
    MorseDash();
    break;
    case 'l':
      MorseDot();
    MorseDash();
    MorseDot();
    MorseDot();
    break;
      case 'm':
      MorseDash();
    MorseDash();
    break;
    case 'n':
      MorseDash();
    MorseDot();
    break;
    case 'o':
      MorseDash();
    MorseDash();
    MorseDash();
    break;
    case 'p':
      MorseDot();
    MorseDash();
    MorseDash();
    MorseDot();
    break;
    case 'q':
      MorseDash();
    MorseDash();
    MorseDot();
    MorseDash();
    break;
    case 'r':
      MorseDot();
    MorseDash();
    MorseDot();
    break;
    case 's':
      MorseDot();
    MorseDot();
    MorseDot();
    break;
    case 't':
      MorseDash();
    break;
    case 'u':
      MorseDot();
    MorseDot();
    MorseDash();
    break;
    case 'v':
      MorseDot();
    MorseDot();
    MorseDot();
    MorseDash();
    break;
    case 'w':
      MorseDot();
    MorseDash();
    MorseDash();
    break;
    case 'x':
      MorseDash();
    MorseDot();
    MorseDot();
    MorseDash();
    break;
    case 'y':
      MorseDash();
    MorseDot();
    MorseDash();
    MorseDash();
    break;
    case 'z':
      MorseDash();
    MorseDash();
    MorseDot();
    MorseDot();
    break;
    default: 
    // If a matching character was not found it will default to a blank space
    noTone(speaker);      
  }
}



