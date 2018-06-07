#include "MPU9250.h"

/*                 DEFINITION DES PARAMETRES ABSTRAITS                   */

// Position des capteurs dans les tableaux
static int FL = 2;   //Front Left
static int FR = 1;   //Front Right
static int SL = 3;   //Side Left
static int SR = 0;   //Side Right

// Gauche/Droite/Avant/Arrière
int LEFT = 0;
int RIGHT = 1;
int FORWARD = 1;
int BACKWARD = -1;
int STOPPED = 0;

const int motion_to_goal = 0;
const int rotation = 1;
const int follow_boundary  = 2;
const int analysis  = 3;
const int finished = 4;

const String states[5] = {"MtG", "rot", "fb", "anl", "finished"};

int current_state = analysis;       //État actuel
int previous_state = analysis;      //État précédent

/*                 DEFINITIION DES PARAMETRES MATERIELS                 */

//Postion des broches digitales des différents capteurs
int ping[4] = {6, 7, 8, 11};

//Positions des broches digitales du pont L298N
int IN1 = 3;
int IN2 = 4;
int IN3 = 5;
int IN4 = 12;
int ENA = 10;
int ENB = 9;

/*                  VARIABLES PHYSIQUES                              */

//Distances mesurées par les différents capteurs
float dist[4]={0,0,0,0};

double pos[2]; //Position actuelle (x, y)
double angle;  //Angle actuel
double mid[2]; //Position du point médian

//Etat des roues (avant/arrière
int wheelState[2] = {STOPPED, STOPPED};

double breakDist=1;
double maxAngleDeviation=10*PI/180;

//Vitesses des moteurs pour marche avant rectiligne
int spdL = 110;
int spdR = 100;

//vitesse mesurée en mm/s
const int car_speed = 80;

//Dernière distance
double last_dist = 10000000000;

double calGyro = 0;
/////////////////////////////////////////////////////////////////////////////////////////////// 
static double goal[2] = {100,1};                  //Destination finale                     //
///////////////////////////////////////////////////////////////////////////////////////////////
static float toR;

MPU9250 IMU(Wire,0x68);
int status;


unsigned long t;
unsigned long t_action_begin;

void setup() {
  Serial.begin(115200);
  
  // start communication with IMU 
  status = IMU.begin();
  if (status < 0) {
    Serial.println("IMU initialization unsuccessful");
    Serial.println("Check IMU wiring or try cycling power");
    Serial.print("Status: ");
    Serial.println(status);
    while(1);
  }

  initPins();
  initCar();
  //calibrate();
  Serial.print("ANGLE =");
  Serial.println(getAngleToGoal(), 5);
  t = millis(); 
}

void loop() {
  IMU.readSensor();
  unsigned long ti = millis();
  float gyro = IMU.getGyroX_rads(); 
  if(abs(gyro) > 0.5){
    double d = gyro*(ti-t)/1000;
    angle += d;
    while(angle > PI){
      angle -= 2*PI;
    }
    while(angle < -PI){
      angle += 2*PI;
    }
  }

  switch(current_state){
    
    case motion_to_goal:
      moveToGoal();
      break;
      
    case rotation:
      rotate();
      break;

    case follow_boundary:
      break;

    case analysis:
      analyze();
      break;

    case finished:
      analogWrite(LED_BUILTIN, HIGH);
      break;
  }
  
  //printPos();
  t=ti;
}
