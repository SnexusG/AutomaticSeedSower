/*
  ---------------------------------------------------------------
          Group No.7
  ---------------------------------------------------------------
  project Name  :- Automated Seed Sower
  ---------------------------------------------------------------
  Group members :- 1.Amanshu S. Tiwari
                   2.Antariksh Mohandas
           3.Nishant G. Bangar
           4.Omkar A. Bhilare
           5.Om V. Chaurasia
           6.Saheel S. Patil
           7.Swapnil V. Gore

  ----------------------------------------------------------------
*/


//-------Libraries include in  this program :-------------------

#include <Servo.h>
#include <Keypad.h>
#include <LiquidCrystal.h>                //temporary       

//--------Variables for servo :---------------------------------
Servo myservo;

//--------Syntax for 4*4 keypad:--------------------------------
const byte ROWS = 4;                  // Four rows
const byte COLS = 4;                  // Four columns

char keys[ROWS][COLS] =

{
  //Changing code for proteus simulation(practical syntax in comments )
  {'7', '8', '9', 'A'},               // {'1', '2', '3', 'A'}, 
  {'4', '5', '6', 'B'},               // {'4', '5', '6', 'B'},  
  {'1', '2', '3', 'C'},               // {'7', '8', '9', 'C'},
  {'*', '0', '.', '='}                // {'*', '0', '.', '='}
};


//--------Pins for rows:---------------------------------------
byte rowPins[ROWS] = {5, 6, 7, 8};

//--------Pins for columns:--------------------------------------
byte colPins[COLS] = {9, 10, 11, 12};

//--------Create the Keypad--------------------------------------
Keypad kpd = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );


//--------Lcd  program:------------------------------------------
LiquidCrystal lcd(A0, A1, A2, A3, A4, A5);


//-------Motor Driver:-------------------------------------------
int IN1 = 0 ;                       //Motor 1 +VE
int IN2 = 1 ;                       //Motor 1 -VE
int IN3 = 2 ;                       //Motor 2 +VE
int IN4 = 3 ;                       //Motor 2 -VE

//------Extra Variables for internal and external Actions:-------

//Group of variables for confirming whether printing task has been performed
int a = 0;
int b = 0;
int c = 0;
int d = 0;
int e = 0;

//------Incrementer variable-------------------------------------
int i = 0;

//------Group of variables for calculating  post decimal digits--
int m = 0;
int n = 0;
int o = 0;

//------A variable to run lcd and keypad program only once-------
int p = 0;
int q = 0;                        //to restrict update of x1
int r = 0;                        //for first half cycle
int temp = 0;                       //to check if the half cycles have been completed or not
int s = 0;                        //for second half cycle
int Tc = 0;                       //for total time


//------Four main vaiables:-------------------------------------
//Example for testing purpose
float distance = 0;                     //Distance between two seeds = 20cm
float columns = 0;                          //Length Of column = 200cm
int col = 0;                      //Number of Columns = 4
float distBet = 0;                   //Distance between two columns = 50cm
//Hence total time for one cycle = 29cm

//------Variable to create new millis function------------------
double Treq = 0;                    //Time taken by Lcd and keypad operation in milliseconds
double Nmillis = 0 ;                  //New time variable for post keypad and lcd action
double Ttime = 0;                   //Variable for incrementing Servo Operation**

//------Variables for decimal calculations:--------------------
float decDist = 0;
float decColumns = 0;
float decdistBet = 0;

//------Increment Variable-------------------------------------
float mult = 10;

//------Some Important Variables-------------------------------
float Speed = 20;                    //Assuming Speed of the bot = 20cm/sec
float turn = 1; //(double to float)            //Time taken by bot to take complete 90degree turn(Assuming that right turn time = left turn time)

//------For my code :------------------------------------------
float x = 0;                         //Forward running time of the bot in seconds
float y = 0;                                           //Distance between two seeds in seconds
float u = 0;                                           //Distance between two columns in seconds
float z = 0;                                           //Controlling Variable for odd number of columns
float w = 0 ;                                          //Controlling Variable for even number of columns
float x1 = 0;                      //X1  = x ,variable is used to store X1


void setup() {

  //------Initialising lcd:--------------------------------------
  lcd.begin(16, 2);
  lcd.clear();
  lcd.print("Press * to Start");


  //------Defining pin modes:------------------------------------
  pinMode(4, OUTPUT);                  // Servo motor is connected to pin number 4
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);

  //-----Declaring Servo pin:-----------------------------------
  myservo.attach(4);

}


void loop() {

  if (p == 0) {
    char key = kpd.getKey();
    myservo.write(0);
    if ( (key == '=') && (a == 1) ) {
      i++;
    }

    //Printing Input prompt
    if ( (key == '*') && (i == 0) && (a == 0) ) {
      print("Enter Distance");
      a = 1;
    }
    if ( (key == '=') && (i == 1) ) {
      print("Columns Length");
      b = 1;
    }
    if ( (key == '=') && (b == 1) && (i == 2) ) {
      print("No. of columns");
      c = 1;
    }
    if ( (key == '=') && (c == 1) && (i == 3) ) {
      print("Dist b/w columns");
      d = 1;
    }
    if ( (key == '=') && (i == 4) && (d == 1) ) {
      lcd.clear();
      lcd.print("Data fetched");
      lcd.setCursor(3, 1);
      lcd.print("Thank You!");
      delay(3000);                  //Delay after taking inputs from user
      lcd.clear();
      p = 1;
    }


    //CALCULATING INPUT DATA AND STORING

    //Distance between two seeds :-
    if (key != '*' && key != 'A' && key != 'B' && a == 1) {
      if (key && b == 0 && c == 0) {
        if (key != '.' && m == 0) {
          distance *= 10;
          distance += key - '0';
          distance += decDist;
        }
        if (m >= 1 && key != '.') {
          decDist = ((key - '0') / mult);
          mult *= 10;
          distance += decDist;
        }
        if (key == '.') {
          m++;
        }
        if (m < 2 || key != '.' ) {
          lcd.print(key);
        }
      }
      if (key == 'C') {             //If loop to erase everything
        distance = 0;
        m = 0;
        decDist = 0;
        mult = 10;
        print("Enter Distance");
      }
    }



    //For Calculating Columns length
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
      if (key == 'C') {             //If loop to erase everything
        columns = 0;
        n = 0;
        mult = 10;
        decColumns = 0;
        print("Column Length");
      }
    }

    //For Calculating num
    if (c == 1 && key != 'B' && key != '=' && key != '.') {
      if (key && d == 0) {
        col *= 10;
        col += key - '0';
        lcd.print(key);
      }
      if (key == 'C') {             //If loop to erase everything
        col = 0;
        print("NO. of columns");
      }
    }

    //For calculating distance between two columns
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
      if (key == 'C') {             //If loop to erase everything
        distBet = 0;
        o = 0;
        mult = 10;
        decdistBet = 0;
        print("Distance b/w columns");
      }
    }


    //Thank you
    if (e == 1 && key != 'C' && key != '=') { //**
      lcd.clear();
    }
  }

  //Keypad and lcd code ends here from now on code for servo and motor movement begin :-

  /* p = 1; Treq = 0; */

  if (p == 1) {                                //An if loop for measuring Time required by lcd and keypad action
    Treq = millis();
    p = 2;
  }

if((p == 2)){
  
    //Note that now the new millis is Nmillis   (There is difference of 10 millis in The output )
    Nmillis = ( millis() - Treq)/1000; 

    //Code for running bot in forward direction
    r = col / 2;

    if (col % 2 == 1) { // if no. of columns is odd
      r = r + 1;
      s = r - 1; //the second half cycle will run one less than the no. of times the first half cycle runs
    }

    if (col % 2 == 0) { // if no. of columns is even
      s = r; // the 2nd half cycle will run as many times as 1st half cycle
    }

    if (q == 0) { //to restrict value of x1 from changing after every cycle (x1 should always be orignal x)
      x = columns / Speed;
      x1 = x;
      y = distance / Speed;
      u = distBet / Speed;
      w = x + (2 * turn) + u;
      q++;
    }


    if (temp < r) {
      if ( Nmillis >= 0 && Nmillis <= x ) {
        forward();
      }

      //Code for Servo

      if (Nmillis >= 0 && Nmillis <= x) {
        if (Nmillis == z) {
          myservo.write(90);
        }
        if (Nmillis == (z + 0.250)) {
          myservo.write(0);
          z = z + y;
        }
      } else if (Nmillis > x && Nmillis <= x + (2 * turn) + u) {
        myservo.write(0);
      }


      if (Nmillis >= x && Nmillis <= x + turn) {
        right();
      }

      if (Nmillis >= (x + turn) && Nmillis <= (x + turn) + u) {
        forward();
      }

      if (Nmillis >= ((x + turn) + u) && Nmillis <= x + (2 * turn) + u) {
        right();
      }

      //first half cycle
      if ((temp == s && Nmillis >= x + (2 * turn) + u) || (r == 1 && Nmillis >= x + (2 * turn) + u)) { //if the bot has comleted its no. of 2nd half cycles, then turn off bot at end of first half cycle
        off();
      }



      if (temp < s && Nmillis >= x + (2 * turn) + u) {

        if (Nmillis >= x + (2 * turn) + u && Nmillis <= (x1 + x) + (2 * turn) + u) {
          forward();
        }

        //servo code
        if (Nmillis >= x + (2 * turn) + u && Nmillis <= (x1 + x) + (2 * turn) + u) {
          if (Nmillis == w) {
            myservo.write(90);
          }
          if (Nmillis == (w + 0.250)) {
            myservo.write(0);
            w = w + y;
          }
        }
        else if (Nmillis > (x1 + x) + (2 * turn) + u && Nmillis <= (x1 + x) + (4 * turn) + (2 * u)) {
          myservo.write(0);
        }


        if (Nmillis >= (x1 + x) + (2 * turn) + u && Nmillis <= (x1 + x) + (3 * turn) + u) {
          left();
        }
        if (Nmillis >= (x1 + x) + (3 * turn) + u && Nmillis <= (x1 + x) + (3 * turn) + (2 * u)) {
          forward();
        }
        if (Nmillis >= (x1 + x) + (3 * turn) + (2 * u) && Nmillis <= (x1 + x) + (4 * turn) + (2 * u)) {
          left();
        }
        if (Nmillis == (x1 + x) + (4 * turn) + (2 * u)) { //if bot has completed its whole cycle, then update x and increament temp
          x = (x1 + x + x1) + (4 * turn) + (2 * u);
          temp++;
          if (Tc == 0) {
            Ttime = Nmillis;
            Tc = 1;
          }
          z = Tc * Ttime;
          w = z + (x1 + 2 * turn + u);
          Tc++;
          if (temp == r) {
            off(); // if temp = no. of first half cycles, turn bot off
          }
        }
      }
    }
  }               //IF p == 1 bracket

  // void loop bracket

}


//functions
void print(String text) {
  lcd.clear();
  lcd.print(text);
  lcd.setCursor(0, 1);
  lcd.blink();
}



void forward() {
  digitalWrite(IN1, HIGH );  //Right side motor in forward (Negative speed will be shown)
  digitalWrite(IN2, LOW );
  digitalWrite(IN3, HIGH );  //Left Side motor in forward (Negative Speed will be shown)
  digitalWrite(IN4, LOW );
}

void right() {
  digitalWrite(IN1, LOW);    //right side of motor will run in backward direction
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, HIGH);    //Left side of motor will run in forward direction
  digitalWrite(IN4, LOW);
}

void left() {
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
}

void off  () {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
}

