/*
 * SD card attached to SPI bus as follows:
 ** MOSI - pin 11
 ** MISO - pin 12
 ** CLK - pin 13
 ** CS - pin 4
 */

#include <SPI.h>
#include <SD.h>

const int chipSelect = 4;

const int analogPin = 0;
const int buttonPin = 3;

char* filename = "datalog.txt";

void setup()
{
  Serial.begin(9600);

  Serial.print("Initializing SD card...");
  // make sure that the default chip select pin is set to
  // output, even if you don't use it:
  pinMode(10, OUTPUT);

  // see if the card is present and can be initialized:
  if (!SD.begin(chipSelect)) {
    Serial.println("Card failed, or not present");
    // don't do anything more:
    return;
  }
  Serial.println("card initialized.");
  
  if (SD.exists(filename)) {
    SD.remove(filename);
  }
  
  pinMode(buttonPin, INPUT);
}

void loop()
{
  int sensor = analogRead(analogPin);
  
  File dataFile = SD.open(filename, FILE_WRITE);

  if (dataFile) {
    String dataString = String(sensor);
    //Serial.println(dataString);
    dataFile.println(dataString);
    dataFile.close();
  } else {
    Serial.println("error opening " + String(filename));
  }
    
  int dumpData = digitalRead(buttonPin);
  if (dumpData) {
    Serial.println("Content of " + String(filename));
    Serial.println("-----------------");
    File dataFile = SD.open(filename);
    if (dataFile) {
      while (dataFile.available()) {
        Serial.write(dataFile.read());
      }
      dataFile.close();
    }  
    Serial.println("-----------------");
  }
  
  delay(500);
}
