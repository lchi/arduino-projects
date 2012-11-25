int roughPins[] = {2,3,4,5,6,7,8,9};
int finePins[] = {13,10,11,12};

const int ROUGH_PINS = 8;
const int FINE_PINS = 4;

int temperaturePin = 0;
                              
void setup() {
  _setupPins(roughPins, ROUGH_PINS);
  _setupPins(finePins, FINE_PINS);
}

void _setupPins(int* arr, int len) {  
  for(int i = 0; i < len; i++){
      pinMode(arr[i],OUTPUT);
  }
  // debugging
  Serial.begin(9600);
}

float getVoltage(int pin) {
  // const conversion from 0-5 to 0-1024
  return (analogRead(pin) * .004882814);
}

void displayTemp (float temp) {
  for (int i = 0; i < ROUGH_PINS; i++) {
    if (temp > (10*(i+1))) {
      digitalWrite(roughPins[i], HIGH);
    } else {
      digitalWrite(roughPins[i], LOW);
    }
  }

  temp = int(temp) % 10;  
  for (int i = 0; i < FINE_PINS; i++) {
    if (temp > (2*(i+1))) {
      digitalWrite(finePins[i], HIGH);
    } else {
      digitalWrite(finePins[i], LOW);
    }
  }  
  
}

void loop(){
  float temperature = getVoltage(temperaturePin);
  temperature = (((temperature - .5) * 100) * 1.8) + 32;
  Serial.println(temperature);
  displayTemp(temperature);
  delay(1000);  
}
