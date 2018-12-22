
#include <allegro.h>
#include <time.h>
#include "Glow.h"
#include "functions.h"

int main()
{
    //initializations
    init();
    loadAll();
    initGame();
    tela_inicial();

    //game loop
    while(!key[KEY_ESC])
    {
        glow.glow();
        paint();
        controle();
        clear(buffer);
    }

    freeAll();
    deinit();
    return 0;
}
END_OF_MAIN();
