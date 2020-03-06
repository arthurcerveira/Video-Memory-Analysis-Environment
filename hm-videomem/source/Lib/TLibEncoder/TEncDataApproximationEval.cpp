#include <list>

#include "TEncDataApproximationEval.h"

long long int TEncDataApproximationEval::numOfCalls, TEncDataApproximationEval::numOfErrors;

Pel* TEncDataApproximationEval::backup;
Pel* TEncDataApproximationEval::faulty;

Int TEncDataApproximationEval::stride;
Int TEncDataApproximationEval::width, TEncDataApproximationEval::height;
	
std::fstream TEncDataApproximationEval::fout;

bool TEncDataApproximationEval::firstFrameFlag;

UInt TEncDataApproximationEval::faultOcc;

Int TEncDataApproximationEval::iSrchRngHorLeft;
Int TEncDataApproximationEval::iSrchRngHorRight;
Int TEncDataApproximationEval::iSrchRngVerTop;
Int TEncDataApproximationEval::iSrchRngVerBottom;

clock_t TEncDataApproximationEval::resilientKernel;
clock_t TEncDataApproximationEval::totalDuration;

std::list<clock_t> TEncDataApproximationEval::resilientKernelList;

TEncDataApproximationEval::TEncDataApproximationEval() {
}

void TEncDataApproximationEval::init(Int w, Int h) {
	fout.open("approx_debug.txt", std::fstream::out);
	width = w;
	height = h;
	
	firstFrameFlag = true;
	
	backup = new Pel[width * height];
	faulty = new Pel[width * height];
	
	totalDuration = 0;
	resilientKernel = 0;
	totalDuration = 0;
	
	resilientKernelList.clear();
	
	srand(time(NULL));

	numOfCalls = 0;
	numOfErrors = 0;
        
        std::cout << "Error Rate: " << 1.0 / faultOcc << std::endl;
		
}

void TEncDataApproximationEval::close() {

	std::cout << "\n\n\nERROR INJECTION REPORT\n" << numOfErrors << "\n" << numOfCalls << "\n\n\n";

	fout.close();
	
}

void TEncDataApproximationEval::initSearchWindow(TComMv& mvLT, TComMv& mvRB, Int xCU, Int yCU) {
	iSrchRngHorLeft   = mvLT.getHor();
	iSrchRngHorRight  = mvRB.getHor();
	iSrchRngVerTop    = mvLT.getVer();
	iSrchRngVerBottom = mvRB.getVer();
	
}


void TEncDataApproximationEval::saveSearchWindow(Pel* p, Int stride) {
	Pel* pOrig, *pAuxOrig, *pBackup;
	
	
	pOrig = p;
	pOrig += (iSrchRngVerTop * stride);	//point the pointer to the first line of the search window
	
	pBackup = backup;
	
	for (int y = iSrchRngVerTop; y < iSrchRngVerBottom; y++) {
		for (int x = iSrchRngHorLeft; x < iSrchRngHorRight; x++) {
			pAuxOrig = pOrig + x; //point the auxiliar pointer to the right sample inside the search window limits
			*pBackup = *pAuxOrig;
			
			if(faultOcc != 0) {
				Pel faultySample = insertFault(*pAuxOrig);
				*pAuxOrig = faultySample;
			}
						
			pBackup++;
		}
		pOrig += stride;
		
	}
}

void TEncDataApproximationEval::debugReferenceFrame(Pel* p, Int stride) {
	Pel *pOrig = p, *pAuxOrig;	
	
	for (int y = 0; y < height; y++) {
		for (int x = 0; x < width; x++) {
			pAuxOrig = pOrig;
			fout << *pOrig << " ";
			pAuxOrig ++;
		}
		fout << std::endl;
		pOrig += stride;
	}
}

Pel TEncDataApproximationEval::insertFault(Pel sample) {
	Pel masc = 0x0001; //16-bit data

	numOfCalls ++;
	if(faultOcc == 0)
		return sample;
	while(masc != 0x0100) { 
		Int bit = (masc & sample) ? 1 : 0;
		UInt maxRand = rand() % faultOcc;

		if(maxRand == 1) {
			numOfErrors ++;

			if(bit == 0) { //flip the bit from 0 to 1
				sample = sample | masc;
			}
			else { //flip the bit from 1 to 0
				Pel negMasc = ~masc;
				sample = sample & negMasc;
			}
		}				
		masc = masc << 1;
	}
	return sample;
}

void TEncDataApproximationEval::recoverySearchWindow(Pel* p, Int stride) {
	Pel* pOrig, *pAuxOrig, *pBackup;
	pOrig = p;
	pOrig += (iSrchRngVerTop * stride);	//point the pointer to the first line of the search window
	
	pBackup = backup;
	
	for (int y = iSrchRngVerTop; y < iSrchRngVerBottom; y++) {
		for (int x = iSrchRngHorLeft; x < iSrchRngHorRight; x++) {
			pAuxOrig = pOrig + x; //point the auxiliar pointer to the right sample inside the search window limits
			*pAuxOrig = *pBackup;
			
			pBackup++;
		}
		pOrig += stride;
		
		
	}
}

void TEncDataApproximationEval::recoveryFaultySearchWindow(Pel* p, Int stride) {
	Pel* pOrig, *pAuxOrig, *pFaulty;
	pOrig = p;
	pOrig += (iSrchRngVerTop * stride);	//point the pointer to the first line of the search window
	
	pFaulty = faulty;
	
	for (int y = iSrchRngVerTop; y < iSrchRngVerBottom; y++) {
		for (int x = iSrchRngHorLeft; x < iSrchRngHorRight; x++) {
			pAuxOrig = pOrig + x; //point the auxiliar pointer to the right sample inside the search window limits
			*pAuxOrig = *pFaulty;
			
			pFaulty++;
		}
		pOrig += stride;
		
		
	}
}

void TEncDataApproximationEval::printBackupLSamples() {
	Pel *pBackup = backup;	
	
	for (int y = iSrchRngVerTop; y < iSrchRngVerBottom; y++) {
		for (int x = iSrchRngHorLeft; x < iSrchRngHorRight; x++) {
			fout << *pBackup << " ";
			pBackup ++;
		}
		fout << std::endl;
	}
}

void TEncDataApproximationEval::printSearchWindow(Pel* p, Int stride) {
	if(firstFrameFlag) {
		Pel* pAux;
		p += (iSrchRngVerTop * stride);	//point the pointer to the first line of the search window

		for (int y = iSrchRngVerTop; y < iSrchRngVerBottom; y++) {
			for (int x = iSrchRngHorLeft; x < iSrchRngHorRight; x++) {
				pAux = p + x; //point the auxiliar pointer to the right sample inside the search window limits
				fout << *pAux << " ";
			}
			p += stride;
			fout << std::endl;
		}
		firstFrameFlag = false;
	}
	
}

void TEncDataApproximationEval::insertFaults() {
	
	Pel *pBackup = backup;
	Pel *pFaulty = faulty;
	
	for (int y = iSrchRngVerTop; y < iSrchRngVerBottom; y++) {
		for (int x = iSrchRngHorLeft; x < iSrchRngHorRight; x++) {
			
			Pel sample = *pBackup;
			Pel masc = 0x0001; //16-bit data
			
			while(masc != 0x0100) { 
				Int bit = (masc & sample) ? 1 : 0;
				UInt maxRand = rand() % faultOcc;
				
				if(maxRand == 1) {
					if(bit == 0) { //flip the bit from 0 to 1
						sample = sample | masc;
					}
					else { //flip the bit from 1 to 0
						Pel negMasc = ~masc;
						sample = sample & negMasc;
					}
				}				
				masc = masc << 1;
			}
			
			*faulty = sample;
			pFaulty ++;
			pBackup ++;
		}
	}
}

	
