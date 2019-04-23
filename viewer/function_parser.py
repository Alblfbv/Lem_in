#! /usr/bin/env python3
# coding: utf-8

import fileinput
from main_viewer import *

def	ft_parser():
	read = list()
	for line in fileinput.input():
		read.append(line)
	return (read)

def	ft_len_lem(read):
	i = 0
	nb_lem = 0
	while i < len(read):
		tmp = read[i].replace('\n', '')
		if tmp.isnumeric() == True:
			nb_lem = tmp
			break
		i += 1
	return nb_lem

# STORE ROOM / PATH

def ft_store_room(read, room, type_room, grid):
	tmp_room = Room()
	line = read.split(' ')
	while i < len(line):
		while line[i] == '':
			line.pop(i)
		i += 1
	if len(line) != 3:
		return
	line[2] = line[2].replace('\n', '')
	if line[1].isnumeric() == False or line[2].isnumeric() == False:
		return
	tmp_room.name = str(line[0].replace('\n', ''))
	tmp_room.x = int(line[1])
	tmp_room.y = int(line[2])
	if tmp_room.x > grid.xmax:
		grid.xmax = tmp_room.x
	if tmp_room.y > grid.ymax:
		grid.ymax = tmp_room.y
	if type_room == 'S':
		tmp_room.type_room = 'S'
	if type_room == 'E':
		tmp_room.type_room = 'E'
	if type_room == 'M':
		tmp_room.type_room = 'M'
	room.append(tmp_room)
	grid.nb_room += 1

def ft_store_path(read, path, room):
	tmp_path = Path()
	line = read.split('-')
	while i < len(line):
		while line[i] == '':
			line.pop(i)
		i += 1
	if len(line) != 2:
		return
	tmp_path.path_1 = str(line[0].replace('\n', ''))
	tmp_path.path_2 = str(line[1].replace('\n', ''))
	path.append(tmp_path)

def ft_comment(read, i):
	while read[i][0] == "#" and read[i][1] != "#":
		i += 1
	return i

def	ft_room_path(read, room, path, grid, i):
	while i < len(read):
		if (read[i] == "\n"):
			break
		if read[i] == "##start\n":
			i += 1
			i = ft_comment(read, i)
			ft_store_room(read[i], room, 'S', grid)
			i += 1
		if read[i] == "##end\n":
			i += 1
			i = ft_comment(read, i)
			ft_store_room(read[i], room, 'E', grid)
			i += 1
		i = ft_comment(read, i)
		if i == len(read):
			break
		ft_store_room(read[i], room, 'M', grid)
		ft_store_path(read[i], path, room)
		i += 1
	i += 1
	return i

#STORE MOVE

def ft_store_move(read, move):
	tmp = Move()
	tmp.tab_move = read
	tmp.tab_move = tmp.tab_move.split(' ')
	move.append(tmp)

def	ft_move(read, move, i):
	while i < len(read):
		ft_store_move(read[i], move)
		i += 1
	i = 0

#STORE LEM

def ft_store_lem(lem, room):
	tmp_lem = Lem()
	tmp_lem.x = room.x
	tmp_lem.y = room.y
	lem.append(tmp_lem)

def	ft_lem_static(lem, room, nb_lem):
	j = 0
	i = 0
	while room[j].type_room != 'S':
		j += 1
	while i < int(nb_lem):
		ft_store_lem(lem, room[j])
		i += 1

# Normalize

def ft_normalize(room, grid):
	i = 0
	x = 0
	y = 0
	while i < len(room):
		room[i].x = ((int((int(room[i].x) * (grid.nb_room - 1) / (grid.xmax))) * 100) + 25)
		room[i].y = ((int((int(room[i].y) * (grid.nb_room - 1) / (grid.ymax))) * 100) + 25)
		i += 1
