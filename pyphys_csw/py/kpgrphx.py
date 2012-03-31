
from math import *

import pyglet
from pyglet.window import mouse
from pyglet.window import key
pyglet.options['debug_gl'] = False
from pyglet.gl import *

from kpsim import *


def kCircle( x = 0.0, y = 0.0, r = 1.0, s = 4 ):
    va = []
    id = 0
    s = 360 / s
    while( id <= 360 ):
        p = radians( id )
        nx = r * cos( p ) + x
        ny = r * sin( p ) + y
        va.append( ( nx, ny ) )

        id += s

    return va

c = kCircle( 0, 0, 1, 8 )

def gInit():
    config = pyglet.gl.Config( buffer_size = 32, alpha_size = 8,
                               double_buffer = True )
    window = pyglet.window.Window( 800, 600, config = config,
                                   caption = "3aroJIoBoK",
                                   vsync = False, resizable = False )
    context = window.context
    platform = pyglet.window.get_platform()
    display = platform.get_default_display()

    glClearColor( 0.0, 0.0, 0.0, 0.0 )
    #glPolygonMode( GL_FRONT_AND_BACK, GL_SMOOTH )
    glEnable( GL_CULL_FACE )

    glEnable( GL_BLEND)
    glBlendFunc( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA )

    #glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);
    #glHint(GL_POINT_SMOOTH_HINT, GL_NICEST);
    #glHint(GL_POLYGON_SMOOTH_HINT, GL_NICEST);
    #glHint(GL_LIGHTING, GL_NICEST);
    #glEnable(GL_LINE_SMOOTH);
    #glEnable(GL_POINT_SMOOTH);
    #glEnable(GL_POLYGON_SMOOTH);

    glEnable( GL_COLOR_MATERIAL )
    glEnable( GL_DEPTH_TEST )

    amb = [ 0.0, 0.0, 0.0, 0.0 ]
    dif = [ 0.5, 0.5, 0.5, 0.0 ]
    spec = [ 1.0, 1.0, 1.0, 0.0 ]
    lightexp = [ 1.0, 1.0, 1.0, 0.0 ]
    amb = (GLfloat * 4)( *amb )
    dif = (GLfloat * 4)( *dif )
    spec = (GLfloat * 4)( *spec )
    lightexp = (GLfloat * 4)( *lightexp )

    glEnable(GL_LIGHTING)
    glEnable(GL_LIGHT0)
    glLightModelf(GL_LIGHT_MODEL_LOCAL_VIEWER,1)
    glLightfv(GL_LIGHT0,GL_AMBIENT,amb)
    glLightfv(GL_LIGHT0,GL_DIFFUSE,dif)
    glLightfv(GL_LIGHT0,GL_SPECULAR,spec)
    glLightfv(GL_LIGHT0,GL_SPOT_EXPONENT,lightexp)

    return window

def drawCGn( cg ):
    for n in cg.childs:
        glColor4f( 0, 1, 0, 0.6 )
        pyglet.graphics.draw( 8, GL_LINE_STRIP,
                ( 'v2f', ( n.p0.x, n.p0.y, n.p0.x, n.p1.y, n.p0.x,
                           n.p1.y, n.p1.x, n.p1.y, n.p1.x, n.p1.y,
                           n.p1.x, n.p0.y, n.p1.x, n.p0.y, n.p0.x,
                           n.p0.y ) ) )
        drawCGn( n )


def handlevents( window, sim ):
    @window.event()
    def on_resize( width, height ):
        glViewport( 0, 0, width, height )
        glMatrixMode( GL_PROJECTION )
        glLoadIdentity()
        glOrtho( 0, width, 0, height, -1, 1 )
        glMatrixMode( GL_MODELVIEW )

        sim.SetBounds( Vector2( ( width, height ) )  )
        #sim.colg.csubd( 2 )

        return pyglet.event.EVENT_HANDLED

    @window.event()
    def on_draw():
        #window.clear()
        glClear( GL_COLOR_BUFFER_BIT )
        glClear( GL_DEPTH_BUFFER_BIT )
        #glLoadIdentity()

        for b in sim.bodyes:
            #glPointSize( GLfloat(b.size*1.2) )
            #pyglet.graphics.draw( 1, GL_POINTS, ( 'v2f',
            #    ( b.coord.x, b.coord.y ) ),
            #    ( 'c4B', ( b.color[0], b.color[1], b.color[2], 255 ) ) )
            glPushMatrix()
            glColor4f( b.color[0]/100, b.color[1]/100, b.color[2]/100, 0.3 )
            glTranslatef( b.coord.x, b.coord.y, 0 )
            glScalef( b.size, b.size, 1 )
            pyglet.graphics.draw( 9, GL_LINE_STRIP,
                    ( 'v2f', ( c[0][0], c[0][1], c[1][0], c[1][1],
                               c[2][0], c[2][1], c[3][0], c[3][1], c[4][0], c[4][1],
                               c[5][0], c[5][1], c[6][0], c[6][1], c[7][0], c[7][1],
                               c[0][0], c[0][1]) ) )
            glPopMatrix()

        dftr = sim.dftr
        glPushMatrix()
        glColor4f( 100, 0, 0, 0.3 )
        glTranslatef( 100, 100, 0 )
        #glScalef( 1, 1, 1 )
        pyglet.graphics.draw( 5, GL_LINE_STRIP,
                ( 'v2f', ( dftr.p0.x, dftr.p0.y, dftr.p1.x, dftr.p1.y,
                           dftr.p2.x, dftr.p2.y, dftr.p3.x, dftr.p3.y,
                           dftr.p0.x, dftr.p0.y ) ) )
        glPopMatrix()

        drawCGn( sim.colg )

        #glFlush()
        #glFinish()

    @window.event()
    def on_key_press( symbol, modifiers ):
        if symbol == key.SPACE:
            sim.Rands( randint( 2, 6 ) )
        elif symbol == key.LEFT:
            fv = Vector2( ( -1000.0, 0.0 ) )
            sim.uf = sim.uf.vAdd( fv )
        elif symbol == key.RIGHT:
            fv = Vector2( ( 1000.0, 0.0 ) )
            sim.uf = sim.uf.vAdd( fv )
        elif symbol == key.UP:
            fv = Vector2( ( 0.0, 1000.0 ) )
            sim.uf = sim.uf.vAdd( fv )
        elif symbol == key.DOWN:
            fv = Vector2( ( 0.0, -1000.0 ) )
            sim.uf = sim.uf.vAdd( fv )
        elif symbol == key.ESCAPE:
            pyglet.app.exit()

    @window.event()
    def on_mouse_press( x, y, button, modifiers ):
        pass

    #window.push_handlers(pyglet.window.event.WindowEventLogger())

def fschedule( fs, dt ):
    pyglet.clock.schedule_interval( fs, dt )

def rRun():
    pyglet.app.run()

