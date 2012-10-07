#include <SCV/Kernel.h>
#include <SCV/ColorScheme.h>
#include <SCV/ButtonGroup.h>
#include "MyDCTS.h"
#include "Values.h"
#include "LabelsRDCanvas.h"
#include "CanvasDCT.h"
#include "CanvasIDCT.h"
#include "CanvasEditDCT.h"
#include "CanvasOrig.h"
#include "Panels.h"
#include "WAVReader.h"
#include "ButtonGenerateValues.h"
#include "WAVPanelComponents.h"
#include "AuxiliaryButtons.h"
#include "SettersButtons.h"

void SCV_main(){

   using namespace scv;

   // Kernel Instance
   static Kernel *kernel = Kernel::getInstance();

   // Load ColorScheme
   static ColorScheme *scheme = ColorScheme::getInstance();
   scheme->loadScheme(ColorScheme::warcraft);

   // Set Windows Size
   kernel->setWindowSize(1173, 786);
   kernel->setWindowTitle("Application DCT IDCT");

   // Set Frame Rate
   kernel->setFramesPerSecond(40.f);

   std::cout << "O programa contem 4 graficos, cada um deles representando:\n"
      << "1-grafico das amostras originais(Editavel) 2-grafico DCT\n"
      << "3-grafico dct(Editavel)          4-grafico IDCT\n"
      << "As atualizações dos canvas são feitos quando e' soltado o botao do mouse (MouseUp)\n"
      << "No painel da esquerda e possivel:\n"
      << "-Setar valores (os primeiros botoes)\n"
      << "-Restringir valores(mostrar apenas parte do vetor)\n"
      << "-Mostrar grafico original junto do grafico 4 (IDCT)\n"
      << "-Editar as escalas do grafico numero 3 (DCT editavel)\n"
      << "-Resetar os valores do grafico numero 3 (DCT editavel)\n"
      << "No painel da direita e acima e possivel:\n"
      << "-Setar tamanho do vetor (8 e 16 como base e depois de 1 ate 1024)\n"
      << "-Abrir arquivo wav (sera explicado abaixo sobre isso)\n"
      << "No painel da direita e abaixo e possivel:\n"
      << "-Editar o grafico 1 e 3 por interacao do mouse\n"
      << "Clique do mouse direito seta o valor para 0\n" 
      << "e o esquerdo calcula posicao do mouse\n"
      << "-Ao grafico 3 e possivel editar a escala com o scroll do mouse\n"
      << "Para cada canvas temos:\n" 
      << "-Acima e na esquerda o valor de cada ponto (mostrado de acordo com a\n posicao do mouse no grafico)\n"
      << "-Acima e na direita o valor da escala(nao interfere no valor que e' mostrado dos pontos)\n"
      << "Para o arquivo wav temos:\n"
      << "-Ao clicar, o wav comeca a ser carregado, pouco a pouco\n"
      << "-Quando carregar, abre o painel com os componentes\n"
      << "-Podemos separar o arquivo em blocos de 200,400,600,800,1000 e um so\n"
      << "-Voce pode escolher entre pegar os valores do canal direito ou esquerdo\n"
      << "-Podemos escolher qual bloco queremos pegar para passar para o vetor do canvas\n"
      << "-Quando escolhe um bloco aparece um botao para mandar os valores de voltar para o wav\n"
      << "-Se pegar um bloco de tamanho x e restaurar um de tamanho diferente de x, ele nao sera restaurado\n"
      << "-Voce pode escolher entre zerar alguns valores da esquerda ou da direita (10% no início ou no final)\n"
      << "(halfLeftTruncade e halfRightTruncade) [MUITO LENTO]\n"
      << "O arquivo wav lido SEMPRE sera o in.wav da pasta Resources, e a out.wav tambem\n"
      << "Por ter restrição de valores, se e' setado um vetor com mais de 200 valores, o programa seta como padrao mostrar de 1 a 200, caso queira aumentar o numero de valores e' so modificar no componente\n"
      << std::endl;

   scv::Spinner *spinDe = new Spinner(scv::Point(20, 251), 100, 1, 8,1,1);
   scv::Spinner *spinAte = new Spinner(scv::Point(20, 273), 100, 1, 8,1,1);
   scv::Label *tamLabel = new scv::Label(scv::Point(0,420), scv::Point(10,670), "TamVetor: 8");
   scv::Label *iL = new scv::Label(scv::Point(0,440), scv::Point(10,670), "posIni: 1");
   scv::Spinner *fS = new scv::Spinner(scv::Point(1, 560), 160, 1,8 , 8, 1);
   scv::Label *fL = new scv::Label(scv::Point(0,450), scv::Point(10,670), "posFin: 8");
   scv::Spinner *iS = new scv::Spinner(scv::Point(1, 525), 160, 1,8 , 1, 1);
   Values *MyValues = new Values(tamLabel,iL,fL,iS,fS,spinDe,spinAte);

   /************************************************/   
   /*Painéis*/
   scv::Panel * RUpanel;
   RUpanel = new RightUpPanel();
   kernel->addComponent(RUpanel);

   scv::Panel *RDpanel;
   RDpanel = new RightDownPanel();
   kernel->addComponent(RDpanel);

   scv::Panel *Lpanel;
   Lpanel = new LeftPanel();
   kernel->addComponent(Lpanel);

   scv::Panel *Wpanel;
   Wpanel = new WAVPanel();
   RUpanel->addComponent(Wpanel);
   Wpanel->setVisible(false);

   scv::Panel *AWpanel;
   AWpanel = new AWAVPanel();
   RUpanel->addComponent(AWpanel);
   AWpanel->setVisible(true);
   /*-------------------------*/

   /*Wav Panels*/
   scv::Label *lreading = new scv::Label(scv::Point(420, 20), scv::Point(600, 40), "Arquivo WAV: Carregando");
   lreading->setVisible(false);

   WAVLeftChannelRadioButton *bLF = new WAVLeftChannelRadioButton();
   Wpanel->addComponent(bLF);
   WAVRightChannelRadioButton *bRF = new WAVRightChannelRadioButton();
   Wpanel->addComponent(bRF);
   scv::ButtonGroup * wavChannels = new scv::ButtonGroup();
   bLF->registerButtonGroup(wavChannels);
   bRF->registerButtonGroup(wavChannels);

   WavRadioButton200 *b200 = new WavRadioButton200();
   Wpanel->addComponent(b200);
   WavRadioButton400 *b400 = new WavRadioButton400();
   Wpanel->addComponent(b400);
   WavRadioButton600 *b600 = new WavRadioButton600();
   Wpanel->addComponent(b600);
   WavRadioButton800 *b800 = new WavRadioButton800();
   Wpanel->addComponent(b800);
   WavRadioButton1000 *b1000 = new WavRadioButton1000();
   Wpanel->addComponent(b1000);
   WavRadioButtonAll *ball = new WavRadioButtonAll();
   Wpanel->addComponent(ball);
   Wpanel->addComponent(new scv::Label(scv::Point(0, 27),scv::Point(502, 40), "Bloco numero:"));
   scv::Spinner *chunkSpinner = new scv::Spinner(scv::Point(70, 25), 70, 1, 255, 1, 1);
   Wpanel->addComponent(chunkSpinner);
   Wpanel->addComponent(new WavCloseButton(Wpanel, AWpanel));


   scv::ButtonGroup * wavGroup = new scv::ButtonGroup();

   b200->registerButtonGroup(wavGroup);
   b400->registerButtonGroup(wavGroup);
   b600->registerButtonGroup(wavGroup);
   b800->registerButtonGroup(wavGroup);
   b1000->registerButtonGroup(wavGroup);
   ball->registerButtonGroup(wavGroup);

   scv::Label *tam_vet_wav = new scv::Label(scv::Point(503, 5),scv::Point(650, 5), "Tam de cada vetor:");
   Wpanel->addComponent(tam_vet_wav);
   scv::Label *nchunks_wav = new scv::Label(scv::Point(503, 25),scv::Point(650, 25), "Num de blocos:");
   Wpanel->addComponent(nchunks_wav);

   WAVReader *wrd = new WAVReader(tam_vet_wav, nchunks_wav, Wpanel,b200,bLF,chunkSpinner,lreading, MyValues);
   b200->setPointerWav(&wrd->chunkSizeValue);
   b400->setPointerWav(&wrd->chunkSizeValue);
   b600->setPointerWav(&wrd->chunkSizeValue);
   b800->setPointerWav(&wrd->chunkSizeValue);
   b1000->setPointerWav(&wrd->chunkSizeValue);
   ball->setPointerWav(&wrd->chunkSizeValue);

   WAVHalfTruncadeButton *whtbl = new WAVHalfTruncadeButton(wrd, 0, "LeftHalfTruncade",2);
   WAVHalfTruncadeButton *whtbr = new WAVHalfTruncadeButton(wrd, 0, "RightHalTtruncade",25);
   Wpanel->addComponent(whtbl);
   Wpanel->addComponent(whtbr);

   ReturnChunkButton *rcbt = new ReturnChunkButton(wrd);
   Wpanel->addComponent(rcbt);
   rcbt->setVisible(false);
   
   SetChunkButton *scb = new SetChunkButton(wrd,rcbt,bLF,bRF,chunkSpinner);
   Wpanel->addComponent(scb);
   
   WAVGenerateOutputButton *wgob = new WAVGenerateOutputButton(wrd);
   Wpanel->addComponent(wgob);
   /*------*/

   /*---------------------------RightUpPanel-------------------------------*/
   scv::ButtonGroup * bgroup = new scv::ButtonGroup();
   scv::Spinner * Spin1 = new scv::Spinner(scv::Point(100, 25), 50, 1, 1024, 1, 1);
   RUpanel->addComponent(Spin1);
   RadioButton *rb1 = new RadioButton8(MyValues);
   RadioButton *rb2 = new RadioButton16(MyValues);
   RadioButton *rSetarvalores = new RadioButtonRSV(MyValues,Spin1);
   rb1->registerButtonGroup(bgroup);
   rb2->registerButtonGroup(bgroup);
   rSetarvalores->registerButtonGroup(bgroup);
   RUpanel->addComponent(rb1);
   RUpanel->addComponent(rb2);
   RUpanel->addComponent(rSetarvalores);
   ButtonWav *rb = new ButtonWav(MyValues, AWpanel, wrd,lreading, rcbt);
   AWpanel->addComponent(rb);
   RUpanel->addComponent(lreading);
   /*------------------------------------------------------------------------*/
  

   /*---------------------------RightDownPanel-------------------------------*/
   /*Canvas + Labels do vetor original*/
   scv::Label *EOrig = new scv::Label(scv::Point(400, 5),scv::Point(502, 0), "Escala:");
   RDpanel->addComponent(EOrig);
   scv::Label *VOrig = new scv::Label(scv::Point(2, 5),scv::Point(502, 0), "");
   RDpanel->addComponent(VOrig);
   RDpanel->addComponent(new CanvasVOrig(MyValues, VOrig, EOrig));
   RDpanel->addComponent(new LabelVetIn());
   /*--------------------------------*/
   /*Canvas + Labels do vetor DCT*/
   scv::Label *EVDCT = new scv::Label(scv::Point(900, 5),scv::Point(1004, 0), "Escala:");
   RDpanel->addComponent(EVDCT);
   scv::Label *IVDCT = new scv::Label(scv::Point(504, 5),scv::Point(1004, 0), "");
   RDpanel->addComponent(IVDCT);
   RDpanel->addComponent(new CanvasVetDCT(MyValues, IVDCT, EVDCT));
   RDpanel->addComponent(new LabelVetDCT());
   /*----------------------------*/
   /*Canvas + Labels do vetor DCT editável*/
   scv::Label *EVEDCT = new scv::Label(scv::Point(400, 375),scv::Point(502, 365), "Escala:");
   RDpanel->addComponent(EVEDCT);
   scv::Label *VEDCT = new scv::Label(scv::Point(2, 375),scv::Point(502, 365), "");
   RDpanel->addComponent(VEDCT);
   CanvasEditDCT *CED = new CanvasEditDCT(MyValues, VEDCT, EVEDCT);
   RDpanel->addComponent(CED);
   RDpanel->addComponent(new LabelVetEditDCT());
   /*-----------------------------------*/
   /*Canvas + Labels do vetor IDCT*/
   scv::Label *EVIDCT = new scv::Label(scv::Point(900, 375),scv::Point(1004, 365), "Escala:");
   RDpanel->addComponent(EVIDCT);
   scv::Label *IVEDCT = new scv::Label(scv::Point(504, 375),scv::Point(1004, 365), "");
   RDpanel->addComponent(IVEDCT);
   CanvasIDCT *cidct = new CanvasIDCT(MyValues, IVEDCT, EVIDCT);
   RDpanel->addComponent(cidct);
   RDpanel->addComponent(new LabelVetIDCT());
   /*-----------------------------*/
   /*------------------------------------------------------------------------*/


   /*---------------------------LeftPanel Components-------------------------*/
   Lpanel->addComponent(new labelGenValues());
   /*Random Generator button*/
   Lpanel->addComponent(new RandomValuesButton(MyValues));
   /*Linearly increasing Generator button*/
   scv::Spinner *MSLC = new scv::Spinner(scv::Point(124, 49), 41, 0, 255, 0, 1);
   Lpanel->addComponent(MSLC);
   Lpanel->addComponent(new ButtonLinearlyIncreasing(MyValues, MSLC));
   /*------------------------------------*/
   /*Senoide Generator button*/
   scv::Spinner *MSS = new scv::Spinner(scv::Point(124, 77), 41, 0, 255, 0, 1);
   Lpanel->addComponent(MSS);
   Lpanel->addComponent(new ButtonSenoide(MyValues, MSS));
   /*----------------------*/
   /*Equal Generator button*/
   scv::Spinner *MSI = new scv::Spinner(scv::Point(124, 105), 41, 0, 255, 0, 1);
   Lpanel->addComponent(MSI);
   Lpanel->addComponent(new ButtonSetEqual(MyValues ,MSI));
   /*----------------------*/
   /*LCG Generator Button*/
   Lpanel->addComponent(new scv::Label(scv::Point(2,162),scv::Point(10, 170), "a"));
   scv::Spinner *LCGA = new scv::Spinner(scv::Point(10, 156), 45, -999,999 , 0, 1);
   Lpanel->addComponent(LCGA);

   Lpanel->addComponent(new scv::Label(scv::Point(57, 162),scv::Point(65, 170), "c"));
   scv::Spinner *LCGC = new scv::Spinner(scv::Point(65, 156), 45, -999,999 , 0, 1);
   Lpanel->addComponent(LCGC);

   Lpanel->addComponent(new scv::Label(scv::Point(112, 162),scv::Point(150, 170), "m"));
   scv::Spinner *LCGM = new scv::Spinner(scv::Point(120, 156), 45, 1,999 , 1, 1);
   Lpanel->addComponent(LCGM);

   Lpanel->addComponent(new LCGButton(MyValues, LCGA, LCGC, LCGM));
   /*---------------------*/
   /*Keyboard Generator Button*/
   Lpanel->addComponent(new scv::Label(scv::Point(2,208),scv::Point(10, 210), "Ponto"));
   scv::Spinner *SPos = new scv::Spinner(scv::Point(30, 205), 50, 1,999999 , 1, 1);
   Lpanel->addComponent(SPos);

   Lpanel->addComponent(new scv::Label(scv::Point(82,208),scv::Point(120, 210), "Valor"));
   scv::Spinner *SVal = new scv::Spinner(scv::Point(105, 205), 60, 0,255 , 0, 0.001);
   Lpanel->addComponent(SVal);

   scv::Button *SetB = new ButtonSetKeyboard(SPos, SVal, MyValues);
   Lpanel->addComponent(SetB);
   /*---------------------*/
   /*Botão de truncamento de valores*/
   ButtonTruncadeParts *btpb = new ButtonTruncadeParts(spinDe,spinAte,MyValues);
   Lpanel->addComponent(spinDe);
   Lpanel->addComponent(spinAte);
   Lpanel->addComponent(new scv::Label(scv::Point(1,258), scv::Point(20,270),"de"));
   Lpanel->addComponent(new scv::Label(scv::Point(1,278), scv::Point(20,280),"ate"));
   Lpanel->addComponent(btpb);

   /*-------*/
   /*Botões para auxílio de manipulação do gráfico Editável da DCT*/

   printOutputButton *pob = new printOutputButton(MyValues);
   Lpanel->addComponent(pob);
   Lpanel->addComponent(new scv::Label(scv::Point(5, 640), scv::Point(100, 650), "Grafico Editavel da DCT"));

   resizeGraphButton *ButtonRGP = new resizeGraphButton(CED);
   Lpanel->addComponent(ButtonRGP);

   resetDCTEditButton *ButtonRED = new resetDCTEditButton(MyValues);
   Lpanel->addComponent(ButtonRED);

   ScaleUpDCTButton *ButtonScaleUp = new ScaleUpDCTButton(CED);
   Lpanel->addComponent(ButtonScaleUp);

   ScaleDownDCTButton *ButtonScaleDown = new ScaleDownDCTButton(CED);
   Lpanel->addComponent(ButtonScaleDown);
   /*-----------------------------------------------------------*/
   /*----------Imprimir gráfico original junto na IDCT-----------*/
   Lpanel->addComponent(new scv::Label(scv::Point(5,600), scv::Point(10,670), "Grafico IDCT"));
   CheckboxOG *cog = new CheckboxOG(&cidct->state);
   Lpanel->addComponent(cog);
   /*------------------------------------------------------------*/
   /*------------------------LABELS--------------------------*/
   Lpanel->addComponent(tamLabel);
   Lpanel->addComponent(iL);
   Lpanel->addComponent(fL);
   /*------------------------------------------------------------*/
   /*----------Restringir faixa de valores que serão imprimidos-----------*/
   Lpanel->addComponent(new scv::Label(scv::Point(1,470), scv::Point(10,520), "Restringir valores nos graficos:"));
   RestButton *Rbutton = new RestButton(iS,fS,MyValues);
   Lpanel->addComponent(Rbutton);
   Lpanel->addComponent(new scv::Label(scv::Point(3,510), scv::Point(160,560), "posicao")); 
   Lpanel->addComponent(iS);
   Lpanel->addComponent(new scv::Label(scv::Point(3,545), scv::Point(160,560), "ate a posicao"));
   Lpanel->addComponent(fS);
   /*------------------------------------------------------------*/
   Lpanel->addComponent(new scv::Label(scv::Point(0, 580), scv::Point(100, 600), "Opcoes dos graficos:"));
   /*----------------------------------------------------------------*/

   kernel->run();

}