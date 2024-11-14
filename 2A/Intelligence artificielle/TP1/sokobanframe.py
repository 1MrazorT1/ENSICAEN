# -*- coding: utf-8; mode: python -*-

# ENSICAEN
# École Nationale Supérieure d'Ingénieurs de Caen
# 6 Boulevard Maréchal Juin
# F-14050 Caen Cedex France
#
# Artificial Intelligence 2I1AE1

# @file sokobanframe.py
#
# @author Régis Clouard
# Based on Risto Stevcev's program (pysokoban)

import sys
if sys.version_info.major >= 3:
    import tkinter as tk
else:
    import Tkinter as tk
import threading
import copy
import time
import os

_ROOT = os.path.abspath(os.path.dirname(__file__))

def enum(**enums):
    return type('Enum', (), enums)

Hole = enum(filled = True, empty = False)

class Direction( object ):
    left = 'Left'
    right = 'Right'
    up = 'Up'
    down = 'Down'

class Level( object ):
    wall = '*'
    hole = 'o'
    crate_in_hole = '@'
    crate = '#'
    player = 'P'
    floor = ' '

class Image( object ):
    wall = os.path.join(_ROOT, 'images/wall.gif')
    hole = os.path.join(_ROOT, 'images/hole.gif')
    crate_in_hole = os.path.join(_ROOT, 'images/crate-in-hole.gif')
    crate = os.path.join(_ROOT, 'images/crate.gif')
    player = os.path.join(_ROOT, 'images/player.gif')
    player_in_hole = os.path.join(_ROOT, 'images/player-in-hole.gif')

class SokobanFrame( tk.Frame, threading.Thread ):
    number_of_explored_nodes = 0
    number_of_moves = 0

    def __init__(self, gridfile, solver, function, timeout):
        threading.Thread.__init__(self)
        tk.Frame.__init__(self)
        self.grid()
        self.timeout = timeout
        self.configure(background="black")
        self.master.title("Sokoban - Level %s" % gridfile.split("/"))
        self.master.resizable(0,0)
        icon = tk.PhotoImage(file = Image.crate)
        self.master.tk.call('wm', 'iconphoto', self.master._w, icon)
        self.DEFAULT_SIZE = 200
        self.frame = tk.Frame(self, height = self.DEFAULT_SIZE, width = self.DEFAULT_SIZE)
        self.frame.grid()
        self.player = None
        self.crates = {}
        self.start_level(gridfile)

    def key( self, event ):
        directions = {Direction.left, Direction.right, Direction.up, Direction.down}
        if event.keysym in directions:
            SokobanFrame.number_of_moves += 1
            self.move_player(event.keysym)

    def start_level( self, level_file_name ):
        level_file = open(level_file_name, "r")
        self.current_state = SokobanState()
        self.current_state.load_level(level_file)
        self.grid()
        self.display_level()

    def display_level( self ):
        for row, line in enumerate(self.current_state.level):
            level_row = list(line)

            for column, char in enumerate(line):
                if char == Level.wall:
                    wall = tk.PhotoImage(file = Image.wall)
                    w = tk.Label(self.frame, image = wall, borderwidth = 0)
                    w.wall = wall
                    w.grid(row = row, column = column)

                elif char == Level.hole:
                    hole = tk.PhotoImage(file = Image.hole)
                    w = tk.Label(self.frame, image = hole, borderwidth = 0)
                    w.hole = hole
                    w.grid(row = row, column = column)

                elif char == Level.crate_in_hole:
                    crate_in_hole = tk.PhotoImage(file = Image.crate_in_hole)
                    w = tk.Label(self.frame, image = crate_in_hole, borderwidth = 0)
                    w.crate_in_hole = crate_in_hole
                    w.grid(row = row, column = column)
                    self.crates[(row, column)] = w

                elif char == Level.crate:
                    crate = tk.PhotoImage(file = Image.crate)
                    w = tk.Label(self.frame, image = crate, borderwidth = 0)
                    w.crate = crate
                    w.grid(row = row, column = column)
                    self.crates[(row, column)] = w
        (row, column) = self.current_state.player_position
        player_image = tk.PhotoImage(file = Image.player)
        self.player = tk.Label(self.frame, image = player_image, borderwidth = 0)
        self.player.player_image = player_image
        self.player.grid(row = row, column = column)

    def move_player( self, direction ):
        row, column = self.current_state.player_position
        prev_row, prev_column = row, column

        blocked = True
        if direction == Direction.left and self.current_state.level[row][column - 1] is not Level.wall and column > 0:
            blocked = self.move_crate((row, column - 1), (row, column - 2))
            if not blocked:
                self.current_state.player_position = (row, column - 1)
        elif direction == Direction.right and self.current_state.level[row][column + 1] is not Level.wall:
            blocked = self.move_crate((row, column + 1), (row, column + 2))
            if not blocked:
                self.current_state.player_position = (row, column + 1)
        elif direction == Direction.down and self.current_state.level[row + 1][column] is not Level.wall:
            blocked = self.move_crate((row + 1, column), (row + 2, column))
            if not blocked:
                self.current_state.player_position = (row + 1, column)
        elif direction == Direction.up and self.current_state.level[row - 1][column] is not Level.wall and row > 0:
            blocked = self.move_crate((row - 1, column), (row - 2, column))
            if not blocked:
                self.current_state.player_position = (row - 1, column)

        if self.current_state.is_goal_state():
            self.game_win()
            return True

        if blocked:
            return False

        row, column = self.current_state.player_position
        if self.current_state.level[prev_row][prev_column] is Level.hole and not blocked:
            hole = tk.PhotoImage(file = Image.hole)
            w = tk.Label(self.frame, image = hole, borderwidth = 0)
            w.hole = hole
            w.grid(row = prev_row, column = prev_column)

        if not blocked:
            self.player.grid_forget()

            if self.current_state.level[row][column] is Level.hole:
                player_image = tk.PhotoImage(file = Image.player_in_hole)
            else:
                player_image = tk.PhotoImage(file = Image.player)

            self.player = tk.Label(self.frame, image = player_image, borderwidth = 0)
            self.player.player_image = player_image
            self.player.grid(row = row, column = column)
        return True

    def move_crate( self, location, next_location ):
        row, column = location
        next_row, next_column = next_location

        if self.current_state.level[row][column] is Level.crate and self.current_state.level[next_row][next_column] is Level.floor:
            self.crates[(row, column)].grid_forget()
            crate = tk.PhotoImage(file = Image.crate)
            w = tk.Label(self.frame, image = crate, borderwidth = 0)
            w.crate = crate
            w.grid(row = next_row, column = next_column)

            self.crates[(next_row, next_column)] = w
            self.current_state.level[row][column] = Level.floor
            self.current_state.level[next_row][next_column] = Level.crate

        elif self.current_state.level[row][column] is Level.crate and self.current_state.level[next_row][next_column] is Level.hole:
            self.crates[(row, column)].grid_forget()
            crate_in_hole = tk.PhotoImage(file = Image.crate_in_hole)
            w = tk.Label(self.frame, image = crate_in_hole, borderwidth = 0)
            w.crate = crate_in_hole
            w.grid(row = next_row, column = next_column)

            self.crates[(next_row, next_column)] = w
            self.current_state.level[row][column] = Level.floor
            self.current_state.level[next_row][next_column] = Level.crate_in_hole
            self.current_state.holes[(next_row, next_column)] = Hole.filled

        elif self.current_state.level[row][column] is Level.crate_in_hole and self.current_state.level[next_row][next_column] is Level.floor:
            self.crates[(row, column)].grid_forget()
            crate = tk.PhotoImage(file = Image.crate)
            w = tk.Label(self.frame, image = crate, borderwidth = 0)
            w.crate = crate
            w.grid(row = next_row, column = next_column)

            self.crates[(next_row, next_column)] = w
            self.current_state.level[row][column] = Level.hole
            self.current_state.level[next_row][next_column] = Level.crate
            self.current_state.holes[(row, column)] = Hole.empty

        elif self.current_state.level[row][column] is Level.crate_in_hole and self.current_state.level[next_row][next_column] is Level.hole:
            self.crates[(row, column)].grid_forget()
            crate_in_hole = tk.PhotoImage(file = Image.crate_in_hole)
            w = tk.Label(self.frame, image = crate_in_hole, borderwidth = 0)
            w.crate_in_hole = crate_in_hole
            w.grid(row = next_row, column = next_column)

            self.crates[(next_row, next_column)] = w
            self.current_state.level[row][column] = Level.hole
            self.current_state.level[next_row][next_column] = Level.crate_in_hole
            self.current_state.holes[(row, column)] = Hole.empty
            self.current_state.holes[(next_row, next_column)] = Hole.filled

        if self.is_blocked(location, next_location):
            return True
        return False

    def is_blocked( self, location, next_location ):
        row, column = location
        next_row, next_column = next_location

        if self.current_state.level[row][column] is Level.crate and self.current_state.level[next_row][next_column] is Level.wall:
            return True
        elif self.current_state.level[row][column] is Level.crate_in_hole and self.current_state.level[next_row][next_column] is Level.wall:
            return True
        elif (self.current_state.level[row][column] is Level.crate_in_hole and
                  (self.current_state.level[next_row][next_column] is Level.crate or
                           self.current_state.level[next_row][next_column] is Level.crate_in_hole)):
            return True
        elif (self.current_state.level[row][column] is Level.crate and
                  (self.current_state.level[next_row][next_column] is Level.crate or
                           self.current_state.level[next_row][next_column] is Level.crate_in_hole)):
            return True

    def game_over( self ):
        inlay = tk.PhotoImage(file = 'images/gameover.gif')
        w = tk.Label(self.master, image=inlay)
        w.inlay = inlay
        w.place(x = (self.frame.winfo_width() - inlay.width()) / 2, y = (self.frame.winfo_height() - inlay.height()) / 2)
        self.after(2000, self.quit)

    def game_win( self ):
        inlay = tk.PhotoImage(file = 'images/winner.gif')
        w = tk.Label(self.master, image=inlay)
        w.inlay = inlay
        w.place(x = (self.frame.winfo_width() - inlay.width()) / 2, y = (self.frame.winfo_height() - inlay.height()) / 2)
        if SokobanFrame.number_of_moves>0:
            print('Number of moves: %d' % SokobanFrame.number_of_moves)
        self.after(2000, self.quit)

    def get_start_state( self ):
        return self.current_state

    def display_path( self, path ) :
        if path:
            if not self.move_player(path.pop(0)):
                return False
            self.after(self.timeout, self.display_path, path)
        return True

DEAD_CELL = -1

class SokobanState( ):
    """
    A search problem defines the state space, start state, goal test,
    successor function and cost function.  This search problem can be
    used to find paths to a particular point on the sokoban board.

    The state space consists of (x,y) positions in a sokoban and the board..

    Note: this search problem is fully specified; you should NOT change it.
    """

    def __init__( self ):
        self.player_position = ()
        self.level = []
        self.holes = {}
        self.dead_map = []

    def __deepcopy__(self, memo):
        state = SokobanState()
        state.level = copy.deepcopy(self.level, memo)
        state.player_position = copy.deepcopy(self.player_position, memo)
        state.holes = copy.deepcopy(self.holes, memo)
        state.dead_map = self.dead_map # shared
        return state

    def __eq__( self, other ):
        return self.player_position == other.player_position and self.level == other.level

    def __hash__( self ):
        l = [item for sublist in self.level for item in sublist]
        return hash((self.player_position, tuple(l)))

    def load_level( self, level_file ):
        for row, line in enumerate(level_file):
            level_row = list(line)
            for column, x in enumerate(level_row):
                if x == Level.player:
                    level_row[column] = Level.floor
                    self.player_position = (row, column)

                elif x == Level.hole:
                    self.holes[(row, column)] = Hole.empty

                elif x == Level.crate_in_hole:
                    self.holes[(row, column)] = Hole.filled

            self.level.append(level_row)
        self.mark_dead_cells()

    def mark_dead_cells( self ):
        """ The map dead_map is use to mark cell where the crates cannot be pushed,
        for example corners. This reduces the size of the search tree. """
        height = len(self.level)
        width = max(len(y) for y in self.level)

        self.dead_map = [[0 for x in range(width)] for y in range(height)]

        for y in range(height):
            for x in range(len(self.level[y])):
                if self.level[y][x] is not Level.wall and y != 0 and x != 0 and y != height - 1 and x != width - 1 and x < len(self.level[y + 1]) and x < len(self.level[y - 1]):
                    self.dead_map[y][x] = 1

        # mark corners
        for y in range(height):
            for x in range(len(self.level[y])):
                if self.dead_map[y][x] == 1:
                    if self.level[y][x] is Level.floor and self.level[y - 1][x] is Level.wall and self.level[y][x - 1] is Level.wall:
                        self.dead_map[y][x] = DEAD_CELL
                    if self.level[y][x] is Level.floor and self.level[y + 1][x] is Level.wall and self.level[y][x - 1] is Level.wall:
                        self.dead_map[y][x] = DEAD_CELL
                    if self.level[y][x] is Level.floor and self.level[y - 1][x] is Level.wall and self.level[y][x + 1] is Level.wall:
                        self.dead_map[y][x] = DEAD_CELL
                    if self.level[y][x] is Level.floor and self.level[y + 1][x] is Level.wall and self.level[y][x + 1] is Level.wall:
                        self.dead_map[y][x] = DEAD_CELL

        def mark_row( start_x, y ):
            end_x = -1
            for x in range(start_x + 1, len(self.level[y])):
                if self.dead_map[y][x] == DEAD_CELL:
                    end_x = x
                elif not (self.dead_map[y][x] == 1
                          and (self.level[y - 1][x] is Level.wall or self.level[y + 1][x] is Level.wall)
                          and self.level[y][x] == Level.floor):
                    break
            if end_x > -1:
                for x in range(start_x + 1, end_x):
                    self.dead_map[y][x] = DEAD_CELL

        # mark dead row
        for y in range(height):
            for x in range(len(self.level[y])):
                if self.dead_map[y][x] == DEAD_CELL:
                    mark_row(x, y)
                
        def mark_column( x, start_y ):
            end_y = -1
            for y in range(start_y + 1, len(self.level)):
                if self.dead_map[y][x] == DEAD_CELL:
                    end_y = y
                elif not (self.dead_map[y][x] == 1
                          and (self.level[y][x - 1] is Level.wall or self.level[y][x + 1] is Level.wall)
                          and self.level[y][x] == Level.floor):
                    break
            if end_y > -1:
                for y in range(start_y + 1, end_y):
                    self.dead_map[y][x] = DEAD_CELL

        # mark dead row
        for x in range(len(self.level[y])):
            for y in range(height):
                if self.dead_map[y][x] == DEAD_CELL:
                    mark_column(x, y)

    def is_goal_state( self ) :
        """ Returns the goal state (in your state space,
        not the full Pacman state space).
        """
        SokobanFrame.number_of_explored_nodes += 1
        all_holes_filled = True
        for hole in self.holes.values():
            if hole is not Hole.filled:
                all_holes_filled = False
        return all_holes_filled

    def get_successor_states( self ):
        """
        For a given state, this should return a list of triples,
        (successor, action, stepCost), where 'successor' is a
        successor to the current state, 'action' is the direction
        required to get there, and 'stepCost' is the incremental
        cost of expanding to that successor (always 1).
        """ 
        successors = []
        for action in [Direction.left, Direction.right, Direction.up, Direction.down]:
            next_state = copy.deepcopy(self);
            if next_state.move_player(action):
                cost = 1
                successors.append( ( next_state, action, cost) )

        return successors

    def move_player( self, direction ):
        row, column = self.player_position
        prev_row, prev_column = row, column

        blocked = True
        if direction == Direction.left and self.level[row][column - 1] is not Level.wall and column > 0:
            blocked = self.move_crate((row, column - 1), (row, column - 2))
            if not blocked:
                self.player_position = (row, column - 1)
        elif direction == Direction.right and self.level[row][column + 1] is not Level.wall:
            blocked = self.move_crate((row, column + 1), (row, column + 2))
            if not blocked:
                self.player_position = (row, column + 1)
        elif direction == Direction.down and self.level[row + 1][column] is not Level.wall:
            blocked = self.move_crate((row + 1, column), (row + 2, column))
            if not blocked:
                self.player_position = (row + 1, column)
        elif direction == Direction.up and self.level[row - 1][column] is not Level.wall and row > 0:
            blocked = self.move_crate((row - 1, column), (row - 2, column))
            if not blocked:
                self.player_position = (row - 1, column)

        if self.is_goal_state():
            return True
        
        return not blocked

    def move_crate( self, location, next_location ):
        row, column = location
        next_row, next_column = next_location

        if self.is_blocked(location, next_location):
            return True
        if self.level[row][column] is Level.crate and self.level[next_row][next_column] is Level.floor:
            self.level[row][column] = Level.floor
            self.level[next_row][next_column] = Level.crate

        elif self.level[row][column] is Level.crate and self.level[next_row][next_column] is Level.hole:
            self.level[row][column] = Level.floor
            self.level[next_row][next_column] = Level.crate_in_hole
            self.holes[(next_row, next_column)] = Hole.filled

        elif self.level[row][column] is Level.crate_in_hole and self.level[next_row][next_column] is Level.floor:
            self.level[row][column] = Level.hole
            self.level[next_row][next_column] = Level.crate
            self.holes[(row, column)] = Hole.empty

        elif self.level[row][column] is Level.crate_in_hole and self.level[next_row][next_column] is Level.hole:
            self.level[row][column] = Level.hole
            self.level[next_row][next_column] = Level.crate_in_hole
            self.holes[(row, column)] = Hole.empty
            self.holes[(next_row, next_column)] = Hole.filled

        return False

    def is_blocked( self, location, next_location ):
        row, column = location
        next_row, next_column = next_location
        if ((self.level[row][column] is Level.crate or self.level[row][column] is Level.crate)
            and self.dead_map[next_row][next_column] != 1):
            return True
        if self.level[row][column] is Level.crate and self.level[next_row][next_column] is Level.wall:
            return True
        elif self.level[row][column] is Level.crate_in_hole and self.level[next_row][next_column] is Level.wall:
            return True
        elif (self.level[row][column] is Level.crate_in_hole
              and (self.level[next_row][next_column] is Level.crate
                   or self.level[next_row][next_column] is Level.crate_in_hole)):
            return True
        elif (self.level[row][column] is Level.crate
              and (self.level[next_row][next_column] is Level.crate
                   or self.level[next_row][next_column] is Level.crate_in_hole)):
            return True

    def heuristic( self ):
        return self.heuristic2()

    def heuristic1( self ):
        """ Number of misplaced crates. """
        number_of_misplaced_crate = 0
        for y in range(len(self.level)):
            for x in range(len(self.level[y])):
                if self.level[y][x] is Level.crate:
                    number_of_misplaced_crate += 1 
        return number_of_misplaced_crate

    def heuristic2( self ):
        """ Manhattan distance of crates to nearest hole. """
        crates = []
        holes = []
        for y in range(len(self.level)):
            for x in range(len(self.level[y])):
                if self.level[y][x] is Level.crate:
                    crates += [(x, y)]
                elif self.level[y][x] is Level.hole:
                    holes += [(x, y)]

        def manhattanDistance( c1, c2 ):
            return abs(c1[0] - c2[0]) + abs(c1[1] - c2[1])

        total_distance = 0
        for crate in crates:
            distance = 1e30
            for hole in holes:
                d = manhattanDistance(crate, hole)
                if (d < distance):
                    distance = d
            total_distance += distance

        distance = 0
        return total_distance + distance
    
