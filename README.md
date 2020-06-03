# MAX 7219 MQTT enabled display

Based on [homie][homie-esp] framework.

## How to build.

Use PlatformIO at the moment

### How to change text:

    mosquitto_pub -h mqtt-broker -t homie/dot-display/text/text/set -m 'Hello, world'

### How to change text intensity    

    mosquitto_pub -h mqtt-broker -t homie/dot-display/text/intensity/set -m 200

# License

WTFPL

[homie-esp]: https://github.com/homieiot/homie-esp8266