#include "MyDCTS.h"
#include <math.h>

double Cg_PI = 3.1415926535897932384626433832795028841971693993751058209749;
double InvSQRT2 = 0.7071067811865475244008443621048490392848359376884740365883;

std::vector<double> MyDCTS::DCT(std::vector<double> &vi)
{
   std::vector<double> vf;
   double res = 0;
   int vSize = (int)vi.size();
   double constSqrt = sqrt((2.0/(double)vSize));
   for(int i = 0 ; i < vSize ; i++){
      res = 0;
      for(int t = 0 ; t < vSize ; t++){
         res += vi.at(t) * cos( ((((2.0*(double)t)+1.0)*(double)i)*Cg_PI)    / (2.0*(double)vSize)   );
      }
      if(i == 0)
      {
         vf.push_back(constSqrt*InvSQRT2*res);
      } else {
         vf.push_back(constSqrt*res);
      }
   }
   return vf;
}  
   

/*Para truncar os valores, basta setar como zero*/
std::vector<double> MyDCTS::IDCT(std::vector<double> &vi)
{
   std::vector<double> vf;
   double res = 0;
   int vSize = (int)vi.size();
   double constSqrt = sqrt((2.0/(double)vSize));
   for(int i = 0 ; i < vSize ; i++){
      res = 0;
      for(int t = 0 ; t < vSize ; t++){
         if(t == 0){
            res += vi.at(t) * InvSQRT2 * cos( ((((2.0*(double)i)+1.0)*(double)t)*Cg_PI)    / (2.0*(double)vSize)   );
         } else {
            res += vi.at(t) * cos( ((((2.0*(double)i)+1.0)*(double)t)*Cg_PI)    / (2.0*(double)vSize)   );
         }
      }
      vf.push_back(constSqrt*res);
   }
   return vf;
}