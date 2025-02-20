# Project3

Bailey Clark and Adam Otsuka

The system we built is a driver's education car that implements a windshield wipers system that has user interaction to choose the speed and elay of the wipers. We built the ignition system to abide by the New York State Department of Motor Vehicles which states that the ignition can only turn on when the passenger and driver are sat down and seatbelts are both on. This will be shown by a green LED when theses conditions are met. The ignition starting will be shown by a blue LED. If one or more condition is not met an alarm will sound and the saftey requirment that was not met will be displayed. The ignition will also turn off if the button is pressed and released. The wipers systme allows the user to control the speed and delay time of them. The speed wil either be Hi, Low, Int (Intermittent), or Off, while the delay time selection is short, medium, or long that is only significant in the Int mode. The display will give the user feedback to which mode and delay time they have selected.

We are using positional motors for the windshield wipers since the motor movements require accuracy of the angle while speed can be control by using a step time. The accuracy of 67 degrees is hard to accomplish with a continous servo because of mechanical error that it has.

Here is a diagram of the relationships between the modules used in our Car System.
![IMG_3904](https://github.com/user-attachments/assets/924d9dae-46f4-4e3d-9f65-ad2a5bad2251)

## Project Behavior Table

|Specification                                                                            |        Test Result          |         Comment
|------------------|-----------------------------|----------------------
| Welcome message is displeyed when the driver sits down|         pass    |        
| Green LED turns on when all saftey measures are met                    |         pass  |      
| Engine Starts message and blue LED turns on when saftey measures are met and ignition button is pressed      | pass|                                                                      
| If the green LED is off and ignition button is pressed ignition is inhibited. Sound the alarm buzzer and display the message, “Ignition inhibited” and why the ignition was inhibited | pass |
| Stop the engine when the ignition button is pushed and released when running                 | pass |
| The speed of the wipers are correct based on the user select | pass |
| In intermittent mode, the delay selected is correctly implemented | pass |
| LCD display shows the Wipers mode, and the delay if it is in intermittent mode| pass|
| When the wipers are turned off, the wipers complete the cycle before stopping | pass |
