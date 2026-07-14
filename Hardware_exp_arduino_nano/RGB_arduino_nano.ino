#define RED 22
#define BLUE 24
#define GREEN 23
#define LED_PWR 25

//initialise the digit Pin as an output
void setup(){
  pinMode(RED,OUTPUT);
  pinMode(BLUE,OUTPUT);
  pinMode(GREEN,OUTPUT);
  pinMode(LED_PWR,OUTPUT);
}

void loop(){
  digitalWrite(RED,LOW);
  delay(1000);
  digitalWrite(GREEN,LOW);
  delay(1000);
  digitalWrite(BLUE,LOW);
  delay(1000);
  digitalWrite(RED,HIGH);
  delay(1000);
  digitalWrite(GREEN,HIGH);
  delay(1000);
  digitalWrite(BLUE,HIGH);
  delay(1000);
  digitalWrite(LED_PWR,HIGH);
  delay(1000);
  digitalWrite(LED_PWR,LOW);
  delay(1000);

}