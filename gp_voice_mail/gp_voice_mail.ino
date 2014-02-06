//
// ghello phone voice mail
//
// Push button on Digital 7
// LED on Digital 13
// PhotoCell on A0
//

int bState = 0;
int lLevel = 0;
int is_triggered = 0;
const int tThreshold = 50;
const int pInterval = 3000;


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


  delay(pInterval);
  Serial.println(analogRead(0));
  
  if(is_triggered == 0){
    if(analogRead(0) > tThreshold)
    {
      digitalWrite(13,HIGH);
      is_triggered = 1;
      Serial.println("triggered");
    }
  }
//  if (is_triggered == 1){
//    if(digitalRead(7) == HIGH){
//        digitalWrite(13,LOW);
//        Serial.println("reset");
//        is_triggered = 0;
//    }
//  }
  if ((digitalRead(7) == LOW) && (is_triggered == 1 )){
   digitalWrite(13,LOW);
   is_triggered = 0;
   Serial.println("reset");
    
  }
  
//  bState = digitalRead(7);
//  if (bState == LOW)
//    digitalWrite(13,HIGH);
//  else
//    digitalWrite(13,LOW);
   

}

