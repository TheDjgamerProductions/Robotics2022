# Table of contents
- [Void setup](https://github.com/TheDjgamerProductions/Robotics2022/blob/main/Assessments/Assessment_2_Smart_Device_House/Logic.md#void-setup)
- [Void Loop](https://github.com/TheDjgamerProductions/Robotics2022/blob/main/Assessments/Assessment_2_Smart_Device_House/Logic.md#void-loop)
- [Void StateHandler](https://github.com/TheDjgamerProductions/Robotics2022/blob/main/Assessments/Assessment_2_Smart_Device_House/Logic.md#void-statehandler)
- [Void DisarmedState](https://github.com/TheDjgamerProductions/Robotics2022/blob/main/Assessments/Assessment_2_Smart_Device_House/Logic.md#Void-DisarmedState)
- [Void armedState](https://github.com/TheDjgamerProductions/Robotics2022/blob/main/Assessments/Assessment_2_Smart_Device_House/Logic.md#Void-armedState)
- [Void LEDController](https://github.com/TheDjgamerProductions/Robotics2022/blob/main/Assessments/Assessment_2_Smart_Device_House/Logic.md#void-ledcontroller)
- [Void FanCrontroller](https://github.com/TheDjgamerProductions/Robotics2022/blob/main/Assessments/Assessment_2_Smart_Device_House/Logic.md#void-fancrontroller)
- [Int readDistance](https://github.com/TheDjgamerProductions/Robotics2022/blob/main/Assessments/Assessment_2_Smart_Device_House/Logic.md#int-readDistance)

- - -

# Void setup
```mermaid
  flowchart TD
    terminalStart([Void Setup])
    step1[set trafic light pins to output]
    step2[Set HC-SR04 tigger pin to output]
    step3[Set buzzer pin to output]
    step4[Set up servo]
    step5[Set up Motor Driver]
    step6[set pot pin to input]
    step7[Set line sensor pin to input]
    step8[Set button pin to input]
    step9[Set HC-SR04 echo pin to input]
    step10[Set up Bluetooth]
    terminalEnd([End])
    terminalStart --> step1 --> step2 --> step3 --> step4 --> step5 --> step6 --> step7 --> step8 --> step9 --> step10 --> terminalEnd
```

- - - -


# Void loop
```mermaid
  flowchart TD
    terminalStart([Void Loop])
    step1[StateHandler]
    terminalStart --> step1 --> terminalStart
```

- - - -


# Void StateHandler
This function is used to determan what state the system should be in (Armed or Disarmed)
```mermaid
  flowchart TD
    terminalStart([Void StateHandler])
    bluetooth{Bluetooth connected}
    armedState(ArmedState)
    DisarmedState(DisarmedState)
    terminalEnd([End])
    terminalStart --> bluetooth
    bluetooth --> |True| DisarmedState --> terminalEnd
    bluetooth --> |False| armedState --> terminalEnd

```

- - - -
# Void DisarmedState
This function is used to call the other functions that are used to implement user control when the system is in a disarmed state
```mermaid
  flowchart TD
    terminalStart([Void DisarmedState])
    terminalEnd([End])
    led(LEDController)
    fan(FanCrontroller)
    terminalStart --> led --> fan --> terminalEnd
```
- - - 
# Void armedState
This function is used when the system is armed due to the user not being conected.

When someone is within distance to the sonar it sounds the alarm.
```mermaid
  flowchart TD
    terminalStart([Void armedState])
    terminalEnd([End])
    off(Turn Everything off)
    if{readDistance < 10cm}
    alarm(Write high to Buzzer)
    noAlarm(Write low to Buzzer)
    terminalStart --> off --> if
    if --> |True| alarm --> terminalEnd
    if --> |False| noAlarm --> terminalEnd
```
See readDistacne function [Here](https://github.com/TheDjgamerProductions/Robotics2022/blob/main/Assessments/Assessment_2_Smart_Device_House/Logic.md#int-readDistance)


- - - 

# Void LEDController
This function is used to controll the LEDs when the system is in a disarmed state
```mermaid
  flowchart TD
    terminalStart([Void LEDController])
    terminalEnd([End])
    LineReadout(LineReadout = Read Line Sensor)
    bluetoothReadout(BluetoothReadout = Read Bluetooth)
    setLED(Set LED High)
    LEDoff(Set LED Low)
    ifButtonandBluetooth{if LineReadout or bluetoothReadout}
    terminalStart --> LineReadout --> bluetoothReadout --> ifButtonandBluetooth
    ifButtonandBluetooth --> |True| setLED --> terminalEnd
    ifButtonandBluetooth --> |False| LEDoff --> terminalEnd 
```


- -  -

# Void FanCrontroller
*Description goes here*
```mermaid
  flowchart TD
    terminalStart([Void FanCrontroller])
    terminalEnd([End])
    readPot(PotReadout = readPot)
    mapPot(MappedPotReadout = map PotReadout min:0 max:255)
    fan(AnalogWirte Fan - MappedPotReadout)
    terminalStart --> readPot --> mapPot --> fan --> terminalEnd
```

- - -

# Int readDistance

```mermaid
  flowchart TD
    terminalStart([int readDistance])
    terminalEnd([End])
    trigLow(Write Low to HC-SR04 Tigger pin)
    delay1(Wait for 2 Microseconds)
    TrigHigh(Write High to HC-SR04 Tigger pin)
    delay2(Wait for 10 Microseconds)
    trigLow2(Write Low to HC-SR04 Tigger pin)
    duration(long duration = pulseIn HC-SR04 Tigger pin)
    distacne(int distacne = duration * 0.034 / 2)
    return(return distacne)
    terminalStart --> trigLow --> delay1 --> TrigHigh --> delay2 --> trigLow2 --> duration --> distacne --> return --> terminalEnd
```




<!--- template
```mermaid
  flowchart TD
    terminalStart([Void name])
    terminalEnd([End])
```
-->
