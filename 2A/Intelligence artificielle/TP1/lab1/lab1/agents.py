# -*- coding: utf-8; mode: python -*-

# ENSICAEN
# École Nationale Supérieure d'Ingénieurs de Caen
# 6 Boulevard Maréchal Juin
# F-14050 Caen Cedex France
#
# Artificial Intelligence 2I1AE1

# @file agents.py
#
# @author Régis Clouard

import copy
import utils

class Agent:
    """
    Abstract class for the agents that implement the various search strategies.
    It is based on the Strategy Design Pattern (abstract method is search()).

    YOU DO NOT NEED TO CHANGE ANYTHING IN THIS CLASS, EVER.
    """
    def search( self ):
        """ This is the method to implement for each specific searcher."""
        raise Exception("Invalid Agent class, search() not implemented")

 #  ______                               _                  __ 
 # |  ____|                             (_)                /_ |
 # | |__    __  __   ___   _ __    ___   _   ___    ___     | |
 # |  __|   \ \/ /  / _ \ | '__|  / __| | | / __|  / _ \    | |
 # | |____   >  <  |  __/ | |    | (__  | | \__ \ |  __/    | |
 # |______| /_/\_\  \___| |_|     \___| |_| |___/  \___|    |_|

class DFS( Agent ):

    def search( self, initial_state ):
        """ Depth-First Search.

        Returns the path as a list of directions among
        { Direction.left, Direction.right, Direction.up, Direction.down }

        """
        open_list = [[ (initial_state, None) ]] # A state is a pair (board, direction)
        closed_list = set([initial_state]) # keep already explored positions

        while open_list:
            # Get the path at the top of the stack (pop() returns the last item of the list)
            current_path = open_list.pop()
            # Get the last place of that path
            current_state, current_direction = current_path[-1]
            # Check if we have reached the goal
            if current_state.is_goal_state():
                # remove the start point and return only the directions.
                return (list (map(lambda x : x[1], current_path[1:])))
            else:
                # Check where we can go from here
                next_steps = current_state.get_successor_states()
                # Add the new paths (one step longer) to the stack
                for state, direction, weight in next_steps:
                    # do not add already explored states
                    if state not in closed_list:
                        # add at the end of the list
                        closed_list.add(state)
                        open_list.append( (current_path + [ (state, direction) ]) )
        return []

class BFS( Agent ):
    
    def search( self, initial_state ):
        """ Breadth-First Search
        
        Returns the path as a list of directions among
        { Direction.left, Direction.right, Direction.up, Direction.down }
        
        Useful methods:
        - state.is_goal_state(): Returns true if the state is a valid goal state.
        - state.get_successor_states(): Returns all states reachable from the state as a list of triplets (state, direction, cost).
        """

        # *** YOUR CODE HERE ***
        # Base your work in the above DFS implementation
        open_list = [[ (initial_state, None) ]] # A state is a pair (board, direction)
        closed_list = set([initial_state]) # keep already explored positions

        while open_list:
            # Get the path at the top of the stack (pop() returns the last item of the list)
            current_path = open_list.pop(0)
            # Get the last place of that path
            current_state, current_direction = current_path[-1]
            # Check if we have reached the goal
            if current_state.is_goal_state():
                # remove the start point and return only the directions.
                return (list (map(lambda x : x[1], current_path[1:])))
            else:
                # Check where we can go from here
                next_steps = current_state.get_successor_states()
                # Add the new paths (one step longer) to the stack
                for state, direction, weight in next_steps:
                    # do not add already explored states
                    if state not in closed_list:
                        # add at the end of the list
                        closed_list.add(state)
                        open_list.append( (current_path + [ (state, direction) ]) )
        return []

 #  ______                               _                  ___  
 # |  ____|                             (_)                |__ \ 
 # | |__    __  __   ___   _ __    ___   _   ___    ___       ) |
 # |  __|   \ \/ /  / _ \ | '__|  / __| | | / __|  / _ \     / / 
 # | |____   >  <  |  __/ | |    | (__  | | \__ \ |  __/    / /_ 
 # |______| /_/\_\  \___| |_|     \___| |_| |___/  \___|   |____|

class UCS( Agent ):
    def search( self, initial_state ):
        """ Uniform-Cost Search.

        It returns the path as a list of directions among
        { Direction.left, Direction.right, Direction.up, Direction.down }
        """

        # use a priority queue with the minimum queue.
        from utils import PriorityQueue
        open_list = PriorityQueue()
        open_list.push([(initial_state, None)], 0) # a state is a pair (boad, direction)
        closed_list = set([initial_state]) # keep already explored positions

        while not open_list.isEmpty():
            # Get the path at the top of the queue
            current_path, cost = open_list.pop()
            # Get the last place of that path
            current_state, current_direction = current_path[-1]
            # Check if we have reached the goal
            if current_state.is_goal_state():
                return (list (map(lambda x : x[1], current_path[1:])))
            else:
                # Check were we can go from here
                next_steps = current_state.get_successor_states()
                # Add the new paths (one step longer) to the queue
                for state, direction, weight in next_steps:
                    # Avoid loop!
                    if state not in closed_list:
                        closed_list.add(state)
                        open_list.push((current_path + [ (state, direction) ]), cost + weight)
        return []

class GBFS( Agent ):

    def search( self, initial_state ):
        """ Greedy Best First Search.

        Returns the path as a list of directions among
        { Direction.left, Direction.right, Direction.up, Direction.down }
        
        Useful methods:
        - state.is_goal_state(): Returns true if the state is a valid goal state.
        - state.get_successor_states(): Returns all states reachable from the specified state as a list of triplets (state, direction, cost)
        - state.heuristic(): Returns the heuristic value for the specified state.
        """

        # *** YOUR CODE HERE ***
        # Base your work in the above UCS implementation
        from utils import PriorityQueue
        open_list = PriorityQueue()
        open_list.push([(initial_state, None)], initial_state.heuristic()) # a state is a pair (boad, direction)
        closed_list = set([initial_state]) # keep already explored positions

        while not open_list.isEmpty():
            # Get the path at the top of the queue
            current_path, _ = open_list.pop()
            # Get the last place of that path
            current_state, current_direction = current_path[-1]
            # Check if we have reached the goal
            if current_state.is_goal_state():
                return (list (map(lambda x : x[1], current_path[1:])))
            else:
                # Check were we can go from here
                next_steps = current_state.get_successor_states()
                # Add the new paths (one step longer) to the queue
                for state, direction, weight in next_steps:
                    # Avoid loop!
                    if state not in closed_list:
                        closed_list.add(state)
                        open_list.push((current_path + [ (state, direction) ]), state.heuristic())
        return []

 #  ______                               _                  ____  
 # |  ____|                             (_)                |___ \ 
 # | |__    __  __   ___   _ __    ___   _   ___    ___      __) |
 # |  __|   \ \/ /  / _ \ | '__|  / __| | | / __|  / _ \    |__ < 
 # | |____   >  <  |  __/ | |    | (__  | | \__ \ |  __/    ___) |
 # |______| /_/\_\  \___| |_|     \___| |_| |___/  \___|   |____/ 

class ASS( Agent ):
    def search( self, initial_state ):
        """ A Star Search.

        It returns the path as a list of directions among
        { Direction.left, Direction.right, Direction.up, Direction.down }

        Useful methods:
        - state.is_goal_state(): Returns true if the state is a valid goal state.
        - state.get_successor_states(): Returns all states reachable from the specified state as a list of triplets (state, direction, cost)
        - state.heuristic(): Returns the heuristic value for the specified state.

        """
        
        # *** YOUR CODE HERE ***
        from utils import PriorityQueue
        open_list = PriorityQueue()
        open_list.push([(initial_state, None)], initial_state.heuristic()) # a state is a pair (boad, direction)
        closed_list = set([initial_state]) # keep already explored positions

        while not open_list.isEmpty():
            # Get the path at the top of the queue
            current_path, cost = open_list.pop()
            # Get the last place of that path
            current_state, current_direction = current_path[-1]
            # Check if we have reached the goal
            if current_state.is_goal_state():
                return (list (map(lambda x : x[1], current_path[1:])))
            else:
                # Check were we can go from here
                next_steps = current_state.get_successor_states()
                # Add the new paths (one step longer) to the queue
                for state, direction, weight in next_steps:
                    # Avoid loop!
                    if state not in closed_list:
                        closed_list.add(state)
                        open_list.push((current_path + [ (state, direction) ]), state.heuristic() + cost + weight)
        return []

 #  ______                               _                  _  _   
 # |  ____|                             (_)                | || |  
 # | |__    __  __   ___   _ __    ___   _   ___    ___    | || |_ 
 # |  __|   \ \/ /  / _ \ | '__|  / __| | | / __|  / _ \   |__   _|
 # | |____   >  <  |  __/ | |    | (__  | | \__ \ |  __/      | |  
 # |______| /_/\_\  \___| |_|     \___| |_| |___/  \___|      |_|  

class IDS( Agent ):
    MAX_PATH_LENGTH = 500 # Found in literature
    def search( self, initial_state ):
        """ Iterative Deepening Search.

        Returns the path as a list of directions among
        { Direction.left, Direction.right, Direction.up, Direction.down }

        Useful methods:
        - state.is_goal_state(): Returns true if the state is a valid goal state.
        - state.get_successor_states(): Returns all states reachable from the specified state as a list of triplets (state, direction, cost)
        - state.heuristic(): Returns the heuristic value for the specified state.
        """

        # *** YOUR CODE HERE ***
        for depth in range(self.MAX_PATH_LENGTH + 1):
            result = self.depth_limited_search(initial_state, depth, set())
            if result is not None:
                return result
        return None
    

    def depth_limited_search(self, state, limit, visited):
        if state.is_goal_state():
            return []

        if limit == 0:
            return None

        visited.add(state)

        for next_state, direction, cost in state.get_successor_states():
            if next_state not in visited:
                result = self.depth_limited_search(next_state, limit - 1, visited)
                if result is not None:
                    return [direction] + result

        visited.remove(state)
        return None

 #  ______                               _                  _____ 
 # |  ____|                             (_)                | ____|
 # | |__    __  __   ___   _ __    ___   _   ___    ___    | |__  
 # |  __|   \ \/ /  / _ \ | '__|  / __| | | / __|  / _ \   |___ \ 
 # | |____   >  <  |  __/ | |    | (__  | | \__ \ |  __/    ___) |
 # |______| /_/\_\  \___| |_|     \___| |_| |___/  \___|   |____/ 
class IDASS( Agent ):
    MAX_PATH_LENGTH = 500 # Found in literature
    def search( self, initial_state ):
        """ Iterative deepening A*
        
        Returns the path as a list of directions among
        { Direction.left, Direction.right, Direction.up, Direction.down }.

        Useful methods:
        - state.is_goal_state(): Returns true if the state is a valid goal state.
        - state.get_successor_states(): Returns all states reachable from the specified state as a list of triplets (state, direction, cost)
        - state.heuristic(): Returns the heuristic value for the specified state.
        """

        # *** YOUR CODE HERE ***
        threshold = initial_state.heuristic()
        while threshold < float('inf'):
            result, new_threshold = self.depth_limited_search(initial_state, 0, threshold, set())
            if result is not None:
                return result
            if new_threshold == float('inf'):
                return None
            threshold = new_threshold
        return None

    def depth_limited_search(self, state, g, threshold, visited):
        f = g + state.heuristic()
        if f > threshold:
            return None, f
        if state.is_goal_state():
            return [], None
        visited.add(state)
        next_threshold = float('inf')
        for next_state, direction, cost in state.get_successor_states():
            if next_state not in visited:
                result, new_threshold = self.depth_limited_search(next_state, g + cost, threshold, visited)
                if result is not None:
                    return [direction] + result, None
                if new_threshold is not None:
                    next_threshold = min(next_threshold, new_threshold)
        visited.remove(state)
        return None, next_threshold

