
#ifndef WEAPON_H
#define WEAPON_H

typedef struct {
  char name[35];

  // Scaling
  float strScale;
  float skillScale;
  float bloodtingeScale;
  float arcaneScale;

  // Scaling increase
  float strScaleIncrease;
  float skillScaleIncrease;
  float bloodtingeScaleIncrease;
  float arcaneScaleIncrease;

  // Attack multipliers
  float r1;
  float tapR2;
  float chargeR2;
  float regTransformAttack;
  float transformedR1;
  float transformedTapR2;
  float transformedChargeR2;
  float l2;
  float transformedTransformAttack;

  // Base damage stats & amount added per weapon level
  int basePhys;
  int baseArc;
  int baseBlood;
  int physInc;
  int arcInc;
  int bloodInc;

  // Amounted added at level 10 weapon
  int physFinal;
  int arcFinal;
  int bloodFinal;
} Weapon;

extern Weapon weapons[28];

extern int bloodLevel;

#endif
