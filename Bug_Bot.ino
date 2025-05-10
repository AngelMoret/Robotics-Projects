#include <Servo.h>


Servo myServoF;
Servo myServoB;

// Loop Counters
long Readings[7];
int count = 0;


//Servo Var
int fRu = 72;
int fLu = 112;
int bRf = 75;
int bLf = 105;
int center = 90;

//Ultrasonic Sensor Var
const int ultraTrig = 4;
const int ultraEcho = 5;
long duration;
int dist;
int prevDist;
long meanDistance;

//Movement functions

void moveBackward(){
  myServoF.write(fRu);
  myServoB.write(bLf);
  delay(125);

  myServoF.write(center);
  myServoB.write(center);
  delay(65);

  myServoF.write(fLu);
  myServoB.write(bRf);
  delay(125);

  myServoF.write(center);
  myServoB.write(center);
  delay(65);
}

void moveForward(){
  myServoF.write(fRu);
  myServoB.write(bRf);
  delay(125);

  myServoF.write(center);
  myServoB.write(center);
  delay(65);

  myServoF.write(fLu);
  myServoB.write(bLf);
  delay(125);

  myServoF.write(center);
  myServoB.write(center);
  delay(65);
}

void moveBackRight(){
  myServoF.write(fRu);
  myServoB.write(bLf - 6);
  delay(125);

  myServoF.write(center);
  myServoB.write(center - 6);
  delay(65);

  myServoF.write(fLu + 9);
  myServoB.write(bRf - 6);
  delay(125);

  myServoF.write(center);
  myServoB.write(center);
  delay(65);
  
}

void moveTurnRight(){
  myServoF.write(fRu -9);
  myServoB.write(bRf -9);
  delay(125);

  myServoF.write(center -9);
  myServoB.write(center -9);
  delay(65);

  myServoF.write(fLu +5);
  myServoB.write(bLf -9);
  delay(125);

  myServoF.write(center -9);
  myServoB.write(center -9);
  delay(65);
}

long distance(){
  digitalWrite(ultraTrig,LOW);
  delayMicroseconds(2);

  digitalWrite(ultraTrig,HIGH);
  delayMicroseconds(10);
  digitalWrite(ultraTrig,LOW);
  
  duration = pulseIn(ultraEcho,HIGH);
  dist = duration * (0.0343/2);
  return dist;
}

long meanDist(long arr[], int size){
  long sum = 0;
  long mean;
  for (int i = 0; i < size; i++){
    sum += arr[i];
  }
  mean = sum/7;
  return mean;

}


void setup() {

  Serial.begin(9600);

  // Servo Legs
  myServoF.attach(3);
  myServoF.write(center);

  myServoB.attach(2);
  myServoB.write(center);

  delay(1500);

  //Ultrasonic Sensor
  
  pinMode(ultraTrig,OUTPUT);
  pinMode(ultraEcho,INPUT);
  
}

void loop() {
  //Ultrasonic Sensor:
  
  prevDist = dist;
  
  dist = distance();

  // Accuracy improvement

  if (dist > prevDist +100){
    dist = prevDist;
  }

  Readings[count] = dist; 
  meanDistance = meanDist(Readings, 7);



  Serial.print("Distance: ");
  Serial.println(dist);


  Serial.print("Mean Distance: ");
  Serial.println(meanDistance);


  // Servo Legs:
  /*
  if(meanDistance > 1){
    if(meanDistance < 20){
      for( int i = 0; i <= 8; i++){
        moveBackward();
        Serial.print("Move Back");
        delay(150);
      }
      
    }
    else{
      moveForward();
      Serial.print("Move Forward");
      delay(150);
    }

  }
  
*/

  




  count++;
  if (count > 6){
    count = 0;
  }

}
