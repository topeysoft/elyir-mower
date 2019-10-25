#include <Arduino.h>
#include "ElyirConfig.h"
#include "ElyirGPS.h"
#include "ElyirLogger.h"
#include <ElyirCompass.h>
#include "ElyirMotion.h"
#include "MegaComm.h"
#include "MowerBlade.h"
#include "HeightAdjuster.h"
#include "ElyirDataUpdater.h"
#include "ProximitySensor.h"

ElyirCompass compass;
ElyirGPS gps;
ElyirMotion motion;
MegaComm megaComm;
HeightAdjuster adjuster;
MowerBlade blade;
ElyirDataUpdater updater;
ElyirLogger logger;
ProximitySensor sensors;
// ProximitySensor sensor_center;
// ProximitySensor sensor_right;

void heightChangeCb(String height)
{
    if (height.equalsIgnoreCase(COMMAND_CUT_HEIGHT_HIGH))
    {
        logger.logLn("Setting cut height to HIGH");
        adjuster.setHighCut();
    }
    else if (height.equalsIgnoreCase(COMMAND_CUT_HEIGHT_LOW))
    {
        logger.logLn("Setting cut height to LOW");
        adjuster.setLowCut();
    }
    else if (height.equalsIgnoreCase(COMMAND_CUT_HEIGHT_MEDIUM))
    {
        logger.logLn("Setting cut height to MEDIUM");
        adjuster.setMediumCut();
    }
    else if (height.equalsIgnoreCase(COMMAND_CUT_HEIGHT_CHARGE))
    {
        logger.logLn("Setting cut height to CHARGE");
        adjuster.setChargeHeight();
    }
}
void spdChangeCb(String speedTag)
{
    if (speedTag.equalsIgnoreCase(COMMAND_SPEED_HIGH))
    {
        logger.logLn("GOING FULL SPEED");
        motion.goFullSpeed();
    }
    else if (speedTag.equalsIgnoreCase(COMMAND_SPEED_LOW))
    {
        logger.logLn("GOING HALF SPEED");
        motion.goHalfSpeed();
    }
}
void bladeChangeCb(String state)
{
    if (state.equalsIgnoreCase(COMMAND_BLADE_POWER_STATE_ON))
    {
        logger.logLn("Turning ON mower blade");
        blade.turnOn();
    }
    else if (state.equalsIgnoreCase(COMMAND_BLADE_POWER_STATE_OFF))
    {
        logger.logLn("Turning OFF mower blade");
        blade.turnOff();
    }
}
void dirChangeCb(String dir)
{
    if (dir.equalsIgnoreCase(COMMAND_FORWARD))
    {
        logger.logLn("FORWARD ");
        motion.goForward();
    }
    else if (dir.equalsIgnoreCase(COMMAND_BACKWARD))
    {
        logger.logLn("BACKWARD ");
        motion.goBackward();
    }
    else if (dir.equalsIgnoreCase(COMMAND_LEFT))
    {
        logger.logLn("LEFT ");
        motion.turnLeft();
    }
    else if (dir.equalsIgnoreCase(COMMAND_RIGHT))
    {
        logger.logLn("RIGHT ");
        motion.turnRight();
    }
    else if (dir.equalsIgnoreCase(COMMAND_STOP))
    {
        logger.logLn("STOP");
        motion.stop();
    }
    else if (dir.equalsIgnoreCase(COMMAND_SPEED_UP))
    {
        logger.logLn("SPEEDING_UP");
        motion.goFullSpeed();
    }
    else if (dir.equalsIgnoreCase(COMMAND_SLOW_DOWN))
    {
        logger.logLn("SLOWING_DOWN");
        motion.goHalfSpeed();
    }
    else if (dir.equalsIgnoreCase(COMMAND_SPINDLE))
    {
        logger.logLn("TOGGLING SPINDLE");
        // motion.();
    }
}

// void onLeftBlockedCallback()
// {
//     logger.infoLn("LEFT Obstructed!");
//     motion.foundLeftObstacle();
// }
// void onCenterBlockedCallback()
// {
//     logger.infoLn("CENTER Obstructed!");
//     motion.foundCenterObstacle();
// }
// void onRightBlockedCallback()
// {
//     logger.infoLn("RIGHT Obstructed!");
//     motion.foundRightObstacle();
// }
// void onLeftUnBlockedCallback()
// {
//     logger.verifiedLn("LEFT Obstacle cleared");
//     motion.clearedLeftObstacle();
// }
// void onCenterUnBlockedCallback()
// {
//     logger.verifiedLn("CENTER Obstacle cleared");
//     motion.clearedCenterObstacle();
// }
// void onRightUnBlockedCallback()
// {
//     logger.verifiedLn("RIGHT Obstacle cleared");
//     motion.clearedRightObstacle();
// }

void queueUpdate() {
     StaticJsonDocument<256> doc;
    JsonObject root = doc.to<JsonObject>();
    // root["location"] = "Paris";
    JsonObject location = root.createNestedObject("location");
    location["lat"] = gps.lat();
    location["lng"] = gps.lng();
    location["spd"] = gps.speedMPS();

    JsonObject heading = root.createNestedObject("heading");
    heading["cur"] = motion.getCurrentHeading();
    heading["tgt"] = motion.getTargetHeading();
    char output[256];
    serializeJson(doc, output);//root.;
    DataUpdate_t updateData {
        "data",
        output
    };
    updater.queueUpdate(updateData);

}
void obstructed(bool left, bool center, bool right){
     motion.approachingObstacle(left, center, right);
     Serial.print("THERE'S AN OBSTRUCTION !!! \n --------------------------- \n ");
     Serial.print("LEFT Distance: ");
        Serial.println(sensors.left_distance());
        Serial.print("CENTER Distance: ");
        Serial.println(sensors.center_distance());
        Serial.print("RIGHT Distance: ");
        Serial.println(sensors.right_distance());
}
void setup()
{
    logger.setup(LOG_BAUD_RATE, LOG_LEVEL);
    compass.setup();
    motion.setup(IN1_L, IN2_L, EN_L, IN1_R, IN2_R, EN_R, MAX_WHEEL_SPEED_PWM);
    motion.setLogger(&logger);
    motion.setGps(&gps);
    // motion.setLeftSensors(&sensors);
    // motion.setCenterSensor(&sensor_center);
    // motion.setRightSensor(&sensor_right);
    motion.goFullSpeed();
    adjuster.setup(CUT_HEIGHT_SERVO_PIN, CUT_HEIGHT_LOW, CUT_HEIGHT_MEDIUM, CUT_HEIGHT_HIGH, CUT_HEIGHT_CHARGE);
    megaComm.setup(&logger);
    updater.setup(&megaComm);
    megaComm.setDirectionChangeCallback(dirChangeCb);
    megaComm.setSpeedChangeCallback(spdChangeCb);
    megaComm.setHeightChangeCallback(heightChangeCb);
    megaComm.setDirectionChangeCallback(heightChangeCb);
    // sensor_left.setup(PROXIMITY_SENSOR_LEFT_PIN);
    // sensor_center.setup(PROXIMITY_SENSOR_CENTER_PIN);
    // sensor_right.setup(PROXIMITY_SENSOR_RIGHT_PIN);
    sensors.setup(PROXIMITY_SENSOR_LEFT_PIN, PROXIMITY_SENSOR_CENTER_PIN, PROXIMITY_SENSOR_RIGHT_PIN, PROXIMITY_SENSOR_COMMON, OBSTACLE_DISTANCE_TOLERANCE);
    sensors.setOnBlockedCallback(&obstructed);
    gps.setup();
}

void loop()
{
    queueUpdate();
    gps.run();
    motion.run();
    megaComm.run();
    // updater.run();
    sensors.run();
}
