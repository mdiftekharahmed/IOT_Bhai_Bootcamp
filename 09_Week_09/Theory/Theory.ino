// Docs by me:
// https://www.notion.so/DHT11-Measure-temperature-humidity-by-DHRUB-SAHA-34b1ad10ea4080a3b698e7003545b7fb?source=copy_link

//========by DHT11 library of Dhrub Saha========

// #include<DHT11.h>

// DHT11 dht11(2);

// void setup() {
//   Serial.begin(9600);
//   // put your setup code here, to run once:

// }

// void loop() {
//   int temp, hum;
//   int result = dht11.readTemperatureHumidity(temp, hum);
//   if(result==0){
//     Serial.print("Temp: ");
//     Serial.print(temp);
//     Serial.print(" °C | Humidity: ");
//     Serial.print(hum);
//     Serial.println(" %");  
//   }
//   else{
//     Serial.println(DHT11::getErrorString(result));
//   }
//   // put your main code here, to run repeatedly:
//   delay(1000);

// }





//=======================by adafruit library==================

#include <DHT.h>
#define DHTPIN 2
#define DHTTYPE DHT11

DHT dht(DHTPIN, DHTTYPE);

void setup(){
  Serial.begin(9600);
  dht.begin();
}

void loop(){
  float hum = dht.readHumidity();
  float temp = dht.readTemperature();

  if(isnan(hum)||isnan(temp)){
    Serial.println("Error reading data from sensor!");
    return ;
  }


  Serial.print("Adafruit: Temp: ");
  Serial.print(temp);
  Serial.print(" °C | Humidity: ");
  Serial.print(hum);
  Serial.println(" %");  
  
}
