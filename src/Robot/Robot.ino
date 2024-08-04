#include <L298NX2.h>
#include <HCSR04.h>

// Pin definition
const unsigned int EN_A = 6;
const unsigned int IN1_A = 5;
const unsigned int IN2_A = 4;

const unsigned int IN1_B = 3;
const unsigned int IN2_B = 2;
const unsigned int EN_B = 11;

const unsigned int Trig = 10;
const unsigned int Echo = 9;

const unsigned int CNY = A3;
int count = 0;
int threshold = 20;

HCSR04 hc(Trig, Echo); //initialisation class HCSR04 (trig pin , echo pin)

// Initialize both motors
L298NX2 motors(EN_A, IN1_A, IN2_A, EN_B, IN1_B, IN2_B);

const unsigned int min_distance = 7;

void setup()
{
  // Used to display information
  Serial.begin(9600);

  pinMode(CNY, INPUT); // Configure CNY pin as INPUT
  // Set initial speed for both motors
  motors.setSpeed(255);
  delay(3000);
}

void loop()
{
  // Tell both motors to go forward (may depend by your wiring)
  int color = analogRead(CNY);  // Read value CNY70
  Serial.print(color);
  if (color < threshold) {   // Black line

    motors.setSpeedA(255);
    motors.setSpeedB(50);
    motors.backward();
    delay(3000);
    
  } else {

    int distance = hc.dist();
    Serial.print(distance);
    if (distance < min_distance && distance > 0) {

      count++;
      if (count > 50) {
        motors.setSpeedA(255);
        motors.setSpeedB(90);
        delay(5000);
        motors.setSpeedA(90);
        motors.setSpeedB(255);
        delay(5000);
        motors.setSpeedA(255);
        count = 0;
      } else if (distance > min_distance)
        motors.setSpeed(255);
    }
 
    motors.forward();
  }

  delay(60);
}
