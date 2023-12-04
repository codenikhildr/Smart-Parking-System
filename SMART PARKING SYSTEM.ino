//IR SENSOR IN THE PARKING SLOT TO DETECT THE VEHICLE WEATHER PARKED ELSE SLOT IS FREE
int IR1 = 4;  //IR Sensor - 1
int IR1_Value; //variable declaration to hold the IR value
int IR2 = 3;  //IR Sensor - 2
int IR2_Value; //variable declaration to hold the IR value
int IR3 = 5;  //IR Sensor - 3
int IR3_Value; //variable declaration to hold the IR value
int IR4 = 6;  //IR Sensor - 4
int IR4_Value; //variable declaration to hold the IR value

//IR SENSOR TO DETECT THE VEHICLE AT THE GATE AND SEND THE SIGNAL TO THE SERVO MOTOR 
int IR5 = 7;  //IR Sensor - 5
int IR5_Value; //variable declaration to hold the IR value

//Servo Declarations
#include <Servo.h> //Includong header file
Servo myservo;  //Creating Servo Object
int servoPin = 6; //Declaring the servo motor Pin

#include <Wire.h>
#include <LiquidCrystal_I2C.h> 
LiquidCrystal_I2C lcd(0x27,16,2);


void setup() {
  
  //Serial monitor bard rate declarations.
  Serial.begin(9600); //Declared bard rate ===> 9600
  
  myservo.attach(servoPin);
  /*
    Setting the Servo motor to 0 degree.
    Valus for the gate open and close are as follows:
      1. 0 degree gate is closed.
      2. 90 degree gate is opened.
   */
  myservo.write(0);

  //LCD Declarations
  Wire.begin();
  lcd.init();   //Iinitializing LCD          
  lcd.backlight(); //Turning the Backling on in the LCD
  lcd.setCursor(0,0); //Setting Cursor to 0th row oth column.
  lcd.print("SMART PARKING SYS");//Printing the desired output in the LCD
  /*PINMODE DECLARATIONS
    1.sensors which sends the value to the controller will be INPUT or else Actuator 
    2.sensor required signal from the controller  declare the pinmode as OUTPUT
    3.if push button is used the need to declare the pinmode as INPUT_PULLUP
  */
  pinMode(IR1,INPUT);
  pinMode(IR2,INPUT);
  pinMode(IR3,INPUT);
  pinMode(IR4,INPUT);
  pinMode(IR5,INPUT);

}

void loop() {
  // put your main code here, to run repeatedly:
  /*
    Reading all the sensor values and storing it in the respective Variables.
   */
  IR1_Value = digitalRead(IR1);
  IR2_Value = digitalRead(IR2);
  IR3_Value = digitalRead(IR3);
  IR4_Value = digitalRead(IR4);
  IR5_Value = digitalRead(IR5);

  lcd.clear(); //Clearing the LCD Display

 //Checking for the parking slot status and maping the respective output in the LCD for all 4 slots
  if(IR1_Value == 0) //Checking for Slot 1
  {
     lcd.setCursor(0,0);
     lcd.print("SLOT 1 OCCUPIED");
  }
  else
  {
     lcd.setCursor(0,0);
     lcd.print("SLOT 1 VACANT");
  }
  
  if(IR2_Value == 0)//Checking for Slot 2
  {
    lcd.setCursor(0,1);
    lcd.print("SLOT 2 OCCUPIED");
  }
  else
  {
    lcd.setCursor(0,1);
    lcd.print("SLOT 2 VACANT");
  }

  delay(5000); //5 seconds delay to hold the screen

  lcd.clear();
  
  if(IR3_Value == 0) //Checking for Slot 3
  {
    lcd.setCursor(0,1);
    lcd.print("SLOT 3 OCCUPIED");
  }
  else
  {
    lcd.setCursor(0,1);
    lcd.print("SLOT 3 VACANT");
  }

  if(IR4_Value == 0)  //Checking for Slot 4
  {
    lcd.setCursor(0,1);
    lcd.print("SLOT 4 OCCUPIED");
  }
  else
  {
    lcd.setCursor(0,1);
    lcd.print("SLOT 4 VACANT");
  }

  /*
      The IR sensor checks weather vehicle approach near the gate
      If IR detected then it checks for the free parking slots.
      If Free slot detected then the singal is given to the Servo motor to turn open the gate
      once the gate is opened and vehicle enters the parking area gate closes as IR sensor near the gate won't detects vehicle.
   */
  if(IR5_Value == 0 && (IR1_Value == 1 || IR2_Value == 1 || IR3_Value == 1 || IR4_Value == 1))
  {
    myservo.write(90);
    Serial.println("Gates are Open");
  }
  else
  {
     myservo.write(0);
     Serial.println("Gates are Closed");
  }

  delay(5000);
}
