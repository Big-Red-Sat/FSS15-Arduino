#include "Arduino.h"
#include "FSS15.h"
#include <Wire.h>

FSS15::FSS15(int address, TwoWire *wire)
{
	ptr = wire;
	_addr = address;
	_conl_reg = 0;
}

void FSS15::init()
{
	default_config();
}

void FSS15::read_regmap(void)
{
	ptr->beginTransmission(_addr);
	ptr->write(0);
	ptr->endTransmission();
	ptr->requestFrom(_addr, 36);
	int i = 0;

	uint8_t register_bytes[36] = { 0 };
	while (ptr->available())
	{
		register_bytes[i++] = ptr->read();
	}
	software_version = register_bytes[0] | (register_bytes[1] << 8);
	model = register_bytes[2] | (register_bytes[3] << 8);
	temperature = register_bytes[4] | (register_bytes[5] << 8);
	sample_count = register_bytes[8] | (register_bytes[9] << 8) | (register_bytes[10] << 16) | (register_bytes[11] << 24);
	pd_sum = register_bytes[12] | (register_bytes[13] << 8) | (register_bytes[14] << 16) | (register_bytes[15] << 24);
	control1 = register_bytes[16] | (register_bytes[17] << 8);
	control2 = register_bytes[20];
	status = register_bytes[24] | (register_bytes[25]);
	alpha = register_bytes[28] | (register_bytes[29] << 8) | (register_bytes[30] << 16) | (register_bytes[31] << 24);
	beta = register_bytes[32] | (register_bytes[33] << 8) | (register_bytes[34] << 16) | (register_bytes[35] << 24);
}

void FSS15::default_config(void)
{
	setContinuousSampling(true);
	setSamplingRate(FSS15_SR_16HZ);
	setSampleBit(true);
	uint8_t current_conl = get_conl();
	if (current_conl != _conl_reg)  update_conl();
}

void FSS15::continuous_config(void)
{
	setContinuousSampling(true);
	setSamplingRate(FSS15_SR_16HZ);
	setSampleBit(false);
	uint8_t current_conl = get_conl();
	if (current_conl != _conl_reg) update_conl();
}

void FSS15::set_one_shot(void)
{
	set_conl(get_conl());
	setSampleBit(true);
	update_conl();
}

bool FSS15::sample_wait()
{
	ptr->beginTransmission(_addr);
	ptr->write(4);
	ptr->endTransmission();
	ptr->requestFrom(_addr, 1);
	if (ptr->available())
	{
		char c = ptr->read();
		if (!(c & (1 << 7)))
		{
			return true;
		}
		else
		{
			return false;
		}
	}
	return false;
}

uint8_t FSS15::get_conl(void)
{
	ptr->beginTransmission(_addr);
	ptr->write(4);
	ptr->endTransmission();

	uint8_t conl_reg = 0;
	int i = 0;
	ptr->requestFrom(_addr, 1);
	while(ptr->available())
	{
		conl_reg = ptr->read();
	}

	return conl_reg;
}

void FSS15::update_conl(void)
{
	ptr->beginTransmission(_addr);
	ptr->write(4);
	ptr->write(_conl_reg);
	ptr->endTransmission();
}

void FSS15::set_conl(uint8_t new_conl)
{
	_conl_reg = new_conl;
}

void FSS15::setContinuousSampling(bool continuous)
{
	if (continuous) _conl_reg |= FSS15_CONL_CONTINUOUS;
	else _conl_reg &= FSS15_CONL_ONESHOT;
}

void FSS15::setSamplingRate(int samplingRate)
{
	_conl_reg &= FSS15_SR_CLEAR;
	_conl_reg |= samplingRate;
}

void FSS15::setCommitBit(bool commit)
{
	if (commit) _conl_reg |= FSS15_CONL_COMMIT;
	else _conl_reg &= FSS15_CONL_COMMIT_CLEAR;
}

void FSS15::setSampleBit(bool sample)
{
	if (sample) _conl_reg |= FSS15_CONL_SAMPLEREQUEST;
	else _conl_reg &= FSS15_CONL_SAMPLEDONE;
}