#include "Wire.h"
#include <Servo.h>
 
// I2Cdev and MPU9250 must be installed as libraries, or else the .cpp/.h files
// for both classes must be in the include path of your project
#include "MPU9250.h"
 
// class default I2C address is 0x68
// specific I2C addresses may be passed as a parameter here
// AD0 low = 0x68 (default for InvenSense evaluation board)
// AD0 high = 0x69
MPU9250 accelgyro; 
 
int16_t ax, ay, az;
 
float Axyz[3];
float BaseSetxyz[3];

int InclineX = 90;
int InclineY = 90;

Servo ServoX;
Servo ServoY;


void setup() {
    Wire.begin();
 
    // initialize serial communication
    // (38400 chosen because it works as well at 8MHz as it does at 16MHz, but
    // it's really up to you depending on your project)
    Serial.begin(38400);
 
    // initialize device
    Serial.println("Initializing I2C devices...");
    accelgyro.initialize();
 
    // verify connection
    Serial.println("Testing device connections...");
    Serial.println(accelgyro.testConnection() ? "MPU9250 connection successful" : "MPU9250 connection failed");


    ServoX.attach(4);
    ServoY.attach(5);
    
    Calibrating();
}
 
void loop() {
    //get data
    getSensor_Data();
    //print data
    int mesureXY[2];
    mesureXY[0] =  (BaseSetxyz[0]-Axyz[0])*100;
    mesureXY[1] = (BaseSetxyz[1]-Axyz[1])*100;
    
    InclineX = map(mesureXY[0], -150, 150, 0, 180);
    InclineY = map(mesureXY[1], -150, 150, 0, 180);
 
    Serial.print (InclineX);
    Serial.print(",");
    Serial.print (InclineY);
    Serial.println();
 
    ServoX.write(InclineX);
    ServoY.write(InclineY);
    
    delay(5);
}

void Calibrating() {
    Serial.println("     ");
    delay(3000);
    Serial.println("Calibration starting... Please hold still for 3 seconds");
    delay(1000);
    Serial.println("Calibration starting... Please hold still for 2 seconds");
    delay(1000);
    Serial.println("Calibration starting... Please hold still for 1 seconds");
    delay(1000);
 
    getSensor_Data();
    BaseSetxyz[0] = Axyz[0];
    BaseSetxyz[1] = Axyz[1];
    BaseSetxyz[2] = Axyz[2];
  
    Serial.println(BaseSetxyz[0]);
    Serial.println(BaseSetxyz[1]);
    Serial.println(BaseSetxyz[2]);
    Serial.println();
    delay(1000);
}
 
void getSensor_Data(void) { 
    accelgyro.getAcceleration(&ax, &ay, &az); //store measures into ax ay az
    //map values of acceleration into Axyz vector (array)
    Axyz[0] = (double) ax / 16384; // range from -2 to 2 ?
    Axyz[1] = (double) ay / 16384;
    Axyz[2] = (double) az / 16384;

}
