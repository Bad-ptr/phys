
#coding=UTF-8

from math import *
from kmp import *

#class Vector:
#    def __init__( self, coord = ( 0.0, 0.0 ) ):
#        self.x, self.y = coord

Vector2 = kmvect3f

class Vector2f:
    """
    Mega Vector class
    +---+---+
    | x | y |
    +---+---+
    """
    def __init__( self, c = ( 0.0, 0.0 ) ):
        """
        x - x coord
        y - y coord
        """
        self.x = c[0]
        self.y = c[1]

    def __copy__( self ):
        return Vector2( self )

    def __repr__( self ):
        return "Vector2( %.2f, %.2f )" % ( self.x, self.y )

    def __str__( self, pfx = "Vector", add = "" ):
        return ( pfx + "( " + repr( self.x ) + ", " + repr( self.y )
                + add + " )" )

    def __eq__( self, other ):
        return self.x == other[0] and self.y == other[1]

    def __neq__( self, other ):
        return not self.__eq__( other )

    def __len__( self ):
        return 2

    def __getitem__( self, k ):
        if( k > 1 ):
            return 1.0
        return ( self.x, self.y )[k]

    def __setitem__( self, k, s ):
        if k == 0:
            self.x = s
        elif k == 1:
            self.y = s
        else:
            raise Exception("Invalid Key")

    def __iter__( self ):
        return iter( ( self.x, self.y ) )

    def __neg__( self ):
        return Vector2( (  -self.x, -self.y  ) )

    copy = __call__ = __copy__

    def sset( self, x = 0.0, y = 0.0 ):
        self.x = x
        self.y = y

    def vadd( self, other ):
        return Vector2( ( self.x + other[0], self.y + other[1] ) )

    def vsub(  self, other ):
        return Vector2( ( self.x - other[0], self.y - other[1] ) )

    def inv( self ):
        return self.__neg__()

    def mul( self, mm = 1 ):
        return Vector2( ( self.x * mm, self.y * mm ) )

    def div( self, d = 1 ):
        return Vector2( ( self.x / d, self.y / d ) )

    def vmul( self, other ):
        return Vector2( ( self.x * other[0], self.y * other[1] ) )

    def vmmul( self, other ):
        return Vector2( ( self.x * other[0] + self.y * other[1],
                          self.y * other[0] + self.x * other[1] ) )

    def dot( self, other ):
        return self.x * other[0] + self.y * other[1]

    def cross( self ):
        return Vector2( ( self.y, -self.x ) )

    def mag( self ):
        return sqrt( self.x**2 + self.y**2 )

    def norm( self ):
        m = self.Len()
        if m > 0.0:
            return self.sDiv( m )
        else:
            return Vector2()


class DFTR():
    def __init__( self ):
        self.p0 = Vector2( (  0.0, 250.0  ) )
        self.p1 = Vector2( (  250.0, 250.0  ) )
        self.p2 = Vector2( (  250.0, 0.0  ) )
        self.p3 = Vector2( (  0.0, 0.0  ) )


class Matrix3x3:
    """
    Matrix3x3 class
    +-----+-----+-----+
    | m11 | m12 | m13 |
    +-----+-----+-----+
    | m21 | m22 | m23 |
    +-----+-----+-----+
    | m31 | m32 | m33 |
    +-----+-----+-----+
    """
    def __init__( self, m = ( 1.0, 0.0, 0.0,
                              0.0, 1.0, 0.0,
                              0.0, 0.0, 1.0 ) ):
        """
        Matrix Ident by Init()
        """
        self.m11, self.m12, self.m13 = m[0], m[1], m[2]
        self.m21, self.m22, self.m23 = m[3], m[4], m[5]
        self.m31, self.m32, self.m33 = m[6], m[7], m[8]

    def __copy__( self ):
        return Matrix3x3( self )

    def __repr__( self ):
        return "Matrix3x3( ( %.2f, %.2f, %.2f,\n\t \
        %.2f, %.2f, %.2f,\n\t \
        %.2f, %.2f, %.2f ) )" % (self.m11, self.m12, self.m13,
        self.m21, self.m22, self.m23,
        self.m31, self.m32, self.m33 )

    def __eq__( self, m ):
        return ( self.m11 == m[0] and self.m12 == m[1] and self.m13 == m[2]
             and self.m21 == m[3] and self.m22 == m[4] and self.m23 == m[5]
             and self.m31 == m[6] and self.m32 == m[7] and self.m33 == m[8] )

    def __neq__( self, m ):
        return not self.__eq__( m )

    def __len__( self ):
        return 9

    def __getitem__( self, k ):
        return ( self.m11, self.m12, self.m13,
                 self.m21, self.m22, self.m23,
                 self.m31, self.m32, self.m33 )[k]

    def __setitem__( self, k, s ):
        L = self[:]
        L[k] = s
        ( self.m11, self.m12, self.m13,
          self.m21, self.m22, self.m23,
          self.m31, self.m32, self.m33 ) = L

    def __iter__( self ):
        return iter( ( self.m11, self.m12, self.m13,
                       self.m21, self.m22, self.m23,
                       self.m31, self.m32, self.m33 ) )

    copy = __call__ = __copy__

    def identity( self ):
        return Matrix3x3()

    def det( self ):
        _m11, _m12, _m13 = self.m11, self.m12, self.m13
        _m21, _M22, _m23 = self.m21, self.m22, self.m23
        _m31, _m32, _m33 = self.m31, self.m32, self.m33

        return (   _m11 * _m22 * _m33
                 - _m11 * _m32 * _m23
                 + _m21 * _m32 * _m13
                 - _m21 * _m12 * _m33
                 + _m31 * _m12 * _m23
                 - _m31 * _m22 * _m13 )

    def trans( self ):
        _m11, _m12, _m13 = self.m11, self.m12, self.m13
        _m21, _m22, _m23 = self.m21, self.m22, self.m23
        _m31, _m32, _m33 = self.m31, self.m32, self.m33

        return Matrix3x3( _m11, _m21, _m31,
                          _m12, _m22, _m32,
                          _m13, _m23, _m33 )

    def inv( self ):
        d = self.Det()
        if d == 0:
            return 0

        _m11, _m12, _m13 = self.m11, self.m12, self.m13
        _m21, _m22, _m23 = self.m21, self.m22, self.m23
        _m31, _m32, _m33 = self.m31, self.m32, self.m33

        return Matrix3x3( ( _m22 * _m33 - _m23 * _m32 ) / d,
                         -( _m12 * _m33 - _m13 * _m32 ) / d,
                          ( _m12 * _m23 - _m13 * _m22 ) / d,

                         -( _m21 * _m33 - _m23 * _m31 ) / d,
                          ( _m11 * _m33 - _m13 * _m31 ) / d,
                         -( _m11 * _m23 - _m13 * _m21 ) / d,

                          ( _m21 * _m32 - _m22 * _m31 ) / d,
                         -( _m11 * _m32 - _m12 * _m31 ) / d,
                          ( _m11 * _m22 - _m12 * _m21 ) / d )

    def madd( self, m ):
        _m11, _m12, _m13 = self.m11, self.m12, self.m13
        _m21, _m22, _m23 = self.m21, self.m22, self.m23
        _m31, _m32, _m33 = self.m31, self.m32, self.m33

        return Matrix3x3( _m11 + m[0], _m12 + m[1], _m13 + m[2],
                          _m21 + m[3], _m22 + m[4], _m23 + m[5],
                          _m31 + m[6], _m32 + m[7], _m33 + m[8] )

    def msub( self, m ):
        _m11, _m12, _m13 = self.m11, self.m12, self.m13
        _m21, _m22, _m23 = self.m21, self.m22, self.m23
        _m31, _m32, _m33 = self.m31, self.m32, self.m33

        return Matrix3x3( _m11 - m[0], _m12 - m[1], _m13 - m[2],
                          _m21 - m[3], _m22 - m[4], _m23 - m[5],
                          _m31 - m[6], _m32 - m[7], _m33 - m[8] )

    def mul( self, s ):
        _m11, _m12, _m13 = self.m11, self.m12, self.m13
        _m21, _m22, _m23 = self.m21, self.m22, self.m23
        _m31, _m32, _m33 = self.m31, self.m32, self.m33

        return Matrix3x3( _m11 * s, _m12 * s, _m13 * s,
                          _m21 * s, _m22 * s, _m23 * s,
                          _m31 * s, _m32 * s, _m33 * s )

    def vmul( self, v ):
        _m11, _m12, _m13 = self.m11, self.m12, self.m13
        _m21, _m22, _m23 = self.m21, self.m22, self.m23
        _m31, _m32, _m33 = self.m31, self.m32, self.m33

        return Vector2( ( _m11 * v[0] + _m21 * v[1] + _m31 * v[2],
                          _m12 * v[0] + _m22 * v[1] + _m32 * v[2],
                          _m13 * v[0] + _m23 * v[1] + _m33 * v[2] ) )

    def mmul( self, m ):
        _m11, _m12, _m13 = self.m11, self.m12, self.m13
        _m21, _m22, _m23 = self.m21, self.m22, self.m23
        _m31, _m32, _m33 = self.m31, self.m32, self.m33

        return Matrix3x3( _m11 * m[0], _m12 * m[1], _m13 * m[2],
                          _m21 * m[3], _m22 * m[4], _m23 * m[5],
                          _m31 * m[6], _m32 * m[7], _m33 * m[8] )

    def div( self, s ):
        _m11, _m12, _m13 = self.m11, self.m12, self.m13
        _m21, _m22, _m23 = self.m21, self.m22, self.m23
        _m31, _m32, _m33 = self.m31, self.m32, self.m33

        return Matrix3x3( _m11 / s, _m12 / s, _m13 / s,
                          _m21 / s, _m22 / s, _m23 / s,
                          _m31 / s, _m32 / s, _m33 / s )



class Line:
    """
    Line class is cool
    """
    def __init__( self, p0 = Vector2(), p1 = Vector2( ( 1.0, 1.0 ) ) ):
        self.Set( p0, p1 )

    def Set( self, p0 = Vector2(), p1 = Vector2( ( 1.0, 1.0 ) ) ):
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
        return Line( p0 = self.p0, p1 = Vector2( ( -self.p1.y, self.p1.x ) ) )

class Rect:
    """
    Rect is a very cool class
    """
    def __init__( self, p0 = Vector2(), p1 = Vector2( ( 1.0, 0.0 ) ),
                  p2 = Vector2( ( 0.0, 1.0 ) ), p3 = Vector2( ( 1.0, 1.0 ) ) ):
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
    def __init__( self, p0 = Vector2(), r = Vector2( ( 1.0, 1.0 ) ) ):
        """
        p0 - origin of Circle
        r - radi of Circle
        """
        self.p0 = p0
        self.r = r


def mkrv( rad = 0.0 ):
    return Vector2( ( cos( rad ), sin( rad ) ) )

def vrv( v, rv ):
    m = v.Len()
    return v.Norm().vMul( rv ).sMul( m )

def vrot( v = Vector2(), rad = 0.0 ):
    rcos = cos( rad )
    rsin = sin( rad )
    return Vector2( ( v.x * rcos + v.y * rsin, v.x * -rsin + v.y * rcos ) )

def vrotap( v = Vector2(), p = Vector2(), rad = 0.0 ):
    nv = v.Vsub( p )
    rcos = cos( rad )
    rsin = sin( rad )
    return Vector2( ( nv.x * rcos + nv.y * rsin,
                   nv.x * -rsin + nv.y * rcos ) ).Vadd( p )
