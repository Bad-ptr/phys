using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

using System.Runtime.InteropServices;

namespace phys.Vectors
{
    public class Vector2
    {
        [StructLayout(LayoutKind.Explicit, Size = 4)]
        private struct IntFloat
        {
            [FieldOffset(0)]
            public float floatValue;

            [FieldOffset(0)]
            public int intValue;

            // redundant assignment to avoid any complaints about uninitialized members
            IntFloat(int x)
            {
                floatValue = 0;
                intValue = x;
            }

            IntFloat(float x)
            {
                intValue = 0;
                floatValue = x;
            }

            public static explicit operator float(IntFloat x)
            {
                return x.floatValue;
            }

            public static explicit operator int(IntFloat x)
            {
                return x.intValue;
            }

            public static explicit operator IntFloat(int i)
            {
                return new IntFloat(i);
            }
            public static explicit operator IntFloat(float f)
            {
                return new IntFloat(f);
            }
        }

        public unsafe float InvSqrt(float x)
        {
           /* float xhalf = 0.5f * x;
            int i = BitConverter.ToInt32(BitConverter.GetBytes(x), 0);
            i = 0x5f3759df - (i >> 1);
            x = BitConverter.ToSingle(BitConverter.GetBytes(i), 0);
            x = x * (1.5f - xhalf * x * x);
            return x;*/
            float xhalf = 0.5f * x;
            int i = *(int*)&x; // get bits for floating value
            i = 0x5f375a86 - (i >> 1); // gives initial guess y0
            x = *(float*)&i; // convert bits back to float
            x = x * (1.5f - xhalf * x * x); // Newton step, repeating increases accuracy
            return x;
        }

        public float x, y;

        public Vector2()
        {
            this.x = 0;
            this.y = 0;
        }
        public Vector2(float s)
        {
            this.x = s;
            this.y = s;
        }
        public Vector2(float _x, float _y)
        {
            this.x = _x;
            this.y = _y;
        }
        public Vector2(Vector2 v)
        {
            this.x = v.x;
            this.y = v.y;
        }

        public Vector2 Clone()
        {
            return new Vector2(this);
        }
        override public string ToString()
        {
            return "Vec2(X = " + this.x.ToString() + ", Y = "
                + this.y.ToString() + ");";
        }
        public Vector2 Sset( float x, float y)
        {
            this.x = x;
            this.y = y;
            return this;
        }
        public Vector2 Vset( Vector2 v )
        {
            this.x = v.x;
            this.y = v.y;
            return this;
        }
        public Vector2 Sadd(float s)
        {
            this.x += s;
            this.y += s;

            return this;
        }
        public Vector2 Ssub(float s)
        {
            this.x -= s;
            this.y -= s;

            return this;
        }
        public Vector2 Smul(float s)
        {
            this.x *= s;
            this.y *= s;

            return this;
        }
        public Vector2 Sdiv(float s)
        {
            this.x /= s;
            this.y /= s;

            return this;
        }

        public Vector2 Vadd(Vector2 v)
        {
            this.x += v.x;
            this.y += v.y;

            return this;
        }
        public Vector2 Vsub(Vector2 v)
        {
            this.x -= v.x;
            this.y -= v.y;

            return this;
        }
        public Vector2 Vmul(Vector2 v)
        {
            this.x *= v.x;
            this.y *= v.y;

            return this;
        }
        public Vector2 Vdiv(Vector2 v)
        {
            this.x /= v.x;
            this.y /= v.y;

            return this;
        }

        public Vector2 Zero()
        {
            this.x = 0;
            this.y = 0;

            return this;
        }
        public Vector2 Inv()
        {
            this.x = -this.x;
            this.y = -this.y;

            return this;
        }
        public float Len()
        {
            //return 1.0f/this.InvSqrt(this.x * this.x + this.y * this.y);
            return (float)Math.Sqrt(this.x * this.x + this.y * this.y);
        }
		public float InvLen()
		{
			return this.InvSqrt(this.x * this.x + this.y * this.y);
		}
        public Vector2 Norm()
        {
            var ilen = this.InvLen();
           // if (ilen > 0.0f)
           // {
                this.x *= ilen;
                this.y *= ilen;
           // }

            return this;
        }
        public float Dot( Vector2 v )
        {
            return this.x * v.x + this.y * v.y;
        }

    }

}
