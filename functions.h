
int tamBloco=32;
int tela[19][19];

BITMAP* buffer;
BITMAP* blocoVerm;
BITMAP* blocoAzul;
BITMAP* blocoVerde;
BITMAP* blocoCinza;
BITMAP* blocoAmarelo;
BITMAP* blocoRoxo;
BITMAP* blocoLaranja;
BITMAP* blocoRosa;
BITMAP* logo;
BITMAP* spiderman;
BITMAP* spiderman_meme;
BITMAP* spiderman_intro;
BITMAP* shield;
BITMAP* spiderlost;
FONT *letra;
FONT *fontCordia48;
FONT *fontCordia28;
Glow glow;

//class for simple map object
class objeto
{
   public:
   int x;
   int y;
   BITMAP* imagem;
};

//class for a player
class jogador
{
   public:
   int x;
   int y;
   BITMAP* imagem;
   int artefatos;
   int combustivel;
};

objeto artefato;
objeto combustivel;
jogador jogador_spiderman;

inline void init()
{   //allegro 4.2 initialization function
    allegro_init();
    set_color_depth(32);
    set_gfx_mode(GFX_AUTODETECT_WINDOWED, 20*tamBloco, 20*tamBloco, 0, 0);

    install_timer();
    install_keyboard();
    install_mouse();
}

inline void deinit()
{   //allegro deinit function
    clear_keybuf();
    allegro_exit();
}


void loadAll()
{   //class that loads all extern images and fonts

    set_window_title("TictacKode - Mini-Game do Pirralho - Linguagem C com Allegro 4");
    buffer=create_bitmap(20*tamBloco,20*tamBloco);

    fontCordia28=load_font("fonts/cordia28.pcx",NULL,NULL);
    if(!fontCordia28) { exit(1); }

    letra=load_font("fonts/cordia36.pcx",NULL,NULL);
    if(!letra) { exit(1); }

    fontCordia48=load_font("fonts/cordia48.pcx",NULL,NULL);
    if(!fontCordia48) { exit(1); }

    logo=create_bitmap(640,640);
    logo=load_bitmap("img/tictackode.bmp",0);
    if(!logo) { exit(1); }

    spiderman=create_bitmap(32,32);
    spiderman=load_bitmap("img/spider_man_head.bmp",0);
    if(!spiderman) { exit(1); }

    shield=create_bitmap(32,32);
    shield=load_bitmap("img/shield.bmp",0);
    if(!shield) { exit(1); }

    spiderman_meme=create_bitmap(640,640);
    spiderman_meme=load_bitmap("img/spiderman_meme.bmp",0);
    if(!spiderman_meme) { exit(1); }

    spiderman_intro=create_bitmap(640,640);
    spiderman_intro=load_bitmap("img/spiderman_intro.bmp",0);
    if(!spiderman_intro) { exit(1); }

    spiderlost=create_bitmap(640,640);
    spiderlost=load_bitmap("img/spiderlost.bmp",0);
    if(!spiderlost) { exit(1); }
}
void freeAll()
{   //clear bitmaps from memory

    destroy_bitmap(blocoVerm);
    destroy_bitmap(blocoAzul);
    destroy_bitmap(blocoVerde);
    destroy_bitmap(blocoCinza);
    destroy_bitmap(blocoAmarelo);
    destroy_bitmap(blocoRoxo);
    destroy_bitmap(blocoLaranja);
    destroy_bitmap(blocoRosa);
}

void criaBloco(BITMAP* bmp, int red, int green, int blue)
{   //this function generates the color for the square bitmaps

	int escuroR = 30,escuroG=30,escuroB=30;

	if (red < 30) { escuroR = 0; }
	if (green < 30) { escuroG = 0; }
	if (blue < 30) { escuroB = 0; }

	rectfill(bmp, 0, 0, tamBloco - (tamBloco / 10), tamBloco - (tamBloco / 10), makecol(red, green, blue));
	rectfill(bmp, 0, tamBloco - (tamBloco / 10), tamBloco, tamBloco, makecol(red - escuroR, green - escuroG, blue - escuroB));
	rectfill(bmp, tamBloco - (tamBloco / 10), 0, tamBloco, tamBloco, makecol(red - escuroR, green - escuroG, blue - escuroB));

}
void initBlockColor()
{
	// tamBloco é a variavel que guarda o tamanho dos blocos
	// tamBloco=size of the square in pixels
	blocoAzul=create_bitmap(tamBloco, tamBloco);
	criaBloco(blocoAzul, 32, 32, 192);

	blocoVerde = create_bitmap(tamBloco, tamBloco);
	criaBloco(blocoVerde, 32, 192, 32);

	blocoVerm = create_bitmap(tamBloco, tamBloco);
	criaBloco(blocoVerm, 192, 32, 32);

	blocoAmarelo = create_bitmap(tamBloco, tamBloco);
	criaBloco(blocoAmarelo, 255,215,0);

	blocoRoxo = create_bitmap(tamBloco, tamBloco);
	criaBloco(blocoRoxo, 139, 0, 204);

	blocoCinza = create_bitmap(tamBloco, tamBloco);
	criaBloco(blocoCinza, 92, 92, 92);

	blocoLaranja = create_bitmap(tamBloco, tamBloco);
	criaBloco(blocoLaranja, 255, 153, 0);

	blocoRosa = create_bitmap(tamBloco, tamBloco);
	criaBloco(blocoRosa, 255, 0, 128);

}
void initGame()
{   //do the game initializations

    srand(time(0));
    jogador_spiderman.x=rand()%19;
    jogador_spiderman.y=rand()%19;

    artefato.x=rand()%19;
    artefato.y=rand()%19;

    combustivel.x=rand()%19;
    combustivel.y=rand()%19;

    jogador_spiderman.combustivel=(rand()%40)+15;
    initBlockColor();

    jogador_spiderman.imagem=spiderman;
    textout_ex(jogador_spiderman.imagem, font, "P1", 5, 5,makecol(0, 0, 0), -1);

    artefato.imagem=shield;

    combustivel.imagem=blocoRosa;
    textout_ex(combustivel.imagem, font, "GAS", 0, 5,makecol(0, 0, 0), -1);
    jogador_spiderman.artefatos=0;
}
void tela_inicial()
{   //initial screen

    key[KEY_ESC]=false;

    int loop_count=0;
    while(loop_count<250)
    {
        draw_sprite(buffer, spiderman_intro, 0, 0);
        textprintf_ex(buffer, fontCordia48, 50,250 ,makecol(glow.fontaux,0,0),-1,"Ajude o Spidey a pegar");
        textprintf_ex(buffer, fontCordia48, 80,300 ,makecol(glow.fontaux,0,0),-1,"o escudo do Captain");
        loop_count++;
        glow.glow();
        rest(10);
        blit(buffer,screen,0,0,0,0,20*tamBloco,20*tamBloco);
        if(key[KEY_ESC]) { freeAll(); deinit(); exit(0); }
    }
}
void desenhaBlocoRandomico(int i, int j)
{   //draws grayscale squares with random color

    BITMAP* temp;
    temp=create_bitmap(tamBloco,tamBloco);
    int aux=64+rand()%191;

    criaBloco(temp,aux,aux,aux);
    blit(temp,buffer,0,0,i*tamBloco,j*tamBloco,(i*tamBloco)+tamBloco,(j*tamBloco)+tamBloco);
}

void reinicia_posicoes()
{   //reinit mob positions

    combustivel.x=rand()%19;
    combustivel.y=rand()%19;
    artefato.x=rand()%19;
    artefato.y=rand()%19;
}
void confere_se_jogador_pegou_o_artefato()
{   // checks if player got the shield

    if ((jogador_spiderman.x==artefato.x)&&(jogador_spiderman.y==artefato.y))
    {
        jogador_spiderman.artefatos++;

        int loop_count=0;
        while(loop_count<50)
        {
            textprintf_ex(buffer, fontCordia48, 15,250 ,makecol(glow.fontaux,0,0), -1,"Pegou o escudo! contagem: %d ", jogador_spiderman.artefatos);
            loop_count++;
            glow.glow();
            rest(10);
            blit(buffer,screen,0,0,0,0,20*tamBloco,20*tamBloco);
        }

        artefato.x=rand()%19;
        artefato.y=rand()%19;
    }
}

void confere_se_jogador_pegou_o_combustivel()
{   //checks if player got the fuel/gas

    if ((jogador_spiderman.x==combustivel.x)&&(jogador_spiderman.y==combustivel.y))
    {
        int upgradeCombustivel=6+(rand()%5);
        jogador_spiderman.combustivel+=upgradeCombustivel;
        int loop_count=0;
        while(loop_count<50)
        {
            textprintf_ex(buffer, fontCordia48, 80,250 ,makecol(glow.fontaux,0,0), -1,"Pegou %d Combustivel", upgradeCombustivel);
            loop_count++;
            glow.glow();
            rest(10);
            blit(buffer,screen,0,0,0,0,20*tamBloco,20*tamBloco);
        }

        combustivel.x=rand()%19;
        combustivel.y=rand()%19;
    }
}

void confere_se_jogador_venceu()
{   //checks if player won

    key[KEY_ESC]=false;
    if (jogador_spiderman.artefatos==3)
    {
        int loop_count=0;
        while(loop_count<1000)
        {
            draw_sprite(buffer, spiderman_meme, 0, 0);
            textprintf_ex(buffer, fontCordia48, 15,300 ,makecol(glow.fontaux,0,0),-1,"VOCE VENCEU E MITOU!");
            textprintf_ex(buffer, fontCordia28, 20,480 ,makecol(0,glow.fontaux,0),-1,"https://www.facebook.com/groups/ProgDesafios/");
            textprintf_ex(buffer, fontCordia28, 20,540 ,makecol(0,glow.fontaux,0),-1,"https://www.youtube.com/user/tictacKode/playlists");
            loop_count++;
            glow.glow();
            rest(10);
            blit(buffer,screen,0,0,0,0,20*tamBloco,20*tamBloco);
            if(key[KEY_ESC]) { freeAll(); deinit(); exit(0); }
        }
        freeAll(); deinit(); exit(0);
    }
}

void paint()
{   //função que desenha o estado atual do jogo
    //draws the current game state

    int i, j;
    for(i=0; i<20; i++)
    {
        for(j=0; j<20; j++)
        {
            desenhaBlocoRandomico(i,j);
        }
    }

    blit(jogador_spiderman.imagem,buffer,0,0,jogador_spiderman.x*tamBloco,jogador_spiderman.y*tamBloco,(jogador_spiderman.x*tamBloco)+tamBloco,(jogador_spiderman.y*tamBloco)+tamBloco);
    blit(artefato.imagem,buffer,0,0,artefato.x*tamBloco,artefato.y*tamBloco,(artefato.x*tamBloco)+tamBloco,(artefato.y*tamBloco)+tamBloco);
    blit(combustivel.imagem,buffer,0,0,combustivel.x*tamBloco,combustivel.y*tamBloco,(combustivel.x*tamBloco)+tamBloco,(combustivel.y*tamBloco)+tamBloco);
    textprintf_ex(buffer, fontCordia48, 10,tamBloco ,makecol(0,glow.fontaux,0), -1,"Combustivel: %d ",jogador_spiderman.combustivel);
    textprintf_ex(buffer, fontCordia48, 10,tamBloco+50 ,makecol(0,glow.fontaux,0), -1,"Artefatos %d ",jogador_spiderman.artefatos);
    blit(buffer,screen,0,0,0,0,20*tamBloco,20*tamBloco);
}

void fim_de_jogo()
{   //Game over screen

    key[KEY_ESC]=false;

    int loop_count=0;
    while(loop_count<1000)
    {
        draw_sprite(buffer, spiderlost, 0, 0);
        textprintf_ex(buffer, fontCordia48, 180,150 ,makecol(glow.fontaux,0,0),-1,"Game Over!",jogador_spiderman.artefatos);
        textprintf_ex(buffer, fontCordia48, 50,200 ,makecol(0,glow.fontaux,0),-1,"Pegou %d vezes o escudo",jogador_spiderman.artefatos);
        textprintf_ex(buffer, fontCordia48, 180,250 ,makecol(0,glow.fontaux,0),-1,"Esc para sair");
        textprintf_ex(buffer, fontCordia28, 20,480 ,makecol(0,glow.fontaux,0),-1,"https://www.facebook.com/groups/ProgDesafios/");
        textprintf_ex(buffer, fontCordia28, 20,540 ,makecol(0,glow.fontaux,0),-1,"https://www.youtube.com/user/tictacKode/playlists");
        loop_count++;
        glow.glow();
        rest(10);
        blit(buffer,screen,0,0,0,0,20*tamBloco,20*tamBloco);
        if(key[KEY_ESC]) { freeAll(); deinit(); exit(0); }
    }
    freeAll(); deinit(); exit(0);
}

void controle()
{   // handles the keys that controls the application

    bool ativou=false;
    readkey();

    if (key[KEY_UP])    {   if(jogador_spiderman.y>0) {  jogador_spiderman.y-=1;  ativou=true;  }  else {  }     }

    if (key[KEY_DOWN])  {  if(jogador_spiderman.y<20) {  jogador_spiderman.y+=1;  ativou=true;  }  else {  }     }

    if (key[KEY_LEFT])  {  if(jogador_spiderman.x>0)  {  jogador_spiderman.x-=1;  ativou=true;  }  else {  }     }

    if (key[KEY_RIGHT]) {  if(jogador_spiderman.x<20) {  jogador_spiderman.x+=1;  ativou=true;  }  else {  }     }

    if (key[KEY_ESC])   {   freeAll(); deinit(); exit(0);     }

    //checks if player got the shield
    confere_se_jogador_pegou_o_artefato();

    //checks if player got the fuel/gas
    confere_se_jogador_pegou_o_combustivel();

    //checks if player got the shield 3 times
    confere_se_jogador_venceu();

    key[KEY_UP]=false;
    key[KEY_DOWN]=false;
    key[KEY_LEFT]=false;
    key[KEY_RIGHT]=false;
    key[KEY_ESC]=false;

    // testa se combustível acabou
    //checks if player is out of fuel
    if((ativou==true))
    {
        if(jogador_spiderman.combustivel>0)
        {
            jogador_spiderman.combustivel-=1;
        }
        else if (jogador_spiderman.combustivel<=0)
        {
            fim_de_jogo();
        }
    }
}
