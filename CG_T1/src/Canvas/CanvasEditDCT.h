//Classe do gráfico esquerdo e de baixo.
// mostra os valores dct do vetor.
//Editavel.
#ifndef __CANVAS_EDIT_DCT__H_
#define __CANVAS_EDIT_DCT__H_

#include <SCV/Canvas.h>
#include <SCV/Label.h>
#include <SCV/Color4f.h>
#include "../MyDCTS.h"
#include "../Values.h"


class CanvasEditDCT : public scv::Canvas {
public:

   CanvasEditDCT(Values* MyValuest, scv::Label *VEdct, scv::Label *Tscale);
   ~CanvasEditDCT() {}

   void onMouseClick(const scv::MouseEvent& evt);

   void onMouseHold (const scv::MouseEvent& evt);

   void onMouseOver(const scv::MouseEvent& evt);

   void onMouseWheel(const scv::MouseEvent& evt);

   void onMouseUp(const scv::MouseEvent& evt);

   void setScale(double x);

   void recalculateScale();

   void update(void);

   void render(void);

protected:
private:
   scv::Color4f bg_color;
   Values* MyValues;
   double eixoy;
   MyDCTS *MDCT;
   double PI;
   double eixox;
   int position_vector;
   scv::Label *PointsVEDCT;
   scv::Label *scale;
   double max;
   int nVal;
};
#endif