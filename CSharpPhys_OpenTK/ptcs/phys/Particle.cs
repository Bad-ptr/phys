using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

using phys.Vectors;

namespace phys.Particles
{
    public class Particle
    {
        public float r, mass, kf;
        public Vector2 pos, oldpos, force, vel;

        public Particle()
        {
            this.r = this.mass = this.kf = 0.9f;
            force = new Vector2();
			vel = new Vector2();
			pos =  new Vector2();
			oldpos = new Vector2();
        }
        public Particle(float r, float mass, float x, float y)
        {
            this.r = r;
            this.mass = mass;
            this.kf = 0.999f;
            this.force = new Vector2();
            this.vel = new Vector2();
            this.oldpos = new Vector2(x, y);
			this.pos = new Vector2(x, y);
        }
        public Particle(float r, float mass, Vector2 pos)
        {
            this.r = r;
            this.mass = mass;
            this.oldpos = pos.Clone();
			this.pos =  pos.Clone();
        }
        public Particle(float r, float mass, float kf, Vector2 pos,
            Vector2 force, Vector2 vel)
        {
            this.r = r;
            this.mass = mass;
            this.oldpos = pos.Clone();
			this.pos =  pos.Clone();
            this.kf = kf;
            this.force = force;
            this.vel = vel;
        }

        public Particle Upd ( float dt )
        {
            //lock(this)
            //{
            this.vel.x = (this.pos.x - this.oldpos.x) * this.kf/*- this.vel.x * this.kf*/;
            this.vel.y = (this.pos.y - this.oldpos.y) * this.kf/*- this.vel.y * this.kf*/;
            //Vector2 acc = this.force.Clone();

            //this.force.Zero();

           // acc.Sdiv(this.mass).Smul(dt);
            //this.vel.Vadd(acc);
            //this.vel.Vsub(vel.Clone().Smul(this.kf));
/*

            if (vel.Len() > 2)
            {
                vel.Norm();
                vel.Smul(2);
            }
*/

            oldpos.x = pos.x;
			oldpos.y = pos.y;
			
            this.pos.Vadd(this.vel/*.Clone().Smul(dt * dt * 0.5f)*/);

            return this;
			//}
        }
    }
}
