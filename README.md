# FormiBot
The FormiBot is a line-following robot with some extra features, including wireless (Bluetooth) control via dedicated Android app, obstacle detection, checkpoint selection along the line, including U-turn to go back to previous location on the line with an LCD to display the current or next location. 
The robot's name is inspired from Formica which is Latin for 'ant' – a diligent trail or line follower. :)

**List of parts:**
* 1 x Arduino UNO R3
* 2 x TCRT5000 IR sensor modules
* 1 x L293D IC motor driver
* 1 x HC-SR04 ultrasonic sensor
* 1 x HC-05 bluetooth module
* 2 x DC motors
* 2 x Wheels (connected directly to the DC motors)
* 1 x front ball caster
* 2 x 4xAA battery holders (one battery holder is connected to the motors and the second one is for the electronics, since the motors drain the batteries much quicker. Optionally, you can use only one battery pack to power the entire robot)
* Dupont cables or jumper wires
* A chassis to fix and mount all the components. You can purchase a robot chassis online or build your own from acrylic, wood, etc, or 3D print (Thingiverse has a lot of freely available designs).

The bill of materials (BOM) as well as the datasheets are available in pdf format in the repository.

**Features:**
* At the starting position, the robot is positioned with the line in between its two front IR sensor modules. So, in essence, the robot operates by avoiding the line, since the programming causes the two IR sensors to avoid the line in  between them, which subsequently causes the robot to follow the line.
* A maximum of four checkmarks can be set anywhere on the line by placing another short line (it must be at least the same width as both front IR sensors, but preferably a bit wider to account for small shifts as the robot turns to navigate along the line) at a 90 degrees angle across the path line to follow, so that both IR sensors will be on top of the dark line which will trigger its programming to act accordingly. The number of checkmarks can be increased by modifying the Arduino code. The provided Android app won't work for more than four checkpoints along the line as it cannot be directly customised but you can use the MIT App Inventor.
* Follows a line of any shape:
  - given that there is a high contrast between the line and the surrounding surface. Ideally, the line should be black and on a white surface. I used black tape to draw the line on a white plastic surface (a tabletop).
  - as long as the curves are not too sharp, which would otherwise cause the robot to lose track of the line and go off-course. This can be fixed to a certain extent by lowering the speed of the motors in the Arduino code. 
* Using the Android app, the robot can be controlled to move to any checkpoint on the line. The robot follows the line and counts each checkpoint until it reaches the desired position and then stops. While moving, the robot LCD shows each checkpoint position that it passes.
* The robot can be controlled to move to any position on the line. For example, it can move from position 2 to 4. It can also move backwards by first making a 180 degrees turn and then stay on the line while moving forwards. During the whole manoeuver, the LCD shows the updated checkmark position. 
* If there is any obstacle in front of the robot, the latter will stop until the obstacle is removed. The distance of obstacle detection can be changed in the Arduino code. By default, it is set to 100 cm.
* The robot is meant to work as a Tour Guide, so the app has a Start Tour feature which causes the robot to go through all the checkpoints until the end and then do a 180 degrees turn on the line and follow it all the way back to the starting position.
* There is an emergency *Stop* feature in the app which does exactly what it says, as well as a *Reset* feature in case something goes wrong, such as the LCD showing a wrong value for the checkpoint which would mean that the counter variable needs to be reset. Instead of pressing the hardware reset button on the Arduino board, you can simply use the app.

Feel free to experiment! Any improvements are most welcome, so just fork it and contribute.
