#include "common.h"

#ifdef BIN_SCALE

#include "FLOAT.h"

FLOAT F_mul_F(FLOAT a, FLOAT b) {
	int64_t aa = (int32_t)a;
	int64_t bb = (int32_t)b;
	return (int32_t)((aa * bb) >> 16);
}

FLOAT F_div_F(FLOAT a, FLOAT b) {
	int32_t aa = (int32_t)a;
	int32_t bb = (int32_t)b;
	return (aa/bb)<<16;
}

FLOAT f2F(float a) {
	uint32_t val =0;
	val = (a>=0)?0:(1<<31);
	a = a*(1<<16);
	int32_t t=a;
	t &= (0x7fffffff);
	val |= t;
	return val;
}

static inline FLOAT Fabs(FLOAT x) {
	return (*(uint32_t *)&x)&0x7fffffff;
}


FLOAT pow(FLOAT x, FLOAT y) {
	/* we only compute x^(1/3) */
	FLOAT t, t2, dt, next_t = int2F(2);

	do {
		t = next_t;
		t2 = F_mul_F(t, t);
		dt = (F_div_F(x, t2) - t) / 3;
		next_t = t + dt;
	} while(Fabs(dt) > f2F(1e-3));

	return next_t;
}

#endif
