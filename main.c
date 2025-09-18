#include "weapon.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>


void calcDamage(const Weapon *w, int weaponLevel, int userStr, int userSkill, int userBloodtinge, int userArc);

int main(){

    int amountOfWeapons = sizeof(weapons) / sizeof(weapons[0]);

    int userChoice = 0;

    int weaponLevel = 0;

    float strScale, strSat, skillScale, skillSat, bloodtingeScale, bloodtingeSat, arcScale, arcSat;

    float weaponStrScale, weaponSkillScale, weaponBloodtingeScale, weaponArcaneScale;

    int userStr, userSkill, userBloodtinge, userArc;



    printf("Choose a weapon by number:\n");

    for (int i = 0; i < amountOfWeapons; i++) {
        printf("%d: %s\n", i+1, weapons[i].name);
    };


    scanf("%d", &userChoice);

    userChoice--;


        printf("Enter the weapon level\n");
            scanf("%d", &weaponLevel);



        printf("Enter your strength\n");
            scanf("%d", &userStr);
        printf("Enter your skill\n");
            scanf("%d", &userSkill);
        printf("Enter your bloodtinge\n");
            scanf("%d", &userBloodtinge);
        printf("Enter your arcane\n");
            scanf("%d", &userArc);

        calcDamage(&weapons[userChoice], weaponLevel, userStr, userSkill, userBloodtinge, userArc);


    return 0;
}
