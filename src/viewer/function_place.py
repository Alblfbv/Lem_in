#! /usr/bin/env python3
# coding: utf-8

from tkinter import *

def ft_place_room(room, canvas):
		i = 0
		while i < len(room):
			if room[i].type_room == 'S':
				canvas.create_oval(room[i].x, room[i].y, room[i].x + 75, room[i].y + 75, outline="green", width="4", fill="#005085")
			if room[i].type_room == 'E':
				canvas.create_oval(room[i].x, room[i].y, room[i].x + 75, room[i].y + 75, outline="red", width="4", fill="#005085")
			if room[i].type_room == 'M':
				canvas.create_oval(room[i].x, room[i].y, room[i].x + 75, room[i].y + 75, outline="white", width="4", fill="#005085")
			i += 1

def ft_place_path(room, path, canvas):
		i = 0
		while i < len(path):
			j = 0
			k = 0
			while room[j].name != path[i].path_1:
				j += 1
			while room[k].name != path[i].path_2:
				k += 1
			canvas.create_line(room[j].x + 35, room[j].y + 35, room[k].x + 35, room[k].y + 35, fill="white", width="4")
			i += 1

def ft_place_lem(lem,canvas):
		i = 0
		l = list()
		while (i < len(lem)):
			l.append(canvas.create_oval(lem[i].x + 25, lem[i].y + 25, lem[i].x + 50, lem[i].y + 50, fill="black", outline="white"))
			i += 1
		return l
