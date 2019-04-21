/*------ Arduino Line Follower with Obstacle Detection and Bluetooth Control via Android app ----- */

/*Libraries*/
#include <LiquidCrystal.h>

/*Initialize LCD*/
LiquidCrystal lcd(A0, A1, A2, A3, A4, A5);

/*-------Defining IR and Ultrasonic Pins------*/
#define LS 2      // Left IR sensor
#define RS 3      // Right IR sensor
#define TrigPin 5  // Trig Ultrasonic sensor
#define EchoPin 4  // Echo Ultrasonic sensor

/*-------Defining Motor Pins------*/
#define E1 10       // Enable Pin for left motor
#define E2 11       // Enable Pin for right motor
#define LM1 12      // left motor
#define LM2 13      // left motor
#define RM1 8       // right motor
#define RM2 9       // right motor

/*-----------Global variables--------*/
double distance = 0;
unsigned long lastmillis = 0;
int count = 0, goToLocation;
bool isFacingEndLoc = 1;

/*-----------Operational parameters--------*/
//Calibration for obstacle distance detection
int stopPoint = 20;  //stop when an obstacle is within 20cm

//Wait 100msec until next sensor check
int sensDelay = 100;

//Find the location on the line
void findLocation(int loc);

//Start tour - wait 3 secs at each checkpoint until last checkpoint is reached.
void startTour(int num);

//Turns the robot 180 degrees until the right sensor is over the line
void rotateToLine ();

//Calculates the value of the distance of the ultrasonic sensor to an obstacle.
int getDistance();

void findStart();

void setup() // The setup routine runs once when you press reset or power on
{
  pinMode(LS, INPUT);
  pinMode(RS, INPUT);

  pinMode(TrigPin, OUTPUT);
  pinMode(EchoPin, INPUT);

  pinMode(E1, OUTPUT);
  pinMode(E2, OUTPUT);

  pinMode(LM1, OUTPUT);
  pinMode(LM2, OUTPUT);
  pinMode(RM1, OUTPUT);
  pinMode(RM2, OUTPUT);

  lcd.begin(16, 2);

  Serial.begin(9600);

  delay (1000);  // wait 1 sec before going
}

void loop()
{
  analogWrite(E1, 70); // Change speed using PWM via Enable pins (varies from min 0 to max 255)
  analogWrite(E2, 70); // And make both motors run at same speed and slow enough to not miss the line during turns
  
  if (Serial.available() > 0) // Checks if data is coming from the serial port
  {
    goToLocation = Serial.read(); // Reads the data from the serial port
  }
  if (1 <= goToLocation && goToLocation <= 4) //moves to the specific locations on the line
  {
    findLocation(goToLocation);
  }
  if (goToLocation == 5) //moves to last checkpoint, pausing at each checkpoint and then returns to starting point.
  {
    startTour(goToLocation);
  }
  if (goToLocation == 6) //stops the robot at any time
  {
    stopRobot();
  }
  if (goToLocation == 7) //returns the robot back to the starting point
  {
    findStart();
  }
  if (goToLocation == 8) //resets the counter to zero
  {
    count = 0;
  }
  else
  {
    stopRobot();
  }
}  // end of main loop

void findLocation(int loc)
{
  bool increment = counterMode(loc); //determines if the current count is higher or lower than the selected location
  bool isOnCheckpoint = false; //initialised to false
  
  if (isFacingEndLoc != increment)  //initialised bool isFacingEndLoc = 1
  {
    rotateToLine();
    isFacingEndLoc = increment;
  }
  if (digitalRead(LS) && digitalRead(RS))
  {
    isOnCheckpoint = true;
  }
  
  do
  {
    if (Serial.available())
    {
      goToLocation = Serial.read();
      break;
    }

    distance = getDistance();

    if (distance >= stopPoint || distance <= 0)
    {
      followLine();
      if (count == loc)
      {
        stopRobot ();
        printToLCD(count);
        break;
      }
      if (digitalRead(LS) && digitalRead(RS))     // stop robot if both IR sensors over black line
      {
        if (millis() - lastmillis > 1000) // Increments the counter only once and keeps the robot moving until both sensors are no longer over checkpoint line.
        {                                 // The time to move between checkpoints must be higher than 1000 ms.
          if (isOnCheckpoint == true)
          {
            isOnCheckpoint = false;
          }
          if (isOnCheckpoint == false)
          {
            if (increment == true)
            {
              count++;
            }
            if (increment == false)
            {
              count--;
            }
          }
        }
        else
        {
          followLine();
        }
        lastmillis = millis();
      }
    }
    else
    {
      stopRobot();
    }
  } while (goToLocation == loc);
}

void findStart()
{
  while (count==1)
  {  
    stopRobot();
    if (Serial.available())
    {
      goToLocation = Serial.read();
      break;
    }
  }
  
  rotateToLine ();
  
  do
  {
    if (Serial.available())
    {
      goToLocation = Serial.read();
      break;
    }

        distance = getDistance();
        
        if (distance >= stopPoint || distance <= 0)
        {
          followLine();
          if (digitalRead(LS) && digitalRead(RS))     // Stop robot if both IR sensors over black line
          {
            if(millis()  - lastmillis > 1000) // Decrements the counter only once and keeps the robot moving until both sensors are no longer over checkpoint.
            {                                 // The time to move between checkpoints must be higher than 1000 ms.
              count--;
              if(count == 1)
              {
                stopRobot ();
                printToLCD(count);
              }
            }
            else
            {
              followLine();
            }
          lastmillis = millis();
         }
        }
      else
      {
        stopRobot();
      }
    } while (count != 1);
}

void startTour(int num)
{
  do
  {
    if (Serial.available())
      goToLocation = Serial.read();
    
    if (count >= 4) //the robot stops indefinitely when it has reached checkpoint 4.
    {
      stopRobot ();
    }
    
    distance = getDistance();
    
    if (distance >= stopPoint || distance <= 0)
    {
      followLine();
      if (digitalRead(LS) && digitalRead(RS))     // stop robot if both IR sensors over black line
      {
        if (millis()  - lastmillis > 1000) // Increments the counter only once and keeps the robot moving until both sensors are no longer over checkpoint line.
        {                                  // The time to move between checkpoints must be higher than 1000 ms.
          count++;
          
          if (1 <= count && count <= 4) //There are 4 checkpoints in all. The 4th checkpoint is the last stop.
          {
            stopRobot ();
            printToLCD(count);
          }
        }
        else
        {
          followLine();
        }
        lastmillis = millis();
      }
    }
    else
    {
      stopRobot();
    }
  } while (goToLocation == num);
}

int getDistance() {

  int duration, distance;

  digitalWrite(TrigPin, LOW);
  delayMicroseconds(2);

  //send 10 micro second pulse to trigger
  digitalWrite(TrigPin, HIGH);
  delayMicroseconds(10); // Added this line per spec (spec says at least 10us)
  digitalWrite(TrigPin, LOW);

  //Below step wait for HIGH upto a second (default) on the Echo pin before timing out.
  duration = pulseIn(EchoPin, HIGH);   //wait for HIGH

  //Calculate the distance in cm
  distance = (duration / 2) * 0.0343; //Speed of sound in cm/us to easily calculate distance in cm based on time received from Echo pin

  //Ignore distance of more than 100cm
  if (distance >= 100 || distance <= 0) {
    return 0;
  } else {
    return distance;
  }
}

void goForward ()
{
  digitalWrite(LM1, HIGH);
  digitalWrite(LM2, LOW);
  digitalWrite(RM1, HIGH);
  digitalWrite(RM2, LOW);
}

void turnRight ()
{
  digitalWrite(LM1, LOW);
  digitalWrite(LM2, LOW);
  digitalWrite(RM1, HIGH);
  digitalWrite(RM2, LOW);
}

void turnLeft ()
{
  digitalWrite(LM1, HIGH);
  digitalWrite(LM2, LOW);
  digitalWrite(RM1, LOW);
  digitalWrite(RM2, LOW);
}

void stopRobot ()
{
  digitalWrite(LM1, LOW);
  digitalWrite(LM2, LOW);
  digitalWrite(RM1, LOW);
  digitalWrite(RM2, LOW);
}

void goBackward ()
{
  digitalWrite(LM1, LOW);
  digitalWrite(LM2, HIGH);
  digitalWrite(RM1, LOW);
  digitalWrite(RM2, HIGH);
}

void rotate () // rotate on spot clockwise
{
  digitalWrite(LM1, LOW);
  digitalWrite(LM2, HIGH);
  digitalWrite(RM1, HIGH);
  digitalWrite(RM2, LOW);
}

void rotateToLine () // rotate robot 180 degrees - until right sensor goes over the line and then stops.
{
  analogWrite(E1, 45); // Change speed using PWM via Enable pins (varies from min 0 to max 255)
  analogWrite(E2, 55); // And make both motors run at same speed and slow enough to not miss the line during turns
  rotate();
  delay(1000);
  
  do
  {
    analogWrite(E1, 45); // Change speed using PWM via Enable pins (varies from min 0 to max 255)
    analogWrite(E2, 55); // And make both motors run at same speed and slow enough to not miss the line during turns
    rotate();
  } while (!digitalRead(RS));    // stop rotating when right IR sensor over black line
  stopRobot();
  delay(1000);
  analogWrite(E1, 70); // Change speed using PWM via Enable pins (varies from min 0 to max 255)
  analogWrite(E2, 70); // And make both motors run at same speed and slow enough to not miss the line during turns.
}

void printToLCD(int a) { //prints the current location on the LCD
  lcd.display();
  lcd.setCursor(0, 0);
  lcd.print("Location");
  lcd.setCursor(9, 0);
  lcd.print(a);
  delay(3000);
  lcd.noDisplay();
}

void followLine()
{
  if (!(digitalRead(LS)) && !(digitalRead(RS))) // Move robot forward if both sensors not on black line
  {
    goForward ();
  }
  else if (!(digitalRead(LS)) && digitalRead(RS))    // Turn right for robot to follow black line
  {
    turnRight ();
  }
  else if (digitalRead(LS) && !(digitalRead(RS)))    // Turn left for robot to follow black line
  {
    turnLeft ();
  }
}

bool counterMode(int loc)
{
  bool increment;
  if(count == loc)
  {
    increment = isFacingEndLoc; //initialised bool isFacingEndLoc = 1
  }
  if (count > loc)
  {
    increment = false;
  }
  if (count < loc)
  {
    increment = true;
  }
  return increment;
}


