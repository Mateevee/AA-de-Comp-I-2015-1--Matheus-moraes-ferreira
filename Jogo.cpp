// Jogo.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "SDL/SDL.h"
#include"stdio.h"
#include "iostream"
#include "SDL/SDL_mixer.h"
#include "SDL/SDL_ttf.h"
#include "fstream"
using namespace std;

int raiospeed = 2;
int raiospeed1 = 2;
int raiospeed2 = 2;
int vidasRestantes = 3;
const int gamespeed = 2;
bool usandoescudo = false;
bool pulando=false;
bool pulou = false;
bool esquerda = false;
bool direita = false;
int pulosize=0;
void feedback(SDL_Rect rect,bool x,bool y)
{
	if (x)
	{
      cout << rect.x << endl;
	}
	if (y)
	{
		cout << rect.y << endl;
	}
}
bool intersectsWith(SDL_Rect rect1, SDL_Rect rect2)
{
	bool colliding = false;
	if ((rect1.x+rect1.w>=rect2.x)&&(rect1.x<=rect2.x+rect2.w)&&(rect1.y+1==rect2.y))
	{
		colliding = true;
	}
	return colliding;
}
bool intersectpino(SDL_Rect rect,SDL_Rect pino,int y )
{
	bool colliding=false;
	if ((rect.y==y)&&((rect.x+12)==(pino.x+pino.w)||(rect.x+rect.w-12==pino.x)))
	{
		colliding = true;
	}
	return colliding;
}
SDL_Rect mover(SDL_Rect rect)
{
	
		if (rect.x + 2 + 32 <= 720)
		{
			if (rect.x + raiospeed + 32 >= 720)
			{
				raiospeed = -2;
			}
			if (rect.x + raiospeed <= 0)
			{
				raiospeed = +2;
			}
			rect.x += raiospeed;
		}
	return rect;
}

int main(int argc, char** argv)
{
	inicio:
	SDL_Init(SDL_INIT_EVERYTHING);
	TTF_Init();
	SDL_Window* telaFase1 = nullptr;
	SDL_Window* telaFase2 = nullptr;
	SDL_Window* telafase3 = nullptr;
	SDL_Window* gameoverwindow = nullptr;
	SDL_Window*menu = nullptr;
	SDL_Surface* fundoImg = nullptr;
	SDL_Surface* fase2img = SDL_LoadBMP("C:\\Users\\matee_000\\Documents\\Jogo\\fundofase2.bmp");
	SDL_Surface* fase3img = SDL_LoadBMP("C:\\Users\\matee_000\\Documents\\Jogo\\fasefinal.bmp");
	SDL_Surface* menuimg1 = SDL_LoadBMP("C:\\Users\\matee_000\\Documents\\Jogo\\menu.bmp");
	SDL_Surface* menuimg2 = SDL_LoadBMP("C:\\Users\\matee_000\\Documents\\Jogo\\menu1.bmp");
	SDL_Surface* menuimg3 = SDL_LoadBMP("C:\\Users\\matee_000\\Documents\\Jogo\\menu2.bmp");
	SDL_Surface* menuimg4 = SDL_LoadBMP("C:\\Users\\matee_000\\Documents\\Jogo\\menu3.bmp");
	SDL_Surface* menuimg5 = SDL_LoadBMP("C:\\Users\\matee_000\\Documents\\Jogo\\menu4.bmp");
	SDL_Surface* menufundoimg1 = SDL_LoadBMP("C:\\Users\\matee_000\\Documents\\Jogo\\menufundo.bmp");
	SDL_Surface* inst = SDL_LoadBMP("C:\\Users\\matee_000\\Documents\\Jogo\\inst.bmp");
	SDL_Surface*raioimg = SDL_LoadBMP("C:\\Users\\matee_000\\Documents\\Jogo\\raio.bmp");
	SDL_Surface*scoreVidas = SDL_LoadBMP("C:\\Users\\matee_000\\Documents\\Jogo\\score-1.bmp");
	SDL_Surface*princesaimg = SDL_LoadBMP("C:\\Users\\matee_000\\Documents\\Jogo\\princesa.bmp");
	SDL_Surface*vilaoimg = SDL_LoadBMP("C:\\Users\\matee_000\\Documents\\Jogo\\vilao.bmp");
	SDL_Surface*escudoleftimg = SDL_LoadBMP("C:\\Users\\matee_000\\Documents\\Jogo\\shieldleft.bmp");
	SDL_Surface*escudorightimg = SDL_LoadBMP("C:\\Users\\matee_000\\Documents\\Jogo\\shieldright.bmp");
	SDL_Surface*proximafaseimg = SDL_LoadBMP("C:\\Users\\matee_000\\Documents\\Jogo\\saida info.bmp");
	SDL_Surface*pinoimg = SDL_LoadBMP("C:\\Users\\matee_000\\Documents\\Jogo\\pinos.bmp");
	SDL_Surface*previtoriaimg = SDL_LoadBMP("C:\\Users\\matee_000\\Documents\\Jogo\\fasefinal1.bmp");
	SDL_Surface*vitoriaimg = SDL_LoadBMP("C:\\Users\\matee_000\\Documents\\Jogo\\fasefinal2.bmp");
	SDL_Surface*vilaoderrotadoimg = SDL_LoadBMP("C:\\Users\\matee_000\\Documents\\Jogo\\vilaoderrotado.bmp");
	SDL_Surface*textscoreimg;
	SDL_Surface*gameoverimg= SDL_LoadBMP("C:\\Users\\matee_000\\Documents\\Jogo\\game_over.bmp");
	SDL_Surface*pegarescudoimg = SDL_LoadBMP("C:\\Users\\matee_000\\Documents\\Jogo\\shieldpegar.bmp");
	SDL_Surface*creditos = SDL_LoadBMP("C:\\Users\\matee_000\\Documents\\Jogo\\creditos.bmp");
	SDL_Event ev;
	SDL_Renderer*fase1 = nullptr;
	SDL_Renderer*fase2 = nullptr;
	SDL_Renderer*fase3 = nullptr;
	SDL_Renderer*menurender = nullptr;
	SDL_Surface*imghandler = SDL_LoadBMP("C:\\Users\\matee_000\\Documents\\Jogo\\image.bmp");
	SDL_Texture*imagem = NULL;
	SDL_Texture*fundoTex = nullptr;
	SDL_Texture*menufundo = nullptr;
	SDL_Texture*raiotx = nullptr;
	SDL_Texture*menufundotx = nullptr;
	SDL_Texture*scoreVidastx = nullptr;
	SDL_Texture*princesatx = nullptr;
	SDL_Texture*escudolefttx = nullptr;
	SDL_Texture*escudorighttx = nullptr;
	SDL_Texture*vilaotx = nullptr;
	SDL_Texture*proximafasetx = nullptr;
	SDL_Texture*fase2tx = nullptr;
	SDL_Texture*fase3tx = nullptr;
	SDL_Texture*pinotx = nullptr;
	SDL_Texture*previtoriatx = nullptr;
	SDL_Texture*vitoria = nullptr;
	SDL_Texture*vilaoderrotadotx = nullptr;
	SDL_Texture*textscoretx = nullptr;
	SDL_Texture*gameovertx = nullptr;
	SDL_Texture*pegarescudotx = nullptr;
	SDL_Rect personagem;
	SDL_Rect Sizehandler;
	SDL_Rect raio; 
	SDL_Rect raiosized;
	SDL_Rect score;
	SDL_Rect vidas;
	SDL_Rect vilaohandler;
	SDL_Rect vilao;
	SDL_Rect princesahandler;
	SDL_Rect princesa;
	SDL_Rect escudohandler;
	SDL_Rect escudo;
	SDL_Rect proximafasehandler;
	SDL_Rect proximafase;
	SDL_Rect pinos[8];
	SDL_Rect pinoshandler;
	SDL_Rect textrect;
	SDL_Rect pegarescudo;
	SDL_Rect pegarescudohandler;
	SDL_Rect raio2;
	SDL_Rect raio3;
	int totalscore = 0;
	bool pinosvisible[8];
	int tempo = 0;
	bool exe = true;
	bool exe2=true;
	bool exe3=true;
	bool exe4 = true;
	int time = 0;
	int raiotime = 0;
	int persowidth, persoheight;
	int telaH, telaW;
	const int gamespeed = 2;
	char direcao =	NULL;
	const Uint8*estadoteclado;
	bool menuestado = true;
	int estado = 0;
	int troca = 0;
	int vilaovariacao=0;
	int proximafasetime = 0;
	bool proximafasedisponivel = false;
	int effect = 0;
	bool gameover = false;
	bool win = false;
	bool com_escudo = false;
	bool lancar1=false;
	bool lancar2=false;
	menu = SDL_CreateWindow("Menu", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 720, 480, SDL_WINDOW_SHOWN);
	menurender = SDL_CreateRenderer(menu, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    SDL_LoadBMP("C:\\Users\\matee_000\\Documents\\Jogo\\menu.bmp");
	SDL_SetColorKey(menuimg1, 100, SDL_MapRGB(menuimg1->format, 255, 255, 255));
	SDL_SetColorKey(menuimg2, 100, SDL_MapRGB(menuimg2->format, 255, 255, 255));
	SDL_SetColorKey(menuimg3, 100, SDL_MapRGB(menuimg3->format, 255, 255, 255));
	SDL_SetColorKey(menuimg4, 100, SDL_MapRGB(menuimg4->format, 255, 255, 255));
	SDL_SetColorKey(menuimg5, 100, SDL_MapRGB(menuimg5->format, 255, 255, 255));
	SDL_SetColorKey(scoreVidas, 100, SDL_MapRGB(scoreVidas->format, 255, 255, 255));
    menufundo = SDL_CreateTextureFromSurface(menurender, menuimg1);
	menufundotx = SDL_CreateTextureFromSurface(menurender, menufundoimg1);
	SDL_SetColorKey(princesaimg, 100, SDL_MapRGB(princesaimg->format, 255, 255, 255));
	princesatx = SDL_CreateTextureFromSurface(menurender, princesaimg);
	Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048);
	Mix_Music *teste = Mix_LoadMUS("C:\\Users\\matee_000\\Documents\\Jogo\\teste1.wav");
	Mix_Chunk *menuhover=Mix_LoadWAV("C:\\Users\\matee_000\\Documents\\Jogo\\menu_move_1.wav");
	
	TTF_Font *fonte = TTF_OpenFont("C:\\Users\\matee_000\\Documents\\Jogo\\OpenSans-Regular.ttf", 20);
	int a = 5000;
	int b = 5000;
	int c = 5000;
	
	while (menuestado)
	{
	
		if (!Mix_PlayingMusic())
		{
			Mix_PlayMusic(teste, 0);
		}
		while ((SDL_PollEvent(&ev) != 0))
		{
			if (ev.type==SDL_QUIT)
			{
				menuestado = false;
				SDL_DestroyWindow(menu);
				SDL_Quit();
				return 0;
			}
			else if (ev.type == SDL_MOUSEMOTION)
			{
				if ((ev.button.x >= 100 && (ev.button.x <= 570)&&(ev.button.y >= 200) && (ev.button.y <= 232))&&estado==0)
				{
					menufundo = SDL_CreateTextureFromSurface(menurender, menuimg2);
					if (effect == 0||effect==1)
					{
					  effect = 2;
                      Mix_PlayChannel(1, menuhover,0);
					}
				}
				else if ((ev.button.x >= 100 && (ev.button.x <= 570) && (ev.button.y >= 240) && (ev.button.y <= 276)) && estado == 0)
				{
					menufundo = SDL_CreateTextureFromSurface(menurender, menuimg3);
					if (effect == 0||effect==2)
					{
						effect = 1;
						Mix_PlayChannel(1, menuhover, 0);
					}

				}
				else if ((ev.button.x >= 100 && (ev.button.x <= 570) && (ev.button.y >= 240) && (ev.button.y <= 276)) && estado == 0)
				{
					menufundo = SDL_CreateTextureFromSurface(menurender, menuimg3);
					if (effect == 0 || effect == 2)
					{
						effect = 1;
						Mix_PlayChannel(1, menuhover, 0);
					}

				}
				else if ((ev.button.x >= 100 && (ev.button.x <= 570) && (ev.button.y >= 280) && (ev.button.y <= 318)) && estado == 0)
				{
					menufundo = SDL_CreateTextureFromSurface(menurender, menuimg4);
					if (effect == 0 || effect == 2)
					{
						effect = 1;
						Mix_PlayChannel(1, menuhover, 0);
					}

				}
				else if ((ev.button.x >= 100 && (ev.button.x <= 570) && (ev.button.y >= 326) && (ev.button.y <= 360)) && estado == 0)
				{
					menufundo = SDL_CreateTextureFromSurface(menurender, menuimg5);
					if (effect == 0 || effect == 2)
					{
						effect = 1;
						Mix_PlayChannel(1, menuhover, 0);
					}

				}
				else if (estado==0)
				{
					effect = 0;
					menufundo = SDL_CreateTextureFromSurface(menurender, menuimg1);
					
				}
			}
			else if ((ev.button.x >= 100 && (ev.button.x <= 570) && (ev.button.y >= 200) && (ev.button.y <= 232)))
			{
				if (ev.button.x>=152)
				{
					menuestado = false;
					SDL_DestroyWindow(menu);
				}
			}
			else if ((ev.button.x >= 100 && (ev.button.x <= 570) && (ev.button.y >= 240) && (ev.button.y <= 276))&&estado==0)
			{
				menufundo = SDL_CreateTextureFromSurface(menurender, inst);
				estado = 1;
			}
			else if ((ev.button.x >= 100 && (ev.button.x <= 570) && (ev.button.y >= 280) && (ev.button.y <= 318)) && estado == 0)
			{
				menufundo = SDL_CreateTextureFromSurface(menurender, creditos);
				estado = 1;
			}
			else if ((ev.button.x >= 640 && (ev.button.x <= 700) && (ev.button.y >= 420) && (ev.button.y <= 450)) && estado == 1)
			{
				menufundo = SDL_CreateTextureFromSurface(menurender, menuimg1);
				estado = 0;
			}
			else if ((ev.button.x >= 100 && (ev.button.x <= 570) && (ev.button.y >= 326) && (ev.button.y <= 360)) && estado == 0)
			{
				return 0;
			}
			
			if (gameover)
			{
				estado = 1;
				menufundo = SDL_CreateTextureFromSurface(menurender, gameoverimg);
			}
		}	
	
		SDL_RenderClear(menurender);
		SDL_RenderCopy(menurender, menufundotx,NULL,NULL);
		SDL_RenderCopy(menurender, menufundo, NULL, NULL); 
		SDL_RenderPresent(menurender);
	}
	Mix_CloseAudio();
	Mix_Quit();

	telaFase1 = SDL_CreateWindow("Teste", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 720, 480, SDL_WINDOW_SHOWN);
	SDL_SetColorKey(imghandler, 100, SDL_MapRGB(imghandler->format, 255, 255, 255));
	SDL_SetColorKey(raioimg, 100, SDL_MapRGB(raioimg->format, 255, 255, 255));
	SDL_SetColorKey(princesaimg, 100, SDL_MapRGB(princesaimg->format, 255, 255, 255));
	SDL_SetColorKey(escudoleftimg, 100, SDL_MapRGB(escudoleftimg->format, 255, 255, 255));
	SDL_SetColorKey(escudorightimg, 100, SDL_MapRGB(escudorightimg->format, 255, 255, 255));
	SDL_SetColorKey(vilaoimg, 100, SDL_MapRGB(vilaoimg->format, 255, 255, 255));
	SDL_SetColorKey(proximafaseimg, 100, SDL_MapRGB(proximafaseimg->format, 255, 255, 255));
	fundoImg = SDL_LoadBMP("C:\\Users\\matee_000\\Documents\\Jogo\\fundo-final.bmp");
	fase1 = SDL_CreateRenderer(telaFase1, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	fundoTex = SDL_CreateTextureFromSurface(fase1, fundoImg);
	imagem = SDL_CreateTextureFromSurface(fase1, imghandler);
	raiotx = SDL_CreateTextureFromSurface(fase1, raioimg);
	scoreVidastx = SDL_CreateTextureFromSurface(fase1, scoreVidas);
	escudolefttx = SDL_CreateTextureFromSurface(fase1, escudoleftimg);
	escudorighttx = SDL_CreateTextureFromSurface(fase1, escudorightimg);
	princesatx = SDL_CreateTextureFromSurface(fase1, princesaimg);
	vilaotx = SDL_CreateTextureFromSurface(fase1, vilaoimg);
	proximafasetx = SDL_CreateTextureFromSurface(fase1, proximafaseimg);
	SDL_QueryTexture(imagem, NULL, NULL, &persowidth, &persoheight);
	Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048);
	Mix_Chunk *pulo = Mix_LoadWAV("C:\\Users\\matee_000\\Documents\\Jogo\\pulo.wav");
	Mix_Music *backmusic = Mix_LoadMUS("C:\\Users\\matee_000\\Documents\\Jogo\\musicafundo.wav");

	Mix_VolumeChunk(pulo, 40);
	
	telaH = persoheight / 4;
	telaW = persowidth / 3;
	
	personagem.x = 0;
	personagem.y = 64;
	personagem.h = telaH;
	personagem.w = telaW;
	
	Sizehandler.x = 0;
	Sizehandler.y =453-32;
	Sizehandler.h = 32;
	Sizehandler.w = 32;

	raio.x = 0;
	raio.y = 0;
	raio.h = 32;
	raio.w = 32;

	raiosized.x = 30;
	raiosized.y = 343;
	raiosized.h = 32;
	raiosized.w = 32;
	
	raio2.x = 40;
	raio2.y = 261;
	raio2.h = 32;
	raio2.w = 32;

	raio3.x = 50;
	raio3.y = 175;
	raio3.h = 32;
	raio3.w = 32;

	score.x = 0;
	score.y = 0;
	score.h =32;
	score.w = 96;

	vidas.x = 0;
	vidas.y = 0;
	vidas.h = 32;
	vidas.w = 96;

	princesahandler.x = 0;
	princesahandler.y = 0;
	princesahandler.h = 40;
	princesahandler.w = 32;

	princesa.x = 126;
	princesa.y = 35;
	princesa.h = 40;
	princesa.w = 32;

	escudohandler.x = 0;
	escudohandler.y = 0;
	escudohandler.h = 18;
	escudohandler.w = 10;

	escudo.x = 0;
	escudo.y = 0;
	escudo.h = 18;
	escudo.w = 10;

	vilaohandler.x = 0;
	vilaohandler.y = 0;
	vilaohandler.h = 71;
	vilaohandler.w = 55;

	vilao.x = 50;
	vilao.y = 101-39;
	vilao.h = 71;
	vilao.w = 55;


	proximafasehandler.x = 0;
	proximafasehandler.y = 0;
	proximafasehandler.h = 42;
	proximafasehandler.w = 32;

	proximafase.x = 92;
	proximafase.y = 40;
	proximafase.h = 42;
	proximafase.w = 32;



	
	SDL_SetRenderDrawColor(fase1, 0xFF, 0, 0, 0xFF);
	while (exe&&(gameover==false))
	{
		if (!Mix_PlayingMusic())
		{
			Mix_PlayMusic(backmusic, 0);
		}
		char buffer[20];
		SDL_itoa(a, buffer, 10);
		SDL_Color cor = { 255, 255, 255 };
		textscoreimg = TTF_RenderText_Solid(fonte, buffer, cor);
		textscoretx = SDL_CreateTextureFromSurface(fase1, textscoreimg);
		SDL_QueryTexture(textscoretx, NULL, NULL, &textrect.w, &textrect.h);
		textrect.x = 720 - textrect.w;
		textrect.y = 0;
		if (a>0)
		{
           a--;
		}
		
		//tempo = SDL_GetTicks();
		while ((SDL_PollEvent(&ev) != 0))
		{
			switch (ev.type)
			{
		    	case SDL_QUIT:
				exe = false;
				break;
			}
		}

		bool escada1UP = ((Sizehandler.x >= 550) && (Sizehandler.x <= 570) && (Sizehandler.y <= 453 - 32)&&(Sizehandler.y>=376-32));
		bool escada1DOWN = ((Sizehandler.x >= 550) && (Sizehandler.x <= 570) && (Sizehandler.y <= 453 - 32)&&Sizehandler.y>=343-gamespeed);
		bool escada2UP = ((Sizehandler.x >= 320) && (Sizehandler.x <= 340) && (Sizehandler.y <= 344)&&(Sizehandler.y>=263));
		bool escada2DOWN = ((Sizehandler.x >= 320) && (Sizehandler.x <= 340) && (Sizehandler.y >= 261) && (Sizehandler.y <= 343 - gamespeed));
		bool escada3UP = ((Sizehandler.x >= 20) && (Sizehandler.x <= 40) && (Sizehandler.y <= 261) && (Sizehandler.y >= 176));
		bool escada3DOWN = ((Sizehandler.x >= 20) && (Sizehandler.x <= 40) && (Sizehandler.y <= 261 - gamespeed) && (Sizehandler.y >= 175));
		bool escada4UP=((Sizehandler.x >= 520) && (Sizehandler.x <= 540) && (Sizehandler.y <= 175) && (Sizehandler.y >= 102));
		bool escada4DOWN = ((Sizehandler.x >= 520) && (Sizehandler.x <= 540) && (Sizehandler.y >= 101) && (Sizehandler.y <= 175 - gamespeed));
		bool escada5UP = ((Sizehandler.x >= 220) && (Sizehandler.x <= 240) && (Sizehandler.y <= 101) && (Sizehandler.y >= 45));
		bool escada5DOWN = ((Sizehandler.x >= 220) && (Sizehandler.x <= 240) && (Sizehandler.y <= 101 - gamespeed) && (Sizehandler.y >= 45));
		bool escadas = escada1UP||escada2UP||escada3UP||escada4UP||escada5UP;
		bool Nochao = ((Sizehandler.y == 453 - 32) || (Sizehandler.y == 343) || (Sizehandler.y == 261) || (Sizehandler.y == 175) || (Sizehandler.y == 101) || (Sizehandler.y == 43));
	
			estadoteclado = SDL_GetKeyboardState(NULL);
			vidas.y = (vidasRestantes-1) * 32;
			bool movendo = true;
			esquerda = false;
			direita = false;
			usandoescudo = false;
			if (estadoteclado[SDL_SCANCODE_LCTRL])
			{
				if (com_escudo)
				{
			     usandoescudo = true;
				 movendo = false;
				}
			}
			else if (estadoteclado[SDL_SCANCODE_SPACE] && estadoteclado[SDL_SCANCODE_RIGHT]&&!escadas)
			{
				direita = true;
				esquerda = false;
				personagem.y = 64;
				if (pulando == false && pulou == false)
				{
					Mix_PlayChannel(1, pulo, 0);
					pulando = true;
				}
			}
			else if (estadoteclado[SDL_SCANCODE_SPACE] && estadoteclado[SDL_SCANCODE_LEFT]&&!escadas)
			{
				direita = false;
				esquerda = true;
				personagem.y = 32;
				if (pulando == false && pulou == false)
				{
					Mix_PlayChannel(1, pulo, 0);
					pulando = true;
				}
			}

			else if (estadoteclado[SDL_SCANCODE_RIGHT] && Nochao)
			{
				direita = true;
				if ((Sizehandler.x + gamespeed <= 720 - 32))
				{
					Sizehandler.x += gamespeed;
					Sizehandler.y += 0;
					personagem.y = 64;
				}
			}
			else if (estadoteclado[SDL_SCANCODE_LEFT] && Nochao)
			{
				esquerda = true;
				if ((Sizehandler.x + gamespeed >= 8))
				{
					Sizehandler.x += -gamespeed;
					Sizehandler.y += 0;
					personagem.y = 32;
				}
			}
			else if (estadoteclado[SDL_SCANCODE_UP] && (escada1UP||escada2UP||escada3UP||escada4UP||escada5UP))
			{
				if ((Sizehandler.y + gamespeed >= 8)&&pulou==false)
				{
					Sizehandler.x += 0;
					Sizehandler.y += -gamespeed;
					personagem.y = 96;
				}
			}
			else if (estadoteclado[SDL_SCANCODE_DOWN] && (escada1DOWN||escada2DOWN||escada3DOWN||escada4DOWN||escada5DOWN))
			{
				if ((Sizehandler.y + gamespeed <= 421)&&pulou==false)
				{
					Sizehandler.x += 0;
					Sizehandler.y += gamespeed;
					personagem.y = 0;
				}
			}
			else if (estadoteclado[SDL_SCANCODE_SPACE])
			{ 
				if (pulando==false&&pulou==false&&!escadas)
				{
					Mix_PlayChannel(1, pulo, 0);
					pulando = true;	
				}
			}
			else
			{
				movendo = false;
			}
			raiosized = mover(raiosized);
			raio2=mover(raio2);
			raio3 = mover(raio3);
			if (proximafasedisponivel)
			{
				proximafasetime++;
				if (60 / proximafasetime == 10)
				{
					proximafasetime = 0;
					proximafasehandler.x += 32;
					if (proximafasehandler.x >= 512)
						proximafasehandler.x = 0;
				}
			}
			if (movendo)
			{
               time++;
			   if (60 / time == 4)
			    {
				time = 0;
				personagem.x += telaW;
				if (personagem.x >= persowidth)
					personagem.x = 0;
			  	}
			}
		raiotime++;
		  if (60 / raiotime == 4)
		  {
			  raiotime = 0;
			  raio.x += 32;
			  if (raio.x >= 96)
				  raio.x = 0;
		  }
		  if (pulando==true)
		  {
			  
			  if (direita && (Sizehandler.x + gamespeed <= 720 - 32))
			  {
				  Sizehandler.x += gamespeed;
			  }
			  if (esquerda && (Sizehandler.x + gamespeed >= 8))
			  {
				  Sizehandler.x -= gamespeed;
			  }
			  if (pulosize>=40)
			  {
				  pulosize = 0;
				  pulando = false;
				  pulou = true;
			  }
			  if (pulosize<=40)
			  {
                Sizehandler.y -= gamespeed;
			  }
			  pulosize += gamespeed;
		  }
		  else if (pulando == false && pulou == true)
		  {
			  if (direita&&(Sizehandler.x + gamespeed <= 720 - 32))
			  {
				  Sizehandler.x += gamespeed;
			  }
			  if (esquerda&&(Sizehandler.x + gamespeed >= 8))
			  {
				  Sizehandler.x -= gamespeed;
			  }
			  
			  if (Sizehandler.y <= 453 - 32 && !((Sizehandler.y <= 343)||(Sizehandler.y <= 261) || (Sizehandler.y <= 175) || (Sizehandler.y <= 101)))
			  {	
				if (Sizehandler.y<=453-32)
				  {
					  if (escadas)
					  {
						  pulou = false;
						  personagem.y = 96;
					  }
					  else
					  {
                        Sizehandler.y += gamespeed;
					  }
					  
				  }
				if (Sizehandler.y>=453-32)
				{
				  pulou = false;
				}
			  }
			  if (Sizehandler.y <= 343 && !((Sizehandler.y <= 261) || (Sizehandler.y <= 175) || (Sizehandler.y <= 101)))
			  {
				  if (Sizehandler.y <= 343)
				  {
					  if (escadas)
					  {
						  pulou = false;
						  personagem.y = 96;
					  }
					  else
					  {
						  Sizehandler.y += gamespeed;
					  }
				  }
				  if (Sizehandler.y >= 343)
				  {
					  pulou = false;
				  }
			  }  
			  if (Sizehandler.y <= 261 && !( (Sizehandler.y <= 175) || (Sizehandler.y <= 101)))
			  {
				  if (Sizehandler.y <= 261)
				  {
					  if (escadas)
					  {
						  pulou = false;
						  personagem.y = 96;
					  }
					  else
					  {
						  Sizehandler.y += gamespeed;
					  }
				  }
				  if (Sizehandler.y >= 261)
				  {
					  pulou = false;
				  }
			  }
			  if (Sizehandler.y <= 175 && !( (Sizehandler.y <= 101)))
			  {
				  if (Sizehandler.y <= 175)
				  {
					  if (escadas)
					  {
						  pulou = false;
						  personagem.y = 96;
					  }
					  else
					  {
						  Sizehandler.y += gamespeed;
					  }
				  }
				  if (Sizehandler.y >= 175)
				  {
					  pulou = false;
				  }
			  }
			  if (Sizehandler.y <= 101 )
			  {
				  if (Sizehandler.y <= 101)
				  {
					  if (escadas)
					  {
						  pulou = false;
						  personagem.y = 96;
					  }
					  else
					  {
						  Sizehandler.y += gamespeed;
					  }
				  }
				  if (Sizehandler.y >= 101)
				  {
					  pulou = false;
				  }
			  }
		  }
	
			  

		  if (!usandoescudo)
		  {  
			  if (intersectsWith(Sizehandler,raiosized))
			  {
              
				Sizehandler.x = 0;
				Sizehandler.y = 453 - 32; 
				vidasRestantes--;
				personagem.y = 64;
			  }

		  }
		  else if (usandoescudo == true && (Sizehandler.x + Sizehandler.w == raiosized.x + raiosized.w) && (Sizehandler.y + 1 + Sizehandler.h == raiosized.y + raiosized.h))		
			  {
				  raiosized.x = 32;
				  raiosized.y = 101;
				  raiospeed = +2;
			  }
		  if (Sizehandler.y<=101)
		  {
			  vilaovariacao++;
			  if (vilaovariacao<=40)
			  {
                vilao.x++;
			  }
			  else 
			  {
				  if (!(vilao.y<=-71))
				  { 
					  vilao.y--;
					  if (vilao.y==princesa.y)
						 {
							 princesa.y--;
						 }
				  }
				  else
				  {
					  proximafasedisponivel = true;
				  }
			  }
		  }
		  if (proximafasedisponivel==true)
		  {
			  raiosized.x = -32;
		  }
		  if (Sizehandler.x<=140 && Sizehandler.y<=101)
		  {
			  exe = false;
		  }
		SDL_RenderClear(fase1);
		SDL_RenderCopy(fase1, fundoTex,NULL, NULL);
		SDL_RenderCopy(fase1, NULL, NULL, NULL);
		SDL_RenderCopy(fase1, imagem, &personagem, &Sizehandler);
		SDL_RenderCopy(fase1, raiotx, &raio, &raiosized);
		SDL_RenderCopy(fase1, raiotx, &raio, &raio2);
		SDL_RenderCopy(fase1, raiotx, &raio, &raio3);
		SDL_RenderCopy(fase1, scoreVidastx, &vidas, &score);
		SDL_RenderCopy(fase1, princesatx, &princesahandler, &princesa);  
		SDL_RenderCopy(fase1, vilaotx, &vilaohandler, &vilao);
		
		
		if (usandoescudo)
		  {
			  escudo.y = Sizehandler.y+12;
			  if (personagem.y == 64)
			  {
				  escudo.x = Sizehandler.x+Sizehandler.w-10;
				  SDL_RenderCopy(fase1, escudorighttx, &escudohandler, &escudo);
			  }
			  else if (personagem.y == 32)
			  {
				  escudo.x = Sizehandler.x;
				  SDL_RenderCopy(fase1, escudolefttx, &escudohandler, &escudo);
			  }
		  }
		if (proximafasedisponivel)
		{
			SDL_RenderCopy(fase1, proximafasetx, &proximafasehandler, &proximafase);
		}
		SDL_RenderCopy(fase1, textscoretx, NULL, &textrect);
		SDL_RenderPresent(fase1);
	}

	SDL_DestroyWindow(telaFase1);
	Mix_Quit();
	Mix_CloseAudio();
	proximafasedisponivel = false;
        telaFase2 = SDL_CreateWindow("Fase 2", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 720, 480, SDL_WINDOW_SHOWN);
		fase2 = SDL_CreateRenderer(telaFase2, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
		SDL_FreeSurface(vilaoimg);
		vilaoimg = SDL_LoadBMP("C:\\Users\\matee_000\\Documents\\Jogo\\vilao2fase.bmp");
		SDL_SetColorKey(vilaoimg, 100, SDL_MapRGB(vilaoimg->format, 255, 255, 255));
		SDL_SetColorKey(pegarescudoimg, 100, SDL_MapRGB(pegarescudoimg->format, 255, 255, 255));
		fase2tx = SDL_CreateTextureFromSurface(fase2, fase2img);
        imagem = SDL_CreateTextureFromSurface(fase2, imghandler);
		raiotx = SDL_CreateTextureFromSurface(fase2, raioimg);
		scoreVidastx = SDL_CreateTextureFromSurface(fase2, scoreVidas);
		escudolefttx = SDL_CreateTextureFromSurface(fase2, escudoleftimg);
		escudorighttx = SDL_CreateTextureFromSurface(fase2, escudorightimg);
		princesatx = SDL_CreateTextureFromSurface(fase2, princesaimg);
		vilaotx = SDL_CreateTextureFromSurface(fase2, vilaoimg);
		pegarescudotx = SDL_CreateTextureFromSurface(fase2, pegarescudoimg);
		proximafasetx = SDL_CreateTextureFromSurface(fase2, proximafaseimg);
		raiospeed = -2;
		Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048);

		
		Sizehandler.x = 150;
		Sizehandler.y = 453 - 32;
		Sizehandler.h = 32;
		Sizehandler.w = 32;

		raiosized.x = 0;
		raiosized.y = 175;
		raiosized.h = 32;
		raiosized.w = 32;

		raio2.x = 0;
		raio2.y = 261;
		raio2.h = 32;
		raio2.w = 32;

		raio3.x = 0;
		raio3.y = 343;
		raio3.h = 32;
		raio3.w = 32;

		princesa.x = 500;
		princesa.y = 35;
		princesa.h = 40;
		princesa.w = 32;

		vilao.x = 440;
		vilao.y = 101 - 39;
		vilao.h = 71;
		vilao.w = 55;

		proximafase.x = 480;
		proximafase.y = 40;
		proximafase.h = 42;
		proximafase.w = 32;

		pegarescudohandler.x = 0;
		pegarescudohandler.y = 0;
		pegarescudohandler.h = 32;
		pegarescudohandler.w = 32;

		pegarescudo.x = 680;
		pegarescudo.y = 90;
		pegarescudo.h = 25;
		pegarescudo.w = 25;

	while (exe2&&(gameover==false))
	{
		char buffer[20];
		SDL_itoa(b, buffer, 10);
		SDL_Color cor = { 255, 255, 255 };
		textscoreimg = TTF_RenderText_Solid(fonte, buffer, cor);
		textscoretx = SDL_CreateTextureFromSurface(fase2, textscoreimg);
		SDL_QueryTexture(textscoretx, NULL, NULL, &textrect.w, &textrect.h);
		textrect.x = 720 - textrect.w;
		textrect.y = 0;
		if (b>0)
		{
			b--;
		}
		if (!Mix_PlayingMusic())
		{
			Mix_PlayMusic(backmusic, 0);
		}
		estadoteclado = SDL_GetKeyboardState(NULL);

		while ((SDL_PollEvent(&ev) != 0))
		{
			switch (ev.type)
			{
			case SDL_QUIT:
				exe2 = false;
				break;
			}
		}
		estadoteclado = SDL_GetKeyboardState(NULL);
		bool movendo = true;
		esquerda = false;
		direita = false;
		usandoescudo = false;
		bool escada1UP = ((Sizehandler.x >= 100) && (Sizehandler.x <= 120) && (Sizehandler.y <= 453 - 32) && (Sizehandler.y >= 378 - 32));
		bool escada1DOWN = ((Sizehandler.x >= 100) && (Sizehandler.x <= 120) && (Sizehandler.y <= 453 - 32) && Sizehandler.y >= 343 - gamespeed);
		bool escada2UP = ((Sizehandler.x >= 340) && (Sizehandler.x <= 360) && (Sizehandler.y <= 345) && (Sizehandler.y >= 263));
		bool escada2DOWN = ((Sizehandler.x >= 340) && (Sizehandler.x <= 360) && (Sizehandler.y >= 261) && (Sizehandler.y <= 345-gamespeed));
		bool escada3UP = ((Sizehandler.x >= 660) && (Sizehandler.x <= 680) && (Sizehandler.y <= 345) && (Sizehandler.y >= 102));
		bool escada3DOWN = ((Sizehandler.x >= 660) && (Sizehandler.x <= 680) && (Sizehandler.y <= 345-gamespeed) && (Sizehandler.y >= 100));
		bool escada4UP = ((Sizehandler.x >= 580) && (Sizehandler.x <= 600) && (Sizehandler.y <= 261) && (Sizehandler.y >= 177));
		bool escada4DOWN = ((Sizehandler.x >= 580) && (Sizehandler.x <= 600) && (Sizehandler.y >= 175) && (Sizehandler.y <= 261 - gamespeed));
		bool escada5UP = ((Sizehandler.x >= 20) && (Sizehandler.x <= 40) && (Sizehandler.y <= 175) && (Sizehandler.y >= 102));
		bool escada5DOWN = ((Sizehandler.x >= 20) && (Sizehandler.x <= 40) && (Sizehandler.y <= 175 - gamespeed) && (Sizehandler.y >= 100));
		bool escada6UP = (Sizehandler.x >= 500) && (Sizehandler.x <= 520) && (Sizehandler.y <= 102) && (Sizehandler.y >= 45);
		bool escada6DOWN = (Sizehandler.x >= 500) && (Sizehandler.x <= 520) && (Sizehandler.y <= 100) && (Sizehandler.y >= 45-gamespeed);
		bool escadas = escada1UP || escada2UP || escada3UP || escada4UP || escada5UP;
		bool Nochao = ((Sizehandler.y == 453 - 32) || (Sizehandler.y == 345) || (Sizehandler.y == 261) || (Sizehandler.y == 175) || (Sizehandler.y == 101) || (Sizehandler.y == 43));
		vidas.y = (vidasRestantes - 1) * 32;
		if (estadoteclado[SDL_SCANCODE_LCTRL])
		{
			if (com_escudo)
			{
				usandoescudo = true;
				movendo = false;
			}
		}
		else if (estadoteclado[SDL_SCANCODE_SPACE] && estadoteclado[SDL_SCANCODE_RIGHT] )
		{
			direita = true;
			esquerda = false;
			personagem.y = 64;
			if (pulando == false && pulou == false)
			{
				Mix_PlayChannel(1, pulo, 0);
				pulando = true;
			}
		}
		else if (estadoteclado[SDL_SCANCODE_SPACE] && estadoteclado[SDL_SCANCODE_LEFT] )
		{
			direita = false;
			esquerda = true;
			personagem.y = 32;
			if (pulando == false && pulou == false)
			{
				Mix_PlayChannel(1, pulo, 0);
				pulando = true;
			}
		}

		else if (estadoteclado[SDL_SCANCODE_RIGHT]&&Nochao)
		{
			direita = true;
			if ((Sizehandler.x + gamespeed <= 720 - 32))
			{
				if (Sizehandler.y == 453 - 32 && ((Sizehandler.x + gamespeed <= 260 - 32)))
				{
					Sizehandler.x += gamespeed;
					Sizehandler.y += 0;
					personagem.y = 64;
				}
				else if (Sizehandler.y <= 261 && Sizehandler.x <= 600)
				{
					if (Sizehandler.x + gamespeed <= 600)
					{
						Sizehandler.x += gamespeed;
						Sizehandler.y += 0;
						personagem.y = 64;
					}


				}
				else if (Sizehandler.y!=453-32)
				{
				Sizehandler.x += gamespeed;
				Sizehandler.y += 0;
				personagem.y = 64;

				}
				
			}
		}
		else if (estadoteclado[SDL_SCANCODE_LEFT] &&Nochao)
		{
			esquerda = true;
			if ((Sizehandler.x + gamespeed >= 8))
			{
				if (Sizehandler.y == 453 - 32 && ((Sizehandler.x + gamespeed >= 140 - 32)))
				{
					Sizehandler.x += -gamespeed;
					Sizehandler.y += 0;
					personagem.y = 32;
				}
				else if (Sizehandler.y == 101 && Sizehandler.x >= 648)
				{
					if (Sizehandler.x - gamespeed >= 648 )
					{
						Sizehandler.x += -gamespeed;
						Sizehandler.y += 0;
						personagem.y = 32;
					}


				}
				else if (Sizehandler.y != 453 - 32)
				{
				Sizehandler.x += -gamespeed;
				Sizehandler.y += 0;
				personagem.y = 32;
				}
				
			}
		}
		else if (estadoteclado[SDL_SCANCODE_UP]&&(escada1UP||escada2UP||escada3UP||escada4UP||escada5UP||escada6UP))
		{
			if ((Sizehandler.y + gamespeed >= 8) && pulou == false)
			{
				Sizehandler.x += 0;
				Sizehandler.y += -gamespeed;
				personagem.y = 96;
			}
		}
		else if (estadoteclado[SDL_SCANCODE_DOWN] && (escada1DOWN || escada2DOWN||escada3DOWN||escada4DOWN||escada5DOWN||escada6DOWN))
		{
			if ((Sizehandler.y + gamespeed <= 421) && pulou == false)
			{
				Sizehandler.x += 0;
				Sizehandler.y += gamespeed;
				personagem.y = 0;
			}
		}
		else if (estadoteclado[SDL_SCANCODE_SPACE])
		{
			if (pulando == false && pulou == false && !escadas)
			{
				Mix_PlayChannel(1, pulo, 0);
				pulando = true;
			}
		}
		else
		{
			movendo = false;
		}
		if (movendo)
		{
			time++;
			if (60 / time == 4)
			{
				time = 0;
				personagem.x += telaW;
				if (personagem.x >= persowidth)
					personagem.x = 0;
			}

		}
		raiotime++;
		if (60 / raiotime == 4)
		{
			raiotime = 0;
			raio.x += 32;
			if (raio.x >= 96)
				raio.x = 0;
		}
		if (proximafasedisponivel)
		{
			proximafasetime++;
			if (60 / proximafasetime == 10)
			{
				proximafasetime = 0;
				proximafasehandler.x += 32;
				if (proximafasehandler.x >= 512)
					proximafasehandler.x = 0;
			}
		}
		if (pulando == true)
		{
			if (direita && (Sizehandler.x + gamespeed <= 720 - 32))
			{
				Sizehandler.x += gamespeed;
			}
			if (esquerda && (Sizehandler.x + gamespeed >= 8))
			{
				Sizehandler.x -= gamespeed;
			}
			if (pulosize >= 40)
			{
				pulosize = 0;
				pulando = false;
				pulou = true;
			}
			if (pulosize <= 40)
			{
				Sizehandler.y -= gamespeed;
			}
			pulosize += gamespeed;
		}
		else if (pulando == false && pulou == true)
		{
			if (direita && (Sizehandler.x + gamespeed <= 720 - 32))
			{
				Sizehandler.x += gamespeed;
			}
			if (esquerda && (Sizehandler.x + gamespeed >= 8))
			{
				Sizehandler.x -= gamespeed;
			}

			if (Sizehandler.y <= 453 - 32 && !((Sizehandler.y <= 345) || (Sizehandler.y <= 261) || (Sizehandler.y <= 175) || (Sizehandler.y <= 101)))
			{
				if (Sizehandler.y <= 453 - 32)
				{
					if (escadas)
					{
						pulou = false;
						personagem.y = 96;
					}
					else
					{
						Sizehandler.y += gamespeed;
					}

				}
				if (Sizehandler.y >= 453 - 32)
				{
					pulou = false;
				}
			}
			if (Sizehandler.y <= 345 && !((Sizehandler.y <= 261) || (Sizehandler.y <= 175) || (Sizehandler.y <= 101)))
			{
				if (Sizehandler.y <= 345)
				{
					if (escadas)
					{
						pulou = false;
						personagem.y = 96;
					}
					else
					{
						Sizehandler.y += gamespeed;
					}
				}
				if (Sizehandler.y >= 345)
				{
					pulou = false;
				}
			}
			if (Sizehandler.y <= 261 && !((Sizehandler.y <= 175) || (Sizehandler.y <= 101)))
			{
				if (Sizehandler.y <= 261)
				{
					if (escadas)
					{
						pulou = false;
						personagem.y = 96;
					}
					else
					{
						Sizehandler.y += gamespeed;
					}
				}
				if (Sizehandler.y >= 261)
				{
					pulou = false;
				}
			}
			if (Sizehandler.y <= 175 && !((Sizehandler.y <= 101)))
			{
				if (Sizehandler.y <= 175)
				{
					if (escadas)
					{
						pulou = false;
						personagem.y = 96;
					}
					else
					{
						Sizehandler.y += gamespeed;
					}
				}
				if (Sizehandler.y >= 175)
				{
					pulou = false;
				}
			}
			if (Sizehandler.y <= 101)
			{
				if (Sizehandler.y <= 101)
				{
					if (escadas)
					{
						pulou = false;
						personagem.y = 96;
					}
					else
					{
						Sizehandler.y += gamespeed;
					}
				}
				if (Sizehandler.y >= 101)
				{
					pulou = false;
				}
			}
		}
		if (Sizehandler.y+Sizehandler.h==105)
		{
			com_escudo = true;
		}
	    if ((raiosized.y<=262)==false)
			{
				if (raiosized.x + 2 + 32 <= 720)
				{
					if (raiosized.x + raiospeed1 + 32 >= 720)
					{
						raiospeed1 = -2;
					}
					if (raiosized.x + raiospeed1 <= 0)
					{
						raiospeed1 = +2;
					}
					raiosized.x += raiospeed1;
				}
			}
		else
		{
			if (raiosized.x + 2 + 32 <= 648)
				{
					if (raiosized.x + raiospeed1 + 32 >= 648)
					{
						raiospeed1 = -2;
					}
					if (raiosized.x + raiospeed1 <= 0)
					{
						raiospeed1 = +2;
					}
					raiosized.x += raiospeed1;
				}
		}
		if ((raio2.y <= 262) == false)
		{
			if (raio2.x + 2 + 32 <= 720)
			{
				if (raio2.x + raiospeed2 + 32 >= 720)
				{
					raiospeed2 = -2;
				}
				if (raio2.x + raiospeed2 <= 0)
				{
					raiospeed2 = +2;
				}
				raio2.x += raiospeed2;
			}
		}
		else
		{
			if (raio2.x + 2 + 32 <= 648)
			{
				if (raio2.x + raiospeed2 + 32 >= 648)
				{
					raiospeed2 = -2;
				}
				if (raio2.x + raiospeed2 <= 0)
				{
					raiospeed2 = +2;
				}
				raio2.x += raiospeed2;
			}
		}
		raio3 = mover(raio3);
		

		if (!usandoescudo)
		{
			if (intersectsWith(Sizehandler, raiosized))
			{

				Sizehandler.x = 150;
				Sizehandler.y = 453 - 32;
				vidasRestantes--;
				personagem.y = 64;
			}

		}
		if (Sizehandler.y <= 101&&Sizehandler.x<=500)
		{
				if (!(vilao.y <= -71))
				{
					vilao.y--;
					if (vilao.y == princesa.y)
					{
						princesa.y--;
					}
				}
				else
				{
					proximafasedisponivel = true;
				}
			
		}
		if (proximafasedisponivel == true)
		{
			raiosized.x = -32;
		}
		if (Sizehandler.y<=75-32&&proximafasedisponivel)
		{
			exe2 = false;
		}
		SDL_RenderClear(fase2);
		SDL_RenderCopy(fase2, fase2tx, NULL, NULL);
		SDL_RenderCopy(fase2, imagem, &personagem, &Sizehandler);
		SDL_RenderCopy(fase2, raiotx, &raio, &raiosized);
		SDL_RenderCopy(fase2, raiotx, &raio, &raio2);
		SDL_RenderCopy(fase2, raiotx, &raio, &raio3);
		SDL_RenderCopy(fase2, scoreVidastx, &vidas, &score);
		SDL_RenderCopy(fase2, princesatx, &princesahandler, &princesa);
		SDL_RenderCopy(fase2, vilaotx, &vilaohandler, &vilao);
       
		if (com_escudo==false)
		{
			 SDL_RenderCopy(fase2, pegarescudotx, &pegarescudohandler, &pegarescudo);
		}
		if (usandoescudo)
		{
			escudo.y = Sizehandler.y + 12;
			if (personagem.y == 64)
			{
				escudo.x = Sizehandler.x + Sizehandler.w - 10;
				SDL_RenderCopy(fase2, escudorighttx, &escudohandler, &escudo);
			}
			else if (personagem.y == 32)
			{
				escudo.x = Sizehandler.x;
				SDL_RenderCopy(fase2, escudolefttx, &escudohandler, &escudo);
			}
		}
			if (proximafasedisponivel)
		{
			SDL_RenderCopy(fase2, proximafasetx, &proximafasehandler, &proximafase);
		}
			SDL_RenderCopy(fase2, textscoretx, NULL, &textrect);
		SDL_RenderPresent(fase2);
	}
	SDL_DestroyWindow(telaFase2);
	Mix_Quit();
	Mix_CloseAudio();
	
	telafase3 = SDL_CreateWindow("Fase 3", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 720, 480, SDL_WINDOW_SHOWN);
	fase3 = SDL_CreateRenderer(telafase3, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	SDL_FreeSurface(vilaoimg);
	vilaoimg = SDL_LoadBMP("C:\\Users\\matee_000\\Documents\\Jogo\\vilao2fase.bmp");
	SDL_SetColorKey(vilaoderrotadoimg, 100, SDL_MapRGB(vilaoderrotadoimg->format, 255, 255, 255));
	SDL_SetColorKey(vilaoimg, 100, SDL_MapRGB(vilaoimg->format, 255, 255, 255));
	fase3tx = SDL_CreateTextureFromSurface(fase3, fase3img);
	imagem = SDL_CreateTextureFromSurface(fase3, imghandler);
	raiotx = SDL_CreateTextureFromSurface(fase3, raioimg);
	scoreVidastx = SDL_CreateTextureFromSurface(fase3, scoreVidas);
	escudolefttx = SDL_CreateTextureFromSurface(fase3, escudoleftimg);
	escudorighttx = SDL_CreateTextureFromSurface(fase3, escudorightimg);
	princesatx = SDL_CreateTextureFromSurface(fase3, princesaimg);
	vilaotx = SDL_CreateTextureFromSurface(fase3, vilaoimg);
	pinotx = SDL_CreateTextureFromSurface(fase3, pinoimg);
	previtoriatx = SDL_CreateTextureFromSurface(fase3, previtoriaimg);
	vitoria = SDL_CreateTextureFromSurface(fase3, vitoriaimg);
	vilaoderrotadotx = SDL_CreateTextureFromSurface(fase3, vilaoderrotadoimg);
	raiospeed = -2;
	Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048);	
	    pinosvisible[0] = true;
		pinosvisible[1] = true;
		pinosvisible[2] = true;
		pinosvisible[3] = true;
		pinosvisible[4] = true;
		pinosvisible[5] = true;
		pinosvisible[6] = true;
		pinosvisible[7] = true;

	Sizehandler.x = 150;
	Sizehandler.y = 453 - 32;
	Sizehandler.h = 32;
	Sizehandler.w = 32;

	raiosized.x = 440 - 32;
	raiosized.y = 101;
	raiosized.h = 32;
	raiosized.w = 32;

	princesa.x = 360;
	princesa.y = 40;
	princesa.h = 40;
	princesa.w = 32;

	vilao.x = 280;
	vilao.y = 101 - 39;
	vilao.h = 71;
	vilao.w = 55;

	pinoshandler.x = 0;
	pinoshandler.y = 0;
	pinoshandler.h = 24;
	pinoshandler.w = 12;

	pinos[0].x = 532;
	pinos[0].y = 367;
	pinos[0].h = 24;
	pinos[0].w = 12;

	pinos[1].x = 148;
	pinos[1].y = 367;
	pinos[1].h = 24;
	pinos[1].w = 12;

	pinos[2].x = 502;
	pinos[2].y = 285;
	pinos[2].h = 24;
	pinos[2].w = 12;

	pinos[3].x = 178;
	pinos[3].y = 285;
	pinos[3].h = 24;
	pinos[3].w = 12;

	pinos[4].x = 462;
	pinos[4].y = 200;
	pinos[4].h = 24;
	pinos[4].w = 12;

	pinos[5].x = 208;
	pinos[5].y = 200;
	pinos[5].h = 24;
	pinos[5].w = 12;

	pinos[6].x = 432;
	pinos[6].y = 124;
	pinos[6].h = 24;
	pinos[6].w = 12;

	pinos[7].x = 250;
	pinos[7].y = 124;
	pinos[7].h = 24;
	pinos[7].w = 12;

	while (exe3 && (gameover == false))
	{
		char buffer[20];
		SDL_itoa(c, buffer, 10);
		SDL_Color cor = { 255, 255, 255 };
		textscoreimg = TTF_RenderText_Solid(fonte, buffer, cor);
		textscoretx = SDL_CreateTextureFromSurface(fase3, textscoreimg);
		SDL_QueryTexture(textscoretx, NULL, NULL, &textrect.w, &textrect.h);
		textrect.x = 720 - textrect.w;
		textrect.y = 0;
		if (c>0)
		{
			c--;
		}
		if (!Mix_PlayingMusic())
		{
			Mix_PlayMusic(teste, 0);
		}
		estadoteclado = SDL_GetKeyboardState(NULL);

		while ((SDL_PollEvent(&ev) != 0))
		{
			switch (ev.type)
			{
			case SDL_QUIT:
				exe3 = false;
				break;
			}
		}
		bool escada1UP = ((Sizehandler.x >= 550) && (Sizehandler.x <= 570) && (Sizehandler.y <= 453 - 32) && (Sizehandler.y >= 376 - 32));
		bool escada1DOWN = ((Sizehandler.x >= 550) && (Sizehandler.x <= 570) && (Sizehandler.y <= 453 - 32) && Sizehandler.y >= 343 - gamespeed);
		bool escada2UP = ((Sizehandler.x >= 320) && (Sizehandler.x <= 340) && (Sizehandler.y <= 453 - 32) && (Sizehandler.y >= 376 - 32));
		bool escada2DOWN = ((Sizehandler.x >= 320) && (Sizehandler.x <= 340) && (Sizehandler.y <= 453 - 32) && Sizehandler.y >= 343 - gamespeed);
		bool escada3UP = ((Sizehandler.x >= 20) && (Sizehandler.x <= 40) && (Sizehandler.y <= 453 - 32) && (Sizehandler.y >= 376 - 32));
		bool escada3DOWN = ((Sizehandler.x >= 20) && (Sizehandler.x <= 40) && (Sizehandler.y <= 453 - 32) && Sizehandler.y >= 343 - gamespeed);
		bool escada4UP = ((Sizehandler.x >= 100) && (Sizehandler.x <= 120) && (Sizehandler.y <= 344) && (Sizehandler.y >= 263));
		bool escada4DOWN = ((Sizehandler.x >= 100) && (Sizehandler.x <= 120) && (Sizehandler.y >= 261) && (Sizehandler.y <= 343 - gamespeed));
		bool escada5UP = ((Sizehandler.x >= 210) && (Sizehandler.x <= 230) && (Sizehandler.y <= 344) && (Sizehandler.y >= 263));
		bool escada5DOWN = ((Sizehandler.x >= 210) && (Sizehandler.x <= 230) && (Sizehandler.y >= 261) && (Sizehandler.y <= 343 - gamespeed));
		bool escada6UP = ((Sizehandler.x >= 420) && (Sizehandler.x <= 440) && (Sizehandler.y <= 344) && (Sizehandler.y >= 263));
		bool escada6DOWN = ((Sizehandler.x >= 420) && (Sizehandler.x <= 440) && (Sizehandler.y >= 261) && (Sizehandler.y <= 343 - gamespeed));
		bool escada7UP = ((Sizehandler.x >= 610) && (Sizehandler.x <= 630) && (Sizehandler.y <= 344) && (Sizehandler.y >= 263));
		bool escada7DOWN = ((Sizehandler.x >= 610) && (Sizehandler.x <= 630) && (Sizehandler.y >= 261) && (Sizehandler.y <= 343 - gamespeed));
		bool escada8UP = ((Sizehandler.x >= 20) && (Sizehandler.x <= 40) && (Sizehandler.y <= 261) && (Sizehandler.y >= 176));
		bool escada8DOWN = ((Sizehandler.x >= 20) && (Sizehandler.x <= 40) && (Sizehandler.y <= 261 - gamespeed) && (Sizehandler.y >= 175));
		bool escada9UP = ((Sizehandler.x >= 370) && (Sizehandler.x <= 390) && (Sizehandler.y <= 261) && (Sizehandler.y >= 176));
		bool escada9DOWN = ((Sizehandler.x >= 370) && (Sizehandler.x <= 390) && (Sizehandler.y <= 261 - gamespeed) && (Sizehandler.y >= 175));
		bool escada10UP = ((Sizehandler.x >= 660) && (Sizehandler.x <= 680) && (Sizehandler.y <= 261) && (Sizehandler.y >= 176));
		bool escada10DOWN = ((Sizehandler.x >= 660) && (Sizehandler.x <= 680) && (Sizehandler.y <= 261 - gamespeed) && (Sizehandler.y >= 175));
		bool escada11UP = ((Sizehandler.x >= 510) && (Sizehandler.x <= 530) && (Sizehandler.y <= 175) && (Sizehandler.y >= 102));
		bool escada11DOWN = ((Sizehandler.x >= 510) && (Sizehandler.x <= 530) && (Sizehandler.y >= 101) && (Sizehandler.y <= 175 - gamespeed));
		bool escada12UP = ((Sizehandler.x >= 100) && (Sizehandler.x <= 120) && (Sizehandler.y <= 175) && (Sizehandler.y >= 102));
		bool escada12DOWN = ((Sizehandler.x >= 100) && (Sizehandler.x <= 120) && (Sizehandler.y >= 101) && (Sizehandler.y <= 175 - gamespeed));
		bool escadas = escada1UP || escada2UP || escada3UP || escada4UP || escada5UP;
		bool Nochao = ((Sizehandler.y == 453 - 32) || (Sizehandler.y == 343) || (Sizehandler.y == 261) || (Sizehandler.y == 175) || (Sizehandler.y == 101) || (Sizehandler.y == 43));

		estadoteclado = SDL_GetKeyboardState(NULL);
		vidas.y = (vidasRestantes - 1) * 32;
		bool movendo = true;
		esquerda = false;
		direita = false;
		usandoescudo = false;
		if (estadoteclado[SDL_SCANCODE_LCTRL])
		{
			usandoescudo = true;
			movendo = false;
		}
		else if (estadoteclado[SDL_SCANCODE_SPACE] && estadoteclado[SDL_SCANCODE_RIGHT] && !escadas)
		{
			direita = true;
			esquerda = false;
			personagem.y = 64;
			if (pulando == false && pulou == false)
			{
				Mix_PlayChannel(1, pulo, 0);
				pulando = true;
			}
		}
		else if (estadoteclado[SDL_SCANCODE_SPACE] && estadoteclado[SDL_SCANCODE_LEFT] && !escadas)
		{
			direita = false;
			esquerda = true;
			personagem.y = 32;
			if (pulando == false && pulou == false)
			{
				Mix_PlayChannel(1, pulo, 0);
				pulando = true;
			}
		}

		else if (estadoteclado[SDL_SCANCODE_RIGHT] && Nochao)
		{
			direita = true;
			if ((Sizehandler.x + gamespeed <= 720 - 32))
			{
				Sizehandler.x += gamespeed;
				Sizehandler.y += 0;
				personagem.y = 64;
			}
		}
		else if (estadoteclado[SDL_SCANCODE_LEFT] && Nochao)
		{
			esquerda = true;
			if ((Sizehandler.x + gamespeed >= 8))
			{
				Sizehandler.x += -gamespeed;
				Sizehandler.y += 0;
				personagem.y = 32;
			}
		}
		else if (estadoteclado[SDL_SCANCODE_UP] && (escada1UP || escada2UP || escada3UP || escada4UP || escada5UP || escada6UP || escada7UP || escada8UP || escada9UP || escada10UP || escada11UP || escada12UP ))
		{
			if ((Sizehandler.y + gamespeed >= 8) && pulou == false)
			{
				Sizehandler.x += 0;
				Sizehandler.y += -gamespeed;
				personagem.y = 96;
			}
		}
		else if (estadoteclado[SDL_SCANCODE_DOWN] && (escada1DOWN || escada2DOWN || escada3DOWN || escada4DOWN || escada5DOWN || escada6DOWN || escada7DOWN || escada8DOWN || escada9DOWN || escada10DOWN || escada11DOWN || escada12DOWN ))
		{
			if ((Sizehandler.y + gamespeed <= 421) && pulou == false)
			{
				Sizehandler.x += 0;
				Sizehandler.y += gamespeed;
				personagem.y = 0;
			}
		}
		else if (estadoteclado[SDL_SCANCODE_SPACE])
		{
			if (pulando == false && pulou == false && !escadas)
			{
				Mix_PlayChannel(1, pulo, 0);
				pulando = true;
			}
		}
		else
		{
			movendo = false;
		}
		if (movendo)
		{
			time++;
			if (60 / time == 4)
			{
				time = 0;
				personagem.x += telaW;
				if (personagem.x >= persowidth)
					personagem.x = 0;
			}

		}
		raiotime++;
		if (60 / raiotime == 4)
		{
			raiotime = 0;
			raio.x += 32;
			if (raio.x >= 96)
				raio.x = 0;
		}
		if (pulando == true)
		{

			if (direita && (Sizehandler.x + gamespeed <= 720 - 32))
			{
				Sizehandler.x += gamespeed;
			}
			if (esquerda && (Sizehandler.x + gamespeed >= 8))
			{
				Sizehandler.x -= gamespeed;
			}
			if (pulosize >= 40)
			{
				pulosize = 0;
				pulando = false;
				pulou = true;
			}
			if (pulosize <= 40)
			{
				Sizehandler.y -= gamespeed;
			}
			pulosize += gamespeed;
		}
		else if (pulando == false && pulou == true)
		{
			if (direita && (Sizehandler.x + gamespeed <= 720 - 32))
			{
				Sizehandler.x += gamespeed;
			}
			if (esquerda && (Sizehandler.x + gamespeed >= 8))
			{
				Sizehandler.x -= gamespeed;
			}

			if (Sizehandler.y <= 453 - 32 && !((Sizehandler.y <= 343) || (Sizehandler.y <= 261) || (Sizehandler.y <= 175) || (Sizehandler.y <= 101)))
			{
				if (Sizehandler.y <= 453 - 32)
				{
					if (escadas)
					{
						pulou = false;
						personagem.y = 96;
					}
					else
					{
						Sizehandler.y += gamespeed;
					}

				}
				if (Sizehandler.y >= 453 - 32)
				{
					pulou = false;
				}
			}
			if (Sizehandler.y <= 343 && !((Sizehandler.y <= 261) || (Sizehandler.y <= 175) || (Sizehandler.y <= 101)))
			{
				if (Sizehandler.y <= 343)
				{
					if (escadas)
					{
						pulou = false;
						personagem.y = 96;
					}
					else
					{
						Sizehandler.y += gamespeed;
					}
				}
				if (Sizehandler.y >= 343)
				{
					pulou = false;
				}
			}
			if (Sizehandler.y <= 261 && !((Sizehandler.y <= 175) || (Sizehandler.y <= 101)))
			{
				if (Sizehandler.y <= 261)
				{
					if (escadas)
					{
						pulou = false;
						personagem.y = 96;
					}
					else
					{
						Sizehandler.y += gamespeed;
					}
				}
				if (Sizehandler.y >= 261)
				{
					pulou = false;
				}
			}
			if (Sizehandler.y <= 175 && !((Sizehandler.y <= 101)))
			{
				if (Sizehandler.y <= 175)
				{
					if (escadas)
					{
						pulou = false;
						personagem.y = 96;
					}
					else
					{
						Sizehandler.y += gamespeed;
					}
				}
				if (Sizehandler.y >= 175)
				{
					pulou = false;
				}
			}
			if (Sizehandler.y <= 101)
			{
				if (Sizehandler.y <= 101)
				{
					if (escadas)
					{
						pulou = false;
						personagem.y = 96;
					}
					else
					{
						Sizehandler.y += gamespeed;
					}
				}
				if (Sizehandler.y >= 101)
				{
					pulou = false;
				}
			}
		}
		if (intersectpino(Sizehandler,pinos[0],343))
		{
			pinosvisible[0] = false;
		}
		if (intersectpino(Sizehandler, pinos[1],343))
		{
			pinosvisible[1] = false;
		}
		if (intersectpino(Sizehandler, pinos[2],261))
		{
			pinosvisible[2] = false;
		}
		if (intersectpino(Sizehandler, pinos[3], 261))
		{
			pinosvisible[3] = false;
		}
		if (intersectpino(Sizehandler, pinos[4], 175))
		{
			pinosvisible[4] = false;
		}
		if (intersectpino(Sizehandler, pinos[5], 175))
		{
			pinosvisible[5] = false;
		}
		if (intersectpino(Sizehandler, pinos[6], 101))
		{
			pinosvisible[6] = false;
		}
		if (intersectpino(Sizehandler, pinos[7], 101))
		{
			pinosvisible[7] = false;
		}
	
		bool raiomove1 = (raiosized.x == 30) && (raiosized.y >= 101) && (raiosized.y <= 175);
		bool raiomove2 = (raiosized.x == 590) && (raiosized.y >= 175) && (raiosized.y <= 261);
		bool raiomove3 = (raiosized.x == 350) && (raiosized.y >= 261) && (raiosized.y <= 343);
		bool raiomove4 = (raiosized.x == 110) && (raiosized.y >= 343) && (raiosized.y <= 421);
		if (raiomove1 || raiomove2 || raiomove3 || raiomove4)
		{
			raiosized.y += gamespeed / 2;
		}
		else if ((raiosized.y <= 262) == false)
		{
			if (raiosized.x + 2 + 32 <= 720)
			{
				if (raiosized.x + raiospeed + 32 >= 720)
				{
					raiospeed = -2;
				}
				if (raiosized.x + raiospeed <= 0)
				{
					raiospeed = +2;
				}
				raiosized.x += raiospeed;
			}
		}
		else
		{
			if (raiosized.x + 2 + 32 <= 648)
			{
				if (raiosized.x + raiospeed + 32 >= 648)
				{
					raiospeed = -2;
				}
				if (raiosized.x + raiospeed <= 0)
				{
					raiospeed = +2;
				}
				raiosized.x += raiospeed;
			}


		}
		if (raiosized.x <= 105 - 32 && raiosized.y == 422)
		{
			raiosized.x = 440 - 32;
			raiosized.y = 101;
			raiospeed = -2;
		}

		if (!usandoescudo)
		{
			if (intersectsWith(Sizehandler, raiosized))
			{

				Sizehandler.x = 150;
				Sizehandler.y = 453 - 32;
				vidasRestantes--;
				personagem.y = 64;
			}

		}
	
		SDL_RenderClear(fase3);
		if (pinosvisible[0] || pinosvisible[1] || pinosvisible[2] || pinosvisible[3] || pinosvisible[4] || pinosvisible[5] || pinosvisible[6] || pinosvisible[7])
		{
           SDL_RenderCopy(fase3, fase3tx, NULL, NULL);
		}
		else
		{
			win = true;
			if (vilao.y<=462-71)
			{
				vilao.y++;
			}
			if (vilao.y<224)
			{
			SDL_RenderCopy(fase3, previtoriatx, NULL, NULL);
			}
			else
			{
				if (princesa.y<=101-10)
				{
					princesa.y++;
				}
	         SDL_RenderCopy(fase3, vitoria, NULL, NULL);
			}
		
		}
		
		SDL_RenderCopy(fase3, imagem, &personagem, &Sizehandler);
		SDL_RenderCopy(fase3, raiotx, &raio, &raiosized);
		SDL_RenderCopy(fase3, scoreVidastx, &vidas, &score);
		SDL_RenderCopy(fase3, princesatx, &princesahandler, &princesa);
		if (win)
		{
			SDL_RenderCopy(fase3, vilaoderrotadotx, &vilaohandler, &vilao);
		}
		else
		{
	        SDL_RenderCopy(fase3, vilaotx, &vilaohandler, &vilao);
		}
	
		if (usandoescudo)
		{
			escudo.y = Sizehandler.y + 12;
			if (personagem.y == 64)
			{
				escudo.x = Sizehandler.x + Sizehandler.w - 10;
				SDL_RenderCopy(fase3, escudorighttx, &escudohandler, &escudo);
			}
			else if (personagem.y == 32)
			{
				escudo.x = Sizehandler.x;
				SDL_RenderCopy(fase3, escudolefttx, &escudohandler, &escudo);
			}
		}
		if (pinosvisible[0])
		{
			SDL_RenderCopy(fase3, pinotx, &pinoshandler, &pinos[0]);
		}
		if (pinosvisible[1])
		{
			SDL_RenderCopy(fase3, pinotx, &pinoshandler, &pinos[1]);
		}
		if (pinosvisible[2])
		{
			SDL_RenderCopy(fase3, pinotx, &pinoshandler, &pinos[2]);
		}
		if (pinosvisible[3])
		{
			SDL_RenderCopy(fase3, pinotx, &pinoshandler, &pinos[3]);
		}
		if (pinosvisible[4])
		{
			SDL_RenderCopy(fase3, pinotx, &pinoshandler, &pinos[4]);
		}
		if (pinosvisible[5])
		{
			SDL_RenderCopy(fase3, pinotx, &pinoshandler, &pinos[5]);
		}
		if (pinosvisible[6])
		{
			SDL_RenderCopy(fase3, pinotx, &pinoshandler, &pinos[6]);
		}
		if (pinosvisible[7])
		{
			SDL_RenderCopy(fase3, pinotx, &pinoshandler, &pinos[7]);
		}
		SDL_RenderCopy(fase3, textscoretx, NULL, &textrect);
		SDL_RenderPresent(fase3);
		
		feedback(Sizehandler, true, true);
	}
	SDL_DestroyWindow(telafase3);
	if (gameover)
	{
		menuestado = true;
		exe = true;
		exe2 = true;
		exe3 = true;
		goto inicio;
	}
	char scorestring[30];
	ofstream file;
	file.open("C:\\Users\\matee_000\\Documents\\Jogo\\teste.txt");
	SDL_itoa(a + b + c, scorestring, 10);
	file << scorestring;
	file.close();

	SDL_FreeSurface(fundoImg);
	SDL_FreeSurface(menufundoimg1);
	SDL_FreeSurface(menuimg1);
	SDL_FreeSurface(menuimg2);
	SDL_FreeSurface(menuimg3);
	SDL_FreeSurface(inst);
	SDL_FreeSurface(raioimg);
	
}