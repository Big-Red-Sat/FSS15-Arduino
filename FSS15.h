#ifndef FSS15_h
#define FSS15_h

#include "Arduino.h"

#define FSS15_SR_CLEAR ~((1 << 4) | (1 << 3))
#define FSS15_SR_32HZ (1 << 4) | (1 << 3)
#define FSS15_SR_16HZ (1 << 4) | (0 << 3)
#define FSS15_SR_8HZ (0 << 4) | (1 << 3)
#define FSS15_SR_4HZ (0 << 4) | (0 << 3)

#define FSS15_CONL_COMMIT (1 << 5)
#define FSS15_CONL_COMMIT_CLEAR ~FSS15_CONL_COMMIT

#define FSS15_CONL_CONTINUOUS (1 << 6)
#define FSS15_CONL_ONESHOT ~FSS15_CONL_CONTINUOUS

#define FSS15_CONL_SAMPLEREQUEST (1 << 7)
#define FSS15_CONL_SAMPLEDONE ~FSS15_CONL_SAMPLEREQUEST

class FSS15
{
	public:
	FSS15(int address);
	void init();
	void getSample(int16_t *theta, int16_t *phi, int16_t *temp);
	int16_t getTheta();
	int16_t getPhi();
	int16_t getTemp();
	uint8_t get_conl(void);
	void set_conl(uint8_t new_conl);
	void set_one_shot(void);
	uint8_t getAddress(void);
	void setI2CAddress(int address);
	void update_conl();
	void setContinuousSampling(bool continuous);
	void setSamplingRate(int rate);
	bool sample_wait(void);
	void setSampleBit(bool sample);
	void setCommitBit(bool commit);
	void default_config(void);
	void continuous_config(void);

	private:
	int _addr;
	uint8_t _conl_reg;
};

#endif // FSS15
