# Capactitive Tank Level Signal Converter

This is the tank monitor converter thinger I made. It takes a 0-4vdc signal from a capactitive, non contact fluid level sensor and converts it to an analog resistance from 240-30 (approximately) ohms.

The sensors come from this place:
https://www.ferriellosales.com/monitoring-systems.html

There is a bunch of signal smoothing going on to make the values look good. I also emit a JSON message of the status of the tanks.

# Requirements and Such

1. I have 4 tanks, two waste and two fresh tanks. The pairs are connected with a crossover, so I need to level average between the two of them.

2. I then want to easily export the levels to an analog meter, or something that takes a resistance signal. In my case, it's a Victron Venus GX, which has three analog inputs to measure tankage.

3. I also don't want to drill any holes in the tanks, hence the capacitive monitors. It seems like all the capactitive types (see level, this one, others) all have a dedicated reading head for the monitors. This is my attempt at "genericising" the signal output. It's only 16 levels of resistance, but it works well.

4. In the future, I'd like to completely omit the analog rube goldberg machine and directly take in smoothed voltage levels from the senders, and send them to the Venus GX. From there a daemon would listen to USBxx tty port, and publish a tank level onto the DBUS.

This is version 0.0001 so please be kind. What would be neat is to build a more robust board.

# Hardware Details
I use two CD74HC4067 Analog Multiplexer breakout boards to select from a resistor ladder. The ladder has 15x 13 Ohm resistors in series, and the address lines of the multiplexer tap at each junction between resistors. They are balanced on the high resistance end (the end that needs to go to 240 Ohm) with a series of two 10 Ohm 1% (20 Ohm total) resistors.

This gives a workable range of 240-47ish ohms. For some reason, there is an internal resistance in the board I built, but it's good enough. 30 Ohms is "full" and 240 ohms is "empty"

# Top of Board
You can see the arduino Uno clone that is logic/adac. Basically, 4 digital pins on Arduino go to the Mux to select the channel. Repeat this for the other channel. Refer to the code to see what pins I selected if you're interested.

The enable pin is a single pin that is set low. Setting this to high blocks the signal through the Mux. Useful if you were switching things like audio signals through it or whatever. In this case, it's just trouble if you ignore it.

I stuck the breakout boards on 90 degree angle pins so I had more room. It also makes it easier to solder.

![Top of Board](https://github.com/aaronsb/Arduino/blob/master/tankmonitor/resistor_converter_top.jpg "Top of Board")

# Bottom Of Board
The little wires go from the edge to the balance resistors at the end. The other wires carry the other end of the resistor ladder to the screw terminals.

![Top of Board](https://github.com/aaronsb/Arduino/blob/master/tankmonitor/resistor_converter_bottom.jpg "Bottom of Board")

# Tank Montitor Sender
You can buy these from https://www.ferriellosales.com/monitoring-systems.html. They're about 35 bucks a piece. You just stick two strips of foil onto a non-conductive liquids tank, then stick the copper foil on top of the other foil. Wire the Red and Black wires to 12VDC, and the blue wire becomes a 0-4VDC signal. You'll need to borrow that ground from the sender and attach it to the arduino, so you have a good ground reference.

In general, good electrical hygene will make the signal noise less.
![Tank Sender](https://github.com/aaronsb/Arduino/blob/master/tankmonitor/capacitive_tank_monitor.jpg "Tank Sender")

