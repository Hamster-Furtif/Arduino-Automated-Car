 //Renvoie True si la roation est terminée
void rotate(){
  double atg = getAngleToGoal();
  if(!closeTo(angle, atg, maxAngleDeviation)){
    double a = angle + (angle < 0 ? 2*PI : 0);
    atg += (atg < 0 ? 2*PI : 0);
    if(a > atg){
      wheel(LEFT, 0);
      wheel(RIGHT, 80);
    }
    else{
      wheel(LEFT, 80);
      wheel(RIGHT, 0);
    }
    /*Serial.print(angle);
    Serial.print("\t");
    Serial.print(atg);
    Serial.print("\t");
    Serial.println(maxAngleDeviation);*/
  }
  else{
    wheel(LEFT, 0);
    wheel(RIGHT, 0);
    changeState(analysis);
  }
}


void analyze(){
  wheel(RIGHT,0);
  wheel(LEFT, 0);
  if(previous_state != rotation ){
    mid[0] = goal[0];
    mid[1] = goal[1];
  }
  if(distanceToGoal() > 10 or previous_state == rotation){
    double  theta = getAngleToGoal();
    if(closeTo(angle, theta, maxAngleDeviation)){
      getFrontDist();
      if(dist[FR] > 30 && dist[FL] > 30){
        getFrontMid(25);
        changeState(motion_to_goal);
        t_action_begin = millis();
        last_dist = 1000000000;
      }
    }
    else{
      changeState(rotation);
    }
  }
  else{
    changeState(finished);
  }
}

void moveToGoal(){
  unsigned long ti = millis();
  float gyro = IMU.getGyroX_rads();
  
  if(abs(gyro) >= calGyro*1.1 && false){
    if( gyro<0)
      if(spdR < 120)
        spdR++;
       else if(spdL > 100)
        spdL--;
    
    else
      if(spdL < 120)
        spdL++;
       else if(spdR > 100)
        spdR--;
  }

  pos[0] += car_speed*(ti-t_action_begin)*cos(angle)/1000;
  pos[1] += car_speed*(ti-t_action_begin)*sin(angle)/1000;
  double d = distanceToGoal();
  if(d > 10 && d < last_dist){
    wheel(LEFT, spdL);
    wheel(RIGHT, spdR);
    last_dist =d;
    Serial.println(distanceToGoal(), 20);
  }
  else{
    wheel(LEFT, 0);
    wheel(RIGHT, 0);
    changeState(analysis);
  }
  
  t_action_begin = millis();
}

