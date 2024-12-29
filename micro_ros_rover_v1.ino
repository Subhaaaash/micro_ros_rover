#include <micro_ros_arduino.h>
#include <stdio.h>
#include <rcl/rcl.h>
#include <rcl/error_handling.h>
#include <rclc/rclc.h>
#include <rclc/executor.h>
#include <geometry_msgs/msg/twist.h>
#include <ESP32Servo.h>

static const int servoPin1 = 13;
static const int servoPin2 = 12;
static const int servoPin3 = 14;
static const int servoPin4 = 27;

Servo servo1, servo2, servo3, servo4;


void stop() {
    servo1.write(88);
    servo2.write(87);
    servo3.write(88);
    servo4.write(88);
    Serial.println("stopped");
}

void front() {
    servo1.write(60);
    servo2.write(60);
    servo3.write(120);
    servo4.write(120);
    Serial.println("forward");
}

void back() {
    servo1.write(120);
    servo2.write(120);
    servo3.write(60);
    servo4.write(60);
    Serial.println("backward");
}

void right() {
    servo1.write(120);
    servo2.write(120);
    servo3.write(120);
    servo4.write(120);
    Serial.println("right");
}

void left() {
    servo1.write(60);
    servo2.write(60);
    servo3.write(60);
    servo4.write(60);
    Serial.println("left");
}

rcl_subscription_t subscriber;
geometry_msgs__msg__Twist msg;
rclc_support_t support;
rcl_allocator_t allocator;
rcl_node_t node;
rclc_executor_t executor;

#if defined(LED_BUILTIN)
#define LED_PIN LED_BUILTIN
#else
#define LED_PIN 02
#endif

#define RCCHECK(fn) { rcl_ret_t temp_rc = fn; if((temp_rc != RCL_RET_OK)){error_loop();}}
#define RCSOFTCHECK(fn) { rcl_ret_t temp_rc = fn; if((temp_rc != RCL_RET_OK)){}}

void error_loop() {
    while (1) {
        digitalWrite(LED_PIN, !digitalRead(LED_PIN));
        delay(100);
    }
}

void subscription_callback(const void *msg_in) {
    // Cast received message to geometry_msgs__msg__Twist
    const geometry_msgs__msg__Twist *msg = (const geometry_msgs__msg__Twist *)msg_in;

    // Copy the received message to the global variable
    ::msg = *msg;

    //uncomment the following lines to debug.

    //Serial.print("Linear Velocity: x = ");
    //Serial.print(msg->linear.x);
    //Serial.print(", y = ");
    //Serial.print(msg->linear.y);
    //Serial.print(", z = ");
    //Serial.println(msg->linear.z);

    //Serial.print("Angular Velocity: x = ");
    //Serial.print(msg->angular.x);
    //Serial.print(", y = ");
    //Serial.print(msg->angular.y);
    //Serial.print(", z = ");
    //Serial.println(msg->angular.z);
    //Serial.println("-------------------------");
}

void setup() {
    servo1.attach(servoPin1);
    servo2.attach(servoPin2);
    servo3.attach(servoPin3);
    servo4.attach(servoPin4);

    set_microros_wifi_transports("your_SSID", "network_password", "192.168.0.110(your host ros2 device ip)", 8888); //fill in your network credentials

    pinMode(LED_PIN, OUTPUT);
    digitalWrite(LED_PIN, HIGH);

    Serial.begin(115200);
    delay(2000);

    allocator = rcl_get_default_allocator();

    // Create init_options
    RCCHECK(rclc_support_init(&support, 0, NULL, &allocator));

    // Create node
    RCCHECK(rclc_node_init_default(&node, "micro_ros_arduino_wifi_node", "", &support));

    // Create subscriber
    RCCHECK(rclc_subscription_init_default(
        &subscriber,
        &node,
        ROSIDL_GET_MSG_TYPE_SUPPORT(geometry_msgs, msg, Twist),
        "/cmd_vel"));

    // Initialize executor
    RCCHECK(rclc_executor_init(&executor, &support.context, 1, &allocator));
    RCCHECK(rclc_executor_add_subscription(&executor, &subscriber, &msg, &subscription_callback, ON_NEW_DATA));
}

void loop() {
    // Spin the executor to handle callbacks
    rclc_executor_spin_some(&executor, RCL_MS_TO_NS(100));

    // Control logic based on msg values(comment these lines to debug)
    
    if (msg.linear.x > 0) {
        back();
    } else if (msg.linear.x < 0) {
        front();
    } else if (msg.angular.z > 0) {
        left();
    } else if (msg.angular.z < 0) {
        right();
    } else {
        stop();
    }
}
