#pragma once

#include <SDL2/SDL.h>
#include <Rasterizer.h>
#include <functional>
#include <pixel.h>
#include <Timer.h>
#include <Model.h>
#include <Material.h>

class Renderer
{
	public:
		Renderer() : m_window(NULL), m_renderer(NULL), m_screen(NULL), m_depthBuffer(NULL), 
							m_timer(200) , m_frameBuffer(NULL), m_clearColor(0,0,0,255), m_shadowEnabled(false)
		{}

		~Renderer() {}
		bool Initialize(const char*title, int x, int y, int width, int height);
		void MainLoop();
		void CleanUp();
		
		// callbacks
		void SetRenderCallback(void(*renderCallback)(void)) { m_render = renderCallback; }
		void SetUpdateCallback(void(* updateCallback)(double)) { m_update = updateCallback; }
		void SetKeyboardCallback(void(*keyboardcallback)(SDL_Event*)) { m_keyboard = keyboardcallback; }
        void SetVertexDepthShader(Vertex3D(*vdepthShader)(const Vertex3D&)) { m_vertexDepthShader = vdepthShader;}
		//void SetResizeCallback(std::function<void(int, int)> resizeCallback) { m_resize = resizeCallback; }

		void SetPixel(int x, int y, ColorRGBA color)
		{
			if (x >= 0 && x < m_width && y >= 0 && y < m_height)
            {
            	Uint32* p = (Uint32*)m_screen->pixels;
            	p[y*m_width + x] = (0xFF << 24) | (color.R << 16) | (color.G << 8) | color.B;
           	}

		}

		// for rendering the models loaded, this renders the overall scene of the program
		void DrawModels(std::vector<Model>models, Vertex3D(*v)( const Vertex3D&), void(*s)(Point2D&));

        //for lightspace things 
        void DepthModels(std::vector<Model>models, Vertex3D(*v)(const Vertex3D&));

	private:
		void ClearDepthBuffer();
		void Clear(void)
		{
			for (int i = 0; i <= m_width; ++i)
			{
				for(int j=0; j<= m_height; ++j)
				{
					SetPixel(i, j, m_clearColor);
					m_depthBuffer[i*m_height+j] = 1.0f;
                    m_depthBufferShadow[i*m_height+j] = 1.0f;
				}
			}
		}

	public:
		Material *m_currentMaterial;
        Mat4 *m_currentModelMatrix;
		float* m_depthBuffer;
		float* m_depthBufferShadow;
		

	private:
		Timer m_timer;

		uint32_t* m_frameBuffer;
		int m_width, m_height;
		SDL_Window* m_window;
		SDL_Renderer* m_renderer;
		SDL_Surface* m_screen;
		ColorRGBA m_clearColor;
        bool m_shadowEnabled;
		
		std::function<void(double)> m_update;
		std::function<void()> m_render;
		std::function<void(SDL_Event*)> m_keyboard;
        std::function<Vertex3D(const Vertex3D&)> m_vertexDepthShader;
		//std::function<void(int,int)> m_resize;
		
};
