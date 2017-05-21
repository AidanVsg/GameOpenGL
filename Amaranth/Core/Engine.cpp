#include <windows.h>		
#include <iostream>
#include "../glew/include/GL/glew.h"			
#include "../View/Headers/Renderer.h"
#include "../Object/Headers/NPC.h"
#include "../Object/Headers/Player.h"
//#include "../Object/Headers/World.h" //Deprecated. Using a Spatial Grid to collect world objects now.
#include "../View/Headers/Texture.h"
#include "tgaload.h"
#include "SpatialHash.h"
#include <fstream>
#include <string>
#include <sstream>

#include "../glm/glm/glm.hpp"
#include "../glm/glm/gtc/matrix_transform.hpp"
#include "../glm/glm/gtc/type_ptr.hpp"
float worldWidth = 2500;
float worldHeight = 2500;
float jumpHeight = 70.0f;
float pVelocityY = 18.0f;

GLuint currentWidth = 1024, currentHeight = 768; //Current resolution
GLuint targetWidth = 1024, targetHeight = 1024; //Target resolution
GLfloat AR = ((float)targetWidth / targetHeight);
double timerFrequencyRecip = 0.000003;
float deltaT; //Delta time between each update cycle
__int64 prevTime;
glm::vec2 startingCoord;
glm::vec2 pSize(25.0f, 25.0f);

Texture t;
GLuint plChar;

//Player* player = new Player(glm::vec2(0.0f, 80.0f), pSize, glm::vec2(15.0f, pVelocityY), plChar , jumpHeight);
Player* player = new Player();
Renderer renderer(AR);
//World world; //Deprecated. Using a Spatial Grid to collect world objects now.
SpatialHash grid(worldWidth, worldHeight, 200);

enum GameState
{
	MENU,
	ACTIVE,
	SETUP,
};

GameState stateOfThisGame;

void loadTextures();
void checkGameState();
void generateMapFile();
void setCollisionFlags(int things[99][99], Entity* e, int i, int j);
double timeSimulation(); //Simulates the delta of time for each update cycle
void doCollisions();
void processKeys_external();
void update(); //Game update cycle to process objects on screen, keyboard, resolve collision, check jumping
void render(int width, int height); //Renders the objects on screen
void populateWorld(); //Function to populate the game world, adding objects to grid
std::vector<Entity*> collected;
std::pair<Renderer::X, Renderer::Y> cam;
LRESULT	CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);	// Declaration For WndProc
void KillGLWindow();									// releases and destroys the window
bool CreateGLWindow(char* title, int width, int height); //creates the window
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int);  // Win32 main function

													   //win32 global variabless
HDC			hDC = NULL;		// Private GDI Device Context
HGLRC		hRC = NULL;		// Permanent Rendering Context
HWND		hWnd = NULL;		// Holds Our Window Handle
HINSTANCE	hInstance;		// Holds The Instance Of The Application

void checkGameState()
{
	if (stateOfThisGame == GameState::SETUP)
	{
		player = new Player(glm::vec2(0.0f, 80.0f), pSize, glm::vec2(15.0f, pVelocityY), plChar, jumpHeight); 
		std::cout << "Player created." << std::endl;

		player->SetTextures(t);
		std::cout << "Player texture list set." << std::endl;
		
		std::cout << "Populating world." << std::endl; 
		populateWorld();

		stateOfThisGame == GameState::ACTIVE;
	}	
	else if (stateOfThisGame == GameState::ACTIVE)
	{
		update();
	}
	else
	{
		renderer.screen_height = currentHeight; renderer.screen_width = currentWidth; renderer.virtual_height = targetHeight; renderer.virtual_width = targetWidth;

		Entity *start = new Entity(glm::vec2(25.0f, 25.0f), glm::vec2(25.0f, 25.0f), glm::vec2(0.00f, 0.0f), t.textures["start"]);
		Entity *exit = new Entity(glm::vec2(25.0f, 60.0f), glm::vec2(25.0f, 25.0f), glm::vec2(0.00f, 0.0f), t.textures["start"]);

		std::vector<Entity*> buttons;
		buttons.push_back(start);
		buttons.push_back(exit);
		renderer.displayMenu(buttons);

		delete(start);
		delete(exit);
	}
}

void update()
{		
	collected = grid.collect(cam.first.first, cam.first.second, cam.second.first, cam.second.second);

	processKeys_external();
	player->processKeys();											//Process keyboard
	doCollisions();													//Collision detection
	player->checkJumpState(timeSimulation());						//Check if player is jumping/falling/on-ground

	renderer.screen_height = currentHeight; renderer.screen_width = currentWidth; renderer.virtual_height = targetHeight; renderer.virtual_width = targetWidth;
	cam = renderer.reshape(currentWidth, currentHeight, player);	//Sets Perspective GL Screen in respect to player coordinates
	renderer.display(player, collected);							// Draw the scene
	if (player->GetCoordinate().x < -100 || player->GetCoordinate().y < -100)
	{
		delete(player);
		player = new Player(startingCoord, pSize, glm::vec2(15.0f, pVelocityY), plChar, jumpHeight);
		player->SetTextures(t);
		std::cout << "Player reset." << std::endl;
	}
}

void loadTextures()
{
	std::cout << "Loading textures." << std::endl;

	t.textures["pChar"] = tgaLoadAndBind("player.tga", TGA_ALPHA); plChar = tgaLoadAndBind("player.tga", TGA_ALPHA);
	t.textures["pCharL"] = tgaLoadAndBind("player_left.tga", TGA_ALPHA);
	t.textures["pCharLU"] = tgaLoadAndBind("player_leftUp.tga", TGA_ALPHA);
	t.textures["pCharLD"] = tgaLoadAndBind("player_leftDown.tga", TGA_ALPHA);
	t.textures["pCharR"] = tgaLoadAndBind("player_right.tga", TGA_ALPHA);
	t.textures["pCharRU"] = tgaLoadAndBind("player_rightUp.tga", TGA_ALPHA);
	t.textures["pCharRD"] = tgaLoadAndBind("player_rightDown.tga", TGA_ALPHA);
	t.textures["pCharU"] = tgaLoadAndBind("player_up.tga", TGA_ALPHA);
	t.textures["pCharD"] = tgaLoadAndBind("player_down.tga", TGA_ALPHA);
	t.textures["grass"] = tgaLoadAndBind("grass.tga", TGA_ALPHA);
	t.textures["dirt"] = tgaLoadAndBind("dirt.tga", TGA_ALPHA);
	t.textures["start"] = tgaLoadAndBind("start.tga", TGA_ALPHA);

	std::cout << "Textures loaded." << std::endl;
	
	renderer.SetTextureList(t);
}

void processKeys_external()
{
	if (player->keys[0x52])
	{
		player = new Player(startingCoord, pSize, glm::vec2(15.0f, pVelocityY), plChar, jumpHeight);
		player->SetTextures(t);
	}
}

void render(int width, int height)
{
	cam = renderer.reshape(width, height, player);	// Set Up Our Perspective GL Screen
	renderer.init();
}

void setCollisionFlags(int things[99][99], Entity* e, int i, int j )
{
	if (things[i + 1][j] == 1 || things[i + 1][j] == 2)
		e->SetN_up(true);
	if (things[i - 1][j] == 1 || things[i - 1][j] == 2)
		e->SetN_down(true);
	if (things[i][j + 1] == 1 || things[i][j + 1] == 2)
		e->SetN_right(true);
	if (things[i][j - 1] == 1 || things[i][j - 1] == 2)
		e->SetN_left(true);
}

void doCollisions()
{	
	player->resetCollisions(); //Each update cycle resets collision to none

	for(Entity* e : collected) //For each entity on screen
	{
		if (player->checkCollision(e)) //AABB collision detection
		{
			player->collisionSide(e); //Check for the side of collision 
		}
	}
}

void generateMapFile()
{
	using namespace std;
	ofstream out;

	out.open("level_template.amap", fstream::out);

	for (int i = 0; i <= worldHeight/25; i++)
	{
		for (int j = 0; j <= worldWidth/25; j++)
		{
			out << "0 ";
		}
		out << endl;
	}
}

void populateWorld()
{
	int row = 0, col = 0;
	int tileCode;
	std::string line;
	char* levelName = "level1.amap";
	std::cout << "Loading " << levelName << "." << std::endl;
	std::ifstream fstream(levelName);
	std::vector<std::vector<GLuint>> tileData;

	int things[99][99];
	if (fstream)
	{
		while (std::getline(fstream, line)) // Read each line from level
		{
			col = 0;
			std::istringstream sstream(line);
			while (sstream >> tileCode) 
			{
				if (tileCode == 1 || tileCode == 2 || tileCode == 5)
				{
					things[100-row][col] = tileCode;
				}
				col++;
			}
		row++;
		}
	}

	for (int i = 0; i < 99; i++)
	{
		for (int j = 0; j < 99; j++)
		{
			if (things[i][j] == 1)
			{
				Entity *e = new Entity(glm::vec2(j*25.0f, i*25.0f), glm::vec2(25.0f, 25.0f), glm::vec2(0.08f, 0.033f), t.textures["dirt"]);
				setCollisionFlags(things, e, i, j);
				grid.add(e);
			}
			if (things[i][j] == 2)
			{
				Entity *e = new Entity(glm::vec2(j*25.0f, i*25.0f), glm::vec2(25.0f, 25.0f), glm::vec2(0.08f, 0.033f), t.textures["grass"]);
				setCollisionFlags(things, e, i, j);
				grid.add(e);
			}
			if (things[i][j] == 5)
			{
				player->SetCoordinate(glm::vec2(j*25.0f, i*25.0f));
				startingCoord = glm::vec2(j*25.0f, i*25.0f);
				std::cout << "Starting player coordinate set." << std::endl;
			}
				
		}
	}
}

double timeSimulation()
{
	// Get the current time
	LARGE_INTEGER t;
	QueryPerformanceCounter(&t);
	__int64 currentTime = t.QuadPart;

	__int64 ticksElapsed = currentTime - prevTime;					// Ticks elapsed since the previous time step
	double deltaT = double(ticksElapsed) * timerFrequencyRecip;		// Convert to second
																	//cout << ticksElapsed << " " << deltaT << endl;
	
	// Advance timer
	prevTime = currentTime;					// use the current time as the previous time in the next step
	return deltaT;
}
							/******************* WIN32 FUNCTIONS ***************************/
int WINAPI WinMain(HINSTANCE	hInstance,			// Instance
	HINSTANCE	hPrevInstance,		// Previous Instance
	LPSTR		lpCmdLine,			// Command Line Parameters
	int			nCmdShow)			// Window Show State
{
	MSG		msg;									// Windows Message Structure
	bool	done = false;								// Bool Variable To Exit Loop


	AllocConsole();
	FILE *stream;
	freopen_s(&stream, "CONOUT$", "w", stdout);

	// Create Our OpenGL Window
	if (!CreateGLWindow("OpenGL Win32 Example", currentWidth, currentHeight))
	{
		return 0;									// Quit If Window Was Not Created
	}

	prevTime = 0;

	while (!done)									// Loop That Runs While done=FALSE
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))	// Is There A Message Waiting?
		{
			if (msg.message == WM_QUIT)				// Have We Received A Quit Message?
			{
				done = true;							// If So done=TRUE
			}
			else									// If Not, Deal With Window Messages
			{
				TranslateMessage(&msg);				// Translate The Message
				DispatchMessage(&msg);				// Dispatch The Message
			}
		}
		else										// If There Are No Messages
		{
				if (player->keys[VK_ESCAPE]) done = true;

				checkGameState();
				SwapBuffers(hDC);							// Swap Buffers (Double Buffering)
			
		}
	}

	// Shutdown
	KillGLWindow();									// Kill The Window
	return (int)(msg.wParam);						// Exit The Program
}

//WIN32 Processes function - useful for responding to user inputs or other events.
LRESULT CALLBACK WndProc(HWND	hWnd,			// Handle For This Window
	UINT	uMsg,								// Message For This Window
	WPARAM	wParam,								// Additional Message Information
	LPARAM	lParam)								// Additional Message Information
{
	switch (uMsg)								// Check For Windows Messages
	{
	case WM_CLOSE:								// Did We Receive A Close Message?
	{
		PostQuitMessage(404);						// Send A Quit Message
		return 0;								// Jump Back
	}
	break;

	case WM_SIZE:								// Resize The OpenGL Window
	{
		renderer.reshape(LOWORD(lParam), HIWORD(lParam), player);  // LoWord=Width, HiWord=Height
		currentWidth = LOWORD(lParam);
	    currentHeight = HIWORD(lParam);
		
		return 0;								// Jump Back
	}
	break;

	case WM_LBUTTONDOWN:
	{
		//mouse_x = LOWORD(lParam);
		//mouse_y = screenHeight - HIWORD(lParam);
		//LeftPressed = true;
	}
	break;

	case WM_LBUTTONUP:
	{
		//LeftPressed = false;
	}
	break;

	case WM_MOUSEMOVE:
	{
		/*mouse_x = LOWORD(lParam);
		mouse_y = screenHeight - HIWORD(lParam);*/
	}
	break;
	case WM_KEYDOWN:							// Is A Key Being Held Down?
	{
		player->keys[wParam] = true;					// If So, Mark It As TRUE
		return 0;								// Jump Back
	}
	break;
	case WM_KEYUP:								// Has A Key Been Released?
	{
		player->keys[wParam] = false;					// If So, Mark It As FALSE
		return 0;								// Jump Back
	}
	break;
	}

	// Pass All Unhandled Messages To DefWindowProc
	return DefWindowProc(hWnd, uMsg, wParam, lParam);
}

void KillGLWindow()								// Properly Kill The Window
{
	if (hRC)											// Do We Have A Rendering Context?
	{
		if (!wglMakeCurrent(NULL, NULL))					// Are We Able To Release The DC And RC Contexts?
		{
			MessageBox(NULL, "Release Of DC And RC Failed.", "SHUTDOWN ERROR", MB_OK | MB_ICONINFORMATION);
		}

		if (!wglDeleteContext(hRC))						// Are We Able To Delete The RC?
		{
			MessageBox(NULL, "Release Rendering Context Failed.", "SHUTDOWN ERROR", MB_OK | MB_ICONINFORMATION);
		}
		hRC = NULL;										// Set RC To NULL
	}

	if (hDC && !ReleaseDC(hWnd, hDC))					// Are We Able To Release The DC
	{
		MessageBox(NULL, "Release Device Context Failed.", "SHUTDOWN ERROR", MB_OK | MB_ICONINFORMATION);
		hDC = NULL;										// Set DC To NULL
	}

	if (hWnd && !DestroyWindow(hWnd))					// Are We Able To Destroy The Window?
	{
		MessageBox(NULL, "Could Not Release hWnd.", "SHUTDOWN ERROR", MB_OK | MB_ICONINFORMATION);
		hWnd = NULL;										// Set hWnd To NULL
	}

	if (!UnregisterClass("OpenGL", hInstance))			// Are We Able To Unregister Class
	{
		MessageBox(NULL, "Could Not Unregister Class.", "SHUTDOWN ERROR", MB_OK | MB_ICONINFORMATION);
		hInstance = NULL;									// Set hInstance To NULL
	}
}

/*	This Code Creates Our OpenGL Window.  Parameters Are:					*
*	title			- Title To Appear At The Top Of The Window				*
*	width			- Width Of The GL Window Or Fullscreen Mode				*
*	height			- Height Of The GL Window Or Fullscreen Mode			*/

bool CreateGLWindow(char* title, int width, int height)
{
	GLuint		PixelFormat;			// Holds The Results After Searching For A Match
	WNDCLASS	wc;						// Windows Class Structure
	DWORD		dwExStyle;				// Window Extended Style
	DWORD		dwStyle;				// Window Style
	RECT		WindowRect;				// Grabs Rectangle Upper Left / Lower Right Values
	WindowRect.left = (long)0;			// Set Left Value To 0
	WindowRect.right = (long)width;		// Set Right Value To Requested Width
	WindowRect.top = (long)0;				// Set Top Value To 0
	WindowRect.bottom = (long)height;		// Set Bottom Value To Requested Height

	hInstance = GetModuleHandle(NULL);				// Grab An Instance For Our Window
	wc.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;	// Redraw On Size, And Own DC For Window.
	wc.lpfnWndProc = (WNDPROC)WndProc;					// WndProc Handles Messages
	wc.cbClsExtra = 0;									// No Extra Window Data
	wc.cbWndExtra = 0;									// No Extra Window Data
	wc.hInstance = hInstance;							// Set The Instance
	wc.hIcon = LoadIcon(NULL, IDI_WINLOGO);			// Load The Default Icon
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);			// Load The Arrow Pointer
	wc.hbrBackground = NULL;									// No Background Required For GL
	wc.lpszMenuName = NULL;									// We Don't Want A Menu
	wc.lpszClassName = "OpenGL";								// Set The Class Name

	if (!RegisterClass(&wc))									// Attempt To Register The Window Class
	{
		MessageBox(NULL, "Failed To Register The Window Class.", "ERROR", MB_OK | MB_ICONEXCLAMATION);
		return false;											// Return FALSE
	}

	dwExStyle = WS_EX_APPWINDOW | WS_EX_WINDOWEDGE;			// Window Extended Style
	dwStyle = WS_OVERLAPPEDWINDOW;							// Windows Style

	AdjustWindowRectEx(&WindowRect, dwStyle, FALSE, dwExStyle);		// Adjust Window To True Requested Size

																	// Create The Window
	if (!(hWnd = CreateWindowEx(dwExStyle,							// Extended Style For The Window
		"OpenGL",							// Class Name
		title,								// Window Title
		dwStyle |							// Defined Window Style
		WS_CLIPSIBLINGS |					// Required Window Style
		WS_CLIPCHILDREN,					// Required Window Style
		0, 0,								// Window Position
		WindowRect.right - WindowRect.left,	// Calculate Window Width
		WindowRect.bottom - WindowRect.top,	// Calculate Window Height
		NULL,								// No Parent Window
		NULL,								// No Menu
		hInstance,							// Instance
		NULL)))								// Dont Pass Anything To WM_CREATE
	{
		KillGLWindow();								// Reset The Display
		MessageBox(NULL, "Window Creation Error.", "ERROR", MB_OK | MB_ICONEXCLAMATION);
		return false;								// Return FALSE
	}

	static	PIXELFORMATDESCRIPTOR pfd =				// pfd Tells Windows How We Want Things To Be
	{
		sizeof(PIXELFORMATDESCRIPTOR),				// Size Of This Pixel Format Descriptor
		1,											// Version Number
		PFD_DRAW_TO_WINDOW |						// Format Must Support Window
		PFD_SUPPORT_OPENGL |						// Format Must Support OpenGL
		PFD_DOUBLEBUFFER,							// Must Support Double Buffering
		PFD_TYPE_RGBA,								// Request An RGBA Format
		24,										// Select Our Color Depth
		0, 0, 0, 0, 0, 0,							// Color Bits Ignored
		0,											// No Alpha Buffer
		0,											// Shift Bit Ignored
		0,											// No Accumulation Buffer
		0, 0, 0, 0,									// Accumulation Bits Ignored
		24,											// 24Bit Z-Buffer (Depth Buffer)  
		0,											// No Stencil Buffer
		0,											// No Auxiliary Buffer
		PFD_MAIN_PLANE,								// Main Drawing Layer
		0,											// Reserved
		0, 0, 0										// Layer Masks Ignored
	};

	if (!(hDC = GetDC(hWnd)))							// Did We Get A Device Context?
	{
		KillGLWindow();								// Reset The Display
		MessageBox(NULL, "Can't Create A GL Device Context.", "ERROR", MB_OK | MB_ICONEXCLAMATION);
		return false;								// Return FALSE
	}

	if (!(PixelFormat = ChoosePixelFormat(hDC, &pfd)))	// Did Windows Find A Matching Pixel Format?
	{
		KillGLWindow();								// Reset The Display
		MessageBox(NULL, "Can't Find A Suitable PixelFormat.", "ERROR", MB_OK | MB_ICONEXCLAMATION);
		return false;								// Return FALSE
	}

	if (!SetPixelFormat(hDC, PixelFormat, &pfd))		// Are We Able To Set The Pixel Format?
	{
		KillGLWindow();								// Reset The Display
		MessageBox(NULL, "Can't Set The PixelFormat.", "ERROR", MB_OK | MB_ICONEXCLAMATION);
		return false;								// Return FALSE
	}

	if (!(hRC = wglCreateContext(hDC)))				// Are We Able To Get A Rendering Context?
	{
		KillGLWindow();								// Reset The Display
		MessageBox(NULL, "Can't Create A GL Rendering Context.", "ERROR", MB_OK | MB_ICONEXCLAMATION);
		return false;								// Return FALSE
	}

	if (!wglMakeCurrent(hDC, hRC))					// Try To Activate The Rendering Context
	{
		KillGLWindow();								// Reset The Display
		MessageBox(NULL, "Can't Activate The GL Rendering Context.", "ERROR", MB_OK | MB_ICONEXCLAMATION);
		return false;								// Return FALSE
	}

	ShowWindow(hWnd, SW_SHOW);						// Show The Window
	SetForegroundWindow(hWnd);						// Slightly Higher Priority
	SetFocus(hWnd);									// Sets Keyboard Focus To The Window

	stateOfThisGame = GameState::MENU;

	std::cout << "Initial screen rendering." << std::endl;
	render(width, height);
	
	loadTextures();

	return true;									// Success
}



