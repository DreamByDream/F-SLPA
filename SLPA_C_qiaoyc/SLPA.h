//============================================================================
// Name        : SLPA.h
// Author      : Jierui Xie (xiej2@rpi.edu)
// Date        : Oct. 2011
// Version     :
// Copyright   : All rights reserved.
// Description : SLPA algorithm for community detection.
// Web Site    : https://sites.google.com/site/communitydetectionslpa/
// Publication:
//             J. Xie, B. K. Szymanski and X. Liu, "SLPA: Uncovering Overlapping Communities in Social Networks via A Speaker-listener Interaction Dynamic Process", IEEE ICDM workshop on DMCCI 2011, Vancouver, CA.
//============================================================================
#ifndef SLPA_H_
#define SLPA_H_

#include "Net.h"
#include "NODE.h"
#include <map>
#include <vector>
#include <utility>
#include <tr1/unordered_map>

#include "MersenneTwister.h"


//---------------------------
//		Multi-threading
//---------------------------
typedef std::tr1::unordered_map<int, int> UOrderedH_INT_INT;

struct thread_data{
	int  startind;
	int  endind;

	int *pIndicator;

	//expect to do sharro copy of the pointers
	vector<vector<int>* > cpm;
	vector<UOrderedH_INT_INT* > vectHTable;
};


class SLPA {
public:
	//---------------------------
	//		network parameters
	//---------------------------
	Net* net;
	string netName;
	string fileName_net;
	string networkPath;

	bool isUseLargestComp; //***
	//---------------------------
	//		SLPA parameters
	//---------------------------
	vector<double> THRS;      //thr
	vector<int> THRCS; 		  //thr count
	bool isSyn;  			  //is synchronous version?
	int maxT;
	int maxRun;
	int versioin;
	//---------------------------
	//		more
	//---------------------------
	string outputDir;

	MTRand mtrand1;
	MTRand mtrand2;

	SLPA(string, vector<double>,int ,int ,string ,bool,int );
	SLPA(string, vector<double>, int, int, string, bool, int, int);
	virtual ~SLPA();

	void start();
	void start_time(); // instrument time recorder into the original code
	void start_qiao_v1(); // modified version by qiao_yuchen

	void pre_initial_THRCS();
	void initWQueue_more();

	//void GLPA_asyn();
	void GLPA_asyn_pointer();
	void GLPA_asyn_pointer_qiao_v1(); // modified version by qiao_yuchen

	int ceateHistogram_selRandMax(const vector<int>& wordsList);
	void post_createWQHistogram_MapEntryList();
	void post_thresholding(vector<pair<int,int> >& pairList, int thrc, vector<int>& WS);

	int selectMostFrequentLabel(map<int, int>& labelsList);

	//need to change
	//vector<vector<int> > post_sameLabelDisconnectedComponents(vector<vector<int> >& cpm);
	//static void show_cpm(vector<vector<int> >& cpm);
	static void sort_cpm(vector<vector<int> >& cpm);

	//cpm pointer function
	vector<vector<int>* > post_removeSubset_UorderedHashTable_cpmpointer(vector<vector<int>* >& cpm);
	static void sort_cpm_pointer(vector<vector<int>* >& cpm);

	void write2txt_CPM_pointer(string fileName,vector<vector<int>* >& cpm);
	void post_threshold_createCPM_pointer(int thrc,string fileName);

	void dothreshold_createCPM(int thrc,vector<vector<int> >& cpm);
	void dothreshold_createCPM_pointer(int thrc,vector<vector<int>* >& cpm);

	static bool isDEBUG;


	//---------------------------
	//		Multi-threading
	//---------------------------
	int numThreads;

	void decomposeTasks(int numTasks,int numThd,int stInds[],int enInds[]);
	static void *removesubset_onethread(void *threadarg);
	vector<vector<int>* > post_removeSubset_UorderedHashTable_cpmpointer_MultiThd(vector<vector<int>* >& cpm);
};

#endif /* SLPA_H_ */
