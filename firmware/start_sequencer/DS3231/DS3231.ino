#include <Wire.h>
#define DS3231_I2C_ADDRESS 104

byte seconds, minutes, hours, day, date, month, year;
char weekDay[4];

byte tMSB, tLSB;
float temp3231;

char pwm = 0;

void setup()
{
  Wire.begin();
  Serial.begin(9600);
  analogWrite(5,pwm);
}

void loop()
{
  
  watchConsole();
  
  
  get3231Date();
  
  Serial.print(weekDay); Serial.print(", "); Serial.print(date, DEC); Serial.print("/"); Serial.print(month, DEC); Serial.print("/"); Serial.print(year, DEC); Serial.print(" - ");
  Serial.print(hours, DEC); Serial.print(":"); Serial.print(minutes, DEC); Serial.print(":"); Serial.print(seconds, DEC);
  
  Serial.print(" - Temp: "); Serial.println(get3231Temp());

  analogWrite(5,++pwm);
  Serial.println(pwm);
  delay(1000);
}

// Convert normal decimal numbers to binary coded decimal
byte decToBcd(byte val)
{
  return ( (val/10*16) + (val%10) );
}

void watchConsole()
{
  if (Serial.available()) {      // Look for char in serial queue and process if found
    if (Serial.read() == 84) {      //If command = "T" Set Date
      set3231Date();
      get3231Date();
      Serial.println(" ");
    }
  }
}
  
void set3231Date()
{ 
//T(sec)(min)(hour)(dayOfWeek)(dayOfMonth)(month)(year)
//T(00-59)(00-59)(00-23)(1-7)(01-31)(01-12)(00-99)
//Example: 02-Feb-09 @ 19:57:11 for the 3rd day of the week -> T1157193020209

  seconds = (byte) ((Serial.read() - 48) * 10 + (Serial.read() - 48)); // Use of (byte) type casting and ascii math to achieve result.  
  minutes = (byte) ((Serial.read() - 48) *10 +  (Serial.read() - 48));
  hours   = (byte) ((Serial.read() - 48) *10 +  (Serial.read() - 48));
  day     = (byte) (Serial.read() - 48);
  date    = (byte) ((Serial.read() - 48) *10 +  (Serial.read() - 48));
  month   = (byte) ((Serial.read() - 48) *10 +  (Serial.read() - 48));
  year    = (byte) ((Serial.read() - 48) *10 +  (Serial.read() - 48));
  Wire.beginTransmission(DS3231_I2C_ADDRESS);
  Wire.write(0x00);
  Wire.write(decToBcd(seconds));
  Wire.write(decToBcd(minutes));
  Wire.write(decToBcd(hours));
  Wire.write(decToBcd(day));
  Wire.write(decToBcd(date));
  Wire.write(decToBcd(month));
  Wire.write(decToBcd(year));
  Wire.endTransmission();
}


void get3231Date()
{
  // send request to receive data starting at register 0
  Wire.beginTransmission(DS3231_I2C_ADDRESS); // 104 is DS3231 device address
  Wire.write(0x00); // start at register 0
  Wire.endTransmission();
  Wire.requestFrom(DS3231_I2C_ADDRESS, 7); // request seven bytes

  if(Wire.available()) { 
    seconds = Wire.read(); // get seconds
    minutes = Wire.read(); // get minutes
    hours   = Wire.read();   // get hours
    day     = Wire.read();
    date    = Wire.read();
    month   = Wire.read(); //temp month
    year    = Wire.read();
       
    seconds = (((seconds & B11110000)>>4)*10 + (seconds & B00001111)); // convert BCD to decimal
    minutes = (((minutes & B11110000)>>4)*10 + (minutes & B00001111)); // convert BCD to decimal
    hours   = (((hours & B00110000)>>4)*10 + (hours & B00001111)); // convert BCD to decimal (assume 24 hour mode)
    day     = (day & B00000111); // 1-7
    date    = (((date & B00110000)>>4)*10 + (date & B00001111)); // 1-31
    month   = (((month & B00010000)>>4)*10 + (month & B00001111)); //msb7 is century overflow
    year    = (((year & B11110000)>>4)*10 + (year & B00001111));
  }
  else {
    //oh noes, no data!
  }
  
  switch (day) {
    case 1:
      strcpy(weekDay, "Sun");
      break;
    case 2:
      strcpy(weekDay, "Mon");
      break;
    case 3:
      strcpy(weekDay, "Tue");
      break;
    case 4:
      strcpy(weekDay, "Wed");
      break;
    case 5:
      strcpy(weekDay, "Thu");
      break;
    case 6:
      strcpy(weekDay, "Fri");
      break;
    case 7:
      strcpy(weekDay, "Sat");
      break;
  }
}

float get3231Temp()
{
  //temp registers (11h-12h) get updated automatically every 64s
  Wire.beginTransmission(DS3231_I2C_ADDRESS);
  Wire.write(0x11);
  Wire.endTransmission();
  Wire.requestFrom(DS3231_I2C_ADDRESS, 2);
  
  if(Wire.available()) {
    tMSB = Wire.read(); //2's complement int portion
    tLSB = Wire.read(); //fraction portion
    
    temp3231 = (tMSB & B01111111); //do 2's math on Tmsb
    temp3231 += ( (tLSB >> 6) * 0.25 ); //only care about bits 7 & 8
  }
  else {
    //oh noes, no data!
  }
    
  return temp3231;
}
