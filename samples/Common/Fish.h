#ifndef Fish_h
#define Fish_h

#ifdef _WIN32
#include <time.h>
#else
#include <sys/time.h>
#endif
#include <iostream>
#include <stdlib.h>

class Value
{
protected:
	double _v;

public:
	double get() { return _v; };
	char* getMem () { return (char*)&_v;};
	void set (double v) {_v = v;};
	void add (double incr) { _v += incr;};
	void add (Value incr) { _v += incr._v;};
	void mul (Value fact) { _v *= fact._v;};
	void encode (char*);
	void decode (const char*);
	int size () { return sizeof(_v);};
};



class Fish
{
public:
	Value x,y;

	Fish();
	void move (Value xDir, Value yDir);
	friend std::ostream& operator << ( std::ostream &s, Fish &f );
};


#endif
