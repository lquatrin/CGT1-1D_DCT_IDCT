//Classe do gráfico direito e de baixo.
// mostra os valores depois da idct do vetor.
#ifndef __CANVAS_IDCT___H___
#define __CANVAS_IDCT___H___

#include <SCV/Canvas.h>
#include <SCV/Label.h>
#include <SCV/Color4f.h>
#include "../MyDCTS.h"
#include "../Values.h"

class CanvasIDCT : public scv::Canvas {
public:

   CanvasIDCT(Values* MyValuest, scv::Label *IVEdct, scv::Label *Tscale);
   ~CanvasIDCT() {}

   void onMouseOver(const scv::MouseEvent& evt);

   void update(void);

   void render(void);

   bool state;

protected:
private:
   scv::Color4f bg_color;
   Values* MyValues;
   double eixoy;
   double eixox;
   MyDCTS *MDCT;
   double PI;
   int position_vector;
   scv::Label *scale;
   scv::Label *PointsIVDCT;
   double maximum_value;
   int nVal;

};
#endif