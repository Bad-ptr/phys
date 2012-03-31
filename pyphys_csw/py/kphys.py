
#coding=UTF-8

from kpmath import *


class Pdc:
    def __init__( self, coord = Vector2(), force = Vector2(), vel = Vector2(),
                  mass = 1.0, oldcoord = Vector2() ):
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
    def __init__( self, coord = Vector2(), force = Vector2(), mass = 1.0,
            vel = Vector2(), size = 1, color = ( 128, 128, 128 ),
            oldcoord = Vector2() ):

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
                diff = sb.coord.vSub( fb.coord )
                fsdist = diff.Len()**2
                m1 = 1.0 / fb.invmass
                m2 = 1.0 / sb.invmass
                if fsdist == 0: fsdist=0.001
                gf = ( self.G * m1 * m2 ) / fsdist
                diff = diff.Norm().sMul( gf )
                fb.force = fb.force.vAdd( diff )
                sb.force = sb.force.vSub( diff )

                sid += 1

    def upd2b( self, fb, sb ):
        diff = sb.coord.vSub( fb.coord )
        fsdist = diff.Len()
        if fsdist == 0: fsdist=0.001
        gf = ( self.G * 1.0 / ( fb.invmass * sb.invmass ) ) / fsdist**2
        diff = diff.sDiv( fsdist ).sMul( gf )
        fb.force = fb.force.vAdd( diff )
        sb.force = sb.force.vSub( diff )


class eGforce:
    def __init__( self, g = 9.8 ):
        self.g = g

    def __str__( self, pfx = "eGforce", add = "" ):
        return ( pfx + "( g = " + repr( self.g ) + add + " )" )

    def updfl( self, bl = [] ):
        acc = Vector2( (  0.0, self.g  ) )
        for b in bl:
            m = 1/b.invmass
            b.force = b.force.vAdd( acc.sMul( m ) )

    def upd1b( self, fb ):
        #acc = Vector2( (  0.0, self.g  ) )
        #m = 1.0 / fb.invmass
        #fb.force = fb.force.vAdd( acc.sMul( m ) )
        fb.force.y += self.g/fb.invmass


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
            force = force.sMul( -fk )
            b.force = b.force.vAdd( force )

    def upd1b( self, fb ):
            fk = fb.vel.Len()
            fk = fk * self.k + fk * self.kk**2
            force = fb.vel.Norm()
            force = force.sMul( -fk )
            fb.force = fb.force.vAdd( force )



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
        dx = sb.coord.vSub( fb.coord )
        dxm = dx.Len()
        if dxm == 0:
            dxm = 0.001

        dv = sb.vel.vSub( fb.vel )
        rf = dx.Norm()
        rf = rf.sMul( self.ks * ( dxm - self.rl ) + self.kd *
                dv.Dot( dx ) / dxm )
        fb.force = fb.force.vAdd( rf )
        sb.force = sb.force.vSub( rf )

    def upd2b( self, fb, sb ):
        dx = sb.coord.vSub( fb.coord )
        dxm = dx.Len()
        if dxm == 0:
            dxm = 0.001

        dv = sb.vel.vSub( fb.vel )
        rf = dx.Norm()
        rf = rf.sMul( self.ks * ( dxm - self.rl ) + self.kd *
                dv.Dot( dx ) / dxm )
        fb.force = fb.force.vAdd( rf )
        sb.force = sb.force.vSub( rf )



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
        dx = sb.coord.vSub( fb.coord )
        dxm = dx.Len()
        p = self.rl - dxm
        tim = fb.invmass + sb.invmass
        mv = dx.sDiv(dxm).sMul( -p / tim )
        fb.coord = fb.coord.vAdd( mv.sMul( fb.invmass ) )
        sb.coord = sb.coord.vAdd( mv.sMul( sb.invmass ) )

    def upd2b( self, fb, sb ):
        dx = sb.coord.vSub( fb.coord )
        dxm = dx.Len()
        dn = dx.sDiv( dxm )
        if dxm == 0:
            return
        p = self.rl - dxm
        #tim = fb.invmass+sb.invmass
        #mv = dx.Norm().sMul( -p / tim )
        #fb.coord = fb.coord.vAdd( mv.sMul( fb.invmass ) )
        #sb.coord = sb.coord.vSub( mv.sMul( sb.invmass ) )

        tim = fb.invmass + sb.invmass
        d1 = -p * ( fb.invmass / tim )
        d2 = p * ( sb.invmass / tim )
        fb.coord = fb.coord.vAdd( dn.sMul( d1 ) )
        sb.coord = sb.coord.vAdd( dn.sMul( d2 ) )

        #dx = sb.coord.vSub( fb.coord )
        #dxm = dx.Len()
        #if dxm == 0:
        #    dxm = 0.001
        #tim = fb.invmass + sb.invmass
        #dl = self.ks * ( dxm - self.rl ) / dxm * tim
        #fb.coord = fb.coord.vAdd( dx.sMul( fb.invmass ).sMul( dl ) )
        #sb.coord = sb.coord.vSub( dx.sMul( sb.invmass ).sMul( dl ) )

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


def moupd( pdc = [], f1bl = [], f2bl = [], sl = [], cl = [] ):
    for b in pdc:
        b.force = Vector2()

    idm = len( pdc )
    for fid in range( idm ):
        sid = fid + 1
        fb = pdc[fid]
        #fb.force = Vector2()
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

        ctpdc.vel = cipdc.vel.vAdd( cspdc.force.sMul( mdt ) )

        ctpdc.invmass = cipdc.invmass

        tmp = ctpdc.coord

        ctpdc.coord = cipdc.coord.vAdd( cspdc.vel.sMul( dt ) )

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

        nv = ca2.force.vAdd( ca3.force ).sMul( 2.0 )
        nv = nv.vAdd( ca1.force.vAdd( ca4.force ) )
        nv = nv.sMul( 1.0 / 6.0 )
        ct.vel = ct.vel.vAdd( nv.sMul(ct.invmass*dt) )

        ct.oldcoord = ct.coord
        nc = ca2.vel.vAdd( ca3.vel ).sMul( 2.0 )
        nc = nc.vAdd( ca1.vel.vAdd( ca4.vel ) )
        nc = nc.sMul( 1.0 / 6.0 )
        ct.coord = ct.coord.vAdd( nc.sMul(dt) )

        id -= 1

def Verlet( pdc = [], dt = 1.0 ):
    for b in pdc:
        a = b.force.sMul( b.invmass * dt )
        tmp = b.coord
        b.vel = b.vel.vAdd( b.coord.vSub( b.oldcoord ).vAdd( a ) ).sMul( 0.5 )
        b.coord = b.coord.vAdd( b.vel.sMul( dt ) )
        b.oldcoord = tmp



def KCFsl( fl = [], pdc = [] ):
    for b in pdc:
        b.oldforce = b.force
        b.force = Vector2()
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

        ctpdc.vel = cipdc.vel.vAdd( cspdc.oldforce.vAdd(
            cspdc.force).sMul( mdt ) )

        ctpdc.invmass = cipdc.invmass

        tmp = ctpdc.coord

        ctpdc.coord = cipdc.coord.vAdd( cspdc.coord.vSub(
            cspdc.oldcoord ).vAdd( cspdc.vel.sMul( dt ) ).sMul( 0.5 ) )

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

        nv = ca2.force.vAdd( ca3.force ).sMul( 2.0 )
        nv = nv.vAdd( ca1.force.vAdd( ca4.force ) )
        nv = nv.sMul( 1.0 / 6.0 )
        ct.vel = ct.vel.vAdd( nv.sMul(ct.invmass*dt) )

        ct.oldcoord = ct.coord
        nc = ca2.vel.vAdd( ca3.vel ).sMul( 2.0 )
        nc = nc.vAdd( ca1.vel.vAdd( ca4.vel ) )
        nc = nc.sMul( 1.0 / 6.0 )
        ct.coord = ct.coord.vAdd( nc.sMul(dt) )

        id -= 1


class RB( Pdc ):
     """
     Rigid Body
     """
     def __init__( self, coord = Vector2( ( 1.0, 1.0 ) ), force = Vector2(),
                   vel = Vector2(), mass = 1.0, oldcoord = Vector2(),
                   orient = 0.0, avel = 0.0 ):
         self.coord = coord
         self.force = force
         self.vel = vel
         self.avel = avel
         self.invmass = 1.0 / mass
         self.oldcoord = oldcoord
         self.orient = orient
