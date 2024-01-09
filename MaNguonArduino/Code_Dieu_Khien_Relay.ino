#include <Adafruit_Fingerprint.h>
int electronic_lock = 12; 
// pin #2 is IN from sensor 
// pin #3 is OUT from arduino  
SoftwareSerial mySerial(2, 3);// Tx, Rx

Adafruit_Fingerprint finger = Adafruit_Fingerprint(&mySerial);

void setup()  
{
  pinMode(12, OUTPUT);
  Serial.begin(9600);
  //pinMode(8, OUTPUT);
  while (!Serial);
  delay(100);
  // set the data rate for the sensor serial port
  finger.begin(57600);
  
  if (finger.verifyPassword()) {
    Serial.println("Found fingerprint sensor");
  } else {
    Serial.println("Did not find fingerprint sensor");
    while (1) { delay(1); }
  }

  finger.getTemplateCount();
  Serial.print("Sensor contains "); Serial.print(finger.templateCount); Serial.println(" template(s)");
  Serial.println("Waiting for valid finger...");
}

void loop()             // run over and over again
{
  digitalWrite(8, HIGH);
  delay(5000);  
  getFingerprintIDez();
  delay(50);            //don't ned to run this at full speed.
}

int getFingerprintIDez() {
  uint8_t p = finger.getImage();
  if (p != FINGERPRINT_OK)  return -1;

  p = finger.image2Tz();
  if (p != FINGERPRINT_OK)  return -1;

  p = finger.fingerFastSearch();
  if (p != FINGERPRINT_OK)  return -1;
  
  // found a match!
  Serial.print("Found ID #"); Serial.print(finger.fingerID); 
  Serial.print(" with confidence of "); Serial.println(finger.confidence);
   digitalWrite(electronic_lock, HIGH);
  delay(1500);                        //Change the door lock delay from here
  digitalWrite(electronic_lock, LOW);
  Serial.println("Unlocked");
  return finger.fingerID; 
}
