using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Collections;


using phys.Vectors;
using phys.Particles;


namespace phys
{
    public class kMath
    {
        public static int PtoPCollide( Particle p1, Particle p2 )
        {
//            if ( p1 == null || p2 == null )
//                return 0;

            Vector2 dx = p2.pos.Clone();
            dx.Vsub(p1.pos);

            float r = p1.r + p2.r - dx.Len();

            if ( r > 0.0f )
            {
                Vector2 cn = dx.Norm();

				float pr = r / ( p1.mass + p2.mass ) * 0.4f;

                p1.pos.x -= cn.x * ( p2.mass * pr );
				p1.pos.y -= cn.y * ( p2.mass * pr );

                p2.pos.x += cn.x * ( p1.mass * pr );
				p2.pos.y += cn.y * ( p1.mass * pr );

                return 1;
            }

            return 0;
        }


        public static void CgPtPCollide ( CollGrid cg )
        {
           if ( cg == null )
                return;

            Particle p1, p2;
            int l = cg.PL.Count;

            for (int i = 0; i < l; i++)
            {
                p1 = (Particle)cg.PL[i];
				//Parallel.For(i, l, index =>
                for (int j = i; j < l; j++)
                {
                    p2 = (Particle)cg.PL[j];
                    PtoPCollide(p1, p2);
                }//);
            }

            if (cg.CL[0] != null){
                foreach (CollGrid clg in cg.CL)
                    CgPtPCollide(clg);
				//lock(cg.CL){
                //Parallel.ForEach(cg.CL, CgPtPCollide);
				//}
			}
        }

        public class CollGrid
        {
            public Vector2 p0;
            public Vector2 p1;
            public ArrayList PL;
            public CollGrid[] CL;
            public int tnump;

            public CollGrid()
            {
                this.p0 = this.p1 = new Vector2(0.0f,0.0f);
                this.PL = new ArrayList();
                CL = new CollGrid[4];
                tnump = 0;
            }
            public CollGrid(Vector2 p0, Vector2 p1)
            {
                this.p0 = p0;
                this.p1 = p1;
                PL = new ArrayList();
                CL = new CollGrid[4];
                tnump = 0;
            }
            public CollGrid(float x0, float y0, float x1, float y1)
            {
                Vector2 p0 = new Vector2(x0, y0);
                Vector2 p1 = new Vector2(x1, y1);
                this.p0 = p0;
                this.p1 = p1;
                PL = new ArrayList();
                CL = new CollGrid[4];
                tnump = 0;
            }

            public int pcontain(Particle p)
            {
                if ( (p.pos.x - p.r < this.p1.x && p.pos.x + p.r > this.p0.x)
                    && (p.pos.y - p.r < this.p1.y && p.pos.y + p.r > this.p0.y) )
                {
                    return 1;
                }
                return 0;
            }

            public void resize(Vector2 np0, Vector2 np1)
            {
                this.p0 = np0;
                this.p1 = np1;

                if (this.CL[0] != null)
                {
                    Vector2 ser = np0.Clone();
                    ser.Vadd(np1);
                    ser.Smul(0.5f);

                    this.CL[0].resize(this.p0, ser);

                    this.CL[1].resize(new Vector2(ser.x,this.p0.y),
                        new Vector2(this.p1.x,ser.y));

                    this.CL[2].resize(new Vector2(this.p0.x,ser.y),
                        new Vector2(ser.x,this.p1.y));

                    this.CL[3].resize(ser,this.p1);

                }
            }

            public void csubd(int l)
            {
                if (l < 1)
                    return;

                l-=1;

                if (this.CL[0] == null)
                {
                    Vector2 ser = this.p0.Clone();
                    ser.Vadd(this.p1);
                    ser.Smul(0.5f);

                    this.CL[0] = new CollGrid(this.p0, ser);
                    this.CL[1] = new CollGrid(ser.x, this.p0.y, this.p1.x, ser.y);
                    this.CL[2] = new CollGrid(this.p0.x, ser.y, ser.x, this.p1.y);
                    this.CL[3] = new CollGrid(ser, this.p1);
                }

                this.CL[0].csubd(l);
                this.CL[1].csubd(l);
                this.CL[2].csubd(l);
                this.CL[3].csubd(l);

            }
            public void dsubd ( int l, int nmp )
            {
                if ( l < 1 )
                    return;

                if ( tnump > nmp )
                {
                    l -= 1;
     
                    if ( this.CL[0] == null )
                    {
                        Vector2 ser = new Vector2( this.p0.x, this.p0.y );
                        ser.Vadd ( this.p1 ).Smul ( 0.5f );

                        this.CL[0] = new CollGrid ( this.p0, ser );
                        this.CL[1] = new CollGrid ( ser.x, this.p0.y, this.p1.x, ser.y );
                        this.CL[2] = new CollGrid ( this.p0.x, ser.y, ser.x, this.p1.y );
                        this.CL[3] = new CollGrid ( ser, this.p1 );
                    }

                    this.CL[0].dsubd(l, nmp);
                    this.CL[1].dsubd(l, nmp);
                    this.CL[2].dsubd(l, nmp);
                    this.CL[3].dsubd(l, nmp);
                }
                else
                {
                    this.CL[0] = null;
                    this.CL[1] = null;
                    this.CL[2] = null;
                    this.CL[3] = null;
                }
            }

            public int locate ( Particle p )
            {

                if ( this.pcontain ( p ) == 1 )
                {
                    int r = 0;
    
                    if ( this.CL[0] != null )
                    {

                        foreach ( CollGrid cg in this.CL )
                        {
                            if ( cg.pcontain ( p ) == 1 )
                            {
                                r += cg.locate ( p );
                            }
                        }

                        if ( r > 0 )
                        {
                            tnump += 1;
                            return r;
                        }

                    }
     
                        this.PL.Add ( p );

                    tnump += 1;
                    return 1;
                }

                return 0;
            }

            public void llocate(List<Particle> Plist)
            {
               foreach (Particle p in Plist )
               {
                    this.locate(p);
               }
            }

            public void ClearPL()
            {
                this.PL.Clear();
                tnump = 0;

                if (this.CL[0] == null)
                    return;

               foreach (CollGrid cg in this.CL)
                {
                    cg.ClearPL();
                }

            }

            public void Clear()
            {
                this.PL.Clear();
                this.CL[0] = null;
                this.CL[1] = null;
                this.CL[2] = null;
                this.CL[3] = null;
           }

            public void dupd(List<Particle> Plist, int l, int nmp)
            {
                this.ClearPL();
                this.llocate(Plist);
                this.dsubd(l, nmp);
                
            }

        }
    }
}
