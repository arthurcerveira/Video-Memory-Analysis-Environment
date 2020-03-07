// Arthur
#include "MemoryTracer.h"


std::fstream MemoryTracer::fp;
bool MemoryTracer::firstOrRasterSearchFlag;
std::string MemoryTracer::videoSequence;

MemoryTracer::MemoryTracer() {
}

void MemoryTracer::init(std::string fileName, unsigned int wFrame, unsigned int hFrame, unsigned int searchRange) {
	fp.open(fileName.c_str(), std::fstream::out);
	firstOrRasterSearchFlag = false;
	
	std::string outStr = "";
	
	std::stringstream ss;
    ss << "VVC" << " ";
	ss << videoSequence << " ";
	ss << wFrame << " ";
	ss << hFrame << " ";
	ss << searchRange << std::endl;
	
	outStr += ss.str();
	fp << outStr;
}

void MemoryTracer::finalize() {
	fp.close();
}

void MemoryTracer::setVideoSequence(std::string videoFile) {
	int initPos = videoFile.rfind("/");
	
	videoSequence = videoFile.substr(initPos+1);
}

void MemoryTracer::initFrame(int idCurrFrame) {
	std::string outStr = "I ";
	
	std::stringstream ss;
	ss << idCurrFrame << std::endl;
	outStr += ss.str();
	fp << outStr;
}

void MemoryTracer::initCTU(int xLCU, int yLCU) {
	std::string outStr = "L ";
	
	std::stringstream ss;
	ss << xLCU << " ";
	ss << yLCU << std::endl;
	
	outStr += ss.str();
	fp << outStr;
}

void MemoryTracer::initCU(int xCU, int yCU, int depthCU, int widthCU, int heightCU) {
	std::string outStr = "VU ";
	
	std::stringstream ss;
	ss << xCU << " ";
	ss << yCU << " ";
    ss << widthCU << " ";
	ss << heightCU << " ";
	ss << depthCU << std::endl;
	
	outStr += ss.str();
	fp << outStr;
}

void MemoryTracer::initPU(int idPart, int sizePU, int idRefFrame) {
	std::string outStr = "P ";
	
	std::stringstream ss;
	ss << idRefFrame << std::endl;
	
	outStr += ss.str();
	fp << outStr;
}

void MemoryTracer::insertFirstSearch(int itId) {
	std::string outStr = "F ";
	
	std::stringstream ss;
	ss << itId << std::endl;
	
	outStr += ss.str();
	fp << outStr;
}

void MemoryTracer::insertCandidate(int xCand, int yCand) {
	if(!firstOrRasterSearchFlag) {
		std::string outStr = "C ";
	
		std::stringstream ss;
		ss << xCand << " ";
		ss << yCand << std::endl;
		
		outStr += ss.str();
		fp << outStr;
	}
}

void MemoryTracer::insertRasterSearch(int xLeft, int xRight, int yTop, int yBottom, int rasterStep) {
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

void MemoryTracer::finalizeCTU() {
	fp << "E" << std::endl;
}

void MemoryTracer::finalizePU() {
	fp << "p" << std::endl;
}

void MemoryTracer::finalizeCU() {
	fp << "u" << std::endl;
}

void MemoryTracer::finalizeFrame() {
	fp << "i" << std::endl;
}

void MemoryTracer::debug(std::string text) {
	fp << text << std::endl;
}