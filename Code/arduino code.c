// Arduino Code

int last_beat_time = 0;
bool timer = false;
bool detector = false;
int beats_per_minute = 0;    
#define upper_threshold 518
#define lower_threshold 490    
int LED13 = 44; // The on-board Arduino LED
int sensor_value; // holds the incoming raw data. sensor_value value can range from 0-1024
int time_controller=0;
void setup() {
  pinMode(LED13, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  int value = analogRead(0);
  if (value > upper_threshold) {
    if (detector) {
      beats_per_minute = millis() - last_beat_time;
      beats_per_minute = int(60 / (float(beats_per_minute) / 1000));
      timer = false;
      detector = false;
    }
    if (timer == false) {
      last_beat_time = millis();
      timer = true;
    }
    time_controller++;
  }
  if ((value < lower_threshold) & (timer))
    detector = true;
    // display beats_per_minute
  Serial.print(beats_per_minute);
  Serial.println("BPM");

  sensor_value = analogRead(0); // Read the PulseSensor's value.
  // Assign this value to the "sensor_value" variable.
  if (sensor_value > upper_threshold) {
    // If the sensor_value is above "550", then "turn-on" Arduino's on-Board LED.
    digitalWrite(LED13, HIGH);
  } else {
    digitalWrite(LED13, LOW); //  Else, the sensor_value must be below "550", so "turn-off" this LED.
  }
  if(millis()==6000){
    time_controller=(time_controller/6)*60;
     Serial.print(time_controller);
  Serial.println(" Average BPM");
  exist(0);
  }
}
