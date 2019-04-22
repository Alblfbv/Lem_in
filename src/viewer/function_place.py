#! /usr/bin/env python3
# coding: utf-8

from tkinter import *
#1274, height=766


def ft_place_grid(canvas, grid):
	j = 0
	while j < grid.win_height * 10:
		canvas.create_line(j, 0, j, grid.win_height * 10, fill="#323232")
		j += 100
	j = 0
	while j < grid.win_width * 10:
		canvas.create_line(0, j, grid.win_width * 10, j, fill="#323232")
		j += 100

def ft_place_room(room, canvas):
		"""
		normalisée = (originale - MIN) * (max - min) / (MAX - MIN) + min

		[MIN,MAX] : interval d'origine
		[min,max] : interval cible
		originale : valeur dans l'interval d'origine
		normalisée : valeur normalisée dans l'interval cible
		"""
		i = 0
		while i < len(room):
			if room[i].type_room == 'S':
				canvas.create_oval(room[i].x, room[i].y, room[i].x + 50, room[i].y + 50, outline="#FE53BB", width="6", fill="black")
			if room[i].type_room == 'E':
				canvas.create_oval(room[i].x, room[i].y, room[i].x + 50, room[i].y + 50, outline="#FE53BB", width="6", fill="black")
			if room[i].type_room == 'M':
				canvas.create_oval(room[i].x, room[i].y, room[i].x + 50, room[i].y + 50, outline="#08F7FE", width="6", fill="black")
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
			canvas.create_line(room[j].x + 25, room[j].y + 25, room[k].x + 25, room[k].y + 25, fill="#08F7FE", width="6")
			i += 1

def ft_place_lem(lem,canvas):
		i = 0
		l = list()
		while (i < len(lem)):
			l.append(canvas.create_oval(lem[i].x + 15, lem[i].y + 15, lem[i].x + 35, lem[i].y + 35, fill="#F5D300"))
			i += 1
		return l
