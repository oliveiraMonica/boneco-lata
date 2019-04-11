/**
*** Mix - Diogo_RBG - 11/12/2007 ***
* Tocando música e sons com SDL_mixer - http://diogorbg.blogspot.com/2007/12/tocando-msica-e-sons-com-sdlmixer.html
* Teste da SDL_mix

*** Link's ***
* Lazy Foo - http://lazyfoo.net/SDL_tutorials/lesson11/index.php
*/
#include <stdio.h>
#include <SDL/SDL.h>
#include <SDL/SDL_mixer.h>

SDL_Surface *screen, *img;

Mix_Music *musica;
#define NOTA 25
Mix_Chunk *nota[NOTA];
char vet[NOTA] = {
	'q','w','e','r','t','y','u','i','o',
	'a','s','d','f','g','h','j','k','l',
	'z','x','c','v','b','n','m'
};

void init(const char *caption);
void carregar();
SDL_Surface *carregarBmp(const char *nome);
Mix_Chunk *carregarSom(const char *nome);
Mix_Music *carregarMus(const char *nome);
void descarregar();

void play_pause();
void busca_nota(char c);

int main(int argc, char* args[]){
	printf("*** Mix - Diogo_RBG - 11/12/2007 ***\n");
	init("Mix - Diogo_RBG - 11/12/2007");
	carregar();

	int done=0;
	SDL_Event event;
	SDLKey key;
	while(!done){
		while(SDL_PollEvent(&event)){ //- retirando evento da fila.
			switch(event.type){
			case SDL_KEYDOWN: //- evento de botão precionado
				key = event.key.keysym.sym; //- botão precionado
				if(key == SDLK_ESCAPE)
					done = 1;
				else if(key == SDLK_SPACE)
					play_pause();
				else if(key == SDLK_RETURN)
					Mix_HaltMusic(); //- matar música
				else
					busca_nota((char)key);
				break;
			case SDL_QUIT: //- evento para fechar a janela
				done = 1;
				break;
			}
		}
		SDL_Flip(screen); //- atualiza a tela
	}

	descarregar();
}

//- inicializa a SDL e SDL_Mix
void init(const char *caption){
	//--- Inicializando a SDL... ---//
	if( SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_TIMER) <0 ){
		printf("SDL_Init> %s\n", SDL_GetError());
		exit(1);
	}
	atexit(SDL_Quit); //- Irá chamar SDL_Quit quando o programa encerrar

	//- Configurações de vídeo
	screen = SDL_SetVideoMode( 650, 292, 32, SDL_SWSURFACE );
	if(screen == NULL){
		printf("SDL_SetVideo> %s\n", SDL_GetError());
		exit(1);
	}
	SDL_WM_SetCaption(caption, NULL);

	//Initialize SDL_mixer
	if( Mix_OpenAudio( 22050, MIX_DEFAULT_FORMAT, 2, 1024 ) <0 ){
		printf("Mix_OpenAudio> %s\n", Mix_GetError());
		exit(1);
	}
	atexit(Mix_CloseAudio);
}

//- carrega todos os arquivos (imagens,sons...)
void carregar(){
	char str[32];
	int i;

	img = carregarBmp("screen.bmp");
	SDL_BlitSurface(img,0,screen,0);

	musica = carregarMus("tum-tititi.wav");

	for(i=0;i<NOTA;i++){
		sprintf(str,"notas/%02d.ogg",i+1);
		//printf("%s\n",str);
		nota[i] = carregarSom(str);
	}
}

//- carrega imagem -//
SDL_Surface *carregarBmp(const char *nome){
	SDL_Surface *img = SDL_LoadBMP(nome);
	if(!img)
		printf("ERRO> arquivo:'%s'\n",nome);
	return img;
}

//- carrega efeito sonoro
Mix_Chunk *carregarSom(const char *nome){
	Mix_Chunk *som = Mix_LoadWAV(nome);
	if(!som)
		printf("ERRO> arquivo:'%s'\n",nome);
	return som;
}

//- carrega fundo musical
Mix_Music *carregarMus(const char *nome){
	Mix_Music *mus = Mix_LoadMUS(nome);
	if(!mus)
		printf("ERRO> arquivo:'%s'\n",nome);
	return mus;
}

void descarregar(){
	SDL_FreeSurface(img);
	Mix_FreeMusic(musica);
	int i;
	for(i=0;i<NOTA;i++)
		Mix_FreeChunk(nota[i]);

    //Quit SDL_mixer
	Mix_CloseAudio();

    //Quit SDL
    SDL_Quit();
}

//- play/pause fundo musical -//
void play_pause(){
	if( Mix_PlayingMusic() == 0 ){ //- sem música
		if( Mix_PlayMusic( musica, -1 ) == -1 ) //- play música
			printf("ERRO> Mix_PlayMusic\n");
	}else{
		if( Mix_PausedMusic() == 1 ){ //- música pausada
			Mix_ResumeMusic(); //- continua tacando
		}else{
			Mix_PauseMusic(); //- pausar música
		}
	}
}

//- busca por uma nota musical -//
void busca_nota(char c){
	int i;
	for(i=0;i<NOTA;i++){
		if(c==vet[i]){
			if( Mix_PlayChannel( -1, nota[i], 0 ) == -1 )
				printf("ERRO> %c:nota[%d]\n",c,i);
		}
	}
}
