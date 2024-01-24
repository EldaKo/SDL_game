#include <stdio.h> 
#include <SDL.h> 

// 화면 크기
#define WIDTH 800
#define HEIGHT 600

// 전역 변수
SDL_Window* window;
SDL_Renderer* renderer;

int main(int argc, char** argv)
{
	SDL_Event event;
	int quit = 0;
	SDL_Init(SDL_INIT_VIDEO);

	// 원칙적으로 반환된 값이 NULL인지를 검사하여야 한다. 이 코드에서는 생략하였다.
	window = SDL_CreateWindow("galaga", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, 0);
	renderer = SDL_CreateRenderer(window, -1, 0);

	while (!quit) {
		// 이벤트 처리
		while (SDL_PollEvent(&event)) {
			if (event.type == SDL_QUIT) {	// 윈도우의 x 표시를 누르면
				quit = 1;
			}
		}
		// 화면 지우기
		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);	// 검정색
		SDL_RenderClear(renderer);						// 지정된 색상으로 칠한다. 
		SDL_RenderPresent(renderer);
	}
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
	return 0;
}