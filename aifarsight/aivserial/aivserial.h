#ifndef AI_VSERIAL_H_
#define AI_VSERIAL_H_

struct aivserial_option {
	unsigned int datab;
	unsigned int parity;
	unsigned int stopb;
};

#define AI_VSERIAL_MAGIC 's'
#define AI_VSERIAL_SET_BAUD _IOW(AI_VSERIAL_MAGIC, 0, unsigned int)
#define AI_VSERIAL_GET_BAUD _IOW(AI_VSERIAL_MAGIC, 1, unsigned int)
#define AI_VSERIAL_SET_FFMT _IOW(AI_VSERIAL_MAGIC, 2, struct aivserial_option)
#define AI_VSERIAL_GET_FFMT _IOW(AI_VSERIAL_MAGIC, 3, struct aivserial_option)

#endif /* AI_VSERIAL_H_ */
