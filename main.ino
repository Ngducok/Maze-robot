
#define AIN1 8
#define AIN2 9
#define BIN1 10
#define BIN2 11

#define S_t 5
#define S_tr 6
#define S_p 7

#define pwmMax 255


void motor(int trai, int phai) {
  trai = constrain(trai, -pwmMax, pwmMax);
  phai = constrain(phai, -pwmMax, pwmMax);
  if (trai >= 0) {
    analogWrite(AIN1, trai);
    digitalWrite(AIN2, LOW);
  } else {
    analogWrite(AIN2, -trai);
    digitalWrite(AIN1, LOW);
  }
  if (phai >= 0) {
    analogWrite(BIN1, phai);
    digitalWrite(BIN2, LOW);
  } else {
    analogWrite(BIN2, -phai);
    digitalWrite(BIN1, LOW);
  }
}

void forward() {
  motor(150, 150);
}
void left() {
  motor(80, 150);
}
void right() {
  motor(150, 80);
}
void stopMotor() {
  motor(0, 0);
}


void setup() {
  Serial.begin(115200);
  pinMode(S_t, INPUT_PULLUP);
  pinMode(S_tr, INPUT_PULLUP);
  pinMode(S_p, INPUT_PULLUP);
  pinMode(AIN1, OUTPUT);
  pinMode(AIN2, OUTPUT);
  pinMode(BIN1, OUTPUT);
  pinMode(BIN2, OUTPUT);
}

void loop() {

  int trai = !readStable(S_t);
  int truoc = !readStable(S_tr);
  int phai = !readStable(S_p);
  int state = (trai << 2) | (truoc << 1) | phai;
  Serial.print("T:");
  Serial.print(trai);
  Serial.print(" | G:");
  Serial.print(truoc);
  Serial.print(" | P:");
  Serial.print(phai);
  Serial.print(" => STATE: ");
  Serial.println(state, BIN);
  switch (state) {
    case 0b000:
    case 0b101:
      forward();
      break;
    case 0b001:
      left();   
      break;
    case 0b100: 
      right(); 
      break;
    case 0b010: 
    case 0b011: 
    case 0b111: 
      left();  
      break;
    case 0b110:
      right();
      break;
    default:
      stopMotor();
      break;
  }
  delay(100);
}
