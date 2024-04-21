#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <string>
#include <vector>
#include <cmath>
#include <filesystem>
#include <windows.h>
#include <utility>
#include <memory>

using namespace std;
using namespace sf;
namespace fs = filesystem;

unique_ptr<RenderWindow> initsWindow(HWND windowHandle)
{
	
	if (windowHandle == nullptr)
	{
		vector<VideoMode> modes = VideoMode::getFullscreenModes();
		VideoMode mode = modes.at(0);
		unique_ptr<RenderWindow> window = make_unique<RenderWindow>(mode, "Window", Style::Fullscreen);
		return move(window);
	}
	else
	{
		unique_ptr<RenderWindow> window = make_unique<RenderWindow>(windowHandle);
		return move(window);
	}
}

int main(int argc, char* argv[])
{
	const vector<string> args{ argv, argv + argc };
	string nums;
	HWND windowHandle = nullptr;
	if (args.size() == 3)
	{
		if (args.at(1) == "/p")
		{
			nums = args.at(2);
			windowHandle = (HWND)stoull(nums);
		}
	}

	unique_ptr<RenderWindow> window = initsWindow(windowHandle);
	
	window->setFramerateLimit(144);
	
	fs::path cwd = fs::current_path();
	fs::path imagesDir = cwd / "assets" / "images";
	fs::path imagepath = imagesDir / "SunsetImage1.png";

	Texture texture;
	texture.loadFromFile(imagepath.string());
	

	/*Image image;
	image.loadFromFile(imagepath.string());*/
	RectangleShape rect(Vector2f(window->getSize()));
	rect.setTexture(&texture);
	//rect.setFillColor({ 255, 255, 255, 100 });
	
	
	/*Sprite sprite;
	sprite.setTexture(texture);
	sprite.setOrigin(0.f, 0.f);
	sprite.setScale(2.f, 2.f);*/

	int mouseX = 0;
	int mouseY = 0;
	int mouseDX = 0;
	int mouseDY = 0;

	Event event;

	while (window->isOpen())
	{
		while (window->pollEvent(event))
		{
			if (event.type == Event::KeyPressed || event.type == Event::MouseButtonPressed || event.type == Event::Closed)
			{
				window->close();
			}
			else if (event.type == Event::MouseMoved)
			{
				if (mouseX == 0)
				{
					mouseX = event.mouseMove.x;
				}
				if (mouseY == 0)
				{
					mouseY = event.mouseMove.y;
				}

				if (mouseDX > 10 || mouseDY > 10)
				{
					window->close();
				}
				else
				{
					mouseDX += abs(event.mouseMove.x - mouseX);
					mouseDY += abs(event.mouseMove.y - mouseY);
				}			
			}
		}

		window->clear();
		window->draw(rect);
		window->display();
		
	}
}