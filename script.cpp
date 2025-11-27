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
    // join I2C bus (I2Cdev library doesn't do this automatically)
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
    
    delay(1000);
    Serial.println("     ");
    getSensor_Data();

    
    delay(3000);
    Serial.println("Calibration starting... Please hold still for 4 seconds");
    delay(1000);
    Serial.println("Calibration starting... Please hold still for 3 seconds");
    delay(1000);
    Serial.println("Calibration starting... Please hold still for 2 seconds");
    delay(1000);
    Serial.println("Calibration starting... Please hold still for 1 seconds");
    delay(1000);
    BaseSetxyz[0] = Axyz[0];
    BaseSetxyz[1] = Axyz[1];
    BaseSetxyz[2] = Axyz[2];
  
    Serial.println(BaseSetxyz[0]);
    Serial.println(BaseSetxyz[1]);
    Serial.println(BaseSetxyz[2]);
    Serial.println();
    delay(4000);
}
 
void loop() {
    //get data
    getSensor_Data();
    //print data
    int Xvalue = 0;
    int Yvalue = 0;
    
    Xvalue = (BaseSetxyz[0]-Axyz[0])*100;
    Yvalue = (BaseSetxyz[1]-Axyz[1])*100;
    InclineX = map(Xvalue, -150, 150, 0, 180);
    InclineY = map(Yvalue, -150, 150, 0, 180);
    Serial.print (InclineX);
    Serial.print(",");
    Serial.print (InclineY);

    ServoX.write(InclineX);
    ServoY.write(InclineY);
    
    /*Serial.print((BaseSetxyz[0]-Axyz[0]));
    Serial.print(",");
    Serial.print(BaseSetxyz[1]-Axyz[1]);
    Serial.print(",");
    Serial.println(BaseSetxyz[2]-Axyz[2]);
    */Serial.println();
    
    delay(5);
}
 
 
void getSensor_Data(void) { 
    accelgyro.getAcceleration(&ax, &ay, &az); //store measures into ax ay az
    //map values of acceleration into Axyz vector (array)
    Axyz[0] = (double) ax / 16384; // range from -2 to 2 ?
    Axyz[1] = (double) ay / 16384;
    Axyz[2] = (double) az / 16384;

}
