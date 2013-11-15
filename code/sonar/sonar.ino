#include <Bridge.h>
#include <Temboo.h>
#include "TemboAccount.h"


// For additional security and reusability, you could
// use #define statements to specify these values in a .h file.

const String TWITTER_ACCESS_TOKEN = "2196476876-0qV8yVXzXZqUhkpZCDRj5LLmU35Pc5PT426nH2r";
const String TWITTER_ACCESS_TOKEN_SECRET = "h8AVVJsvphVT1h1jBIMAoyqeGJdJHIDpN4w1RMJGWckaf";
const String TWITTER_CONSUMER_KEY = "TSlbBvROhyLeXfKugoelYg";
const String TWITTER_CONSUMER_SECRET = "6VQnvhRiSruX58vLRQ78WdAHZBMwwlfRxRVGDbdc";

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
  long duration, cm;

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
          StatusesUpdateChoreo.setAppKeyName(TEMBOO_APP_KEY_NAME);
          StatusesUpdateChoreo.setAppKey(TEMBOO_APP_KEY);
          
          // identify the Temboo Library choreo to run (Twitter > Tweets > StatusesUpdate)
          StatusesUpdateChoreo.setChoreo("/Library/Twitter/Tweets/StatusesUpdate");
          
          StatusesUpdateChoreo.addInput("AccessToken", TWITTER_ACCESS_TOKEN);
          StatusesUpdateChoreo.addInput("AccessTokenSecret", TWITTER_ACCESS_TOKEN_SECRET);
          StatusesUpdateChoreo.addInput("ConsumerKey", TWITTER_CONSUMER_KEY);
          StatusesUpdateChoreo.addInput("ConsumerSecret", TWITTER_CONSUMER_SECRET);
         
          // and the tweet we want to send
          StatusesUpdateChoreo.addInput("StatusUpdate", tweetText);
          
          unsigned int returnCode = StatusesUpdateChoreo.run();
          
          // a return code of zero (0) means everything worked
          if (returnCode == 0) {
              Serial.println("Success! Tweet sent!");
          } else {
          // a non-zero return code means there was an error
          // read and print the error message
          while (StatusesUpdateChoreo.available()) {
            char c = StatusesUpdateChoreo.read();
          Serial.print(c);
           }
          } 
          StatusesUpdateChoreo.close();

          // do nothing for the next 90 seconds
          Serial.println("Waiting...");
          delay(90000);

          } else {
            Serial.println("We don't like flooding");
          }
          
        } else {
          
          Serial.println(cm);
          
         
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
