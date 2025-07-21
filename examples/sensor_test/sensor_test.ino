#include <FSS15.h>
#include <Wire.h>

FSS15 sun_sensor(0x50, &Wire);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  while (!Serial) delay(50);

  Serial.println("Starting FSS15 Testing");
  Wire.begin();
  sun_sensor.init();
}

void loop()
{
  while (!sun_sensor.sample_wait());
  sun_sensor.read_regmap();
  Serial.print("Model:\t\t"); Serial.println(sun_sensor.model, HEX);
  Serial.print("Version:\t"); Serial.println(sun_sensor.software_version, HEX);
  Serial.print("Temperature:\t"); Serial.print(sun_sensor.temperature * 0.03125); Serial.println("C");
  Serial.print("Samples:\t"); Serial.println(sun_sensor.sample_count);
  Serial.print("PdSum:\t\t"); Serial.print(sun_sensor.pd_sum); Serial.println("mA");
  Serial.print("Control1:\t"); Serial.println(sun_sensor.control1, HEX);
  Serial.print("Control2:\t"); Serial.println(sun_sensor.control2, HEX);
  Serial.print("Status:\t\t"); Serial.println(sun_sensor.status, HEX);
  Serial.print("Alpha:\t\t"); Serial.print(sun_sensor.alpha); Serial.println(" degrees");
  Serial.print("Beta:\t\t"); Serial.print(sun_sensor.beta); Serial.println(" degrees");
}