#ifndef TDECMEMORYTRACER_H
#define	TDECMEMORYTRACER_H

#include <fstream>
#include <string>
#include <iostream>
#include <sstream>

#include "../TLibCommon/TypeDef.h"

class TDecMemoryTracer {
private:
    
    static std::fstream fp;
    static Int xCurrCU, yCurrCU, sizeCurrCU;
    static std::string videoSequence;

public:
    
    TDecMemoryTracer();
    
    static void init(std::string fileName, UInt wFrame, UInt hFrame);
    static void finalize();

    static void setVideoSequence(std::string videoFile);

    static void debug(std::string sss);
    
    static void initFrame(Int idCurrFrame);
    static void initCTU(Int xLCU, Int yLCU);
    static void initCU(Int xCU, Int yCU, std::string predMode, Int width, std::string partSize);

    static void traceMCBlock(Int idRefFrame, Int xPos, Int yPos, Int width, Int height);
    static void traceMCBlockPerComponent(std::string comp, Int idRefFrame, Int xPos, Int yPos, Int width, Int height);
    static void traceIntraReferences(Int xPos, Int yPos, Int size);
    static void traceIntraReferencesPerComponent(std::string comp, Int xPos, Int yPos, Int size);

    static void traceIntraSample(Int xPos, Int yPos);
    
    static void finalizeFrame();
	static void finalizeCTU();
    static void finalizeCU();
    static void finalizePU();

    static void finalizeCUPerComp(std::string comp);
};

#endif	/* TDECMEMORYTRACER_H */