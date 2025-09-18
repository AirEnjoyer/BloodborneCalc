#include "weapon.h"
#include <stdio.h>
#include <string.h>
#include <math.h>
float getSat(int inputStat){
    float sat;
    if (inputStat >= 5 && inputStat <= 10){
        sat = (inputStat * 0.005) + .025;
    }
    else if (inputStat >= 11 && inputStat <= 25) {
        sat = ((inputStat - 10) * 0.03) + 0.050;
    }
    else if (inputStat >= 26 && inputStat <= 50) {
        sat = ((inputStat - 25) * 0.014) + .5;
    }
    else if (inputStat >= 51 && inputStat <= 58){
        sat = ((inputStat - 50) * 0.003) + .85;
    }
    else if (inputStat == 58){
        sat = 0.878;
    }
    else if (inputStat >= 59 && inputStat <= 99){
        sat = ((inputStat - 58) * 0.003) + 0.878;
    }
    return sat;
}


void calcDamage(const Weapon *w, int weaponLevel, int userStr, int userSkill, int userBloodtinge, int userArc){


    int effectiveLevel = weaponLevel;

    float strSat = getSat(userStr);
    float skillSat = getSat(userSkill);
    float bloodtingeSat = getSat(userBloodtinge);
    float arcSat = getSat(userArc);



    float weaponStrScale = w->strScale + (w->strScaleIncrease * effectiveLevel);
    float weaponSkillScale = w->skillScale + (w->skillScaleIncrease * effectiveLevel);
    float weaponBloodtingeScale = w->bloodtingeScale + (w->bloodtingeScaleIncrease * effectiveLevel);
    float weaponArcScale = w->arcaneScale + (w->arcaneScaleIncrease * effectiveLevel);



    float basePhys = w->basePhys + (w->physInc * (effectiveLevel-1));
    float baseBlood = w->baseBlood + (w->bloodInc * (effectiveLevel-1));
    float baseArc = w->baseArc + (w->arcInc * (effectiveLevel-1));

    if (weaponLevel == 10) {
        if (basePhys > 0)
            basePhys += w->physFinal;
        if (baseBlood > 0){
            baseBlood += w->bloodFinal;
        if (baseArc > 0){
                baseArc += w->arcFinal;
            }
        }
    }

    float physDamage = (basePhys + (weaponStrScale * strSat + basePhys * weaponSkillScale * skillSat));

    float bloodDamage = (baseBlood + (weaponBloodtingeScale * bloodtingeSat));

    float arcDamage = (baseArc + (weaponArcScale * arcSat));
    

    if (strcmp(w->name, "Holy Moonlight Sword")){
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
        printf("Charged R2: %f\n", (physDamage * w->chargeR2 + arcDamage * holyGSwordChargedR2Arc));
        printf("Transform Attack: %f\n", (physDamage * w->regTransformAttack + arcDamage * holyGSwordTransformArc));
        printf("Transformed R1: %f\n", (physDamage * w->transformedR1 + arcDamage * transformedHolyGSwordR1Arc));
        printf("Transformed R2: %f\n", (physDamage * w->transformedTapR2 + arcDamage * transformedHolyGSwordR2Arc));
        printf("Transformed Charged R2: %f\n", (physDamage * w->transformedChargeR2 + arcDamage * transformedHolyGSwordChargedR2Arc));
        printf("L2: %f\n", (physDamage * w->l2 + arcDamage * holyGSwordL2));\
        printf("Transformed Transform Attack: %f\n", (physDamage * w->transformedTransformAttack + arcDamage * transformedHolyGSwordTransformArc));
    }

    else  if (strcmp(w->name, "Whirligig Saw")){
        if (arcDamage == 0) {
        printf("R1: %f\n", w->r1);
        printf("R2: %f\n", w->tapR2);
        printf("Charged R2: %f\n", w->chargeR2);
        printf("Transform Attack: %f\n", w->regTransformAttack);
        printf("Transformed R1: %f\n", w->transformedR1);
        printf("Transformed R2: %f\n", w->transformedTapR2);
        printf("Transformed Charged R2: %f\n", (w->transformedChargeR2 * 1.8) + pow((w->transformedChargeR2 * 0.3), 3));
        printf("L2: %f\n", w->l2);
        }
    }




    else {
    printf("\nResults for %s at level %d:\n", w->name, weaponLevel);
    if (physDamage > 0){
        printf(" Physical damage: %.2f\n", physDamage);
    }
    if (bloodDamage > 0){
        printf(" Blood damage: %.2f\n", bloodDamage);
    }
    if (arcDamage > 0){
        printf(" Arcane damage: %.2f\n", arcDamage);
    }
}
}
