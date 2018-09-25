
#include <fstream>
#include <iostream>
#include <string>
#include <sstream> 
#include "opencv\cv.h"
#include "opencv\highgui.h"
using namespace cv;
using namespace std;
int test28(int argc, char *argv[])
{
	int classlabel = 6;
	string  labelpath = "I:/双个车牌放在一起/黑上白下/0_text.txt";
	string  labelpathone = "I:/双个车牌放在一起/黑上白下/0_one.txt";


	fstream finRead;
	finRead.open(labelpath, ios::in);
	if (!finRead.is_open())
	{
		cout << "finRead 文件数据打开错误！" << endl;
		system("pause");
		return false;
	}

	fstream finWrite;
	finWrite.open(labelpathone, ios::out);
	if (!finWrite.is_open())
	{
		cout << "finRead 文件数据打开错误！" << endl;
		system("pause");
		return false;
	}

	string line;
	while (getline(finRead, line))
	{
		if (line.empty())
		{
			break;
		}
		fstream fin1;
		fin1.open(line);
		cout << line.c_str() << endl;
		if (!fin1.is_open())
		{
			cout << "error" << endl;
			cout << line.c_str() << endl;
			cout << "fin1 文件数据打开错误！" << endl;
			system("pause");
			return false;
		}
		string line1; int label[10] = { 0 }; string ntxt; int i = 0;
		int x1[10] = { 0 }; int y1[10] = { 0 }; int x2[10] = { 0 }; int y2[10] = { 0 };
		while (getline(fin1, line1))
		{
			
			stringstream str_s(line1);
			str_s >> ntxt>>label[i] >> x1[i] >> y1[i] >> x2[i] >> y2[i];
			i++;
		}

		int num = i;

		if (num!=2)
		{
			cout << "num 不为2！" << endl;
			system("pause");
			continue;
		}
		int x1d = 0; int x2d = 0; int y1d = 0; int y2d = 0;
		x1d = min(x1[0],x1[1]);
		y1d = min(y1[0],y1[1]);
		x2d = max(x2[0], x2[1]);
		y2d = max(y2[0], y2[1]);

		string temp = line;
		temp.replace(temp.find_last_of("."), 4, ".jpg");
		finWrite << temp << " " << classlabel << " " << x1d << " " << y1d << " " << x2d << " " << y2d << endl;

		fin1.close();
	}
	finRead.close();
	finWrite.close();
	return 0;
}