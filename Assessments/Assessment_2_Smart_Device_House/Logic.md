# Table of contents
- [Void setup](https://github.com/TheDjgamerProductions/Robotics2022/blob/main/Assessments/Assessment_2_Smart_Device_House/Logic.md#void-setup)
- [Void Loop](https://github.com/TheDjgamerProductions/Robotics2022/blob/main/Assessments/Assessment_2_Smart_Device_House/Logic.md#void-loop)
- [Void StateHandler](https://github.com/TheDjgamerProductions/Robotics2022/blob/main/Assessments/Assessment_2_Smart_Device_House/Logic.md#void-statehandler)
- [Void LEDController](https://github.com/TheDjgamerProductions/Robotics2022/blob/main/Assessments/Assessment_2_Smart_Device_House/Logic.md#void-ledcontroller)
- [Void FanCrontroller](https://github.com/TheDjgamerProductions/Robotics2022/blob/main/Assessments/Assessment_2_Smart_Device_House/Logic.md#void-fancrontroller)



## Void setup

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

# Void LEDController
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

```mermaid
  flowchart TD
    terminalStart([Void FanCrontroller])
    terminalEnd([End])
```




<!--- template
```mermaid
  flowchart TD
    terminalStart([Void name])
    terminalEnd([End])
```
-->
