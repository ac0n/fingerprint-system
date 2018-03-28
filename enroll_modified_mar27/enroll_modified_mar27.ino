/*************************************************** 
This is an example sketch for our optical Fingerprint sensor


Designed specifically to work with the Adafruit BMP085 Breakout ----> http://www.adafruit.com/products/751

These displays use TTL Serial to communicate, 2 pins are required to interface Adafruit invests time and resources providing this open source code, please support Adafruit and open-source hardware by purchasing products from Adafruit!

Written by Limor Fried/Ladyada for Adafruit Industries. BSD license, all text above must be included in any redistribution ****************************************************/
/**********************MODIFIED BY PELEGREN of bedRoonics Labs**********************************/
/********************** ARDUINO FINGERPRINT SCANNER with 16x2 LCD monitor***************/

#include <Adafruit_Fingerprint.h>
#include <LiquidCrystal.h>
#include <SoftwareSerial.h>
int Con=80;
int getFingerprintIDez();
// pin #2 is IN from sensor (GREEN wire)

// pin #3 is OUT from arduino (WHITE wire)

SoftwareSerial mySerial(2, 3);
Adafruit_Fingerprint finger = Adafruit_Fingerprint(&mySerial);
LiquidCrystal lcd(12, 11, 7, 6, 5, 4); // initialize the library with the numbers of the interface pins


void setup()
{ 
  analogWrite(8, Con);
  Serial.begin(9600); // initialize the serial communications:
  lcd.begin(16,2); 
  lcd.print("Waiting...");

pinMode(13,OUTPUT);

pinMode(12,OUTPUT);

pinMode(11, OUTPUT);

pinMode(A0, INPUT);

  finger.begin(9600); // set the data rate for the sensor serial port }

//Start digital scanning...
 
  if (finger.verifyPassword()) {
    Serial.println("Found fingerprint sensor!");
  } else {
    Serial.println("Did not find fingerprint sensor");
  }
  while(1){
  delay(1000); 
  getFingerprintEnroll(); 
  Serial.println("Waiting for valid finger...");
  }
}


void displayUnlockedScreen()
{
   lcd.setCursor(0,0); lcd.print("Loading...");
   for (int positionCounter = 0; positionCounter < 13; positionCounter++) {
    // scroll one position left:
    lcd.scrollDisplayLeft();
    // wait a bit:
    delay(150);
  }
  for (int positionCounter = 0; positionCounter < 29; positionCounter++) {
    // scroll one position right:
    lcd.scrollDisplayRight();
    // wait a bit:
    delay(150);
  }
  for (int positionCounter = 0; positionCounter < 16; positionCounter++) {
    // scroll one position left:
    lcd.scrollDisplayLeft();
    // wait a bit:
    delay(150);
  }
  delay(1000);    // delay at the end of the full loop:


  
   lcd.setCursor(4,2);
   lcd.print("Unlocked");

   lcd.setCursor(4,2);
   lcd.print("WELCOME");
}
void displayNick()
{
  lcd.setCursor(4,2);
  lcd.print("Pagado!");
}

void displayIoanna()
{
  lcd.setCursor(2,2);
  lcd.print("Pago vencido!");
}

void displayLockScreen()
{
  lcd.setCursor(1,1);
  digitalWrite(13,HIGH); 
  delay(8000);
  lcd.print("LOCKED");

  lcd.setCursor(1,2);
  digitalWrite(13,HIGH); 
  delay(5000);
  lcd.print("Waiting...");

}






void loop() // run over and over again
{
    delay(100);
  
    digitalWrite (13,HIGH);
  
    uint8_t getFingerprintID();
    int fingerprintID = getFingerprintID();
  
  if (fingerprintID == 0) {// ID #0 not allowed, try again!
       return;
  }
       
  if(fingerprintID == 1)
    {
      lcd.setCursor(0,0); lcd.print("Loading...");
      displayUnlockedScreen();
      displayIoanna();
      delay(5000);
      displayLockScreen();
    }
  
     if(fingerprintID == 2)
    {
      displayUnlockedScreen();
      displayNick();
      delay(5000);
      displayLockScreen();
    }

}

uint8_t getFingerprintEnroll() {
   int p = -1;
   uint8_t fingerprintID;
    Serial.print("Waiting for valid finger to enroll as #"); Serial.println(fingerprintID);
    while (p != FINGERPRINT_OK) 
    {
      
  uint8_t p = finger.getImage();
  
     switch (p) {
      case FINGERPRINT_OK:
        Serial.println("Image taken");
        break;
      case FINGERPRINT_NOFINGER:
        Serial.println(".");
        break;
      case FINGERPRINT_PACKETRECIEVEERR:
        Serial.println("Communication error");
        break;
      case FINGERPRINT_IMAGEFAIL:
        Serial.println("Imaging error");
        break;
      default:
        Serial.println("Unknown error");
        break;
        
        }
    }
  // found a match!
  
  digitalWrite(13, LOW);
  
  delay(10);
  
  digitalWrite(13, HIGH);
  
  delay(10);
  
  digitalWrite(11,LOW);
  
  delay(500);
  
  digitalWrite(12,HIGH);
  
  lcd.clear();
  
  lcd.setCursor(0, 0);
  
  lcd.print("Found ID # ");
  
  lcd.print(finger.fingerID);
  
  lcd.setCursor(0, 1);
  
  lcd.print("confidence ");
  
  lcd.print(finger.confidence);
  
  return finger.fingerID;
  
  
   p = finger.image2Tz(1);
  switch (p) {
    case FINGERPRINT_OK:
      Serial.println("Image converted");
      break;
    case FINGERPRINT_IMAGEMESS:
      Serial.println("Image too messy");
      return p;
    case FINGERPRINT_PACKETRECIEVEERR:
      Serial.println("Communication error");
      return p;
    case FINGERPRINT_FEATUREFAIL:
      Serial.println("Could not find fingerprint features");
      return p;
    case FINGERPRINT_INVALIDIMAGE:
      Serial.println("Could not find fingerprint features");
      return p;
    default:
      Serial.println("Unknown error");
      return p;
  }
  
  Serial.println("Remove finger");
  delay(2000);
  p = 0;
  while (p != FINGERPRINT_NOFINGER) {
    p = finger.getImage();
  }
  Serial.print("ID "); Serial.println(fingerprintID);
  p = -1;
  Serial.println("Place same finger again");
  while (p != FINGERPRINT_OK) {
    p = finger.getImage();
    switch (p) {
    case FINGERPRINT_OK:
      Serial.println("Image taken");
      break;
    case FINGERPRINT_NOFINGER:
      Serial.print(".");
      break;
    case FINGERPRINT_PACKETRECIEVEERR:
      Serial.println("Communication error");
      break;
    case FINGERPRINT_IMAGEFAIL:
      Serial.println("Imaging error");
      break;
    default:
      Serial.println("Unknown error");
      break;
    }
  }
  
  p = finger.image2Tz(2);
  switch (p) {
    case FINGERPRINT_OK:
      Serial.println("Image converted");
      break;
    case FINGERPRINT_IMAGEMESS:
      Serial.println("Image too messy");
      return p;
    case FINGERPRINT_PACKETRECIEVEERR:
      Serial.println("Communication error");
      return p;
    case FINGERPRINT_FEATUREFAIL:
      Serial.println("Could not find fingerprint features");
      return p;
    case FINGERPRINT_INVALIDIMAGE:
      Serial.println("Could not find fingerprint features");
      return p;
    default:
      Serial.println("Unknown error");
      return p;
  }
  
  // OK converted!
  Serial.print("Creating model for #");  Serial.println(fingerprintID);
  
  p = finger.createModel();
  if (p == FINGERPRINT_OK) {
    Serial.println("Prints matched!");
  } else if (p == FINGERPRINT_PACKETRECIEVEERR) {
    Serial.println("Communication error");
    return p;
  } else if (p == FINGERPRINT_ENROLLMISMATCH) {
    Serial.println("Fingerprints did not match");
    return p;
  } else {
    Serial.println("Unknown error");
    return p;
  }   
  
  Serial.print("ID "); Serial.println(fingerprintID);
  p = finger.storeModel(fingerprintID);
  if (p == FINGERPRINT_OK) {
    Serial.println("Stored!");
  } else if (p == FINGERPRINT_PACKETRECIEVEERR) {
    Serial.println("Communication error");
    return p;
  } else if (p == FINGERPRINT_BADLOCATION) {
    Serial.println("Could not store in that location");
    return p;
  } else if (p == FINGERPRINT_FLASHERR) {
    Serial.println("Error writing to flash");
    return p;
  } else {
    Serial.println("Unknown error");
    return p;
  }   
  
}

