#include <Sparki.h>  // include the robot library

void setup() {
  sparki.servo(SERVO_CENTER); // center the servo
}

int program = true;
void loop() {
  
  //Scan for IR Receiver
  int code = sparki.readIR();
  
   // if there is a valid remote button press
  if(code != -1){
    sparki.moveStop(); // stop the motor
    sparki.RGB(RGB_OFF); // clear the RGB
    program = false; // turn off the starter program
  } 
  
  switch(code){
    case 70: sparki.moveForward(); break;
    case 21: sparki.moveBackward(); break;
    case 67: sparki.moveRight(); break;
    case 71: sparki.moveRight(); break;
    case 68: sparki.moveLeft(); break;
    case 69: sparki.moveLeft(); break;
    case 64: sparki.moveStop();
             sparki.gripperStop(); break;      

    // Gripper Buttons
    case 9:  sparki.gripperOpen(); break;
    case 7:  sparki.gripperClose(); break;

    // RGB
    case 25: sparki.RGB(RGB_OFF); break;
    case 12: sparki.RGB(RGB_RED); break;
    case 24: sparki.RGB(RGB_GREEN); break;
    case 94: sparki.RGB(RGB_BLUE); break;

    // Servo
    case 90: sparki.servo(SERVO_LEFT); break;
    case 28: sparki.servo(SERVO_CENTER); break;
    case 8: sparki.servo(SERVO_RIGHT); break;

    // buzzer
    case 74: sparki.beep(); break;
    
    // Program Control
    case 66:  
      sparki.moveStop();
      sparki.RGB(0,0,0);
      program = false; break;
    case 82:  
      program = true; break;
  }  
  
  // Run Autonomy Code if
  if(program == true){
    sparki.moveForward();
    sparki.RGB(RGB_GREEN);
    int cm = sparki.ping(); // measures the distance with Sparki's eyes
        
    if(cm != -1) // make sure its not too close or too far
    { 
        if(cm < 20) // if the distance measured is less than 20 centimeters
        {
            sparki.RGB(RGB_RED); // turn the led red
            sparki.beep(); // beep!
            sparki.moveBackward(10); // move sparki backwards
            sparki.moveRight(30);
        }
    }
    
  int edgeLeft   = sparki.edgeLeft();   // measure the left edge IR sensor
  int edgeRight  = sparki.edgeRight();  // measure the right edge IR sensor
  
  int threshold = 200; // if below this value, no surface underneath
  
  if (edgeLeft < threshold) // if no surface underneath left sensor
  {
    sparki.moveBackward(5);
    sparki.moveRight(20); // turn right
  }

  if (edgeRight < threshold) // if no surface underneath right sensor
  {
    sparki.moveBackward(5);
    sparki.moveLeft(20); // turn left
  }     
    
    delay(100); // wait 0.1 seconds (100 milliseconds)
  }
}