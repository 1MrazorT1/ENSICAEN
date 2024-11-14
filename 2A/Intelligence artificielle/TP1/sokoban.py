#! /usr/bin/env python
# -*- coding: utf-8; mode: python -*-

# ENSICAEN
# École Nationale Supérieure d'Ingénieurs de Caen
# 6 Boulevard Maréchal Juin
# F-14050 Caen Cedex France
#
# Artificial Intelligence 2I1AE1

# @file sokoban.py
#
# @author Régis Clouard

import os
import sys
import time
from utils import TimeoutFunctionException, TimeoutFunction
from sokobanframe import SokobanFrame

def search_path( sokoban, agent ):
    print("Searching.. "),
    sys.stdout.flush()
    starttime = time.time()
    timed_func = TimeoutFunction(agent.search, 1000)
    try:
        path = timed_func(sokoban.get_start_state())
        print("Done.")
    except TimeoutFunctionException as ex:
        print("Error #1: time out", ex)
        path = []
    if path:
        if sokoban.display_path(path):
            print("Statistics:")
            print('    - Time                    : %.1f s' % (time.time() - starttime))
            print("    - Number of explored nodes: %3d" % SokobanFrame.number_of_explored_nodes)
            print("    - Number of moves         : %3d\n" % len(path))
        else:
            sokoban.game_over()
            print("FAILED : Inconsistant solution.")
    else:
        sokoban.game_over()
        print("FAILED: No solution.")

def run_agent( agent, gridfile, framerate, function = None ):
    """ The real main. """

    number_of_explored_nodes = 0
    if not agent: # by hand
        sokoban = SokobanFrame(gridfile, agent, function, framerate)
        sokoban.bind_all("<Key>", sokoban.key)
        sokoban.mainloop()
    else:
        sokoban = SokobanFrame(gridfile, agent, function, framerate)
        sokoban.after(1500, search_path, sokoban, agent)
        sokoban.mainloop()

def default(str):
    return str + ' [Default: %default]'

def read_command( argv ):
    """ Processes the command used to run Sokoban from the command line. """
    from optparse import OptionParser
    usageStr = """
    USAGE:      python sokoban.py <options>
    EXAMPLES:   python sokoban.py --agent DFS --grid grid1.txt
                OR  python sokoban.py -a DFS -g grid1.txt
                    - solve grid1 with the naive path finder
    """
    parser = OptionParser(usageStr)
    
    parser.add_option('-a', '--agent', dest = 'agent',
                      help = default('the agent to use'),
                      metavar = 'TYPE', default = None)
    parser.add_option('-g', '--grid', dest = 'grid',
                      help = 'The grid to solve', default = 'grid1.txt')
    parser.add_option('-f', '--function', dest = 'function',
                      help = 'The heuristic to use', default = None)
    parser.add_option('-t', '--framerate', dest = 'framerate',
                      help=default('Maximum frame rate time'), default = 200)
    
    options, otherjunk = parser.parse_args(argv)

    if len(otherjunk) != 0:
        raise Exception('Command line input not understood: ' + str(otherjunk))
    args = dict()
    
    args['gridfile'] = "puzzles/" + options.grid
    args['framerate'] = int(options.framerate)
    if not options.agent:
        args['agent'] = None
        return args
    try:
        module = __import__('agents')
        if options.agent in dir(module):
            agent = getattr(module, options.agent)
            args['agent'] = agent()
        else:
            raise Exception('Unknown agent: ' + options.agent)
    except ImportError:
        raise Exception('No file agents.py')
    
    # Choose a heuristic
    if options.function != None:
        try:
            module = __import__('agents')
            if options.function in dir(module):
                args['function'] = getattr(module, options.function)
            else:
                raise Exception('Unknown heuristic: ' + options.function)
        except ImportError:
            raise Exception('No file agents.py')
    return args

if __name__ == '__main__':
    """ The main function called when sokoban.py is run
    from the command line:

    > python sokoban.py

    See the usage string for more details.

    > python sokoban.py --help
    > python sokoban.py -h """
    args = read_command( sys.argv[1:] ) # Get game components based on input
    print("\n-------------------------------------------------------")
    os.environ['PYTHONHASHSEED']='0'
    current_seed = os.environ.get("PYTHONHASHSEED")
    for arg in sys.argv:
        print(arg, end=" ")
    print("\n-------------------------------------------------------")
    run_agent( **args )
