#include <Control_Surface.h>

class CCPotentiometer14 : public MIDIFilteredAnalog<ContinuousCCSender14<10>> {
  public:
    CCPotentiometer14(pin_t analogPin, MIDIAddress address)
        : MIDIFilteredAnalog(analogPin, address, {}) {}
};

USBMIDI_Interface midi;
CCPotentiometer14 pot {A0, MIDI_CC::General_Purpose_Controller_1};

void
setup()
{
  Control_Surface.begin();
}

void
loop()
{
  Control_Surface.loop();
}
