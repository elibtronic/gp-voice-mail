//
// ghello phone voice mail
//
// Push button on Digital 7
// LED on Digital 13
// PhotoCell on A0
//

int bState = 0;

void setup(){
 
 Serial.begin(9600);
 pinMode(13, OUTPUT);
 pinMode(7, INPUT);
 digitalWrite(7,HIGH); //Pull UP Dammit

 Serial.println("Init");
 start_led();
 
  
}

void start_led()
{
  digitalWrite(13, HIGH);
  delay(500);
  digitalWrite(13, LOW);
  delay(500);
  digitalWrite(13, HIGH);
  delay(500);
  digitalWrite(13, HIGH);
  delay(500);
  digitalWrite(13, LOW);
}

void loop(){
  bState = digitalRead(7);
  Serial.println(bState);
  if (bState == LOW)
    digitalWrite(13,HIGH);
  else
    digitalWrite(13,LOW);
 

  
  
}

