#include <Keypad.h>
#include <LiquidCrystal.h>
#include <Servo.h>

//define variables
const byte ROWS = 1;
const byte COLS = 4;
int ledSuccess = A3;
int ledFailed = A4;

// define keymap
char keys[ROWS][COLS] = {
  {'1','2','3','4'}
};
byte rowPins[ROWS] = {8};
byte colPins[COLS] = {13, 12, 11, 10};

//create keypad
Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );

//set lcd pins
LiquidCrystal lcd(2, 3, 7, 6, 5, 4);

//initiate servo
Servo myservo;
int pos = 0;

//create code array
char code [4] = {'1', '2', '4', '3'};
char type [5] = {};
int i = 0; // tracks array position

void setup() {
  pinMode(ledSuccess, OUTPUT);
  pinMode(ledFailed, OUTPUT);
  lcd.begin(16, 2);
  Serial.begin(9600);
  myservo.attach(A2);
  myservo.write(0);
}

void loop(){
  //define variables
  char key = keypad.getKey();
  
  if(key != NO_KEY) {
    //display input on lcd
    lcd.print(char(key));
    type[i] = key;
    i++; //keep track of number of inputs
    Serial.println(type);//debugger
    Serial.println(i);//debugger

    // if input reaches code length
    if(i==4){
      int count = 0;
      int n = 0;
      char *pointer = code;    
      Serial.println("start test");//debugger

      //check if input array matches code array
      for(n = 0; n < 4; n++){   
        if ( type[n] == code[n] ){
          count++;
          Serial.println("test pass");//debugger
        }
        else{
          Serial.println("test fail");//debugger
        }
      }

      // input is correct, raise deadlock
      if(count == 4){
        for(pos = 0; pos<=90; pos++){
           myservo.write(pos);
           delay(15);
           //turn on green light
           digitalWrite(ledSuccess, HIGH);
        }
      }
      else {
          // turn on red light
          digitalWrite(ledFailed, HIGH);
        }
    }
  }
}
