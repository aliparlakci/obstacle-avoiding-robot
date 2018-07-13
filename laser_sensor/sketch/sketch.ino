#include <AFMotor.h>
#include <NewPing.h>
/*
#define trigOn A3
#define echoOn A2

#define trigSol A1
#define echoSol A0

#define trigSag A5
#define echoSag A4
*/
#define laserOn A3
#define laserSol A2
#define laserSag A4

const int hassasiyet = 30;
const int surat = 110;
const int spin = 150;
const int bekle = 250;
const int azami_uzaklik = 200;

AF_DCMotor solMotor(2,MOTOR12_1KHZ);
AF_DCMotor sagMotor(4,MOTOR34_1KHZ);

void setup() {
/*
  pinMode(trigOn, OUTPUT);
  pinMode(echoOn, INPUT);
  pinMode(trigSol, OUTPUT);
  pinMode(echoSol, INPUT);
  pinMode(trigSag, OUTPUT);
  pinMode(echoSag, INPUT);
  */
  pinMode(laserOn,INPUT);
  pinMode(laserSol,INPUT);
  pinMode(laserSag,INPUT);
    Serial.begin(9600);
    delay(2000);
}

void loop() {
  laser();
}
// ----------ULTRASONIC SENSOR KOMUTLARI---------- //
// -------------LASER SENSOR KOMUTLARI------------ //
void laser(){
  if(onSensor() || solSensor() || sagSensor()){
    git(0,0);
    delay(500);
    git(-surat,-surat);
    delay(500);
    don(spin);
    delay(500);
    git(0,0);
    delay(500);
  }else{
    git(surat,surat);
  }
}

boolean solSensor(){
  if(digitalRead(laserSol)){
    return false;
  }else{
    return true;
  }
}

boolean sagSensor(){
  if(digitalRead(laserSag)){
    return false;
  }else{
    return true;
  }
}

boolean onSensor(){
  if(digitalRead(laserOn)){
    return false;
  }else{
    return true;
  }
}
// -------------LASER SENSOR KOMUTLARI------------ //

void git(int sol, int sag){
    if(sol > 255 || sol < -255 || sag > 255 || sag < -255){
    if(sol > 255){sol = 255;}
    if(sol < -255){sol = -255;}
    if(sag > 255){sag = 255;}
    if(sag < -255){sag = -255;}
  }

  if(sol > 0){solMotor.setSpeed(sol);solMotor.run(FORWARD);}
  if(sol < 0){solMotor.setSpeed((-1 * sol));solMotor.run(BACKWARD);}
  if(sol == 0){solMotor.run(RELEASE);}

  if(sag > 0){sagMotor.setSpeed(sag);sagMotor.run(FORWARD);}
  if(sag < 0){sagMotor.setSpeed((-1 * sag));sagMotor.run(BACKWARD);}
  if(sag == 0){sagMotor.run(RELEASE);}
}

void don(int hiz){
  int i = random(0,2);
  if(i == 0){
    git(-hiz,hiz);
  }else{
    git(hiz,-hiz);
  }
}
