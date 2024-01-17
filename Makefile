#DEVICE := /dev/ttyACM1
# FreeBSD (via Linuxator).
# This requires installation of the linux-compatible-tty.conf devd script.
# Without this, `arduino-cli upload` will not work.
# You can however manually invoke avrdude on FreeBSD if everything fails.
DEVICE := /dev/ttyACM0

FQBN := arduino:avr:leonardo

ARDUINO_CLI := arduino-cli
#ARDUINO_CLI := ~/arduino-ide_2.2.1_Linux_64bit/resources/app/lib/backend/resources/arduino-cli

all: compile

install-deps:
	$(ARDUINO_CLI) core install arduino:avr
	$(ARDUINO_CLI) lib install DistanceSensor
	$(ARDUINO_CLI) lib install MIDIUSB
	@echo 'You have to install https://github.com/tttapa/Control-Surface manually.'

# For the legacy arduino-build that runs natively on FreeBSD.
# Not all libraries are compatible, though.
# Especially Control-Surface apparently needs a v2 core.
# arduino-builder -compile -hardware /usr/local/arduino/hardware -tools /usr/local/arduino/hardware/tools/ -tools /usr/local/arduino/tools-builder/ -core-api-version 10618 -libraries ~/Arduino/libraries -fqbn arduino:avr:leonardo -prefs "compiler.cpp.extra_flags=-DARDUINO_API_VERSION=1" -verbose shmotbox.ino
compile:
	$(ARDUINO_CLI) compile --fqbn $(FQBN) .

# You may have to run this as root, but this will require installing
# the arduino:avr core into the root account as well.
# It therefore makes sense to have $(DEVICE) accessible as a regular user.
# On FreeBSD you have to be in the dialer group.
upload:
	$(ARDUINO_CLI) upload -p $(DEVICE) --fqbn $(FQBN) .
