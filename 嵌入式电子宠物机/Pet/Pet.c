#include "Pet.h"
#include "Timer.h"
/* 全局宠物对象 */
Pet_t Pet;
PetEvent CurrentEvent = EVENT_NONE;
/* 睡眠状态（来自main.c） */
extern uint8_t Sleep;

/* 内部函数：更新宠物情绪 */
static void Pet_UpdateMood(void)
{
    if(Pet.Alive == 0)
    {
        Pet.Mood = MOOD_DEAD;
    }
    else if(Pet.Health < 30)
    {
        Pet.Mood = MOOD_SICK;
    }
    else if(Pet.Food < 20)
    {
        Pet.Mood = MOOD_HUNGRY;
    }
    else if(Pet.Happy > 90)
    {
        Pet.Mood = MOOD_HAPPY;
    }
    else
    {
        Pet.Mood = MOOD_NORMAL;
    }
}

/* 初始化宠物 */
void Pet_Init(void)
{
    Pet.Food = 100;
    Pet.Happy = 100;
    Pet.Health = 100;

    Pet.Level = 1;
    Pet.Exp = 0;

    Pet.Alive = 1;

    Pet.Mood = MOOD_NORMAL;
}

/* 每秒更新宠物状态 */
void Pet_Update(void)
{
    if(Pet.Alive == 0)
    {
        Pet_UpdateMood();
        return;
    }
	 /* 睡觉时暂停状态下降 */
    if(Sleep)
    {
        Pet_UpdateMood();
        return;
    }
    /* Food、Happy 自动下降 */
    if(Pet.Food > 0)
    {
        Pet.Food--;
    }

    if(Pet.Happy > 0)
    {
        Pet.Happy--;
    }

    /* 饥饿或快乐值过低开始掉血 */
    if(Pet.Food < 20 || Pet.Happy < 20)
    {
        if(Pet.Health > 0)
        {
            Pet.Health--;
        }
    }

    /* 死亡 */
    if(Pet.Health == 0)
    {
        Pet.Alive = 0;
    }

    /* 更新情绪 */
    Pet_UpdateMood();
}

/* 增加经验
 * 返回值：
 * 0 -> 未升级
 * 1 -> 升级成功
 */
uint8_t Pet_AddExp(uint8_t Exp)
{
    if(Pet.Alive == 0)
    {
        return 0;
    }

    Pet.Exp += Exp;

    if(Pet.Exp >= 30)
    {
        Pet.Exp = 0;

        if(Pet.Level < 99)
        {
            Pet.Level++;
        }

        /* 升级奖励 */

        if(Pet.Food <= 90)
            Pet.Food += 10;
        else
            Pet.Food = 100;

        if(Pet.Happy <= 90)
            Pet.Happy += 10;
        else
            Pet.Happy = 100;

        if(Pet.Health <= 80)
            Pet.Health += 20;
        else
            Pet.Health = 100;

        Pet_UpdateMood();

        return 1;
    }

    Pet_UpdateMood();

    return 0;
}

/* 喂食 */
/* 喂食 */
uint8_t Pet_Feed(void)
{
    if(Pet.Alive == 0)
    {
        return 0;
    }

    /* 已经满了，不增加经验 */
    if(Pet.Food >= 100)
    {
        return 0;
    }

    /* 增加Food */
    if(Pet.Food <= 80)
    {
        Pet.Food += 20;
    }
    else
    {
        Pet.Food = 100;
    }

    Pet_UpdateMood();

    /* 获得经验，返回是否升级 */
    return Pet_AddExp(3);
}

/* 玩耍 */
uint8_t Pet_Play(void)
{
    if(Pet.Alive == 0)
    {
        return 0;
    }

    /* 快乐值已经满了 */
    if(Pet.Happy >= 100)
    {
        return 0;
    }

    if(Pet.Happy <= 85)
    {
        Pet.Happy += 15;
    }
    else
    {
        Pet.Happy = 100;
    }

    Pet_UpdateMood();

    return Pet_AddExp(5);
}

/* 治疗 */
uint8_t Pet_Heal(void)
{
    if(Pet.Alive == 0)
    {
        return 0;
    }

    /* 只有真正治疗时才获得经验 */
    if(Pet.Health < 100)
    {
        if(Pet.Health <= 90)
        {
            Pet.Health += 10;
        }
        else
        {
            Pet.Health = 100;
        }

        Pet_UpdateMood();

        return Pet_AddExp(8);
    }

    return 0;
}

void Pet_RandomEvent(void)
{
    uint8_t r;

    if(Pet.Alive == 0)
        return;

    r = (SystemTick + Pet.Food + Pet.Happy + Pet.Level) % 5;

    switch(r)
    {
        case 0:
            CurrentEvent = EVENT_FOOD;
            Pet.Food += 15;
            if(Pet.Food > 100)
                Pet.Food = 100;
            break;

        case 1:
            CurrentEvent = EVENT_GIFT;
            Pet.Happy += 15;
            if(Pet.Happy > 100)
                Pet.Happy = 100;
            break;

        case 2:
            CurrentEvent = EVENT_MEDICINE;
            Pet.Health += 10;
            if(Pet.Health > 100)
                Pet.Health = 100;
            break;

		case 3:

			CurrentEvent = EVENT_SICK;
			if(Pet.Health >= 10)
				Pet.Health -= 10;
			else
				Pet.Health = 0;

			if(Pet.Health == 0)
				Pet.Alive = 0;
			break;

        case 4:
            CurrentEvent = EVENT_THIEF;

            if(Pet.Food >= 10)
                Pet.Food -= 10;
            else
                Pet.Food = 0;

            break;
    }

    Pet_UpdateMood();
}
