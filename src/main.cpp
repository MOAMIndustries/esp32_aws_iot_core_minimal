#include <arduino.h>
#include "../secrets/wifi_credentials.h"
#include "parameters.h"
#include "esp_log.h"
#include "WiFi.h"

bool connectWifi(){
    // Connects to the Wifi network with the credentials stored in /secrets/wifi_credentials.h"
    // Returns true on success, false on failure
    // Paramters for timeout periods can be applied

    WiFi.begin(WIFI_SSID, WIFI_SSID_PW);
    int checksPerConnectionAttempt = 10;
    int timeout_ms = WIFI_TIMEOUT_SECONDS * 1000;
    int check_period = timeout_ms / checksPerConnectionAttempt;
    int checkCount = 0;
    
    while (
        WiFi.status() != WL_CONNECTED && 
        checkCount < checksPerConnectionAttempt
    ) {
        delay(check_period);
        log_i("Establishing connection to WiFi..");

        checkCount++;
    }
    if (WiFi.status() != WL_CONNECTED){
        log_w("Could not connect to %s",WIFI_SSID);
        return false;
    }
    log_i("Connected to network %s",WIFI_SSID);
    return true;
}

void setup(){
    esp_log_level_set("connectWifi", ESP_LOG_DEBUG);        // set all components to ERROR level
    Serial.begin(BAUD_RATE);
    log_i("Initialising");
    
    if (connectWifi()){
        Serial.print("Connected");
    }
    else{
        Serial.print("Connection failed");
    }
}

void loop(){
    
}