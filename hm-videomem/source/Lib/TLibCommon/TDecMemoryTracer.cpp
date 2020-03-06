#include "TDecMemoryTracer.h"

std::fstream TDecMemoryTracer::fp;
Int TDecMemoryTracer::xCurrCU, TDecMemoryTracer::yCurrCU, TDecMemoryTracer::sizeCurrCU;
std::string TDecMemoryTracer::videoSequence;

TDecMemoryTracer::TDecMemoryTracer() {
}

void TDecMemoryTracer::init(std::string fileName, UInt wFrame, UInt hFrame) {
	fp.open(fileName.c_str(), std::fstream::out);
	
	std::string outStr = "";
	
	std::stringstream ss;
	ss << videoSequence << " ";
	ss << wFrame << " ";
	ss << hFrame << std::endl;
	
	outStr += ss.str();
	fp << outStr;
}

void TDecMemoryTracer::setVideoSequence(std::string videoFile) {
	int initPos = videoFile.rfind("/");
	videoSequence = videoFile.substr(initPos+1);
}

void TDecMemoryTracer::debug(std::string sss) {
	fp << sss;
}

void TDecMemoryTracer::initFrame(Int idCurrFrame) {
	std::string outStr = "FRAME ";
	
	std::stringstream ss;
	ss << idCurrFrame << std::endl;
	outStr += ss.str();
	fp << outStr;
}

void TDecMemoryTracer::initCTU(Int xLCU, Int yLCU) {
	std::string outStr = "CTU ";
	
	std::stringstream ss;
	ss << xLCU << " ";
	ss << yLCU << std::endl;
	
	outStr += ss.str();
	fp << outStr;
}

void TDecMemoryTracer::initCU(Int xCU, Int yCU, std::string predMode, Int width, std::string partSize) {
	std::string outStr = "CU ";
	
	std::stringstream ss;
	ss << xCU << " ";
	ss << yCU << " ";
	ss << predMode << " ";
	ss << partSize << " ";
	ss << width << std::endl;
	
	outStr += ss.str();
	fp << outStr;

	xCurrCU = xCU;
	yCurrCU = yCU;
	sizeCurrCU = width;
}

void TDecMemoryTracer::traceMCBlock(Int idRefFrame, Int xPos, Int yPos, Int width, Int height){
	traceMCBlockPerComponent("Y", idRefFrame, xPos, yPos, width, height);
	traceMCBlockPerComponent("Cb", idRefFrame, xPos, yPos, width, height);
	traceMCBlockPerComponent("Cr", idRefFrame, xPos, yPos, width, height);
}

void TDecMemoryTracer::traceMCBlockPerComponent(std::string comp, Int idRefFrame, Int xPos, Int yPos, Int width, Int height) {
	std::string outStr = "MC ";

	std::stringstream ss;
	ss << comp << " ";
	ss << idRefFrame << " ";
	if(comp.compare("Y") == 0 ) {
		ss << xPos << " ";
		ss << yPos << " ";
		ss << width << " ";
		ss << height << std::endl;
	}
	else {
		ss << int(xPos / 2) << " ";
		ss << int(yPos / 2) << " ";
		ss << int(width / 2) << " ";
		ss << int(height / 2) << std::endl;
	}

	outStr += ss.str();
	fp << outStr;
}

//TODO extend it to distinctly support Y and Cb/Cr 
void TDecMemoryTracer::traceIntraReferences(Int xPos, Int yPos, Int size) {
	traceIntraReferencesPerComponent("Y", xPos, yPos, size);
	traceIntraReferencesPerComponent("Cb", xPos, yPos, size);
	traceIntraReferencesPerComponent("Cr", xPos, yPos, size);
}

void TDecMemoryTracer::traceIntraReferencesPerComponent(std::string comp, Int xPos, Int yPos, Int size) {
	fp << "IH " << comp << " ";
	
	if(comp.compare("Y") != 0) {
		size = size / 2;
		xPos = xPos / 2;
		yPos = yPos / 2;
	}

	traceIntraSample(xPos-1, yPos-1);
	traceIntraSample(xPos + size * 2, yPos-1);

	fp << std::endl;

	fp << "IV " << comp << " ";
	
	traceIntraSample(xPos-1, yPos);
	traceIntraSample(xPos-1, xPos + size * 2);

	fp << std::endl;

	/*for(Int x = xPos-1; x < xPos + size * 2 + 1; x++) {
		traceIntraSample(x, yPos-1);
	}
	for(Int y = yPos; y < yPos + size * 2 + 1; y++) {
		traceIntraSample(xPos-1, y);
	}*/

}

void TDecMemoryTracer::traceIntraSample(Int xPos, Int yPos) {		
	fp << xPos << " " << yPos << " ";
}

void TDecMemoryTracer::finalizeCU() {
	finalizeCUPerComp("Y");
	finalizeCUPerComp("Cb");
	finalizeCUPerComp("Cr");
}

void TDecMemoryTracer::finalizeCUPerComp(std::string comp) {
	fp << "WR" << " ";
	fp << comp << " ";
	if(comp.compare("Y") == 0) {
		fp << xCurrCU << " ";
		fp << yCurrCU << " ";
		fp << sizeCurrCU << std::endl;
	}
	else {
		fp << xCurrCU/2 << " ";
		fp << yCurrCU/2 << " ";
		fp << sizeCurrCU/2 << std::endl;
	}

}