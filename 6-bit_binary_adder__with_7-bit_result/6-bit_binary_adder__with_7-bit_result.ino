void setup() {
  // put your setup code here, to run once:
  for(byte i = 0;i<12;i=i+1)pinMode(i, INPUT);
  for(byte i = 12;i<=18;i=i+1)pinMode(i, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly: h = digitalRead(H);
  byte secondValue = 6,result=12;
  bool carry = LOW;
  for(byte firstValue = 0;firstValue<6;firstValue++){
    
    if((digitalRead(secondValue) && carry && digitalRead(firstValue))){
      digitalWrite(result,HIGH);
      carry = HIGH;
    }
    else if((digitalRead(secondValue) && digitalRead(firstValue))||(digitalRead(firstValue) && carry)||(carry && digitalRead(secondValue))){
      digitalWrite(result,LOW);
      carry = HIGH;
    }
    else if((digitalRead(secondValue)) || (digitalRead(firstValue) || carry)){
      digitalWrite(result,HIGH);
      carry = LOW;
    }
    else{ digitalWrite(result, LOW);}
    if((firstValue == 5) && carry)digitalWrite(result+1, HIGH);
    else if(firstValue == 5)digitalWrite(result+1, LOW);
    secondValue+=1;
    result+=1;
  }
}
