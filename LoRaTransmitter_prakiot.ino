#include <SPI.h>
#include <LoRa.h>

#define SCK     5    // GPIO5  -- SX1278's SCK
#define MISO    19   // GPIO19 -- SX1278's MISO
#define MOSI    27   // GPIO27 -- SX1278's MOSI
#define SS      18   // GPIO18 -- SX1278's CS
#define RST     14   // GPIO14 -- SX1278's RESET
#define DI0     26   // GPIO26 -- SX1278's IRQ(Interrupt Request)
#define BAND    915E6

unsigned int counter = 0;

void setup() {
  Serial.begin(9600);
  while (!Serial);
  Serial.println();
  Serial.println("LoRa Sender Test");

  SPI.begin(SCK, MISO, MOSI, SS);
  LoRa.setPins(SS, RST, DI0);
  if (!LoRa.begin(BAND)) {
    Serial.println("Starting LoRa failed!");
    while (1);
  }
   LoRa.setSyncWord(0xF1);
  Serial.println("init ok");

  delay(1500);
}

void loop() {
  Serial.println("Sending packet: " + String(counter));

  // send packet
  LoRa.beginPacket();
  LoRa.write(counter);
  LoRa.endPacket();
  Serial.println("sended");

  counter++;
  delay(500); // delay for 1 second before sending the next packet
}
