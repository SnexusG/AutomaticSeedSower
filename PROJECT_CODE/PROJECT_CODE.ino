//Code for numpad + lcd + servo + motor driver :-


//Libraries Include in  this program :-
#include <Servo.h>
#include <Keypad.h>
#include <LiquidCrystal.h>


//Variables for servo :-
Servo myservo;
int servopin = 10 ; //Servo is attached to the pin No.1


//Keypad  program :-
const byte ROWS = 4; // Four rows
const byte COLS = 4; // Four columns

char keys[ROWS][COLS] =

{
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'*', '0', '.', '='}
};


// Pins for rows :-
byte rowPins[ROWS] = {};

//Pins for columns
byte colPins[COLS] = {};

// Create the Keypad
Keypad kpd = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );


//Lcd  program :-
LiquidCrystal lcd(A0, A1, A2, A3, A4, A5);


//Motor Driver :-
int IN1 = 2 ;   //Motor 1 +VE
int IN2 = 3 ;   //Motor 1 -VE
int IN3 = 4 ;   //Motor 2 +VE
int IN4 = 5 ;   //Motor 2 -VE 

//Extra Variables for internal and external Actions :-

//Group of variables for confirming whether printing task has been performed
int a = 0;
int b = 0;
int c = 0;
int d = 0;
int e = 0;

//Incrementer variable
int i = 0;

//Group of variables for calculating  post decimal digits
int m = 0;
int n = 0;
int o = 0;

//A variable to run lcd and keypad program only once
int p = 0;
int q = 0; //to restrict update of x1
int r = 0; //for first half cycle
int temp = 0; //to check if the half cycles have been completed or not
int s = 0; //for second half cycle


//Four main vaiables :-
float distance = 6;
float columns = 50;
int col = 3;
float distBet = 5;

//Variable to create new millis function
double Treq = 0;
double Nmillis = 0 ;
double turn= 1; //time taken to turn 90 degree

//Variables for decimal calculations
float decDist = 0;
float decColumns = 0;
float decdistBet = 0;

//Increment Variable
float mult = 10;
float Speed = 20; // assuming speed of bot to be 20cm/sec
  

//For my code :-
float x = 0;  //Forward running time
float y = 0;   //Distance between two seeds
float u = 0; //Distance between two columns
float z = 0;     // Increment variable
int w = 0 ;     // Controlling variable
float x1 = 0;

void setup() {
  lcd.begin(16, 2);
  lcd.clear();
  lcd.print("Press * to Start");
  Serial.begin(9600);
  pinMode(servopin, OUTPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  //Attaching servo to pin no.1
  myservo.attach(servopin);
}


void loop() {

/*  if (p == 0) {
    char key = kpd.getKey();

    // ==

    if (key == '=' && a == 1) {
      i++;
    }
    //Printing Input prompt
    if (key == '*' && i == 0 && a == 0) {
      print("Enter Distance");
      a = 1;
    }
    if (key == '=' && i == 1) {
      print("Columns Length");
      b = 1;
    }
    if (key == '=' && b == 1 && i == 2) {
      print("No. of columns");
      c = 1;
    }
    if (key == '=' && c == 1 && i == 3) {
      print("Dist b/w columns");
      d = 1;
    }


    if (key == '=' && i == 4 && d == 1) {
      lcd.clear();
      lcd.print("Data fetched");
      lcd.setCursor(3, 1);
      lcd.print("Thank You!");
      delay(3000);
      lcd.clear();
      p = 1;
    }

    //CALCULATING INPUT DATA AND STORING
    //Distance
    if (key != '*' && key != 'A' && key != 'B' && a == 1) {
      if (key && b == 0 && c == 0) {
        if (key != '.' && m == 0) {
          distance *= 10;
          distance += key - '0';
          distance += decDist;
        }
        if (m >= 1 && key!= '.') {
          decDist = ((key - '0') / mult);
          mult *= 10;
          distance += decDist;
        }
        if (key == '.') {
          m++;
          Serial.println(m);
        }
        if (m < 2 || key != '.' ) {
          lcd.print(key);
        }
      }


      if (key == 'C') {
        distance = 0;
        m = 0;
        decDist = 0;
        mult = 10;
        print("Enter Distance");
      }
    }

    //TILL HERE

    //Columns Length
    if (b == 1 && key != 'A' && key != 'B' && key != '=') {
      if (key && c == 0) {
        if (key != '.' && n == 0) {
          mult = 10;
          columns *= 10;
          columns += key - '0';
          columns += decColumns;
        }
        if (n >= 1 && key != '.') {
          decColumns = ((key - '0') / mult);
          mult *= 10;
          columns += decColumns;
        }
        if (key == '.') {
          n++;
        }
        if (n < 2 || key != '.' ) {
          lcd.print(key);
        }
      }
      if (key == 'C') {
        columns = 0;
        n = 0;
        mult = 10;
        decColumns = 0;
        print("Column Length");
      }
    }

    //Number of columns
    if (c == 1 && key != 'B' && key != '=' && key != '.') {
      if (key && d == 0) {
        col *= 10;
        col += key - '0';
        lcd.print(key);
      }
      if (key == 'C') {
        col = 0;
        print("NO. of columns");
      }
    }
    //Distance between two columns
    if (d == 1 && key != 'B' && key != '=') {
      if (key && e == 0) {
        if (key != '.' && o == 0) {
          mult = 10;
          distBet *= 10;
          distBet += key - '0';
          distBet += decdistBet;
        }
        if (o >= 1 && key != '.') {
          decdistBet = ((key - '0') / mult);
          mult *= 10;
          distBet += decdistBet;
        }
        if (key == '.') {
          o++;
        }
        if (o < 2 || key != '.' ) {
          lcd.print(key);
        }
      }
      if (key == 'C') {
        distBet = 0;
        o = 0;
        mult = 10;
        decdistBet = 0;
        print("Distance b/w columns");
      }
    }
    //Thank you
    if (e == 1 && key != 'C' && key != '=') {
      lcd.clear();
    }
    //DISPLAYING RESULT
    if (key == '=' && i == 1) {
      Serial.print("Distance ");
      Serial.println(distance);
    }
    if (key == '=' && i == 2) {
      Serial.print("Column length ");
      Serial.println(columns);
    }
    if (key == '=' && i == 3) {
      Serial.print("No. of columns ");
      Serial.println(col);
    }
    if (key == '=' && i == 4) {
      Serial.print("Distance between two columns ");
      Serial.println(distBet);
    }
  }
  //done KeypadxxLCD
  */
  p=1;


 if (p == 1) {              //An if loop for measuring Time required by lcd and keypad action
      Treq = 0;
      p = 2;
    }
    Nmillis = (millis() - Treq)/1000 ;    //For printing purpose
 
    

    //Code begins here
    //Note that now the new millis is Nmillis (There is difference of 10 millis in The output )

    
    //Code for running bot in forward direction
r = col/2;
if(col%2 == 1){ // if no. of columns is odd
 r = r + 1;
 s = r-1;//the second half cycle will run one less than the no. of times the first half cycle runs
}
if(col%2 == 0){ // if no. of columns is even
 s = r; // the 2nd half cycle will run as many times as 1st half cycle
}
  
if(q == 0){  //to restrict value of x1 from changing after every cycle (x1 should always be orignal x)
x = columns/Speed;
x1 = x;
y = distance/Speed;
u = distBet/Speed;
q++;
}

  
if(temp<r){ 
if( Nmillis >= 0 && Nmillis <= x ){
     w = 0;
     forward();
    //This code is temporary and just  for indication purpose  
  }

  //Code for Servo 
  
  if( Nmillis >= z && Nmillis <= z + 0.05){
    if(w == 0){
    myservo.write(45); }    //45 stands for servo motor  will move from it's initial position to 45 degree
   }
  
  if( Nmillis >= z+0.25 && Nmillis <= z + 0.27){
    myservo.write(0);
    z = z + y ;
  }
  
if(Nmillis >= x && Nmillis <= x+turn){
  w = 1;      // New variable for turning off  servo motor after distance x 
  right();
}  
    
if(Nmillis >= (x+turn) && Nmillis <= (x+turn)+u){
forward();
}

if(Nmillis >= ((x+turn)+u) && Nmillis <= x+(2*turn)+u){
  right();
}
 
//first half cycle  
if((temp==s && Nmillis >= x+(2*turn)+u)||(r == 1 && Nmillis >= x+(2*turn)+u)){  //if the bot has comleted its no. of 2nd half cycles, then turn off bot at end of first half cycle
 off();
} 
    


if(temp<s){

if(Nmillis >= x+(2*turn)+u && Nmillis <= (x1 + x)+(2*turn)+u){
   w=0;
   forward();
}  
  
if(Nmillis >= (x1 + x)+(2*turn)+u && Nmillis <= (x1+x)+(3*turn)+u){
  w=1;
  left();
}
if(Nmillis >= (x1+x)+(3*turn)+u && Nmillis <= (x1+x)+(3*turn)+(2*u)){
  forward();
}
if(Nmillis >= (x1+x)+(3*turn)+(2*u) && Nmillis <= (x1+x)+(4*turn)+(2*u)){
left();
}
if(Nmillis == (x1+x)+(4*turn)+(2*u)){//if bot has completed its whole cycle, then update x and increament temp
  x = (x1+x+x1)+(4*turn)+(2*u);
  temp++;
  if(temp == r){
    off(); // if temp = no. of first half cycles, turn bot off
  }
  Serial.println(temp);
}
  }
}
   
   
  // void loop bracket

}


//functions
void print(String text) {
  lcd.clear();
  lcd.print(text);
  lcd.setCursor(0, 1);
  lcd.blink();
}



void forward(){
    digitalWrite(IN1,HIGH );   //Right side motor in forward (Negative speed will be shown)
    digitalWrite(IN2,LOW );
    digitalWrite(IN3,HIGH );   //Left Side motor in forward (Negative Speed will be shown)
    digitalWrite(IN4,LOW );
}

void right(){
    digitalWrite(IN1,LOW);     //right side of motor will run in backward direction
    digitalWrite(IN2,HIGH);
    digitalWrite(IN3,HIGH);     //Left side of motor will run in forward direction
    digitalWrite(IN4,LOW);
}

void left(){
    digitalWrite(IN1,HIGH);     
    digitalWrite(IN2,LOW);
    digitalWrite(IN3,LOW);     
    digitalWrite(IN4,HIGH);
}

void off(){
    digitalWrite(IN1,LOW);     
    digitalWrite(IN2,LOW);
    digitalWrite(IN3,LOW);     
    digitalWrite(IN4,LOW);
}

