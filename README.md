# FormiBot
The FormiBot is a line-following robot with some extra features, including wireless (Bluetooth) control via dedicated Android app, obstacle detection, checkpoint selection along the line, including U-turn to go back to previous location and a nice LCD to show the current or next location. 
Its name is inspired from Formica which is Latin for 'ant' – a diligent trail or line follower. :)

**List of parts:**
* 1 x Arduino UNO R3
* 2 x TCRT5000 IR sensor modules
* 1 x L293D IC motor driver
* 1 x HC-SR04 ultrasonic sensor
* 1 x HC-05 bluetooth module
* 2 x DC motors
* Mini Robot Rover Chassis Kit (i purchased a kit due to time limitations but the chassis parts can be 3D printed)
  - 2 x Wheels
  - 2 x DC motors in micro servo body
  - 1 x Support wheel
  - 1 x Metal chasis
  - 1 x Top metal plate with mounting hardware
* 2 x 4xAA battery holders
* 8 x AA batteries (preferably rechargeable)
* Dupont cables or jumper wires

The bill of materials (BOM) as well as the datasheets are available in pdf format in the repository.

**Features:**
* At the starting position, the robot is set on top of the line which must be in-between the two front IR sensor modules.
* A maximum of four checkmarks can be set anywhere on the line by placing a line across the path, so the two IR sensors will detect the dark line. The number of checkmarks can be increased by modifying the Arduino code but the app won't work for more than four checkmarks.
* Follows a line of any shape:
  - given that there is a high contrast between the line and the surrounding surface. Ideally, the line should be black and on a white surface. I used black tape to draw the line on a white plastic surface (a tabletop).
  - as long as the curves are not too sharp, which would otherwise cause the robot to lose track of the line and go off-course. This can be fixed to a certain extent by lowering the speed of the motors in the Arduino code. 
* Using the Android app, the robot can be controlled to move to any checkpoint on the line. The robot follows the line and counts each checkpoint until it reaches the desired position and then stops. While moving, the robot LCD shows each checkpoint position that it passes.
* The robot can be controlled to move to any position on the line. For example, it can move from position 2 to 4. It can also move backwards by first making a 180 degrees turn and then stay on the line while moving forwards. During the whole manoeuver, the LCD shows the updated checkmark position. 
* If there is any obstacle in front of the robot, the latter will stop until the obstacle is gone. The distance of obstacle detection can be changed.
* The robot is meant to work as a Tour Guide, so the app has a Start Tour feature which causes the robot to go through all the checkpoints until the end and then come back to the starting position.
* There is an emergency *Stop* feature in the app which does exactly what it says, as well as a *Reset* feature in case the LCD shows a wrong value for the checkpoint.

Feel free to experiment with it, maybe even improve it and share with us!
