# FormiBot
The FormiBot is a line-following robot with some extra features, including wireless control via dedicated Android app, obstacle detection, checkpoint selection along the line, LCD to show current or next location, etc. 
Its name is inspired from Formica which is Latin for Ant – a diligent trail or line follower. :)

**List of parts:**
* 1 x Arduino UNO R3
* 2 x TCRT5000 IR sensor modules
* 1 x L293D IC motor driver
* 1 x HC-SR04 ultrasonic sensor
* 1 x HC-05 bluetooth module
* 2 x DC motors
* Mini Robot Rover Chassis Kit
  - 2 x Wheels
  - 2 x DC motors in micro servo body
  - 1 x Support wheel
  - 1 x Metal chasis
  - 1 x Top metal plate with mounting hardware
* 2 x 4xAA battery holders
* 8 x AA batteries (preferably rechargeable)
* Dupont cables or jumper wires

The bill of materials (BOM) is available in pdf format in the repository.

**Features:**
* At the starting position, the robot is set on top of the line which must be in-between the two front IR sensor modules.
* Checkmarks can be set anywhere on the line by placing a line across the path, so the two IR sensors will detect the dark line.
* Follows a line of any shape
  - given that there is a high contrast between the line and the surrounding surface. Ideally, the line should be black and on a white surface. I used black tape to draw the line on a white plastic surface (a tabletop).
  - as long as the curves are not too sharp, which would otherwise cause the robot to lose track of the line and go off-course. This can be fixed to a certain extent by lowering the speed of the motors in the Arduino code. 
* Using the Android app, the robot can be controlled to move to any checkpoint on the line. The robot follows the line and counts each checkpoint until it reaches the desired position and then stops. While moving, the robot LCD shows each checkpoint position that it passes.
* The robot can be controlled to move to any position on the line. So, it can move from, say, position 2 to 4. It can also move backwards, say, from position 4 to 3, by making a 180 degrees turn and staying on the line and moving forwards. During the whole manoeuver, the LCD updates the checkmark position on the LCD corresponding. 
