#include "HCSR04.h"
////////////////////////////////////consttruct/destruct
void HCSR04::init(int out,int echo[],int n)
{
	this->out = out;
	this->echo = echo;
	this->n = n;
	pinMode(this->out, OUTPUT);
	for(int i=0;i<n;i++){ pinMode(this->echo[i], INPUT); }
}
void HCSR04::setup(int out,int echo){this->init(out,new int[1]{echo},1);}
void HCSR04::setup(int out,int echo[],int n){this->init(out,echo,n);}
HCSR04::~HCSR04()
{
	~this->out;
	delete[] this->echo;
	~this->n;
}
///////////////////////////////////////////////////dist
float HCSR04::dist(int n) const
{
	digitalWrite(this->out, LOW);
	delayMicroseconds(2);
	digitalWrite(this->out, HIGH);
	delayMicroseconds(10);
	digitalWrite(this->out, LOW);
	// noInterrupts();
	int timeout = 30000;
	float d=pulseIn(this->echo[n], HIGH, timeout);
	// interrupts();
	if(d==0){
		d = timeout;
	}
	return d / 58.0;
}
float HCSR04::dist() const{return this->dist(0);}
