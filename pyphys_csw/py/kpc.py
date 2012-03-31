
# coding=UTF8


from math import *

from random import randint, uniform
from kmp import *

#class Vector:
#    def __init__( self, coord = ( 0.0, 0.0 ) ):
#        self.x, self.y = coord

class Vector:
    def __init__( self, coord = ( 0.0, 0.0 ) ):
        self.v = kmvect3f()
        self.Set( coord )

    def __setattr__( self, name, value ):
        if name == "x":
            self.v.x = value
        elif name == "y":
            self.v.y = value
        elif name == "z":
            self.v.z = value
    def __getattr__( self, name ):
        if name == "x":
            return self.v.x
        elif name == "y":
            return self.v.y
        elif name == "z":
            return self.v.z

    def __str__( self, pfx = "Vector", add = "" ):
        return ( pfx + "( ( " + repr( self.x ) + ", " + repr( self.y )
                + add + " ) )" )

    def Set( self, coord = ( 0.0, 0.0 ) ):
        #self.x, self.y = coord
        self.v.sSet( coord[0], coord[1], 0.0 )

    def Vadd( self, other ):
        #return Vector( ( self.x + other.x, self.y + other.y ) )
        return self.v.vAdd( other )

    def Vsub(  self, other ):
        #return Vector( ( self.x - other.x, self.y - other.y ) )
        return self.v.vSub( other )

    def Inv( self ):
        #return Vector( ( -self.x, -self.y ) )
        return self.v.Reverse()

    def Mul( self, mm = 1.0 ):
        #return Vector( ( self.x * mm, self.y * mm ) )
        return self.v.sMul( mm )

    def Div( self, d = 1.0 ):
        #return Vector( ( self.x / d, self.y / d ) )
        return self.v.sDiv( d )

    def Vmul( self, coord ):
        #return Vector( ( self.x * coord.x, self.y * coord.y ) )
        return self.v.vMul( coord )

    def Dot( self, coord ):
        #return self.x * coord.x + self.y * coord.y
        return self.v.Dot( coord )

    def Len( self ):
        #return sqrt( self.x**2 + self.y**2 )
        return self.v.Length()

    def Norm( self ):
        #len = self.Len()
        #if len > 0.0:
        #    return self.Div( self.Len() )
        #else:
        #    return Vector( ( 0.0, 0.0 ) )
        return self.v.Normalize()

    def Eql( self, coord ):
        if self.x == coord.x and self.y == coord.y:
            return True
        return False

    def Copy( self, coord ):
        self.x, self.y = coord.x, coord.y

    def rCopy( self ):
        return Vector( ( self.x, self.y ) )



class Pdc:
    def __init__( self, coord = Vector(), force = Vector(), vel = Vector(),
            mass = 1.0, oldcoord = Vector() ):

        self.coord = coord
        self.force = force
        self.oldcoord = oldcoord
        self.vel = vel
        if mass == 0:
            self.invmass = 0
        else:
            self.invmass = 1.0 / mass

    def __str__( self, pfx = "Pdc", add = "" ):
        return ( pfx + "( coord = " + str( self.coord ) + ", force = " +
                str( self.force ) + ", vel = " + str( self.vel )  +
                ", mass = " + repr( 1.0 / self.invmass ) +
                ", oldcoord = " + str( self.oldcoord ) + add + " )" )

    def Copy( self, pdc ):
        self.coord, self.force, self.vel, self.invmass = ( pdc.coord,
                pdc.force, pdc.vel, pdc.invmass )
        return self

    def rCopy( self ):
        np = Pdc()
        return np.Copy(self)


class Particle( Pdc ):
    def __init__( self, coord = Vector(), force = Vector(), mass = 1.0,
            vel = Vector(), size = 1, color = ( 128, 128, 128 ),
            oldcoord = Vector() ):

        Pdc.__init__( self, coord, force, vel, mass, oldcoord )
        self.size, self.color = size, color

    def __str__( self, pfx = "Particle", add = "" ):
        return ( pfx + Pdc.__str__( self, "", ", size = " + repr( self.size )
            + ", color = " + repr( self.color ) + add ) )

    def SetPdc( self, pdc):
        Pdc.Copy( self, pdc)




class Gforce:
    def __init__( self, G = 0.0001 ):
        self.G = G

    def __str__( self, pfx = "Gforce", add = "" ):
        return ( pfx + "( G = " + repr( self.G ) + add + " )" )

    def updfl( self, bl = [] ):
        idm = len( bl )
        for fid in range( idm ):
            fb = bl[fid]
            sid = fid + 1
            while( sid < idm ):
                sb = bl[sid]
                diff = sb.coord.Vsub( fb.coord )
                fsdist = diff.Len()**2
                m1 = 1.0 / fb.invmass
                m2 = 1.0 / sb.invmass
                if fsdist == 0: fsdist=0.001
                gf = ( self.G * m1 * m2 ) / fsdist
                diff = diff.Norm().Mul( gf )
                fb.force = fb.force.Vadd( diff )
                sb.force = sb.force.Vsub( diff )

                sid += 1

    def upd2b( self, fb, sb ):
        diff = sb.coord.Vsub( fb.coord )
        fsdist = diff.Len()**2
        m1 = 1.0 / fb.invmass
        m2 = 1.0 / sb.invmass
        if fsdist == 0: fsdist=0.001
        gf = ( self.G * m1 * m2 ) / fsdist
        diff = diff.Norm().Mul( gf )
        fb.force = fb.force.Vadd( diff )
        sb.force = sb.force.Vsub( diff )


class eGforce:
    def __init__( self, g = 9.8 ):
        self.g = g

    def __str__( self, pfx = "eGforce", add = "" ):
        return ( pfx + "( g = " + repr( self.g ) + add + " )" )

    def updfl( self, bl = [] ):
        acc = Vector( ( 0.0, self.g ) )
        for b in bl:
            m = 1/b.invmass
            b.force = b.force.Vadd( acc.Mul( m ) )

    def upd1b( self, fb ):
        acc = Vector( ( 0.0, self.g ) )
        m = 1/fb.invmass
        fb.force = fb.force.Vadd( acc.Mul( m ) )




class Fforce:
    def __init__( self, k = 0.3, kk = 0.02 ):
        self.k = k
        self.kk = kk

    def __str__( self, pfx = "Fforce", add = "" ):
        return ( pfx + "( k = " + repr( self.k ) + ", kk = "
                + repr( self.kk ) + add + " )" )

    def updfl( self, bl = [] ):
        for b in bl:
            fk = b.vel.Len()
            fk = fk * self.k + fk * self.kk**2
            force = b.vel.Norm()
            force = force.Mul( -fk )
            b.force = b.force.Vadd( force )

    def upd1b( self, fb ):
            fk = fb.vel.Len()
            fk = fk * self.k + fk * self.kk**2
            force = fb.vel.Norm()
            force = force.Mul( -fk )
            fb.force = fb.force.Vadd( force )



class Sforce:
    def __init__( self, ks = 0.3, kd = 0.3, rl = 1.0, fid = 0, sid = 1 ):
        self.ks = ks
        self.kd = kd
        self.rl = rl
        self.fid = fid
        self.sid = sid

    def __str__( self, pfx = "Sforce", add = "" ):
        return ( pfx + "( ks = " + repr( self.ks ) + ", kd = "
                + repr( self.kd ) + ", rl = " + repr( self.rl ) +
                ", fid = " + repr( self.fid ) + ", sid = " + repr( self.sid )
                + add + " )" )

    def updfl( self, bl = [] ):
        fb = bl[self.fid]
        sb = bl[self.sid]
        dx = sb.coord.Vsub( fb.coord )
        dxm = dx.Len()
        if dxm == 0:
            dxm = 0.001

        dv = sb.vel.Vsub( fb.vel )
        rf = dx.Norm()
        rf = rf.Mul( self.ks * ( dxm - self.rl ) + self.kd *
                dv.Dot( dx ) / dxm )
        fb.force = fb.force.Vadd( rf )
        sb.force = sb.force.Vsub( rf )

    def upd2b( self, fb, sb ):
        dx = sb.coord.Vsub( fb.coord )
        dxm = dx.Len()
        if dxm == 0:
            dxm = 0.001

        dv = sb.vel.Vsub( fb.vel )
        rf = dx.Norm()
        rf = rf.Mul( self.ks * ( dxm - self.rl ) + self.kd *
                dv.Dot( dx ) / dxm )
        fb.force = fb.force.Vadd( rf )
        sb.force = sb.force.Vsub( rf )




def CompFs( fl = [], pdc = [] ):
    idm = len( pdc )
    for fid in range( idm ):
        sid = fid + 1
        fb = pdc[fid]
        while ( sid < idm ):
            sb = pdc[sid]
            sid += 1
            for it in fl:
                for f in it:
                    f.upd2b( fb, sb )


class Sconst:
    def __init__( self, ks = 0.3, rl = 1.0, fid = 0, sid = 1 ):
        self.ks = ks
        self.fid = fid
        self.sid = sid
        self.rl = rl

    def __str__( self, pfx = "Sconst", add = "" ):
        return ( pfx + "( ks = " + repr( self.ks )
                + ", fid = " + repr( self.fid )
                + ", sid = " + repr( self.sid )
                + ", rl = " + repr( self.rl) + add + " )" )

    def updcl( self, bl = [] ):
        fb = bl[self.fid]
        sb = bl[self.sid]
        dx = sb.coord.Vsub( fb.coord )
        dxm = dx.Len()
        p = self.rl - dxm
        tim = fb.invmass + sb.invmass
        mv = dx.Div(dxm).Mul( -p / tim )
        fb.coord = fb.coord.Vadd( mv.Mul( fb.invmass ) )
        sb.coord = sb.coord.Vadd( mv.Mul( sb.invmass ) )

    def upd2b( self, fb, sb ):
        dx = sb.coord.Vsub( fb.coord )
        dxm = dx.Len()
        if dxm == 0:
            dxm = 0.001
        p = self.rl - dxm
        m1 = 1.0 / fb.invmass
        m2 = 1.0 / sb.invmass
        tim = m1+m2
        mv = dx.Div( dxm ).Mul( -p / tim )
        fb.coord = fb.coord.Vadd( mv.Mul( m2 ) )
        sb.coord = sb.coord.Vsub( mv.Mul( m1 ) )
        #dx = sb.coord.Vsub( fb.coord )
        #dxm = dx.Len()
        #if dxm == 0:
        #    dxm = 0.001
        #tim = fb.invmass + sb.invmass
        #dl = self.ks * ( dxm - self.rl ) / dxm * tim
        #fb.coord = fb.coord.Vadd( dx.Mul( fb.invmass ).Mul( dl ) )
        #sb.coord = sb.coord.Vsub( dx.Mul( sb.invmass ).Mul( dl ) )

def SolveC( cl = [], pdc = [] ):
    idm = len( pdc )
    for fid in range( idm ):
        sid = fid + 1
        fb = pdc[fid]
        while ( sid < idm ):
            sb = pdc[sid]
            sid += 1
            for it in cl:
                for c in it:
                    c.upd2b( fb, sb )



#def collideP( fb, sb ):
#
#    dx = sb.coord.Vsub( fb.coord )
#    r = fb.size + sb.size
#    kr = 0.6
#
#    if dx.Len() < r:
#        cn = dx.Norm()
#        cr = Sconst( ks = 1.0, rl = r, fid = 0, sid = 1 )
#        cr.upd2b( fb, sb )
#
#        dv = fb.vel.Vsub( sb.vel )
#        sv = dv.Dot( cn )
#
#        if sv <= 0:
#            return True
#
#        nsv = -sv * kr
#        dsv = nsv - sv
#
#        tim = fb.invmass + sb.invmass
#
#        p = dsv / tim
#        pn = cn.Mul( p )
#
#        fb.vel = fb.vel.Vadd( pn.Mul( fb.invmass ) )
#        sb.vel = sb.vel.Vsub( pn.Mul( sb.invmass ) )
#
#        return True
#    return False

#def wcollide( b, bounds ):
#    if b.coord.x + b.size > bounds.x:
#        b.coord.x = bounds.x - b.size
#        b.vel.x *= -0.2
#    if b.coord.x - b.size < 0:
#        b.coord.x = b.size
#        b.vel.x *= -0.2
#    if b.coord.y + b.size > bounds.y:
#        b.coord.y = bounds.y - b.size
#        b.vel.y *= -0.2
#    if b.coord.y - b.size < 0:
#        b.coord.y = b.size
#        b.vel.y *= -0.2

def collideP( cg, abl ):
    kr = 0.6
    bl = cg.bl + abl

    idm = len( bl )
    if ( idm > 1 ):
        for fid in range( idm ):
            sid = fid + 1
            fb = bl[fid]
            while ( sid < idm ):
                sb = bl[sid]
                sid += 1

                dx = sb.coord.Vsub( fb.coord )
                r = fb.size + sb.size


                if dx.Len() < r:

                    cn = dx.Norm()
                    cr = Sconst( ks = 1.0, rl = r, fid = 0, sid = 1 )
                    cr.upd2b( fb, sb )

                    dv = fb.vel.Vsub( sb.vel )
                    sv = dv.Dot( cn )

                    if sv <= 0:
                        continue

                    nsv = -sv * kr
                    dsv = nsv - sv

                    m1 = 1.0 / fb.invmass
                    m2 = 1.0 / sb.invmass

                    tim = m1+m2

                    p = dsv / tim
                    pn = cn.Mul( p )

                    fb.vel = fb.vel.Vadd( pn.Mul( m2 ) )
                    sb.vel = sb.vel.Vsub( pn.Mul( m1 ) )

    for n in cg.childs:
        collideP( n, bl )


def wcollide( cg, bounds, abl ):
    for n in cg:
        bl = n.bl + abl
        #if n.parent:
        bl += n.parent.bl
        if n.p0[0] == 0:
            for p in bl:
                if p.coord.x - p.size < 1:
                    p.coord.x = p.size+1
                    p.vel.x *= -0.2
        if n.p1[0] >= bounds[0]:
            for p in bl:
                if p.coord.x + p.size > bounds[0]-1:
                    p.coord.x = bounds[0] - p.size-1
                    p.vel.x *= -0.2
        if n.p0[1] == 0:
            for p in bl:
                if p.coord.y - p.size < 1:
                    p.coord.y = p.size+1
                    p.vel.y *= -0.2
        if n.p1[1] >= bounds[1]:
            for p in bl:
                if p.coord.y + p.size > bounds[1]-1:
                    p.coord.y = bounds[1] - p.size-1
                    p.vel.y *= -0.2




def moupd( pdc = [], f1bl = [], f2bl = [], sl = [], cl = [] ):
    for b in pdc:
        b.force = Vector()

    idm = len( pdc )
    for fid in range( idm ):
        sid = fid + 1
        fb = pdc[fid]
        #fb.force = Vector()
        for f in f1bl:
            f.upd1b( fb )
        while ( sid < idm ):
            sb = pdc[sid]
            sid += 1
            for it in f2bl:
                for f in it:
                    f.upd2b( fb, sb )
            #for it in cl:
            #    for c in it:
            #        c.upd2b( fb, sb )
            #collideP( fb, sb )
        #wcollide( fb )




def Derive( ipdc = [], spdc = [], tpdc = [], dt = 1 ):

    id = len( ipdc ) - 1

    while ( id > -1 ):

        cipdc = ipdc[id]
        cspdc = spdc[id]
        ctpdc = tpdc[id]

        mdt = cipdc.invmass * dt

        ctpdc.vel = cipdc.vel.Vadd( cspdc.force.Mul( mdt ) )

        ctpdc.invmass = cipdc.invmass

        tmp = ctpdc.coord

        ctpdc.coord = cipdc.coord.Vadd( cspdc.vel.Mul( dt ) )

        ctpdc.oldcoord = tmp
        id -= 1

def Euler( pdc = [], dt = 1.0 ):
    Derive( pdc, pdc, pdc, dt )

def Midpoint( pdc = [], f1bl = [], f2bl = [], sl = [], dt = 1.0 ):
    tmp = list(pdc)
    Derive( pdc, pdc, tmp, dt*0.5 )
    #CompFsl( fl, tmp )
    moupd( pdc, f1bl, (f2bl,[]), sl )
    Derive( pdc, tmp, pdc, dt )

def RK4( pdc = [], f1bl = [], f2bl = [], sl = [], dt = 1.0 ):
    a1, a2, a3, a4 = list(pdc),list(pdc),list(pdc),list(pdc)

    Derive( pdc, pdc, a1, dt*0.5 )
    #CompFsl( fl, a1 )
    moupd( a1, f1bl, (f2bl,[]), sl )
    Derive( pdc, a1, a2, dt*0.5 )
    #CompFsl( fl, a2 )
    moupd( a2, f1bl, (f2bl,[]), sl )
    Derive( pdc, a2, a3, dt )
    #CompFsl( fl, a3 )
    moupd( a3, f1bl, (f2bl,[]), sl )

#    Derive( pdc, a3, a4, dt )
#    CompFsl( fl, a4 )

    #Derive( pdc, pdc, a1, dt )
    #CompFsl( fl, a1 )
    #Derive( pdc, a1, a2, dt*0.5 )
    #CompFsl( fl, a2 )
    #Derive( a2, a2, a3, dt*0.5 )
    #CompFsl( fl, a3 )
    #Derive( a3, a3, a4, dt )
    #CompFsl( fl, a4 )

    id = len( pdc ) - 1

    while ( id > -1 ):

        ct = pdc[id]
        ca1 = a1[id]
        ca2 = a2[id]
        ca3 = a3[id]
        ca4 = pdc[id]

        nv = ca2.force.Vadd( ca3.force ).Mul( 2.0 )
        nv = nv.Vadd( ca1.force.Vadd( ca4.force ) )
        nv = nv.Mul( 1.0 / 6.0 )
        ct.vel = ct.vel.Vadd( nv.Mul(ct.invmass*dt) )

        ct.oldcoord = ct.coord
        nc = ca2.vel.Vadd( ca3.vel ).Mul( 2.0 )
        nc = nc.Vadd( ca1.vel.Vadd( ca4.vel ) )
        nc = nc.Mul( 1.0 / 6.0 )
        ct.coord = ct.coord.Vadd( nc.Mul(dt) )

        id -= 1

def Verlet( pdc = [], dt = 1.0 ):
    for b in pdc:
        a = b.force.Mul( b.invmass * dt )
        tmp = b.coord
        b.vel = b.vel.Vadd( b.coord.Vsub( b.oldcoord ).Vadd( a ) ).Mul( 0.5 )
        b.coord = b.coord.Vadd( b.vel.Mul( dt ) )
        b.oldcoord = tmp



def KCFsl( fl = [], pdc = [] ):
    for b in pdc:
        b.oldforce = b.force
        b.force = Vector()
    for it in fl:
        for f in it:
            f.updfl( pdc )



def KDerive( ipdc = [], spdc = [], tpdc = [], dt = 1 ):

    id = len( ipdc ) - 1

    while ( id > -1 ):

        cipdc = ipdc[id]
        cspdc = spdc[id]
        ctpdc = tpdc[id]

        mdt = cipdc.invmass * dt * dt * 0.25

        ctpdc.vel = cipdc.vel.Vadd( cspdc.oldforce.Vadd(
            cspdc.force).Mul( mdt ) )

        ctpdc.invmass = cipdc.invmass

        tmp = ctpdc.coord

        ctpdc.coord = cipdc.coord.Vadd( cspdc.coord.Vsub(
            cspdc.oldcoord ).Vadd( cspdc.vel.Mul( dt ) ).Mul( 0.5 ) )

        ctpdc.oldcoord = tmp
        id -= 1


def K4( pdc = [], fl = [], dt = 1.0 ):
    a1, a2, a3, a4 = list(pdc),list(pdc),list(pdc),list(pdc)

    KDerive( pdc, pdc, a1, dt*0.5 )
    KCFsl( fl, a1 )
    KDerive( pdc, a1, a2, dt*0.5 )
    KCFsl( fl, a2 )
    KDerive( pdc, a2, a3, dt )
    KCFsl( fl, a3 )
#    KDerive( pdc, a3, a4, dt )
#    KCFsl( fl, a4 )

    #Derive( pdc, pdc, a1, dt )
    #CompFsl( fl, a1 )
    #Derive( pdc, a1, a2, dt*0.5 )
    #CompFsl( fl, a2 )
    #Derive( a2, a2, a3, dt*0.5 )
    #CompFsl( fl, a3 )
    #Derive( a3, a3, a4, dt )
    #CompFsl( fl, a4 )

    id = len( pdc ) - 1

    while ( id > -1 ):

        ct = pdc[id]
        ca1 = a1[id]
        ca2 = a2[id]
        ca3 = a3[id]
        ca4 = pdc[id]

        nv = ca2.force.Vadd( ca3.force ).Mul( 2.0 )
        nv = nv.Vadd( ca1.force.Vadd( ca4.force ) )
        nv = nv.Mul( 1.0 / 6.0 )
        ct.vel = ct.vel.Vadd( nv.Mul(ct.invmass*dt) )

        ct.oldcoord = ct.coord
        nc = ca2.vel.Vadd( ca3.vel ).Mul( 2.0 )
        nc = nc.Vadd( ca1.vel.Vadd( ca4.vel ) )
        nc = nc.Mul( 1.0 / 6.0 )
        ct.coord = ct.coord.Vadd( nc.Mul(dt) )

        id -= 1


class CollGridn:
    def __init__( self, p0, p1 ):
        self.p0 = p0
        self.p1 = p1
        self.bl = []
        self.childs = []
        self.parent = None
        self.nb = 0
        self.nbm = 50

    def __str__( self ):
        ret = ( "CollGridn( p0 = " + repr( self.p0) + ", p1 = "
                + repr( self.p1 )  + ", bl = " + repr( self.bl ) + " \n" )
        ret += "childs = [ "
        for ch in self.childs:
            ret += str( ch ) + ","
        ret += " ] )\n"
        return ret

    def contain( self, p ):
        #if p in self.bl:
        #    return True
        if ((p.coord.x + p.size >= self.p0[0]) and ( p.coord.x - p.size <=
                self.p1[0] )):
            if ((p.coord.y + p.size >= self.p0[1]) and (p.coord.y - p.size <=
                    self.p1[1])):
                return True
        return False

    def econtain( self, p ):
        #if p in self.bl:
        #    return True
        if ((p.coord.x - p.size >= self.p0[0]) and ( p.coord.x + p.size <=
                self.p1[0] )):
            if ((p.coord.y - p.size >= self.p0[1]) and (p.coord.y + p.size <=
                    self.p1[1])):
                return True
        return False


    def locate( self, p ):
        r = 0
        if self.econtain( p ):
            for ch in self.childs:
                r += ch.locate( p )
        else:
            return 0
        if r == 0:
            self.bl.append( p )
            return 1
        else:
            return 1



    def subd( self, l ):
        if l <= 0:
            return

        nc = ( self.p0[0] + ( self.p1[0] - self.p0[0] ) / 2,
                self.p0[1] + ( self.p1[1] - self.p0[1] ) /2 )

        self.childs.append( CollGridn ( self.p0, nc ) )
        self.childs[0].parent = self
        self.childs.append( CollGridn ( nc, self.p1 ) )
        self.childs[1].parent = self
        self.childs.append( CollGridn ( ( self.p0[0], nc[1] ),
            ( nc[0], self.p1[1] ) ) )
        self.childs[2].parent = self
        self.childs.append( CollGridn ( ( nc[0], self.p0[1] ),
            ( self.p1[0], nc[1] ) ) )
        self.childs[3].parent = self

        l -= 1
        for ch in self.childs:
            ch.subd( l )

    def clear( self ):
        for ch in self.childs:
            ch.bl = []
            ch.clear()

    def update( self ):
        ret = []
        if self.childs == []:
            for p in self.bl:
                if self.contain( p ):
                    pass
                else:
                    ret.append( p )
                    self.bl.remove( p )
            return ret

        for n in self.childs:
            ret.extend( n.update() )
        #print ret
        return set(ret)



def fborder( cg, bounds ):
    ret = []
    if cg.childs == []:
        ret.append(cg)
    else:
        for ch in cg.childs:
            if ( ch.p0[0] == 0 ) or ( ch.p1[0] == bounds[0] ):
                ret.extend( fborder( ch, bounds ) )
            elif ( ch.p0[1] == 0 ) or ( ch.p1[1] == bounds[1] ):
                ret.extend( fborder( ch, bounds ) )
    return ret


class CollGrid:
    def __init__( self, sim, bounds, d ):
        self.p0 = ( 0, 0 )
        self.p1 = ( bounds[0], bounds[1] )
        self.childs = []
        self.childs.append( CollGridn( ( 0, 0 ), ( bounds[0], bounds[1] ) ) )
        self.childs[0].subd( d )
        self.border = []
        self.bl=[]
        #self.nodes = []
        #x0 = 0
        #y0 = 0
        #x1 = x0 + d[0]
        #y1 = y0 + d[1]
        #while ( y0 < bounds[0] ):
        #    while ( x0 < bounds[0] ):
        #        self.nodes.append( CollGridn( ( x0, y0 ), ( x1, y1 ) ) )
        #        x0 = x1
        #        x1 += d[0]
        #    x0 = 0
        #    x1 = x0 + d[0]
        #    y0 = y1
        #    y1 += d[1]

        #for p in sim.bodyes:
        #    self.locate(p)

    def econtain( self, p ):
        #if p in self.bl:
        #    return True
        if ((p.coord.x - p.size >= self.p0[0]) and ( p.coord.x + p.size <=
                self.p1[0] )):
            if ((p.coord.y - p.size >= self.p0[1]) and (p.coord.y + p.size <=
                    self.p1[1])):
                return True
        return False


    def clear( self ):
        self.bl = []
        for n in self.childs:
            n.bl = []
            n.clear()

    def locate( self, p ):
        if self.econtain( p ):
            if self.childs[0].locate( p ) == 0:
                self.bl.append( p )
                return
        else:
            self.bl.append(p)
                #return True
        #return False

    def update( self ):
        bl = self.childs[0].update()
        #print bl
        for p in bl:
            self.locate( p )


class Simulation:

    def __init__( self, bounds = ( 800, 600 ), bodylist = [], force1bl = [],
            force2bl = [], springl = [], dt = 0.07 ):
        self.bodyes, self.forces1b, self.forces2b, self.springs = ( bodylist,
                force1bl, force2bl, springl )
        self.bounds = bounds
        self.border = []
        self.dt = dt
        self.uf = Vector()
        self.colg = CollGrid( self, bounds, 4 )

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

    def AddBody( self, body ):
        self.bodyes.append( body )
        #self.colg.locate( body )

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
            if s < 1: s = 1
            #r = int(sqrt(m*10)/2)
            m = uniform( 1, 50 )
            mv = m * 0.3
            ve = Vector( ( uniform( -mv, mv ),uniform( -mv, mv ) ) )
            ncoord = Vector( ( randint( 10, 600 ), randint( 10, 500 ) ) )
            ncolor = ( randint( 100, 255 ), randint( 100, 255 ),
                    randint( 100, 255 ) )
            self.AddBody( Particle( coord = ncoord, mass = m, vel =
                ve, size = s, color = ncolor ) )

    def CenterAt( self, x = 0.0, y = 0.0, bid = 0 ):
        for b in self.bodyes:
            b.coord = (
                b.coord.Vsub( self.bodyes[bid].coord ).Vadd(
                    Vector( ( x, y ) ) ) )
            b.oldcoord = (
                b.oldcoord.Vsub( self.bodyes[bid].coord ).Vadd(
                    Vector( ( x, y ) ) ) )


    def Solve( self, dt = 0.1 ):
        #CompFsl( ( self.forces, self.springs ), self.bodyes )
        moupd( self.bodyes, self.forces1b, (self.forces2b,[]), self.springs )

        self.bodyes[1].force = self.bodyes[0].force.Vadd( self.uf )
        #self.bodyes[1].force = self.bodyes[1].force.Vadd( self.uf )
        self.uf = Vector()
        Euler( self.bodyes, self.dt )
        #Midpoint( self.bodyes, self.forces1b, self.forces2b, self.springs,
        #        self.dt )
        #RK4( self.bodyes, self.forces1b, self.forces2b, self.springs, self.dt )

        #K4( self.bodyes, (self.forces, self.springs ), dt )

        #self.bodyes[0].coord = self.bodyes[0].coord.Vadd( self.uf )
        #self.bodyes[1].coord = self.bodyes[1].coord.Vadd( self.uf )
        #self.uf = Vector()
        #Verlet( self.bodyes, self.dt )

        self.colg.clear()
        #self.colg.update()
        for p in self.bodyes:
            self.colg.locate( p )
        #print self.colg.childs[0].childs[1].bl
        #print (self.colg.childs[0].childs[1].childs[0].p0,
        #        self.colg.childs[0].childs[1].childs[0].p1)
        #print self.bodyes[0].coord
        #print self.colg.bl
        collideP( self.colg, [] )
        wcollide( self.border, self.bounds, self.colg.bl )
        #exit()

        #fid = len( self.bodyes ) -1
        #for i in xrange( 1 ):
        #    while ( fid > -1 ):
        #        sid = fid - 1
        #        fb = self.bodyes[fid]
        #        while ( sid > -1 ):
        #            sb = self.bodyes[sid]
        #            sid -= 1
        #            collideP( fb, sb )
        #        wcollide( fb )
        #        fid -= 1
        #for fb in self.bodyes:
        #    for sb in self.bodyes:
        #        if sb == fb:
        #            continue
        #        collideP(fb, sb)
        #    wcollide( fb, self.bounds )

        #self.CenterAt( 525, 350 )

        #for b in set( self.rmb ): self.bodyes.remove( b )
        #for b in set( self.ab ): self.bodyes.append( b )
        #self.rmb, self.ab = [], []
