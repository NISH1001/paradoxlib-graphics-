#include <primitives.h>

void Primitives::ellipsePlot(SDL_Renderer *renderer, int cx, int cy, int x, int y, ColorRGBA color)
{
	setPixel(renderer, cx+x, cy+y, color);
	setPixel(renderer, cx-x, cy+y, color);
	setPixel(renderer, cx+x, cy-y, color);
	setPixel(renderer, cx-x, cy-y, color);
}

void Primitives::ellipseFill(SDL_Renderer *renderer, int cx, int cy, int rx, int ry, ColorRGBA color)
{
	int rx2 = rx * rx;
	int ry2 = ry * ry;
	int tworx2 = 2 * rx2;
	int twory2 = 2 * ry2;
	
	int x = 0;
	int y = ry;

	int p = ry2 - rx2*ry + rx2/4.f + 0.5f;
	
	ellipsePlot(renderer, cx, cy, x, y, color);
	
	while(x*ry2 < y*rx2)
	{
		x++;
		
		if(p<0)
			p += x*twory2 + ry2;
		
		else
		{
			y--;
			p += x*twory2 + ry2 - y*tworx2;
		}
		
		ellipsePlot(renderer, cx, cy , x, y, color);

        bresenham(renderer, cx+x, cy-y, cx-x, cy-y, color);
        bresenham(renderer, cx+x, cy+y, cx-x, cy+y, color);
	}

	p = ry2*(x+0.5)*(x+0.5) + rx2*(y-1)*(y-1) - rx2*ry2;
	
	while(y>=0)
	{
		y--;
		
		if(p<0)
		{
			x++;
			p += x*twory2-y*tworx2 + 3*rx2;
		}
		
		else
			p += 3*rx2-y*tworx2;
		
		ellipsePlot(renderer, cx, cy , x, y, color);
        
        bresenham(renderer, cx+x, cy-y, cx-x, cy-y, color);
        bresenham(renderer, cx+x, cy+y, cx-x, cy+y, color);
	}
}

void Primitives::ellipse(SDL_Renderer *renderer, int cx, int cy, int rx, int ry, ColorRGBA color)
{
	int rx2 = rx * rx;
	int ry2 = ry * ry;
	int tworx2 = 2 * rx2;
	int twory2 = 2 * ry2;
	
	int x = 0;
	int y = ry;

	int p = ry2 - rx2*ry + rx2/4.f + 0.5f;
	
	ellipsePlot(renderer, cx, cy, x, y, color);
	
	while(x*ry2 < y*rx2)
	{
		x++;
		
		if(p<0)
			p += x*twory2 + ry2;
		
		else
		{
			y--;
			p += x*twory2 + ry2 - y*tworx2;
		}
		
		ellipsePlot(renderer, cx, cy , x, y, color);
	}

	p = ry2*(x+0.5)*(x+0.5) + rx2*(y-1)*(y-1) - rx2*ry2;
	
	while(y>=0)
	{
		y--;
		
		if(p<0)
		{
			x++;
			p += x*twory2-y*tworx2 + 3*rx2;
		}
		
		else
			p += 3*rx2-y*tworx2;
		
		ellipsePlot(renderer, cx, cy , x, y, color);
	}
}

void Primitives::bresenham(SDL_Renderer *renderer, int xstart, int ystart, int xend, int yend, ColorRGBA color)
{
	int dx = abs(xend - xstart);
	int dy = abs(yend - ystart);
	
	int xinc = (xend>xstart ? 1 : -1);
	int yinc = (yend>ystart ? 1 : -1);	
	
	int twodx = 2*dx;
	int twody = 2*dy;
	int twodydx = twody - twodx;
	int x = xstart;
	int y = ystart;	
		
	setPixel(renderer, xstart, ystart, color);
	
	if(dx > dy)
	{
		int p = twody - dx;
		
		while(x != xend)
		{
			x += xinc;
		
			if(p<0)
			{
				p += twody;	
			}
			else
			{	
				y += yinc;
				p += twodydx;
			}
			setPixel(renderer, x , y, color);
		}
	}
	
	else
	{
		int p = twodx - dy;
		
		while(y != yend)
		{
			y += yinc;
			if(p <0)
				p += twodx;
			else
			{
				x += xinc;
				p -= twodydx;
			}
			setPixel(renderer, x, y, color);
		}

	}
}


void Primitives::circlePlot(SDL_Renderer *renderer, int cx, int cy, int x, int y, ColorRGBA color)
{
    setPixel(renderer, cx+x, cy+y, color);
    
    setPixel(renderer, cx-x, cy+y, color);

    setPixel(renderer, cx+x, cy-y, color);
    
    setPixel(renderer, cx-x, cy-y, color);

    setPixel(renderer, cx+y, cy+x, color);

    setPixel(renderer, cx-y, cy+x, color);

    setPixel(renderer, cx+y, cy-x, color);

    setPixel(renderer, cx-y, cy-x, color);
}

void Primitives::circleFill(SDL_Renderer *renderer, int cx, int cy, int r, ColorRGBA color)

{
    int x = 0;
    int y = r;
    int p = 1-r;;

    circlePlot(renderer, cx, cy, x, y, color);
    bresenham(renderer, cx+x, cy+y, cx+x,cy-y, color);

    while(x <= y)
    {
        x++;

        if(p<0)
            p += 2*x+1;

        else
        {
            y--;
            p += 2*(x-y)+1;
        }

        circlePlot(renderer, cx, cy, x, y, color);

        bresenham(renderer, cx+x, cy+y, cx+x, cy-y, color);
        bresenham(renderer, cx+y, cy+x, cx+y, cy-x, color);
        bresenham(renderer, cx-x, cy+y, cx-x, cy-y, color);
        bresenham(renderer, cx-y, cy+x, cx-y, cy-x, color);
    }
}

void Primitives::circle(SDL_Renderer *renderer, int cx, int cy, int r, ColorRGBA color)
{
    int x = 0;
    int y = r;
    int p = 1-r;
    
    circlePlot(renderer, cx, cy, x, y, color);
    
    while(x<=y)
    {
        x++;
        
        if(p<0)
            p += 2*x+1;

        else
        {
            y--;
            p += 2*(x-y)+1; 
        }   
        
        circlePlot(renderer, cx, cy, x, y, color);
    }       
}

