#include "CommonFunc.h"
#include "LTexture.h"
#include "Enemy.h"
#include "BulletObject.h"
#include "Character.h"
#include "FoodObject.h"

//Font
TTF_Font* gFont = NULL;
//The music that will be played
Mix_Music *music = NULL;

//Entities
std::vector<Enemy> enemies;
Character player;
BulletObject bullet;
FoodObject food;


SDL_Renderer* renderer = NULL;
SDL_Window* window = NULL;

//Texture
LTexture background;
LTexture gameOver;
LTexture font1;
LTexture font2;

//Rect
SDL_Rect fontRect = { 0, 0 , TEXT_WIDTH, TEXT_HEIGHT };
SDL_Rect screenRect = { 0 , 0 , SCREEN_WIDTH , SCREEN_HEIGHT };
SDL_Rect enemyRect = { 0 , 0 , SCALE , SCALE };

bool running = true;
int points = 0;
bool game_over = false;
bool spawn = false;

void initSDL(void)
{
    int rendererFlags, windowFlags;

    rendererFlags = SDL_RENDERER_ACCELERATED;

    windowFlags = 0;

    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        printf("Couldn't initialize SDL: %s\n", SDL_GetError());
        exit(1);
    }

    window = SDL_CreateWindow("Snake_game", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, windowFlags);

    if (!window)
    {
        printf("Failed to open %d x %d window: %s\n", SCREEN_WIDTH, SCREEN_HEIGHT, SDL_GetError());
        exit(1);
    }

    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");

    renderer = SDL_CreateRenderer(window, -1, rendererFlags);

    if (!renderer)
    {
        printf("Failed to create renderer: %s\n", SDL_GetError());
        exit(1);
    }
    if (TTF_Init() == -1) {
        std::cout << "Could not initailize SDL2_ttf, error: " << TTF_GetError() << std::endl;
    }
    else
    {
        std::cout << "SDL2_ttf system ready to go!" << std::endl;
    }
    //Initialize SDL
    if( SDL_Init(SDL_INIT_AUDIO ) < 0 )
    {
        printf( "SDL could not initialize! SDL Error: %s\n", SDL_GetError() );
    }
    //Initialize SDL_mixer
    if( Mix_OpenAudio( 44100, MIX_DEFAULT_FORMAT, 2, 2048 ) < 0 )
    {
        printf( "SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError() );
    }
    //Initialize PNG loading
    int imgFlags = IMG_INIT_PNG;
    if (!(IMG_Init(imgFlags) & imgFlags))
    {
        printf("SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError());
    }

}
void loadMedia()
{
    //Load Textures
    background.loadTexture("img/Stars Small_1.png", renderer);
    gameOver.loadTexture("img/gameover.png", renderer);
    food.foodLoadTexture("img/cherry_20.png", renderer);
    player.charLoadTexture("img/ghost_20.png", renderer);
    bullet.bulletLoadTexture("img/bullet_red.png", renderer);

    //Load music
    music = Mix_LoadMUS( "sounds/MixueLovesYou.wav" );
    if( music == NULL )
    {
        printf( "Failed to load beat music! SDL_mixer Error: %s\n", Mix_GetError() );
    }
}
void close()
{
    background.close();
    food.close();
    gameOver.close();
    SDL_DestroyRenderer(renderer);
    renderer = NULL;

    SDL_DestroyWindow(window);
    window = NULL;

    Mix_FreeMusic(music);
    music = NULL;

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);

    SDL_Quit();
    IMG_Quit();
    TTF_Quit();

    TTF_CloseFont(gFont);
}

void enemySpawn()
{
    for (int i = 0; i < ENEMY_AMOUNT; i++)
    {
        Enemy p_enemy;
        int randLoc = rand() % 4;
        p_enemy.enemySpawn(randLoc);
        enemies.push_back(p_enemy);
    }
   for (auto& p_enemy : enemies)
    {
        p_enemy.enemyLoadTexture("img/ghost_21.png", renderer);
    }
}
void g_over()
{
   SDL_RenderClear(renderer);
   for (auto& p_enemy : enemies)
    {
       int randLoc = rand() % 4;
          p_enemy.enemySpawn(randLoc);
    }
    points = 0;
    player.returnSpawn();
    food.addFood();
    gameOver.render(0, 0, renderer, &screenRect);
}
int main(int argc, char* argv[])
{
    srand(time(0));
    initSDL();
    SDL_Event event;

    SDL_ShowCursor(false);
    gFont = TTF_OpenFont("font/minecraft.ttf", TEXT_RESOLUTION);

    loadMedia();

    food.addFood();

    while (running)
    {
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);

        SDL_RenderClear(renderer);

        SDL_Delay(5);

        SDL_Rect foodRect = food.foodRect();
        SDL_Rect playerRect = player.charRect();

        if (enemies.size() == 0)
        {
            enemySpawn();
        }
        while (SDL_PollEvent(&event) != 0)
        {
            if (event.type == SDL_QUIT)
            {
                SDL_Quit();
            }
            if (event.type == SDL_KEYDOWN)
            {
                switch(event.key.keysym.sym)
                {
                    case SDLK_TAB:
                    game_over = false;
                    break;
                    case SDLK_1:
                    //If there is no music playing
					if( Mix_PlayingMusic() == 0 )
                    {
						//Play the music
						Mix_PlayMusic( music, -1 );
					}
					//If music is being played
					else
					{
					//If the music is paused
                        if( Mix_PausedMusic() == 1 )
                        {
                            //Resume the music
                            Mix_ResumeMusic();
                        }
                        //If the music is playing
                        else
                        {
                        //Pause the music
                        Mix_PauseMusic();
                        }
                    }
                    break;

                    case SDLK_0:
                    //Stop the music
                    Mix_HaltMusic();
                    break;
				}
            }
            player.DoInput(event);

            bullet.Fire(event, player.charPosX(),player.charPosY());
        }

        bullet.bulletMove();

        player.DoPlayer(SPEED);

        background.render(0, 0, renderer, &screenRect);

        font1.loadFont("font/minecraft.ttf", gFont ,renderer,
                      (std::string("POINTS: ") + std::to_string(points)).c_str(), 10 , 10);

        for (auto& p_enemy : enemies)
        {
          p_enemy.enemyFollow(ENEMY_SPEED, player.charPosX(), player.charPosY());
        }

        bullet.bulletRender(renderer);

        player.charRender(renderer, &playerRect);

        for (auto& p_enemy : enemies)
        {
            p_enemy.enemyRender(renderer, &enemyRect);
        }

        if (food.foodCheckCollision(foodRect,playerRect))
        {
            food.addFood();
            points += 10;
        }

        food.foodRender(renderer,&foodRect);

        for (int i = 0; i < enemies.size(); )
        {
            if (enemies.at(i).CheckCollision(enemies.at(i).enemyRect(), player.charRect()))
            {
                gameOver.render(0, 0, renderer, &screenRect);
                game_over = true;
            }
            if (enemies.at(i).enemyHealthCheck(enemies.at(i).enemyRect(), bullet.bulletRect()))
            {
                enemies.erase(enemies.begin() + i);
                points++;
                continue;
            }
            i++;
        }

        bullet.bulletReload();

        if (game_over == true)
        {
            g_over();
        }
        SDL_RenderPresent(renderer);
    }
    close();
    return 0;
}
