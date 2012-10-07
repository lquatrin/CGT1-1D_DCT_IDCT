//Componentes referentes ao painel do ArquivoWav que é aberto após o WAV
//ser carregado
#ifndef __WAV__PANEL__COMPONENTS__H___
#define __WAV__PANEL__COMPONENTS__H___

#include <SCV/Spinner.h>
#include <SCV/Button.h>
#include <SCV/RadioButton.h>
#include <SCV/Panel.h>
#include "WAVReader.h"

scv::Panel * _Wpanel = NULL;
/*Classe que seta o tamanho do bloco para pegar de 200*/
class WavRadioButton200 : public scv::RadioButton
{
public:
   WavRadioButton200() : scv::RadioButton(scv::Point(224, 2), true, "blocos de 200")
   {}

   ~WavRadioButton200() {}

   void setPointerWav(long int *t)
   {
      _iWav = t;
   }

   void onValueChange()
   {
      *_iWav = 200;
   }

private:
   long int *_iWav;
};

/*Classe que seta o tamanho do bloco para pegar de 400*/
class WavRadioButton400 : public scv::RadioButton
{
public:
   WavRadioButton400() : scv::RadioButton(scv::Point(224, 17), false, "blocos de 400")
   {}

   ~WavRadioButton400() {}
   void setPointerWav(long int *t)
   {
      _iWav = t;
   }

   void onValueChange()
   {
      *_iWav = 400;
   }

private:
   long int *_iWav;
};

/*Classe que seta o tamanho do bloco para pegar de 600*/
class WavRadioButton600 : public scv::RadioButton
{
public:
   WavRadioButton600() : scv::RadioButton(scv::Point(224, 32), false, "blocos de 600")
   {}

   ~WavRadioButton600() {}

   void setPointerWav(long int *t)
   {
      _iWav = t;
   }

   void onValueChange()
   {
      *_iWav = 600;
   }

private:
   long int *_iWav;
};

/*Classe que seta o tamanho do bloco para pegar de 800*/
class WavRadioButton800 : public scv::RadioButton
{
public:
   WavRadioButton800() : scv::RadioButton(scv::Point(325, 2), false, "blocos de 800")
   {}

   ~WavRadioButton800() {}

   void setPointerWav(long int *t)
   {
      _iWav = t;
   }

   void onValueChange()
   {
      *_iWav = 800;
   }

private:
   long int *_iWav;
};

/*Classe que seta o tamanho do bloco para pegar de 1000*/
class WavRadioButton1000 : public scv::RadioButton
{
public:
   WavRadioButton1000() : scv::RadioButton(scv::Point(325, 17), false, "blocos de 1000")
   {}

   ~WavRadioButton1000() {}

   void setPointerWav(long int *t)
   {
      _iWav = t;
   }

   void onValueChange()
   {
      *_iWav = 1000;
   }

private:
   long int *_iWav;
};

/*Classe que seta o tamanho para que consiga guardar tudo em um bloco apenas*/
class WavRadioButtonAll : public scv::RadioButton
{
public:
   WavRadioButtonAll() : scv::RadioButton(scv::Point(325, 32), false, "Um bloco")
   {}

   ~WavRadioButtonAll() {}

   void setPointerWav(long int *t)
   {
      _iWav = t;
   }

   void onValueChange()
   {
      *_iWav = -1;
   }

private:
   long int *_iWav;
};

/*Classe que fecha o painel do arquivo wav*/
class WavCloseButton : public scv::Button
{
public:
   WavCloseButton(scv::Panel * Wpanel, scv::Panel * AWpanel) : scv::Button(scv::Point(420, 1),scv::Point(500, 24), "Fechar WAV")
   {
      _Wpanel = Wpanel;
      _AWpanel = AWpanel;

   }

   ~WavCloseButton() {}
   
   void onMouseUp(const scv::MouseEvent& evt)
   {
      if(_Wpanel != NULL && _Wpanel->isVisible())
      {
         _Wpanel->setVisible(false);
         _AWpanel->setVisible(true);

      }
   }

private:
   scv::Panel * _AWpanel;
};

/*Classe que ger o out.wav*/
class WAVGenerateOutputButton : public scv::Button
{
public:
   WAVGenerateOutputButton(WAVReader *wvr) : scv::Button(scv::Point(420, 25),scv::Point(500, 47), "Gerar out.WAV")
   {
      _wr = wvr;

   }

   ~WAVGenerateOutputButton() {}
   
   void onMouseUp(const scv::MouseEvent& evt)
   {
      if(_Wpanel != NULL && _Wpanel->isVisible())
      {
         _wr->writeWAV();
      }
   }

private:
   WAVReader *_wr;
};

/*Classe que chama a função de truncamento dos valores*/
class WAVHalfTruncadeButton : public scv::Button
{
public:
   WAVHalfTruncadeButton(WAVReader *wvr, int p, std::string t, int pos) : scv::Button(scv::Point(746, pos),scv::Point(840, pos+20), t)
   {
      _wr = wvr;
      _p = p;

   }

   ~WAVHalfTruncadeButton() {}
   
   void onMouseUp(const scv::MouseEvent& evt)
   {
      if(_Wpanel != NULL && _Wpanel->isVisible())
      {
         _wr->halfTruncade(_p);
      }
   }

private:
   WAVReader *_wr;
   int _p;
};

/*Classe que chama a função para retornar os valores na posição que o usuário havia pego*/
class ReturnChunkButton : public scv::Button
{
public:
   ReturnChunkButton(WAVReader *wreader) : scv::Button(scv::Point(660, 23),scv::Point(745, 47), "Retornar bloco")
   {
      _wreader = wreader;
   }
   ~ReturnChunkButton() {}

   void onMouseUp(const scv::MouseEvent& evt)
   {
      if(_Wpanel != NULL && _Wpanel->isVisible() && isVisible())
      {
         _wreader->returnValuesToWav();
         setVisible(false);
      }
   }
private:
   WAVReader *_wreader;


};

/*Classe que pega os valores de uma posição e passa para o vetor inicial*/
class SetChunkButton : public scv::Button
{
public:
   SetChunkButton(WAVReader *wreader, ReturnChunkButton* rcbt, scv::RadioButton *lc, scv::RadioButton *rc,
      scv::Spinner *chunkValue) : scv::Button(scv::Point(150, 23),scv::Point(220, 47), "Setar bloco")
   {
      _wreader = wreader;
      _rcbt = rcbt;
      _lc = lc;
      _rc = rc;
      _chunkValue = chunkValue;
   }
   ~SetChunkButton() {}

   void onMouseUp(const scv::MouseEvent& evt)
   {
      if(_Wpanel != NULL && _Wpanel->isVisible())
      {
         if(_lc->getState()){
            _wreader->setToValues(0);
         }else if(_rc->getState())
         {
            _wreader->setToValues(1);
         }
         _rcbt->setVisible(true);
      }
   }

private:
   WAVReader *_wreader;
   ReturnChunkButton *_rcbt;
   scv::RadioButton *_rc;
   scv::RadioButton *_lc;
   scv::Spinner *_chunkValue;
};

/*Classe que seta que os valores do canal esquerdo serão copiados*/
class WAVLeftChannelRadioButton : public scv::RadioButton
{
public:
   WAVLeftChannelRadioButton() : scv::RadioButton(scv::Point(0, 5), false, "Left Channel")
   {}

   ~WAVLeftChannelRadioButton() {}


private:

};

/*Classe que seta que os valores do canal direito serão copiados*/
class WAVRightChannelRadioButton : public scv::RadioButton
{
public:
   WAVRightChannelRadioButton() : scv::RadioButton(scv::Point(100, 5), false, "Right Channel")
   {}

   ~WAVRightChannelRadioButton() {}


private:

};

#endif