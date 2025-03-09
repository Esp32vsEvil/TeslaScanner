/* A bluetooth scanner for ESP32 devices to find Tesla vehicles and do things. Tesla in all their genious uses the same bt device naming convention
across all (truck included) vehicles, first letter "S" eighteenth letter "C".

I'm a codelet and this was written in the Arduino IDE, this particular version for an ESP32-CAM module. (POS, avoid)
Will flash the very bright LED when a Tesla is in the vincinity, altering speed/duration dependent on signal strength.
This can of course be modified to fit your device/desired action.

Uses the libraries listed below obviously, thank you to Neil Kolban and Evandro Copercini. Update to newest libraries
in case of errors. 

*/
#include <Arduino.h>
#include <BLEDevice.h>
#include <BLEUtils.h>
#include <BLEScan.h>
#include <BLEAdvertisedDevice.h>
#include <BLEBeacon.h>

//change this to your LED pin or whatever you want to control
int goPin = 4;



int scanTime = 5;  //In seconds
BLEScan *pBLEScan;

class MyAdvertisedDeviceCallbacks : public BLEAdvertisedDeviceCallbacks {
  void onResult(BLEAdvertisedDevice advertisedDevice) {


  if (advertisedDevice.haveName())
      {
        //print device name, determine if characters at 0 and 17 match Tesla convention
        Serial.print("Device name: ");
        String stringName = (advertisedDevice.getName());
        Serial.println(stringName);
        Serial.println("--");
        char firstletter = stringName.charAt(0);
        char lastletter = stringName.charAt(17);
        
        //its a Tesla, do things
        if(firstletter =='S'  & lastletter =='C' ) {
          Serial.println("FOUND IT");

          //determine signal strength, maybe map a trimpot input here to adjust
          int rssiSigned = (advertisedDevice.getRSSI());
          int rssi = constrain (rssiSigned - (rssiSigned * 2), 80, 100);
          Serial.println(rssi);
          int jaws = map (rssi, 80, 100, 50, 1000);
          for (int i = map (rssi, 80, 100, 10, 1); i > 0; i-- ){
          digitalWrite(goPin, HIGH);
          delay(100);
          digitalWrite(goPin, LOW);
          delay(jaws);
          }
          
        }
        
      }

 
  } 
};

void setup() {
  Serial.begin(115200);
  delay(2000);

  pinMode(goPin, OUTPUT);
  digitalWrite(goPin, LOW);
  
  Serial.println("Scanning...");

  BLEDevice::init("");
  pBLEScan = BLEDevice::getScan();  //create new scan
  pBLEScan->setAdvertisedDeviceCallbacks(new MyAdvertisedDeviceCallbacks());
  pBLEScan->setActiveScan(true);  //active scan uses more power, but get results faster
  pBLEScan->setInterval(40);
  pBLEScan->setWindow(40);  // less or equal setInterval value
}

void loop() {
  // put your main code here, to run repeatedly:
  BLEScanResults *foundDevices = pBLEScan->start(scanTime, false);
 // Serial.print("Devices found: ");
 // Serial.println(foundDevices->getCount());
 // Serial.println("Scan done!");
  pBLEScan->clearResults();  // delete results fromBLEScan buffer to release memory
 // delay(500);
}
