/*
 * kbtypes.h
 *
 *  Created on: 06.05.2010
 *      Author: constantin
 */

#ifndef KBTYPES_H_
#define KBTYPES_H_


#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <stdio.h>


#define GEN_OP_BINFUNC_DECL(TYPE, FNAME, OP)                \
	static inline TYPE TYPE##_##FNAME( TYPE _f, TYPE _s )   \
	{                                                       \
		return (TYPE)(_f OP _s);                            \
	};

#define GEN_OP_UNFUNC_DECL(TYPE, FNAME, OPpre, OPpost)  \
	static inline TYPE TYPE##_##FNAME( TYPE _f ){       \
		return (TYPE)(OPpre _f OPpost);                 \
	};

#define GEN_NEGFUNC_DECL(TYPE)                  \
	static inline TYPE TYPE##_neg( TYPE _f ){   \
		return -(TYPE)_f;                       \
	};

#define GEN_ABSFUNC_DECL(TYPE)                  \
	static inline TYPE TYPE##_mod( TYPE _f ){   \
		if( _f < 0 ){                           \
                                                \
			return TYPE##_neg( _f );            \
		}else                                   \
			return _f;                          \
	};

#define GEN_POWFUNC_DECL(TYPE)                              \
	static inline TYPE TYPE##_pow( TYPE _f, TYPE _pow ){    \
		return (TYPE)pow( _f, _pow );                       \
	};

#define GEN_CMP_FUNC(TYPE)                     	    \
	static inline int TYPE##_cmp( TYPE _f, TYPE _s ){ \
		if( _f > _s ){                             	\
			return 1;                                 \
		}else if( _f < _s ){                          \
			return -1;                               \
		}else									\
			return 0;                              \
		return 0;                                 \
	};

#define GEN_CP_FUNC(TYPENAME)                        \
	static inline void * TYPENAME##_cp( TYPENAME _f ){\
		TYPENAME * ret = malloc(sizeof(TYPENAME));   \
		*ret=_f;                                      \
		return ret;                                  \
	};

#define GEN_FLOAT_REM_FUNC(TYPE)                    \
    static inline TYPE TYPE##_rem( TYPE _f, TYPE _s ){   \
        return fmod( _f, _s );                      \
    };


//==============================================================================


#define GEN_INT_TYPE_DECL(BASETYPE,TYPENAME)\
	typedef BASETYPE TYPENAME;           	\
	GEN_OP_BINFUNC_DECL(TYPENAME,add,+)  	\
	GEN_OP_BINFUNC_DECL(TYPENAME,sub,-)     \
	GEN_OP_BINFUNC_DECL(TYPENAME,mul,*)     \
	GEN_OP_BINFUNC_DECL(TYPENAME,div,/)     \
	GEN_OP_BINFUNC_DECL(TYPENAME,rem,%)     \
	GEN_OP_BINFUNC_DECL(TYPENAME,lshift,<<) \
	GEN_OP_BINFUNC_DECL(TYPENAME,rshift,>>) \
	GEN_OP_BINFUNC_DECL(TYPENAME,and,&)     \
	GEN_OP_BINFUNC_DECL(TYPENAME,or,|)      \
	GEN_OP_BINFUNC_DECL(TYPENAME,xor,^)     \
	GEN_OP_UNFUNC_DECL(TYPENAME,inv,~,)     \
	GEN_OP_UNFUNC_DECL(TYPENAME,preinc,++,) \
	GEN_OP_UNFUNC_DECL(TYPENAME,postinc,,++)\
	GEN_OP_UNFUNC_DECL(TYPENAME,predec,--,) \
	GEN_OP_UNFUNC_DECL(TYPENAME,postdec,,--)\
	GEN_NEGFUNC_DECL(TYPENAME)              \
	GEN_ABSFUNC_DECL(TYPENAME)              \
	GEN_POWFUNC_DECL(TYPENAME)              \
	GEN_CMP_FUNC(TYPENAME)                  \
	GEN_CP_FUNC(TYPENAME)

#define GEN_FLOAT_TYPE_DECL(BASETYPE,TYPENAME)  \
	typedef BASETYPE TYPENAME;                  \
	GEN_OP_BINFUNC_DECL(TYPENAME,add,+)         \
	GEN_OP_BINFUNC_DECL(TYPENAME,sub,-)         \
	GEN_OP_BINFUNC_DECL(TYPENAME,mul,*)         \
	GEN_OP_BINFUNC_DECL(TYPENAME,div,/)         \
    GEN_FLOAT_REM_FUNC(TYPENAME)                \
	GEN_OP_UNFUNC_DECL(TYPENAME,preinc,++,)     \
	GEN_OP_UNFUNC_DECL(TYPENAME,postinc,,++)    \
	GEN_OP_UNFUNC_DECL(TYPENAME,predec,--,)     \
	GEN_OP_UNFUNC_DECL(TYPENAME,postdec,,--)    \
	GEN_NEGFUNC_DECL(TYPENAME)                  \
	GEN_ABSFUNC_DECL(TYPENAME)                  \
	GEN_POWFUNC_DECL(TYPENAME)                  \
	GEN_CMP_FUNC(TYPENAME)                      \
	GEN_CP_FUNC(TYPENAME)

#define GEN_PTR_TYPE_DECL(BASETYPE,TYPENAME)    \
	typedef BASETYPE TYPENAME;                  \
	GEN_OP_BINFUNC_DECL(TYPENAME,sub,-)         \
	GEN_OP_UNFUNC_DECL(TYPENAME,preinc,++,)     \
	GEN_OP_UNFUNC_DECL(TYPENAME,postinc,,++)    \
	GEN_OP_UNFUNC_DECL(TYPENAME,predec,--,)     \
	GEN_OP_UNFUNC_DECL(TYPENAME,postdec,,--)    \
	GEN_CMP_FUNC(TYPENAME)                      \
	GEN_CP_FUNC(TYPENAME)
static inline int ptr_cmp( void * p1, void * p2 ){
	if( p1 > p2 ){
		return 1;
	}else if( p1 < p2 ){
		return -1;
	}else
		return 0;
	return 0;
};
static inline void * ptr_cp( void * p ){
	void * ret = malloc( sizeof(void *) );
	ret = p;
	return ret;
};


//==============================================================================


GEN_INT_TYPE_DECL(unsigned char,uchar)
GEN_INT_TYPE_DECL(unsigned int,uint)
#define KHASH uint // used for storing hashes
GEN_INT_TYPE_DECL(unsigned short,ushort)
GEN_INT_TYPE_DECL(unsigned long long,ulonglong)
GEN_INT_TYPE_DECL(char,kchar)
GEN_INT_TYPE_DECL(int,kint)
GEN_INT_TYPE_DECL(size_t,ksize)
#define KID kint // used in cycles and in funcs, that works with id's


GEN_FLOAT_TYPE_DECL(float,kfloat)
GEN_FLOAT_TYPE_DECL(double,kdouble)
#define DEFCMATHTYPE double // default type, used by c math library


GEN_PTR_TYPE_DECL(void *,kptr)


typedef	enum
{
	kfalse, ktrue, kother,
	kprev = 0, knext = 1,
	kleft = 0, kright = 1,
	kbefore = 0, kafter = 1

} kbool; // bool emulation ;)

typedef enum
{
	ktbool,
	ktptr,
	ktchar,
	ktbyte,
	ktfloat, ktint, ktuint, ktsize,
	ktid,
	kthash,
	ktllist, ktdllist, kthashlist,
	ktobject

} ktype;


//==============================================================================

typedef void * (* kunfunc)( void * );
typedef void * (* kbinfunc)( void *, void * );
typedef void * (* kterfunc)( void *, void *, void * );

typedef kint (* kcmpfunc)( void *, void * );

typedef KHASH (* khashfunc)( void *, ksize );

#define CCMPF(F) (kcmpfunc)F

//==============================================================================


#endif /* KBTYPES_H_ */
