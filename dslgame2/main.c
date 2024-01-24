#include <stdio.h> 
#include <SDL.h> 

// ȭ�� ũ��
#define WIDTH 800
#define HEIGHT 600

// ���� ����
SDL_Window* window;
SDL_Renderer* renderer;

struct Spaceship {
	SDL_Rect rect;
	int dx, dy;
	int health;

		SDL_Texture* texture;
} spaceship = { {WIDTH / 2, HEIGHT - 60, 100, 100}, 0, 0, 0 , NULL };

int main(int argc, char** argv)
{
	SDL_Event event;
	int quit = 0;
	SDL_Init(SDL_INIT_VIDEO);

	// ��Ģ������ ��ȯ�� ���� NULL������ �˻��Ͽ��� �Ѵ�. �� �ڵ忡���� �����Ͽ���.
	window = SDL_CreateWindow("galaga", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, 0);
	renderer = SDL_CreateRenderer(window, -1, 0);


		SDL_Surface* bmp = SDL_LoadBMP("spaceship.bmp");
	spaceship.texture = SDL_CreateTextureFromSurface(renderer, bmp);
	SDL_FreeSurface(bmp);

	while (!quit) {
		// �̺�Ʈ ó��
		while (SDL_PollEvent(&event)) {
			if (event.type == SDL_QUIT) {
				quit = 1;
			}
			else if (event.type == SDL_KEYDOWN) {

					if (event.key.keysym.sym == SDLK_RIGHT)
						spaceship.rect.x += 10;
				if (event.key.keysym.sym == SDLK_LEFT)
					spaceship.rect.x -= 10;
			}
		}
		// ȭ�� �����
		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
		SDL_RenderClear(renderer);

		SDL_RenderCopy(renderer, spaceship.texture, NULL, &(spaceship.rect));

			SDL_Delay(10);
		SDL_RenderPresent(renderer);
	}
	SDL_DestroyRenderer(renderer); //������ �ı�
	SDL_DestroyWindow(window); //������ �ı�
	SDL_Quit(); //SDL ����
	return 0;
}