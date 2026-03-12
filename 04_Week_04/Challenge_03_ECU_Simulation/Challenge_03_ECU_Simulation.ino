int potPin=A2, btn=8, led=3;

void setup() {
  // put your setup code here, to run once:

  Serial.begin(9600);
  pinMode(led, OUTPUT);
  pinMode(potPin, INPUT);
  pinMode(btn, INPUT);

}

int t=millis();
int eng_st=0,pnt=0, btn_st=0, btn_st_prev=0, potVal=0, potVal_prev=0, eng_val=0, val_sign=1;

void loop() {
  btn_st_prev=btn_st;
  btn_st=digitalRead(btn);
  potVal_prev=potVal;
  potVal= analogRead(potPin);

  //BTN PRESS CONTROL
  if(btn_st_prev==HIGH && btn_st==LOW){
    if(eng_st==0){
      eng_st=1;
      Serial.println("Engine in Neutral Gear");
    }
    else if(eng_st==1){
      eng_st=2;
      Serial.println("Engine in First Gear!");
    }
    else if(eng_st==2){
      if(potVal>1000){
        eng_st=3;
        Serial.println("Engine in Reverse Gear!");
      }
      else{
        Serial.println("Not Enough Throttle!");
      }
    }
    else if(eng_st==3){
      
        eng_st=0;
        Serial.println("Engine Turned OFF");
    }
    
  }

  //ENGINE OFF
  if(eng_st==0){
    if(!pnt){
      Serial.println("Engine off");
      pnt=1;
    }
    digitalWrite(led, LOW);
  }

  //ENGINE IDLE
  else if(eng_st==1 && millis()-t>100){
    t =millis();
    if(eng_val<1)val_sign=1;
    else if(eng_val>=250) val_sign=0;

    if(val_sign){
      eng_val+=25;
    }
    else{
      eng_val-=25;
    }
    analogWrite(led, eng_val);
    // Serial.print("Engine brightness value: ");
    // Serial.println(eng_val);
  }

  //FIRST GEAR
  else if(eng_st==2){
    int b=(potVal/1024.0)*255;
    analogWrite(led, b);
    // Serial.print("First Gear | Engine Throttle: ");
    // Serial.print((b/255.0)*100);
    // // Serial.print(b);
    // Serial.println("%");
  }

  //REVERSE GEAR
  else if(eng_st==3){
    int b=(potVal/1024.0)*255;
    analogWrite(led,(255-b));
    // Serial.print("Reverse Gear | Engine Throttle: ");
    // Serial.print(100-((b/255.0)*100));
    // Serial.println("%");
  }
}
