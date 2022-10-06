#include <Wire.h>
#include <LiquidCrystal_I2C.h>    
LiquidCrystal_I2C lcd(0x27, 16, 2);
#define ph_sensor A1
float ph_value,sensor_value=0;


int sensorPin = A0;
float volt;
float ntu;

void setup()
{
  Serial.begin(9600);
  pinMode(11,OUTPUT);
  pinMode(8,OUTPUT);
  Serial.begin(9600);
  lcd.init(); // initialize the lcd
  lcd.backlight();
}

void loop()
{

  volt = 0;
  for (int i = 0; i < 800; i++)
  {
    volt += ((float)analogRead(sensorPin) / 1023) * 5;
  }
  volt = volt / 800;
  volt = round_to_dp(volt, 2);
  if (volt < 2.5) {
    ntu = 3000;
    digitalWrite(11,HIGH);
  } else {
    digitalWrite(11,LOW);
    ntu = -1120.4 * square(volt) + 5742.3 * volt - 4353.8;
  }
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(volt);
  Serial.println(volt);
  lcd.print(" V");

//  lcd.setCursor(0, 1);
//  lcd.print(ntu);
//  Serial.println(ntu);

  lcd.print(" NTU");
  delay(10);

  //
  ph_value=analogRead(ph_sensor);
  sensor_value=(ph_value-200)/35;
  Serial.print("\n ph_value=");
  Serial.print(sensor_value);
   lcd.setCursor(0, 1);
   lcd.print("pH : ");
  lcd.print(sensor_value);
  delay(1000);

  //rel
  if (sensor_value < 3) {
    digitalWrite(8,HIGH);
  } 
  else {
    digitalWrite(8,LOW);
  }
  


}

float round_to_dp( float in_value, int decimal_place )
{
  float multiplier = powf( 10.0f, decimal_place );
  in_value = roundf( in_value * multiplier ) / multiplier;
  return in_value;
}
