#include <stdio.h> 
#include <SDL.h> 

// 화면 크기
#define WIDTH 800
#define HEIGHT 600

// 전역 변수
SDL_Window* window;
SDL_Renderer* renderer;

struct Spaceship {
        SDL_Rect rect;
        int dx, dy;
        int health;
        SDL_Texture* texture;
} spaceship = { {WIDTH / 2, HEIGHT - 60, 100, 100}, 0, 0, 0 , NULL };

struct Alien {
        SDL_Rect rect;
        int dx, dy;
        int health;
        SDL_Texture* texture;
} alien = { {0, 0, 100, 100}, 1, 1, 0 , NULL };

struct Missile {
        SDL_Rect rect;
        int dx, dy;
        int show;
        SDL_Texture* texture;
} missile = { {WIDTH / 2, HEIGHT - 60, 60, 60}, 1, 10, 0 , NULL };

int checkCollision(SDL_Rect rect1, SDL_Rect rect2) {
        // 두 개의 바운딩 박스가 서로 겹치는지 확인

        if (rect1.x + rect1.w >= rect2.x &&
                rect2.x + rect2.w >= rect1.x &&
                rect1.y + rect1.h >= rect2.y &&
                rect2.y + rect2.h >= rect1.y) {
                // 충돌 발생
                return 1;
        }
        // 충돌하지 않음
        return 0;
}

int main(int argc, char** argv)
{
        SDL_Event event;
        int quit = 0;
        SDL_Init(SDL_INIT_VIDEO);

        // 원칙적으로 반환된 값이 NULL인지를 검사하여야 한다. 이 코드에서는 생략하였다.
        window = SDL_CreateWindow("galaga", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, 0);
        renderer = SDL_CreateRenderer(window, -1, 0);

        SDL_Surface* bmp = SDL_LoadBMP("spaceship.bmp");
        spaceship.texture = SDL_CreateTextureFromSurface(renderer, bmp);
        SDL_FreeSurface(bmp);

        bmp = SDL_LoadBMP("alien.bmp");
        alien.texture = SDL_CreateTextureFromSurface(renderer, bmp);
        SDL_FreeSurface(bmp);

        bmp = SDL_LoadBMP("missile.bmp");
        missile.texture = SDL_CreateTextureFromSurface(renderer, bmp);
        SDL_FreeSurface(bmp);

        while (!quit) {
                // 이벤트 처리
                while (SDL_PollEvent(&event)) {
                        if (event.type == SDL_QUIT) {
                                quit = 1;
                        }
                        else if (event.type == SDL_KEYDOWN) {
                                if (event.key.keysym.sym == SDLK_RIGHT)
                                        spaceship.rect.x += 10;
                                if (event.key.keysym.sym == SDLK_LEFT)
                                        spaceship.rect.x -= 10;
                                if (event.key.keysym.sym == SDLK_SPACE) {
                                        missile.show = 1;
                                        missile.rect.x = spaceship.rect.x;
                                        missile.rect.y = spaceship.rect.y;
                                }
                        }
                }

                int collision = checkCollision(alien.rect, missile.rect);
                if (collision) {
                        missile.show = 0;

                        missile.rect.y = spaceship.rect.y;
                        alien.rect.x = alien.rect.y = 0;
                        alien.dx = alien.dy = 1;
                }
                alien.rect.x += alien.dx;
                if (alien.rect.x <= 0 || alien.rect.x > WIDTH) {
                        alien.dx *= -1;
                        alien.rect.y += 10;
                }
                if (missile.show == 1) {
                        missile.rect.y -= missile.dy;
                        if (missile.rect.y < 0)
                                missile.show = 0;
                }

                // 화면 지우기
                SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
                SDL_RenderClear(renderer);

                SDL_RenderCopy(renderer, spaceship.texture, NULL, &(spaceship.rect));
                SDL_RenderCopy(renderer, alien.texture, NULL, &(alien.rect));
                if (missile.show == 1) {
                        SDL_RenderCopy(renderer, missile.texture, NULL, &(missile.rect));
                }

                SDL_Delay(10);
                SDL_RenderPresent(renderer);
        }
        SDL_DestroyRenderer(renderer); //렌더러 파괴
        SDL_DestroyWindow(window); //윈도우 파괴
        SDL_Quit(); //SDL 종료
        return 0;
}