#include "CanvasIDCT.h"
#include <cstdlib>
#include <cmath>
#include <sstream>

CanvasIDCT::CanvasIDCT(Values* MyValuest, scv::Label *IVEdct, scv::Label *Tscale) 
   : scv::Canvas(scv::Point(504, 350+30),scv::Point(1004, 700+30)), bg_color(1.0f, 1.0f, 1.0f) {
   PointsIVDCT = IVEdct;
   MyValues = MyValuest;
   position_vector = 0;
   eixoy = 30.0;
   eixox = 180.0;
   PI = 3.1415926535897932384626433832795028841971693993751058209749;
   maximum_value = 1.0;
   scale = Tscale;
   state = false;
}

void CanvasIDCT::onMouseOver(const scv::MouseEvent& evt)
{
   if((((double)evt.getPosition().x - ((double)eixoy + (((450)/((double)nVal))/2.0))) )/((450)/((double)nVal)) >= 0 
     &&(((double)evt.getPosition().x - ((double)eixoy + (((450)/((double)nVal))/2.0))) )/((450)/((double)nVal)) < (double)nVal) {
      position_vector =(int)((((double)evt.getPosition().x - ((double)eixoy+ (((450)/((double)nVal))/2.0))) )/((450)/((double)nVal)));
      position_vector += (int)MyValues->valIni-1;
   }
}

void CanvasIDCT::update(void) {
   nVal = (int)(MyValues->valFin - MyValues->valIni);
   nVal++;
   maximum_value = 1.0;
   double ax;
   for(int i = (int)(MyValues->valIni-1); i < (int)MyValues->valFin  ; i++)
   {
      ax = MyValues->idctValues[i];
      if(ax < 0)
      {
         ax *= -1.0;
      }
      if(maximum_value < ax)
      {
         maximum_value = ax;
      }
      if(state)
      {
         ax = MyValues->initialValues[i];
         if(ax < 0)
         {
            ax *= -1.0;
         }
         if(maximum_value < ax)
         {
            maximum_value = ax;
         }
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
   out <<  MyValues->idctValues[position_vector];
   std::string value = out.str();
   std::stringstream ss;
   ss << (position_vector+1);
   PointsIVDCT->setString("Ponto[" + ss.str() + "] = "+value);
   std::stringstream sse;
   sse << (maximum_value/160);
   scale->setString("Escala: " + sse.str());
}

void CanvasIDCT::render(void) {
   GLint ieixoy = (GLint)eixoy;
   GLint ieixox = (GLint)eixox;
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

   if(state) // desenha o grafico original junto
   {
      glBegin(GL_LINE_STRIP);
      glColor3f(.0f, .0f, 1.0);
      double x1 = eixoy+((450.0)/(double)(nVal));
      for(int i = (int)(MyValues->valIni-1); i < (int)MyValues->valFin ; i++)
      {   
         glVertex2i((int)x1,(int)(((MyValues->initialValues[i]*(160.0/maximum_value)  )-eixox)*-1.0));
         x1+=(450.0)/((double)nVal);
      }
      glEnd();
      double x = eixoy+((450.0)/((double)nVal));
      for(int i = (int)(MyValues->valIni-1); i < (int)MyValues->valFin ; i++)
      {
         glBegin(GL_TRIANGLE_FAN);
         glColor3f(.0f, .0f, 1.0);
         glVertex2i((int)x,(int)(((MyValues->initialValues[i]*(160.0/maximum_value))-eixox)*-1.0));
         for(double j = 0 ; j <= (2* (PI+0.1)) ; j +=0.01)
         {
            glVertex2i((int)(x + (3* cos(j) )),(int)(       ((MyValues->initialValues[i]*(160.0/maximum_value))-eixox)*-1.0 + (3* sin(j))   )       );     
         }
         x+=450.0/((double)nVal);

         glEnd();
      }
   }

   glBegin(GL_LINE_STRIP); // desenhar as linhas
   glColor3f(.0f, 0.f, .0f);
   double x1 = eixoy+((450.0)/(double)(nVal));
   for(int i = (int)(MyValues->valIni-1); i < (int)MyValues->valFin ; i++)
   {   
      glVertex2i((int)x1,(int)(((MyValues->idctValues[i]*(160.0/maximum_value)  )-eixox)*-1.0));
      x1+=(450.0)/((double)nVal);
   }
   glEnd();
   double x = eixoy+((450.0)/((double)nVal));
   for(int i = (int)(MyValues->valIni-1); i < (int)MyValues->valFin ; i++)
   {
      glBegin(GL_TRIANGLE_FAN); // marcar os pontos
      glColor3f(.0f, 0.f, .0f);
      glVertex2i((int)x,(int)(((MyValues->idctValues[i]*(160.0/maximum_value))-eixox)*-1.0));
      for(double j = 0 ; j <= (2* (PI+0.1)) ; j +=0.4)
      {
         glVertex2i((int)(x + (3* cos(j) )),(int)(       ((MyValues->idctValues[i]*(160.0/maximum_value))-eixox)*-1.0 + (3* sin(j))   )       );     
      }
      x+=450.0/((double)nVal);

      glEnd();
   } 

}