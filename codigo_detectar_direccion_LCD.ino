#include <Wire.h>

void setup() {
  Wire.begin();
  Serial.begin(9600);
  while (!Serial); // Espera al monitor serial (si es necesario)
  Serial.println("\nEscaneando dispositivos I2C...");

  byte error, address;
  int nDevices = 0;

  for (address = 1; address < 127; address++) {
    Wire.beginTransmission(address);
    error = Wire.endTransmission();

    if (error == 0) {
      Serial.print("¡Dispositivo I2C encontrado en la dirección 0x");
      if (address < 16) Serial.print("0");
      Serial.print(address, HEX);
      Serial.println(" !");
      nDevices++;
    }
  }

  if (nDevices == 0) Serial.println("No se encontraron dispositivos I2C");
  else Serial.println("Escaneo completo");
}

void loop() {}
