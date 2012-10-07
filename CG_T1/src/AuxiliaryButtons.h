/*Arquivo contendo os componentes que auxiliam o usuário a:
redimensionar gráfico
restringir os valores
aumentar escala e diminuir escala (DCTedit)
Marcar checkbox pra aparecer o gráfico original junto com a idct*/
#ifndef __AUXILIARY_BUTTONS___H____
#define __AUXILIARY_BUTTONS___H____
 
#include <SCV/Button.h>
#include "Canvas\CanvasEditDCT.h"
#include <SCV/CheckBox.h>
#include "Values.h"
#include <cstdlib>
#include <fstream> 
#include <sstream>
#include <SCV/Spinner.h>
#include "MyDCTS.h"

/*Botão que imprimi os valores num output.txt*/
class printOutputButton : public scv::Button {
public:

   printOutputButton(Values *mv) : scv::Button(scv::Point(1, 350),scv::Point(163, 350+24), "Gerar output.txt") {
      _mv = mv;
   }
   ~printOutputButton() {}

   void onMouseUp(const scv::MouseEvent& evt)
   {
      int x = 0;
      FILE*arq;
      arq = fopen("Resources/output.txt", "w");
      fprintf(arq,"Valores iniciais:\n");
      fprintf(arq,"[");
      while(x < _mv->nValores){
         std::stringstream sse;
         sse << _mv->initialValues[x];
         fprintf(arq,sse.str().c_str());
         x++;
         if(x == _mv->nValores){
            fprintf(arq,"]\n");
            break;
         }
         fprintf(arq,",");

      }
      x=0;

      fprintf(arq,"Valores DCT:\n");
      fprintf(arq,"[");
      while(x < _mv->nValores){
         std::stringstream sse;
         sse << _mv->dctValues[x];
         fprintf(arq,sse.str().c_str());
         x++;
         if(x == _mv->nValores){
            fprintf(arq,"]\n");
            break;
         }
         fprintf(arq,",");
      }
      x=0;

      fprintf(arq,"Valores DCT Editados:\n");
      fprintf(arq,"[");
      while(x < _mv->nValores){
         std::stringstream sse;
         sse << _mv->dctEditValues[x];
         fprintf(arq,sse.str().c_str());
         x++;
         if(x == _mv->nValores){
            fprintf(arq,"]\n");
            break;
         }
         fprintf(arq,",");
      }
      x=0;

      fprintf(arq,"Valores IDCT:\n");
      fprintf(arq,"[");
      while(x < _mv->nValores){
         std::stringstream sse;
         sse << _mv->idctValues[x];
         fprintf(arq,sse.str().c_str());
         x++;
         if(x == _mv->nValores){
            fprintf(arq,"]\n");
            break;
         }
         fprintf(arq,",");
      }
      fclose(arq);
   }

protected:
private:
   Values *_mv;

};

/*Botão de resize do grafico DCT edit*/
class resizeGraphButton : public scv::Button {
public:

   resizeGraphButton(CanvasEditDCT *Mt) : scv::Button(scv::Point(1, 660),scv::Point(165, 660+24), "Redimensionar Grafico") {
      c = Mt;
   }
   ~resizeGraphButton() {}

   void onMouseUp(const scv::MouseEvent& evt)
   {
      c->recalculateScale();
   }

protected:
private:
   CanvasEditDCT *c;

};

/*Botão para aumentar a escala do grafico DCT edit*/
class ScaleUpDCTButton : public scv::Button {
public:

   ScaleUpDCTButton(CanvasEditDCT *Mt) : scv::Button(scv::Point(1, 690),scv::Point(165, 690+24), "Aumetar Escala") {
      c = Mt;
   }
   ~ScaleUpDCTButton() {}

   void onMouseUp(const scv::MouseEvent& evt)
   {
      c->setScale(10.00);
   }

protected:
private:
   CanvasEditDCT *c;

};

/*Botão para diminuir a escala do grafico DCT edit*/
class ScaleDownDCTButton : public scv::Button {
public:

   ScaleDownDCTButton(CanvasEditDCT *Mt) : scv::Button(scv::Point(1, 720),scv::Point(165, 720+24), "Diminuir Escala") {
      c = Mt;
   }
   ~ScaleDownDCTButton() {}

   void onMouseUp(const scv::MouseEvent& evt)
   {
      c->setScale(-10.00);
   }

protected:
private:
   CanvasEditDCT *c;

};

/*Botão para resetar os valores do grafico DCT edit*/
class resetDCTEditButton : public scv::Button {
public:

   resetDCTEditButton(Values *MtValues) : scv::Button(scv::Point(1, 750),scv::Point(165, 750+24), "Resetar Grafico") {
      MValues = MtValues;
   }
   ~resetDCTEditButton() {}

   void onMouseUp(const scv::MouseEvent& evt)
   {
      MyDCTS _md;
      MValues->dctEditValues = MValues->dctValues;
      MValues->idctValues = _md.IDCT(MValues->dctEditValues);
   }

protected:
private:
   Values *MValues;

};

/*Checkbox para desenhar o gráfico inicial junto com o grafico da idct*/
class CheckboxOG : public scv::CheckBox
{
public:
   CheckboxOG(bool *st) : scv::CheckBox(scv::Point(1,620), false, "Mostrar Grafico Original")
   {
      state = st;
   }
   ~CheckboxOG() {}

   void onValueChange()
   {
      *state = getState();
   }
private:
   bool *state;

};

/*Botão que seta a restrição dos valores que serão desenhados no grafico*/
class RestButton : public scv::Button
{
public:
   RestButton(scv::Spinner *sp1, scv::Spinner *sp2, Values *MValues) : scv::Button(scv::Point(1, 485),scv::Point(160, 485+24), "Restringir Valores")
   {
      _sp1 = sp1;
      _sp2 = sp2;
      _MyValues = MValues;
   }
   ~RestButton() {}

   void onMouseUp(const scv::MouseEvent& evt)
   {
      _MyValues->changeLimits((int)_sp1->getValue() , (int)_sp2->getValue());
   }
private:
   scv::Spinner *_sp1;
   scv::Spinner *_sp2;
   Values *_MyValues;

};

#endif