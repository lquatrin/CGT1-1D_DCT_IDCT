#include "Values.h"
#include <iostream>
#include <sstream>

Values::Values(scv::Label *tL, scv::Label *iL, scv::Label *fL, scv::Spinner *iS, scv::Spinner *fS,scv::Spinner *de,scv::Spinner *ate)
{
   _tL = tL;
   _iL = iL;
   _fL = fL;
   _iS = iS;
   _fS = fS;
   _Sde = de;
   _Sate = ate;
   nValores = 8;
   for( int i = 0; i < 8 ; i ++)
   {
      initialValues.push_back(0);
      dctEditValues.push_back(0);
      dctValues.push_back(0);
      idctValues.push_back(0);
   }
   valIni = 1;
   valFin = 8;
}

void Values::changeTo(int n)
{
   initialValues.clear();
   dctValues.clear();
   dctEditValues.clear();
   idctValues.clear();
   nValores=n;
   for( int i = 0; i < n ; i ++)
   {
      initialValues.push_back(0);
      dctEditValues.push_back(0);
      dctValues.push_back(0);
      idctValues.push_back(0);
   }
   std::stringstream sse;
   sse << (nValores);
   _tL->setString("TamVetor: " + sse.str());

   valIni = 1;
   _iL->setString("posIni: 1");


   _iS->setMaxValue(nValores);
   _iS->setValue(1);
   _fS->setMaxValue(nValores);
   _Sde->setMaxValue(nValores);
   _Sde->setValue(1);
   _Sate->setMaxValue(nValores);
   _Sate->setValue(1);

   if(nValores < 201){
      valFin = nValores;
      _fS->setValue(nValores);
      std::stringstream sse1;
      sse1 << (nValores);
      _fL->setString("posFin: " + sse1.str());
   }else{
      valFin = 200;
      _fS->setValue(200);
      std::stringstream sse1;
      sse1 << (200);
      _fL->setString("posFin: " + sse1.str());
   }   
}

void Values::changeLimits(int i, int f)
{
   valIni = i;
   if(i > f)
   {
      valFin = i;
   }else {
      valFin = f;
   }

   std::stringstream sse;
   sse << (valIni);
   _iL->setString("posIni: " + sse.str());
   std::stringstream sse1;
   sse1 << (valFin);
   _fL->setString("posFin: " + sse1.str());
}