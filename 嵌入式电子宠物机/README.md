# 🐱 基于 STM32 的电子宠物（Virtual Pet）

## 📖 项目简介

本项目基于 **STM32F103C8T6** 开发，使用 **128×64 OLED（I2C）** 显示屏实现一个简单的电子宠物（Virtual Pet）。

项目采用模块化设计，实现了宠物成长、情绪管理、等级系统、多界面显示、按键交互、蜂鸣器提示、眨眼动画、自动睡眠以及随机事件系统，并通过 **TIM2** 提供 **1ms SystemTick** 作为系统时基。

---

# ✨ 已完成功能

## ✅ 硬件驱动

* OLED 显示（128×64）
* 三个按键输入
* 蜂鸣器
* TIM2 定时器（1ms SystemTick）
* LED 驱动

---

## ✅ 宠物系统

支持以下属性：

* Food（饱食度）
* Happy（快乐值）
* Health（生命值）
* Level（等级）
* Exp（经验值）
* Alive（存活状态）

系统每秒自动更新一次宠物状态：

* Food 自动下降
* Happy 自动下降
* Food 或 Happy 过低时开始掉血
* Health 为 0 时宠物死亡
* 睡眠状态暂停属性下降

---

## 😊 情绪系统（Mood）

目前支持五种情绪：

| Mood   | 表情      |
| ------ | ------- |
| Normal | (=^.^=) |
| Happy  | (=^o^=) |
| Hungry | (=T.T=) |
| Sick   | (=-.-=) |
| Dead   | (=x.x=) |

宠物情绪会根据当前状态自动更新，并在状态发生变化时自动切换到 PET 页面。

---

## ⭐ 等级成长系统

可通过以下操作获得经验：

* 🍖 Feed（喂食）
* 🎮 Play（玩耍）
* 💊 Heal（治疗）

经验达到升级条件后：

* Level +1
* Food 恢复
* Happy 恢复
* Health 恢复
* 播放升级动画
* 蜂鸣器双响提示

---

## 😴 睡眠系统

为了模拟真实电子宠物，加入自动睡眠机制。

功能：

* 长时间无操作自动睡眠
* 显示 Zzz
* 任意按键立即唤醒
* 睡眠期间暂停属性下降

---

## 😉 眨眼动画

宠物会自动进行眨眼动画。

功能：

* 自动循环眨眼
* 正常状态播放
* 睡眠时停止眨眼

---

## 🎲 随机事件系统

每 **30 秒** 自动触发一次随机事件。

目前包含五种事件：

| 事件            | 效果         |
| ------------- | ---------- |
| 🍖 Lucky Food | Food +15   |
| 🎁 Gift       | Happy +15  |
| 💊 Medicine   | Health +10 |
| 🌧 Sick       | Health -10 |
| 🐭 Thief      | Food -10   |

事件发生时：

* 自动唤醒睡眠中的宠物
* OLED 弹出事件提示界面
* 2 秒后自动返回 Status 页面

---

# 🖥 UI 界面

目前共有 **6 个界面**。

## 🐱 PET

根据不同 Mood 自动显示 ASCII 萌猫。

### 😊 Normal

```text
   /\_/\
  (=^.^=)
   (___)
```

### 😄 Happy

```text
   /\_/\
  (=^o^=)
   (___)
```

### 😭 Hungry

```text
   /\_/\
  (=T.T=)
   (___)
```

### 🤒 Sick

```text
   /\_/\
  (=-.-=)
   (___)
```

### 😴 Sleep

```text
   /\_/\
  (=-.-=)
    Zzz
```

### ☠ Dead

```text
   /\_/\
  (=x.x=)
   (___)
```

自动显示规则：

* 开机显示 5 秒
* 按键操作后显示 2 秒
* 状态变化自动弹出
* 睡眠期间保持显示

---

## 📊 STATUS

显示：

* Food
* Happy
* HP
* Level
* Exp

---

## 🎉 LEVEL UP

升级时显示：

```text
LEVEL
 UP!
```

---

## 😺 LEVEL PET

升级完成后显示开心小猫。

随后自动返回 STATUS 页面。

---

## 🎲 EVENT

随机事件提示界面。

根据事件类型显示：

* Lucky!
* Gift!
* Medicine
* Rain
* Oops!

显示约 2 秒后自动关闭。

---

## ☠ GAME OVER

生命值为 0 时：

```text
GAME
OVER
```

宠物停止更新。

---

# 🔔 蜂鸣器

### 普通操作

* Feed
* Play
* Heal

播放提示音。

### 升级

双响提示。

### 报警

当：

* Food < 20
* Happy < 20

每秒报警一次。

---

# 📁 当前工程结构

```text
Project
│
├── Hardware
│   ├── OLED
│   ├── Key
│   ├── LED
│   ├── Buzzer
│   └── Timer
│
├── User
│   ├── main.c
│   ├── Pet.c
│   ├── Pet.h
│   ├── Bitmap.c（预留）
│   └── Bitmap.h（预留）
│
└── Objects
```

---

# 🚀 后续开发计划

* [ ] Flash 存档
* [ ] 点阵宠物（Bitmap）
* [ ] 多只宠物选择
* [ ] 小游戏
* [ ] UI 美化

---

# 📝 更新日志

## V1.2 Final

### 新增

* ✅ Mood 情绪系统
* ✅ EXP 经验系统
* ✅ 等级成长系统
* ✅ Level Up 动画
* ✅ Level Pet 展示界面
* ✅ ASCII 萌猫
* ✅ 自动升级奖励
* ✅ 自动经验累计
* ✅ 自动状态切换
* ✅ 宠物眨眼动画
* ✅ 自动睡眠系统
* ✅ 睡眠暂停属性下降
* ✅ 任意按键唤醒
* ✅ 随机事件系统
* ✅ Event 提示页面
* ✅ Status 页面显示 Exp

### 优化

* OLED 刷新逻辑
* UI 页面切换
* Pet 模块结构
* 升级动画流程
* 按键交互逻辑
* 状态机逻辑

---

# 🛠 开发环境

* STM32F103C8T6
* STM32 Standard Peripheral Library
* Keil MDK5
* OLED 128×64（I2C）
* ST-Link V2
* C Language
