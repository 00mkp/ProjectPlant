#include <DHT.h>
#include <LiquidCrystal.h>

#define DHTTYPE DHT11
#define DHT11PIN 36
#define waterLevelSensorPower 48
#define waterLevelSensorPin A15
#define waterLevelPinRed 22
#define waterLevelPinBlue 26
#define waterLevelPinGreen 24

//set up pins for rgb led for temp sensor

int waterLevelVal = 0;

DHT dht(DHT11PIN, DHTTYPE);

LiquidCrystal lcd(7, 8, 9, 10, 11, 12);   

void setup()
{ 
  lcd.begin(16, 2);   
  lcd.clear();        
  dht.begin();
  pinMode(waterLevelSensorPower, OUTPUT);
  digitalWrite(waterLevelSensorPower, LOW);
  pinMode(waterLevelPinRed, OUTPUT);
  pinMode(waterLevelPinBlue, OUTPUT);
  pinMode(waterLevelPinGreen, OUTPUT);
  digitalWrite(waterLevelPinRed, LOW);
  digitalWrite(waterLevelPinBlue, LOW);
  digitalWrite(waterLevelPinGreen, LOW);
  Serial.begin(9600);
  delay(1000);        
}
 
void loop()
{
  int chk = dht.read(DHT11PIN);
  lcd.setCursor(0, 0); 
  lcd.print((float)dht.readHumidity(), 2);
  lcd.print("% - "); 
    
  lcd.print((float)dht.readTemperature(true), 2);
  lcd.print("F "); 

  // set up temp check BEFORE custom temp input 

  //less than 250 for empty 
  //less than 470 for half 
  //520 is full 

  lcd.setCursor(0, 1);
  int waterLevel = readWaterLevelSensor();
  Serial.println(waterLevel);
  if(waterLevel < 400) {
    digitalWrite(waterLevelPinRed, HIGH);
    digitalWrite(waterLevelPinBlue, LOW);
    digitalWrite(waterLevelPinGreen, LOW);
    lcd.print("Water LVL: EMPTY");
  } else if (waterLevel < 530) {
    digitalWrite(waterLevelPinRed, HIGH);
    digitalWrite(waterLevelPinBlue, LOW);
    digitalWrite(waterLevelPinGreen, HIGH);
    lcd.print("Water LVL: MED");
  } else if (waterLevel >= 530) {
    digitalWrite(waterLevelPinRed, LOW);
    digitalWrite(waterLevelPinBlue, LOW);
    digitalWrite(waterLevelPinGreen, HIGH);
    lcd.print("Water LVL: FULL");
  }
  delay(1000);
  lcd.clear();
}

int readWaterLevelSensor() {
  digitalWrite(waterLevelSensorPower, HIGH);
  delay(10);
  int waterLevelVal = analogRead(waterLevelSensorPin);
  digitalWrite(waterLevelSensorPower, LOW);
  
  return waterLevelVal;
}

