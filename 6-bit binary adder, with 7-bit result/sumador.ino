void setup() {
  // put your setup code here, to run once:
  for(byte i = 0;i<12;i=i+1)pinMode(i, INPUT);
  for(byte i = 12;i<=18;i=i+1)pinMode(i, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly: h = digitalRead(H);
  byte o = 7,r=12;
  bool c = LOW;
  
  for(byte i = 0;i<7;i++){
     digitalWrite(r, LOW);
    if(o && c && i){
      digitalWrite(r,HIGH);
      c = HIGH;
    }
    else if((o && i)||(i && c)||(c && o)){
      digitalWrite(r,HIGH);
      c = LOW;
    }
    else if(o || i || c){
      digitalWrite(r,HIGH);
      c = LOW;
    }
    o+=1;
    r+=1;
  }
}
