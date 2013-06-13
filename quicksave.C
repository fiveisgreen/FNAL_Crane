#include <cstring>
TTree* Save(float * array,int length, const char* name);
TTree* Save(int * array,int length, const char* name);
TTree* Save(double * array,int length, const char* name);

float* Get_F(TTree* t, const char* name);
double* Get_D(TTree* t, const char* name);
int* Get_I(TTree* t, const char* name);

TH1F* Array_to_TH1F(float * array, int length, const char* name);
TH1F* Array_to_TH1F(float * array, float* err_array, int length, const char* name);
TH1F* Array_to_TH1F(float * array, float* err_array, const char* name, int length, float* binning);

float* TH1F_to_Array(TH1F* hist, int nbins);
float* TH1Ferr_to_Array(TH1F* hist, int nbins);

float * ArrayDiv(float* num,float* den, int length);
float * ArrayDivError(float* num,float* den, int length);
//xxxxxxxxxxxxxxxxxxxx
TTree* Save(float * array,int length, const char* name){
		//takes an array of length l, 
		//makes a ttree with only one branch "name"
		//and returns that ttree. 
		//this makes a package that can be easily passed through a root file. 
	string T = "t";
	TTree *t = new TTree((T+name).c_str(),"floats");
	float temp;
	t->Branch(name,&temp);
	for (int i=0; i<length; i++) {
		temp = array[i];
		t->Fill();
	}
	return t;
}

TTree* Save(int * array,int length, const char* name){
	string T = "t";
	TTree *t = new TTree((T+name).c_str(),"ints");
	float temp;
	t->Branch(name,&temp);
	for (int i=0; i<length; i++) {
		temp = array[i];
		t->Fill();
	}
	return t;
}

TTree* Save(double * array,int length, const char* name){
	string T = "t";
	TTree *t = new TTree((T+name).c_str(),"doubles");
	float temp;
	t->Branch(name,&temp);
	for (int i=0; i<length; i++) {
		temp = array[i];
		t->Fill();
	}
	return t;
}

float* Get_F(TTree* t, const char* name){
		//takes a ttree with float branch "name" and fills the entire branch into an array. 
		//only use this on short ttrees!
	cout<<"in Get_F"<<endl;
	int nentries = t->GetEntriesFast(); //segfault here
	cout<<"got entries fast"<<endl;
	float* array = new float[nentries];
	cout<<"made array"<<endl;
	float temp;
	TBranch  *b_temp;
	cout<<"a"<<endl;
        t->SetBranchAddress(name, &temp, &b_temp);
	cout<<"b"<<endl;
	for (int jentry=0; jentry<nentries;jentry++) {
		cout<<"jentry "<<jentry<<endl;
		t->GetEntry(jentry);
		cout<<"got entry"<<endl;
                if (temp==temp) array[jentry] = temp;
                else    array[jentry] = -1.f;
	}
	cout<<"fin Get_F"<<endl;
	return array;
}

double* Get_D(TTree* t, const char* name){
                //takes a ttree with double branch "name" and fills the entire branch into an array. 
                //only use this on short ttrees!
        int nentries = t->GetEntriesFast();
        double* array = new double[nentries];
        double temp;
        TBranch  *b_temp;
        t->SetBranchAddress(name, &temp, &b_temp);
        for (int jentry=0; jentry<nentries;jentry++) {
                t->GetEntry(jentry);
                if (temp==temp) array[jentry] = temp;
                else    array[jentry] = -1.f;
        }
        return array;
}

int* Get_I(TTree* t, const char* name){
                //takes a ttree with int branch "name" and fills the entire branch into an array. 
                //only use this on short ttrees!
        int nentries = t->GetEntriesFast();
        int* array = new int[nentries];
        int temp;
        TBranch  *b_temp;
        t->SetBranchAddress(name, &temp, &b_temp);
        for (int jentry=0; jentry<nentries;jentry++) {
                t->GetEntry(jentry);
                if (temp==temp) array[jentry] = temp;
                else    array[jentry] = -1;
        }
        return array;
}

TH1F* Array_to_TH1F(float * array, int length, const char* name){
		//package an array of floats as a TH1F. Don't fill the overflow and underflow bins. 
	TH1F* hist = new TH1F(name,"",length,0.f,(float)length);
	for (int i=0; i<length; i++) hist->SetBinContent(i+1,array[i]);
	return hist;
}
TH1F* Array_to_TH1F(float * array, float* err_array, int length, const char* name){
		//package an array of floats as a TH1F. Don't fill the overflow and underflow bins. 
	TH1F* hist = new TH1F(name,"",length,0.f,(float)length);
	for (int i=0; i<length; i++){
		 hist->SetBinContent(i+1,array[i]);
		 hist->SetBinError(i+1,err_array[i]);
	}
	return hist;
}
TH1F* Array_to_TH1F(float * array, float* err_array, const char* name, int length, float* binning){
                //package an array of floats as a TH1F. Don't fill the overflow and underflow bins. 
        TH1F* hist = new TH1F(name,"",length,binning);
        for (int i=0; i<length; i++){
                 hist->SetBinContent(i+1,array[i]);
                 hist->SetBinError(i+1,err_array[i]);
        }
        return hist;
}


float* TH1F_to_Array(TH1F* hist, int nbins){
	float * out = new float[nbins];
	for (int i=0; i<nbins;i++) out[i] = hist->GetBinContent(i+1);
	return out;
}
float* TH1Ferr_to_Array(TH1F* hist, int nbins){
	float * out = new float[nbins];
	for (int i=0; i<nbins;i++) out[i] = hist->GetBinError(i+1);
	return out;
}



float * ArrayDiv(float* num,float* den, int length){
        float* out = new float[length];
        for(int i=0;i<length;i++) out[i] = num[i]/den[i];
        return out;
}

float * ArrayDivError(float* num,float* den, int length){
        float* out = new float[length];
        for(int i=0;i<length;i++){
                out[i] = (num[i]/den[i])*sqrt((1.f/num[i])+(1.f/den[i]));
        }
        return out;
}



