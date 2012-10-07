#ifndef __LABELS___CG___H____
#define __LABELS___CG___H____

#include <SCV/Label.h>

class LabelVetIn : public scv::Label {
   public:

      LabelVetIn() : scv::Label(scv::Point(150, 0), "Grafico Editavel do Vetor Inicial") {

      }
      ~LabelVetIn() {}

   protected:
   private:

};

class LabelVetDCT : public scv::Label {
   public:

      LabelVetDCT() : scv::Label(scv::Point(650, 0), "Grafico do Vetor DCT") {

      }
      ~LabelVetDCT() {}

   protected:
   private:

};

class LabelVetIDCT : public scv::Label {
   public:

      LabelVetIDCT() : scv::Label(scv::Point(650, 365), "Grafico do Vetor IDCT") {

      }
      ~LabelVetIDCT() {}

   protected:
   private:

};


class LabelVetEditDCT : public scv::Label {
   public:

      LabelVetEditDCT() : scv::Label(scv::Point(150, 365), "Grafico Editavel do Vetor DCT") {

      }
      ~LabelVetEditDCT() {}

   protected:
   private:

};

#endif