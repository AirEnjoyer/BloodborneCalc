#include "weapon.h"
#include <math.h>
#include <stdio.h>
#include <string.h>

int bloodLevel = 0;

float getSat(int inputStat) {
  float sat;
  if (inputStat >= 5 && inputStat <= 10) {
    sat = (inputStat * 0.005) + .025;
  } else if (inputStat >= 11 && inputStat <= 25) {
    sat = ((inputStat - 10) * 0.03) + 0.050;
  } else if (inputStat >= 26 && inputStat <= 50) {
    sat = ((inputStat - 25) * 0.014) + .5;
  } else if (inputStat >= 51 && inputStat <= 58) {
    sat = ((inputStat - 50) * 0.003) + .85;
  } else if (inputStat == 58) {
    sat = 0.878;
  } else if (inputStat >= 59 && inputStat <= 99) {
    sat = ((inputStat - 58) * 0.003) + 0.878;
  }
  return sat;
}

void getVisceralDamage(int skill, float *initThrustDamage,
                       float *parryViscDamage, float *breakViscDamage) {
  float visceralSat = 0;

  if (skill >= 5 && skill <= 10) {
    visceralSat = (skill * 0.01) + .05;
  } else if (skill >= 11 && skill <= 50) {
    visceralSat = ((skill - 10) * 0.0175) + 0.1;
  } else if (skill >= 51 && skill <= 53) {
    visceralSat = ((skill - 50) * 0.004) + .8;
  } else if (skill == 54) {
    visceralSat = 0.8163;
  } else if (skill >= 55 && skill <= 62) {
    visceralSat = ((skill - 54) * 0.0041) + 0.8163;
  } else if (skill == 63) {
    visceralSat = 0.853;
  } else if (skill >= 64 && skill <= 69) {
    visceralSat = ((skill - 63) * 0.0041) + 0.853;
  } else if (skill == 70) {
    visceralSat = .8816;
  } else if (skill >= 71 && skill <= 74) {
    visceralSat = ((skill - 70) * 0.0041) + 0.8816;
  } else if (skill == 75) {
    visceralSat = 0.902;
  } else if (skill >= 76 && skill <= 79) {
    visceralSat = ((skill - 75) * 0.0041) + 0.9061;
  } else if (skill == 80) {
    visceralSat = .9224;
  } else if (skill >= 81 && skill <= 84) {
    visceralSat = ((skill - 80) * 0.0041) + 0.9924;
  } else if (skill == 85) {
    visceralSat = 0.9428;
  } else if (skill >= 86 && skill <= 89) {
    visceralSat = ((skill - 85) * 0.0041) + 0.9428;
  } else if (skill == 90) {
    visceralSat = 0.9633;
  } else if (skill == 91) {
    visceralSat = 0.9673;
  } else if (skill >= 92 && skill <= 99) {
    visceralSat = ((skill - 91) * 0.0041) + 0.9673;
  }

  float initThrust, parryVisc, breakVisc;

  if (bloodLevel >= 4 && bloodLevel <= 14) {
    initThrust = 0.5f;
    parryVisc = 2.5f;
    breakVisc = 3;
  } else if (bloodLevel >= 15 && bloodLevel <= 29) {
    initThrust = 0.55;
    parryVisc = 3.25;
    breakVisc = 3.75;
  } else if (bloodLevel >= 30 && bloodLevel <= 44) {
    initThrust = 0.6;
    parryVisc = 3.9;
    breakVisc = 4.4;
  } else if (bloodLevel >= 45 && bloodLevel <= 59) {
    initThrust = 0.65;
    parryVisc = 5.7;
    breakVisc = 6.2;
  } else if (bloodLevel >= 60 && bloodLevel <= 79) {
    initThrust = 0.7;
    parryVisc = 6.4;
    breakVisc = 6.9;
  } else if (bloodLevel >= 80 && bloodLevel <= 99) {
    initThrust = 0.75;
    parryVisc = 7.2;
    breakVisc = 7.7;
  } else if (bloodLevel >= 100 && bloodLevel <= 119) {
    initThrust = 0.8;
    parryVisc = 7.4;
    breakVisc = 7.9;
  } else if (bloodLevel >= 120 && bloodLevel <= 139) {
    initThrust = 0.85;
    parryVisc = 7.6;
    breakVisc = 8.1;
  } else if (bloodLevel >= 140 && bloodLevel <= 159) {
    initThrust = 0.9;
    parryVisc = 7.7;
    breakVisc = 8.2;
  } else if (bloodLevel >= 160 && bloodLevel <= 199) {
    initThrust = 0.95;
    parryVisc = 7.8;
    breakVisc = 8.3;
  } else if (bloodLevel > 199) {
    initThrust = 1;
    parryVisc = 7.9;
    breakVisc = 8.4;
  }
  *initThrustDamage = (130 + (130 * 1.3 * visceralSat)) * initThrust;
  *parryViscDamage = (130 + (130 * 1.3 * visceralSat)) * parryVisc;
  *breakViscDamage = (130 + (130 * 1.3 * visceralSat)) * breakVisc;
}

void calcDamage(const Weapon *w, int weaponLevel, int userStr, int userSkill,
                int userBloodtinge, int userArc) {

  int effectiveLevel = weaponLevel;

  float strSat = getSat(userStr);
  float skillSat = getSat(userSkill);
  float bloodtingeSat = getSat(userBloodtinge);
  float arcSat = getSat(userArc);

  float weaponStrScale = w->strScale + (w->strScaleIncrease * effectiveLevel);
  float weaponSkillScale =
      w->skillScale + (w->skillScaleIncrease * effectiveLevel);
  float weaponBloodtingeScale =
      w->bloodtingeScale + (w->bloodtingeScaleIncrease * effectiveLevel);
  float weaponArcScale =
      w->arcaneScale + (w->arcaneScaleIncrease * effectiveLevel);

  float basePhys = w->basePhys + (w->physInc * (effectiveLevel - 1));
  float baseBlood = w->baseBlood + (w->bloodInc * (effectiveLevel - 1));
  float baseArc = w->baseArc + (w->arcInc * (effectiveLevel - 1));

  if (weaponLevel == 10) {
    if (basePhys > 0)
      basePhys += w->physFinal;
    if (baseBlood > 0) {
      baseBlood += w->bloodFinal;
      if (baseArc > 0) {
        baseArc += w->arcFinal;
      }
    }
  }

  float physDamage = (basePhys + (weaponStrScale * strSat +
                                  basePhys * weaponSkillScale * skillSat));

  float bloodDamage = (baseBlood + (weaponBloodtingeScale * bloodtingeSat));

  float arcDamage = (baseArc + (weaponArcScale * arcSat));

  if (strcmp(w->name, "Holy Moonlight Sword")) {
    float holyGSwordR1Arc = 0.50;
    float holyGSwordR2Arc = 0.65f;
    float holyGSwordChargedR2Arc = 0.9f;
    float holyGSwordTransformArc = 1.0f;
    float transformedHolyGSwordR1Arc = 0.7f;
    float transformedHolyGSwordR2Arc = 2.0f;
    float transformedHolyGSwordChargedR2Arc = 2.8f;
    float holyGSwordL2 = 1.5f;
    float transformedHolyGSwordTransformArc = 1.3f;

    printf("R1: %f\n", (physDamage * w->r1 + arcDamage * holyGSwordR1Arc));
    printf("R2: %f\n", (physDamage * w->tapR2 + arcDamage * holyGSwordR2Arc));
    printf("Charged R2: %f\n",
           (physDamage * w->chargeR2 + arcDamage * holyGSwordChargedR2Arc));
    printf("Transform Attack: %f\n", (physDamage * w->regTransformAttack +
                                      arcDamage * holyGSwordTransformArc));
    printf("Transformed R1: %f\n", (physDamage * w->transformedR1 +
                                    arcDamage * transformedHolyGSwordR1Arc));
    printf("Transformed R2: %f\n", (physDamage * w->transformedTapR2 +
                                    arcDamage * transformedHolyGSwordR2Arc));
    printf("Transformed Charged R2: %f\n",
           (physDamage * w->transformedChargeR2 +
            arcDamage * transformedHolyGSwordChargedR2Arc));
    printf("L2: %f\n", (physDamage * w->l2 + arcDamage * holyGSwordL2));
    printf("Transformed Transform Attack: %f\n",
           (physDamage * w->transformedTransformAttack +
            arcDamage * transformedHolyGSwordTransformArc));
  }

  else if (strcmp(w->name, "Whirligig Saw")) {
    if (arcDamage == 0) {
      printf("R1: %f\n", w->r1);
      printf("R2: %f\n", w->tapR2);
      printf("Charged R2: %f\n", w->chargeR2);
      printf("Transform Attack: %f\n", w->regTransformAttack);
      printf("Transformed R1: %f\n", w->transformedR1);
      printf("Transformed R2: %f\n", w->transformedTapR2);
      printf("Transformed Charged R2: %f\n",
             (w->transformedChargeR2 * 1.8) +
                 pow((w->transformedChargeR2 * 0.3), 3));
      printf("L2: %f\n", w->l2);
    }
  }

  else {
    printf("\nResults for %s at level %d:\n", w->name, weaponLevel);
    if (physDamage > 0) {
      printf(" Physical damage: %.2f\n", physDamage);
    }
    if (bloodDamage > 0) {
      printf(" Blood damage: %.2f\n", bloodDamage);
    }
    if (arcDamage > 0) {
      printf(" Arcane damage: %.2f\n", arcDamage);
    }
  }
  float initThrustDamage, parryViscDamage, breakViscDamage;
  getVisceralDamage(userSkill, &initThrustDamage, &parryViscDamage,
                    &breakViscDamage);
  printf("Viscerals:\n");
  printf("Initial thrust damage: %f\n", initThrustDamage);
  printf("Visceral damage agianst an enemy that was parried/backstriked: %f\n",
         parryViscDamage);
  printf("Visceral damage against a limb broken enemy: %f\n", breakViscDamage);
}
