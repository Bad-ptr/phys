using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Runtime.InteropServices;
using System.Text;
using System.Threading;
using System.Threading.Tasks;
using System.Windows.Forms;

using phys;
using phys.Particles;
using phys.Simulations;

namespace physTryOnCsharp
{
    public partial class Form1 : Form
    {
        public Particle part = new Particle ( 50, 50, 50, 50 );
        public Simulation s = new Simulation ();

		
        System.Threading.TimerCallback tcb;
        System.Threading.Timer kphystimer;
		
        System.Threading.TimerCallback cgtcb;
        System.Threading.Timer kcgtimer;

        void kphyssolve ( Object stateInfo )
        {
          //  lock ( s )
          //  {
                s.Upd ( (int)System.Environment.TickCount );
           // }
        }

        void kcgsolve ( Object stateInfo )
        {
            //lock ( s )
           // {
                s.cg.dupd ( s.bodyes, 3, 50 );
           // }
        }

        public Form1 ()
        {
            InitializeComponent ();
            s.Rand ( 1000 );
            s.Badd ( part );

            this.Form1_ResizeEnd ( null, null );

            tcb = kphyssolve;
            kphystimer = new System.Threading.Timer ( tcb, null, 0, 60 );

            cgtcb = kcgsolve;
            kcgtimer = new System.Threading.Timer ( cgtcb, null, 0, 100 );

        }

        private void Form1_Paint ( object sender, PaintEventArgs e )
        {
            e.Graphics.DrawImageUnscaled ( bmp, 0, 0 );
        }

        protected override void OnPaintBackground ( PaintEventArgs e )
        {
            //Disable background drawing...
        }

        private void Form1_KeyDown ( object sender, KeyEventArgs e )
        {
            switch ( e.KeyCode )
            {
            case Keys.Right:
                lock ( s.bodyes[0] )
                {
                    ( (Particle)s.bodyes[ 0 ] ).pos.x += 2.5f;
                    return;
                }
            case Keys.Left:
                lock ( s.bodyes[0] )
                {
                    ( (Particle)s.bodyes[ 0 ] ).pos.x -= 2.5f;
                    return;
                }
            case Keys.Up:
                lock ( s.bodyes[0] )
                {
                    ( (Particle)s.bodyes[ 0 ] ).pos.y -= 2.5f;
                    return;
                }

            case Keys.Down:
                lock ( s.bodyes[0] )
                {
                    ( (Particle)s.bodyes[ 0 ] ).pos.y += 2.5f;
                    return;
                }
            case Keys.Space:
                lock ( s )
                {
                    s.bodyes.Clear ();
                    s.Rand ( 25000 );
                    //s.cg.csubd(5);
                    // s.cg.ClearPL();
                    //s.cg.llocate(s.bodyes);
                }
                return;
            case Keys.A:
                s.cg.ClearPL ();
                return;
            case Keys.S:
                s.cg.llocate ( s.bodyes );
                return;
            case Keys.Escape:
                this.Close ();
                return;
            default:
                return;
            }
         
        }

        private void Form1_ResizeEnd ( object sender, EventArgs e )
        {
            lock ( s )
            {
                s.Resize ( (float)this.Size.Width, (float)this.Size.Height );
            }
            bmp = new Bitmap ( this.Size.Width, this.Size.Height );
            g = Graphics.FromImage ( bmp );
        }

        private void DrawCg ( kMath.CollGrid cg )
        {
            if ( cg != null )
            {
                    g.DrawRectangle ( ppen, cg.p0.x, cg.p0.y,
                                     cg.p1.x - cg.p0.x, cg.p1.y - cg.p0.y );

                    if ( cg.CL[ 0 ] != null )
                    {
                        foreach ( kMath.CollGrid cgl in cg.CL )
                        {
                            DrawCg ( cgl );
                        }
                        //Parallel.ForEach(cg.CL, DrawCg);
                    }
            }
        }

        public void DrawParticle ( phys.Particles.Particle p )
        {
            if ( p == null )
                return;
            //lock ( p )
            //{
                g.DrawEllipse ( ppen, p.pos.x, p.pos.y, p.r, p.r );
           // }
        }

        private void timer2_Tick (object sender, EventArgs e)
		{
			this.g.Clear (Color.Black);
			// lock (s.bodyes)
			//  {
//            lock (s)
//            {
			//lock (s.bodyes) {
				foreach (Particle p in s.bodyes) {
					this.g.DrawEllipse (ppen, p.pos.x - p.r, p.pos.y - p.r, p.r * 2, p.r * 2);
					//this.g.DrawString(p.pos.ToString(), fnt, brsh, p.pos.x, p.pos.y);
				}
           
				//Parallel.ForEach(this.s.bodyes, this.DrawParticle);
			//}
			
			//  }
			// this.g.DrawString((this.s.dt*0.0000001).ToString(), fnt, brsh, 50, 50);
			//   lock (s.cg)
			//  {
			DrawCg (s.cg);
			//   }
//            }
			Invalidate ();
		}
    }
}
