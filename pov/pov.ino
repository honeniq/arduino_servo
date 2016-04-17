
#include <Servo.h>

const int UP    = 2;  //pin No.
const int DOWN  = 3;
const int LEFT  = 4;
const int RIGHT = 5;

const int MINH = 20;
const int MAXH = 160;
const int MINV = 20;
const int MAXV = 160;

const int CYCLE = 50;  // 何ミリ秒に1回判定するか


Servo servoH;  // create servo object to control a servo
Servo servoV;  // create servo object to control a servo

void setup() {
  Serial.begin(9600);

  // Initialize Servo
  servoH.attach(9);  // pin9  => Horizontal
  servoV.attach(10); // pin10 => Vertical
  servoH.write(90);
  servoV.write(90);

  // Initialize Button
  pinMode(UP, INPUT_PULLUP);
  pinMode(DOWN, INPUT_PULLUP);
  pinMode(LEFT, INPUT_PULLUP);
  pinMode(RIGHT, INPUT_PULLUP);
}


void loop() {
  int dir = 5;

  delay(CYCLE);

  dir = button();
  Serial.println(dir);
  control(dir);

}


int control(int dir) {
  int h = servoH.read();
  int v = servoV.read();
  int ratio = 1; 

  switch(dir) {
    case 1: h -= ratio; v-= ratio; break;  
    case 2:             v-= ratio; break;  
    case 3: h += ratio; v-= ratio; break;  
    case 4: h -= ratio;            break;  
    case 5:                        break;  
    case 6: h += ratio;            break;  
    case 7: h -= ratio; v+= ratio; break;  
    case 8:             v+= ratio; break;  
    case 9: h += ratio; v+= ratio; break;  
  }
 
  Serial.print(h);
  Serial.println(v);

  if (h <= MAXH && h >= MINH) {
    servoH.write(h);
  } else {
    Serial.print("Limit reached!!");
  }

  if (v <= MAXV && v >= MINV) {
    servoV.write(v);
    Serial.print("Limit reached!!");
  }
}


int button() {
  // 
  // 7  8  9
  // 4     6
  // 1  2  3
  // 

  int up, down, left, right;
  int dir = 0;

  up    = digitalRead(UP);
  down  = digitalRead(DOWN);
  left  = digitalRead(LEFT);
  right = digitalRead(RIGHT);
  
  // 次のswitchで判定できる形に変える
  //   up down left right の順になるように
  dir = (up << 3) + (down << 2) + (left << 1) + right;

  switch(dir) {
    case B1001: return 1;
    case B1011: return 2;
    case B1010: return 3;
    case B1101: return 4;
    case B1111: return 5;
    case B1110: return 6;
    case B0101: return 7;
    case B0111: return 8;
    case B0110: return 9;
    default:    return 5;
  }
}
