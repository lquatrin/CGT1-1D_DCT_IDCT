//Arquivo que tem os painéis usados no trabalho:
//Painel da esquerda, os dois da direita (cima e embaixo)
//e os dois com o botão de abrir o wav e os componentes do wav

#ifndef ___PANELS___H___
#define ___PANELS___H___

#include <SCV/Panel.h>

class RightUpPanel : public scv::Panel {
   public:

      RightUpPanel() : scv::Panel(scv::Point(167, 0), scv::Point(1173, 48)) {}
      ~RightUpPanel() {}

   protected:
   private:

};

class RightDownPanel : public scv::Panel {
   public:

      RightDownPanel() : scv::Panel(scv::Point(167, 49), scv::Point(1173, 785)) {}
      ~RightDownPanel() {}

   protected:
   private:

};

class LeftPanel : public scv::Panel {
   public:

      LeftPanel() : scv::Panel(scv::Point(1, -1), scv::Point(166, 785)) {}
      ~LeftPanel() {}

   protected:
   private:

};

class WAVPanel : public scv::Panel {
   public:

      WAVPanel() : scv::Panel(scv::Point(160,0),scv::Point(1010,48)) {}
      ~WAVPanel() {}

   protected:
   private:

};

class AWAVPanel : public scv::Panel {
   public:

      AWAVPanel() : scv::Panel(scv::Point(160,0),scv::Point(260,48)) {}
      ~AWAVPanel() {}

   protected:
   private:

};

#endif