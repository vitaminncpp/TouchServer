#include "Util.h"
#include <string>
int ReadJSON(char *buff, InputJSON &in) {
	int i = 0;
	char ch = buff[i];
	int state = 0;
	int start = 0;
	int stop = -1;
	std::string key;
	std::string value;
	bool flag = true;
	while (flag)
	{
		ch = buff[i];
		switch (state) {
		case 0:
			if (ch == '{') {
				state = 1;
			}
			else {
				state = -1;
				flag = false;
			}
			break;
		case 1:
			if (ch == '\"') {
				state = 2;
			}
			else {
				state = -2;
				flag = false;
			}
			break;
		case 2:
			if ((ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z')) {
				start = i;
			}
			else {
				state = -3;
				flag = false;
			}
			break;
		case 3:
			if ((ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z')) {
				break;
			}
			else {
				state = -4;
				flag = false;
			}
			break;
		case 4:
			if (ch == '\"') {
				stop = i;
				int len = stop - start;
				string 
			}
			else {
				state = -5;
				flag = false;
			}
			break;
		case 5:
			break;
		case 6:
			break;
		case 7:
			break;
		case 8:
			break;
		default:
			break;
		}
		i++;
	}
}