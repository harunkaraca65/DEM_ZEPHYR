# DemeduKit: Universal Zephyr RTOS Project

A multi-platform embedded system project developed on **DemeduKit hardware** using **Zephyr RTOS**.  
The same C source code runs on both **STM32G030 (ARM Cortex-M0+)** and **ESP32 (Xtensa)** architectures via a **Universal Firmware** approach.

Hardware abstraction is achieved using **Device Tree (DTS)** and **Kconfig**, fully isolating the application layer from the underlying processor architecture.

---

## 🇹🇷 Türkçe Açıklama

Bu proje, DemeduKit donanımı üzerinde Zephyr RTOS kullanılarak geliştirilmiş çok platformlu bir gömülü sistem uygulamasıdır.  
Aynı C kaynak kodu, **STM32G030 (ARM Cortex-M0+)** ve **ESP32 (Xtensa)** mimarilerinde değişiklik yapılmadan çalışır.

Donanım soyutlama **Device Tree (DTS)** ve **Kconfig** yapıları ile sağlanmıştır. Bu sayede uygulama katmanı, işlemci mimarisinden tamamen izole edilmiştir.

### Teknik Mimari ve Kazanımlar

#### 1. Özel Board Desteği (Custom Board Support)
- DemeduKit donanımı için sıfırdan Zephyr board tanımları oluşturulmuştur.
- STM32 ve ESP32 için `.dts` (Device Tree Source) ve `.yaml` dosyaları yazılmıştır.
- Pin atamaları ve saat (clock) ayarları bu dosyalarda tanımlanmıştır.

#### 2. Evrensel Yazılım (Universal Firmware)
- `DT_ALIAS` mekanizması ile donanım bağımsızlığı sağlanmıştır.
- Fiziksel pin isimleri (PA9, GPIO17 vb.) yerine mantıksal alias’lar kullanılmıştır.
- Aynı kod, farklı mimarilerde yeniden düzenleme olmadan derlenebilir.

#### 3. Çekirdek (Kernel) Özellikleri
- Zephyr Kernel thread (iş parçacığı) yönetimi kullanılmıştır.
- Zaman kritik ve periyodik görevler (Heartbeat, LED Strobe) kernel zamanlayıcısı ile çalışır.
- Dual-UART köprüsü sayesinde veriler hem PC terminaline hem de MCU-to-MCU hattına aynalanır.

---

## 🇬🇧 English Description

This project is a multi-platform embedded system application developed using **Zephyr RTOS** on **DemeduKit hardware**.  
It follows a **Universal Firmware** architecture where the same C source code runs on both **STM32G030 (ARM Cortex-M0+)** and **ESP32 (Xtensa)** processors.

Hardware abstraction is provided via **Device Tree (DTS)** and **Kconfig**, completely isolating the application layer from the processor architecture.

### Technical Architecture & Achievements

#### 1. Custom Board Support
- Custom Zephyr board definitions were created from scratch for DemeduKit.
- Separate `.dts` and `.yaml` configuration files were written for STM32 and ESP32.
- Pin mappings and clock configurations are fully defined in these files.

#### 2. Universal Firmware
- Hardware independence is achieved using the `DT_ALIAS` mechanism.
- Logical aliases are used instead of physical pin names (PA9, GPIO17, etc.).
- The same source code builds on different architectures without modification.

#### 3. Kernel Features
- Uses Zephyr Kernel thread management.
- Time-critical and periodic tasks (Heartbeat, LED Strobe) are handled by the kernel scheduler.
- Dual-UART bridge mirrors data to both the PC terminal and the MCU-to-MCU communication line.

---

## Setup & Build Guide

This project requires a development environment compliant with the official Zephyr **Getting Started** guide:  
https://docs.zephyrproject.org/latest/develop/getting_started/index.html

### 1. Installing Basic Tools
- Install **Python**, **Git**, and **CMake**.
- For STM32 flashing: install **STM32CubeProgrammer** to its default directory.
- For ESP32 flashing: ensure **esptool** is available in the system `PATH`.

### 2. Creating Zephyr Workspace

```bash
pip install west
cd C:\
west init zephyrproject
cd zephyrproject
west update
west zephyr-export
pip install -r C:\zephyrproject\zephyr\scripts\requirements.txt
```

### 3. Zephyr SDK Installation
- Download the latest **Zephyr SDK**.
- Extract it to `C:\zephyr-sdk-xxx`.
- Run the setup script to register toolchains.

### 4. Project Placement

Copy the repository contents (`DEM_ZEPHYR` folder) to:

```text
C:\zephyrproject\DEM_ZEPHYR
```

### 5. Build & Flash — STM32G030 (DemeduKit STM32)

```bash
west build -p always -b demedukit_stm32 -- -DBOARD_ROOT="C:\zephyrproject\DEM_ZEPHYR"
west flash --runner stm32cubeprogrammer --port swd
```

### 6. Build & Flash — ESP32 (DemeduKit ESP32)

```bash
west build -p always -b demedukit_esp32/esp32/procpu -- -DBOARD_ROOT="C:\zephyrproject\DEM_ZEPHYR"
west flash
```

---

## Test Results (Verification)

| Parameter       | STM32G030 (ARM) | ESP32 (Xtensa) |
|-----------------|----------------|---------------|
| Board           | demedukit_stm32 | demedukit_esp32 |
| Flash Usage     | 14.6 KB (22%)   | 144.6 KB (3%) |
| Interface       | SWD (ST-CubeProgrammer)   | UART (esptool) |
| Baud Rate       | 115200          | 115200        |
| Result          | ✅ SUCCESS      | ✅ SUCCESS    |

---

**Status:** ✔️ Successfully built and tested on both architectures

