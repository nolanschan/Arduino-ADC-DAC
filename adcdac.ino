//**********************************************************************//
//  Name                : Analog In to 12-bit SPI DAC Microchip MCP4921 //
//  Author              : Gary Hill                                     //
//  Last Revision       : 18 March, 2013                                //
//  Created             : 14 March, 2010                                //
//  Version             : 1.1                                           //
//  Arduino IDE Version : 0022                                          //
//  Reference(s)        : http://arduino.cc/en/Reference/SPI            //
//                      : http://arduino.cc/en/Tutorial/SPIDigitalPot   //
//  Notes               : If not included, download SPI folder and place//
//                      : in the arduino-00nn/hardware/libraries folder //
//**********************************************************************//

// SPI Interface     SS_PIN(PB0), SCK_PIN(PB1), COPI_PIN(PB2), CIPO_PIN(PB3)
// Arduino Pin       53           52            51             50
// MCP4921 DAC       CS           SCK           SDI           n/a
#include <SPI.h>

// #define cbi(sfr, bit) (_SFR_BYTE(sfr) &= ~_BV(bit)) //macro to clear bit in special function register
// #define sbi(sfr, bit) (_SFR_BYTE(sfr) |= _BV(bit)) //macro to set bit in special function register

// SPI hardware interface
// set pin 53 as the slave select for the digital pot:
const int slaveSelectPin = 53;   // SS Pin

// ATmega328P ADC 
const int analogPin = 0;     // analog input channel

// ADC analog input value
word sensorValue = 0;  // equivalent to unsigned int

// Byte of data to output to DAC 
byte data = 0;

void setup() {
  // set prescale to 16
  //sbi(ADCSRA, ADPS2);
  //cbi(ADCSRA, ADPS1);
  //cbi(ADCSRA, ADPS0);
  
  // set pin(s) to input and output
  pinMode(analogPin + A0, INPUT);
  
  // set the slaveSelectPin as an output:
  pinMode (slaveSelectPin, OUTPUT);
  // Initializes the SPI bus by setting SCK, MOSI, and SS to outputs, 
  // pulling SCK and MOSI low, and SS high. 
  SPI.begin(); 
}

void loop() {
  // read the value from the sensor:
  sensorValue = analogRead(analogPin);   // comment out this line to test DAC
  // sensorValue = 0x0200;               // 0x03FF = Vref, 0x0200 = 1/2 Vref, 0x0000 = 0
  sensorValue = sensorValue << 2 ;       // 10 bit ADC to 12-bit DAC word
  // set SS pin low, beginning 16-bit (2 byte) data transfer to DAC
  digitalWrite(slaveSelectPin, LOW);
  // send high byte
  data = highByte(sensorValue);  
  data = 0b00001111 & data;     // clear 4-bit command field (optional)  
  data = 0b00110000 | data;     // set command: 0 = DACA, 0 = buffered, 1 = 1x, 1 = output buffer enabled
  SPI.transfer(data);           // alternate: shiftOut(MOSI, SCK, MSBFIRST, data);
  // send low byte
  data = lowByte(sensorValue);
  SPI.transfer(data);           // alternate: shiftOut(MOSI, SCK, MSBFIRST, data);
  // set SS pin high, completing 16-bit transfer to DAC
  digitalWrite(slaveSelectPin, HIGH);
}
