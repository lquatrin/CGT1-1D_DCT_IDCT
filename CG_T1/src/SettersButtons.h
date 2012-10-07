/*Arquivo contendo os componentes para setar
o tamanho do vetor que será editado e inciar o arquivo wav*/

#ifndef __SETTERS_BUTTONS___H____
#define __SETTERS_BUTTONS___H____

#include <SCV/Button.h>
#include "WAVReader.h"
#include <SCV/Panel.h>
#include <SCV/RadioButton.h>
#include "Values.h"
#include <SCV/Spinner.h>

/*Classe que seta o tamanho do vetor para 8*/
class RadioButton8 : public scv::RadioButton {
   public:

      RadioButton8(Values* MValues) : scv::RadioButton(scv::Point(13, 4), false, "8 valores") {
         TValues = MValues;
         setState(true);
      }
      ~RadioButton8() {}
      
      void onValueChange()
      {
         if(getState())
            TValues->changeTo(8);
      }

   protected:
   private:
      Values* TValues;

};

/*Classe que seta o tamanho do vetor para 16*/
class RadioButton16 : public scv::RadioButton {
   public:

      RadioButton16(Values* MValues) : scv::RadioButton(scv::Point(78, 4), false, "16 valores") {
         Values = MValues;
      }
      ~RadioButton16() {}

      void onValueChange()
      {
         if(getState())
         {
            Values->changeTo(16);
         }
      }


   protected:
   private:
       Values* Values;

};

/*Classe que inicia o arquivo wav*/
class ButtonWav : public scv::Button {
   public:

      ButtonWav(Values* MValues,scv::Panel *ap , WAVReader *wr, scv::Label *lreading, ReturnChunkButton *rtb) 
         : scv::Button(scv::Point(0, 10), scv::Point(100, 40), "Abrir arquivo Wav") {
         s = ap;
         _wr = wr;
         _lreading = lreading;
         _rtb = rtb;
      }
      ~ButtonWav() {}

      void onMouseUp(const scv::MouseEvent& evt)
      {
         if(s->isVisible()){
            s->setVisible(false);
            _rtb->setVisible(false);
            _wr->loadWAV();
            _lreading->setVisible(true);
            
         }
      }

   protected:
   private:
      scv::Panel *s;
      WAVReader *_wr;
      ReturnChunkButton *_rtb;
      scv::Label *_lreading;
};

/*Classe que seta o tamanho do vetor para o valor da Spinner que for indicado (a spinner vai de 1 a 1024)*/
class RadioButtonRSV : public scv::RadioButton {
   public:

      RadioButtonRSV(Values* MValues, scv::Spinner *s) : scv::RadioButton(scv::Point(13, 30), false, "Setar Nvalores") {
         Spn1 = s;
         BValues = MValues;
      }
      ~RadioButtonRSV() {}
      
      void onValueChange()
      {
         BValues->changeTo((int)Spn1->getValue());
      }

   protected:
   private:
      scv::Spinner *Spn1;
      Values *BValues;

};

#endif