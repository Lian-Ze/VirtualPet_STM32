# 🐱 VirtualPet_STM32

基于 **STM32F103C8T6** + **0.96寸OLED** 的电子宠物（Virtual Pet）项目。

---

# 📖 项目介绍

本项目采用 **STM32 标准外设库（StdPeriph Library）** 开发，模拟经典电子宠物（Tamagotchi）的玩法。

目前已完成硬件驱动、宠物状态管理、按键交互、蜂鸣器提示以及基础界面切换，后续将继续完善宠物成长、情绪系统、动画和小游戏等功能。

---

# ✨ 当前功能

## ✅ 硬件驱动

- OLED 显示
- LED 控制
- 三个独立按键
- 无源蜂鸣器
- TIM2 1ms 系统时基

## ✅ 宠物系统

- Food（饱食度）
- Happy（心情值）
- Health（生命值）
- Level（等级）

## ✅ 游戏逻辑

- 每秒自动更新宠物状态
- Food 自动下降
- Happy 自动下降
- 喂食（Feed）
- 玩耍（Play）
- 治疗（Heal）
- Game Over 判断

## ✅ UI

- 开机宠物界面（5秒）
- 状态界面
- Level Up 界面（预留）
- Game Over 界面

---

# 🔧 开发环境

| 项目 | 说明 |
|------|------|
| MCU | STM32F103C8T6 |
| IDE | Keil MDK5 |
| 开发库 | STM32 标准外设库 |
| OLED | 0.96寸 I2C OLED |
| 下载器 | ST-Link V2 |

---

# 📂 工程结构

```text
VirtualPet_STM32
│
├── Hardware
│   ├── OLED
│   ├── LED
│   ├── Key
│   ├── Buzzer
│   └── Timer
│
├── System
│   └── Delay
│
├── Pet
│   ├── Pet.c
│   └── Pet.h
│
├── User
│   └── main.c
│
└── README.md
```

---

# 🎮 当前界面

## 开机界面

```text
PET

(^_^)
```

开机后显示 5 秒，然后自动进入状态界面。

---

## 状态界面

```text
Food :100
Happy:100
HP   :100
Lv   :1
```

---

# 🎯 按键功能

| 按键 | 功能 |
|------|------|
| KEY1 | 喂食（Feed） |
| KEY2 | 玩耍（Play） |
| KEY3 | 治疗（Heal） |

---

# 🚀 开发进度

## v0.1

- [x] STM32 工程搭建
- [x] OLED 驱动
- [x] LED 驱动

---

## v0.2

- [x] Key 驱动
- [x] Buzzer 驱动
- [x] Timer 驱动

---

## v0.3

- [x] 新增 Pet 模块
- [x] Food、Happy、Health 数据结构
- [x] 宠物状态自动更新
- [x] Feed / Play / Heal
- [x] Game Over 判断

---

## v0.4（当前版本）

- [x] 开机宠物界面
- [x] 状态界面
- [x] 基础界面切换
- [x] OLED 刷新优化

---

# 📅 后续计划

## 即将完成

- [ ] 情绪（Mood）系统
- [ ] 原创 32×32 宠物图片
- [ ] 饥饿动画
- [ ] 开心动画
- [ ] 生病动画

## 后续功能

- [ ] EXP（经验值）
- [ ] 等级成长
- [ ] Level Up 动画
- [ ] 随机事件
- [ ] 小游戏
- [ ] 蜂鸣器音乐

---

# 📝 开发流程

```
完成一个功能
        ↓
硬件测试
        ↓
修复 Bug
        ↓
Git Commit
        ↓
更新 README
        ↓
继续开发
```

---

# 📌 项目目标

完成一个具有完整功能的 STM32 电子宠物，包括：

- 🐱 原创像素宠物
- 😊 情绪系统
- 📈 等级成长
- 🎮 小游戏
- 🎵 蜂鸣器音效
- 🎨 更丰富的 OLED UI

---

> **持续开发中......**
