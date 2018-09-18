/usr/bin/avrdude -DV -patmega328p \
  -Pnet:192.168.1.14:2323 \
  -carduino -b115200 \
  -U flash:w:./CarPlatform.ino.hex:i\
  -C /etc/avrdude.conf
