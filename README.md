# Arduino Light Following Robot

The following project provides the full code for an Arduino-based light following robot. A servo motor robot that seeks out the brightest light source it can find. 

## Description

This code uses Arduino's Servo library to control the motors and standard IO functions to read sensor input. The Arduino board reads input from 6 sensors and drives 4 motors. The robot navigates based on the sensor with the lowest light intensity, directing the robot towards the light source. 

## Circuit Diagram

### Motors Pins:
```
(4) o---o (6)
      |
      |
(5) o---o (7)
```

### Sensors Pins:

```
    (A0)
    o---o
(A5)  |  (A1)
(A4)  |  (A2)
    o---o
    (A3)
```

## Usage

The robot will stop if the minimum light intensity goes above a certain threshold (`LIGHT_INTENSITY_THRESHOLD`). 

If the sensor with the minimum light value recorded is the forward sensor, the robot will move forward. Alternatively, the robot will rotate towards the direction of the sensor with the lowest light value.

In case the values for sensor A1 are exceeding, reducing it by half. 


## Future Work

Further improvements can be made by integrating more sensors, implementing obstacle avoidance, or making the robot autonomous by adding a battery power source.
