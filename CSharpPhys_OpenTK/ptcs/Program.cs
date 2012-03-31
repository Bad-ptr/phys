using System;
using System.Collections.Generic;
using System.Linq;
using System.Windows.Forms;
using System.Drawing;

using System.Threading;
using System.Threading.Tasks;

using OpenTK;
using OpenTK.Graphics;
//using OpenTK.Graphics.OpenGL;


using phys.Particles;
using phys.Simulations;

namespace physTryOnCsharp
{
    public class Program : GameWindow
    {
		public Particle part = new Particle (50, 50, 50, 50);
		public Simulation s = new Simulation ();
		
		
		
		System.Threading.TimerCallback tcb;
		System.Threading.Timer kphystimer;
		
		System.Threading.TimerCallback cgtcb;
		System.Threading.Timer kcgtimer;
		

		void kphyssolve ( Object stateInfo )
		{
			//lock ( this.s )
			//{
				this.s.Upd ( (int)System.Environment.TickCount );
                this.s.cg.dupd ( s.bodyes, 4, 50 );
			//}
		}

		void kcgsolve ( Object stateInfo )
		{
			//lock ( this.s )
			//{
				this.s.cg.dupd ( s.bodyes, 4, 50 );
			//}
		}
		
		public Program () : base( 1424, 800, new GraphicsMode(16,16) )
		{}
		
		protected override void OnLoad (EventArgs e)
		{
			base.OnLoad (e);
			
			GL.ClearColor (Color.MidnightBlue);
			GL.Enable (EnableCap.DepthTest);
			
			GL.Ortho (0, 1424, 0, 800, -1.0, 1.0);
			
			this.s.Rand (1000);
			this.s.Badd (this.part);
			
			tcb = kphyssolve;
			kphystimer = new System.Threading.Timer (tcb, null, 0, 60);

			//cgtcb = kcgsolve;
			//kcgtimer = new System.Threading.Timer (cgtcb, null, 0, 100);
		}
		
		protected override void OnResize (EventArgs e)
		{
			base.OnResize (e);

			GL.Viewport (0, 0, Width, Height);

			double aspect_ratio = Width / (double)Height;
		
			this.s.Resize ((float)Width, (float)Height);
		}
		
		
		protected override void OnUpdateFrame (FrameEventArgs e)
		{
			base.OnUpdateFrame (e);

			if (Keyboard [OpenTK.Input.Key.Escape]) {
				this.Exit ();
				return;
			} else if (Keyboard [OpenTK.Input.Key.Left]) {
				((Particle)s.bodyes [0]).pos.x -= 2.5f;
				return;
			} else if (Keyboard [OpenTK.Input.Key.Right]) {
				((Particle)s.bodyes [0]).pos.x += 2.5f;
				return;
			} else if (Keyboard [OpenTK.Input.Key.Up]) {
				((Particle)s.bodyes [0]).pos.y += 2.5f;
				return;
			} else if (Keyboard [OpenTK.Input.Key.Down]) {
				((Particle)s.bodyes [0]).pos.y -= 2.5f;
				return;
			} else if (Keyboard [OpenTK.Input.Key.Space]) {
				((Particle)s.bodyes [0]).r = 80;
				Thread.Sleep(10);
				((Particle)s.bodyes [0]).r = 25;
				return;
			}

		}
		
		public void DrawCircle( float x, float y, float r )
		{
			float alp, k = 360/10;
			GL.Begin(BeginMode.LineStrip);
			for(int i = 0; i <= 10; i++){
				alp = k*i * (float)Math.PI / 180.0f;
				GL.Vertex3( r * Math.Cos(alp) + x, r * (float)Math.Sin(alp) + y, 0);
			}
			GL.End();
		}
		
		public void DrawParticles ()
		{
			foreach (Particle p in this.s.bodyes) {
			//Parallel.ForEach( this.s.bodyes, p => {
				DrawCircle (p.pos.x, p.pos.y, p.r);
			}//);
		}
		
		protected override void OnRenderFrame (FrameEventArgs e)
		{
			base.OnRenderFrame (e);

			GL.Clear (ClearBufferMask.ColorBufferBit | ClearBufferMask.DepthBufferBit);
			/*
			Matrix4 lookat = Matrix4.LookAt (0, 5, 5, 0, 0, 0, 0, 1, 0);
			GL.MatrixMode (MatrixMode.Modelview);
			GL.LoadMatrix (ref lookat);
            
			angle += rotation_speed * (float)e.Time;
			GL.Rotate (angle, 0.0f, 1.0f, 0.0f);*/

			DrawParticles ();

			this.SwapBuffers ();
			//Thread.Sleep (1);
		}
		
        /// <summary>
        /// Главная точка входа для приложения.
        /// </summary>
        [STAThread]
        public static void Main ()
		{
			using (Program prog = new Program()) {
				//Utilities.SetWindowTitle (prog);
				prog.Run( 30.0, 0.0 );
			}
		}
    }
}
