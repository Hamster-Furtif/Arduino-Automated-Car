float getDist(int i){
  pinMode(ping[i], OUTPUT);
  digitalWrite(ping[i],LOW);
  delayMicroseconds(20);
  digitalWrite(ping[i],HIGH);
  delayMicroseconds(100);
  digitalWrite(ping[i],LOW);
  pinMode(ping[i], INPUT);
  float d = pulseIn(ping[i], HIGH)/29.387/2;
  return d;
}

void getFrontDist(){
  dist[FR] = getDist(FR);
  dist[FL] = getDist(FL);
}

