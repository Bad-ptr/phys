using System;
using System.Linq;
using System.Text;
using System.Collections;
using System.Collections.Concurrent;
using System.Collections.Generic;
using System.Threading.Tasks;


using phys.Particles;
using phys.Vectors;
using phys;

namespace phys.Simulations
{
    public class Simulation
    {
        public List<Particle> bodyes;
        public Vector2 size { get; set; }
        public kMath.CollGrid cg;
        public static Vector2 nullv = new Vector2(0.0f, 0.0f);
        public float dt = 0.0f;

        public Simulation()
        {
            bodyes = new List<Particle>();
            size = new Vector2(500.0f, 500.0f);
            cg = new kMath.CollGrid(nullv, this.size);
            dt = 0.0f;

        }

        public Particle Badd(Particle b)
        {
            lock (bodyes)
            {
                this.bodyes.Add(b);
                this.cg.locate(b);
            }
            return b;
        }

        public int Rand(int n)
        {
            Random r = new Random();
            float m;
            Particle kp = new Particle(30f, 500f, 150, 150);
            this.Badd(kp);
            for (int i = 0; i < n; i++)
            {
                m = r.Next(15);
                Particle p = new Particle(3.0f+m, 1.0f+m,
                    r.Next((int)this.size.x-50), r.Next((int)this.size.y-50));
                this.Badd(p);
            }

            return 0;
        }

        public void Resize(float nx1, float ny1)
        {
            this.size.x = nx1;
            this.size.y = ny1;
            this.cg.resize(nullv, this.size);
            //this.cg.Clear();
        }

        public int wcollide ()
		{
			lock (this.bodyes) {
				//foreach ( Particle p in this.bodyes )
				
				Parallel.ForEach (this.bodyes, p =>
				{
					if ((p.pos.x + p.r + 20) > this.size.x) {
						p.vel.x = -p.vel.x * 0.2f;
						p.pos.x = this.size.x - p.r - 20.0f;
					}
					if ((p.pos.y + p.r + 100) > this.size.y) {
						p.vel.y = -p.vel.y * 0.2f;
						p.pos.y = this.size.y - p.r - 100.0f;
					}

					if ((p.pos.x - p.r) < 0.0f) {
						p.vel.x = -p.vel.x * 0.2f;
						p.pos.x = p.r + 0.1f;
					}
					if ((p.pos.y - p.r) < 0.0f) {
						p.vel.y = -p.vel.y * 0.2f;
						p.pos.y = p.r + 0.1f;
					}

				});
			}

			return 0;
		}
        public int pwcollide( Particle p )
        {
                if ((p.pos.x + p.r + 20f) > this.size.x)
                {
                   // p.vel.x = -p.vel.x * 0.2f;
                    p.pos.x = this.size.x - p.r - 20.1f;
                }
                if ((p.pos.y + p.r + 100f) > this.size.y)
                {
                  //  p.vel.y = -p.vel.y * 0.2f;
                    p.pos.y = this.size.y - p.r - 100.1f;
                }

                if ((p.pos.x - p.r) < 0.0f)
                {
                  //  p.vel.x = -p.vel.x * 0.2f;
                    p.pos.x = p.r;
                }
                if ((p.pos.y - p.r) < 0.0f)
                {
                   // p.vel.y = -p.vel.y * 0.2f;
                    p.pos.y = p.r;
                }

            return 0;
        }
        public void pUpd(Particle p)
        {
           // lock (p)
          //  {
                //p.force.y += 0.05f * p.mass;
				p.pos.y += 0.01f;
                p.Upd(this.dt*0.0000001f);
                pwcollide(p);
           // }
        }
        public int Upd (int t)
		{
			this.dt = t - this.dt;
			kMath.CgPtPCollide (this.cg);

			foreach (Particle p in bodyes) {
			//Parallel.ForEach (this.bodyes, p => {
				p.pos.y -= 0.1f;
				p.Upd (this.dt * 0.00000001f);
				pwcollide (p);
			}//);

			return 0;
		}

    }
}
