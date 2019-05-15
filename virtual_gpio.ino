/*
 * 1 - Set
 *      1/PIN_NUMBER/VALUE/
 *      VALUE = 1 FOR INPUT, 2 FOR OUTPUT
 *      
 * 2 - Write
 *    2/WRITE_TYPE/PIN_NUMBER/VALUE
 *    WRITE_TYPE = 1 FOR ANALOG, 2 FOR DIGITAL
 *    VALUE = FOR ANALOG WRITE: ANALOG_RATE, FOR DIGITAL WRITE: 2 FOR HIGH OR 1 FOR LOW
 *    
 * 3 - Read
 *    3/READ_TYPE/PIN_NUMBER
 *    READ_TYPE = 1 FOR ANALOG READ, 2 FOR DIGITAL READ
 * 
 * 
 */


#define BAUDRATE 9600

int activityLED = 13;

unsigned long serialdata;
int inbyte;
int digitalState;
int pinNumber;
int analogRate;
int sensorVal;

void setup() {
   for(int k=2; k<=19; k++)
    pinMode(k, INPUT);
   
  Serial.begin(BAUDRATE);
  pinMode(activityLED, OUTPUT);
  digitalWrite(activityLED, HIGH);
  delay(30);
  digitalWrite(activityLED, LOW);
  delay(100);
  digitalWrite(activityLED, HIGH);
  delay(30);
  digitalWrite(activityLED, LOW);  // simply a reset marker of 2 flashes
}

void loop()
{
  getSerial();
  switch(serialdata)
  {

  case 1:{ // SET
    getSerial();
    pinNumber = serialdata;
    getSerial();
    int state = serialdata;
    if (state == 2) // 1 for input, 2 for output
      pinMode(pinNumber, OUTPUT);
    else
      pinMode(pinNumber, INPUT);
  break;
  }
  case 2: // WRITE
    {
      //ANALOG DIGITAL WRITE
      getSerial();
      
      switch (serialdata)
      {
      case 1: // ANALOG WRITE
        {
          getSerial();
          pinNumber = serialdata;
          getSerial();
          analogRate = serialdata;
          analogWrite(pinNumber, analogRate);
          pinNumber = 0;
          break;
        }
      case 2: // DIGITAL WRITE
        {
          getSerial();
          pinNumber = serialdata;
          getSerial();
          digitalState = serialdata;
          //pinMode(pinNumber, OUTPUT);
          if (digitalState == 1)
          {
            digitalWrite(pinNumber, LOW);
          }
          if (digitalState == 2)
          {
            digitalWrite(pinNumber, HIGH);
          }
          pinNumber = 0;
          break;
         
        }
     }
     break; 
    }
    case 3: // READ
    {
      getSerial();
      switch (serialdata)
      {
      case 1: // ANALOG READ
        {
          getSerial();
          pinNumber = serialdata;
          sensorVal = analogRead(pinNumber);
          Serial.println(sensorVal);
          sensorVal = 0;
          pinNumber = 0;
          break;
        } 
      case 2: // DIGITAL READ
        {
          getSerial();
          pinNumber = serialdata;
          sensorVal = digitalRead(pinNumber);
          Serial.println(sensorVal);
          sensorVal = 0;
          pinNumber = 0;
          break;
        }
      }
      break;
    }
    case 4: // WRITE PWM
    {      
      getSerial();
      pinNumber = serialdata;
      getSerial();
      analogRate = serialdata;
      analogWrite(pinNumber, analogRate);
      pinNumber = 0;
     break;
    }
  }
}

long getSerial()
{
  serialdata = 0;
  while (inbyte != '/')
  {
    inbyte = Serial.read(); 
    if (inbyte > 0 && inbyte != '/')
    {
     
      serialdata = serialdata * 10 + inbyte - '0';
    }
  }
  inbyte = 0;
  return serialdata;
}
