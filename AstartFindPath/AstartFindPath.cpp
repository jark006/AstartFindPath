// Lib Required https://easyx.cn
//

#include "pch.h"
#include "AStar.h"
#include <iostream>
#include <ctime>

using namespace std;
/*
  Coordinate System

  O————————> (x)
  |++++++++
  |++++++++
  |++++++++
  V
 (y)

*/

int main(int argc, char** argv)
{
	BMPImage bmpImage1("..\\map.bmp");//24bit BGR BMP

	cout << bmpImage1.width() << '*' << bmpImage1.height() << endl;

	initgraph(bmpImage1.width(), bmpImage1.height(), SHOWCONSOLE);
	setbkcolor(WHITE);
	setfillcolor(WHITE);
	setlinecolor(RED);

	AStar::Vec2i start{ 3, 3 }, target{ 185, 122 }; //起点{x, y}，终点{x, y}
	AStar::Generator generator;
	generator.setWorldSize({ bmpImage1.width(), bmpImage1.height() });//map Size
	generator.setHeuristic(AStar::Heuristic::euclidean);//启发式：欧几里得 sqrt(x^2 + y^2)
	generator.setDiagonalMovement(true);//true:8个方向 false:4个方向

	cout << "start:{ x=" << start.x << ", y=" << start.y << "}\r\n";
	cout << "target:{ x=" << target.x << ", y=" << target.y << "}\r\n";

	BeginBatchDraw();
	//读取BMP, 放置障碍物，图片白色像素(RGB=255/255/255)为空闲
	for (int4 x = 0; x < bmpImage1.width(); x++) {
		for (int4 y = 0; y < bmpImage1.height(); y++) {
			BGR c = bmpImage1.at<BGR>(y, x);
			if (c.r != 255 || c.g != 255 || c.b != 255) //Collision
				generator.addCollision({ x, y });

			putpixel(x, y, RGB(c.r, c.g, c.b));
		}
	}
	putpixel(start.x, start.y, RGB(0, 255, 0));   //GREEN
	putpixel(target.x, target.y, RGB(0, 0, 255)); //BLUE
	EndBatchDraw();

	time_t t1 = time(NULL);
	std::cout << "Generate path ... \n";
	auto path = generator.findPath(start, target);//寻路
	time_t t2 = time(NULL);

	BeginBatchDraw();
	//Ptint the coordinateList of Path (targetPoint to startPoint)
	for (auto& coordinate : path) {
		std::cout << '{' << coordinate.x << ", " << coordinate.y << "} <- ";
		putpixel(coordinate.x, coordinate.y, RGB(255, 0, 0));
	}
	putpixel(start.x, start.y, RGB(0, 255, 0));   //GREEN
	putpixel(target.x, target.y, RGB(0, 0, 255)); //BLUE
	EndBatchDraw();

	cout << "\r\nTimes:" << t2 - t1 << 's' << endl;

	// 保存绘制的图像
	wstring s =L"..\\path_" + to_wstring(time(NULL)) + L".bmp";
	saveimage(s.c_str());
	cout << "寻路结果已保存到：";
	wcout << s;
	cout << endl;

	system("pause");
}


