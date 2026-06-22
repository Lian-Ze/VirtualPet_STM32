#include "stm32f10x.h"
#include "OLED.h"
#include "LED.h"
#include "Key.h"
#include "Buzzer.h"
#include "Timer.h"
#include "Pet.h"
#include "Bitmap.h"

typedef enum
{
    SCREEN_PET = 0,
    SCREEN_STATUS,
    SCREEN_LEVELUP,
    SCREEN_LEVELPET,   
	SCREEN_EVENT,
    SCREEN_GAMEOVER
}ScreenState;

/* 当前界面 */
ScreenState CurrentScreen = SCREEN_PET;
ScreenState LastScreen = SCREEN_GAMEOVER;

/* 定时器 */
uint32_t ScreenTimer = 0;
uint32_t LastTime = 0;
uint32_t WarningTimer = 0;
uint32_t LevelTimer = 0;
uint32_t EventTimer = 0;      // 事件触发计时
uint32_t EventShowTimer = 0;  // 事件显示计时

/* 是否第一次开机 */
uint8_t FirstBoot = 1;

/* 上一次情绪 */
PetMood LastMood;

uint8_t Blink = 0;
uint32_t BlinkTimer = 0;

uint8_t Sleep = 0;
uint32_t SleepTimer = 0;

int main(void)
{
    /* 初始化 */
    OLED_Init();
    LED_Init();
    Key_Init();
    Buzzer_Init();
    Timer_Init();

    Pet_Init();
	
	SleepTimer = SystemTick;
	EventTimer = SystemTick;
    LastMood = Pet.Mood;

    CurrentScreen = SCREEN_PET;
    ScreenTimer = SystemTick;

    while(1)
    {
        /******** 每秒更新宠物 ********/
        if(SystemTick - LastTime >= 1000)
        {
            LastTime = SystemTick;

            Pet_Update();
			
            /* 情绪变化自动显示PET */
            if(Pet.Mood != LastMood)
            {
                LastMood = Pet.Mood;

                if(Pet.Mood != MOOD_NORMAL)
				{
					CurrentScreen = SCREEN_PET;
					ScreenTimer = SystemTick;
				}
            }
        }
		/******** 宠物眨眼 ********/

		if(Pet.Alive)
		{
			if(Blink == 0)
			{
				if(SystemTick - BlinkTimer >= 500)
				{
					Blink = 1;
					BlinkTimer = SystemTick;
				}
			}
			else
			{
				if(SystemTick - BlinkTimer >= 80)
				{
					Blink = 0;
					BlinkTimer = SystemTick;
				}
			}
		}
		/******** 自动睡觉 ********/

		if(Pet.Alive)
		{
			if(Sleep == 0 && Pet.Mood == MOOD_NORMAL)
			{
				if(SystemTick - SleepTimer >= 15000)
				{
					Sleep = 1;
					CurrentScreen = SCREEN_PET;
					ScreenTimer = SystemTick;
				}
			}
		}
        /******** 按键 ********/

        if(Key_Feed())
		{
			
			Sleep = 0;
			SleepTimer = SystemTick;
			if(Pet_Feed())
			{
				CurrentScreen = SCREEN_LEVELUP;
				LevelTimer = SystemTick;

				Buzzer_Beep(100);
				Buzzer_Beep(100);
			}
			else
			{
				CurrentScreen = SCREEN_PET;
				ScreenTimer = SystemTick;

				Buzzer_Beep(50);
			}
		}

        if(Key_Play())
		{
			Sleep = 0;
			SleepTimer = SystemTick;
			if(Pet_Play())
			{
				CurrentScreen = SCREEN_LEVELUP;
				LevelTimer = SystemTick;

				Buzzer_Beep(100);
				Buzzer_Beep(100);
			}
			else
			{
				CurrentScreen = SCREEN_PET;
				ScreenTimer = SystemTick;

				Buzzer_Beep(50);
			}
		}
        if(Key_Medical())
		{
			Sleep = 0;
			SleepTimer = SystemTick;
			if(Pet_Heal())
			{
				CurrentScreen = SCREEN_LEVELUP;
				LevelTimer = SystemTick;

				Buzzer_Beep(100);
				Buzzer_Beep(100);
			}
			else
			{
				CurrentScreen = SCREEN_PET;
				ScreenTimer = SystemTick;

				Buzzer_Beep(50);
			}
		}
		
		if(Pet.Alive)
		{
			if(SystemTick - EventTimer >= 30000)
			{
				EventTimer = SystemTick;

				Pet_RandomEvent();

				/* 睡觉时遇到事件会醒来 */
				Sleep = 0;
				SleepTimer = SystemTick;

				CurrentScreen = SCREEN_EVENT;
				ScreenTimer = SystemTick;
				EventShowTimer = SystemTick;
			}
		}
        /******** Food / Happy报警 ********/

        if(Pet.Alive)
        {
            if(Pet.Food < 20 || Pet.Happy < 20)
            {
                if(SystemTick - WarningTimer >= 1000)
                {
                    WarningTimer = SystemTick;

                    Buzzer_Beep(80);
                }
            }
        }

        /******** 游戏结束 ********/

        if(Pet.Alive == 0)
        {
            CurrentScreen = SCREEN_GAMEOVER;
        }

        /******** PET界面自动返回 ********/

       if(CurrentScreen == SCREEN_PET && Sleep == 0)
        {
            if(FirstBoot)
            {
                if(SystemTick - ScreenTimer >= 5000)
                {
                    CurrentScreen = SCREEN_STATUS;
                    FirstBoot = 0;
                }
            }
            else
            {
                if(SystemTick - ScreenTimer >= 2000)
                {
                    CurrentScreen = SCREEN_STATUS;
                }
            }
        }
		/******** LEVEL UP动画 ********/

		if(CurrentScreen == SCREEN_LEVELUP)
		{
			if(SystemTick - LevelTimer >= 2000)
			{
				CurrentScreen = SCREEN_LEVELPET;
				LevelTimer = SystemTick;
			}
		}

		if(CurrentScreen == SCREEN_LEVELPET)
		{
			if(SystemTick - LevelTimer >= 2000)
			{
				CurrentScreen = SCREEN_STATUS;
			}
		}
		/******** EVENT界面 ********/

		if(CurrentScreen == SCREEN_EVENT)
		{
			if(SystemTick - EventShowTimer >= 2000)
			{
				CurrentScreen = SCREEN_STATUS;
			}
		}
        /******** 界面切换时清屏 ********/

        if(CurrentScreen != LastScreen)
        {
            OLED_Clear();
            LastScreen = CurrentScreen;
        }

        /******** OLED显示 ********/

        switch(CurrentScreen)
        {
            case SCREEN_PET:
                OLED_ShowString(1,4,"Kitty");

                switch(Pet.Mood)
                {
                    case MOOD_NORMAL:
						OLED_ShowString(2,5,"/\\_/\\");
						if(Sleep)
						{
							OLED_ShowString(3,4,"(=-.-=)");
							OLED_ShowString(4,6,"z z");
						}
						else
						{
							if(Blink)
								OLED_ShowString(3,4,"(=-.-=)");
							else
								OLED_ShowString(3,4,"(=^.^=)");

							OLED_ShowString(4,5,"(___)");
						}
						break;
						
                    case MOOD_HAPPY:
                        OLED_ShowString(2,5,"/\\_/\\\\");
						OLED_ShowString(3,4,"(=^o^=)");
						OLED_ShowString(4,5,"(___)");
                        break;

                    case MOOD_HUNGRY:
                        OLED_ShowString(2,5,"/\\_/\\\\");
						OLED_ShowString(3,4,"(=T.T=)");
						OLED_ShowString(4,5,"(___)");
                        break;

                    case MOOD_SICK:
                        OLED_ShowString(2,5,"/\\_/\\\\");
						OLED_ShowString(3,4,"(=-.-=)");
						OLED_ShowString(4,5,"(___)");
                        break;

                    case MOOD_DEAD:
                        OLED_ShowString(2,5,"/\\_/\\\\");
						OLED_ShowString(3,4,"(=x.x=)");
						OLED_ShowString(4,5,"(___)");
                        break;
                }

                break;

            case SCREEN_STATUS:

                OLED_ShowString(1,1,"Food:");
                OLED_ShowNum(1,7,Pet.Food,3);

                OLED_ShowString(2,1,"Happy:");
                OLED_ShowNum(2,8,Pet.Happy,3);

                OLED_ShowString(3,1,"HP:");
                OLED_ShowNum(3,5,Pet.Health,3);

                OLED_ShowString(4,1,"Lv");
				OLED_ShowNum(4,3,Pet.Level,2);

				OLED_ShowString(4,7,"E");
				OLED_ShowNum(4,8,Pet.Exp,2);
                break;

            case SCREEN_LEVELUP:

				OLED_ShowString(2,3,"LEVEL");
				OLED_ShowString(3,4,"UP!");

				OLED_ShowString(4,4,"Lv");
				OLED_ShowNum(4,7,Pet.Level,2);

				break;
			case SCREEN_LEVELPET:

				OLED_ShowString(1,4,"PET");
				OLED_ShowString(3,4,"(^o^)");
				break;
			case SCREEN_EVENT:

				switch(CurrentEvent)
				{
					case EVENT_FOOD:

						OLED_ShowString(2,3,"Lucky!");
						OLED_ShowString(3,2,"Food +15");
						break;

					case EVENT_GIFT:

						OLED_ShowString(2,3,"Gift!");
						OLED_ShowString(3,3,"Happy +15");
						break;

					case EVENT_MEDICINE:

						OLED_ShowString(2,2,"Medicine");
						OLED_ShowString(3,3,"HP +10");
						break;

					case EVENT_SICK:

						OLED_ShowString(2,3,"Rain");
						OLED_ShowString(3,3,"HP -10");
						break;

					case EVENT_THIEF:

						OLED_ShowString(2,3,"Oops!");
						OLED_ShowString(3,3,"Food -10");
						break;
				}

				break;
			
            case SCREEN_GAMEOVER:

                OLED_ShowString(2,3,"GAME");
                OLED_ShowString(3,3,"OVER");
				
                break;
        }
    }
}