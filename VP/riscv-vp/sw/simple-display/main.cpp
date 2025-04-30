#include "libDisplay.hpp"

#include <math.h>
#include <climits>
#include <cstring>
#include <iostream>

Framebuffer* volatile const framebuffer = (Framebuffer * volatile const)(0x72000000);

void activeWait(float factor = 0.5) {
	for (uint16_t i = 0; i < UINT16_MAX * factor; i++) {
	};
}

frame::Point getRandomPoint() {
	return frame::Point(rand() % screenWidth, rand() % screenHeight);
}

Color getRandomColor() {
	return rand() % SHRT_MAX;
}

void drawBackground() {
	for (uint32_t i = 0; i < screenHeight - 1; i++) {
		display::drawLine(Framebuffer::Type::background, frame::Point(0, i), frame::Point(screenWidth, i),
		                  fromRGB(i & 0x7, 0, i >> 3));
		if (i % 5 == 0)
			display::applyFrame();
	}
}

void drawFunnyRects() {
	static uint32_t m = 0;
	for (uint16_t i = 0; i < 400; i++) {
		// drawLine(framebuffer->getInactiveFrame(), getRandomPoint(),
		// getRandomPoint(), getRandomColor());
		display::drawRect(Framebuffer::Type::foreground, frame::Point(m % screenWidth, m % screenHeight),
		                  frame::Point((screenWidth - (m + 1) % screenWidth), (screenHeight - (m + 1) % screenHeight)),
		                  fromRGB(255 - (m % 255), (m % 255), i % 255));
		display::applyFrame();
		activeWait(.005);
		m += 17;
	}
}

/**
 * @param completion Values between 0..1
 */
void progressBar(bool horizontal, frame::PointF base, frame::PointF extent, Color fg, Color bg, float completion) {
	frame::PointF progress = horizontal ? frame::PointF(extent.x * completion, extent.y) : frame::PointF(extent.x, extent.y * completion);

	display::fillRect(Framebuffer::Type::foreground, base, base + progress, fg);
	display::fillRect(Framebuffer::Type::foreground, base + progress, base + extent, bg);
}

void drawFunnyBar(bool horizontal = false) {
	Color bgColor = fromRGB(0, 0, 1);
	Color progressColor = fromRGB(126, 255, 10);
	frame::Point baseOL;
	frame::Point baseUR;
	uint16_t stepsize = 1;
	if (horizontal) {
		baseOL = frame::Point(100, 250);
		baseUR = frame::Point(700, 350);
	} else {
		baseOL = frame::Point(350, 50);
		baseUR = frame::Point(450, 550);
	}

	display::fillRect(Framebuffer::Type::foreground, baseOL, baseUR, bgColor);
	display::applyFrame();
	frame::Point barBase(baseOL.x + 10, baseOL.y + 10);
	frame::Point barExtent((baseUR.x - baseOL.x) - 20, (baseUR.y - baseOL.y) - 20);

	for (float progress = 0; progress <= 1; progress += 0.01) {
		display::fillRect(Framebuffer::Type::foreground, baseOL, baseUR, bgColor);
		progressBar(horizontal, barBase, barExtent, progressColor, bgColor, progress);
		display::applyFrame();
		activeWait(.005);
	}
	for (float progress = 1; progress >= 0; progress -= 0.01) {
		display::fillRect(Framebuffer::Type::foreground, baseOL, baseUR, bgColor);
		progressBar(horizontal, barBase, barExtent, progressColor, bgColor, progress);
		display::applyFrame();
		activeWait(.005);
	}
}

using namespace std;

int main() {
	cout << "draw background" << endl;
	drawBackground();
	while (true) {
		cout << "Draw H-bar" << endl;
		drawFunnyBar(true);
		display::fillFrame(Framebuffer::Type::foreground);
		display::applyFrame();
		cout << "Draw V-bar" << endl;
		drawFunnyBar(false);
		display::fillFrame(Framebuffer::Type::foreground);
		display::applyFrame();
		cout << "Draw Rects" << endl;
		drawFunnyRects();
		display::fillFrame(Framebuffer::Type::foreground);
		display::applyFrame();
	}
	return 0;
}
