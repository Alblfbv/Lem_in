#! /usr/bin/env python3
# coding: utf-8

from tkinter import *
#1274, height=766


def ft_place_grid(canvas):
	i = 0
	j = 0
	while i < 20:
		canvas.create_line(10 + j, 0, 10 + j, 780, fill="#323232")
		j += 125
		i += 1
	i = 0
	j = 0
	while i < 20:
		canvas.create_line(0, 10 + j, 1500, 10 + j, fill="#323232")
		j += 125
		i += 1

def ft_place_room(room, canvas):
		i = 0
		"""
		normalisée = (originale - MIN) * (max - min) / (MAX - MIN) + min

		[MIN,MAX] : interval d'origine
		[min,max] : interval cible
		originale : valeur dans l'interval d'origine
		normalisée : valeur normalisée dans l'interval cible
		"""
		while i < len(room):
			if room[i].type_room == 'S':
				canvas.create_oval(room[i].x, room[i].y, room[i].x + 75, room[i].y + 75, outline="#FE53BB", width="6", fill="black")
			if room[i].type_room == 'E':
				canvas.create_oval(room[i].x, room[i].y, room[i].x + 75, room[i].y + 75, outline="#FE53BB", width="6", fill="black")
			if room[i].type_room == 'M':
				canvas.create_oval(room[i].x, room[i].y, room[i].x + 75, room[i].y + 75, outline="#08F7FE", width="6", fill="black")
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
			canvas.create_line(room[j].x + 35, room[j].y + 35, room[k].x + 35, room[k].y + 35, fill="#08F7FE", width="6")
			i += 1

def ft_place_lem(lem,canvas):
		i = 0
		l = list()
		while (i < len(lem)):
			l.append(canvas.create_oval(lem[i].x + 25, lem[i].y + 25, lem[i].x + 50, lem[i].y + 50, fill="#F5D300"))
			i += 1
		return l
