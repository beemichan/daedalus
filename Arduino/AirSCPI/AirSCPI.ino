/* CO2, Temperature, Humidity Sensor with SCPI commands TEST 2
 *  Testing with SCPI, slow incorporation
 *  Emiko Ito, with example software from Sensiron AG
 */

#include "Arduino.h"
#include "Vrekrer_scpi_parser.h"
#include "SensirionI2CScd4x.h"
#include "Wire.h"

SCPI_Parser my_inst;
SensirionI2CScd4x scd4x;
uint16_t error;
uint16_t co2 = 0;
float temperature = 1;
float humidity = 2;

void setup(){
  my_inst.RegisterCommand(F("ID?"), &identify);
  my_inst.RegisterCommand(F("Co2"), &getCO2);
  my_inst.RegisterCommand(F("Temp"), &getTemp);
  my_inst.RegisterCommand(F("Humi"), &getHumi);

  Serial.begin(9600);
  Wire.begin();
  scd4x.begin(Wire);
  Serial.println("Waiting for first measurement...");
}

void loop(){
  error = scd4x.readMeasurement(co2, temperature, humidity);
  my_inst.ProcessInput(Serial, "\r\n");
}

void identify (SCPI_C commands, SCPI_P parameters, Stream& interface) {
  interface.println(F("Daedalus Air Quality Sensor."));
}

void getCO2 (SCPI_C commands, SCPI_P parameters, Stream& interface) {
  Serial.print("CO2: ");
  interface.println(co2);
}

void getTemp (SCPI_C commands, SCPI_P parameters, Stream& interface) {
  Serial.print("TEMP: ");
  interface.println(temperature);
}

void getHumi (SCPI_C commands, SCPI_P parameters, Stream& interface) {
  Serial.print("HUMI: ");
  interface.println(humidity);
}
