int led = D7;  // The on-board LED
int ldrpin = A0; // the pin that gets data from our sensor

// set some variables about your sensor
int ldrReading = 0;
int ldrMaxReading = 5000; // change this value to suit your sensor

String payload = "";

// variables about our board
String deviceId = "2b0030000647343232363230"; // **** change this to your photon's id
String deviceName = "wombat_green"; // **** change this to your photon's name

// ----- runs once to set everything up
void setup()
{
    pinMode(led, OUTPUT);
    pinMode(ldrpin, INPUT);
    
    Particle.variable("light", ldrReading); // this exposes our variable to the cloud
}

// ----- the main function - runs forever
void loop()
{
    digitalWrite(led, HIGH);   // Turn ON the LED

    ldrReading = analogRead(ldrpin); // get the light reading
    
    Particle.publish("light reading", (String)ldrReading); // so we can see it on our dashboard
    
    int ldrReading_Convert = (ldrReading/ldrMaxReading*255); // change the 3000 to the max value for your sensor
    
    publishData(ldrReading_Convert, "Light"); // publishes the date **** change the text to suit your sensor

    digitalWrite(led, LOW); // Turn OFF the LED
    delay(300000); // Wait for 5 minutes before the next reading
}

// ----- sends the information to our database via the cloud
void publishData(int reading, String readingType)
{
    String reading_string = (String)reading;
    payload = "{'device_id': '";
    payload += deviceId;
    payload += "' , 'type': '";
    payload += readingType;
    payload += "' , 'value': '";
    payload += reading_string;
    payload += "'}";
   
    Particle.publish("disdata", payload, 60, PRIVATE);
    
    delay(60000); // wait 1 minute

}
