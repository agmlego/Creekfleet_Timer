#define LONG_HORN 750
#define LONG_HORN_SPACE LONG_HORN/2
#define SHORT_HORN 400
#define SHORT_HORN_SPACE SHORT_HORN/2
#define HORN_PIN 13


unsigned char hours = 0, minutes = 0, seconds = 0;
unsigned long temp_time = 0, start = 0;
unsigned char idx = 0;
char time_buffer[9];

void long_horn(){
  Serial.println(F("\tLong Horn!"));
  digitalWrite(HORN_PIN,HIGH);
  delay(LONG_HORN);
  digitalWrite(HORN_PIN,LOW);
  delay(LONG_HORN_SPACE);
}

void short_horn(){
  Serial.println(F("\tShort Horn!"));
  digitalWrite(HORN_PIN,HIGH);
  delay(SHORT_HORN);
  digitalWrite(HORN_PIN,LOW);
  delay(SHORT_HORN_SPACE);
}

void tick(unsigned long duration, unsigned char num_long, unsigned char num_short){
  temp_time = millis();
  
  for(idx=0; idx<num_long; ++idx){
    long_horn();
  }
  for(idx=0; idx<num_short; ++idx){
    short_horn();
  }
  
  delay(duration - (millis() - temp_time));
}

void setup() {
  pinMode(HORN_PIN,OUTPUT);
  Serial.begin(115200);
  Serial.println(F("3:00 to start!"));
  tick(60000,3,0);
  Serial.println(F("2:00 to start!"));
  tick(30000,2,0);
  Serial.println(F("1:30 to start!"));
  tick(30000,1,3);
  Serial.println(F("1:00 to start!"));
  tick(30000,1,0);
  Serial.println(F("0:30 to start!"));
  tick(10000,0,3);
  Serial.println(F("0:20 to start!"));
  tick(10000,0,2);
  Serial.println(F("0:10 to start!"));
  tick(5000,0,1);
  Serial.println(F("0:05 to start!"));
  tick(1000,0,1);
  Serial.println(F("0:04 to start!"));
  tick(1000,0,1);
  Serial.println(F("0:03 to start!"));
  tick(1000,0,1);
  Serial.println(F("0:02 to start!"));
  tick(1000,0,1);
  Serial.println(F("0:01 to start!"));
  tick(1000,0,1);
  Serial.println(F("0:00 to start!"));
  tick(1000,1,0);
}

void loop() {
  start = millis();
  temp_time = millis();
  hours = temp_time / (unsigned long)(3600000);
  temp_time %= (unsigned long)(3600000);
  minutes = temp_time / (unsigned long)(60000);
  temp_time %= (unsigned long)(60000);
  seconds = temp_time / 1000;
  sprintf(time_buffer, "%02d:%02d:%02d", hours, minutes, seconds);
  Serial.println(time_buffer);
  delay(1000 - (millis() - start));
}
