// Arthur
#ifndef MEMORYTRACER_H
#define	MEMORYTRACER_H

#include "../CommonLib/CommonDef.h"

#include <fstream>
#include <string>
#include <iostream>
#include <sstream>

class MemoryTracer {
private:
    
    static std::fstream fp;
    static std::string videoSequence;

public:
    
    static bool firstOrRasterSearchFlag;
    
    MemoryTracer();
    
    static void init(std::string fileName, unsigned int wFrame, unsigned int hFrame, unsigned int searchRange);
    static void finalize();

    static void setVideoSequence(std::string videoFile);
    
    static void initFrame(int idCurrFrame);
    static void initCTU(int xLCU, int yLCU);
    static void initCU(int xCU, int yCU, int depthCU, int widthCU, int heightCU);
    static void initPU(int idPart, int sizePU, int idRefFrame);
    static void insertFirstSearch(int itId);
    static void insertCandidate(int xCand, int yCand);
    static void insertRasterSearch(int xLeft, int xRight, int yTop, int yBottom, int rasterStep);
    static void finalizeCTU();
    static void finalizeFrame();
	static void finalizeCU();
	static void finalizePU();

    static void debug(std::string text);
	
};

#endif	/* MEMORYTRACER_H */