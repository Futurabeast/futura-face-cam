#include <WiFi.h>
#include "esp_camera.h"
#include <AsyncTCP.h>
#include <AutoConnect.h>
#include <ESPAsyncWebServer.h>
#include "esp_http_server.h"
#include "ArduinoOTA.h"
#include <Preferences.h>
#include <arduino-timer.h>
#include <FastLED.h>

#define STR_HELPER(x) #x
#define STR(x) STR_HELPER(x)

class FuturaFaceTracker {
    public:
        void init();
        void loop();
        
        void configureCamera();
        void initMDNS();
        void initServer();
        void initOTA();
        void initStreamServer();
        bool initCamera();
        void webRoutes();
        void onConnect(IPAddress& clientIP);
        void statusHandler(AsyncWebServerRequest *request);
        void setFlashHandler(AsyncWebServerRequest *request);
        void loadEprom();

        static esp_err_t streamHandler(httpd_req_t *req);
        String getDeviceName();
        uint16_t getDeviceId();

        CRGB leds[1];

    private:
        WebServer portalServer;
        AutoConnect *portal;
        AutoConnectConfig *apConfig;
        camera_config_t cameraConfig;
        httpd_handle_t streamServer;
        AsyncWebServer *webServer;
        Preferences preferences;
     
        Timer<1, millis, FuturaFaceTracker*> wifiTimer;

        uint16_t battery;
        uint8_t flash;
};