#ifndef _PARTICLES_H_
#define _PARTICLES_H_

extern int pt_explosion,
	pt_emp,
	pt_pointfile,
	pt_entityparticles,
	pt_darkfield,
	pt_blob,
	pt_blood,
	pt_lightningblood,
	pt_gunshot,
	pt_wizspike,
	pt_knightspike,
	pt_spike,
	pt_superspike,
	pt_lavasplash,
	pt_teleportsplash,
	pt_blasterparticles,
	pt_torch,
	pt_flame,
	pt_bullet,
	pt_superbullet,
	pe_default;

extern int rt_rocket_trail,
	rt_smoke,
	rt_blood,
	rt_tracer,
	rt_slight_blood,
	rt_tracer2,
	rt_voor_trail,
	rt_fireball,
	rt_ice,
	rt_spit,
	rt_spell,
	rt_vorpal,
	rt_setstaff,
	rt_magicmissile,
	rt_boneshard,
	rt_scarab,
	rt_acidball,
	rt_bloodshot,
	rt_blastertrail,
	rt_railtrail,
	rt_bubbletrail;

// !!! if this is changed, it must be changed in d_ifacea.h too !!!
typedef struct particle_s
{
// driver-usable fields
	vec3_t		org;
	float		color;
	vec3_t		rgb;
	float		alpha;
	float		scale;

	vec3_t		vel;
	float		angle;
	float		rotationspeed;
	float		nextemit;

// drivers never touch the following fields

	struct particle_s	*next;
	float		die;
} particle_t;

#define BS_LASTSEG 0x1 // no draw to next, no delete
#define BS_DEAD    0x2 // segment is dead
#define BS_NODRAW  0x4 // only used for lerp switching

typedef struct beamseg_s
{
	particle_t *p; 
	struct beamseg_s *next;  // next in beamseg list
	int    flags;            // flags for beamseg
	vec3_t dir;

	float texture_s;
} beamseg_t;

#define PARTICLE_Z_CLIP	8.0

#define frandom() (rand()*(1.0f/RAND_MAX))
#define crandom() (rand()*(2.0f/RAND_MAX)-1.0f)
#define hrandom() (rand()*(1.0f/RAND_MAX)-0.5f)

//main functions
void P_DrawParticles (void);
void P_InitParticles (void);
void P_ClearParticles (void);
void P_NewServer(void);

//allocate a new effect
int P_ParticleTypeForName(char *name);
int P_AllocateParticleType(char *name);

void P_SkyTri(float *v1, float *v2, float *v3, struct msurface_s *surf);

//wierd effects
void P_RunParticleEffect (vec3_t org, vec3_t dir, int color, int count);	//aka: the particle builtin.
void P_RunParticleEffect2 (vec3_t org, vec3_t dmin, vec3_t dmax, int color, int effect, int count);	//these three are needed for hexen2.
void P_RunParticleEffect3 (vec3_t org, vec3_t box, int color, int effect, int count);
void P_RunParticleEffect4 (vec3_t org, float radius, int color, int effect, int count);

void P_DarkFieldParticles (float *org, qbyte colour);
void P_EntityParticles (float *org, qbyte colour, float *radius);	//nq's EF_BRIGHTFIELD
void P_TorchEffect (vec3_t pos, int type);	//particles centered around a model, called every frame for those models.

//functions that spawn trails (basically just pass throughs)
void P_BlasterParticles (vec3_t org, vec3_t dir);

//functions that spawn point effects (basically just pass throughs)
void P_BlobExplosion (vec3_t org);	//tarbaby explosion or TF emp.
void P_ParticleExplosion (vec3_t org);	//rocket explosion (sprite is allocated seperatly :( )
void P_LavaSplash (vec3_t org);	//cthon dying, or a gas grenade.
void P_TeleportSplash (vec3_t org);	//teleporter effect.



typedef struct {
	float lastdist;
	struct beamseg_s *lastbeam; // last beam point
} trailstate_t;
//the core spawn function for trails. (trailstate can be null)
int P_ParticleTrail (vec3_t start, vec3_t end, int type, trailstate_t *trailstate);

void P_DefaultTrail (struct model_s *model);	//fills in the default particle properties for a loaded model. Should already have the model flags set.

//the core spawn function for point effects
int P_RunParticleEffectType(vec3_t org, vec3_t dir, float count, int type);	//1 if failed.
int P_RunParticleEffectTypeString (vec3_t org, vec3_t dir, float count, char *name); //1 if failed.

void P_EmitSkyEffectTris(struct model_s *mod, struct msurface_s 	*fa);

#endif
