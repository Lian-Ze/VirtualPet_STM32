# 基于 STM32 的电子宠物机

> 一个基于 STM32F103C8T6（Blue Pill）的电子宠物机项目。

## 📖 项目简介

本项目基于 **STM32F103C8T6** 单片机开发，使用 **OLED 显示屏、按键、LED、蜂鸣器** 等外设，实现一个具有互动功能的虚拟电子宠物。

项目将按照实际开发过程持续更新，记录从硬件搭建到软件开发的完整过程。

---

## ✨ 计划实现的功能

* 🐱 宠物状态显示
* 🍖 喂食功能
* 🎮 玩耍功能
* 💊 医疗功能
* ❤️ 饥饿值、快乐值管理
* 🔔 蜂鸣器提醒
* 💡 LED 状态指示
* ⏰ 定时器自动更新状态
* 🎲 随机事件系统
* 🎮 简单互动小游戏

---

## 🛠️ 硬件平台

### 主控

* STM32F103C8T6（Blue Pill）

### 外设

* SSD1306 OLED（I2C）
* 三个按键
* 一个 LED
* 有源蜂鸣器
* ST-Link 下载器

---

## 🔌 硬件接线

| 模块       | STM32 引脚 |
| -------- | -------- |
| OLED SCL | PB6      |
| OLED SDA | PB7      |
| 按键1（喂食）  | PB0      |
| 按键2（玩耍）  | PA6      |
| 按键3（医疗）  | PA4      |
| 蜂鸣器      | PA0      |
| LED      | PA1      |

---

## 📷 项目实物

> 后续会补充接线图片和演示图片。

```
Images/
└── wiring.jpg
```

---

# 📈 当前开发进度

- [x] 创建 GitHub 仓库
- [x] 编写 README
- [x] 完成硬件接线
- [x] 建立 STM32 标准库工程
- [x] LED 驱动
- [x] 按键驱动
- [x] OLED 驱动
- [x] 蜂鸣器驱动
- [x] TIM2 定时器（1ms SystemTick）
- [x] Pet 模块（数据结构与初始化）
- [ ] Pet 自动状态更新
- [ ] OLED 宠物界面
- [ ] 宠物图片显示
- [ ] 喂食功能
- [ ] 玩耍功能
- [ ] 医疗功能
- [ ] 随机事件系统
- [ ] 互动小游戏
- [ ] 项目优化与测试
- [ ] 项目完成

---

# 📂 当前项目结构

```text
VirtualPet_STM32
│
├── Hardware/
│   ├── LED.c
│   ├── LED.h
│   ├── Key.c
│   ├── Key.h
│   ├── OLED.c
│   ├── OLED.h
│   ├── OLED_Data.c
│   ├── OLED_Data.h
│   ├── OLED_Font.h
│   ├── OLED_Wire.c
│   ├── OLED_Wire.h
│   ├── Buzzer.c
│   ├── Buzzer.h
│   ├── Timer.c
│   └── Timer.h
│
├── Pet/
│   ├── Pet.c
│   └── Pet.h
│
├── Images/
├── Videos/
├── Library/
├── Start/
├── System/
├── User/
└── README.md
```


---

## 💻 开发环境

* Keil MDK5
* STM32 标准外设库（Standard Peripheral Library）
* ST-Link

---

# 📝 开发日志

## 2026-06-16

### 完成内容

- 创建 GitHub 仓库
- 编写项目 README
- 完成 STM32 最小系统硬件接线
- 建立 STM32F103C8T6 标准库工程（Keil5）
- 完成 LED 驱动模块
- 完成按键驱动模块
- 完成 OLED 驱动模块
- 完成有源蜂鸣器驱动模块
- 完成 TIM2 定时器驱动，实现 1ms SystemTick
- 新建 Pet 模块（Pet.c / Pet.h）
- 完成 Pet 数据结构设计
- 完成 Pet_Init() 初始化函数
- OLED 成功显示宠物基础属性（Food、Happy）

---
# 🚀 下一阶段

- [ ] 完善 Pet_Update()
- [ ] 使用 TIM2 实现宠物状态自动更新
- [ ] OLED 实时刷新 Food、Happy、Health
- [ ] 显示第一版宠物图像（32×32）
- [ ] 根据状态切换宠物表情

---
> 本项目用于记录 STM32 学习过程，并持续更新开发内容。
