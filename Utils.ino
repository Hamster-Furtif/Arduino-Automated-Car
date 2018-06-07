boolean closeTo(double a, double b, double e){
  return ((a+2*PI<=b+e && a+2*PI >=b-e) || (a<=b+e && a >=b-e) || (a-2*PI<=b+e && a-2*PI >=b-e));
}

void initCar(){
  pos[0] = 0;   //posX
  pos[1] = 0;   //posY
  mid[0] = goal[0];
  mid[1] = goal[1];
  angle = PI/2;
}

void initPins(){
  pinMode(IN1,OUTPUT);
  pinMode(IN2,OUTPUT);
  pinMode(IN3,OUTPUT);
  pinMode(IN4,OUTPUT);
  pinMode(ENA,OUTPUT);
  pinMode(ENB,OUTPUT);
  digitalWrite(IN2, LOW);
  digitalWrite(IN1, HIGH);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
}

void calibrate(){
   for(int i=0; i<1000;i++){
      IMU.readSensor();
      calGyro += abs(IMU.getGyroX_rads());
      delay(10);
  }
  calGyro /= 1000;
}


void notifyStateChange(){
    Serial.print("Switched from ");
    Serial.print(states[previous_state]);
    Serial.print(" to ");
    Serial.println(states[current_state]);
}

void printPos(){
  Serial.println("==========================");
  Serial.print("Angle:");
  Serial.print(angle);
  Serial.print("\tX   ");
  Serial.print(pos[0]);
  Serial.print("\tY   ");
  Serial.print(pos[1]);
  Serial.print("\tState  ");
  Serial.println(states[current_state]);

}
void changeState(int s){
  previous_state = current_state;
  current_state = s;
  notifyStateChange();
}

