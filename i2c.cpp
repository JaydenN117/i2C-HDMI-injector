#include <Arduino.h>
#include <Wire.h>

// Dasung display I2C address
const uint8_t DASUNG_I2C_ADDR = 0x37;

// Command sequences
const uint8_t CMD_SEQUENCE_1[] = {0x51, 0x84, 0x03, 0x08, 0x01, 0x01, 0xB0};
const uint8_t CMD_CLEAR[] = {0x51, 0x84, 0x03, 0x08, 0x06, 0x02, 0xB4};

void sendCommand(const uint8_t* cmd, uint8_t length) {
  Wire.beginTransmission(DASUNG_I2C_ADDR);
  for (uint8_t i = 0; i < length; i++) {
    Wire.write(cmd[i]);
  }
  Wire.endTransmission();
}

void setup() {
  // Initialize serial for debugging
  Serial.begin(115200);

  
  Serial.println("Dasung Display Hack Starting...");
  
  // Initialize I2C
  Wire.begin();
  
  // Small delay to ensure I2C is ready
  delay(100);
  
  // Send clear command on startup
  Serial.println("Sending clear command...");
  sendCommand(CMD_CLEAR, sizeof(CMD_CLEAR));
  
  delay(100);
  
  // Send the first command sequence
  Serial.println("Sending command sequence 1...");
  sendCommand(CMD_SEQUENCE_1, sizeof(CMD_SEQUENCE_1));
  
  Serial.println("Setup complete!");
}

void loop() {
  sendCommand(CMD_SEQUENCE_1, sizeof(CMD_SEQUENCE_1));
  // Small delay to prevent overwhelming the serial buffer
  delay(300);
}
