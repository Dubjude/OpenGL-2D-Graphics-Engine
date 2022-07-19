#include <Engine2D.h>

int main()
{
	///Engine app(1000, 1000);
	///app.run();

	using renderer = mem::Renderer;

	renderer::createWindow(850, 550, "Test");
	renderer::setWindowPos(1920 / 2 - 400, 1080 / 2 - 300);

	mem::Texture_ptr ghost = renderer::loadTexture("ghost.png");
	/*mem::Texture_ptr popcat = renderer::loadTexture("pop_cat.png");
	mem::Texture_ptr block = renderer::loadTexture("block.png");
	mem::Texture_ptr brick = renderer::loadTexture("brick.png");*/

	//float angle = PI/5;

	mem::Image img(250, 250, 4);
	img.pixels = new unsigned char[img.width * img.height * 4];
	for (int y = 0; y < img.height; y++) {
		for (int x = 0; x < img.width; x++)
		{
			img.pixels[4 * (y * img.width + x) + 0] = 255;
			img.pixels[4 * (y * img.width + x) + 1] = 0;
			img.pixels[4 * (y * img.width + x) + 2] = 255;
			img.pixels[4 * (y * img.width + x) + 3] = 125;
		}
	}
	mem::Texture_ptr imTex = renderer::loadTexture(img);

	mem::Font_ptr freeSans = renderer::defaultFont("ComicSans", 32);

	while (!renderer::windowShouldClose())
	{
		int fps = renderer::getFPS();
		std::stringstream ss;
		ss << "Test [" << fps << " FPS]";
		renderer::setWindowTitle(ss.str());

		renderer::fillBackground(glm::vec3(51));
		
		//renderer::drawRect({ 255, 255, 0 }, { 250, 250, 150, 150 });
		//renderer::drawRect({ 0, 0, 255 }, mem::rotate({ 250, 250, 150, 150 }, mem::RectPoints::CENTER, angle));
		
		
		/*if (renderer::getMouseButtonDown(MOUSE_BUTTON_RIGHT))
			angle += 0.1;*/

		renderer::drawTexture(ghost, { 150, 25, 250, 250 });
		renderer::drawTexture(imTex, { 550, 25, 250, 250 });
		/*renderer::drawTexture(popcat, { 50, 50, 450, 150 });
		renderer::drawTexture(block, { 75, 350, 150, 150 });
		renderer::drawTexture(popcat, mem::rotate({ 275, 315, 150, 150 }, mem::RectPoints::CENTER, angle));
		*/

		renderer::drawRect({255, 0, 0}, {0, 0, 250, 500});
		renderer::drawRect({ 0, 255, 0 }, { 150, 300, 250, 100 });

		renderer::drawText(freeSans, "This is sample text", { 0, 0 }, { 125, 200, 150, 255 });
		renderer::drawText(freeSans, "This is sample text", { 250, 275 }, { 255, 200, 50, 125 });

		float x = 750;
		float y = 450;
		for (int i = 0; i < 100; i++)
		{
			renderer::drawPixel(mem::Random::Vec3(255), {x + i, y});
		}

		/*mem::Renderer::drawCircle({ 200, 250, 0 }, { 400, 300 }, 150, 20);
		mem::Renderer::drawEllipse({ 0, 0, 250, 170 }, { 125, 350 }, 70, 30);
		mem::Renderer::drawEllipse({ 0, 0, 250, 170 }, { 125, 350 }, 30, 120);
		mem::Renderer::drawEllipse({ 0, 200, 250 }, { 125, 350 }, 100, 150, 5);
		mem::Renderer::drawRect({ 0, 255, 0 }, { 600, 300, 200, 200 }, 20);
		mem::Renderer::drawPolygon({ 0, 0, 255 }, { { 50, 50 }, { 450, 50 }, { 250, 200 } });
		
		std::vector<glm::vec2> points;
		float delta = TWO_PI / 8;
		int radius = 100;
		for (float angle = 0; angle < TWO_PI; angle += delta)
		{
			points.push_back({ 400 + radius * cos(angle), 300 + radius * sin(angle) });
		}
		mem::Renderer::drawPolygon({ 200, 0, 0 }, points, 10);*/

		
		mem::Renderer::update();
	}

	return EXIT_SUCCESS;
}