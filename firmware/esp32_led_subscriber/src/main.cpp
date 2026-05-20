#include "wifi_helpers.h"
#include "ros_helpers.h"

#include <Arduino.h>
#include "WiFi.h"
#include <std_msgs/msg/bool.h>
#include <led_control_msgs/msg/led_status.h>

const int onboard_led_pin = 2;
const int red_led_pin = 21;
const int green_led_pin = 22;
const int yellow_led_pin = 23;

led_control_msgs__msg__LedStatus led_msg;

void subscription_callback(const void *msgin)
{
  const led_control_msgs__msg__LedStatus *msg =
      (const led_control_msgs__msg__LedStatus *)msgin;

  bool is_any_led_on = msg->red || msg->green || msg->yellow;

  digitalWrite(onboard_led_pin, is_any_led_on ? HIGH : LOW);
  digitalWrite(red_led_pin, msg->red ? HIGH : LOW);
  digitalWrite(green_led_pin, msg->green ? HIGH : LOW);
  digitalWrite(yellow_led_pin, msg->yellow ? HIGH : LOW);

  led_msg.red = msg->red;
  led_msg.green = msg->green;
  led_msg.yellow = msg->yellow;
}

void setup()
{
  pinMode(onboard_led_pin, OUTPUT);
  pinMode(red_led_pin, OUTPUT);
  pinMode(green_led_pin, OUTPUT);
  pinMode(yellow_led_pin, OUTPUT);
  digitalWrite(onboard_led_pin, LOW);
  digitalWrite(red_led_pin, LOW);
  digitalWrite(green_led_pin, LOW);
  digitalWrite(yellow_led_pin, LOW);

  Serial.begin(115200);

  wifi_setup(WIFI_SSID, WIFI_PASS);
  micro_ros_setup(WIFI_SSID, WIFI_PASS, AGENT_IP, AGENT_PORT, "esp32_node");
  ros_publisher_init("led_state");
  ros_subscription_init("led_cmd", subscription_callback);
}

void loop()
{
  ros_publish(led_msg);
  ros_subscription();
}
