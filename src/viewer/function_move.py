#! /usr/bin/env python3
# coding: utf-8

import time
from tkinter import *
from class_viewer import *


def ft_move_lem(move, room, lem, l, canvas):
		i = 0
		tab_display = list()
		while i < len(move):
			tmp_display = Display()
			j = 0
			while j < len(move[i].tab_move):
				k = 0
				tmp = move[i].tab_move[j].split('-')
				next_room = tmp[1].replace('\n', '')
				name_lem = int(tmp[0].replace('L', '')) - 1
				#Search Room
				while room[k].name != next_room:
					k += 1
				#Cal de x et y
				x = (room[k].x - lem[name_lem].x) / 50
				y = (room[k].y - lem[name_lem].y) / 50
				lem[name_lem].x = room[k].x
				lem[name_lem].y = room[k].y
				#Move
				tmp_display.name.append(name_lem)
				tmp_display.x.append(x)
				tmp_display.y.append(y)
				j += 1
			tab_display.append(tmp_display)
			i += 1
		i = 0
		time.sleep(5)
		while i < len(tab_display):
			j = 0
			while j < len(tab_display[i].name):
				for loops in range(50):
					time.sleep(0.005)
					canvas.move(l[tab_display[i].name[j]], tab_display[i].x[j], tab_display[i].y[j])
					canvas.update()
				j += 1
			i += 1
			time.sleep(1.5)
