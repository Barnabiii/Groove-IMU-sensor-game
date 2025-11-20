#include "Wire.h"
 
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
 
    delay(1000);
    Serial.println("     ");
 
}
 
void loop() {
    //get data
    getSensor_Data();

    //print data
    Serial.println("Acceleration(g) of X,Y,Z:");
    Serial.print(Axyz[0]);
    Serial.print(",");
    Serial.print(Axyz[1]);
    Serial.print(",");
    Serial.println(Axyz[2]);
 

 
    Serial.println();

    delay(500);
}
 
 
void getSensor_Data(void) { 
    accelgyro.getAcceleration(&ax, &ay, &az); //store measures into ax ay az
    //map values of acceleration into Axyz vector (array)
    Axyz[0] = (double) ax / 16384; // range from -2 to 2 ?
    Axyz[1] = (double) ay / 16384;
    Axyz[2] = (double) az / 16384;

}
