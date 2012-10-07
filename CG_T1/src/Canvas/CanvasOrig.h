//Classe do gráfico esquerdo e de cima.
// mostra os valores iniciais do vetor.
//Editavel.
#ifndef ___CANVAS___ORIG____H___
#define ___CANVAS___ORIG____H___

#include <SCV/Canvas.h>
#include <SCV/Label.h>
#include <SCV/Color4f.h>
#include "../MyDCTS.h"
#include "../Values.h"

class CanvasVOrig : public scv::Canvas {
public:
      
   CanvasVOrig( Values* MyValuest, scv::Label *VOrig, scv::Label *VScale );
   ~CanvasVOrig() {}

   void onMouseClick(const scv::MouseEvent& evt);

   void onMouseHold (const scv::MouseEvent& evt);

   void onMouseOver(const scv::MouseEvent& evt);

   void onMouseUp(const scv::MouseEvent& evt);

   void update(void);

   void render(void);

protected:

private:
   scv::Color4f bg_color;   
   double posx;
   double posy;
   Values* MyValues;
   double eixoy;
   double eixox;
   MyDCTS *MDCT;
   double PI;
   scv::Label *PointsVOrig;
   scv::Label *scale;
   int position_vector;
   int nVal;
};

#endif