#ifndef BTAGWEIGHT4
#define BTAGWEIGHT4
#include <math.h>
#include <iostream>
#include <vector>
using namespace std;
class BTagWeight
{
public:
	struct JetInfo {
			//		JetInfo(float mceff,float datasf,float t=0.) : eff(mceff), sf(datasf) , tag(t){}
		JetInfo(){}
		JetInfo(float mceff,float datasf) : eff(mceff), sf(datasf) {return;}
		~JetInfo(){}
		float eff; // probability of passing b-tag. may be eff or mistag rate.
		float sf; //   (eff in MC)/(eff in Data)
	};

	BTagWeight(int nTaggers_, int nJetRequirement_, std::vector<int> bTagRequirement_) :
	nTaggers(nTaggers_), nJetRequirement(nJetRequirement_) {
		for(int kTag = 0; kTag<nTaggers_;kTag++){
			bTagRequirement.push_back(bTagRequirement_[kTag]);
			bReqType.push_back(0);
		}
		nJetsMax = 1000;
		light_jet_mode = false;
	}
	BTagWeight(int nTaggers_, int nJetRequirement_, std::vector<int> bTagRequirement_,std::vector<short> bReqType_ ):
	nTaggers(nTaggers_), nJetRequirement(nJetRequirement_) {
		for(int kTag = 0; kTag<nTaggers_;kTag++){
			bTagRequirement.push_back(bTagRequirement_[kTag]);
			bReqType.push_back(bReqType_[kTag]);
		}
		nJetsMax = 1000;
		light_jet_mode = false;
	}
	BTagWeight(int nTaggers_, int nJetRequirement_,int nJetsMax_, std::vector<int> bTagRequirement_,std::vector<short> bReqType_ ):
	nTaggers(nTaggers_), nJetRequirement(nJetRequirement_),nJetsMax(nJetsMax_) {
		for(int kTag = 0; kTag<nTaggers_;kTag++){
			bTagRequirement.push_back(bTagRequirement_[kTag]);
			bReqType.push_back(bReqType_[kTag]);
		}
		light_jet_mode = false;
	}


		//here we insist that minLFjet-maxLFjet jets are light flavored. 
	BTagWeight(int nTaggers_, int nJetRequirement_,int nJetsMax_,int minLFjet_, int maxLFjet_,
			   std::vector<int> bTagRequirement_,std::vector<short> bReqType_ ):
	nTaggers(nTaggers_), nJetRequirement(nJetRequirement_),nJetsMax(nJetsMax_), minLFjet(minLFjet_),maxLFjet(maxLFjet_) {
		for(int kTag = 0; kTag<nTaggers_;kTag++){
			bTagRequirement.push_back(bTagRequirement_[kTag]);
			bReqType.push_back(bReqType_[kTag]);
		}
		light_jet_mode = true;
	}



	virtual bool filter(vector<int> tags_counter);
	/*Take a count of how many of each type of tagger the event passes, return if it passes filter
	 loosest tagger is 0th, the rest are ordered by tightness*/
	float weight(vector<vector<BTagWeight::JetInfo> > jets);
	/*vector[njets long] of vectors [nTaggers] long of JetInfo for each such jet with each such tagger*/
private:
	int nTaggers;
	/*how many types of B-taggers we're dealing with.
	 For instance, if you have CSVL and CSVM in your filter, nTaggers = 2*/
	int nJetRequirement; //require >= nJetRequirement or we just assume the event is junk and summarily return 1
	int nJetsMax; //require <= nJetsMax
	std::vector<int> bTagRequirement;//length nTaggers. require >=bTagRequirement[kTag]
		//If you require a medium and two loose besides, that's [3,1]. The medium counts as a L.
	std::vector<short> bReqType;//length nTaggers. if 0, require >= that number of b-tags, if 1, require == that number (if 2, require <= that number)

	bool light_jet_mode;
	int minLFjet;
	int maxLFjet;
	float weight_LFmode(vector<vector<BTagWeight::JetInfo> > jets);
};


bool BTagWeight::filter(std::vector<int> t){
		//if bReqType == 0, as usual, nb's >= req
		//if bReqType == 1, as usual, nb's == req
		//if bReqType == 2, as usual, nb's <= req
	bool pass = true;
	for(int kTag = 0; kTag<nTaggers;kTag++){
		switch (bReqType[kTag]){
			case 0:
				pass &= t[kTag] >= bTagRequirement[kTag];
				break;
			case 1:
				pass &= t[kTag] == bTagRequirement[kTag];
				break;
			case 2:
				pass &= t[kTag] <= bTagRequirement[kTag];
				break;
			default:
				pass &= t[kTag] >= bTagRequirement[kTag];
				break;
		}//end switch
	}
	if (light_jet_mode) {
		pass &= t.back() >= minLFjet && t.back() <=maxLFjet;
	}
	return pass;
}

float BTagWeight::weight(vector<vector<BTagWeight::JetInfo> > jets){
	/*
	 Here we take a list of njets; for each jet we have a list of it's eff and SF for
	 each possible tagger. So given an event with jets, we take in a list with an entry
	 for each jet, giving the JetInfo (eff, SF) for such a jet under each tagger.
	 We then consider hypothetical jets with the same properties, run through all
	 combinations of what they could pass, and figure the probability that such a combination
	 would pass the fitler.
	 */
	if (light_jet_mode) return weight_LFmode(jets);

	const int njets=jets.size();
	if( njets < nJetRequirement || njets > nJetsMax || njets<=0) return 1.;

	int combination[njets];//	std::vector<int> combination(jets.size());
	for(int iJet=0;iJet < njets; iJet++) combination[iJet]=0;
	/*
	 combination is a list[njets] telling tagger what each hypothetical jet passed.
	 0 = did not pass any b-tagger
	 1 = passed the loosest tagger only
	 ...
	 2 = passed the tightest tagger
	 So it's max val = nTaggers unless you hit the stop condition for the while loop.
	 We assume that the taggers are already sorted loosest to tightest.
	 */
	int itterator_position=0;
		//used to itterat the combination.

	float prob_pass_for_MC=0;//probability for MC that such a comb passed the filter
	float prob_pass_for_Data=0;//probability for data that such a comb passed the filter
		//their ratio is the weight we want.


	while(combination[njets-1] < nTaggers+1){  //for every combination.
		/*Say for 3 jets and 3 taggers comb does:
		 [0,0,0]
		 [1,0,0]
		 [2,0,0]
		 [0,1,0]
		 [1,1,0]
		 [2,1,0]
		 [1,2,0]
		 [2,2,0]
		 [0,0,2]
		 ...
		 [2,2,2]
		 //then something different
		 [0,0,3] // which is the stop condition of this while loop.
		 */

			//tags_counter holds a count of how many jets pass each tagger for each combination, indexed by tagger
		std::vector<int> tags_counter; //needs to be a vector for the filter function.
		for(int kTag=0;kTag<nTaggers;kTag++) tags_counter.push_back(0);

			//count how many pass each kind of
			//If we get one M and one L, and no T's, tags_counter = [2,1,0]. The M is counted as a loose.
		for(size_t iJet=0;iJet<(size_t)njets;iJet++){ // loop on jets
			for(int kTag=0;kTag<=combination[iJet]-1; kTag++ ) tags_counter[kTag]++;
		}

		if(filter(tags_counter)){
			float prob_this_comb_passes_MC=1.;
			float prob_this_comb_passes_data=1.;

			for(size_t iJet=0;iJet<(size_t)njets;iJet++){ // loop on jets

					//Calculate the contribution to probability for this jet with this combination
				float ith_Term_MC;
				float ith_Term_Data;
				if(combination[iJet]> 0) //if at least one tagged take the SF for the tightest tagger
				{
					int kTag=combination[iJet]-1; //convert to tagger index
					ith_Term_MC = jets[iJet][kTag].eff;
					ith_Term_Data=jets[iJet][kTag].eff*jets[iJet][kTag].sf;

					if(combination[iJet]< nTaggers){ //if at least one tagged take the SF for the tightest tagger
							//does not pass the tightest tagger. So do eff_M*(1-eff_T/eff_M) = eff_M - eff_T
						int kTag1=kTag+1;
						ith_Term_MC *= 1-jets[iJet][kTag1].eff/jets[iJet][kTag].eff;
						ith_Term_Data*=1-jets[iJet][kTag1].eff/jets[iJet][kTag].eff*jets[iJet][kTag1].sf/jets[iJet][kTag].sf;

					}
				}//end if this jet passes something
				else{ //else they fail even the loosest cut. take the 1-eff SF for the loosest:
					ith_Term_MC  =  1.-jets[iJet][0].eff;
					ith_Term_Data = 1.-jets[iJet][0].eff*jets[iJet][0].sf;
				}

				prob_this_comb_passes_MC   *= ith_Term_MC;
				prob_this_comb_passes_data *= ith_Term_Data;
			}//end for every jet/every entry in combination

			prob_pass_for_MC += prob_this_comb_passes_MC;
			prob_pass_for_Data += prob_this_comb_passes_data;

		}//end if combination passes filter

			//itterate to the next combination.
		while (combination[itterator_position] == nTaggers  && itterator_position+1 < njets) itterator_position++; // find first jets for which we did not already test all configs
		combination[itterator_position]++;  //itterate!!

		for(int iJet=0;iJet<itterator_position;iJet++) combination[iJet]=0;  // reset the tested configs for all previous jets
		itterator_position=0;
	}
	if(prob_pass_for_MC==0) return 0;
	return prob_pass_for_Data/prob_pass_for_MC;
}

float BTagWeight::weight_LFmode(vector<vector<BTagWeight::JetInfo> > jets){
		/*
		 Here we're asking for the weight for the case that we have between minLFjet and maxLFjet light flavor jets
		 and the rest can be whatever they like. 
		 particularly: 
		 2+ light 
		 2-3 light
		 2-3 Jets, 2+ light
		 2-5 jets, 2+ light

		 */

	/*
	 Here we take a list of njets; for each jet we have a list of it's eff and SF for
	 each possible tagger. So given an event with jets, we take in a list with an entry
	 for each jet, giving the JetInfo (eff, SF) for such a jet under each tagger.
	 We then consider hypothetical jets with the same properties, run through all
	 combinations of what they could pass, and figure the probability that such a combination
	 would pass the fitler.
	 */
	nJetRequirement = max(nJetRequirement,minLFjet);
	nJetsMax = max(nJetsMax,minLFjet);

	const int njets=jets.size();
	if( njets < nJetRequirement || njets > nJetsMax || njets<=0) return 1.;

	int combination[njets];//	std::vector<int> combination(jets.size());
	for(int iJet=0;iJet < njets; iJet++) combination[iJet]=0;
	/*
	 combination is a list[njets] telling tagger what each hypothetical jet passed.
	 0 = did not pass any b-tagger
	 1 = passed the loosest tagger only
	 ...
	 2 = passed the tightest tagger
	 So it's max val = nTaggers unless you hit the stop condition for the while loop.
	 We assume that the taggers are already sorted loosest to tightest.
	 */
	int itterator_position=0;
		//used to itterat the combination.

	float prob_pass_for_MC=0;//probability for MC that such a comb passed the filter
	float prob_pass_for_Data=0;//probability for data that such a comb passed the filter
		//their ratio is the weight we want.


	while(combination[njets-1] < nTaggers+1){  //for every combination.
		/*Say for 3 jets and 3 taggers comb does:
		 [0,0,0]
		 [1,0,0]
		 [2,0,0]
		 [0,1,0]
		 [1,1,0]
		 [2,1,0]
		 [1,2,0]
		 [2,2,0]
		 [0,0,2]
		 ...
		 [2,2,2]
		 //then something different
		 [0,0,3] // which is the stop condition of this while loop.
		 */

			//tags_counter holds a count of how many jets pass each tagger for each combination, indexed by tagger
		std::vector<int> tags_counter; //needs to be a vector for the filter function.
		for(int kTag=0;kTag<=nTaggers;kTag++) tags_counter.push_back(0);////0 = #L, 1 = #M, 2 = #T, last is reserved for n_light flavored

			//count how many pass each kind of
			//If we get one M and one L, and no T's, tags_counter = [2,1,0]. The M is counted as a loose.
		for(size_t iJet=0;iJet<(size_t)njets;iJet++){ // loop on jets
			for(int kTag=0;kTag<=combination[iJet]-1; kTag++ ) tags_counter[kTag]++;
			if(combination[iJet]==0) tags_counter.back()++; //count how many fail are not b-tagged. 
		}

		if(filter(tags_counter)){
			float prob_this_comb_passes_MC=1.;
			float prob_this_comb_passes_data=1.;

			for(size_t iJet=0;iJet<(size_t)njets;iJet++){ // loop on jets

					//Calculate the contribution to probability for this jet with this combination
				float ith_Term_MC;
				float ith_Term_Data;
				if(combination[iJet]> 0) //if at least one tagged take the SF for the tightest tagger
				{
					int kTag=combination[iJet]-1; //convert to tagger index
					ith_Term_MC = jets[iJet][kTag].eff;
					ith_Term_Data=jets[iJet][kTag].eff*jets[iJet][kTag].sf;

					if(combination[iJet]< nTaggers){ //if at least one tagged take the SF for the tightest tagger
							//does not pass the tightest tagger. So do eff_M*(1-eff_T/eff_M) = eff_M - eff_T
						int kTag1=kTag+1;
						ith_Term_MC *= 1-jets[iJet][kTag1].eff/jets[iJet][kTag].eff;
						ith_Term_Data*=1-jets[iJet][kTag1].eff/jets[iJet][kTag].eff*jets[iJet][kTag1].sf/jets[iJet][kTag].sf;

					}
				}//end if this jet passes something
				else{ //else they fail even the loosest cut. take the 1-eff SF for the loosest:
					ith_Term_MC  =  1.-jets[iJet][0].eff;
					ith_Term_Data = 1.-jets[iJet][0].eff*jets[iJet][0].sf;
				}

				prob_this_comb_passes_MC   *= ith_Term_MC;
				prob_this_comb_passes_data *= ith_Term_Data;
			}//end for every jet/every entry in combination

			prob_pass_for_MC += prob_this_comb_passes_MC;
			prob_pass_for_Data += prob_this_comb_passes_data;

		}//end if combination passes filter

			//itterate to the next combination.
		while (combination[itterator_position] == nTaggers  && itterator_position+1 < njets) itterator_position++; // find first jets for which we did not already test all configs
		combination[itterator_position]++;  //itterate!!

		for(int iJet=0;iJet<itterator_position;iJet++) combination[iJet]=0;  // reset the tested configs for all previous jets
		itterator_position=0;
	}
	if(prob_pass_for_MC==0) return 0;
	return prob_pass_for_Data/prob_pass_for_MC;

}

#endif
