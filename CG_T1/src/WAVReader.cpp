#include "WAVReader.h"
#include <string>
#include <iostream>
#include <sstream>
#include <cmath>
#include "MyDCTS.h"

WAVReader::WAVReader(scv:: Label *tam_vet_wav, scv:: Label *nchunks_wav, scv::Panel *Wpanel,
   scv::RadioButton *b200, scv::RadioButton *bLF, scv::Spinner *chunkSpinner, scv::Label *labelReadin,
   Values *mValues) :
scv::Canvas(scv::Point(0,0),scv::Point(0,0))
{
   _tam_vet_wav = tam_vet_wav;
   _nchunks_wav = nchunks_wav;
   reading = false;
   sucessfull = false;
   _Wpanel = Wpanel;
   _b200 = b200;
   _bLF = bLF;
   _chunkSpinner = chunkSpinner;
   _labelReadin = labelReadin;
   _mValues = mValues;

}

void WAVReader::update()
{
   if(sucessfull == false && reading == true) // enquanto estiver lendo e não estiver acabado a leitura do wav
   {
      loadSomeChunks();
      if(sucessfull){
         _Wpanel->setVisible(true);
         _b200->setState(true);
         _bLF->setState(true);
         _chunkSpinner->setValue(0);
         _labelReadin->setVisible(false);
         chunkSizeValue = 200; 
      }

   }
   if(sucessfull) //Quando acabar de ler o wav
   {

      std::stringstream sse;
      sse << (Lvalues.size());
      _tam_vet_wav->setString("Tam de cada vetor: " + sse.str());
      if(chunkSizeValue == -1)
      {
         chunkSizeValue = Lvalues.size(); 
      }
      int nblocks = ((Lvalues.size()-1)/chunkSizeValue);
      std::stringstream sse1;
      sse1 << nblocks+1;
      _nchunks_wav->setString("Num de blocos: " + sse1.str());

      _chunkSpinner->setMaxValue(nblocks+1);
      if(_chunkSpinner->getValue() > _chunkSpinner->getMaxValue())
      {
         _chunkSpinner->setValue(_chunkSpinner->getMaxValue());
      }
   }

}

void WAVReader::setToValues(int leftRight) // 0 para left e 1 para right
{
   MyDCTS _md;
   int posIni = ((int)_chunkSpinner->getValue()-1)*chunkSizeValue;
   _SetPosIni = posIni;
   if((int)Lvalues.size() - posIni < chunkSizeValue)
   {
      _mValues->changeTo((int)Lvalues.size() - posIni);
      _SetSizeChunk = (int)Lvalues.size() - posIni;
   }else {
      _mValues->changeTo(chunkSizeValue);
      _SetSizeChunk = chunkSizeValue;
   }
   if(leftRight == 0)//left
   {
      _leftOrRight = 0;
      for(int i = 0 ; i < chunkSizeValue && posIni+i < (int)Lvalues.size() ; i++)
      {
         _mValues->initialValues[i] = Lvalues[posIni+i];
      }

   } else if(leftRight == 1){//right
      _leftOrRight = 1;
      for(int i = 0 ; i < chunkSizeValue && posIni+i < (int)Rvalues.size() ; i++)
      {
         _mValues->initialValues[i] = Lvalues[posIni+i];
      }
   }
   _mValues->dctValues = _md.DCT(_mValues->initialValues);
   _mValues->dctEditValues = _mValues->dctValues;
   _mValues->idctValues = _md.IDCT(_mValues->dctEditValues);

}

void WAVReader::returnValuesToWav()
{
   if((int)_mValues->idctValues.size() == _SetSizeChunk)
   {
      if(_leftOrRight == 0){
         for(int i = 0 ; i < _SetSizeChunk ; i++)
         {

            Lvalues[i] = _mValues->idctValues[i];
         }
      }else if(_leftOrRight == 1){
         for(int i = 0 ; i < _SetSizeChunk ; i++)
         {

            Rvalues[i] = _mValues->idctValues[i];
         }
      }
   }else {
      std::cout << ">>>>>>>>Cant return the values: Size is different of the Chunk<<<<<<<<" << std::endl;
   }
}

void WAVReader::writeWAV()
{
   std::ofstream p("Resources/out.wav", std::ios::out | std::ios::binary);
   for(int i = 0 ; i < (int)header.size() ; i ++)
   {
      p.put(header[i]);
   }
   long int num;
   int n1;
   int n2;
   int auxn;

   for(int j = 0 ; j < (int)Lvalues.size() ; j++)
   {
      num = (long int)Lvalues[j];
      n2 = num/4096;
      num -= n2*4096;
      n2*=16;
      auxn = num/256;
      n2 += auxn;
      num -= auxn*256;

      n1 = num/16;
      num -= n1*16;
      n1*=16;
      n1 += num;
      p.put(n1);
      p.put(n2);

      num = (long int)Rvalues[j];
      n2 = num/4096;
      num -= n2*4096;
      n2*=16;
      auxn = num/256;
      n2 += auxn;
      num -= auxn*256;

      n1 = num/16;
      num -= n1*16;
      n1*=16;
      n1 += num;
      p.put(n1);
      p.put(n2);
   }

   p.close();
}

void WAVReader::loadWAV()
{
   f.open("Resources/in.wav", std::ios::in | std::ios::binary);
   double numT;
   header.clear();
   Lvalues.clear();
   Rvalues.clear();

   //read "RIFF"
   char c = f.get();
   header.push_back(c);
   c = f.get();
   header.push_back(c);
   c = f.get();
   header.push_back(c);
   c = f.get();
   header.push_back(c);

   //reading ChunkSize
   numT = 0;
   int num = f.get();
   numT+= (double)((double)(num/16)*16.0);
   numT+= (double)((double)(num%16));
   c = num;
   header.push_back(c);

   num = f.get();
   numT+= (double)((double)(num/16)*pow(16.0,3));
   numT+= (double)((double)(num%16)*pow(16.0,2));
   c = num;
   header.push_back(c);

   num = f.get();
   numT+= (double)((double)(num/16)*pow(16.0,5));
   numT+= (double)((double)(num%16)*pow(16.0,4));
   c = num;
   header.push_back(c);

   num = f.get();
   numT+= (double)((double)(num/16)*pow(16.0,7));
   numT+= (double)((double)(num%16)*pow(16.0,6));
   c = num;
   header.push_back(c);

   chunkSize = numT;

   //read "WAVE"
   c = f.get();
   header.push_back(c);
   c = f.get();
   header.push_back(c);
   c = f.get();
   header.push_back(c);
   c = f.get();
   header.push_back(c);

   //read "fmt"
   c = f.get();
   header.push_back(c);
   c = f.get();
   header.push_back(c);
   c = f.get();
   header.push_back(c);
   c = f.get();
   header.push_back(c);

   //reading SubChunkSize1
   numT = 0;
   num = f.get();
   numT+= (double)((double)(num/16)*16.0);
   numT+= (double)((double)(num%16));
   c = num;
   header.push_back(c);

   num = f.get();
   numT+= (double)((double)(num/16)*pow(16.0,3));
   numT+= (double)((double)(num%16)*pow(16.0,2));
   c = num;
   header.push_back(c);

   num = f.get();
   numT+= (double)((double)(num/16)*pow(16.0,5));
   numT+= (double)((double)(num%16)*pow(16.0,4));
   c = num;
   header.push_back(c);

   num = f.get();
   numT+= (double)((double)(num/16)*pow(16.0,7));
   numT+= (double)((double)(num%16)*pow(16.0,6));
   c = num;
   header.push_back(c);

   subChunk1Size = numT;

   //reading AudioFormat
   numT = 0;
   num = f.get();
   numT+= (double)((double)(num/16)*16.0);
   numT+= (double)((double)(num%16));
   c = num;
   header.push_back(c);

   num = f.get();
   numT+= (double)((double)(num/16)*pow(16.0,3));
   numT+= (double)((double)(num%16)*pow(16.0,2));
   c = num;
   header.push_back(c);

   audioFormat = numT;

   //reading NumChannels
   numT = 0;
   num = f.get();
   numT+= (double)((double)(num/16)*16.0);
   numT+= (double)((double)(num%16));
   c = num;
   header.push_back(c);

   num = f.get();
   numT+= (double)((double)(num/16)*pow(16.0,3));
   numT+= (double)((double)(num%16)*pow(16.0,2));
   c = num;
   header.push_back(c);

   numChannels = numT;

   //reading SampleRate
   numT = 0;
   num = f.get();
   numT+= (double)((double)(num/16)*16.0);
   numT+= (double)((double)(num%16));
   c = num;
   header.push_back(c);

   num = f.get();
   numT+= (double)((double)(num/16)*pow(16.0,3));
   numT+= (double)((double)(num%16)*pow(16.0,2));
   c = num;
   header.push_back(c);

   num = f.get();
   numT+= (double)((double)(num/16)*pow(16.0,5));
   numT+= (double)((double)(num%16)*pow(16.0,4));
   c = num;
   header.push_back(c);

   num = f.get();
   numT+= (double)((double)(num/16)*pow(16.0,7));
   numT+= (double)((double)(num%16)*pow(16.0,6));
   c = num;
   header.push_back(c);

   sampleRate = numT;

   //reading Byterate
   numT = 0;
   num = f.get();
   numT+= (double)((double)(num/16)*16.0);
   numT+= (double)((double)(num%16));
   c = num;
   header.push_back(c);

   num = f.get();
   numT+= (double)((double)(num/16)*pow(16.0,3));
   numT+= (double)((double)(num%16)*pow(16.0,2));
   c = num;
   header.push_back(c);

   num = f.get();
   numT+= (double)((double)(num/16)*pow(16.0,5));
   numT+= (double)((double)(num%16)*pow(16.0,4));
   c = num;
   header.push_back(c);

   num = f.get();
   numT+= (double)((double)(num/16)*pow(16.0,7));
   numT+= (double)((double)(num%16)*pow(16.0,6));
   c = num;
   header.push_back(c);

   byteRate = numT;

   //reading blockAlign
   numT = 0;
   num = f.get();
   numT+= (double)((double)(num/16)*16.0);
   numT+= (double)((double)(num%16));
   c = num;
   header.push_back(c);

   num = f.get();
   numT+= (double)((double)(num/16)*pow(16.0,3));
   numT+= (double)((double)(num%16)*pow(16.0,2));
   c = num;
   header.push_back(c);

   blockAlign = numT;

   //reading bitsPerSample
   numT = 0;
   num = f.get();
   numT+= (double)((double)(num/16)*16.0);
   numT+= (double)((double)(num%16));
   c = num;
   header.push_back(c);

   num = f.get();
   numT+= (double)((double)(num/16)*pow(16.0,3));
   numT+= (double)((double)(num%16)*pow(16.0,2));
   c = num;
   header.push_back(c);

   bitsPerSample = numT;

   //read "data"
   c = f.get();
   header.push_back(c);
   c = f.get();
   header.push_back(c);
   c = f.get();
   header.push_back(c);
   c = f.get();
   header.push_back(c);

   //reading SubChunkSize2
   numT = 0;
   num = f.get();
   numT+= (double)((double)(num/16)*16.0);
   numT+= (double)((double)(num%16));
   c = num;
   header.push_back(c);

   num = f.get();
   numT+= (double)((double)(num/16)*pow(16.0,3));
   numT+= (double)((double)(num%16)*pow(16.0,2));
   c = num;
   header.push_back(c);

   num = f.get();
   numT+= (double)((double)(num/16)*pow(16.0,5));
   numT+= (double)((double)(num%16)*pow(16.0,4));
   c = num;
   header.push_back(c);

   num = f.get();
   numT+= (double)((double)(num/16)*pow(16.0,7));
   numT+= (double)((double)(num%16)*pow(16.0,6));
   c = num;
   header.push_back(c);

   subChunk2Size = numT;


   a = subChunk2Size;
   reading = true;
   sucessfull = false;

}

void WAVReader::loadSomeChunks()
{
   int countr = 0;

   //read samples:
   while(a > 0){
      //Left channel
      double numT = 0;
      int num = f.get();
      numT+= (double)((double)(num/16)*16.0);
      numT+= (double)((double)(num%16));

      num = f.get();

      numT+= (double)((double)(num/16)*pow(16.0,3));
      numT+= (double)((double)(num%16)*pow(16.0,2));
      Lvalues.push_back(numT);

      //Right channel
      numT = 0;
      num = f.get();
      numT+= (double)((double)(num/16)*16.0);
      numT+= (double)((double)(num%16));

      num = f.get();

      numT+= (double)((double)(num/16)*pow(16.0,3));
      numT+= (double)((double)(num%16)*pow(16.0,2));
      Rvalues.push_back(numT);

      a -=4;
      countr++;
      if(countr == 100){return;}
   }
   reading = false;
   sucessfull = true;
   f.close();
}

void WAVReader::halfTruncade(int _p){ // 0 ou 1
   MyDCTS _md;
   Lvalues = _md.DCT(Lvalues);
   Rvalues = _md.DCT(Rvalues);
   int n = (int)Lvalues.size();
   for(int i = (n-n/10)*_p ; i < ((n-n/10)*_p)+n/10 && i < n; i++)
   {
      Lvalues[i] = 0;
      Rvalues[i] = 0;
   }

   Lvalues = _md.IDCT(Lvalues);
   Rvalues = _md.IDCT(Rvalues);
}

void WAVReader::imprime()
{
   std::cout << "chunkSize = " << chunkSize << std::endl;
   std::cout << "subChunk1Size = " << subChunk1Size << std::endl;
   std::cout << "audioFormat = " << audioFormat << std::endl;
   std::cout << "numChannels = " << numChannels << std::endl;
   std::cout << "sampleRate = " << sampleRate << std::endl;
   std::cout << "byteRate = " << byteRate << std::endl;
   std::cout << "blockAlign = " << blockAlign << std::endl;
   std::cout << "bitsPerSample = " << bitsPerSample << std::endl;
   std::cout << "subChunk2Size = " << subChunk2Size << std::endl;
   std::cout << "LValues = " << Lvalues.size() << std::endl;
   std::cout << "RValues = " << Rvalues.size() << std::endl;
}
