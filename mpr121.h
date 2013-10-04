#ifndef MPR121_H
#define MPR121_H

#include "MPR121_defs.h"

// idea behind this is to create a settings structure that we can use to store all the
// setup variables for a particular setup - comes pre-instantiated with defaults and
// can be easily tweaked - we pass by reference (as a pointer) to save RAM
struct MPR121_settings
{
	// touch and release thresholds
	unsigned char TTHRESH;
	unsigned char RTHRESH;

	// general electrode touch sense baseline filters
	// rising filter
	unsigned char MHDR;
	unsigned char NHDR;
	unsigned char NCLR;
	unsigned char FDLR;

	// falling filter
	unsigned char MHDF;
	unsigned char NHDF;
	unsigned char NCLF;
	unsigned char FDLF;

	// touched filter
	unsigned char NHDT;
	unsigned char NCLT;
	unsigned char FDLT;

	// proximity electrode touch sense baseline filters
	// rising filter
	unsigned char MHDPROXR;
	unsigned char NHDPROXR;
	unsigned char NCLPROXR;
	unsigned char FDLPROXR;

	// falling filter
	unsigned char MHDPROXF;
	unsigned char NHDPROXF;
	unsigned char NCLPROXF;
	unsigned char FDLPROXF;

	// touched filter
	unsigned char NHDPROXT;
	unsigned char NCLPROXT;
	unsigned char FDLPROXT;

	// debounce settings
	unsigned char DTR;

	// configuration registers
	unsigned char AFE1;
	unsigned char AFE2;
	unsigned char ECR;

	// auto-configuration registers
	unsigned char ACCR0;
	unsigned char ACCR1;
	unsigned char USL; 
	unsigned char LSL; 
	unsigned char TL; 
	
	// default values in initialisation list
	MPR121_settings():
		TTHRESH(40),
		RTHRESH(20),
		MHDR(0x3F),
		NHDR(0x3F),
		NCLR(0x05),
		FDLR(0x00),
		MHDF(0x00),
		NHDF(0x3F),
		NCLF(0x10),
		FDLF(0x03),
		NHDT(0x00),
		NCLT(0x00),
		FDLT(0xFF),
		MHDPROXR(0x0F),
		NHDPROXR(0x0F),
		NCLPROXR(0x00),
		FDLPROXR(0x00),
		MHDPROXF(0x01),
		NHDPROXF(0x01),
		NCLPROXF(0xFF),
		FDLPROXF(0xFF),
		NHDPROXT(0x00),
		NCLPROXT(0x00),
		FDLPROXT(0x00),
		DTR(0x11),
		AFE1(0xFF),
		AFE2(0x38),
		ECR(0x00),
		ACCR0(0x00),
		ACCR1(0x00),
		USL(0x00), 
		LSL(0x00), 
		TL(0x00) {}
	
};

enum pinf_t
{
	INPUT,
	INPUT_PU,
	INPUT_PD,
	OUTPUT,
	OUTPUT_HS,
	OUTPUT_LS
};

class MPR121_t
{
	private:
		unsigned char address;
		MPR121_settings defaultSettings;
		unsigned char ECR_backup; // so that we can re-enable the correct number of pins
								  // when recovering from stop mode
	public:
		MPR121_t();
		void begin(unsigned char address);	// I think you only need to be able to set the
											// address at the very beginning
		void begin(); 
		void run();
		void stop();
		void reset();
		void applySettings(MPR121_settings *settings);
		
		void setTouchThreshold(unsigned char val);
		void setTouchThreshold(unsigned char electrode, unsigned char val);
		void setReleaseThreshold(unsigned char val);
		void setReleaseThreshold(unsigned char electrode, unsigned char val);
		
		unsigned char setNumDigPins(unsigned char numPins);
		void pinMode(unsigned char electrode, pinf_t mode); 
		void pinMode(unsigned char electrode, int mode); 				
		void digitalWrite(unsigned char electrode, unsigned char val);
		
		
		bool getTouchStatus(unsigned char electrode);
		unsigned int getTouchStatus();
		
		void setRegister(unsigned char r, unsigned char v);
		volatile unsigned char getRegister(unsigned char r);


};

extern MPR121_t MPR121;

#endif