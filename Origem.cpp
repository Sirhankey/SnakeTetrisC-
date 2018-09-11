
#include <iostream>
#include <thread>
#include <vector>
#include <stdio.h>
#include <conio.h>
#include <Windows.h>

using namespace std;

int gameSet;

//SNAKE
bool gameOver;
const int altura = 20;
const int largura = 40;
int x, y, frutaX, frutaY, placar;
int tailX[100], tailY[100];
int nTail;
int snakeMode;
enum eDirection { STOP = 0 ,LEFT , RIGHT , UP , DOWN };
eDirection dir;

//TETRIS
/*wstring tetromino[7];
int nFieldLargura = 12;
int nFieldAltura = 18;
unsigned char *pField = nullptr; // Alocação Dinâmica
int nLarguraTela = 80; // Tamanho Tela Console X (colunas)
int nAlturaTela = 30; // Tamanho Tela Console Y (linhas)
*/

//TETRIS
int nLarguraTela = 80;			// Tamanha tela X (columns)
int nAlturaTela = 30;			// Tamanha tela Y (rows)
wstring tetromino[7];
int nLarguraCampo = 12;
int nAlturaCampo = 18;
unsigned char *pField = nullptr;

//Seta o jogo
void Setup() 
{
	gameOver = false;
	dir = STOP;
	x = largura / 2;
	y = altura / 2;
	frutaX = rand() % largura;
	frutaY = rand() % altura;
	placar = 0;

}
//Desenha o mapa
void Draw()
{
	system("cls"); //Apagar tela
	cout << "Placar : " << placar << "\n";
	
	//Desenhar Mapa
	for (int i = 0; i < largura + 2; i++)
		cout << "#";
	cout << "\n";

	for (int i = 0; i < altura; i++)
	{
		for (int j = 0; j < largura; j++)
		{
			if (j == 0)
				cout << "#";
			//Desenhar Cabeça
			if (i == y && j == x)
				cout << "O";
			//Desenhar Fruta
			else if (i == frutaY && j == frutaX)
				cout << "F";
			else
			{	
				//Desenhar Rabo
				bool print = false;
				for (int k = 0; k < nTail; k++)
				{
					
					if (tailX[k] == j && tailY[k] == i)
					{
						cout << "o";
						print = true;
					}
				}
				if (!print)
					cout << " ";
			}
				

			if (j == largura - 1)
				cout << "#";			
		}
		cout << "\n";
	}

	for (int i = 0; i < largura + 2; i++)
		cout << "#";
	cout << "\n";
}
//Input player
void Input()
{
	if (_kbhit())
	{
		switch (_getch())
		{
		case 'a':
			dir = LEFT;
			break;
		case 'd':
			dir = RIGHT;
			break;
		case 'w':
			dir = UP;
			break;
		case 's':
			dir = DOWN;
			break;
		case 'x':
			gameOver = true;
			break;
		default:
			break;
		}
	}
}
//Lógica do jogo
void Logic()
{
	//Gerar Rabo
	int prevX = tailX[0];
	int prevY = tailY[0];
	int prev2X, prev2Y;
	tailX[0] = x;
	tailY[0] = y;
	for (int i = 1; i < nTail; i++)
	{
		prev2X = tailX[i];
		prev2Y = tailY[i];
		tailX[i] = prevX;
		tailY[i] = prevY;
		prevX = prev2X;
		prevY = prev2Y;
	}
	//Andar
	switch (dir)
	{
	case LEFT:
		x--;
		break;
	case RIGHT:
		x++;
		break;
	case UP:
		y--;
		break;
	case DOWN:
		y++;
		break;
	default:
		break;
	}
	//dir = STOP; //Andar 1 passo de cada vez


	//Bater em paredes
	if (x > largura || x < 0 || y > altura || y < 0)
		if (snakeMode == 1) 
		{
			gameOver = true;
			system("pause");
		}
		else
		{
			//Modo Portal
			if (x >= largura)x = 0; else if (x < 0)x = largura - 1;
			if (y >= altura)y = 0; else if (y < 0)y = altura - 1;
		}


	
	//Bater no Rabo
	for (int i = 0; i < nTail; i++)
		if (tailX[i] == x && tailY[i] == y)
		{
			gameOver = true;
			system("pause");
		}

			//Comer Fruta
	if (x == frutaX && y == frutaY)
	{
		placar += 10;
		frutaX = rand() % largura;
		frutaY = rand() % altura;
		nTail++;
	}

}

	//TETRIS
	/*
void DrawTetris()
{
	//Desenhar Peças
	tetromino[0].append(L"..X.");
	tetromino[0].append(L"..X.");
	tetromino[0].append(L"..X.");
	tetromino[0].append(L"..X.");

	tetromino[1].append(L"..X.");
	tetromino[1].append(L".XX.");
	tetromino[1].append(L".X..");
	tetromino[1].append(L"....");

	tetromino[2].append(L".X..");
	tetromino[2].append(L".XX.");
	tetromino[2].append(L"..X.");
	tetromino[2].append(L"....");

	tetromino[3].append(L"....");
	tetromino[3].append(L".XX.");
	tetromino[3].append(L".XX.");
	tetromino[3].append(L"....");

	tetromino[4].append(L"..X.");
	tetromino[4].append(L".XX.");
	tetromino[4].append(L"..X.");
	tetromino[4].append(L"....");

	tetromino[5].append(L"....");
	tetromino[5].append(L".XX.");
	tetromino[5].append(L"..X.");
	tetromino[5].append(L"..X.");

	tetromino[6].append(L"....");
	tetromino[6].append(L".XX.");
	tetromino[6].append(L".X..");
	tetromino[6].append(L".X..");
}
*/

/*
int Rotate(int px, int py, int r)
{
	//Rotação Peça
	// 0° i = y . w + x || 90° i = 12 + y - ( x . 4 )
	// 180° i = 15 - ( y . 4 ) - x || 270° i = 3 + y ( x . 4 )
	switch (r % 4)
	{
	case 0: return py * 4 + px;         // 0 graus
	case 1: return 12 + py - (px * 4);  // 90 graus
	case 2: return 15 - (py * 4) - px;  // 180 graus
	case 3: return 3 - py + (px * 4);   // 270 graus
	}
}
*/

int Rotate(int px, int py, int r)
{
	int pi = 0;
	switch (r % 4)
	{
	case 0: // 0 graus			// 0  1  2  3
		pi = py * 4 + px;			// 4  5  6  7
		break;						// 8  9 10 11
									//12 13 14 15

	case 1: // 90 graus			//12  8  4  0
		pi = 12 + py - (px * 4);	//13  9  5  1
		break;						//14 10  6  2
									//15 11  7  3

	case 2: // 180 graus			//15 14 13 12
		pi = 15 - (py * 4) - px;	//11 10  9  8
		break;						// 7  6  5  4
									// 3  2  1  0

	case 3: // 270 graus			// 3  7 11 15
		pi = 3 - py + (px * 4);		// 2  6 10 14
		break;						// 1  5  9 13
	}								// 0  4  8 12

	return pi;
}

bool TestarEspaco(int nTetromino, int nRotation, int nPosX, int nPosY)
{
	// todos os campos cell>0 estao ocupados
	for (int px = 0; px < 4; px++)
		for (int py = 0; py < 4; py++)
		{
			// indice da peca
			int pi = Rotate(px, py, nRotation);

			// indice no campo
			int fi = (nPosY + py) * nLarguraCampo + (nPosX + px);

			// Verifique se a peca está dentro dos limites. 
			if (nPosX + px >= 0 && nPosX + px < nLarguraCampo)
			{
				if (nPosY + py >= 0 && nPosY + py < nAlturaCampo)
				{
					// no limite, verifique também a colisão
					if (tetromino[nTetromino][pi] != L'.' && pField[fi] != 0)
						return false; // fail
				}
			}
		}

	return true;
}

/*
GLint FPS = 0;

void FPS(void) {
	static GLint frameCounter = 0;         // frames averaged over 1000mS
	static GLuint currentClock;             // [milliSeconds]
	static GLuint previousClock = 0; // [milliSeconds]
	static GLuint nextClock = 0;     // [milliSeconds]

	++frameCounter;
	currentClock = glutGet(GLUT_ELAPSED_TIME); //has limited resolution, so average over 1000mS
	if (currentClock < nextClock) return;

	FPS = frameCounter / 1; // store the averaged number of frames per second

	previousClock = currentClock;
	nextClock = currentClock + 1000; // set the next clock to aim for as 1 second in the future (1000 ms)
	frameCounter = 0;
}
*/



int main()
{

	bool continuar = false;
	gameSet = 0;
	

	while (continuar == true);
	{

		//Escolher Jogo
		system("cls"); //Apagar tela
		cout << "     ---------------------------------------\n";
		cout << "     |      Fliperama C++                  |\n";
		cout << "     ---------------------------------------\n";
		cout << "      |                                   |\n";
		cout << "      |    Escolha o Jogo :               |\n";
		cout << "      |      1. Snake                     |\n";
		cout << "      |      2. Tetris                    |\n";
		cout << "      |      3. Challenge                 |\n";
		cout << "      |___________________________________|\n";
		cout << "      |Desenvolvido por:                  |\n";
		cout << "      | Daniel Guimaraes                  |\n";
		cout << "      |___________________________________|\n";
		//cout << "Escolha o Jogo : \n1. Snake\n2. Tetris\n";
		cin >> gameSet;
		cout << gameSet;
		if (gameSet == 1 || gameSet == 2 || gameSet == 3)continuar = false;
	}

	if (gameSet == 1)
	{
		system("cls"); //Apagar tela
		//Rodar jogo Snake
		cout << "     ---------------------------------------\n";
		cout << "     |      Fliperama C++                  |\n";
		cout << "     ---------------------------------------\n";
		cout << "      |                                   |\n";
		cout << "      |    Escolha o modo do Jogo :       |\n";
		cout << "      |      1. Classic Snake             |\n";
		cout << "      |      2. Portal Snake              |\n";
		cout << "      |                                   |\n";
		cout << "      |___________________________________|\n";

		//cout << "Escolha o modo do jogo: \n1. Classic Snake\n2. Portal Snake\n";
		cin >> snakeMode;
		if (snakeMode == 1)
		{
			system("cls"); //Apagar tela
			cout << "     ---------------------------------------\n";
			cout << "     |      Fliperama C++                  |\n";
			cout << "     ---------------------------------------\n";
			cout << "      |   Classic Snake :                 |\n";
			cout << "      | (paredes com colisao)             |\n";
			cout << "      | Use as teclas W,A,S,D para guiar  |\n";
			cout << "      | a cobrinha e coletar o max de     |\n";
			cout << "      | frutas;                           |\n";
			cout << "      |___________________________________|\n";
			Sleep(4000); // Espera 5 segundos
			system("cls"); //Apagar tela
			cout << "     ---------------------------------------\n";
			cout << "     |      Fliperama C++                  |\n";
			cout << "     ---------------------------------------\n";
			cout << "      |   Classic Snake :                 |\n";
			cout << "      |                                   |\n";
			cout << "      |   Boa Sorte!                      |\n";
			cout << "      |                                   |\n";
			cout << "      |                                   |\n";
			cout << "      |___________________________________|\n";
			Sleep(2000);
			system("cls"); //Apagar tela
			cout << "     ---------------------------------------\n";
			cout << "     |      Fliperama C++                  |\n";
			cout << "     ---------------------------------------\n";
			cout << "      |   Classic Snake :                 |\n";
			cout << "      |                                   |\n";
			cout << "      |   TRES                            |\n";
			cout << "      |                                   |\n";
			cout << "      |                                   |\n";
			cout << "      |___________________________________|\n";
			Sleep(1000);
			system("cls"); //Apagar tela
			cout << "     ---------------------------------------\n";
			cout << "     |      Fliperama C++                  |\n";
			cout << "     ---------------------------------------\n";
			cout << "      |   Classic Snake :                 |\n";
			cout << "      |                                   |\n";
			cout << "      |   DOIS                            |\n";
			cout << "      |                                   |\n";
			cout << "      |                                   |\n";
			cout << "      |___________________________________|\n";
			Sleep(1000);
			system("cls"); //Apagar tela
			cout << "     ---------------------------------------\n";
			cout << "     |      Fliperama C++                  |\n";
			cout << "     ---------------------------------------\n";
			cout << "      |   Classic Snake :                 |\n";
			cout << "      |                                   |\n";
			cout << "      |   UM                              |\n";
			cout << "      |                                   |\n";
			cout << "      |                                   |\n";
			cout << "      |___________________________________|\n";
			Sleep(1000);

		}
		else if (snakeMode == 2)
		{
			system("cls"); //Apagar tela
			cout << "     ---------------------------------------\n";
			cout << "     |      Fliperama C++                  |\n";
			cout << "     ---------------------------------------\n";
			cout << "      |   Portal Snake :                  |\n";
			cout << "      | (paredes sem colisao)             |\n";
			cout << "      | Use as teclas W,A,S,D para guiar  |\n";
			cout << "      | a cobrinha e coletar o max de     |\n";
			cout << "      | frutas;                           |\n";
			cout << "      |___________________________________|\n";
			Sleep(4000); // Espera 5 segundos
			system("cls"); //Apagar tela
			cout << "     ---------------------------------------\n";
			cout << "     |      Fliperama C++                  |\n";
			cout << "     ---------------------------------------\n";
			cout << "      |   Portal Snake :                  |\n";
			cout << "      |                                   |\n";
			cout << "      |   Boa Sorte!                      |\n";
			cout << "      |                                   |\n";
			cout << "      |                                   |\n";
			cout << "      |___________________________________|\n";
			Sleep(2000);
			system("cls"); //Apagar tela
			cout << "     ---------------------------------------\n";
			cout << "     |      Fliperama C++                  |\n";
			cout << "     ---------------------------------------\n";
			cout << "      |   Portal Snake :                  |\n";
			cout << "      |                                   |\n";
			cout << "      |   TRES                            |\n";
			cout << "      |                                   |\n";
			cout << "      |                                   |\n";
			cout << "      |___________________________________|\n";
			Sleep(1000);
			system("cls"); //Apagar tela
			cout << "     ---------------------------------------\n";
			cout << "     |      Fliperama C++                  |\n";
			cout << "     ---------------------------------------\n";
			cout << "      |   Portal Snake :                  |\n";
			cout << "      |                                   |\n";
			cout << "      |   DOIS                            |\n";
			cout << "      |                                   |\n";
			cout << "      |                                   |\n";
			cout << "      |___________________________________|\n";
			Sleep(1000);
			system("cls"); //Apagar tela
			cout << "     ---------------------------------------\n";
			cout << "     |      Fliperama C++                  |\n";
			cout << "     ---------------------------------------\n";
			cout << "      |   Portal Snake :                  |\n";
			cout << "      |                                   |\n";
			cout << "      |   UM                              |\n";
			cout << "      |                                   |\n";
			cout << "      |                                   |\n";
			cout << "      |___________________________________|\n";
			Sleep(1000);
		}
		else
		{
			cout << "     ---------------------------------------\n";
			cout << "     |      Fliperama C++                  |\n";
			cout << "     ---------------------------------------\n";
			cout << "      |                                   |\n";
			cout << "      |    Escolha o modo do Jogo :       |\n";
			cout << "      |      1. Classic Snake             |\n";
			cout << "      |      2. Portal Snake              |\n";
			cout << "      |                                   |\n";
			cout << "      |___________________________________|\n";
		}
		Setup();
		while (!gameOver)
		{
			Draw();
			Input();
			Logic();
			//Sleep(60);//Delay
		}
		system("cls"); //Apagar tela
		cout << "Game Over!! \nBom jogo meu amigo!!\nVoce obteve um total de :" << placar << " pontos!\n";
		system("pause");
	}

	/*
	float timeNow, timeLast;
	
	while (!gameOver)
{
    float framedelta = ( timeNow - timeLast )
    timeLast = timeNow;

    for each ( GameObject object in World )
    {
        object->Animate(framedelta);
        object->Move(speed * framedelta)
    }

    render();

	*/
	/*
	const int FPS = 60;
	const int frameDelay = 1000 / FPS;
	
	UINT32 frameStart;
	int frameTime;
	Uint32  current_time = SDL_GetTicks();
	while ()
	{
		frameStart = SDL_GetTicks();

	}
	
	*/



	else if (gameSet == 2)
	{

		//Rodar jogo Tetris
		//Desenhar Peças
		/*tetromino[0].append(L"..X.");
		tetromino[0].append(L"..X.");
		tetromino[0].append(L"..X.");
		tetromino[0].append(L"..X.");

		tetromino[1].append(L"..X.");
		tetromino[1].append(L".XX.");
		tetromino[1].append(L".X..");
		tetromino[1].append(L"....");

		tetromino[2].append(L".X..");
		tetromino[2].append(L".XX.");
		tetromino[2].append(L"..X.");
		tetromino[2].append(L"....");

		tetromino[3].append(L"....");
		tetromino[3].append(L".XX.");
		tetromino[3].append(L".XX.");
		tetromino[3].append(L"....");

		tetromino[4].append(L"..X.");
		tetromino[4].append(L".XX.");
		tetromino[4].append(L"..X.");
		tetromino[4].append(L"....");

		tetromino[5].append(L"....");
		tetromino[5].append(L".XX.");
		tetromino[5].append(L"..X.");
		tetromino[5].append(L"..X.");

		tetromino[6].append(L"....");
		tetromino[6].append(L".XX.");
		tetromino[6].append(L".X..");
		tetromino[6].append(L".X..");

		//Cria Tabuleiro
		pField = new unsigned char[nFieldLargura*nFieldAltura];
		for (int x = 0; x < nFieldLargura; x++)//Limites Tabuleiro
			for (int y = 0; y < nFieldAltura; y++)
				pField[y*nFieldLargura + x] = (x == 0 || x == nFieldLargura - 1 || y == nFieldAltura - 1) ? 9 : 0;//Se for Limite(border) set 9, senao set 0
		//Buffer de Tela
		wchar_t *screen = new wchar_t[nLarguraTela*nAlturaTela]; // Cria Array wchar altura e largura tela
		for (int i = 0; i < nLarguraTela*nAlturaTela; i++)screen[i] = L' '; // Preenche com vazio
		HANDLE hConsole = CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE, 0, NULL, CONSOLE_TEXTMODE_BUFFER, NULL);
		SetConsoleActiveScreenBuffer(hConsole);
		DWORD dwBytesEscritos = 0;

		bool bGameOver = false;

		while (!bGameOver)
		{
			//Desenhar Tabuleiro
			for (int x = 0; x < nLarguraTela; x++)
				for (int y = 0; y < nAlturaTela; y++)
					screen[(y + 2)*nLarguraTela + (x + 2)] = L" ABCDEFG=#"[pField[y*nLarguraTela + x]];//Se for 0 desenha " ", 1 "A"...= Linha e # Border
			//Display Frame
			WriteConsoleOutputCharacter(hConsole, screen, nLarguraTela*nAlturaTela, { 0,0 }, &dwBytesEscritos);
		}
	}
	*/
	// Create Screen Buffer

		wchar_t *screen = new wchar_t[nLarguraTela*nAlturaTela];
		for (int i = 0; i < nLarguraTela*nAlturaTela; i++) screen[i] = L' ';
		HANDLE hConsole = CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE, 0, NULL, CONSOLE_TEXTMODE_BUFFER, NULL);
		SetConsoleActiveScreenBuffer(hConsole);
		DWORD dwBytesWritten = 0;

		//CONSOLE_SCREEN_BUFFER_INFO csbiInfo;
		//GetConsoleScreenBufferInfo(hConsole, &csbiInfo);
		//COORD ConsoleWH; ConsoleWH = csbiInfo.dwSize;
		//nScreenWidth = ConsoleWH.X;
		//nScreenHeight = ConsoleWH.Y;

		tetromino[0].append(L"..X...X...X...X."); // Tetronimos 4x4
		tetromino[1].append(L"..X..XX...X.....");
		tetromino[2].append(L".....XX..XX.....");
		tetromino[3].append(L"..X..XX..X......");
		tetromino[4].append(L".X...XX...X.....");
		tetromino[5].append(L".X...X...XX.....");
		tetromino[6].append(L"..X...X..XX.....");

		pField = new unsigned char[nLarguraCampo*nAlturaCampo]; //  field buffer
		for (int x = 0; x < nLarguraCampo; x++) // Board limites
			for (int y = 0; y < nAlturaCampo; y++)
				pField[y*nLarguraCampo + x] = (x == 0 || x == nLarguraCampo - 1 || y == nAlturaCampo - 1) ? 9 : 0;

		// Game Logic
		bool bKey[4];
		int nPecaAtual = 0;
		int nRotacaoAtual = 0;
		int nCurrentX = nLarguraCampo / 2;
		int nCurrentY = 0;
		int nVelocidade = 20;
		int nCountVel = 0;
		bool bForceDown = false;
		bool bRotateHold = true;
		int nPieceCount = 0;
		int nPlacar = 0;
		vector<int> vLines;
		bool bGameOver = false;

		while (!bGameOver) // Main Loop
		{
			// Timing 
			this_thread::sleep_for(50ms); //  1 Game Tick
			nCountVel++;
			bForceDown = (nCountVel == nVelocidade);

			// Input
			for (int k = 0; k < 4; k++)
				bKey[k] = (0x8000 & GetAsyncKeyState((unsigned char)("DASW"[k]))) != 0; // \x27\x25\x28Z // setas e Z rotacionar

			// Game Logic 

			// movimento player
			nCurrentX += (bKey[0] && TestarEspaco(nPecaAtual, nRotacaoAtual, nCurrentX + 1, nCurrentY)) ? 1 : 0;
			nCurrentX -= (bKey[1] && TestarEspaco(nPecaAtual, nRotacaoAtual, nCurrentX - 1, nCurrentY)) ? 1 : 0;
			nCurrentY += (bKey[2] && TestarEspaco(nPecaAtual, nRotacaoAtual, nCurrentX, nCurrentY + 1)) ? 1 : 0;

			// Rotacao
			if (bKey[3])
			{
				nRotacaoAtual += (bRotateHold && TestarEspaco(nPecaAtual, nRotacaoAtual + 1, nCurrentX, nCurrentY)) ? 1 : 0;
				bRotateHold = false;
			}
			else
				bRotateHold = true;

			// Manter peça descendo
			if (bForceDown)
			{
				// Aumentar dificuldade
				nCountVel = 0;
				nPieceCount++;
				if (nPieceCount % 50 == 0)
					if (nVelocidade >= 10) nVelocidade--;

				// Test descer
				if (TestarEspaco(nPecaAtual, nRotacaoAtual, nCurrentX, nCurrentY + 1))
					nCurrentY++; // It can, so do it!
				else
				{
					// Travar onde parar
					for (int px = 0; px < 4; px++)
						for (int py = 0; py < 4; py++)
							if (tetromino[nPecaAtual][Rotate(px, py, nRotacaoAtual)] != L'.')
								pField[(nCurrentY + py) * nLarguraCampo + (nCurrentX + px)] = nPecaAtual + 1;

					// Checar linhas
					for (int py = 0; py < 4; py++)
						if (nCurrentY + py < nAlturaCampo - 1)
						{
							bool bLine = true;
							for (int px = 1; px < nLarguraCampo - 1; px++)
								bLine &= (pField[(nCurrentY + py) * nLarguraCampo + px]) != 0;

							if (bLine)
							{
								// Remover linhas
								for (int px = 1; px < nLarguraCampo - 1; px++)
									pField[(nCurrentY + py) * nLarguraCampo + px] = 8;
								vLines.push_back(nCurrentY + py);
							}
						}

					nPlacar += 25;
					if (!vLines.empty())	nPlacar += (1 << vLines.size()) * 100;

					// Nova peça
					nCurrentX = nLarguraCampo / 2;
					nCurrentY = 0;
					nRotacaoAtual = 0;
					nPecaAtual = rand() % 7;

					// Game over
					bGameOver = !TestarEspaco(nPecaAtual, nRotacaoAtual, nCurrentX, nCurrentY);
				}
			}

			// Display 

			// Desenhar campo
			for (int x = 0; x < nLarguraCampo; x++)
				for (int y = 0; y < nAlturaCampo; y++)
					screen[(y + 2)*nLarguraTela + (x + 2)] = L" ABCDEFG=#"[pField[y*nLarguraCampo + x]];

			// Desenhar peça atual
			for (int px = 0; px < 4; px++)
				for (int py = 0; py < 4; py++)
					if (tetromino[nPecaAtual][Rotate(px, py, nRotacaoAtual)] != L'.')
						screen[(nCurrentY + py + 2)*nLarguraTela + (nCurrentX + px + 2)] = nPecaAtual + 65;

			// Desenhar placar
			swprintf_s(&screen[2 * nLarguraTela + nLarguraCampo + 6], 16, L"PLACAR %8d", nPlacar);


			// Animacao de linha
			if (!vLines.empty())
			{
				// Display Frame 
				WriteConsoleOutputCharacter(hConsole, screen, nLarguraTela * nAlturaTela, { 0,0 }, &dwBytesWritten);
				this_thread::sleep_for(400ms); // Delay

				for (auto &v : vLines)
					for (int px = 1; px < nLarguraCampo - 1; px++)
					{
						for (int py = v; py > 0; py--)
							pField[py * nLarguraCampo + px] = pField[(py - 1) * nLarguraCampo + px];
						pField[px] = 0;
					}

				vLines.clear();
			}

			// Display Frame﻿
			WriteConsoleOutputCharacter(hConsole, screen, nLarguraTela * nAlturaTela, { 0,0 }, &dwBytesWritten);
		}

		// game over
		CloseHandle(hConsole);

		cout << "Game Over!! \nBom jogo meu amigo!!\nVoce obteve um total de :" << nPlacar << " pontos!\n";
		system("pause");
	}
	else if (gameSet == 3)
	{
		Setup();
		snakeMode = 1;
		while (placar < 105)
		{
			Draw();
			Input();
			Logic();
			if (gameOver) {
				system("cls"); //Apagar tela
				cout << "Game Over!! \nBom jogo meu amigo!!\nVoce obteve um total de :" << placar << " pontos!\n";
				system("pause");
				return 0;
			}
			if (placar == 50)
			{
				system("cls"); //Apagar tela
				cout << "Caramba voce e muito bom mesmo\nConseguiu bater os " << placar << " pontos!\nVamos para a segunda fase!";
				system("pause");
				snakeMode = 2;
				placar = placar + 5;
			}
		}

		system("cls"); //Apagar tela
		cout << "Caramba voce e muito bom mesmo\nConseguiu bater os " << placar << " pontos!\nVamos para a terceira fase!";
		system("pause");
		placar = placar + 5;


		wchar_t *screen = new wchar_t[nLarguraTela*nAlturaTela];
		for (int i = 0; i < nLarguraTela*nAlturaTela; i++) screen[i] = L' ';
		HANDLE hConsole = CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE, 0, NULL, CONSOLE_TEXTMODE_BUFFER, NULL);
		SetConsoleActiveScreenBuffer(hConsole);
		DWORD dwBytesWritten = 0;

		//CONSOLE_SCREEN_BUFFER_INFO csbiInfo;
		//GetConsoleScreenBufferInfo(hConsole, &csbiInfo);
		//COORD ConsoleWH; ConsoleWH = csbiInfo.dwSize;
		//nScreenWidth = ConsoleWH.X;
		//nScreenHeight = ConsoleWH.Y;

		tetromino[0].append(L"..X...X...X...X."); 
		tetromino[1].append(L"..X..XX...X.....");
		tetromino[2].append(L".....XX..XX.....");
		tetromino[3].append(L"..X..XX..X......");
		tetromino[4].append(L".X...XX...X.....");
		tetromino[5].append(L".X...X...XX.....");
		tetromino[6].append(L"..X...X..XX.....");

		pField = new unsigned char[nLarguraCampo*nAlturaCampo]; 
		for (int x = 0; x < nLarguraCampo; x++) 
			for (int y = 0; y < nAlturaCampo; y++)
				pField[y*nLarguraCampo + x] = (x == 0 || x == nLarguraCampo - 1 || y == nAlturaCampo - 1) ? 9 : 0;

		// Game Logic
		bool bKey[4];
		int nPecaAtual = 0;
		int nRotacaoAtual = 0;
		int nCurrentX = nLarguraCampo / 2;
		int nCurrentY = 0;
		int nVelocidade = 20;
		int nCountVel = 0;
		bool bForceDown = false;
		bool bRotateHold = true;
		int nPieceCount = 0;
		int nPlacar = 0;
		vector<int> vLines;
		bool bGameOver = false;



		while (!bGameOver) // Main Loop
		{
			while (nPlacar < 1000) {
		
				this_thread::sleep_for(50ms); 
				nCountVel++;
				bForceDown = (nCountVel == nVelocidade);
			for (int k = 0; k < 4; k++)
					bKey[k] = (0x8000 & GetAsyncKeyState((unsigned char)("DASW"[k]))) != 0; 
				nCurrentX += (bKey[0] && TestarEspaco(nPecaAtual, nRotacaoAtual, nCurrentX + 1, nCurrentY)) ? 1 : 0;
				nCurrentX -= (bKey[1] && TestarEspaco(nPecaAtual, nRotacaoAtual, nCurrentX - 1, nCurrentY)) ? 1 : 0;
				nCurrentY += (bKey[2] && TestarEspaco(nPecaAtual, nRotacaoAtual, nCurrentX, nCurrentY + 1)) ? 1 : 0;


				if (bKey[3])
				{
					nRotacaoAtual += (bRotateHold && TestarEspaco(nPecaAtual, nRotacaoAtual + 1, nCurrentX, nCurrentY)) ? 1 : 0;
					bRotateHold = false;
				}
				else
					bRotateHold = true;


				if (bForceDown)
				{

					nCountVel = 0;
					nPieceCount++;
					if (nPieceCount % 50 == 0)
						if (nVelocidade >= 10) nVelocidade--;


					if (TestarEspaco(nPecaAtual, nRotacaoAtual, nCurrentX, nCurrentY + 1))
						nCurrentY++; 
					else
					{

						for (int px = 0; px < 4; px++)
							for (int py = 0; py < 4; py++)
								if (tetromino[nPecaAtual][Rotate(px, py, nRotacaoAtual)] != L'.')
									pField[(nCurrentY + py) * nLarguraCampo + (nCurrentX + px)] = nPecaAtual + 1;

	
						for (int py = 0; py < 4; py++)
							if (nCurrentY + py < nAlturaCampo - 1)
							{
								bool bLine = true;
								for (int px = 1; px < nLarguraCampo - 1; px++)
									bLine &= (pField[(nCurrentY + py) * nLarguraCampo + px]) != 0;

								if (bLine)
								{
									// Remove Line, set to =
									for (int px = 1; px < nLarguraCampo - 1; px++)
										pField[(nCurrentY + py) * nLarguraCampo + px] = 8;
									vLines.push_back(nCurrentY + py);
								}
							}

						nPlacar += 25;
						if (!vLines.empty())	nPlacar += (1 << vLines.size()) * 100;

						// Nova peca
						nCurrentX = nLarguraCampo / 2;
						nCurrentY = 0;
						nRotacaoAtual = 0;
						nPecaAtual = rand() % 7;

						// If piece does not fit straight away, game over!
						bGameOver = !TestarEspaco(nPecaAtual, nRotacaoAtual, nCurrentX, nCurrentY);
					}
				}

				// Display 

				// Draw Field
				for (int x = 0; x < nLarguraCampo; x++)
					for (int y = 0; y < nAlturaCampo; y++)
						screen[(y + 2)*nLarguraTela + (x + 2)] = L" ABCDEFG=#"[pField[y*nLarguraCampo + x]];

				// Desenha peca
				for (int px = 0; px < 4; px++)
					for (int py = 0; py < 4; py++)
						if (tetromino[nPecaAtual][Rotate(px, py, nRotacaoAtual)] != L'.')
							screen[(nCurrentY + py + 2)*nLarguraTela + (nCurrentX + px + 2)] = nPecaAtual + 65;

				// Placar
				swprintf_s(&screen[2 * nLarguraTela + nLarguraCampo + 6], 16, L"PLACAR %8d", nPlacar);


				// Animate Line Completion
				if (!vLines.empty())
				{
					// Display Frame 
					WriteConsoleOutputCharacter(hConsole, screen, nLarguraTela * nAlturaTela, { 0,0 }, &dwBytesWritten);
					this_thread::sleep_for(400ms); // Delay

					for (auto &v : vLines)
						for (int px = 1; px < nLarguraCampo - 1; px++)
						{
							for (int py = v; py > 0; py--)
								pField[py * nLarguraCampo + px] = pField[(py - 1) * nLarguraCampo + px];
							pField[px] = 0;
						}

					vLines.clear();
				}

				// Display Frame﻿
				WriteConsoleOutputCharacter(hConsole, screen, nLarguraTela * nAlturaTela, { 0,0 }, &dwBytesWritten);
			}
			CloseHandle(hConsole);
			system("cls"); //Apagar tela
			cout << "TEMOS UM NOVO CAMPEAO AQUI MEUS AMIGOS!!!\nVOCE CONSEGUIU UM TOTAL DE :" << placar+nPlacar << " PONTOS!\nAgora vai ler um livro!";
			system("pause");
			return 0;

		}

		// game over
		CloseHandle(hConsole);

		cout << "Game Over!! \nBom jogo meu amigo!!\nVoce obteve um total de :" << nPlacar << " pontos!\n";
		system("pause");


	}
else
{

}

	return 0;
}