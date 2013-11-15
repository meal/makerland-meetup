#include <Bridge.h>
#include <Temboo.h>
#include "TemboAccount.h"



// For additional security and reusability, you could
// use #define statements to specify these values in a .h file.

const String TWITTER_ACCESS_TOKEN = "your-twitter-access-token";
const String TWITTER_ACCESS_TOKEN_SECRET = "your-twitter-access-token-secret";
const String TWITTER_CONSUMER_KEY = "your-twitter-consumer-key";
const String TWITTER_CONSUMER_SECRET = "your-twitter-consumer-secret";

int numRuns = 1;   // execution count, so this sketch doesn't run forever
int maxRuns = 1;  // the max number of times the Twitter Update Choreo should run


// this constant won't change.  It's the pin number
// of the sensor's output:
const int pingPin = 7;

void setup() {
  // initialize serial communication:
  Serial.begin(9600);
}

void loop()
{
  // establish variables for duration of the ping, 
  // and the distance result in inches and centimeters:
  long duration, inches, cm;

  // The PING))) is triggered by a HIGH pulse of 2 or more microseconds.
  // Give a short LOW pulse beforehand to ensure a clean HIGH pulse:
  pinMode(pingPin, OUTPUT);
  digitalWrite(pingPin, LOW);
  delayMicroseconds(2);
  digitalWrite(pingPin, HIGH);
  delayMicroseconds(5);
  digitalWrite(pingPin, LOW);

  // The same pin is used to read the signal from the PING))): a HIGH
  // pulse whose duration is the time (in microseconds) from the sending
  // of the ping to the reception of its echo off of an object.
  pinMode(pingPin, INPUT);
  duration = pulseIn(pingPin, HIGH);

  cm = microsecondsToCentimeters(duration);
  
  if (cm <= 7) {
    if (numRuns <= maxRuns) {
          String tweetText("Someone came to close. Aayyyy!");
          TembooChoreo StatusesUpdateChoreo;
          
          StatusesUpdateChoreo.begin();
          
          StatusesUpdateChoreo.setAccountName(TEMBOO_ACCOUNT);
          

    }
  } else {
    
  }

  delay(100);
}

long microsecondsToInches(long microseconds)
{
  // See: http://www.parallax.com/dl/docs/prod/acc/28015-PING-v1.3.pdf
  return microseconds / 74 / 2;
}

long microsecondsToCentimeters(long microseconds)
{
  // The speed of sound is 340 m/s or 29 microseconds per centimeter.
  // The ping travels out and back, so to find the distance of the
  // object we take half of the distance travelled.
  return microseconds / 29 / 2;
}
