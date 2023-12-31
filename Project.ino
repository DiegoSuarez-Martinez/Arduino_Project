// include the library code:
#include <LiquidCrystal.h>
#include <dht_nonblocking.h>
#define DHT_SENSOR_TYPE DHT_TYPE_11

// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(7, 8, 9, 10, 11, 12);

static const int DHT_SENSOR_PIN = 2;
DHT_nonblocking dht_sensor(DHT_SENSOR_PIN, DHT_SENSOR_TYPE);

void setup() {
  // Initialize the serial port.

  Serial.begin(9600);

  // set up the LCD's number of columns and rows:

  lcd.begin(16, 2);

  

  
}

// Poll for a measurement, keeping the state machine alive.
// Returns true if a measurement is available.

static bool measure_environment(float *temperature, float *humidity) {
  static unsigned long measurement_timestamp = millis();

  // Measure once every four seconds.

  if (millis() - measurement_timestamp > 3000ul) {
    if (dht_sensor.measure(temperature, humidity) == true) {
      measurement_timestamp = millis();
      return (true);
    }
  }
  return (false);
}

// Main program loop.

void loop()

{
  delay(1000);
  float temperature;

  float humidity;

  // Measure temperature and humidity.
  // If the functions returns true, then a measurement is available.

  if (measure_environment(&temperature, &humidity) == true)

  {

    Serial.print("T = ");
    Serial.print(temperature, 1);
    Serial.print(" deg. C, H = ");
    Serial.print(humidity, 1);
    Serial.println("%");
    // Print a message to the LCD.
    lcd.print(temperature);
    //lcd.println(humidity);    
  }
}
