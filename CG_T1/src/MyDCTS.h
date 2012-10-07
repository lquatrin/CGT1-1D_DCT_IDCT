/*Arquivo contendo a classe que tem as 
funções de DCT e IDCT unidimensionais*/
#ifndef __CG__DCTS__
#define __CG__DCTS__

#include <vector>

class MyDCTS
{
public:
   std::vector<double> DCT(std::vector<double> &vi);
   std::vector<double> IDCT(std::vector<double> &vi);
private:
     
};

#endif