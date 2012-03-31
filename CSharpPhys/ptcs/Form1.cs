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
        Bitmap bmp;
        Graphics g;
        Pen ppen = new Pen ( Color.Red );
        System.Threading.TimerCallback tcb;
        System.Threading.Timer kphystimer;
        System.Threading.TimerCallback cgtcb;
        System.Threading.Timer kcgtimer;
        System.Threading.TimerCallback dtcb;
        System.Threading.Timer kdrawtimer;
        Font fnt = new Font ( "Times New Roman", 15.0f );
        Brush brsh = new SolidBrush ( Color.Green );
        Thread kphysthread;// = new Thread(kphysthreadstart);
        Thread kcgthread;
        // static System.Timers.Timer kphystimer;

        [DllImport("user32.dll", CharSet = CharSet.Auto, ExactSpelling = true)]
        public static extern short GetAsyncKeyState ( int vkey );

        [DllImport( "gdi32.dll" )]
        static extern bool BitBlt ( IntPtr hdc, int nXDest, int nYDest, int nWidth, int nHeight,
            IntPtr hdcSrc, int nXSrc, int nYSrc, uint dwRop );

        void kphyssolve ( Object stateInfo )
        {
            //lock(s.cg){
            //   lock(s.bodyes){


          //  lock ( s )
          //  {
                //s.cg.llocate(this.s.bodyes)
                s.Upd ( (int)System.Environment.TickCount );

                //this.s.cg.ClearPL();
                //
                //s.cg.dupd(s.bodyes, 5, 50);
                // }
                //this.s.cg.dupd(s.bodyes, 5, 1);
                //s.cg.ClearPL();

                //  System.Console.WriteLine("heelo");

                //   }
           // }
        }

        void kcgsolve ( Object stateInfo )
        {
            //lock ( s )
           // {
                s.cg.dupd ( s.bodyes, 3, 50 );
           // }
        }

        void kcgupd ( object source, System.Timers.ElapsedEventArgs e )
        {
            //lock (s)
            //   {
            //   this.s.cg.ClearPL();
            //   s.cg.llocate(this.s.bodyes);
            //   this.s.cg.dupd(s.bodyes, 2, 50);
            //s.cg.Clear();
            // this.s.cg.ClearPL();
            // }

            //s.cg.llocate(this.s.bodyes);
        }

        void kphysthreadstart ()
        {
            //  System.Threading.TimerCallback tcb = kphyssolve;
            //  System.Threading.Timer kphystimer = new System.Threading.Timer(tcb,null,1,1);
            //kphystimer.Elapsed += new System.Timers.ElapsedEventHandler(kphyssolve);
            //kphystimer.Start();
            //System.Console.WriteLine("Hello ! physthread had been started !");
        }

        void kcgthreadstart ()
        {
/*            kcgtimer = new System.Timers.Timer(100);
            kcgtimer.Elapsed += new System.Timers.ElapsedEventHandler(kcgupd);
            kcgtimer.Start();*/
        }

        public Form1 ()
        {
            InitializeComponent ();
            s.Rand ( 1000 );
            s.Badd ( part );
            bmp = new Bitmap ( (int)s.size.x, (int)s.size.y );
            g = Graphics.FromImage ( bmp );

            this.Form1_ResizeEnd ( null, null );

            //kphysthread = new Thread(kphysthreadstart);
            //kphysthread.IsBackground = true;
            //kphysthread.Priority = ThreadPriority.Highest;
            //kphysthread.Start();

            tcb = kphyssolve;
            kphystimer = new System.Threading.Timer ( tcb, null, 0, 60 );

            cgtcb = kcgsolve;
            kcgtimer = new System.Threading.Timer ( cgtcb, null, 0, 100 );

            // dtcb = kdraw;
            //kdrawtimer = new System.Threading.Timer(dtcb, null, 10, 100);

            /*kcgthread = new Thread(kcgthreadstart);
            kcgthread.IsBackground = true;
            kcgthread.Start();*/

            g.InterpolationMode = System.Drawing.Drawing2D.InterpolationMode.Low;
            g.CompositingQuality = System.Drawing.Drawing2D.CompositingQuality.HighSpeed;
            g.SmoothingMode = System.Drawing.Drawing2D.SmoothingMode.HighSpeed;
            g.PixelOffsetMode = System.Drawing.Drawing2D.PixelOffsetMode.HighSpeed;
            g.CompositingMode = System.Drawing.Drawing2D.CompositingMode.SourceCopy;

            //s.cg.csubd(4);
        }

        private void Form1_Paint ( object sender, PaintEventArgs e )
        {
            /*  Graphics g = e.Graphics;
            foreach (Particle p in s.bodyes)
            {
                g.DrawEllipse(new Pen(Color.Red), p.pos.x, p.pos.y, p.r, p.r);
            }*/
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
            //
//
//private void Form1_KeyDown( object sender, KeyEventArgs e )
//{
//   byte[] keys = new byte[255];
//
//   GetKeyboardState (keys);
//
//   if( keys[(int)Keys.Up] == 129 && keys[(int)Keys.Right] == 129 )
//   {
//       Console.WriteLine ("Up Arrow key and Right Arrow key down.");
//   }
//}
         
        }

        private void timer1_Tick ( object sender, EventArgs e )
        {
            //this.s.Upd();
            // this.s.cg.dupd(s.bodyes, 2, 50);
            //this.s.cg.ClearPL();
            // lock (s)
            //{
            //   s.Upd((int)System.Environment.TickCount);
            //this.s.cg.ClearPL();
            //    s.cg.dupd(s.bodyes, 5, 50);
            //}
        }

        private void Form1_ResizeEnd ( object sender, EventArgs e )
        {
            lock ( s )
            {
                s.Resize ( (float)this.Size.Width, (float)this.Size.Height );
            }
            //s.cg.csubd(1);
            // s.cg.ClearPL();
            //s.cg.llocate(s.bodyes);
            bmp = new Bitmap ( this.Size.Width, this.Size.Height );
            g = Graphics.FromImage ( bmp );
        }

        private void DrawCg ( kMath.CollGrid cg )
        {
            if ( cg != null )
            {
                //lock ( cg )
                //{
                    /*this.g.DrawLine(ppen, cg.p0.x, cg.p0.y, cg.p0.x, cg.p1.y);
                this.g.DrawLine(ppen, cg.p0.x, cg.p1.y, cg.p1.x, cg.p1.y);
                this.g.DrawLine(ppen, cg.p1.x, cg.p1.y, cg.p1.x, cg.p0.y);
                this.g.DrawLine(ppen, cg.p1.x, cg.p0.y, cg.p0.x, cg.p0.y);*/
                    g.DrawRectangle ( ppen, cg.p0.x, cg.p0.y,
                                     cg.p1.x - cg.p0.x, cg.p1.y - cg.p0.y );
                    //this.g.DrawString(cg.PL.Count.ToString(),
                    //    fnt, brsh, cg.p1.x/2, cg.p0.y/2);
                    //this.g.DrawString(cg.CL.Length.ToString(),
                    //    fnt, brsh, cg.p1.x, cg.p1.y);

                    if ( cg.CL[ 0 ] != null )
                    {
                        foreach ( kMath.CollGrid cgl in cg.CL )
                        {
                            DrawCg ( cgl );
                        }
                        //Parallel.ForEach(cg.CL, DrawCg);
                    }
                //}
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
