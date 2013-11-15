
// constants won't change. They're used here to 
// set pin numbers:
const int buttonPin = A0;     // the number of the button pin
const int ledPin =  A5;      // the number of the LED pin

// variables will change:
int buttonState = 0;         // variable for reading the pushbutton status

void setup() {
  // initialize the LED pin as an output:
  pinMode(ledPin, OUTPUT);
  // initialize the button pin as an input:
  pinMode(buttonPin, INPUT);
  // set button pin to HIGH to enable built-in pull-up (so there is 
  // no need to use resistor between button and arduino)
  digitalWrite(buttonPin, HIGH);
}

void loop(){
  // read the state of the pushbutton value:
  buttonState = digitalRead(buttonPin);

  // check if the pushbutton is pressed.
  // if it is, the buttonState is HIGH:
  if (buttonState != HIGH) {     
    // turn LED on:    
    digitalWrite(ledPin, HIGH);  
  } 
  else {
    // turn LED off:
    digitalWrite(ledPin, LOW); 
  }

}
