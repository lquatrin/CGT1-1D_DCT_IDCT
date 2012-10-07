#include "CanvasOrig.h"
#include <cstdlib>
#include <cmath>
#include <sstream>

CanvasVOrig::CanvasVOrig( Values* MyValuest, scv::Label *VOrig, scv::Label *VScale ) 
   : scv::Canvas(scv::Point(2, 15),scv::Point(502, 350+15)), bg_color(1.f,1.f,1.f) {
   position_vector = 0;
   PointsVOrig = VOrig;
   MyValues = MyValuest;
   eixoy = 30;
   PI = 3.1415926535897932384626433832795028841971693993751058209749;
   eixox = 280.0;
   scale = VScale;
   scale->setString("Escala: 1");
   nVal = 8;
}

void CanvasVOrig::onMouseClick(const scv::MouseEvent& evt)
{
   if((((double)evt.getPosition().x - ((double)eixoy + (((450)/((double)nVal))/2.0))) )/((450)/((double)nVal)) >= 0 
      &&(((double)evt.getPosition().x - ((double)eixoy + (((450)/((double)nVal))/2.0))) )/((450)/((double)nVal)) < (double)nVal) {
      position_vector =(int)((((double)evt.getPosition().x - ((double)eixoy+ (((450)/((double)nVal))/2.0))) )/((450)/((double)nVal)));
      position_vector += (int)MyValues->valIni-1;
      if(((double)evt.getPosition().y - 280.0)*-1.0 < 0) {
         MyValues->initialValues[position_vector] = 0;
      }else if(((double)evt.getPosition().y - 280.0)*-1.0 > 255){
         if(evt.getButton() == GLUT_RIGHT_BUTTON){
            MyValues->initialValues[position_vector] = 0;
         }else if(evt.getButton() == GLUT_LEFT_BUTTON){
            MyValues->initialValues[position_vector] = 255;
         }                      
      } else {
         if(evt.getButton() == GLUT_RIGHT_BUTTON){
            MyValues->initialValues[position_vector] = 0;
         } else if(evt.getButton() == GLUT_LEFT_BUTTON){
            MyValues->initialValues[position_vector] = (((double)evt.getPosition().y - eixox)*-1.0);
         }       
      }
      //MyValues->dctValues = MDCT->DCT(MyValues->initialValues);
      //MyValues->dctEditValues = MyValues->dctValues;
   }
}

void CanvasVOrig::onMouseHold (const scv::MouseEvent& evt)
{     
   if((((double)evt.getPosition().x - ((double)eixoy + (((450)/((double)nVal))/2.0))) )/((450)/((double)nVal)) >= 0 
     &&(((double)evt.getPosition().x - ((double)eixoy + (((450)/((double)nVal))/2.0))) )/((450)/((double)nVal)) < (double)nVal) {
      position_vector =(int)((((double)evt.getPosition().x - ((double)eixoy+ (((450)/((double)nVal))/2.0))) )/((450)/((double)nVal)));
      position_vector += (int)MyValues->valIni-1;
      if(((double)evt.getPosition().y - 280.0)*-1.0 < 0) {
         MyValues->initialValues[position_vector] = 0;
      }else if(((double)evt.getPosition().y - 280.0)*-1.0 > 255){
         if(evt.getButton() == GLUT_RIGHT_BUTTON){
            MyValues->initialValues[position_vector] = 0;
         }else if(evt.getButton() == GLUT_LEFT_BUTTON){
            MyValues->initialValues[position_vector] = 255;
         }                      
      } else {
         if(evt.getButton() == GLUT_RIGHT_BUTTON){
            MyValues->initialValues[position_vector] = 0;
         }else if(evt.getButton() == GLUT_LEFT_BUTTON){
            MyValues->initialValues[position_vector] = (((double)evt.getPosition().y - eixox)*-1.0);
         }       
      }
      //MyValues->dctValues = MDCT->DCT(MyValues->initialValues);
      //MyValues->dctEditValues = MyValues->dctValues;
   }
}

void CanvasVOrig::onMouseOver(const scv::MouseEvent& evt)
{
   if((((double)evt.getPosition().x - ((double)eixoy + (((450)/((double)nVal))/2.0))) )/((450)/((double)nVal)) >= 0 
     &&(((double)evt.getPosition().x - ((double)eixoy + (((450)/((double)nVal))/2.0))) )/((450)/((double)nVal)) < (double)nVal) {
      position_vector =(int)((((double)evt.getPosition().x - ((double)eixoy+ (((450)/((double)nVal))/2.0))) )/((450)/((double)nVal)));
      position_vector += (int)MyValues->valIni-1;
   }
}

void CanvasVOrig::onMouseUp(const scv::MouseEvent& evt)
{
   MyValues->dctValues = MDCT->DCT(MyValues->initialValues);
   MyValues->dctEditValues = MyValues->dctValues;
   MyValues->idctValues = MDCT->IDCT(MyValues->dctEditValues);
}

void CanvasVOrig::update(void) {
   nVal = (int)(MyValues->valFin - MyValues->valIni);
   nVal++;
   if(position_vector >= MyValues->nValores)
   {
      //position_vector = MyValues->nValores-1;
      position_vector = 0;
   }
   std::ostringstream out;
   out <<  MyValues->initialValues[position_vector];
   std::string value = out.str();
   std::stringstream ss;
   ss << (position_vector+1);
   PointsVOrig->setString("Ponto[" + ss.str() + "] = "+value);
}

void CanvasVOrig::render(void) {  
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
         glVertex2i((int)x1,(int)(((MyValues->initialValues[i] )-eixox)*-1.0));
         x1+=(450.0)/((double)nVal); 
      }
   glEnd();
   double x = (double)eixoy+((450.0)/((double)nVal));
   for(int i = (int)(MyValues->valIni-1); i < (int)MyValues->valFin ; i++)
   {
      glBegin(GL_TRIANGLE_FAN);
         glColor3f(.0f, 0.f, .0f);
         glVertex2i((int)x,(int)(((MyValues->initialValues[i])-eixox)*-1.0));
         for(double j = 0 ; j <= (2* (PI+0.1)) ; j +=0.4)
         {
            glVertex2i((int)(x + (3* cos(j) )),(int)(       ((MyValues->initialValues[i])-eixox)*-1.0 + (3* sin(j))   )       );      
         }
         x+=450.0/((double)nVal);            
      glEnd();
   }    
}