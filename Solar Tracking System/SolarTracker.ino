int TL_sensor;
int TR_sensor;
int BR_sensor;
int BL_sensor;

int top = 9;           //Defining the pulse with modulation pin (i.e., Output) for geared motor rotation
int bottom = 10;       //Defining the pulse with modulation pin (i.e., Output) for geared motor rotation

int left = 5;          //Defining the pulse with modulation pin (i.e., Output) for geared motor rotation
int right = 6;         //Defining the pulse with modulation pin (i.e., Output) for geared motor rotation

int power = 200;       //Initializing the Power for the motor rotation
int no = 0;            //Defining the power value
float deadband = 15;   //Setting deadband value to minimize the jitter 

int power_right = 0;     //Initializing the value for auto east rotation
int power_left = 0;      //Initializing the value for auto east rotation

void setup(){
  Serial.begin(9600);
  pinMode(top, OUTPUT);   //Initializing Output pin for geared motor
  pinMode(bottom, OUTPUT);  //Initializing Output pin for geared motor
  pinMode(left, OUTPUT);     //Initializing Output pin for geared motor
  pinMode(right, OUTPUT);      //Initializing Output pin for geared motor
}

void loop(){
  TL_sensor = analogRead(A0);    //Input pin for top left ldr
  TR_sensor = analogRead(A1);     //Input pin for top right sensor
  BR_sensor = analogRead(A2);     //Input pin for bottom right sensor
  BL_sensor  = analogRead(A3);      //Input pin for bottom left sensor
  
  Serial.print("Top Left = ");
  Serial.println(TL_sensor);        // Printing the value stored in top left containeer
  
  Serial.print("Top Right = ");
  Serial.println(TR_sensor);        // Printing the value stored in top right containeer

  
  Serial.print("Bottom Right = ");
  Serial.println(BR_sensor);        // Printing the value stored in bottom right containeer

  
  Serial.print("Bottom Left = ");
  Serial.println(BL_sensor);        // Printing the value stored in bottom left containeer

  Serial.print("power_right: ");
  Serial.print(power_right);       // Printing the value stored in power right

  Serial.println();
  Serial.println();

 
/*From this part all the values that is stored in the respective LDR containeer
is compared and according to the value motor is rotated*/
  
  if (TR_sensor > TL_sensor + deadband)
  {
    analogWrite(right,power);
    analogWrite(left,no);
    analogWrite(top,no);
    analogWrite(bottom,no);
   power_right = power_right -1;
  }
  else if (BR_sensor > BL_sensor + deadband)
  {
    analogWrite(right,power);
    analogWrite(left,no);
    analogWrite(top,no);
    analogWrite(bottom,no);
    power_right = power_right -1;
  }
  else if (TL_sensor > TR_sensor + deadband)
  {
  analogWrite(left,power);
  analogWrite(right,no);
  analogWrite(top,no);
  analogWrite(bottom,no);
  power_right = power_right + 1;
  }
  else if (BL_sensor > BR_sensor + deadband)
  {
  analogWrite(left,power);
  analogWrite(right,no);
  analogWrite(top,no);
  analogWrite(bottom,no);
  power_right = power_right + 1;
  }



  else if (TL_sensor > BL_sensor + deadband)
  {
    analogWrite(top, power);
    analogWrite(bottom,no);
    analogWrite(right,no);
    analogWrite(left,no);
      
  }
  else if (TR_sensor > BR_sensor + deadband)
  {
    analogWrite(top, power);
    analogWrite(bottom,no);
    analogWrite(right,no);
    analogWrite(left,no); 
  }
  else if (BL_sensor > TL_sensor + deadband)
  {
    analogWrite(bottom, power);
    analogWrite(top,no);
    analogWrite(right,no);
    analogWrite(left,no);
  }
  else if (BR_sensor > TR_sensor + deadband)
  {
    analogWrite(bottom, power);
    analogWrite(top,no);
    analogWrite(right,no);
    analogWrite(left,no);
  }
  else
  {
    analogWrite(top,no);
    analogWrite(bottom,no);
    analogWrite(right,no);
    analogWrite(left,no);
  }
  if (BR_sensor < 5 && TR_sensor < 5 && power_right > 1)   //Comparing the value that is generated while moving from east to west, and then auto tilting the
  //solar panels to the east direction at the evening time
  {
    analogWrite(right,power);
    analogWrite(left,no);
    analogWrite(top,no);
    analogWrite(bottom,no);
    power_right = power_right -1;
  }
  delay(1000);
}
