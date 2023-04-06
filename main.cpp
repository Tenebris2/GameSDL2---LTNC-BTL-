
#include "CommonFunc.h"
#include "LTexture.h"
#include "Enemy.h"
#include "BulletObject.h"
#include "Character.h"
TTF_Font* gFont = NULL;
std::vector<Enemy> enemies;
Character snake_test;
BulletObject bullet;
SDL_Renderer* renderer = NULL;
SDL_Window* window = NULL;
LTexture background1;
LTexture background2;
LTexture gameOver;
LTexture food;
LTexture font;
LTexture Mouse;
SDL_Rect mouseRect{ SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 - SCALE, 16 , 16 };
SDL_Rect fontRect = { 0,0,TEXT_WIDTH, TEXT_HEIGHT };
SDL_Rect screenRect = { 0,0, SCREEN_WIDTH, SCREEN_HEIGHT };
SDL_Rect snake = snake_test.charRect();
SDL_Rect enemyRect = { 0,0,SCALE, SCALE };
SDL_Rect fruit = { 0,0, SCALE, SCALE };
bool running = true;
int points = 0;
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
    //Initialize PNG loading
    int imgFlags = IMG_INIT_PNG;
    if (!(IMG_Init(imgFlags) & imgFlags))
    {
        printf("SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError());
    }
}
void loadMedia()
{
    background1.loadTexture("img/Nebula Red.png", renderer);
    background2.loadTexture("img/Stars Small_1.png", renderer);
    gameOver.loadTexture("img/gameover.png", renderer);
    food.loadTexture("img/cherry_20.png", renderer);
    //font.loadFont("font/minecraft.ttf", gFont, renderer, (std::string("POINTS: ") + std::to_string(points)).c_str(), 10, 10);
    snake_test.charLoadTexture("img/ghost_20.png", renderer);
    Mouse.loadTexture("cursor/Crosshair04.png", renderer);
    bullet.bulletLoadTexture("img/bullet.png", renderer);
}
void mouseUpdate()
{
    int x, y;
    SDL_GetMouseState(&x, &y);

    mouseRect.x = x;
    mouseRect.y = y;
}
void close()
{
    SDL_DestroyRenderer(renderer);
    renderer = NULL;

    SDL_DestroyWindow(window);
    window = NULL;
    SDL_Quit();
    IMG_Quit();
    TTF_Quit();
    TTF_CloseFont(gFont);
}
void prepareScene(void)
{
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
    SDL_RenderClear(renderer);
}
void presentScene(void)
{
    SDL_RenderPresent(renderer);
}
void renderFood(int x, int y)
{
    food.render(x, y, renderer,&fruit);
}
std::pair<int, int> addFood()
{
    int x = 0;
    int y = 0;
    x = rand() % cols * SCALE;
    y = rand() % rows * SCALE;
    std::pair<int, int> foodLoc;
    foodLoc = std::make_pair(x, y);
    return foodLoc;
}
bool advancedCollisionDetection(SDL_Rect a,SDL_Rect b)
{
    //The sides of the rectangles
    int leftA, leftB;
    int rightA, rightB;
    int topA, topB;
    int bottomA, bottomB;

    //Calculate the sides of rect A
    leftA = a.x;
    rightA = a.x + a.w;
    topA = a.y;
    bottomA = a.y + a.h;

    //Calculate the sides of rect B
    leftB = b.x;
    rightB = b.x + b.w;
    topB = b.y;
    bottomB = b.y + b.h;

    //If any of the sides from A are outside of B
    if (bottomA <= topB)
    {
        return false;
    }

    if (topA >= bottomB)
    {
        return false;
    }

    if (rightA <= leftB)
    {
        return false;
    }

    if (leftA >= rightB)
    {
        return false;
    }

    //If none of the sides from A are outside B
    return true;
}
int main(int argc, char* argv[])
{
    initSDL();
    SDL_Event event;
    SDL_ShowCursor(false);
    gFont = TTF_OpenFont("font/minecraft.ttf", TEXT_RESOLUTION);
    int foodRand = rand() % 3;
    std::pair<int, int> foodLoc = addFood();
    fruit.x = foodLoc.first;
    fruit.y = foodLoc.second;
    int deaths = 0;
    bool game_over = false;
    bool play_again = true;
    loadMedia();
        for (int i = 0; i < ENEMY_AMOUNT; i++) {
            Enemy p_enemy;
            p_enemy.Spawn();
            enemies.push_back(p_enemy);
        }
        for (auto& p_enemy : enemies)
        {
            p_enemy.enemyLoadTexture("img/ghost_21.png", renderer);
        }
    while (play_again)
    {
        prepareScene();
        SDL_Delay(5);
        while (SDL_PollEvent(&event) != 0)
        {
            if (event.type == SDL_QUIT)
            {
                SDL_Quit();
            }
            if (event.type == SDL_KEYDOWN)
            {
                if (event.key.keysym.sym == SDLK_TAB)
                {
                    game_over = false;
                }
            }
            snake_test.DoInput(event);
            bullet.Fire(event, snake_test.charPosX(),snake_test.charPosY());
        }
        bullet.bulletMove();

        snake_test.DoPlayer(SPEED);

        background1.render(0, 0, renderer, &screenRect);

        background2.render(0, 0, renderer, &screenRect);

        mouseUpdate();

        for (auto& p_enemy : enemies)
        {
          p_enemy.enemyFollow(ENEMY_SPEED, snake_test.charPosX(), snake_test.charPosY());
        }

        bullet.bulletRender(renderer);

        snake_test.charRender(renderer, &snake);
        for (auto& p_enemy : enemies)
        {
            p_enemy.enemyRender(renderer, &enemyRect);
        }

        Mouse.render(mouseRect.x, mouseRect.y,renderer,&mouseRect);

        if (advancedCollisionDetection(fruit, snake_test.charRect()))
        {
            foodLoc = addFood();
            fruit.x = foodLoc.first;
            fruit.y = foodLoc.second;
            points += 10;
        }
        renderFood(fruit.x, fruit.y);
        for (auto& p_enemy : enemies)
        {
            if (p_enemy.CheckCollision(p_enemy.enemyRect(), snake_test.charRect()))
            {
                gameOver.render(0, 0, renderer, &screenRect);
                game_over = true;
            }
            if (p_enemy.CheckCollision(p_enemy.enemyRect(), bullet.bulletRect()))
            {
                int randLoc = rand() % 4;
                p_enemy.enemyHealthCheck(p_enemy.enemyRect(), bullet.bulletRect(), randLoc);
            }
            bullet.bulletCheckCollision(p_enemy.enemyRect(), bullet.bulletRect());
        }
        if (game_over == true)
        {
            SDL_RenderClear(renderer);
            enemies.clear();
            gameOver.render(0, 0, renderer, &screenRect);
        }
        presentScene();
    }
    close();
    return 0;
}
