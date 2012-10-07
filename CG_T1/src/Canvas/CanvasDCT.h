//Classe do gráfico direito e de cima.
// mostra os valores dct do vetor.
#ifndef __CANVAS_DCT_H__
#define __CANVAS_DCT_H__

#include <SCV/Canvas.h>
#include <SCV/Label.h>
#include <SCV/Color4f.h>
#include "../MyDCTS.h"
#include "../Values.h"

class CanvasVetDCT : public scv::Canvas {
   public:

      CanvasVetDCT(Values* MV, scv::Label *Edct, scv::Label *Tscale);
      ~CanvasVetDCT() {}

      void onMouseOver(const scv::MouseEvent& evt);

      void update(void);

      void render(void);
   protected:
   private:
      scv::Color4f bg_color;   
      double eixoy;
      Values *MyValues;
      MyDCTS *MDCT;
      double eixox;
      double PI;
      int position_vector;
      scv::Label *scale;
      scv::Label *PointsVDCT;
      double maximum_value;
      int nVal;

};

#endif