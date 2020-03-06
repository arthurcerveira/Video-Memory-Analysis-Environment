#include "TEncMemoryTracer.h"
#include "TEncAnalyze.h"

std::fstream TEncMemoryTracer::fp;
bool TEncMemoryTracer::firstOrRasterSearchFlag;
std::string TEncMemoryTracer::videoSequence;

TEncMemoryTracer::TEncMemoryTracer() {
}

void TEncMemoryTracer::init(std::string fileName, UInt wFrame, UInt hFrame, UInt tileCols, UInt tileRows, UInt searchRange) {
	fp.open(fileName.c_str(), std::fstream::out);
	firstOrRasterSearchFlag = false;
	
	std::string outStr = "";
	
	std::stringstream ss;
	ss << "HEVC" << " ";
	ss << videoSequence << " ";
	ss << wFrame << " ";
	ss << hFrame << " ";
	//ss << tileCols << " ";
	//ss << tileRows << " ";
	ss << searchRange << std::endl;
	
	outStr += ss.str();
	fp << outStr;
}

void TEncMemoryTracer::finalize() {
	fp.close();
}

void TEncMemoryTracer::setVideoSequence(std::string videoFile) {
	int initPos = videoFile.rfind("/");
	
	videoSequence = videoFile.substr(initPos+1);
}

void TEncMemoryTracer::initFrame(Int idCurrFrame) {
	std::string outStr = "I ";
	
	std::stringstream ss;
	ss << idCurrFrame << std::endl;
	outStr += ss.str();
	fp << outStr;
}

void TEncMemoryTracer::initCTU(Int xLCU, Int yLCU, Int idTile) {
	std::string outStr = "L ";
	
	std::stringstream ss;
	ss << xLCU << " ";
	ss << yLCU << std::endl;
	//ss << idTile << std::endl;
	
	outStr += ss.str();
	fp << outStr;
}

void TEncMemoryTracer::initCU(Int xCU, Int yCU, Int depthCU) {
	std::string outStr = "U ";
	
	Int sizeCU = (depthCU == 0) ? 64 :
				 (depthCU == 1) ? 32 :
				 (depthCU == 2) ? 16 :
				 				  8;

	std::stringstream ss;
	ss << xCU << " ";
	ss << yCU << " ";
	ss << sizeCU << std::endl;
	
	outStr += ss.str();
	fp << outStr;
}

void TEncMemoryTracer::initPU(Int idPart, Int sizePU, Int idRefFrame) {
	std::string outStr = "P ";
	
	std::stringstream ss;
	ss << sizePU << " ";
	ss << idPart << " ";
	ss << idRefFrame << std::endl;
	
	outStr += ss.str();
	fp << outStr;
}

void TEncMemoryTracer::insertFirstSearch(Int itId) {
	std::string outStr = "F ";
	
	std::stringstream ss;
	ss << itId << std::endl;
	
	outStr += ss.str();
	fp << outStr;
}

void TEncMemoryTracer::insertCandidate(Int xCand, Int yCand) {
	std::string outStr = "C ";
	
	std::stringstream ss;
	ss << xCand << " ";
	ss << yCand << std::endl;
	
	outStr += ss.str();
	fp << outStr;
}

void TEncMemoryTracer::insertRasterSearch(Int xLeft, Int xRight, Int yTop, Int yBottom, int rasterStep) {
	std::string outStr = "R ";
	
	std::stringstream ss;
	ss << xLeft << " ";
	ss << xRight << " ";
	ss << yTop << " ";
	ss << yBottom << " ";
	ss << rasterStep << std::endl;
	
	outStr += ss.str();
	fp << outStr;
}

void TEncMemoryTracer::finalizeCTU() {
	//fp << "E" << std::endl;
}

void TEncMemoryTracer::finalizePU() {
	//fp << "p" << std::endl;
}

void TEncMemoryTracer::finalizeCU() {
	//fp << "u" << std::endl;
}

void TEncMemoryTracer::finalizeFrame() {
	//fp << "i" << std::endl;
}

void TEncMemoryTracer::debug(std::string text) {
	fp << text << std::endl;
}