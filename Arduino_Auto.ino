// Basic demo for accelerometer readings from Adafruit MPU6050
#define BLYNK_TEMPLATE_ID           "TMPL2igSWEv0z"
#define BLYNK_TEMPLATE_NAME         "Quickstart Device"
#define BLYNK_AUTH_TOKEN            "4a80gtBmqu1YbQ10mDbAVDO1LK5C2Tj9"

#define BLYNK_PRINT Serial

const int DIR = 12;
const int STEP = 14;
const int steps_per_rev = 200;

#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>
#include <Wire.h>
#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>


/*************************************************************

  This is a simple demo of sending and receiving some data.
  Be sure to check out other examples!
 *************************************************************/

/* Fill-in information from Blynk Device Info here */

/* Comment this out to disable prints and save space */



// Your WiFi credentials.
// Set password to "" for open networks.
//char ssid[] = "Teste Pic";
//char pass[] = "agoravai";

char ssid[] = "S23NET5234";
char pass[] = "MORREUFESPRAGA";



BlynkTimer timer;

// This function is called every time the Virtual Pin 0 state changes
BLYNK_WRITE(V4)
{
  digitalWrite(DIR, HIGH);
  Serial.println("Spinning Clockwise...");

  for (int i = 0; i < steps_per_rev; i++)
  {
    digitalWrite(STEP, HIGH);
    delayMicroseconds(10000);
    digitalWrite(STEP, LOW);
    delayMicroseconds(10000);
  }
}
BLYNK_WRITE(V5)
{
  digitalWrite(DIR, LOW);
  Serial.println("Spinning Anti-Clockwise...");

  for (int i = 0; i < steps_per_rev; i++)
  {
    digitalWrite(STEP, HIGH);
    delayMicroseconds(10000);
    digitalWrite(STEP, LOW);
    delayMicroseconds(10000);
  }
}

// This function is called every time the device is connected to the Blynk.Cloud
BLYNK_CONNECTED()
{
  // Change Web Link Button message to "Congratulations!"
  Serial.println("CONECTOU");
}

// This function sends Arduino's uptime every second to Virtual Pin 2.
void myTimerEvent()
{
  // You can send any value at any time.
  // Please don't send more that 10 values per second.
  Blynk.virtualWrite(V2, millis() / 1000);
}

Adafruit_MPU6050 mpu;

void setup(void)
{
  Serial.begin(115200);
  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);
  //  You can also specify server:
  // Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass, "blynk.cloud", 80);
  // Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass, IPAddress(192,168,1,100), 8080);

  // Setup a function to be called every second
  timer.setInterval(1000L, myTimerEvent);
  pinMode(STEP, OUTPUT);
  pinMode(DIR, OUTPUT);
  while (!Serial)
    delay(10); // will pause Zero, Leonardo, etc until serial console opens

  Serial.println("Adafruit MPU6050 test!");

  // Try to initialize!
  if (!mpu.begin())
  {
    Serial.println("Failed to find MPU6050 chip");
    while (1)
    {
      delay(10);
    }
  }
  Serial.println("MPU6050 Found!");

  mpu.setAccelerometerRange(MPU6050_RANGE_8_G);

  mpu.setGyroRange(MPU6050_RANGE_500_DEG);

  mpu.setFilterBandwidth(MPU6050_BAND_21_HZ);

  mpu.setAccelerometerRange(MPU6050_RANGE_8_G);
  Serial.print("Accelerometer range set to: ");

  Serial.println("");
  delay(100);
}
// void balance(a, g, temp){

// if(g.acceleration.x>0){
//  digitalWrite(DIR, LOW);
// for (int i = 0; i < steps_per_rev; i++)
//{
// digitalWrite(STEP, HIGH);
// delayMicroseconds(5000);
// digitalWrite(STEP, LOW);
//  delayMicroseconds(5000);
//}
//}else if(g.acceleration.x<-2){
// digitalWrite(DIR, HIGH);
// for (int i = 0; i < steps_per_rev; i++)
//{
// digitalWrite(STEP, HIGH);
// delayMicroseconds(5000);
// digitalWrite(STEP, LOW);
// delayMicroseconds(5000);
//}
//}
//}
void loop()
{

  /* Get new sensor events with the readings */
  sensors_event_t a, g, temp;
  mpu.getEvent(&a, &g, &temp);

  Serial.print("pos X: ");
  Serial.print(a.acceleration.x);
  Serial.println("");
  Serial.print("pos z: ");
  Serial.print(a.acceleration.z);
  Serial.println("");
  Serial.print("pos y: ");
  Serial.print(a.acceleration.y);
  Serial.println("");

  // balance();

  //if (a.acceleration.z < -2)
  //{
   // digitalWrite(DIR, LOW);
   // digitalWrite(STEP, HIGH);
   // delayMicroseconds(10000);
   // digitalWrite(STEP, LOW);

  //}
  //else if (a.acceleration.z > 2)
  //{
   // digitalWrite(DIR, HIGH);
   // digitalWrite(STEP, HIGH);
    //delayMicroseconds(10000);
   // digitalWrite(STEP, LOW);

  //}

  Blynk.run();
  timer.run();
}