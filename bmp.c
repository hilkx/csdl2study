#include<SDL.h>
#include<stdio.h>
#include<stdbool.h>

int count=0;


int main(int argc,char* atgv[])
{
	SDL_Init(SDL_INIT_EVERYTHING);
	SDL_Window *window=SDL_CreateWindow("demo",SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED,640,480,SDL_WINDOW_SHOWN);
	SDL_Renderer *render=SDL_CreateRenderer(window,-1,SDL_RENDERER_ACCELERATED);
	
	bool quit=false;
	SDL_Event event;
	SDL_Point point;
	
	SDL_SetRenderDrawColor(render,255,255,255,255);
	
	SDL_Surface *pTmpSurface = SDL_LoadBMP("D:\\me\\pic\\sdl_test.bmp");
	SDL_Texture *pTexture = SDL_CreateTextureFromSurface(render,pTmpSurface);
	SDL_FreeSurface(pTmpSurface);
	
	SDL_Rect src_point;
	SDL_Rect dst_point;
	SDL_QueryTexture(pTexture,NULL,NULL,&src_point.w,&src_point.h);
	dst_point.x=src_point.x=0;
	dst_point.y=src_point.y=0;
	
	dst_point.w=src_point.w;
	dst_point.h=src_point.h;
	
	while(!quit)
	{
		while(SDL_PollEvent(&event))
		{
			switch(event.type)
			{
				case SDL_QUIT:
					quit=true;
					break;
			}
			
		}
		//update
		long ticks=SDL_GetTicks();
		printf("tick:%ld,count:%d\r",ticks,count);
		
		if((ticks%1000)==0)
		{
			count++;
			dst_point.y = 20*(count%6);
		}
		
		//render
		SDL_RenderClear(render);
		SDL_RenderCopy(render,pTexture,&src_point,&dst_point);
		
		SDL_RenderPresent(render);
		SDL_Delay(1000/60);
		
	}
	
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(render);
	SDL_DestroyTexture(pTexture);
	
	SDL_Quit();
	return 0;
}