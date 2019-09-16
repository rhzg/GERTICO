#include "Fish.h"
#include "memory.h"



void Value::encode (char* buffer)
{
  memcpy(buffer, (char*)&_v, sizeof(_v));
};

void Value::decode (const char* buffer)
{
  memcpy((char*)&_v, buffer, sizeof(_v));
};




Fish::Fish()
{
	x.set((1.0*rand()) / RAND_MAX);
	y.set((1.0*rand()) / RAND_MAX);
};


void Fish::move (Value xDir, Value yDir)
{
	x.add (xDir);
	y.add (yDir);
	if (x.get() > 1) x.add (-1.0);
	if (x.get() < 0) x.add (1.0);
	if (y.get() > 1) y.add (-1.0);
	if (y.get() < 0) y.add (1.0);
};

std::ostream &operator << ( std::ostream &s, Fish &f ) 
{
	s << "fish at " << f.x.get() << ", " << f.y.get();
	return s;
}

