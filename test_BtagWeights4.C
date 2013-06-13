#include "BTagWeight4.h"


/// Taggers MUST be sorted from looser to tigther in efficiency
/// i.e. t[0] could be CSVL and t[1] CSVT

class BTagWeight2L1TSel : public BTagWeight
{
public:
 BTagWeight2L1TSel(int nTaggers_):BTagWeight(nTaggers_) {}
 bool filter(std::vector<int> t)
 {
   return t[0] >=2 && t[1] >= 1;
// return (t >= minTags && t <= maxTags);
 }

};


int main()
{


//dummy usage example, equivalent to the other version
BTagWeight2L1TSel b(2);
BTagWeight::JetInfo bjl(0.6,1.00);
BTagWeight::JetInfo cjl(0.08,1.0);
BTagWeight::JetInfo ljl(0.01,1.0);
BTagWeight::JetInfo bjt(0.45,0.94);
BTagWeight::JetInfo cjt(0.03,1.0);
BTagWeight::JetInfo ljt(0.001,1.0);

vector<BTagWeight::JetInfo> bj;
bj.push_back(bjl);
bj.push_back(bjt);
vector<BTagWeight::JetInfo> cj;
cj.push_back(cjl);
cj.push_back(cjt);
vector<BTagWeight::JetInfo> lj;
lj.push_back(ljl);
lj.push_back(ljt);

 for(int ib=2;ib<3;ib++)
  for(int ic=0;ic<1;ic++)
   for(int il=0;il<1;il++)
    {
      vector<vector<BTagWeight::JetInfo> > j;
      for(int i=0;i<ib;i++)j.push_back(bj);
      for(int i=0;i<ic;i++)j.push_back(cj);
      for(int i=0;i<il;i++)j.push_back(lj);

/* for(int ibt=0;ibt<ib;ibt++)
  for(int ict=0;ict<ic;ict++)
   for(int ilt=0;ilt<il;ilt++)
   { 
  */

      std::cout << ib << "   " << ic << "  " << "  " << il << "  " << b.weight(j) << " +- " <<  0 << std::endl;
   }
return 0;
}
