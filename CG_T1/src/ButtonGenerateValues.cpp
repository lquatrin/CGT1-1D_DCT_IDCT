#include "ButtonGenerateValues.h"
#include "MyDCTS.h"

void RandomValuesButton::onMouseUp(const scv::MouseEvent& evt)
{
   for(int i = 0; i < (int)BValues->nValores ; i++)
   {
      BValues->initialValues[i] = (rand() % 255);
   }
   BValues->dctValues = MDCT->DCT(BValues->initialValues);
   BValues->dctEditValues = BValues->dctValues;
   BValues->idctValues = MDCT->IDCT(BValues->dctEditValues);
}

void ButtonLinearlyIncreasing::onMouseUp(const scv::MouseEvent& evt)
{
   int s = (int)SpinB->getValue();
   int auxs = s;
   for(int i = 0 ; i < (int)BValues->initialValues.size() ; i++)
   {
      BValues->initialValues[i] = s;
      s += auxs;
      if(s > 255)
      {
         s = 255;
      }
   }
   BValues->dctValues = MDCT->DCT(BValues->initialValues);
   BValues->dctEditValues = BValues->dctValues;
   BValues->idctValues = MDCT->IDCT(BValues->dctEditValues);

}

void ButtonSenoide::onMouseUp(const scv::MouseEvent& evt)
{

   int s = (int)SpinB->getValue();
   for(int i = 0 ; i < (int)BValues->initialValues.size() ; i++)
   {
      BValues->initialValues[i] = s + (int)(((double)s/2.0) * (double)sin((double)i*45.0));
      if(BValues->initialValues[i] >255)
      {
         BValues->initialValues[i] = 255;
      } else if (BValues->initialValues[i] < 0 ){
         BValues->initialValues[i] = 0;
      }
   }
   BValues->dctValues = MDCT->DCT(BValues->initialValues);
   BValues->dctEditValues = BValues->dctValues;
   BValues->idctValues = MDCT->IDCT(BValues->dctEditValues);

}

void ButtonSetEqual::onMouseUp(const scv::MouseEvent& evt)
{
   int s = (int)SpinB->getValue();
   for(int i = 0 ; i < (int)BValues->initialValues.size() ; i++)
   {
      BValues->initialValues[i] = s;
   }
   BValues->dctValues = MDCT->DCT(BValues->initialValues);
   BValues->dctEditValues = BValues->dctValues;
   BValues->idctValues = MDCT->IDCT(BValues->dctEditValues);

}

void LCGButton::onMouseUp(const scv::MouseEvent& evt)
{
   double a = (double)_LCGA->getValue();
   double c = (double)_LCGC->getValue();
   int m = (int)_LCGM->getValue();
   MValues->initialValues[0] = (int)c % m;
   double val;
   for(int i = 1 ; i < (int)MValues->nValores ; i++)
   {
      val = (double)((a*MValues->initialValues[i-1]) + (double)((int)c % m));
      if(val > 255){
         MValues->initialValues[i] = 255;
      } else if (val <= 0) {
         MValues->initialValues[i] = 0;
      }else{
         MValues->initialValues[i] = val;
      }
   }
   MValues->dctValues = MDCT->DCT(MValues->initialValues);
   MValues->dctEditValues = MValues->dctValues;
   MValues->idctValues = MDCT->IDCT(MValues->dctEditValues);
}

void ButtonSetKeyboard::onMouseUp(const scv::MouseEvent& evt)
{
   if(Pos->getValue() <= MyValues->nValores)
   {
      MyDCTS MDCT;
      MyValues->initialValues[(int)Pos->getValue()-1] = (double)Val->getValue();
      MyValues->dctValues = MDCT.DCT(MyValues->initialValues);
      MyValues->dctEditValues = MyValues->dctValues;
      MyValues->idctValues = MDCT.IDCT(MyValues->dctEditValues);
   }
}

void ButtonTruncadeParts::onMouseUp(const scv::MouseEvent& evt)
{
   if(_posFin->getValue() >= _posIni->getValue())
   {
      MyDCTS _md;
      for(int i = (int)_posIni->getValue()-1 ; i <_posFin->getValue() ; i++)
      {
         _MyValues->dctEditValues[i] = 0;
      }
      _MyValues->idctValues = _md.IDCT(_MyValues->dctEditValues);
   }

}