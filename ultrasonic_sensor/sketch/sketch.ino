#include <AFMotor.h>
#include <NewPing.h>

#define trigOn A3
#define echoOn A2

#define trigSol A1
#define echoSol A0

#define trigSag A5
#define echoSag A4

#define laserOn A2
#define laserSol A0
#define laserSag A1

const int hassasiyet = 30;
const int surat = 120;
const int spin = 200;
const int bekle = 250;
const int azami_uzaklik = 200;

AF_DCMotor solMotor(1,MOTOR12_1KHZ);
AF_DCMotor sagMotor(4,MOTOR34_1KHZ);

NewPing sonarOn(trigOn,echoOn,azami_uzaklik);
NewPing sonarSol(trigSol,echoSol,azami_uzaklik);
NewPing sonarSag(trigSag,echoSag,azami_uzaklik);

void setup() {
	pinMode(trigOn, OUTPUT);
	pinMode(echoOn, INPUT);
	pinMode(trigSol, OUTPUT);
	pinMode(echoSol, INPUT);
	pinMode(trigSag, OUTPUT);
	pinMode(echoSag, INPUT);
  	Serial.begin(9600);
  	delay(2000);
}

void loop() {
	sonic();
}
// ----------ULTRASONIC SENSOR KOMUTLARI---------- //
void sonic() {
	if(sonicOn() || sonicSol() || sonicSag()){
    git(0,0);
    delay(250);
    git(-surat,-surat);
    delay(250);
    don(spin);
    delay(1000);
    git(0,0);
    delay(200);
  }else{
    git(surat,surat);
  }
}

boolean sonicSol(){
	long uzaklik, sure;
	delay(70);
	digitalWrite(trigSol, LOW);
	delayMicroseconds(2);
	digitalWrite(trigSol, HIGH);
	delayMicroseconds(10);
	digitalWrite(trigSol, LOW);
	sure = pulseIn(echoSol, HIGH);
	uzaklik = (sure/2) / 29.1;
	/* uzaklik = sonarSol.ping_cm(); */
	if(uzaklik > 0 && uzaklik < hassasiyet){
		return true;
	}else{
		return false;
	}
}

boolean sonicOn(){
	long uzaklik, sure;
	delay(70);
	digitalWrite(trigOn, LOW);
	delayMicroseconds(2);
	digitalWrite(trigOn, HIGH);
	delayMicroseconds(10);
	digitalWrite(trigOn, LOW);
	sure = pulseIn(echoOn, HIGH);
	uzaklik = (sure/2) / 29.1;
	/* uzaklik = sonarOn.ping_cm(); */
	if(uzaklik > 0 && uzaklik < hassasiyet){
		return true;
	}else{
		return false;
	}
}

boolean sonicSag(){
	long uzaklik, sure;
	delay(70);
	digitalWrite(trigSag, LOW);
	delayMicroseconds(2);
	digitalWrite(trigSag, HIGH);
	delayMicroseconds(10);
	digitalWrite(trigSag, LOW);
	sure = pulseIn(echoSag, HIGH);
	uzaklik = (sure/2) / 29.1;
	/* uzaklik = sonarSag.ping_cm(); */
	if(uzaklik > 0 && uzaklik < hassasiyet){
		return true;
	}else{
		return false;
	}
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
		return true;
	}else{
		return false;
	}
}

boolean sagSensor(){
	if(digitalRead(laserSag)){
		return true;
	}else{
		return false;
	}
}

boolean onSensor(){
	if(digitalRead(laserOn)){
		return true;
	}else{
		return false;
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
