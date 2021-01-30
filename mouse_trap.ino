#include <Servo.h> 

#define INTERRUPT_PIN 2
#define GATE_SERVO_PIN 9
#define LOCK_SERVO_PIN 10

Servo gateservo;  // create servo object to control a servo 
Servo lockservo;  // a maximum of eight servo objects can be created 
     
                
int is_open = 0;
int time_count = 0;

void open(){
  lockservo.write(0);
  delay(100);
  gateservo.write(0);
  is_open = 1;
  digitalWrite(LED_BUILTIN, HIGH);
}

void close(){
  gateservo.write(180);
  delay(1000);
  lockservo.write(90);
  delay(1000);
  gateservo.write(160);
  digitalWrite(LED_BUILTIN, LOW);
}

void start_action() {
  if (is_open == 0) {
      open();
  }
}

void setup() 
{ 
  //attachInterrupt(digitalPinToInterrupt(INTERRUPT_PIN), start_action, FALLING); 
  attachInterrupt(digitalPinToInterrupt(INTERRUPT_PIN), start_action, RISING);
  gateservo.attach(GATE_SERVO_PIN);        // attaches the servo on pin 9 to the servo object
  gateservo.write(160);

  lockservo.attach(LOCK_SERVO_PIN);        // attaches the servo on pin 9 to the servo object
  lockservo.write(90);
} 

void loop() 
{
  if (is_open == 1) {
    time_count++;
    if (time_count == 10) {
      close();
    } else if (time_count == 100) {
      is_open = 0;
      time_count = 0;
    }
  } else {
    time_count = 0;
  }
  delay(100);
} 
