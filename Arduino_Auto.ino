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


// Credenciais para conexão via wifi
char ssid[] = "NOME_DA_REDE";
char pass[] = "SENHA_DA_REDE";

BlynkTimer timer;

// Gira o motor no sentido horário
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

// Gira o motor no sentido anti-horário
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

// Exibe a mensagem de sucesso na conexão com o blynk
BLYNK_CONNECTED()
{
  Serial.println("CONECTOU");
}

// Envia o tempo de atividade da placa a cada segundo para o pino V2. 
void myTimerEvent()
{
  Blynk.virtualWrite(V2, millis() / 1000);
}

Adafruit_MPU6050 mpu;

void setup(void)
{
  Serial.begin(115200);
  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);

  timer.setInterval(1000L, myTimerEvent);
  pinMode(STEP, OUTPUT);
  pinMode(DIR, OUTPUT);
  while (!Serial)
    delay(10); 

  // Verifica se a MPU está devidamente conectada
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

void loop()
{

  // Obtem os valores da MPU
  sensors_event_t a, g, temp;
  mpu.getEvent(&a, &g, &temp);

  // Imprime os valores lidos pela MPU
  Serial.print("pos X: ");
  Serial.print(a.acceleration.x);
  Serial.println("");
  Serial.print("pos z: ");
  Serial.print(a.acceleration.z);
  Serial.println("");
  Serial.print("pos y: ");
  Serial.print(a.acceleration.y);
  Serial.println("");

  Blynk.run();
  timer.run();
}