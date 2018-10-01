#include <Arduino.h>
#include "JQ8400FL.h"

JQ8400FL::JQ8400FL(Stream  * stream)
{
	m_Stream = stream;
	m_Stream->setTimeout(1000);
}

uint16_t JQ8400FL::sendByte(byte value, uint16_t checksum)
{
	m_Stream->write(value);
	return (checksum + value) & 0xFF;
}

void JQ8400FL::sendCmd(byte cmd, byte value)
{
	uint8_t checksum = 0;
	checksum = sendByte(JQ8400_START_COMMAND, checksum);
	checksum = sendByte(cmd, checksum);
	checksum = sendByte(0x01, checksum);
	checksum = sendByte(value, checksum);
	sendByte((byte)checksum, checksum);
}

void JQ8400FL::volumeSet(uint8_t val)
{
	sendCmd(JQ8400_VOLUME_SET, (byte)val);
}

void JQ8400FL::begin()
{
	index = 0;
}

void JQ8400FL::push(char * data)
{
	memcpy(sequence + index, data, strlen(data));	
	index += strlen(data);
}

void JQ8400FL::commit()
{
	uint8_t checksum = 0;
	checksum = sendByte(JQ8400_START_COMMAND, checksum);
	checksum = sendByte(JQ8400_COMBINED_PLAYBACK, checksum);
	checksum = sendByte((byte)index, checksum);
	for (int i=0; i<index; i++)
	{
		checksum = sendByte(sequence[i], checksum);
	}
	sendByte((byte)checksum, checksum);
}