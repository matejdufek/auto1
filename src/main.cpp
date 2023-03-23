#include <AFMotor.h>
#include <Arduino.h>
AF_DCMotor m1(1);
AF_DCMotor m2(2);
AF_DCMotor m3(3);
AF_DCMotor m4(4);
int rychlost=0;
int krok=0;
int faze=0;
int zpomalrych=-2;
int vzdalenost=0;
enum {
  VPRED = 0,
  VZAD,
  POSMERU,
  PROTISMERU,
  STOP
};

// Tady se podívej jak to to změním

void setup() {
  Serial.begin(115200);
  // m1.setSpeed(rychlost);m2.setSpeed(rychlost);m3.setSpeed(rychlost);m4.setSpeed(rychlost);
  m1.run(RELEASE);m2.run(RELEASE);m3.run(RELEASE);m4.run(RELEASE);
}
void start(int kam, int okolik, int vzd) {
  switch (kam) {
    case VPRED:
      m1.run (FORWARD);m2.run (FORWARD);m3.run (FORWARD);m4.run (FORWARD); break;
    case VZAD:
      m1.run (BACKWARD);m2.run (BACKWARD);m3.run (BACKWARD);m4.run (BACKWARD); break; // reverse
    case POSMERU:
      m1.run (BACKWARD);m4.run (BACKWARD);m3.run (FORWARD);m2.run (FORWARD); break; // turn cw
    case PROTISMERU:
      m2.run (BACKWARD);m3.run (BACKWARD);m1.run (FORWARD);m4.run (FORWARD); break; // turn ccw
    case STOP:
      m1.run(RELEASE);m2.run(RELEASE);m3.run(RELEASE);m4.run(RELEASE); break;
  }
  faze=okolik;
  zpomalrych=-2*okolik;
  vzdalenost=vzd;
  krok++;
}

void jedem() {
  int nr=-1;
  if (faze>0) {
    if(rychlost<40)
        nr=rychlost=40;
    else if (rychlost>=250) {
        faze=0;
        nr=255;
        Serial.print((String)"+K:"+krok+" sp:"+rychlost+" v:"+vzdalenost+"\n");
    } else {
        rychlost+=faze;
        nr=rychlost;
    }
  } else if (faze==0) {
    if (vzdalenost<=0)
    {
      faze=zpomalrych;
      if (faze==0) krok++;
      Serial.print((String)"0K:"+krok+" sp:"+rychlost+" v:"+vzdalenost+"\n");
    }
    else vzdalenost--;
  } else{
    if(rychlost<40){
        nr=0;
        if (rychlost<8) {
          krok++;
          Serial.print((String)"-K:"+krok+" sp:"+rychlost+" v:"+vzdalenost+"\n");
        }
    } 
    rychlost+=faze;
  }
  if (nr!=-1) {
  m1.setSpeed(nr);m2.setSpeed(nr);m3.setSpeed(nr);m4.setSpeed(nr);
  }
}

const int O90=10;
const int O180=45;
const int O270=99;
const int O360=175;
const int  V1=50;
const int  R1=4;
void loop() {
  delay(10);
  //Serial.print((String)"K:"+krok+" sp:"+rychlost+" v:"+vzdalenost+"\n");
  switch (krok)
  {
 case 0: start(VPRED,R1,V1); break;
  case 1: jedem();break;
  case 2: start(POSMERU,R1,O90); break;
  case 3: jedem();break;
  case 4: start(VPRED,R1,V1); break;
  case 5: jedem();break;
  case 6: start(POSMERU,R1,O90); break;
  case 7: jedem();break;
  case 8: start(VPRED,R1,V1); break;
  case 9: jedem();break;
  case 10: start(STOP,0,100); break;
  case 11: start(PROTISMERU,R1,O90); break;
  case 12: jedem();break;
  case 13: start(VPRED,R1,V1); break;
  case 14: jedem();break;
  case 15: start(PROTISMERU,R1,O90); break;
  case 16: jedem();break;
  case 17: start(VPRED,R1,V1); break;
  case 18: jedem();break;
  case 19: start(PROTISMERU,R1,O90); break;
  case 20: jedem();break;
  case 21: start(STOP,0,400); break;
  case 22: start(VPRED,R1,V1); break;
  case 23: jedem();break;
  case 24: start(PROTISMERU,R1,O90); break;
  case 25: jedem();break;
  case 26: start(VPRED,R1,V1); break;
  case 27: jedem();break;
  case 28: start(POSMERU,R1,O90); break;
  case 29: jedem();break;
  case 30: start(VPRED,R1,V1); break;
  case 31: jedem();break;
  case 32: start(POSMERU,R1,O360+O90);break;
  case 33: jedem();break;
  case 34: krok= 99 ;

  case 99: start(STOP,0,400); break;
  case 100: jedem(); break;
  default:
  krok=0;
    break;
  }
}
