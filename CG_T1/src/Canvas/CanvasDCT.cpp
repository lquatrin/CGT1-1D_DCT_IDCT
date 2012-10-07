#include "CanvasDCT.h"
#include <cstdlib>
#include <cmath>
#include <sstream>

CanvasVetDCT::CanvasVetDCT(Values* MV, scv::Label *Edct, scv::Label *Tscale) 
   : scv::Canvas(scv::Point(504, 15),scv::Point(1004, 350+15)), bg_color(1.f,1.f,1.f) {
   PointsVDCT = Edct;
   position_vector = 0;
   eixoy = 30.0;
   eixox = 180.0;
   MyValues = MV;
   PI = 3.1415926535897932384626433832795028841971693993751058209749;
   maximum_value = 1.0;
   scale = Tscale;
}

      
void CanvasVetDCT::onMouseOver(const scv::MouseEvent& evt)
{
   if((((double)evt.getPosition().x - ((double)eixoy + (((450)/((double)nVal))/2.0))) )/((450)/((double)nVal)) >= 0 
     &&(((double)evt.getPosition().x - ((double)eixoy + (((450)/((double)nVal))/2.0))) )/((450)/((double)nVal)) < (double)nVal) {
      position_vector =(int)((((double)evt.getPosition().x - ((double)eixoy+ (((450)/((double)nVal))/2.0))) )/((450)/((double)nVal)));
      position_vector += (int)MyValues->valIni-1;
   }
}

void CanvasVetDCT::update(void) {
   nVal = (int)(MyValues->valFin - MyValues->valIni);
   nVal++;
   maximum_value = 1.0;
   double ax;
   for(int i = (int)(MyValues->valIni-1); i < (int)MyValues->valFin  ; i++)
   {
      ax = MyValues->dctValues[i];
      if(ax < 0)
      {
         ax *= -1.0;
      }
      if(maximum_value < ax)
      {
         maximum_value = ax;
      }
   }
   if(maximum_value < 160)
   {
      maximum_value = 160;
   }

   if(position_vector >= MyValues->nValores)
   {
      //position_vector = MyValues->nValores-1;
      position_vector = 0;
   }
   std::ostringstream out;
   out <<  MyValues->dctValues[position_vector];
   std::string value = out.str();
   std::stringstream ss;
   ss << (position_vector+1);
   PointsVDCT->setString("Ponto[" + ss.str() + "] = "+value);

   std::stringstream sse;
   sse << (maximum_value/160);
   scale->setString("Escala: " + sse.str());
}


void CanvasVetDCT::render(void) {
   int ieixox = (int)eixox;
   int ieixoy = (int)eixoy;
   // Desenhar o gráfico da função
   // Eixo y
   glBegin(GL_LINES);
      glColor3f(.0f, 0.f, .0f);
      glVertex2i(ieixoy, 5);
      glVertex2i(ieixoy, 345);
   glEnd();
   // Eixo x
   glBegin(GL_LINES);
      glColor3f(.0f, 0.f, .0f);
      glVertex2i(20, ieixox);
      glVertex2i(480, ieixox);
   glEnd();

   //tem erro nesses quando o numero n é potencia de 2 por causa dos erros de precisão
   glBegin(GL_LINE_STRIP);
      glColor3f(.0f, 0.f, .0f);
      double x1 = (double)eixoy+((450.0)/(double)(nVal));
      for(int i = (int)(MyValues->valIni-1); i < (int)MyValues->valFin ; i++)
      {   
         glVertex2i((int)x1,(int)(((MyValues->dctValues[i]*(160.0/maximum_value)  )-eixox)*-1.0));
         x1+=(450.0)/((double)nVal); 
      }
   glEnd();
   double x = (double)eixoy+((450.0)/((double)nVal));
   for(int i = (int)(MyValues->valIni-1); i < (int)MyValues->valFin ; i++)
   {
      glBegin(GL_TRIANGLE_FAN);
         glColor3f(.0f, 0.f, .0f);
         glVertex2i((int)x,(int)(((MyValues->dctValues[i]*(160.0/maximum_value))-eixox)*-1.0));
         for(double j = 0 ; j <= (2* (PI+0.1)) ; j +=0.4)
         {
            glVertex2i((int)(x + (3* cos(j) )),(int)(       ((MyValues->dctValues[i]*(160.0/maximum_value))-eixox)*-1.0 + (3* sin(j))   )       );   
         }
         x+=450.0/((double)nVal); 
      glEnd();
   }    
}