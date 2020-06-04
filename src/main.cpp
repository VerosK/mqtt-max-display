#include <Arduino.h>
#include <Homie.h>
#include "dot-display.hpp"

#define FIRMWARE_NAME "dot-display"
#define FIRMWARE_VERSION "0.0.5"

DotDisplay the_display(/* clock*/ D5, /*data*/ D7, /*cs=*/D8);
HomieNode textNode("text", "string");

void onHomieEvent(const HomieEvent &event)
{
  switch (event.type)
  {
  case HomieEventType::STANDALONE_MODE:
    the_display.drawSmallText("standalone");
    break;
  case HomieEventType::CONFIGURATION_MODE:
    the_display.drawSmallText("config");
    break;
  case HomieEventType::WIFI_CONNECTED:
    the_display.drawSmallText("on WiFi");
    break;
  case HomieEventType::WIFI_DISCONNECTED:
    the_display.drawSmallText("no WiFi");
    break;
  case HomieEventType::MQTT_READY:
    the_display.drawSmallText("ready");
    break;
  case HomieEventType::MQTT_DISCONNECTED:
    the_display.drawSmallText("no data");
    break;
  case HomieEventType::OTA_STARTED:
    the_display.drawSmallText("updating");
    break;
  case HomieEventType::OTA_SUCCESSFUL:
    the_display.drawSmallText("restarting");
    break;
  case HomieEventType::OTA_FAILED:
    the_display.drawSmallText("failed");
    break;

  case HomieEventType::OTA_PROGRESS:
    the_display.uploadProgress();
    break;
  default:
    break;
  }
}

bool setIntensityHandler(const HomieRange &range, const String &value)
{
  Homie.getLogger() << "IntensityReceived: start" << endl;
  uint8_t new_intensity;
  the_display.setIntensity(100);
  for (unsigned n = 0; n < value.length(); n++)
  {
    if (value[n] > '9')
      return true;
    if (value[n] < '0')
      return true;
  }
  if (value.toInt() > 255)
    return true;
  new_intensity = value.toInt();

  textNode.setProperty("intensity").send(String(new_intensity));
  the_display.setIntensity(new_intensity);
  return true;
}

bool setTextHandler(const HomieRange &range, const String &value)
{
  Homie.getLogger() << "TextReceived: start" << endl;

  String substr = value.substring(0, 32);

  the_display.drawText(substr.c_str());
  return true;
}

void setup()
{
  the_display.begin();
  Serial.begin(9600);
  Serial << endl
         << endl;

  // Homie.getLogger() << "wifiReset: start" << endl;

  //WiFi.disconnect();
  //WiFi.persistent(false);
  //WiFi.mode(WIFI_OFF);
  //Homie.getLogger() << "wifiReset: done" << endl;

  // Homie.disableLogging();

  the_display.drawSmallText("booting");
  Homie_setFirmware(FIRMWARE_NAME, FIRMWARE_VERSION);
  textNode.advertise("intensity").settable(setIntensityHandler);
  textNode.advertise("text").settable(setTextHandler);
  Homie.onEvent(onHomieEvent);
  Homie.setup();
}

void loop()
{
  Homie.loop();
  the_display.loop();
}