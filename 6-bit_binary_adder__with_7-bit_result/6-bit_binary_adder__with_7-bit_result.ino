void setup() {
  // put your setup code here, to run once:
  for(byte i = 0;i<12;i=i+1)pinMode(i, INPUT);
  for(byte i = 12;i<=18;i=i+1)pinMode(i, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly: h = digitalRead(H);
  byte secondValue = 7,result=12;
  bool carry = LOW;
  for(byte firstValue = 0;firstValue<7;firstValue++){
     digitalWrite(result, LOW);
    if(secondValue && carry && firstValue){
      digitalWrite(result,HIGH);
      carry = HIGH;
    }
    else if((secondValue && firstValue)||(firstValue && carry)||(carry && secondValue)){
      digitalWrite(result,HIGH);
      carry = LOW;
    }
    else if(secondValue || firstValue || carry){
      digitalWrite(result,HIGH);
      carry = LOW;
    }
    secondValue+=1;
    result+=1;
  }
}
