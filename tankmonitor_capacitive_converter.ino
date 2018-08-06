/*
 * Controlling and looping through a CD74HC4067's channel outputs
 *
 *

 *
*/

#include <CD74HC4067.h>
#include <math.h>
#include <movingAvg.h>

               // s0 s1 s2 s3
CD74HC4067 mux_A(4, 5, 6, 7);  // create a new CD74HC4067 object with its four control pins
CD74HC4067 mux_B(9, 10, 11, 12);  // create a new CD74HC4067 object with its four control pins

const int mux_A_disable = 3; //identify the pins that disable the mux boards
const int mux_B_disable = 8;

movingAvg AvgA1(50); // set the moving average window to 50 samples. this feature works well when ran with an asynchronous clocking for reporting of data.
movingAvg AvgA2(50);
movingAvg AvgB1(50);
movingAvg AvgB2(50);

//analog sensor pins for tanks
const int tank_A1 = A0;
const int tank_A2 = A1;
const int tank_B1 = A2;
const int tank_B2 = A3;


//values for voltage from adac
int tank_A1_voltage;
int tank_A1_average;
int tank_A1_percent;

int tank_A2_voltage;
int tank_A2_average;
int tank_A2_percent;

int tank_B1_voltage;
int tank_B1_average;
int tank_B1_percent;

int tank_B2_voltage;
int tank_B2_average;
int tank_B2_percent;

int tank_A_combined;
int tank_A_resistor;

int tank_B_combined;
int tank_B_resistor;




unsigned long startMillis;  //clocking for asynchronus operation - last start of seconds
unsigned long currentMillis; //current status of clock
const unsigned long period = 1000;  //milliseconds to wait before executing operation again

void setup()
{
    pinMode(mux_A_disable, OUTPUT);
    pinMode(mux_B_disable, OUTPUT);
    digitalWrite(mux_A_disable, LOW);
    digitalWrite(mux_B_disable, LOW);
    AvgA1.begin();
    AvgA2.begin();
    AvgB1.begin();
    AvgB2.begin();
    startMillis = millis();  //initial start time
    Serial.begin(9600);
}


// Resistor map calibration looks something like this. This is just a comment for reference, for the V1 board I made. Hopefully I don't ever have to make another one.
// A == 15-238, 14-225, 13-213, 12-200, 11-190, 10-178, 9-166, 8-155, 7-142, 6-131, 5-118, 4-106, 3-93, 2-81, 1-68, 0-56
// B == 15-239, 14-226, 13-214, 12-201, 11-190, 10-178, 9-167, 8-155, 7-143, 6-132, 5-119, 4-107, 3-93, 2-82, 1-69, 0-56

void loop()
{   
    tank_A1_voltage = AvgA1.reading(analogRead(tank_A1));
    tank_A2_voltage = AvgA2.reading(analogRead(tank_A2));
    tank_B1_voltage = AvgB1.reading(analogRead(tank_B1));
    tank_B2_voltage = AvgB2.reading(analogRead(tank_B2));
    



    //49 day rollover for millis() works. unsigned long with subtraction rollover doesn't care, because our time frame for counting is very small. if we were counting large timespans
    //like say more than 49 days, we'd be in trouble and it would spiral into never land execution.
    //https://forum.arduino.cc/index.php?topic=503368.0
    currentMillis = millis();  //get the current "time" (actually the number of milliseconds since the program started)
      if (currentMillis - startMillis >= period)  //test whether the period has elapsed
      {
        //do your stuff that you want to do occasionally
        tank_A1_percent = map(tank_A1_voltage, 0, 1023, 0, 100);
        tank_A2_percent = map(tank_A2_voltage, 0, 1023, 0, 100);
        tank_B1_percent = map(tank_B1_voltage, 0, 1023, 0, 100);
        tank_B2_percent = map(tank_B2_voltage, 0, 1023, 0, 100);
        
        tank_A_combined = round((tank_A1_voltage + tank_A2_voltage)/2);
        tank_B_combined = round((tank_B1_voltage + tank_B2_voltage)/2);
        
        tank_A_resistor = map(tank_A_combined, 0, 1023, 15, 0);
        tank_B_resistor = map(tank_B_combined, 0, 1023, 15, 0);
    
        mux_A.channel(tank_A_resistor); //setting these mux channels quicky seems to add a lot of electrical noise to the circuit. I'm pretty sure updating once a second will be fine.
        mux_B.channel(tank_B_resistor); //I noticed a voltage ringing effect when switching channels, which I think is a field collapse and feeds back through the dac. 
                                        //The monitored voltages are pretty darn solid when switching the resistor simulator at this speed.
        JSONSerialStatus(); 
        
        startMillis = currentMillis;  //IMPORTANT to save the start time of the operation(s) that were called.
      }
    
}

void JSONSerialStatus() {
      Serial.print(
    "{"
    "\"TankA1\":{"
    "\"Voltage\":\""
    );
    Serial.print(tank_A1_voltage); //tank A1 voltage
    Serial.print(
    "\","
    "\"Percent\":\""
    );
    Serial.print(tank_A1_percent); //tank A1 full by percentage
    Serial.print(
    "\","
    "\"ResistorMap\":\""
    );
    Serial.print(tank_A_resistor); //tank A1 resistor map selected
    Serial.print(
    "\""
    "},"
    "\"TankA2\":{"
    "\"Voltage\":\""
    );
    Serial.print(tank_A2_voltage); //tank A2 voltage
    Serial.print(
    "\","
    "\"Percent\":\""
    );
    Serial.print(tank_A2_percent); //tank A2 full by percentage
    Serial.print(
    "\","
    "\"ResistorMap\":\""
    );
    Serial.print(tank_A_resistor); //tank A2 resistor map selected
    Serial.print(
    "\""
    "},"
    "\"TankB1\":{"
    "\"Voltage\":\""
    );
    Serial.print(tank_B1_voltage); //tank B1 voltage
    Serial.print(
    "\","
    "\"Percent\":\""
    );
    Serial.print(tank_B1_percent); //tank B1 full by percentage
    Serial.print(
    "\","
    "\"ResistorMap\":\""
    );
    Serial.print(tank_B_resistor); //tank B1 resistor map selected
    Serial.print(
    "\""
    "},"
    "\"TankB2\":{"
    "\"Voltage\":\""
    );
    Serial.print(tank_B2_voltage); //tank B2 voltage
    Serial.print(
    "\","
    "\"Percent\":\""
    );
    Serial.print(tank_B2_percent); //tank B2 full by percentage
    Serial.print(
    "\","
    "\"ResistorMap\":\""
    );
    Serial.print(tank_B_resistor); //tank B2 resistor map selected
    Serial.print(
    "\""
    "}"
    "}"
    );
    Serial.println();
}


