
#coding=UTF-8

from math import *
import numpy as np

#class Vector:
#    def __init__( self, coord = ( 0.0, 0.0 ) ):
#        self.x, self.y = coord


class Vector:
    """
    Mega Vector class
    """
    def __init__( self, coord = np.float_( [ 0.0, 0.0 ] ) ):
        """
        x - x coord
        y - y coord
        """
        self.xy = coord

    def __str__( self, pfx = "Vector", add = "" ):
        return ( pfx + "( " + repr( self.x ) + ", " + repr( self.y )
                + add + " )" )

    def Set( self, x = 0.0, y = 0.0 ):
        self.xy = np.float_( [ x, y ] )

    def Vadd( self, other ):
        return Vector( self.xy + other.xy )

    def Vsub(  self, other ):
        return Vector( self.xy - other.xy )

    def Inv( self ):
        return Vector( -self.xy )

    def Mul( self, mm = 1 ):
        return Vector( self.xy * mm )

    def Div( self, d = 1 ):
        return Vector( self.xy / d )

    def Vmul( self, other ):
        return Vector(  self.xy * other.xy )

    def Dot( self, other ):
        return np.vdot( self.xy, other.xy )

    def Len( self ):
        #return np.sqrt( np.square( self.xy ).sum() )
        return np.linalg.norm( self.xy, ord = None )

    def Norm( self ):
        len = self.Len()
        if len > 0.0:
            return self.Div( len )
        else:
            return Vector( np.float_( [ 0.0, 0.0 ] ) )

    def Eql( self, other ):
        if self.xy == other.xy:
            return True
        return False

    def Copy( self, other ):
        self.xy = other.xy

    def rCopy( self ):
        return Vector( self.xy )


class Line:
    """
    Line class is cool
    """
    def __init__( self, p0 = Vector(), p1 = Vector( 1.0, 1.0 ) ):
        self.Set( p0, p1 )

    def Set( self, p0 = Vector(), p1 = Vector( 1.0, 1.0 ) ):
        """
        p0 - begining of line
        p1 - end of line
        """
        self.p0 = p0
        self.p1 = p1

    def __str__( self, pfx = "Line", add = "" ):
        return ( pfx + "( " + str( self.p0 ) + ", " + str( self.p1 )
                 + add + " )" )

    def Len( self ):
        d = self.p1.Vsub( p0 )
        return d.Len()

    def Dir( self ):
        d = self.p1.Vsub( p0 )
        return d.Norm()

    def Perp( self ):
        return Line( p0 = self.p0, p1 = Vector( -self.p1.y, self.p1.x ) )

class Rect:
    """
    Rect is a very cool class
    """
    def __init__( self, p0 = Vector(), p1 = Vector( 1.0, 0.0 ),
                  p2 = Vector( 0.0, 1.0 ), p3 = Vector( 1.0, 1.0 ) ):
        self.p0 = p0
        self.p1 = p1
        self.p2 = p2
        self.p3 = p3

    def __str__( self, pfx = "Rect", add = "" ):
        return ( pfx + "( " + str( self.p0 ) + ", " + str( self.p1 )
                 + add + " )" )

class Circle:
    """
    Circle is the most coolest class
    """
    def __init__( self, p0 = Vector(), r = Vector( 1.0, 1.0 ) ):
        """
        p0 - origin of Circle
        r - radi of Circle
        """
        self.p0 = p0
        self.r = r

