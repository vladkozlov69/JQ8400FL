#include <Arduino.h>
#include <Stream.h>

#define JQ8400_START_COMMAND 0xAA
#define JQ8400_VOLUME_SET 0x13
#define JQ8400_COMBINED_PLAYBACK 0x1B


class JQ8400FL
{
private:
	Stream * m_Stream;
	byte sequence[80];
	uint16_t index;
	uint16_t sendByte(byte value, uint16_t checksum); 
	void sendCmd (byte cmd, byte value); 
public :
	JQ8400FL(Stream * stream);
	void volumeSet(uint8_t val);
	void begin();
	void push(char * data);
	void commit();
};

