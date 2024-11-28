#include <SPI.h>
#include <LoRa.h>

// Konfigurasi pin untuk LilyGO T-Beam
#define SCK 5
#define MISO 19
#define MOSI 27
#define SS 18
#define RST 23
#define DIO0 26

// Frekuensi LoRa: sesuaikan dengan wilayah geografis Anda
#define BAND 915E6 // 433E6 untuk Asia, 866E6 untuk Eropa, 915E6 untuk Amerika Utara

int counter = 0;

void setup() {
  // Inisialisasi Serial Monitor
  Serial.begin(115200);
  delay(1000);
  Serial.println("Initializing T-Beam Meshtastic...");

  // Inisialisasi SPI LoRa
  SPI.begin(SCK, MISO, MOSI, SS);
  LoRa.setPins(SS, RST, DIO0);

  if (!LoRa.begin(BAND)) {
    Serial.println("LoRa initialization failed!");
    while (true); // Berhenti jika LoRa gagal diinisialisasi
  }
  
  Serial.println("LoRa initialization succeeded!");
  LoRa.setSyncWord(0xF1); // Opsional: Set Sync Word untuk jaringan tertentu
}

void loop() {
  // Kirim pesan melalui LoRa
  Serial.print("Sending packet: ");
  Serial.println(counter);

  LoRa.beginPacket();
  LoRa.print("Hello :) #");
  LoRa.print(counter);
  LoRa.endPacket();

  Serial.println("Packet sent!");

  counter++;
  delay(5000); // Tunggu 5 detik sebelum mengirimkan paket berikutnya
}
