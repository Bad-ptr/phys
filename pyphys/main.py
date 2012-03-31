#!/usr/bin/env python
# coding=UTF8


import sys

from kpsim import *
from kpmath import *
from kphys import *
from kpgrphx import *

import threading

sim = Simulation()

gf = eGforce( -9.8 )
sim.Rands( 100 )
#gf = Gforce( 10 )
sim.AddForce1b( gf )
ff = Fforce( 0.6, 0.3 )
sim.AddForce1b( ff )

p5 = Particle( mass = 3, coord = Vector2( ( 80.0, 35.0 ) ),
        vel = Vector2( ( 3.5, 13.0 ) ), size = 3,
        color = ( 255, 100, 100 ) )

p2 = Particle( mass = 10, coord = Vector2( ( 50.0, 35.0 ) ),
        vel = Vector2( ( -1.0, 10.0 ) ), size = 10,
        color = ( 0, 100, 255 ) )

p3 = Particle( mass = 1, coord = Vector2( ( 30.0, 35.0 ) ),
        vel = Vector2( ( -2.2, 25.4 ) ), size = 1,
        color = ( 100, 100, 100 ) )

p4 = Particle( mass = 2, coord = Vector2( ( 410.0, 350.0 ) ),
        vel = Vector2( ( 0.0, 1.0 ) ), size = 2,
        color = ( 200, 200, 200 ) )
#p4.oldcoord = Vector2( (  410.0, 349.5  ) )

p1 = Particle( mass = 100, coord = Vector2( ( 525, 350.0 ) ),
        vel = Vector2( ( 0.0, 0.0 ) ), size = 50,
        color = ( 200, 200, 200 ) )

sim.AddBody( p1 )
sim.AddBody(p2)
sim.AddBody(p3)
sim.AddBody( p4 )
sim.AddBody(p5)

#sim.Rands( randint( 2, 6 ) )

def foo( dt ):

    print('FPS is %f', pyglet.clock.get_fps())
    #sim.Solve( dt )

def bar( dt ):
    sim.Solve( dt )

def baz( dt ):
    sim.colg.dsubd( 15, 3 )


class mainloopc( threading.Thread ):
    def __init_( self ):
        threading.Thread.__init__( self )
    def run( self ):
        window = gInit()
        handlevents( window, sim )
        #fschedule( foo, 0.01 )
        fschedule( bar, 0.05 )
        fschedule( baz, 3 )
        rRun()

def main():
    bckgrnd = mainloopc()
    bckgrnd.start()

if __name__ == '__main__':
    main()
