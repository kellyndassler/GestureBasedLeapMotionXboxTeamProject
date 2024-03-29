#include "Dpad.h"

using namespace Leap;

//update frame method--update hand tilt position
void Dpad::updateFrame(const Leap::Frame& frame) {
	// remove past hands so if a hand was moved out of the frame, we don't consider it (0 is left, 1 is right)
	leftH = Hand::invalid();
	rightH = Hand::invalid();

	//set hands
	for (const Hand& h : frame.hands()) {
		if (h.isValid()) {
			if (h.isLeft())
				leftH = h;
			else if (h.isRight())
				rightH = h;
		}
	}
}

//sets configuration for hand directions
void Dpad::setSensitivity(const dpadsens_t &hs) {
	config = hs;
	if (config.pitchMax > 3.14159)
		config.pitchMax = 3.14159;
	if (config.pitchMin < 0)
		config.pitchMax = 0;
}

//returns true if hand tilted "up" depending on pitch position (gets tilted around x axis)
//pitch returns negative value if in "up" direction (I think--need to test with leap to make sure)
bool Dpad::up(Hands h) const {
	Hand hand = whichHand(h);
	if (!hand.isValid())
		return false;
	float pitch = hand.direction().pitch();
	if (pitch <= (-config.pitchMin) && pitch >= (-config.pitchMax))
		return true;
	return false;
}

//returns true if hand tilted "down" depending on pitch position (gets tilt around x axis)
//pitch returns positive value if in "down" direction (I think--need to test with leap to make sure)
bool Dpad::down(Hands h) const {
	Hand hand = whichHand(h);
	if (!hand.isValid())
		return false;
	float pitch = hand.direction().pitch();
	if (pitch >= config.pitchMin && pitch <= config.pitchMax)
		return true;
	return false;
}

//returns true if hand tilted "left" depending on roll position (gets tilt around z axis)
//roll returns negative value if in "left" direction (I think--need to test with leap to make sure)
bool Dpad::left(Hands h) const {
	Hand hand = whichHand(h);
	if (!hand.isValid())
		return false;
	float roll = hand.palmNormal().roll();
	if (roll >= config.rollMin && roll <= config.rollMax)
		return true;
	return false;
}


//returns true if hand tilted "right" depending on roll position (gets tilt around z axis)
//roll returns positive value if in "right" direction (I think--need to test with leap to make sure)
bool Dpad::right(Hands h) const {
	Hand hand = whichHand(h);
	if (!hand.isValid())
		return false;
	float roll = hand.palmNormal().roll();
	if (roll <= (-config.rollMin) && roll >= (-config.rollMax))
		return true;
	return false;
}

//return which Hand to use for dpad
const Hand& Dpad::whichHand(Hands h) const {
	if (h == leftHand)
		return leftH;
	return rightH;
}



