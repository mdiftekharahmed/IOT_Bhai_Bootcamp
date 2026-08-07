// // //=======First need info for calibration========
// // // Big Picture (what this code is doing)

// // // You are using an MQ-2 Gas Sensor with an Arduino.

// // // Goal of the code:

// // // Read analog voltage from the sensor
// // // Convert it into a usable electrical value
// // // Estimate sensor resistance in air (RS)
// // // Approximate baseline resistance (R0) in clean air
// // // Print values for calibration/debugging

// // // This is NOT gas concentration yet — it’s just calibration groundwork.

// #define pin A0

// void setup() {
//   // put your setup code here, to run once:
//   Serial.begin(9600);
//   pinMode(pin, INPUT);
// }

// void loop() {
//   // read analog voltage from sensor
//   // convert it into a usable electric value
//   float sensor_volt;
//   float RS_air; // GEt the value of sensor resistance in clean air
//   float R0; //approximate baseline resistance in clean air


//   // sensor_volt → converted voltage from ADC
//   // RS_air → sensor resistance in current air condition
//   // R0 → reference resistance (calibration value in clean air)

//   float sensorValue=0;

//   //get a average data by testing 100 times 
//   for(int i=0;i<100;i++){
//     sensorValue += analogRead(pin);
//   }
//   sensorValue/=100.0;

//   sensor_volt =(sensorValue/ 1024 )*5.0;
// //  Concept: ADC to voltage conversion
// //  Arduino analog read:
// //    Range: 0–1023 (10-bit ADC)
// //    Voltage = (ADC value / 1023) × 5V
// //    So:
// //      0 → 0V
// //      1023 → 5V

//   RS_air = (5.0-sensor_volt) / sensor_volt; //omit *RL


//   // Concept: calibration baseline
//   //   R0 = sensor resistance in clean air
//   //   Datasheet says:
//   //   RS/R0 ≈ 10 in clean air (for MQ-2 approximation)
//   R0 = RS_air / 10.0; //the ratio of rs/r0 is 10 in a clear air

//   Serial.print("sensor volt: ");
//   Serial.print(sensor_volt);
//   Serial.println("V");

//   Serial.print("R0: ");
//   Serial.println(R0);
//   delay(1000);

// }


// // claibration done now check gas:
// // ===============================
// #define G 9
// #define R 8
// #define sen A0
// float R0= 1.40;
// void setup() {
//  Serial.begin(9600);
//  pinMode(G, OUTPUT);
//  pinMode(R, OUTPUT);
//  pinMode(sen, INPUT);

//  digitalWrite(G, HIGH);
// }

// int st = 0, prev_st=1;
// void loop() {
  
//   float sensor_volt;
//   float RS_gas; // Get value of RS in a GAS
//   float ratio; // Get ratio RS_GAS/RS_air
//   int sensorValue = analogRead(sen);
//   sensor_volt=(float)sensorValue/1024*5.0;
//   RS_gas = (5.0-sensor_volt)/sensor_volt; // omit *RL
//   /*-Replace the name "R0" with the value of R0 in the demo of First Test -*/
//   ratio = RS_gas/R0; // ratio = RS/R0
//   /*-----------------------------------------------------------------------*/
//   //  Serial.print("sensor_volt = ");
//   //  Serial.println(sensor_volt);
//   //  Serial.print("RS_ratio = ");
//   //  Serial.println(RS_gas);
//   Serial.print("Rs/R0 = ");
//   Serial.println(ratio);
//   //  Serial.print("\n\n");
//   prev_st=st;
//   if (ratio < 8)st=1;
//   else st=0;
  
//   if(st!=prev_st && st==1){
//     Serial.println("⚠️ Gas detected!");
//     digitalWrite(R, HIGH);
//     digitalWrite(G, LOW);
//   }
//   else if(st!=prev_st && st==0){
//     Serial.println("Air is clean");
//     digitalWrite(G, HIGH);
//     digitalWrite(R, LOW);
//   }
//   delay(1000);
// }


// // claibration done now check gas: (digital Read)
// // ===============================
// #define G 9
// #define R 8
// #define sen 3
// float R0= 1.40;
// void setup() {
//  Serial.begin(9600);
//  pinMode(G, OUTPUT);
//  pinMode(R, OUTPUT);
//  pinMode(sen, INPUT);

//  digitalWrite(G, HIGH);
// }

// int st = 0, prev_st=1;
// void loop() {
//   prev_st=st;
//   st = digitalRead(sen);
//   Serial.print("OUTPUT: ");
//   Serial.println(st);

  
  
 
  
//   if(st!=prev_st && st==1){
//     Serial.println("⚠️ Gas detected!");
//     digitalWrite(R, HIGH);
//     digitalWrite(G, LOW);
//   }
//   else if(st!=prev_st && st==0){
//     Serial.println("Air is clean");
//     digitalWrite(G, HIGH);
//     digitalWrite(R, LOW);
//   }

//   if(!st)digitalWrite(G, HIGH);

//   delay(1000);
// }


void setup() {
  Serial.begin(9600);
  pinMode(3, INPUT);
}

void loop() {
  Serial.println(digitalRead(3));
  delay(500);
}