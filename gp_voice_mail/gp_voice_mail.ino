//
// ghello phone voice mail
//
// Push button on Digital 7
// LED on Digital 13
// PhotoCell on A0
//
// Note to self
//
// - Green wire LED supply
// - Blue wire LED ground
// - Yellow wire Switch
// - Orange wire Switch
//

int bState = 0;
int lLevel = 0;
int is_triggered = 0;
//increase for higher sensitivity, decrease for lower sensitivity
const int tThreshold = 50;
//How Often to start the test loop, all the time is probably overkill
const int pInterval = 1500;
//number of seconds the led on the phone has to be on for
const int led_on_for = 5;

void setup(){
 
 Serial.begin(9600);
 pinMode(13, OUTPUT);
 pinMode(7, INPUT);
 digitalWrite(7,HIGH); //Pull UP Dammit
 start_led(); 
}

void start_led()
{
  digitalWrite(13, HIGH);
  delay(250);
  digitalWrite(13, LOW);
  delay(250);
  digitalWrite(13, HIGH);
  delay(250);
  digitalWrite(13, HIGH);
  delay(250);
  digitalWrite(13, LOW);
}

void loop(){

  delay(pInterval);
  if (is_triggered == 0){
  for (int i = 0; i < led_on_for; i++){
      delay(1000);
      if (analogRead(0) < tThreshold){
        break;
      }
      //Only here if photocell triggered above threshold for led_on_for
      digitalWrite(13,HIGH);
      is_triggered = 1;
    }
  }
  //Reset if button is pressed and if checker has been triggered
  if ((digitalRead(7) == LOW) && (is_triggered == 1)){
   digitalWrite(13,LOW);
   is_triggered = 0;
  }
  
  //If triggered write a 1, else 0 which means no voice mail
  if (is_triggered == 1){
    Serial.print("1");
  }
  else
  {
    Serial.print("0");
  }
  Serial.flush();

}

