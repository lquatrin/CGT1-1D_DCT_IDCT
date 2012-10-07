/*Arquivo contendo a classe que le e armazena os dados de um arquivo wav
Ainda contendo algumas funções para salvar e carregar valores do vetor*/
#ifndef ___WAV___READER___H____
#define ___WAV___READER___H____

#include <SCV/Canvas.h>
#include <SCV/Panel.h>
#include <vector>
#include "Values.h"
#include <cstring>
#include <SCV/RadioButton.h>
#include <fstream> 


class WAVReader : public scv::Canvas
{
public:
   WAVReader(scv:: Label *tam_vet_wav, scv:: Label *nchunks_wav, scv::Panel *Wpanel,
      scv::RadioButton *b200, scv::RadioButton *bLF, scv::Spinner *chunkSpinner, scv::Label *labelReadin,
      Values *mValues);

   ~WAVReader() {}   
   //função chamada para carregar componentes da classe
   void update();
   //pega um bloco do valores e copia no vetor inicial dos valores que serão impressos no grafico
   void setToValues(int leftRight);
   //pega o vetor idct que ja sofreu as modificações e poem no lugar do que foi retirado
   void returnValuesToWav();
   //escreve num arquivo wav
   void writeWAV();
   //le um arquivo wav (le o cabeçalho e da o sinal para o loadSomeChunks começar a ler os blocos).
   void loadWAV();
   //carrega alguns blocos do arquivo wav
   void loadSomeChunks();
   //trunca metade do vetor
   void halfTruncade(int _p);
   //imprime as propriedades retiradas do arquivo wav
   void imprime();
   


   long int chunkSizeValue;
private:
   std::string header;
   long double chunkSize;
   double subChunk1Size;
   double audioFormat;
   double numChannels;
   double sampleRate;
   double byteRate;
   double blockAlign;
   double bitsPerSample;
   long double subChunk2Size;
   std::vector<double> Lvalues;
   std::vector<double> Rvalues;
   scv:: Label *_tam_vet_wav;
   scv:: Label *_nchunks_wav;
   double a;
   bool reading;
   bool sucessfull;
   scv::Panel *_Wpanel;
   scv::RadioButton *_b200;
   scv::RadioButton *_bLF;
   scv::Spinner *_chunkSpinner;
   scv::Label *_labelReadin;
   Values *_mValues;
   int _SetSizeChunk;
   int _SetPosIni;
   int _leftOrRight;
   std::ifstream f;
};


#endif