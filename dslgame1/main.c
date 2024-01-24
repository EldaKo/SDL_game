#include <stdio.h> 
#include <SDL.h> 

// ȭ�� ũ��
#define WIDTH 800
#define HEIGHT 600

// ���� ����
SDL_Window* window;
SDL_Renderer* renderer;

int main(int argc, char** argv)
{
	SDL_Event event;
	int quit = 0;
	SDL_Init(SDL_INIT_VIDEO);

	// ��Ģ������ ��ȯ�� ���� NULL������ �˻��Ͽ��� �Ѵ�. �� �ڵ忡���� �����Ͽ���.
	window = SDL_CreateWindow("galaga", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, 0);
	renderer = SDL_CreateRenderer(window, -1, 0);

	while (!quit) {
		// �̺�Ʈ ó��
		while (SDL_PollEvent(&event)) {
			if (event.type == SDL_QUIT) {	// �������� x ǥ�ø� ������
				quit = 1;
			}
		}
		// ȭ�� �����
		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);	// ������
		SDL_RenderClear(renderer);						// ������ �������� ĥ�Ѵ�. 
		SDL_RenderPresent(renderer);
	}
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
	return 0;
}