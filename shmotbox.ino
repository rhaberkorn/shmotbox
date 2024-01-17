#include <Control_Surface.h>
#include <DistanceSensor.h>

/**
 * Send out 10-bit poti as a 14-bit value, split to 2 CC messages.
 * The higher order byte is sent on the controller's base address.
 * The lower order byte is sent on the address + 0x20.
 */
class CCPotentiometer14 : public MIDIFilteredAnalog<ContinuousCCSender14<10>> {
public:
  CCPotentiometer14(pin_t analogPin, MIDIAddress address)
      : MIDIFilteredAnalog(analogPin, address, {}) {}
};

static USBMIDI_Interface midi;

/*
 * In the constructors, there is always first the pin(s) and then the
 * MIDI address - controller Id with optional channel.
 *
 * NOTE: A6-A11 are available on physical D4, D6, D8-10, D12.
 */
static CCPotentiometer14 pot0 {A0,      0x00};
static CCPotentiometer14 pot1 {A1,      0x01};
static CCPotentiometer14 pot2 {A2,      0x02};
static CCPotentiometer14 pot3 {A3,      0x03};
static CCPotentiometer14 pot4 {A4,      0x04};
static CCPotentiometer14 pot5 {A5,      0x05};
static CCPotentiometer14 pot6 {A6,      0x06};
static CCPotentiometer14 pot7 {A7,      0x07};
static CCPotentiometer14 pot8 {A8,      0x08};
static CCPotentiometer14 pot9 {A9,      0x09};

#if 0
static CCPotentiometer14 pedal {A10,    0x0A};
#endif

static CCRotaryEncoder enc0   {{0, 1},  0x10};
/*
 * FIXME: This button does not physically work.
 */
static CCButton enc0_button   {2,       0x11};

#if 0
static CCRotaryEncoder enc1   {{3, 5},  0x12};
static CCButton enc1_button   {7,       0x13};
#endif

static DistanceSensor dist0(11, 13);
static const byte DIST0_ADDRESS = 0x1F;
static const double DIST0_MAX = 40; /* cm */

void
setup()
{
  RelativeCCSender::setMode(relativeCCmode::TWOS_COMPLEMENT);
  Control_Surface.begin();
}

void
loop()
{
#if 0
  /*
   * FIXME: Should probably be a proper class.
   */
  double dist_cm = dist0.getCM();
  static unsigned short dist_last = 0;
  unsigned short dist_short = min(dist_cm, DIST0_MAX)*0x3FFF/DIST0_MAX;
  if (dist_short != dist_last) {
    Serial.println(dist_cm);
    Serial.println(dist_short);
    midi.sendControlChange(DIST0_ADDRESS | 0x00, (dist_short >> 7) & 0x7F);
    midi.sendControlChange(DIST0_ADDRESS | 0x20, (dist_short >> 0) & 0x7F);
    dist_last = dist_short;
  }
#endif

  Control_Surface.loop();
}
