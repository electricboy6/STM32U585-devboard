# IRIS (Integrated Rocket Intelligence System)
![image](assets/render.png)
## What is it
IRIS is an advanced flight computer designed for controlling guided model rockets. It is specifiacally designed for aerodynamic control, but is also capable of thrust vector control.
## Interfaces
IRIS has 6 pyrotechnic channels with a shared arming circuit. The continuity of each channel may be individually sensed. Each pyro channel may be independently controlled. There is also a physical arming switch for safety.  
It has 4 servo output channels, on the main microcontroller's dedicated pwm output pins so they incur no extra cpu load.  
It has a controlled output camera power header, to lower power draw while idling on the pad or waiting for recovery.  
There is a UART broken out from each microcontroller for debugging purposes, just in case the USB doesn't work.  
Finally, IRIS has a high performance lora transceiver onboard for long range telemetry, ensuring that even the highest flights may be safely flown and recovered.
## What's on it
IRIS has 2 high performance imus, one for lower range higher precision sensing, and one for higher range lower precision sensing. By having dedicated imus for each range, IRIS can maintain a high precision across the entire flight envelope.  
IRIS also includes an ultra high g accelerometer (which will not be populated on the prototype boards for cost reasons), a high performance high sensitivity magnetometer, and an ultra high sensitivity barometer. There is additionally a GPS for stable position updates.  
By fusing all of its sensors IRIS can create an accurate vehicle position esitmate across a wide range of flight profiles. This position estimate may then be used in GNC (Guidance, Navigation, and Control) algorithms to control the flight of a vehicle.  
#### Design Reasoning
IRIS uses 2 microcontrollers, one main processor and one auxilary processor. By using this architecture, one fast processor with lots of ram (the STM32U585 in this case) can handle all of the complex GNC logic that needs super consistent loop times to work. The main processor is in charge of all flight logic and servo control, as well as the sensors. However, we need to also be able to handle very inconsistent actions like telemetry and datalogging. To do that, we use the auxilary processor (the STM32U073 in this case). The auxilary processor is in charge of the pyrotechnic channels (not controlling them, basically just acting as an I/O expander), as well as datalogging to both flash and micro sd, plus sending telemetry.  
IRIS switches both the high and low side of the pyro channels, which is entirely about safety - that way there can be a device level digital and physical arm. You can never be too safe with pyrotechnics.  
IRIS uses a very comprehensive suite of sensors, including some quite high quality ones. This is to ensure that at least one sensor of each type is never out of range, which would lead to the position estimate being off, thus the GNC going out of control. I don't think I need to say this, but an out of control rocket is not a good thing.  
Everything that I chose was chosen for safety or so that IRIS could actually fulfil its intended purpose.
#### About  
This project was made for blueprint, an event ran by Hack Club. Hack Club is a global nonprofit that runs events like this, where teenagers learn valuable skills, like hardware design and programming. You can learn more about my project on the blueprint site, at [my project page](https://blueprint.hackclub.com/projects/486).  
  
If reviewers have any questions, just dm me, there are reasons for all of the overkill stuff (already talked about with Kai, see [this thread](https://hackclub.slack.com/archives/C083S537USC/p1766533095590509?thread_ts=1766460158.717379&cid=C083S537USC), also I'm hand assembling with a stencil and hot air reflow station so no double sided pcba fees for me)