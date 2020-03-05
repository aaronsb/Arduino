#include <WiFi.h>
#include <WiFiClient.h>
#include <WiFiServer.h>
#include <WiFiUdp.h>

#include <PubSubClient.h>

boolean debug = true;

const char* ssid = "xxx";
const char* pass = "xxx";
const char* broker = "cpanel.broccolibus.local";
const char* brokerUser = "esp32-bus-1";
const char* brokerPass = "xxx";

const char* inTopicRelay1 = "bus/lighting/cmnd/relay1/power";
const char* stateTopicRelay1 = "bus/lighting/stat/relay1/power";

const char* inTopicRelay2 = "bus/lighting/cmnd/relay2/power";
const char* stateTopicRelay2 = "bus/lighting/stat/relay2/power";

const char* inTopicRelay3 = "bus/lighting/cmnd/relay3/power";
const char* stateTopicRelay3 = "bus/lighting/stat/relay3/power";

const char* inTopicRelay4 = "bus/lighting/cmnd/relay4/power";
const char* stateTopicRelay4 = "bus/lighting/stat/relay4/power";

const char* inTopicRelay5 = "bus/lighting/cmnd/relay5/power";
const char* stateTopicRelay5 = "bus/lighting/stat/relay5/power";

const char* inTopicRelay6 = "bus/lighting/cmnd/relay6/power";
const char* stateTopicRelay6 = "bus/lighting/stat/relay6/power";

const char* inTopicRelay7 = "bus/lighting/cmnd/relay7/power";
const char* stateTopicRelay7 = "bus/lighting/stat/relay7/power";

const char* inTopicRelay8 = "bus/lighting/cmnd/relay8/power";
const char* stateTopicRelay8 = "bus/lighting/stat/relay8/power";

const char* inTopicRelay9 = "bus/lighting/cmnd/relay9/power";
const char* stateTopicRelay9 = "bus/lighting/stat/relay9/power";

const char* inTopicRelay10 = "bus/lighting/cmnd/relay10/power";
const char* stateTopicRelay10 = "bus/lighting/stat/relay10/power";

const char* inTopicRelay11 = "bus/lighting/cmnd/relay11/power";
const char* stateTopicRelay11 = "bus/lighting/stat/relay11/power";

const char* inTopicRelay12 = "bus/lighting/cmnd/relay12/power";
const char* stateTopicRelay12 = "bus/lighting/stat/relay12/power";

char* stateOn = "ON";
char* stateOff = "OFF";

boolean m_relay1_state = false;
boolean m_relay2_state = false;
boolean m_relay3_state = false;
boolean m_relay4_state = false;
boolean m_relay5_state = false;
boolean m_relay6_state = false;
boolean m_relay7_state = false;
boolean m_relay8_state = false;
boolean m_relay9_state = false;
boolean m_relay10_state = false;
boolean m_relay11_state = false;
boolean m_relay12_state = false;

WiFiClient espClient;
PubSubClient client(espClient);

long currentTime, lastTime;
int count = 0;

//Pins for the Relays
int relay1 = 38;
int relay2 = 39;
int relay3 = 34;
int relay4 = 35;
int relay5 = 32;
int relay6 = 33;
int relay7 = 25;
int relay8 = 26;
int relay9 = 27;
int relay10 = 14;
int relay11 = 12;
int relay12 = 13;

void reconnect() {
    while (!client.connected()) {
        if (debug) {
            Serial.print("\nConnecting to ");
            Serial.println(broker);
        }

        if (client.connect("brokerConnection", brokerUser, brokerPass)) {
            client.subscribe(inTopicRelay1);
            client.subscribe(inTopicRelay2);
            client.subscribe(inTopicRelay3);
            client.subscribe(inTopicRelay4);
            client.subscribe(inTopicRelay5);
            client.subscribe(inTopicRelay6);
            client.subscribe(inTopicRelay7);
            client.subscribe(inTopicRelay8);
            client.subscribe(inTopicRelay9);
            client.subscribe(inTopicRelay10);
            client.subscribe(inTopicRelay11);
            client.subscribe(inTopicRelay12);
            if (debug) {
                Serial.print("\nConnected to ");
                Serial.println(broker);
                Serial.print("topic ==>");
            }
        } else {
            if (debug) {
                Serial.print("\nTrying again ...");
            }
            delay(5000);
        }
    }
}

void setupWifi() {
    delay(100);
    if (debug) {
        Serial.print("\nConnecting to ");
        Serial.println(ssid);
    }

    WiFi.begin(ssid, pass);

    while (WiFi.status() != WL_CONNECTED) {
        delay(100);
        Serial.print("-");
    }

    if (debug) {
        Serial.print("\nConnected!! **** ");
        Serial.println(ssid);
    }
}

void callback(char* topic, byte* payload, unsigned int length) {
    String payloadString;
    for (uint8_t i = 0; i < length; i++) {
        payloadString.concat((char)payload[i]);
    }
    if (debug) {
        Serial.print("Received message: ");
        Serial.println(topic);
        for (int i = 0; i < length; i++) {
            Serial.print((char)payload[i]);
        }
        Serial.println();
    }

    if (strcmp(topic, inTopicRelay1) == 0) {
        if (payloadString.equals(String(stateOn))) {
            m_relay1_state = true;
        } else if (payloadString.equals(String(stateOff))) {
            m_relay1_state = false;
        }
    }
    if (strcmp(topic, inTopicRelay2) == 0) {
        if (payloadString.equals(String(stateOn))) {
            m_relay2_state = true;
        } else if (payloadString.equals(String(stateOff))) {
            m_relay2_state = false;
        }
    }
    if (strcmp(topic, inTopicRelay3) == 0) {
        if (payloadString.equals(String(stateOn))) {
            m_relay3_state = true;
        } else if (payloadString.equals(String(stateOff))) {
            m_relay3_state = false;
        }
    }
    if (strcmp(topic, inTopicRelay4) == 0) {
        if (payloadString.equals(String(stateOn))) {
            m_relay4_state = true;
        } else if (payloadString.equals(String(stateOff))) {
            m_relay4_state = false;
        }
    }
    if (strcmp(topic, inTopicRelay5) == 0) {
        if (payloadString.equals(String(stateOn))) {
            m_relay5_state = true;
        } else if (payloadString.equals(String(stateOff))) {
            m_relay5_state = false;
        }
    }
    if (strcmp(topic, inTopicRelay6) == 0) {
        if (payloadString.equals(String(stateOn))) {
            m_relay6_state = true;
        } else if (payloadString.equals(String(stateOff))) {
            m_relay6_state = false;
        }
    }
    if (strcmp(topic, inTopicRelay7) == 0) {
        if (payloadString.equals(String(stateOn))) {
            m_relay7_state = true;
        } else if (payloadString.equals(String(stateOff))) {
            m_relay7_state = false;
        }
    }
    if (strcmp(topic, inTopicRelay8) == 0) {
        if (payloadString.equals(String(stateOn))) {
            m_relay8_state = true;
        } else if (payloadString.equals(String(stateOff))) {
            m_relay8_state = false;
        }
    }
    if (strcmp(topic, inTopicRelay9) == 0) {
        if (payloadString.equals(String(stateOn))) {
            m_relay9_state = true;
        } else if (payloadString.equals(String(stateOff))) {
            m_relay9_state = false;
        }
    }
    if (strcmp(topic, inTopicRelay10) == 0) {
        if (payloadString.equals(String(stateOn))) {
            m_relay10_state = true;
        } else if (payloadString.equals(String(stateOff))) {
            m_relay10_state = false;
        }
    }
    if (strcmp(topic, inTopicRelay11) == 0) {
        if (payloadString.equals(String(stateOn))) {
            m_relay11_state = true;
        } else if (payloadString.equals(String(stateOff))) {
            m_relay11_state = false;
        }
    }
    if (strcmp(topic, inTopicRelay12) == 0) {
        if (payloadString.equals(String(stateOn))) {
            m_relay12_state = true;
        } else if (payloadString.equals(String(stateOff))) {
            m_relay12_state = false;
        }
    }
    if (debug) {
        Serial.print("topic ==>");
        Serial.println(m_relay1_state);
    }
    setSwitchState();
    publishSwitchState();
}

// function called to turn on/off the switch
void setSwitchState() {
    if (m_relay1_state) {
        digitalWrite(relay1, LOW);
    } else {
        digitalWrite(relay1, HIGH);
    }
    if (m_relay2_state) {
        digitalWrite(relay2, LOW);
    } else {
        digitalWrite(relay2, HIGH);
    }
    if (m_relay3_state) {
        digitalWrite(relay3, LOW);
    } else {
        digitalWrite(relay3, HIGH);
    }
    if (m_relay4_state) {
        digitalWrite(relay4, LOW);
    } else {
        digitalWrite(relay4, HIGH);
    }
    if (m_relay5_state) {
        digitalWrite(relay5, LOW);
    } else {
        digitalWrite(relay5, HIGH);
    }
    if (m_relay6_state) {
        digitalWrite(relay6, LOW);
    } else {
        digitalWrite(relay6, HIGH);
    }
    if (m_relay7_state) {
        digitalWrite(relay7, LOW);
    } else {
        digitalWrite(relay7, HIGH);
    }
    if (m_relay8_state) {
        digitalWrite(relay8, LOW);
    } else {
        digitalWrite(relay8, HIGH);
    }
    if (m_relay9_state) {
        digitalWrite(relay9, LOW);
    } else {
        digitalWrite(relay9, HIGH);
    }
    if (m_relay10_state) {
        digitalWrite(relay10, LOW);
    } else {
        digitalWrite(relay10, HIGH);
    }
    if (m_relay11_state) {
        digitalWrite(relay11, LOW);
    } else {
        digitalWrite(relay11, HIGH);
    }
    if (m_relay12_state) {
        digitalWrite(relay12, LOW);
    } else {
        digitalWrite(relay12, HIGH);
    }
    publishSwitchState();
    client.loop();
}

// function called to publish the state of the switch (on/off)
void publishSwitchState() {
    if (m_relay1_state) {
        client.publish(stateTopicRelay1, stateOn, true);
    } else {
        client.publish(stateTopicRelay1, stateOff, true);
    }
    if (m_relay2_state) {
        client.publish(stateTopicRelay2, stateOn, true);
    } else {
        client.publish(stateTopicRelay2, stateOff, true);
    }
    if (m_relay3_state) {
        client.publish(stateTopicRelay3, stateOn, true);
    } else {
        client.publish(stateTopicRelay3, stateOff, true);
    }
    if (m_relay4_state) {
        client.publish(stateTopicRelay4, stateOn, true);
    } else {
        client.publish(stateTopicRelay4, stateOff, true);
    }
    if (m_relay5_state) {
        client.publish(stateTopicRelay5, stateOn, true);
    } else {
        client.publish(stateTopicRelay5, stateOff, true);
    }
    if (m_relay6_state) {
        client.publish(stateTopicRelay6, stateOn, true);
    } else {
        client.publish(stateTopicRelay6, stateOff, true);
    }
    if (m_relay7_state) {
        client.publish(stateTopicRelay7, stateOn, true);
    } else {
        client.publish(stateTopicRelay7, stateOff, true);
    }
    if (m_relay8_state) {
        client.publish(stateTopicRelay8, stateOn, true);
    } else {
        client.publish(stateTopicRelay8, stateOff, true);
    }
    if (m_relay9_state) {
        client.publish(stateTopicRelay9, stateOn, true);
    } else {
        client.publish(stateTopicRelay9, stateOff, true);
    }
    if (m_relay10_state) {
        client.publish(stateTopicRelay10, stateOn, true);
    } else {
        client.publish(stateTopicRelay10, stateOff, true);
    }
    if (m_relay11_state) {
        client.publish(stateTopicRelay11, stateOn, true);
    } else {
        client.publish(stateTopicRelay11, stateOff, true);
    }
    if (m_relay12_state) {
        client.publish(stateTopicRelay12, stateOn, true);
    } else {
        client.publish(stateTopicRelay12, stateOff, true);
    }

    client.loop();
}

void setup() {
    Serial.begin(115200);

    pinMode(relay1, OUTPUT);
    pinMode(relay2, OUTPUT);
    pinMode(relay3, OUTPUT);
    pinMode(relay4, OUTPUT);
    pinMode(relay5, OUTPUT);
    pinMode(relay6, OUTPUT);
    pinMode(relay7, OUTPUT);
    pinMode(relay8, OUTPUT);
    pinMode(relay9, OUTPUT);
    pinMode(relay10, OUTPUT);
    pinMode(relay11, OUTPUT);
    pinMode(relay12, OUTPUT);
    digitalWrite(relay1, HIGH);
    digitalWrite(relay2, HIGH);
    digitalWrite(relay3, HIGH);
    digitalWrite(relay4, HIGH);
    digitalWrite(relay5, HIGH);
    digitalWrite(relay6, HIGH);
    digitalWrite(relay7, HIGH);
    digitalWrite(relay8, HIGH);
    digitalWrite(relay9, HIGH);
    digitalWrite(relay10, HIGH);
    digitalWrite(relay11, HIGH);
    digitalWrite(relay12, HIGH);

    setupWifi();
    client.setServer(broker, 1883);
    client.setCallback(callback);
}

void loop() {
    // put your main code here, to run repeatedly:
    if (!client.connected()) {
        reconnect();
    }
    client.loop();
}
