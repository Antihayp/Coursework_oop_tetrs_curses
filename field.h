#ifndef FIELD_H
#define FIELD_H

#include "field.h"
#include <string>

using namespace std;

const unsigned int coord_y_scr = 3;
const unsigned int coord_x_scr = 25;
const int start_y_obj = 1;
const int start_x_obj = 10;

class Field
{
	static const unsigned int line = 22;
	static const unsigned int column = 22;
	int y_obj;
	int x_obj;
	char field[line][column];
public:
	Field();
	//~Field();
	int check_x_left();
	int check_x_right();
	int check_y_down(WINDOW*);

	int get_line_win();
	int get_column_win();
	int get_index(int);

	void key_left(WINDOW*);
	void key_right(WINDOW*);
	void key_up(WINDOW*);
	void key_down(WINDOW*);

	void print_obj(WINDOW*);
	void print_del_obj(WINDOW*);
	void print_info(int);
	void print_field(WINDOW* win);
	void print_window_matr();

	void get_figure();


};

Field::Field()
{
	y_obj = start_y_obj;
	x_obj = start_x_obj;

	for (unsigned int i = 0; i < line; i++)
	{
		if (i == 0 || i == line - 1) {
			for (int j = 0; j < 22; j++)
			{
				field[i][j] = '#';
			}
			continue;
		}

		for (int j = 0; j < 22; j++)
		{
			if (j == 0 || j == 21) {
				field[i][j] = '#';
				continue;
			}
			field[i][j] = ' ';
		}
	}

	field[x_obj][y_obj] = '$';
}

int Field::check_x_right()
{
	if (x_obj == line - 2)
		return x_obj;
	//field[x_obj][y_obj] = ' ';
	//field[x_obj + 1][y_obj] = '$';
	return x_obj + 1;
}

int Field::check_x_left()
{
	if (x_obj == 1)
		return x_obj;
	//field[x_obj][y_obj] = ' ';
	//field[x_obj - 1][y_obj] = '$';
	return x_obj - 1;
}

int Field::check_y_down(WINDOW* win)
{
	if (y_obj == line - 2 && field[x_obj][y_obj + 1] != ' ') {
		field[start_x_obj][start_y_obj] = ' ';
		field[x_obj][y_obj] = '$';
		y_obj = start_y_obj;
		x_obj = start_x_obj;
		print_field(win);
		return y_obj;
	}
	return y_obj + 1;
}

int Field::get_line_win() {return line;}

int Field::get_column_win() {return column;}

int Field::get_index(int num_fig)
{
	return num_fig * 7 + num_fig;
}

void Field::key_left(WINDOW* win)
{
	print_del_obj(win);
	x_obj = check_x_left();
}

void Field::key_right(WINDOW* win)
{
	print_del_obj(win);
	x_obj = check_x_right();
}

void Field::key_up(WINDOW* win)
{
	print_del_obj(win);
	y_obj--;
}

void Field::key_down(WINDOW* win)
{
	print_del_obj(win);
	y_obj = check_y_down(win);
}

void Field::print_obj(WINDOW* win)
{
	mvwprintw(win, y_obj, x_obj, "$");
}

void Field::print_del_obj(WINDOW* win)
{
	mvwprintw(win, y_obj, x_obj, " ");
}

void Field::print_info(int key)
{
	mvprintw(0, 0, "Key: %c %d", key, key);
	mvprintw(1, 0, "y, x: %d %d", y_obj, x_obj);
}
/*
void Field::get_figure()
{
	int *obj = figure.get_obj(), num = 0, x, y;

	num = get_index(0);
	for (int i = 0; i < 4; i++, num += 2)
	{
		x = obj[num] + 1;
		y = obj[num + 1] + 10;
		arr_point[i].set_point(x, y);
		field[x][y] = '$';
	}
	//print_field();
}*/

void Field::print_field(WINDOW* win)
{
	unsigned int y_matr = coord_y_scr, x_matr = 0;
	string test;
	for (unsigned int i = 1; i < line - 1; i++)
	{
		for (unsigned int j = 1; j < column - 1; j++)
		{
			mvprintw(j + y_matr, i + x_matr, "%c ", field[i][j]);
			test = field[i][j];
			mvwprintw(win, j, i, &test[0]);
		}
	}
}

#endif