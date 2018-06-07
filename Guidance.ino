double getAngleToGoal(){
  double a = atan((pos[1]-mid[1])/(pos[0]-mid[0]));
  while(a > PI)
      a -= 2*PI;
  while(a < -PI)
      a += 2*PI;
  return a;
}
void getFrontMid(int L){
  mid[0] = pos[0]+L*cos(angle);
  mid[1] = pos[0]+L*sin(angle); 
}

void wheel(int side, int spd){
  if(spd == 0){
    if(side == RIGHT)
      analogWrite(ENA, 0);
    else if(side == LEFT)
      analogWrite(ENB, 0);
    wheelState[side] = STOPPED;
  }
  else if(side == LEFT && spd > 0){
    if(wheelState[LEFT] != FORWARD){
      digitalWrite(IN3, HIGH);
      digitalWrite(IN4, LOW);
      wheelState[LEFT] = FORWARD;
    }
    analogWrite(ENB, spd);
  }
  else if(side == LEFT && spd < 0){
    if(wheelState[LEFT] != BACKWARD){
      digitalWrite(IN3, LOW);
      digitalWrite(IN4, HIGH);
      wheelState[LEFT] = BACKWARD;
    }
    analogWrite(ENB, -spd);
  }
  else if(side == RIGHT && spd > 0){
    if(wheelState[RIGHT] != FORWARD){
      digitalWrite(IN2, HIGH);
      digitalWrite(IN1, LOW);
      wheelState[RIGHT] = FORWARD;
    }
    analogWrite(ENA, spd);
  }
  else if(side = RIGHT && spd < 0){
    if(wheelState[RIGHT] != BACKWARD){
      digitalWrite(IN2, LOW);
      digitalWrite(IN1, HIGH);
      wheelState[RIGHT] = BACKWARD;
    }
    analogWrite(ENA, -spd);
  }
}

double distanceToGoal(){
  return sqrt(sq(mid[0] - pos[0])+sq(mid[1] - pos[1]));
}



