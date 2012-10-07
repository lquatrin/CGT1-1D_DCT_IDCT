/*Classe contendo os valores dos vetores dos 4 canvas mostrados na tela
initialValues - Vetor original
dctValues - vetor dct
dctEditValue - vetor dct porém no gráfico editável
idctValues - vetor idct*/
#ifndef __VALUES_CG__H__
#define __VALUES_CG__H__

#include <SCV/Spinner.h>
#include <SCV/Label.h>
#include <vector>
#include "MyDCTS.h"

class Values
{
public:
   Values(scv::Label *tL, scv::Label *iL, scv::Label *fL, scv::Spinner *iS, scv::Spinner *fS,scv::Spinner *de,scv::Spinner *ate);
   
   std::vector<double> initialValues;
   std::vector<double> dctValues;
   std::vector<double> dctEditValues;
   std::vector<double> idctValues;
   int nValores;
   //Mudar a quantidade de valores dos vetores
   void changeTo(int n);
   //mudar a posição inicial e final que será desenhada nos canvas
   void changeLimits(int i, int f);
   //limites dos gráficos
   double valIni;
   double valFin;
private:
   scv::Label *_tL;
   scv::Label *_iL;
   scv::Label *_fL;
   scv::Spinner *_iS;
   scv::Spinner *_fS;
   scv::Spinner *_Sde;
   scv::Spinner *_Sate;
};

#endif