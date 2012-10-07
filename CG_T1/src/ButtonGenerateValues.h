/*Arquivo referente aos componentes usados 
na geração de valores para a amostra inicial*/
#ifndef ___BUTTON__GENERATE___VALUES__H____
#define ___BUTTON__GENERATE___VALUES__H____

#include <SCV/Button.h>
#include "MyDCTS.h"
#include "Values.h"
#include <SCV/Spinner.h>
#include <SCV/Label.h>

/*Label do gerador de valores*/
class labelGenValues : public scv::Label {
   public:

      labelGenValues() : scv::Label(scv::Point(48, 2), "Gerar Valores") {

      }
      ~labelGenValues() {}

   protected:
   private:

};

/*Seta valores aleatorios para o vetor*/
class RandomValuesButton : public scv::Button {
public:

   RandomValuesButton(Values *MValue) : scv::Button(scv::Point(0, 19),scv::Point(165, 43), "Aleatorios") {
      BValues = MValue;
   }

   ~RandomValuesButton() {}

   void onMouseUp(const scv::MouseEvent& evt);

protected:
private:
   Values *BValues;
   MyDCTS * MDCT;
};

/*Seta valores linearmente crescentes*/
class ButtonLinearlyIncreasing : public scv::Button {
public:

   ButtonLinearlyIncreasing(Values *Values, scv::Spinner* Spin) : scv::Button(scv::Point(0, 47),scv::Point(122, 71), "Linearmente Crescente") {
      BValues = Values;
      SpinB = Spin;
   }

   ~ButtonLinearlyIncreasing() {}

   void onMouseUp(const scv::MouseEvent& evt);

protected:
private:
   Values *BValues;
   scv::Spinner* SpinB;
   MyDCTS *MDCT;
};

/*Seta valores em forma de senoide*/
class ButtonSenoide : public scv::Button {
public:

   ButtonSenoide(Values *Values, scv::Spinner* Spin) : scv::Button(scv::Point(0, 75),scv::Point(122, 99), "Forma de Senoide") {
      BValues = Values;
      SpinB = Spin;
   }
   ~ButtonSenoide() {}

   void onMouseUp(const scv::MouseEvent& evt);

protected:
private:
   Values *BValues;
   scv::Spinner* SpinB;
   MyDCTS *MDCT;
};

/*Seta valores iguais*/
class ButtonSetEqual : public scv::Button {
public:

   ButtonSetEqual(Values *Values, scv::Spinner* Spin) : scv::Button(scv::Point(0, 103),scv::Point(122, 127), "Iguais") {
      BValues = Values;
      SpinB = Spin;
   }
   ~ButtonSetEqual() {}

   void onMouseUp(const scv::MouseEvent& evt);

protected:
private:
   Values *BValues;
   scv::Spinner* SpinB;
   MyDCTS *MDCT;
};

/*Linear Congruential Generators [Xn+1 = a Xn +c(mod m) a->multiplicador c->constante m->módulo*/
class LCGButton : public scv::Button {
public:

   LCGButton(Values *MtValues, scv::Spinner *LCGA, scv::Spinner *LCGC, scv::Spinner *LCGM) : scv::Button(scv::Point(1, 131),scv::Point(165, 155), "LCG - Xn+1 = aXn+c(mod m)") {
      MValues = MtValues;
      _LCGA = LCGA;
      _LCGC = LCGC;
      _LCGM = LCGM;
   }
   ~LCGButton() {}

   void onMouseUp(const scv::MouseEvent& evt);

protected:
private:
   Values* MValues;
   scv::Spinner *_LCGA;
   scv::Spinner *_LCGC;
   scv::Spinner *_LCGM;
   MyDCTS *MDCT;
};

/*Seta valores de acordo com o valor escrito no spinner*/
class ButtonSetKeyboard : public scv::Button {
public:

   ButtonSetKeyboard(scv::Spinner *SPos, scv::Spinner *SVal, Values *MValues) : scv::Button(scv::Point(2, 180), scv::Point(165, 202), "Ponto[x] = Valor") {
      Pos = SPos;
      Val = SVal;
      MyValues = MValues;
   }
   ~ButtonSetKeyboard() {}

   void onMouseUp(const scv::MouseEvent& evt);

protected:
private:
   scv::Spinner *Pos;
   scv::Spinner *Val;
   Values *MyValues;
};

/*Trunca uma parte dos valores do vetor*/
class ButtonTruncadeParts : public scv::Button {
   public:

   ButtonTruncadeParts(scv::Spinner *posIni, scv::Spinner *posFin, Values *MValues) : scv::Button(scv::Point(2, 227), scv::Point(165, 250), "Truncar valores(DCTEdit)") {
      _posIni = posIni;
      _posFin = posFin;
      _MyValues = MValues;
   }
   ~ButtonTruncadeParts() {}

   void onMouseUp(const scv::MouseEvent& evt);

protected:
private:
   scv::Spinner *_posIni;
   scv::Spinner *_posFin;
   Values *_MyValues;

};

#endif