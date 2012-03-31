
#coding=UTF-8

from kpmath import *
from kphys import *


class CollGridn( object ):
    def __init__( self, p0 = Vector2( ( 0.0, 0.0 ) ),
                  p1 = Vector2( ( 100.0, 100.0) ), sl = 0 ):
        self.p0 = p0
        self.p1 = p1
        self.pc = self.p0.vAdd( self.p1 ).sMul( 0.5 )
        self.bl = []
        self.numb = 0
        self.childs = []
        self.csubd( sl )

    def mkFromOld( self, oldcg, p1 = Vector2( ( 100.0, 100.0 ) ), sl = 0 ):
        self.p0 = oldcg.p0
        self.p1 = p1
        self.bl = oldcg.bl
        self.csubd( sl )

    def resize( self, p1 = Vector2( ( 100.0, 100.0 ) ) ):

        if self.childs != []:
            self.pc = self.p0.vAdd( self.p1.vSub( self.p0 ).sMul( 0.5 ) )

            self.childs[0].p0 = self.p0
            self.childs[0].resize( self.pc )

            self.childs[1].p0 = self.pc
            self.childs[1].resize( self.p1 )

            self.childs[2].p0 = Vector2( ( self.p0.x, self.pc.y ) )
            self.childs[2].resize( Vector2( ( self.pc.x, self.p1.y ) ) )

            self.childs[3].p0 = Vector2( ( self.pc.x, self.p0.y ) )
            self.childs[3].resize( Vector2( ( self.p1.x, self.pc.y ) ) )

    def tostr( self, ret = "" ):
        ret += ("CGNode: x0 = "# + repr( self.p0[0]) + ", y0 = "
                + repr( self.p0[1] ) + "; x1 = " + repr( self.p1[0] )
                + ", y1 = " + repr( self.p1[1] ) ) + "\n"
        for ch in self.childs:
            ch.tostr( ret )
        return ret

    def __str__( self ):
        return self.tostr()

    def econtain( self, p ):
        if ( ( p.coord.x - p.size > self.p0.x ) and
            ( p.coord.x + p.size < self.p1.x ) ):
            if ( ( p.coord.y - p.size > self.p0.y ) and
                ( p.coord.y + p.size < self.p1.y ) ):
                return True
        return False

    def contain( self, p ):
        if ( ( p.coord.x + p.size > self.p0.x ) and
            ( p.coord.x - p.size < self.p1.x ) ):
            if ( ( p.coord.y + p.size > self.p0.y ) and
                ( p.coord.y - p.size < self.p1.y ) ):
                return True
        return False

    def tnumb( self ):
        #ret = len( self.bl )
        ret = self.numb
        for ch in self.childs:
            ret += ch.tnumb()
        return ret

    def csubd( self, l = 0 ):
        if l <= 0:
            return

        l -= 1

        if self.childs == []:
            chs = [ CollGridn ( self.p0, self.pc, l ),
                    CollGridn ( self.pc, self.p1, l ),
                    CollGridn ( Vector2( ( self.p0.x, self.pc.y ) ),
                                Vector2( ( self.pc.x, self.p1.y ) ), l ),
                    CollGridn ( Vector2( ( self.pc.x, self.p0.y ) ),
                                Vector2( ( self.p1.x, self.pc.y ) ), l ) ]

            self.childs += chs
        else:
            for ch in self.childs:
                ch.csubd( l )


    def dsubd( self, mb = 15, l = 0 ):
        # lbl = len( self.bl )
        # if l <= 0:
        #     return lbl
        # l -= 1
        # if self.childs == []:
        #     if lbl > mb-1:
        #         self.csubd( 1 )
        #     return lbl
        # else:
        #     t = 0
        #     for ch in self.childs:
        #         t += ch.dsubd( mb, l )
        # if t < mb:
        #     self.childs = []
        # return lbl
        if l <= 0:
            return
        l -= 1
        if self.tnumb() > mb - 1:
            for ch in self.childs:
                ch.dsubd( mb, l )
            self.csubd( 1 )
        else:
            self.childs = []


    def clear( self ):
        self.bl = []
        self.numb = 0
        for ch in self.childs:
            ch.clear()

    def locate( self, p ):
        # if self.childs == []:
        #     self.bl.append( p )
        #     self.numb += 1
        #     return
        # else:
        #     if p.coord.x + p.size < self.pc[0]:
        #         if p.coord.y + p.size < self.pc[1]:
        #             self.childs[0].locate( p )
        #             return
        #         elif p.coord.y - p.size >= self.pc[1]:
        #             self.childs[2].locate( p )
        #             return
        #         else:
        #             self.bl.append( p )
        #             self.numb += 1
        #             return
        #     elif p.coord.x - p.size >= self.pc[0]:
        #         if p.coord.y + p.size < self.pc[1]:
        #             self.childs[3].locate( p )
        #             return
        #         elif p.coord.y - p.size >= self.pc[1]:
        #             self.childs[1].locate( p )
        #             return
        #         else:
        #             self.bl.append( p )
        #             self.numb += 1
        #             return

        #     self.bl.append( p )
        #     self.numb += 1
        #     return

        for ch in self.childs:
           if ch.econtain( p ):
               ch.locate( p )
               return
        self.bl.append( p )
        self.numb += 1


    def lupdate( self ):
        ret = []
        for p in self.bl:
            if self.econtain( p ):
                continue
            else:
                ret.append( p )
                self.bl.remove( p )

        for ch in self.childs:
            ret.extend( ch.lupdate() )

        return ret




class span( object ):
    def __init__(self, min = 0.0, max = 0.0):
        self.min = min
        self.max = max

#    def overlap(self, other=span()):
#        if self.max >= other.min or self.min






def fborder( cg, bounds = Vector2( ( 800, 600 ) ) ):
    ret = []
    if cg.childs == []:
        ret.append(cg)
    else:
        for ch in cg.childs:
            if ( ch.p0.x == 0 ) or ( ch.p1.x == bounds.x ):
                ret.extend( fborder( ch, bounds ) )
            elif ( ch.p0.y == 0 ) or ( ch.p1.y == bounds.y ):
                ret.extend( fborder( ch, bounds ) )
    return ret



def collideP( cg, pbl = [], lpbl = 0 ):

    kr = 1.0

    tbl = cg.bl + pbl

    idm = cg.numb + lpbl
    if ( idm > 1 ):

        for fid in range( idm ):

            fb = tbl[fid]

            sid = fid + 1
            while ( sid < idm ):

                sb = tbl[sid]

                sid += 1

                dx = sb.coord.vSub( fb.coord )
                r = fb.size + sb.size
                dxl = dx.Len()

                if dxl < r:

                    cn = dx.Norm()#div( dxl )
                    cr = Sconst( ks = 1.0, rl = r, fid = 0, sid = 1 )
                    cr.upd2b( fb, sb )

                    dv = fb.vel.vSub( sb.vel )
                    sv = dv.Dot( cn )

                    if sv <= 0:
                        continue

                    nsv = -sv * kr
                    dsv = nsv - sv

                    tim = fb.invmass+sb.invmass

                    p = dsv / tim
                    pn = cn.sMul( p )

                    fb.vel = fb.vel.vAdd( pn.sMul( fb.invmass ) )
                    sb.vel = sb.vel.vSub( pn.sMul( sb.invmass ) )

    for n in cg.childs:
        collideP( n, tbl, idm )

def wcollide( cg ):
    for p in cg.bl:
        if p.coord.x - p.size < cg.p0.x:
            #pass
            #print "Коллизия с левом"
            #print p.coord.x, p.coord.y, p.vel.x, p.vel.y
            #print cg.p0.x
            p.coord.x = p.size+0.000001
            p.vel.x = sqrt( p.vel.x**2.0 ) * 0.3
            #p.vel.x *= -0.2
        elif p.coord.x + p.size > cg.p1.x:
            #print "Коллизия с правом"
            #print p.coord.x, p.coord.y, p.vel.x, p.vel.y
            #print cg.p1.x
            p.coord.x = cg.p1.x - p.size-0.000001
            p.vel.x = sqrt( p.vel.x**2.0 ) * -0.3
            #p.vel.x *= -0.2
        if p.coord.y - p.size < cg.p0.y:
            #pass
            #print "Коллизия с низом"
            #print p.coord.x, p.coord.y, p.vel.x, p.vel.y
            #print cg.p0.y
            p.coord.y = p.size+0.000001
            p.vel.y = sqrt( p.vel.y**2.0 ) * 0.3
            #p.vel.y *= -0.2
        elif p.coord.y + p.size > cg.p1.y:
            #pass
            #print "Коллизия с верхом"
            #print p.coord.x, p.coord.y, p.vel.x, p.vel.y
            #print cg.p1.y
            p.coord.y = cg.p1.y - p.size-0.000001
            p.vel.y = sqrt( p.vel.x**2.0 ) * -0.3
            #p.vel.y *= -0.2

def wcollideborder( cgl ):
    for cg in cgl:
        wcollide( cg )


class CCircle( object ):
    def __init__( self, p0 = Vector2(), r = 1 ):
        self.p0 = p0
        self.r = r

class AABB( object ):
    def __init__( self, p0 = Vector2(), p1 = Vector2( ( 1.0, 1.0 ) ) ):
        self.p0 = p0
        self.p1 = p1

class OOBB( object ):
    def __init__( self, p0 = Vector2(), p1 = Vector2( ( 1.0, 1.0 ) ),
                  q = Vector2() ):
        AABB.__init__( self, p0, p1 )
        self.q = q
