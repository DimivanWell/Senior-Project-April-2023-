# Full Circuit Diagram
Below is the over all circuit for the entire radio. 

![IMG_0104 (1)](https://github.com/DimivanWell/Senior-Project-April-2023-/assets/105472781/4da67b51-d2d8-4d0b-92f4-5533ed305849)

## AUX Filter Circuit
The aux input was divided into two paths, Low Pass and High Pass. Utilizing an audio freuqency detction app and Apples Garage Band to fine tune to proper cutoff frequncies. A Zener Diode in high pass filter load off was also added to remove the possibility of peaks being fed through the high end:
![aux_circ](https://github.com/DimivanWell/Senior-Project-April-2023-/assets/105472781/a7103b5b-5451-4bb2-ac52-401109dd55e8)

## NPN Transistor Volume Control

Given the general properties of transistors (essentially switches) we create a very low range volume knob. This controlled the amount of signal sent through to the amps. 
![transitors](https://github.com/DimivanWell/Senior-Project-April-2023-/assets/105472781/661b4667-f9a1-4ce9-b8d8-db094a3ab692)

## An Issue:
The analog level from the Arduino was being supplied rather high through these transistors. These were feeding the system when the NPN was closed. A high pass filter was then added to diminish this. This was a success, HOWEVER, when the current passed through them it affected the fine-tuned self-contained aux circuit. The solution... 
    
## Diode Bridge

Given the general concept of signal through Diodes, I needed the voltage/current to trigger the transistors while removing its effect it had on the aux end. Putting two diodes in opposite directions allowed for half-wave rectifiers to cut the signals and allow for just the aux signal to be the only complete message being sent through to the amps.

![diodes](https://github.com/DimivanWell/Senior-Project-April-2023-/assets/105472781/d898a37e-6384-405f-8825-9769ce1e8813)

## Radio Module

The diode bridge was needed for the aux's circuit but since the high pass was present for the radio all it needed was a low pass for its output into the system and it sounded clear as day.

![radio](https://github.com/DimivanWell/Senior-Project-April-2023-/assets/105472781/bf99c707-363c-41c6-8cbb-a3188278eb08)

## Relay

The display had presets for the radio stations and then a button to switch to aux. When this was clicked a signal was sent to flip the relay to give power to whichever amp was sending a signal to the speakers.

![relay](https://github.com/DimivanWell/Senior-Project-April-2023-/assets/105472781/8e5cc1bb-0850-4928-8876-3b2d662a4fe9)

## The amps and speaker

The amps being triggered gave way to defining clean uninterrupted audio. Given that the feeds weren't needed the amps could be wired in parallel so even if one was off its output would still play to the same speaker or to an additional speaker that was wired through the speaker.

![amps](https://github.com/DimivanWell/Senior-Project-April-2023-/assets/105472781/2ba7289a-58d2-4bba-9302-a2e1aa2260a0)
