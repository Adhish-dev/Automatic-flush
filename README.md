# Automatic-flush
hey guys, i need a help. I ll include the description of the arduino code in a file. I need to configure this code to " to not work if the person leaves after 10 seconds" which is after 1 cycle of confirmation. Can you guys help? its my sem project. thanks in advance
working:
1) When the person stands in front of the ultra-sonic sensor, it detects the person and sends the signal to Arduino that person is detected. The confirmation is later obtained with a gap of 10 seconds from initial detection to make sure the person is not roaming around. Then after the person leaves the range, Arduino commands the stepper motor to operate.
2) When person stands for more than 10 seconds(initial detection+ 1 confirmation cycle(5 seconds)) it is taken as conformation message. The green light blinks, so this makes the motor to stand by for working.
3) When the person leaves the range after the conformation message the motor is coded to work.
4) When the person leaves before the confirmation period, the Arduino will blink the white light . This procedure is carried to find out whether the person is roaming around or not. In this way we can prevent false operating of motor.

well the 4th point is only stated in report but i was unable to make it work. in this i need help.

Im also planned to integrate an fragrance spraying loop in this code, but im dubious about how to do that. 
PLEASE WALK ME THROUGH THIS. THANK YOU FOR YOUR EFFORTS 
