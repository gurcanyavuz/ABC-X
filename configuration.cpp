#include "configuration.h"
#include "rng.h"
#include <tclap/CmdLine.h>
#include <cfloat>
/***********************************************************************************************************************
 * Configuration sınıfı program için gerekli olan parametrelerin dışarıdan alınmasını ve bunların dışarıya sunulduğu
 * metodları içerir. 
 * *********************************************************************************************************************/
//TCLAP dışarıdan alınan parametrelerin belli bir formatta kolayca alınmasını sağlar
using namespace TCLAP;
using namespace std;

	Configuration::Configuration(int argc,char** argv){
		try {
			CmdLine cmd("ABC-X: Configurable Artificial Bee Colony Algorithm Framework", ' ', "1.0");

			//seed degeri: Gerekli
			ValueArg<unsigned long> seedArg("","seed","RNG seed",true,0,"unsigned long"); //true parametresi gerekli oldugunu belirtir
			cmd.add(seedArg);

			//Max. fonksiyon cagirimi: Gerekli
			ValueArg<unsigned int> fesArg("","fes","Maximum number of function evaluations",true,0,"unsigned int");
			cmd.add(fesArg);

			//Yarışma ID'si :Gerekli
			vector<unsigned int> allowedCompetitions;
			allowedCompetitions.push_back(CEC05);
			allowedCompetitions.push_back(CEC08);
			allowedCompetitions.push_back(SOFT_COMPUTING);
			allowedCompetitions.push_back(MIXTURE);
			ValuesConstraint<unsigned int> allowedCompetitionIDVals( allowedCompetitions );

 			ValueArg<unsigned int> cIDArg("","competitionID","Competiton ID",true,0,&allowedCompetitionIDVals);
			cmd.add(cIDArg);

			
			//problemID2 si: Gerekli
			vector<unsigned int> allowedProblems;
			for(int i = 0; i < 50; i++)
			  allowedProblems.push_back( i );
			ValuesConstraint<unsigned int> allowedProblemIDVals( allowedProblems );
			
 			ValueArg<unsigned int> pIDArg("","problemID","Problem ID",true,0,&allowedProblemIDVals);
			cmd.add(pIDArg);


			//Kaotik map ID'si: Gerekli
			vector<unsigned int> allowedCMaps;
			allowedCMaps.push_back( LOGISTIC );
			allowedCMaps.push_back( CIRCLE );
			allowedCMaps.push_back( GAUSS );
			allowedCMaps.push_back( SINUSOIDAL );
			allowedCMaps.push_back( SINUS );
			allowedCMaps.push_back( TEND );
            		allowedCMaps.push_back( HENON );
			allowedCMaps.push_back( ACFUNC);
            		ValuesConstraint<unsigned int> allowedCMapsIDVals( allowedCMaps );
			
 			ValueArg<unsigned int> cmIDArg("","chaoticmap","Chaotic Map ID",false,0,&allowedCMapsIDVals);
			cmd.add(cmIDArg);
			
			//Problem boyutu: Gerekli
 			ValueArg<unsigned int> dimArg("","dimensions","Dimensionality",true,0,"unsigned int");
			cmd.add(dimArg);

			//Problem aralığının minimum degeri: Gerekli 
			ValueArg<double> minRangeArg("","minrange","Minimum value of the search range",true,0,"double");
			cmd.add(minRangeArg);

			//Problem aralığının maksimum degeri: Gerekli
			ValueArg<double> maxRangeArg("","maxrange","Maximum value of the search range",true,0,"double");
			cmd.add(maxRangeArg);

			//Populasyon buyuklugu: Gerekli
			ValueArg<unsigned int> numFoodArg("","nfoods","Number of food sources",true,1000,"unsigned int");
			cmd.add(numFoodArg);

			
			//limit faktoru: Gerekli
			ValueArg<double> limitFArg("","limitF","factor of limit",true,1,"double");
			cmd.add(limitFArg);

			//wMax parametresi: Gerekli degil
			ValueArg<double> wMaxArg("","wMax","parameter wMax",false,0,"double");
			cmd.add(wMaxArg);
			
			//wMin parametresi: Gerekli degil
			ValueArg<double> wMinArg("","wMin","parameter wMin",false,0,"double");
			cmd.add(wMinArg);
			
			//MR parametresi (employed bees): Gerekli degil
			ValueArg<int> mreArg("","MRE","parameter MR (modification ratio)",false,0,"int");
			cmd.add(mreArg);
	
			//MR parametresi (onlooker bees): Gerekli degil
			ValueArg<int> mroArg("","MRO","parameter MR (modification ratio)",false,0,"int");
			cmd.add(mroArg);
			
			ValueArg<int> mreRArg("","MREr","a parameter",false,0,"int");
			cmd.add(mreRArg);
			
			ValueArg<int> mroRArg("","MROr","a parameter",false,0,"int");
			cmd.add(mroRArg);
			
			//kaotik map için mu parametresi: Gerekli degil
			ValueArg<double> muArg("","mu","Mu control parameter",false,0,"double");
			cmd.add(muArg);
			
			//kaotik iterasyon sayısı: Gerekli degil
			ValueArg<unsigned int> KArg("","K","K (chaotic iteration number)",false,0,"unsigned int");
			cmd.add(KArg);

			//Sıraya göre olasılık icin gereken parametre (Rosenbrock ABC'den alınma): Gerekli degil 
			ValueArg<double> spArg("","sp","sp parameter for Rosenbrock ABC",false,0,"double");
			cmd.add(spArg);

			
			//Shaking Factor: Gerekli degil
			ValueArg<double> shakeArg("","shakingfactor","Swarm Shaking Factor",false,0.0,"double");
			cmd.add(shakeArg);

			//Maksimum yiyecek sayısı (artırımlı versiyon için): Gerekli degil
			ValueArg<unsigned int> maxFoodArg("","maxfoodsize","Maximum food size",false,1000,"unsigned int");
			cmd.add(maxFoodArg);

			//Kac iterasyonda bir populasyon artırım: Gerekli degil
			ValueArg<unsigned int> growthArg("","growthperiod","Growth period",false,1,"unsigned int");
			cmd.add(growthArg);

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////77
			//parameter l1e 
			ValueArg<double> l1eArg("","l1e","lower bound of phi_1 emp",false,0,"double");
			cmd.add(l1eArg);
			//parameter l2e 
			ValueArg<double> l2eArg("","l2e","lower bound of phi_2 emp",false,0,"double");
			cmd.add(l2eArg);
			//parameter l3e 
			ValueArg<double> l3eArg("","l3e","lower bound of phi_3 emp",false,0,"double");
			cmd.add(l3eArg);
			
			//parameter l1o 
			ValueArg<double> l1oArg("","l1o","lower bound of phi_1 onl",false,0,"double");
			cmd.add(l1oArg);
			//parameter l2o 
			ValueArg<double> l2oArg("","l2o","lower bound of phi_2 onl",false,0,"double");
			cmd.add(l2oArg);
			//parameter l3o 
			ValueArg<double> l3oArg("","l3o","lower bound of phi_3 onl",false,0,"double");
			cmd.add(l3oArg);

			//what is the first term of search equation: Gerekli 
			vector<unsigned int> allowedFT;
			allowedFT.push_back( CURRENTLOC );
			allowedFT.push_back( RANDOMLOC );
			allowedFT.push_back( GBESTLOC );
            		ValuesConstraint<unsigned int> allowedFTVals( allowedFT );
			
 			ValueArg<unsigned int> fteArg("","firstTE","First term of empoyed bees step search equation",true, 0,&allowedFTVals);
			cmd.add(fteArg);

			ValueArg<unsigned int> ftoArg("","firstTO","First term of onlooker bees step search equation",true, 0,&allowedFTVals);
			cmd.add(ftoArg);

			
			//what is the first term of search equation: Gerekli 
			vector<unsigned int> allowedRN;
			allowedRN.push_back( DEFAULT_RAND );
			allowedRN.push_back( NOTDEFAULT_RAND );

            		ValuesConstraint<unsigned int> allowedRNVals( allowedRN );
			
 			ValueArg<unsigned int> r1eArg("","dr1e","Select default random range for the first term of ABC",true, 0,&allowedRNVals);
			cmd.add(r1eArg);

			ValueArg<unsigned int> r2eArg("","dr2e","Select default random range for the second term of ABC",true, 0,&allowedRNVals);
			cmd.add(r2eArg);

			ValueArg<unsigned int> r3eArg("","dr3e","Select default random range for the third term of ABC",true, 0,&allowedRNVals);
			cmd.add(r3eArg);

 			ValueArg<unsigned int> r1oArg("","dr1o","Select default random range for the first term of ABC",true, 0,&allowedRNVals);
			cmd.add(r1oArg);

			ValueArg<unsigned int> r2oArg("","dr2o","Select default random range for the second term of ABC",true, 0,&allowedRNVals);
			cmd.add(r2oArg);

			ValueArg<unsigned int> r3oArg("","dr3o","Select default random range for the third term of ABC",true, 0,&allowedRNVals);
			cmd.add(r3oArg);

			
			//what is the other terms of search equation: Gerekli 
			vector<unsigned int> allowedOT;
			allowedOT.push_back( GBEST_CURRENT );
			allowedOT.push_back( GBEST_RANDOM );
			allowedOT.push_back( CURRENT_RANDOM );
			allowedOT.push_back( RANDOM_RANDOM );
			allowedOT.push_back( CURRENT_GBESTDIST );
			allowedOT.push_back( NO_STRATEGY );
			
            		ValuesConstraint<unsigned int> allowedOTVals( allowedOT );
			
 			ValueArg<unsigned int> steArg("","secondTE","Second term of empoyed bees step search equation",true, 0,&allowedOTVals);
			cmd.add(steArg);

			ValueArg<unsigned int> stoArg("","secondTO","Second term of onlooker bees step search equation",true, 0,&allowedOTVals);
			cmd.add(stoArg);

 			ValueArg<unsigned int> tteArg("","thirdTE","Second term of empoyed bees step search equation",true, 0,&allowedOTVals);
			cmd.add(tteArg);

			ValueArg<unsigned int> ttoArg("","thirdTO","Second term of onlooker bees step search equation",true, 0,&allowedOTVals);
			cmd.add(ttoArg);

 			ValueArg<unsigned int> foteArg("","fourthTE","Second term of empoyed bees step search equation",true, 0,&allowedOTVals);
			cmd.add(foteArg);

			ValueArg<unsigned int> fotoArg("","fourthTO","Second term of onlooker bees step search equation",true, 0,&allowedOTVals);
			cmd.add(fotoArg);

			
			//what is the other terms of search equation: Gerekli 
			vector<unsigned int> allowedpStr;
			allowedpStr.push_back( DEFAULT_PROBCALC );
			allowedpStr.push_back( WEIGHTED_PROBCALC );
			allowedpStr.push_back( ORDERED_PROBCALC );
            		ValuesConstraint<unsigned int> allowedpStrVals( allowedpStr );
			ValueArg<unsigned int> pctypeArg("","pStr","probability calculation strategy",true, 0,&allowedpStrVals);
			cmd.add(pctypeArg);

			//populasyon artırımlı olsun mu?
			vector<unsigned int> allowedipopStr;
			allowedipopStr.push_back( 0 );
			allowedipopStr.push_back( 1 );
			
            		ValuesConstraint<unsigned int> allowedipopStrVals( allowedipopStr );
			ValueArg<unsigned int> ipopStrArg("","ipop","incremental population or not",true, 0,&allowedipopStrVals);
			cmd.add(ipopStrArg);

			//opposition-based ilkleme eklenecek mi?
			vector<unsigned int> allowedOpInit;
			allowedOpInit.push_back( 0 );
			allowedOpInit.push_back( 1 );
			
            		ValuesConstraint<unsigned int> allowedOpInitStrVals( allowedOpInit );
			ValueArg<unsigned int> oppInitArg("","oinit","add opposition-based initialization or not",true, 0,&allowedOpInitStrVals);
			cmd.add(oppInitArg);

			// MR'nin default degeri 1'dir. Burada MR default degeri ile mi yoksa farkli deger mi almalı belirtiliyor (Employed bee aşaması)
			vector<unsigned int> allowedMRE;
			allowedMRE.push_back( 0 );
			allowedMRE.push_back( 1 );
			allowedMRE.push_back( 2 );
            		ValuesConstraint<unsigned int> allowedMREVals( allowedMRE );
			
			ValueArg<unsigned int> dmreArg("","dmre","default modification rate or not for employeds",true, 0,&allowedMREVals);
			cmd.add(dmreArg);
			// MR'nin default degeri 1'dir. Burada MR default degeri ile mi yoksa farkli deger mi almalı belirtiliyor (Onlooker bee aşaması)
			ValueArg<unsigned int> dmroArg("","dmro","default modification rate or not for onlookers",true, 0,&allowedMREVals);
			cmd.add(dmroArg);

			//scout bee stratejisi ne olacak: Gerekli
			vector<unsigned int> allowedsStr;
			allowedsStr.push_back( DEFAULT_SCOUT );
			allowedsStr.push_back( BABC_SCOUT);
			allowedsStr.push_back( CABC_SCOUT );
			allowedsStr.push_back( IABC_SCOUT );
			allowedsStr.push_back( ERABC_SCOUT );
            		ValuesConstraint<unsigned int> allowedsStrVals( allowedsStr );
			ValueArg<unsigned int> scoutStrArg("","sStr","scout bees step strategy",true, 0,&allowedsStrVals);
			cmd.add(scoutStrArg);

			// ilkleme stratejisi: Gerekli
			vector<unsigned int> allowediStr;
			allowediStr.push_back( DEFAULT_INIT );
			allowediStr.push_back( CHAOTIC_INIT );
			ValuesConstraint<unsigned int> allowediStrVals( allowediStr );
			ValueArg<unsigned int> initStrArg("","iStr","initialization strategy",true, 0,&allowediStrVals);
			cmd.add(initStrArg);
			
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

			//Parses input
			cmd.parse( argc, argv );

			rngSeed = seedArg.getValue();
			maxFES = fesArg.getValue();
			competitionID = cIDArg.getValue();
			
			problemID = pIDArg.getValue();

			problemDimension = dimArg.getValue();
			minInitRange=minRangeArg.getValue();
			maxInitRange=maxRangeArg.getValue();

			numOfFoods = numFoodArg.getValue();
			limitF = limitFArg.getValue();

			wMax = wMaxArg.getValue();
			wMin = wMinArg.getValue();
			
			dmre = dmreArg.getValue();
			mre = mreArg.getValue();
			mrer = mreRArg.getValue();
			
			dmro = dmroArg.getValue();
			mro = mroArg.getValue();
			mror = mroRArg.getValue();
			
			pctype = pctypeArg.getValue();
			scoutStrID = scoutStrArg.getValue();
			initStr = initStrArg.getValue();
			unsigned int ipop = ipopStrArg.getValue();
			
			if(ipop == 1) isIncrementedPop = true;
			else isIncrementedPop = false;
			
			unsigned int oppi = oppInitArg.getValue();
			if(oppi == 1) isOppInit = true;
			else isOppInit = false;

			
			k_param = KArg.getValue();
			mu = muArg.getValue();
			cmapID = cmIDArg.getValue();
			sp = spArg.getValue();
			
			shakingFactor = shakeArg.getValue();
			maxFoodSize = maxFoodArg.getValue();
			growthPeriod = growthArg.getValue();
			
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
			drand1e	     = r1eArg.getValue();
			drand2e	     = r2eArg.getValue();
			drand3e	     = r3eArg.getValue();
			drand1o	     = r1oArg.getValue();
			drand2o	     = r2oArg.getValue();
			drand3o	     = r3oArg.getValue();
			
			randRange1o = l1oArg.getValue();
			randRange2o = l2oArg.getValue();
			randRange3o = l3oArg.getValue();

			randRange1e = l1eArg.getValue();
			randRange2e = l2eArg.getValue();
			randRange3e = l3eArg.getValue();

			firstTermOnl = ftoArg.getValue();
			firstTermEmp = fteArg.getValue();
			secondTermOnl = stoArg.getValue();
			secondTermEmp = steArg.getValue();
			thirdTermOnl = ttoArg.getValue();
			thirdTermEmp = tteArg.getValue();			
			fourthTermOnl = fotoArg.getValue();
			fourthTermEmp = foteArg.getValue();
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////			
			
			if(competitionID == CEC08 && ( problemID > 6 || problemID < 0)){
			  cout<<"There is no problem available more than 7 in CEC08 competition"<<endl;
			  exit(0);
			}

			if(competitionID == CEC05 && ( problemID > 24 || problemID < 0)){
			  cout<<"There is no problem available more than 25 in CEC05 competition"<<endl;
			  exit(0);
			}


			if(competitionID == CEC08 && ( problemID > 18 || problemID < 0)){
			  cout<<"There is no problem available more than 19 in SOCO competition"<<endl;
			  exit(0);
			}


		}catch (TCLAP::ArgException &e)  // catch any exceptions
		{ std::cerr << "error: " << e.error() << " for arg " << e.argId() << std::endl; }
	}

	Configuration::~Configuration(){}

	unsigned long Configuration::getRNGSeed(){
		return rngSeed;
	}
 	unsigned int Configuration::getMaxFES(){
		return maxFES;
	}
	
	unsigned int Configuration::getCompetitionID(){
		return competitionID;
	}
	
	unsigned int Configuration::getProblemID(){
		return problemID;
	}

	unsigned int Configuration::getProblemDimension(){
		return problemDimension;
	}
	
		
	double Configuration::getMinInitRange(){
	  if((getProblemID() == 6 || getProblemID() == 24) && (getCompetitionID() == 0))
		  return LDBL_MAX*-1.0;
			
	    return minInitRange;
	}
	
      	double Configuration::getMaxInitRange(){
		if((getProblemID() == 6 || getProblemID() == 24) && (getCompetitionID() == 0))
		  return LDBL_MAX;
	
		return maxInitRange;
	}
	
	
	double Configuration::getMinInitBound(){
		return minInitRange;
	}
	
      	double Configuration::getMaxInitBound(){
		return maxInitRange;
	}

	unsigned int Configuration::numOfFoodSources(){
		return numOfFoods;
	}
    // changed by tianjun
	unsigned int Configuration::getLimit(){
		return (int)(limitF*numOfFoods*problemDimension);
	}
	

	void Configuration::setStartTime(double stime){
		startTime = stime;
	}

	double Configuration::getStartTime(){
		return startTime;
	}


	double Configuration::getWMax(){
		return wMax;
	}


	double Configuration::getWMin(){
		return wMin;
	}

	
	unsigned int Configuration::getMRE(){
	      if(dmre == 0) // sadece bir eleman değiştir
		  return 1;
	      if(dmre == 1)
		  return mre;
	      else return floor(RNG::randVal(mre, mre+mrer));
	}

	unsigned int Configuration::getMRO(){
	      if(dmro == 0) // sadece bir eleman değiştir
		  return 1;
	      if(dmro == 1)
		  return mro;
	      else return floor(RNG::randVal(mro, mro+mror));
	}
	
	unsigned int Configuration::getK(){
		return k_param;
	}
	
	unsigned int Configuration::getChaoticMapID(){
		return cmapID;
	}
	
	
	double Configuration::getMu(){
		return mu;
	}
	
	
	double Configuration::getSP(){
		return sp;
	}
	
	void Configuration::setCurrentFoodSize(unsigned int newSize){
		numOfFoods = newSize;
	}


	double Configuration::getShakingFactor(){
		return pow(10.0,shakingFactor);
	}

	
	unsigned int Configuration::getMaximumFoodSize(){
		return maxFoodSize;
	}
	
	unsigned int Configuration::getGrowthPeriod(){
		return growthPeriod;
	}

	
	bool Configuration::isDefaultUniformRE1(){ 
	  if(drand1e == DEFAULT_RAND)
	    return true;
	  return false;
	}

	bool Configuration::isDefaultUniformRE2(){ 
	  if(drand2e == DEFAULT_RAND)
	    return true;
	  return false;
	}
	bool Configuration::isDefaultUniformRE3(){ 
	  if(drand3e == DEFAULT_RAND)
	    return true;
	  return false;
	}
	bool Configuration::isDefaultUniformRO1(){ 
	  if(drand1o == DEFAULT_RAND)
	    return true;
	  return false;
	}
	bool Configuration::isDefaultUniformRO2(){ 
	  if(drand2o == DEFAULT_RAND)
	    return true;
	  return false;
	}
	bool Configuration::isDefaultUniformRO3(){ 
	  if(drand3o == DEFAULT_RAND)
	    return true;
	  return false;
	}


	void Configuration::print(){
		cout << "Parameters:" << endl;
		cout << endl;
		cout << "rngSeed = " << rngSeed << endl;
		cout <<	"maxFES = " << maxFES << endl;
		cout << "problemID = " << problemID << endl;
		cout << "problemDimension = " << problemDimension << endl;
		cout << "minInitRange = " << minInitRange << endl;
		cout << "maxInitRange = " << maxInitRange << endl;
		cout << "numberOfFoodSources = " << numOfFoods << endl;
	}


