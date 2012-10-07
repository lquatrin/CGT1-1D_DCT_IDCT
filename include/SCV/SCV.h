/*!
\file       SCV.h
\brief      Include all SCV dependencies and components.
\author     SCV Team.
*/

#ifndef __SCV_H__
#define __SCV_H__

/*!
\mainpage SCV Documentation

O SCV � uma API (Application Programming Interface) de facilita��o na constru��o de interfaces de usu�rio (GUI - Graphic User Interface), orientada ao uso de um programador com experi�ncia na linguagem de programa��o C++. Aqui voc� ir� encontrar a documenta��o de todos componentes e funcionalidades oferecidas. Na pasta 'scv_examples' s�o dados exemplos de uso da API com projetos do Microsoft Visual Studio 2010.

\section ide IDEs Suportadas
- Microsoft Visual Studio 2010

\subsection ide_so Sistemas Operacionais
- Windows

A documenta��o atualizada poder� ser acessada atrav�s do endere�o: http://www-usr.inf.ufsm.br/~pozzer/scv <br/>
A �ltima vers�o da biblioteca poder� sempre ser encontrada em: http://www-usr.inf.ufsm.br/~pozzer/scv/scv3.0b.rar

\section home Get Started!

- Para acessar a documenta��o do SCV presente na pasta "documentation" execute o arquivo "Documentation.bat".
- Para visualizar v�rios exemplos utilizando o SCV e demonstrando suas funcionalidades execute o arquivo "SCV_Examples.bat".
- Para acessar o InterfaceDesginer execute o "InterfaceDesigner.bat", nele o usu�rio pode graficamente criar sua Interface, atrav�s de DragAndDrop, e gerar o c�digo SCV correspondente para o arquivo "interface.cpp".

\section runtimes Runtimes do Visual Studio

Caso forem rodar os demos ou programas desenvolvidos no VS2010
em m�quinas que nao tenham o VS, deve-se instalar tamb�m o Microsoft
Visual C++ 2010 Redistributable. Sem ele, vem um aviso que faltam dlls
para execucao, mais especificamente as MSVCP100.dll e MSVCR100.dll.

O instalador da runtime pode ser baixado da Microsoft atrav�s deste link: http://www.microsoft.com/downloads/en/confirmation.aspx?familyid=A7B7A05E-6DE6-4D3A-A423-37BF0912DB84&displaylang=en

Caso prefira, pode-se tamb�m simplesmente copiar essas duas DLLs do seu computador com VS para a pasta do exe. (Ficam em C:\\Windows\\System32\\msvcp100.dll e C:\\Windows\\System32\\msvcr100.dll)

\section tech Detalhes T�cnicos

O SCV est� implementado sobre a API gr�fica OpenGL. Existe uma estrutura hier�rquica de componentes, onde cada componente � responsavel por desenhar os componentes contidos nele. O componentes utilizam a fucionalidade de scissors do OpenGL para fazer a limita��o da �rea de desenho para apenas o ret�ngulo que engloba o componente, al�m de fazer o desenho dele mesmo, utilizando mapas de textura, compartilhados por todas as inst�ncias do mesmo tipo de componente, e fontes, representadas com uma textura contendo todos os caracteres, compartilhada em n�vel global. Esquemas de cor s�o implementados modulando-se a cor das texturas dos componentes. A intera��o entre componentes e o c�digo do usu�rio da biblioteca faz-se utilizando callbacks, presentes como fun��es virtuais nos componentes, que devem ser herdados.

\section credits Cr�ditos

- Prof. Cesar Tadeu Pozzer: Coordenador e Idealizador do Projeto
- Cicero Augusto de Lara Pahins: Desenvolvimento, Documenta��o
- Frederico Artur Limberger: Desenvolvimento, Documenta��o
- Leonardo Quatrin Campagnolo: Desenvolvimento, Documenta��o, Suporte
- Yuri Kunde Schlesner: Desenvolvimento, Documenta��o, Suporte
- Bernardo Henz: Beta-testing

\subsection prev_versions Vers�es Anteriores

- SCV 1.0: Celito Much Felipetto e Vinicius Gottin
- SCV 2.0: Eduardo Speroni e Bernardo Henz

*/


//|||||||||||||||||||||||||||||||||||||||||||||||

#ifdef _WIN32
   #ifdef _MSC_VER
      #pragma warning(disable:4018)
   #endif // _WIN32
#endif // _MSC_VER

//|||||||||||||||||||||||||||||||||||||||||||||||

#include <GL/glew.h>
#include <GL/freeglut.h>
#include <GL/glext.h>
/*
#include <algorithm>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <queue>
#include <cmath>
#include <list>
#include <map>

#include <cstring>
#include <cstdio>
#include <cassert>
*/
//|||||||||||||||||||||||||||||||||||||||||||||||

#include "Kernel.h"

#include "Button.h"
#include "Canvas.h"
#include "CheckBox.h"
#include "ColorPicker.h"
#include "ComboBox.h"
#include "ContextMenu.h"
#include "FileOpen.h"
#include "GlslShader.h"
#include "Image.h"
#include "InternalFrame.h"
#include "Label.h"
#include "Mathematic.h"
#include "MenuBar.h"
#include "ProgressBar.h"
#include "RadioButton.h"
#include "ScrollPane.h"
#include "Separator.h"
#include "Singleton.h"
#include "Slider.h"
#include "StateButton.h"
#include "TabbedPane.h"
#include "Table.h"
#include "util.h"
#include "TreeView.h"

//|||||||||||||||||||||||||||||||||||||||||||||||

#endif // __SCV_H__
