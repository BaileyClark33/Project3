# Project3

Name of team members
One paragraph description of the system behavior (what does it do?)
Design Alternatives section with explanation of choice of servo motors
Summary of testing results. Create a table from the list of project behaviors for the two subsystems to organize the results. Fill in “Pass or Fail” for each behavior, and provide comments where necessary. This will be similar to Project 2. 
*Extra credit (+3 points) if a correct modular diagram of the code (similar to Figure 5.3 in textbook) is linked or included in the readme file. 



This system takes a driver's education car and implements a windshield wipers system that gives the user the option to pick the speed of the wipers and the delay time of the wipers. The car must abide by the New York State Department of
Motor Vehicles rules which states that the ignition can only turn on when both the passenger and the driver are sitting down and both seatbelts are fastened. A green LED will turn on when both conditions are met and when the ignition is on a
blue LED turns on instead. If one or more of those conditions are not true then ignition is not possible and an alarm will sound. The driver will get an error message explaining why the car will not turn on and try to fix the problem and attempt
to turn on the ignition again. If the driver pushes the ignition button while the ignition is on, it will turn off. The wiper system allows the driver to have control over the wipers in two ways. The first feature the driver has control over is
the speed of the wipers, the wiper can either be high, low, intermediate, or off. Then, the driver can decide a delay time of either short, medium, or long. A display will show the driver what mode the windshield wipers are in.

We decided to use a positional motor for our windshield wipers. We decided to use this motor because its movements were more accurate and it could reach the degrees specified with more precision. Due to the requirement of the wipers having to go 67 degrees this motor made more sense.

## Project Behavior Table

|Specification                                                                            |        Test Result          |         Comment
|------------------|-----------------------------|----------------------
| When the driver sits down, display the message, “Welcome to enhanced alarm system model 218-W25”|         pass    |        
| Start the engine when the ignition is enabled and ignition button is pushed                     |         pass  |      
| If the ignition is lit, normal ignition occurs, the blue LED turns on and the green LED off . Display the message, “Engine started.”    | pass|                                                                      
| If the ignition is not enabled then ignition is inhibited. Sound the alarm buzzer and display the message, “Ignition inhibited” and why the ignition was inhibited | pass |
| Stop the engine when the ignition button is pushed and released when running                 | pass |
| Wipers move at the speed the user selected if the engine is running | ? |
| Wipers move with the delay selected | ? |
| The speed and delay of the wipers is displayed on the LCD| pass|
| When wiper mode is selected to off the wiper goes back to 0 degrees, completing its cycle if in one | ?|
