#include <SDL.h>
#include <numeric>
#include <complex>
#undef main

int is_in_set(std::complex<double> c)
{
	std::complex <double> z(0, 0);
	for (int i = 0; i < 25; i++)
	{
		z = std::pow(z, 2) + c;	// (z**2 + c) to find point in part of mandelbrot set
		if (std::norm(z) > 10)
		{
			return i;
		}
	}
	return 0;
}

int main() {

	SDL_Init(SDL_INIT_EVERYTHING);
	SDL_Window* window = nullptr;
	SDL_Renderer* renderer = nullptr;
	SDL_CreateWindowAndRenderer(800, 600, 0, &window, &renderer);
	//SDL_RenderSetScale(renderer,2,2);

	for (double x = 0.0; x < 1.0; x += 0.001)
		for (double y = 0.0; y < 1.0; y += 0.001)
		{
			// Don't care about these numbers :-|
			double point_x = std::lerp(-2.69, 4.20, x);
			double point_y = std::lerp(-2.69, 4.20, y);
			int iters = is_in_set(std::complex<double>(point_x,point_y));
			if (iters == 0) 
			{
				SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
				SDL_RenderDrawPointF(renderer, x * 800, y * 800);
			}
			else
			{
				SDL_SetRenderDrawColor(
					renderer,
					3 * iters % 255,
					3 * iters % 255,
					12 * iters % 255,
					255);
				SDL_RenderDrawPointF(renderer, x * 800, y * 800);
			}
		}
	SDL_RenderPresent(renderer);
	SDL_Delay(4000);
	return 0;
}