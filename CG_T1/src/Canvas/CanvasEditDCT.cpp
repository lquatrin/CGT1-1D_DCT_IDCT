#include "CanvasEditDCT.h"
#include <cstdlib>
#include <cmath>
#include <sstream>

CanvasEditDCT::CanvasEditDCT(Values* MyValuest, scv::Label *VEdct, scv::Label *Tscale) 
   : scv::Canvas(scv::Point(2, 350+30),scv::Point(502, 700+30)), bg_color(1.0f, 1.0f, 1.0f) {
   PointsVEDCT = VEdct;
   position_vector = 0;
   MyValues = MyValuest;
   eixoy = 30.0;
   eixox = 180.0;
   PI = 3.1415926535897932384626433832795028841971693993751058209749;
   max = 160;
   scale = Tscale;
}

void CanvasEditDCT::onMouseClick(const scv::MouseEvent& evt)
{
   if((((double)evt.getPosition().x - ((double)eixoy + (((450)/((double)nVal))/2.0))) )/((450)/((double)nVal)) >= 0 
     &&(((double)evt.getPosition().x - ((double)eixoy + (((450)/((double)nVal))/2.0))) )/((450)/((double)nVal)) < (double)nVal) {
      position_vector =(int)((((double)evt.getPosition().x - ((double)eixoy+ (((450)/((double)nVal))/2.0))) )/((450)/((double)nVal)));
      position_vector += (int)MyValues->valIni-1;
      if(evt.getButton() == GLUT_RIGHT_BUTTON){
            MyValues->dctEditValues[position_vector] = 0;
         }else if(evt.getButton() == GLUT_LEFT_BUTTON){
            MyValues->dctEditValues[position_vector] = (((double)evt.getPosition().y - eixox)*-1.0)*(max/160.0);
         }   
   }
}
void CanvasEditDCT::onMouseHold (const scv::MouseEvent& evt)
{     
   if((((double)evt.getPosition().x - ((double)eixoy + (((450)/((double)nVal))/2.0))) )/((450)/((double)nVal)) >= 0 
     &&(((double)evt.getPosition().x - ((double)eixoy + (((450)/((double)nVal))/2.0))) )/((450)/((double)nVal)) < (double)nVal) {
      position_vector =(int)((((double)evt.getPosition().x - ((double)eixoy+ (((450)/((double)nVal))/2.0))) )/((450)/((double)nVal)));
      position_vector += (int)MyValues->valIni-1;
      if(evt.getButton() == GLUT_RIGHT_BUTTON){
            MyValues->dctEditValues[position_vector] = 0;
         }else if(evt.getButton() == GLUT_LEFT_BUTTON){
            MyValues->dctEditValues[position_vector] = (((double)evt.getPosition().y - eixox)*-1.0)*(max/160.0);
         }                
   }
}

void CanvasEditDCT::onMouseOver(const scv::MouseEvent& evt)
{
   if((((double)evt.getPosition().x - ((double)eixoy + (((450)/((double)nVal))/2.0))) )/((450)/((double)nVal)) >= 0 
     &&(((double)evt.getPosition().x - ((double)eixoy + (((450)/((double)nVal))/2.0))) )/((450)/((double)nVal)) < (double)nVal) {
      position_vector =(int)((((double)evt.getPosition().x - ((double)eixoy+ (((450)/((double)nVal))/2.0))) )/((450)/((double)nVal)));
      position_vector += (int)MyValues->valIni-1;
   }
}

void CanvasEditDCT::onMouseWheel(const scv::MouseEvent& evt)
{
   if(evt.getState() == 4){
      max+=5;
   } else if(evt.getState() == 5){
      if(max > 160){
         max -= 5;
      }
      if(max < 160)
      {
         max = 160;
      }
   }
}

void CanvasEditDCT::setScale(double x)
{
   max += 5.00*x;
   if(max < 160)
   {
      max = 160;
   }
}

void CanvasEditDCT::recalculateScale()
{
   max = 1.0;
   double ax;
   for(int i = (int)(MyValues->valIni-1); i < (int)MyValues->valFin  ; i++)
   {
      ax = MyValues->dctEditValues[i];
      if(ax < 0)
      {
         ax *= -1.0;
      }
      if(max < ax)
      {
         max = ax;
      }
   }
   if(max < 160)
   {
      max = 160;
   }
}

void CanvasEditDCT::onMouseUp(const scv::MouseEvent& evt)
{
   MyValues->idctValues = MDCT->IDCT(MyValues->dctEditValues);
}

void CanvasEditDCT::update(void) {
   nVal = (int)(MyValues->valFin - MyValues->valIni);
   nVal++;
   if(position_vector >= MyValues->nValores)
   {
      //a = MyValues->nValores-1;
      position_vector = 0;
   }
   std::ostringstream out;
   out <<  MyValues->dctEditValues[position_vector];
   std::string value = out.str();
   std::stringstream ss;
   ss << (position_vector+1);
   PointsVEDCT->setString("Ponto[" + ss.str() + "] = "+value);

   std::stringstream sse;
   sse << (max/160);
   scale->setString("Escala: " + sse.str());
}

void CanvasEditDCT::render(void) {
   GLint ieixox = (GLint)eixox;
   GLint ieixoy = (GLint)eixoy;
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
      glVertex2i((int)x1,(int)(((MyValues->dctEditValues[i]*(160.0/max)  )-eixox)*-1.0));
      x1+=(450.0)/((double)nVal); 
   }
   glEnd();
   double x = (double)eixoy+((450.0)/((double)nVal));
   for(int i = (int)(MyValues->valIni-1); i < (int)MyValues->valFin ; i++)
   {
      glBegin(GL_TRIANGLE_FAN);
      glColor3f(.0f, 0.f, .0f);
      glVertex2i((int)x,(int)(((MyValues->dctEditValues[i]*(160.0/max))-eixox)*-1.0));
      for(double j = 0 ; j <= (2* (PI+0.1)) ; j +=0.4)
      {
         glVertex2i((int)(x + (3* cos(j) )),(int)(       ((MyValues->dctEditValues[i]*(160.0/max))-eixox)*-1.0 + (3* sin(j))   )       );

      }
      x+=450.0/((double)nVal);

      glEnd();
   }    
}