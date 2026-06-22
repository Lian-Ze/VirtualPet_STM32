#ifndef __PET_H
#define __PET_H

#include "stm32f10x.h"

typedef enum
{
    MOOD_NORMAL = 0,
    MOOD_HAPPY,
    MOOD_HUNGRY,
    MOOD_SICK,
    MOOD_DEAD
} PetMood;

typedef enum
{
    EVENT_NONE = 0,
    EVENT_FOOD,
    EVENT_GIFT,
    EVENT_MEDICINE,
    EVENT_SICK,
    EVENT_THIEF

}PetEvent;

typedef struct
{
    uint8_t Food;
    uint8_t Happy;
    uint8_t Health;

    uint8_t Level;
    uint8_t Exp;

    uint8_t Alive;

    PetMood Mood;

} Pet_t;

extern Pet_t Pet;
extern PetEvent CurrentEvent;

void Pet_RandomEvent(void);
void Pet_Init(void);
void Pet_Update(void);

uint8_t Pet_Feed(void);
uint8_t Pet_Play(void);
uint8_t Pet_Heal(void);

/* 一定要有这一行 */
uint8_t Pet_AddExp(uint8_t Exp);

#endif