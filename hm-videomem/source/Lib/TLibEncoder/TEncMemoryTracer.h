#ifndef TENCMEMORYTRACER_H
#define	TENCMEMORYTRACER_H

#include "../TLibCommon/TypeDef.h"

#include <fstream>
#include <string>
#include <iostream>
#include <sstream>

class TEncMemoryTracer {
private:
    
    static std::fstream fp;
    static std::string videoSequence;

public:
    
    static bool firstOrRasterSearchFlag;
    
    TEncMemoryTracer();
    
    static void init(std::string fileName, UInt wFrame, UInt hFrame, UInt tileCols, UInt tileRows, UInt searchRange);
    static void finalize();

    static void setVideoSequence(std::string videoFile);

    static void initFrame(Int idCurrFrame);
    static void initTile(Int idTile);
    static void initCTU(Int xLCU, Int yLCU, Int idTile);
    static void initCU(Int xCU, Int yCU, Int depthCU);
    static void initPU(Int idPart, Int sizePU, Int idRefFrame);
    static void insertFirstSearch(int itId);
    static void insertCandidate(Int xCand, Int yCand);
    static void insertRasterSearch(int xLeft, int xRight, int yTop, int yBottom, int rasterStep);
    static void finalizeCTU();
    static void finalizeFrame();
	static void finalizeCU();
	static void finalizePU();
    static void debug(std::string text);
	
};

#endif	/* TENCMEMORYTRACER_H */

