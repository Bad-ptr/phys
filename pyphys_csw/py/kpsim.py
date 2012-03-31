#coding=UTF8


from math import *
from random import randint, uniform

from kpmath import *
from kphys import *
from kpcollide import *


class Simulation( object ):

    def __init__( self, bounds = Vector2( ( 800.0, 600.0 ) ), bodylist = [], force1bl = [],
            force2bl = [], springl = [], dt = 0.01 ):
        self.bodyes, self.forces1b, self.forces2b, self.springs = ( bodylist,
                force1bl, force2bl, springl )
        self.border = []
        self.dt = dt
        self.uf = Vector2()
        self.colg = CollGridn( Vector2(), bounds, 0 )
        self.dftr = DFTR()
        self.ab, self.rmb = [], []

    def __str__( self, pfx = "Simulation", add = "" ):
        ret = "bodyes = ( "
        for b in self.bodyes:
            ret += str( b ) + ",\n"
        ret += ")\nforces1b = ( "
        for f1b in self.forces1b:
            ret += str( f1b ) + ",\n"
        ret += ")\nforces2b = ( "
        for f2b in self.forces2b:
            ret += str( f2b ) + ",\n"
        ret += ")\nsprings = ( "
        for s in self.springs:
            ret += str( s ) + ",\n"
        ret += ")\ndt = " + repr( self.dt ) + "\n"
        return ret

    def SetBounds( self, bounds ):
        self.colg.resize( bounds )

    def AddBody( self, body ):
        self.bodyes.append( body )

    def AddBodyes( self, bl = [] ):
        for b in bl:
            self.AddBody( b )

    def AddForce1b( self, force1b ):
        self.forces1b.append( force1b )

    def AddForce2b( self, force2b ):
        self.forces2b.append( force2b )

    def AddForces1b( self, f1bl ):
         for f1b in f1bl:
            self.AddForce1b( f1b )

    def AddForces2b( self, f2bl ):
        for f2b in f2bl:
            self.AddForce2b( f2b )

    def AddSpring( self, spring ):
        self.springs.append( spring )

    def AddSprings( self, springl ):
        for s in springl:
            self.AddSpring( self, s )

    def SaveToFile( self, filename ):
        f = open( filename, 'w' )
        s = str( self )
        f.write( s )
        f.close()

    def LoadFromFile( self, filename ):
        f = open( filename, 'r' )
        for line in f:
            pass
        f.close()

    def Clear ( self ):
        ( self.bodyes, self.forces1b, self.forces2b, self.springs, self.rmb,
                self.ab ) = ( [], [], [], [], [], [] )

    def Rands( self, count ):
        self.Clear()
        for qq in range( count ):
            m = uniform( 1, 50 )
            s = m / 2
            #if s < 1: s = 1
            #r = int(sqrt(m*10)/2)
            mv = m * 0.3
            ve = Vector2( ( uniform( -mv, mv ),uniform( -mv, mv ) ) )
            ncoord = Vector2( ( randint( 10, 600 )*1.0, randint( 10, 500 )*1.0 ) )
            ncolor = ( randint( 100, 255 ), randint( 100, 255 ),
                    randint( 100, 255 ) )
            self.AddBody( Particle( coord = ncoord, mass = m, vel =
                ve, size = s, color = ncolor ) )

    def MoveCoords( self, p = Vector2(), bid = 0 ):
        for b in self.bodyes:
            b.coord = (
                b.coord.vSub( self.bodyes[bid].coord ).vAdd(
                    Vector2( p ) ) )
            b.oldcoord = (
                b.oldcoord.vSub( self.bodyes[bid].coord ).vAdd(
                    Vector2( p ) ) )

    def Solve( self, dt = 0.01 ):

        #CompFsl( ( self.forces, self.springs ), self.bodyes )
        moupd( self.bodyes, self.forces1b, (self.forces2b,[]), self.springs )

        self.bodyes[0].force = self.bodyes[0].force.vAdd( self.uf )
        #print self.bodyes[0].coord.x, self.bodyes[0].coord.y, self.bodyes[0].vel.x, self.bodyes[0].vel.y

        #self.bodyes[1].force = self.bodyes[1].force.vAdd( self.uf )
        self.uf = Vector2()
        Euler( self.bodyes, 0.05 )

        #Midpoint( self.bodyes, self.forces1b, self.forces2b, self.springs,
        #        self.dt )
        #RK4( self.bodyes, self.forces1b, self.forces2b, self.springs, self.dt )

        #K4( self.bodyes, (self.forces, self.springs ), dt )

        #self.bodyes[0].coord = self.bodyes[0].coord.vAdd( self.uf )
        #self.bodyes[1].coord = self.bodyes[1].coord.vAdd( self.uf )
        #self.uf = Vector2()
        #Verlet( self.bodyes, self.dt )

        #self.colg.dsubd( 3, 3 )
        #print self.colg.bl
        #ubl = self.colg.lupdate()
        #for p in ubl:
        #    self.colg.locate( p )
        #self.border = fborder( self.colg, self.colg.p1 )

        collideP( self.colg )

        wcollide( self.colg )

        #wcollideborder( self.border )
        #collideP( self.colg )
        #wcollide( self.border, self.bounds )
        #exit()

        self.colg.clear()

        ##self.colg.update()

        for p in self.bodyes:
            self.colg.locate( p )

        #self.MoveCoords( 525, 350 )

        #for b in set( self.rmb ): self.bodyes.remove( b )
        #for b in set( self.ab ): self.bodyes.append( b )
        #self.rmb, self.ab = [], []
