\# DemeduKit: Universal Zephyr RTOS Project

\# DemeduKit: Evrensel Zephyr RTOS Projesi



---



\## 🇹🇷 Türkçe



Bu proje, DemeduKit donanımı üzerinde Zephyr RTOS kullanılarak geliştirilmiş çok platformlu bir gömülü sistem uygulamasıdır.

Aynı C kaynak kodunun hem \*\*STM32G030 (ARM Cortex-M0+)\*\* hem de \*\*ESP32 (Xtensa)\*\* mimarilerinde çalışabildiği "Universal Firmware" yapısını temel alır.

Donanım soyutlama (Hardware Abstraction), \*\*Device Tree (DTS)\*\* ve \*\*Kconfig\*\* yapıları ile sağlanmıştır.

Bu sayede uygulama katmanı, alttaki işlemci mimarisinden tamamen izole edilmiştir.



\### Teknik Mimari ve Kazanımlar



\*\*1. Özel Board Desteği (Custom Board Support):\*\*

DemeduKit donanımı için sıfırdan Zephyr board tanımları oluşturulmuştur.

STM32 ve ESP32 için `.dts` (Device Tree Source) ve `.yaml` konfigürasyon dosyaları yazılmıştır.

Pin atamaları ve saat (clock) ayarları bu dosyalarda tanımlanmıştır.



\*\*2. Evrensel Yazılım (Universal Firmware):\*\*

`DT\_ALIAS` mekanizması kullanılarak donanım bağımsızlığı sağlanmıştır.

Kod içinde fiziksel pin isimleri (PA9, GPIO17 vb.) yerine mantıksal takma adlar (Alias) kullanılmıştır.

Bu sayede kod değiştirilmeden farklı mimarilerde derleme (Build) alınabilir.



\*\*3. Çekirdek (Kernel) Özellikleri:\*\*

Sistem, Zephyr Kernel'in sunduğu Thread (İş parçacığı) yönetimini kullanır.

Zaman kritik işlemler ve periyodik görevler (Heartbeat, LED Strobe) kernel zamanlayıcısı ile yönetilir.

Dual-UART köprüsü ile veriler hem PC terminaline hem de işlemciler arası (MCU-to-MCU) hatta aynalanır.



\### Kurulum ve Derleme Rehberi



\*\*1. Geliştirme Ortamı:\*\*

Bilgisayarınızda Zephyr SDK ve West aracının kurulu olması gerekir.

Bu proje `C:\\zephyrproject\\DEM\_ZEPHYR` dizinine konumlandırılmalıdır.



\*\*2. STM32G030 (DemeduKit STM32) için Derleme:\*\*

Sanal ortamı aktif edin: `.venv\\Scripts\\activate`

Build komutunu çalıştırın:

`west build -p always -b demedukit\_stm32 -- -DBOARD\_ROOT="C:\\zephyrproject\\DEM\_ZEPHYR"`

Kodu yükleyin (ST-Link üzerinden SWD ile):

`west flash --runner stm32cubeprogrammer --port swd`



\*\*3. ESP32 (DemeduKit ESP32) için Derleme:\*\*

Build komutunu çalıştırın:

`west build -p always -b demedukit\_esp32/esp32/procpu -- -DBOARD\_ROOT="C:\\zephyrproject\\DEM\_ZEPHYR"`

Kodu yükleyin (UART üzerinden):

`west flash`



\### Test Sonuçları (Doğrulama)



Proje her iki mimaride de başarıyla derlenmiş ve test edilmiştir.



| Parametre | STM32G030 (ARM) | ESP32 (Xtensa) |

| :--- | :--- | :--- |

| \*\*Qualifier\*\* | `demedukit\_stm32` | `demedukit\_esp32` |

| \*\*Flash Kullanımı\*\* | 14.6 KB (%22) | 144.6 KB (%3) |

| \*\*Arayüz\*\* | SWD (ST-Link) | UART (esptool) |

| \*\*Baud Rate\*\* | 115200 | 115200 |

| \*\*Sonuç\*\* | ✅ BAŞARILI | ✅ BAŞARILI |



---



\## 🇬🇧 English



This project is a multi-platform embedded system application developed using Zephyr RTOS on DemeduKit hardware.

It is based on a "Universal Firmware" structure where the same C source code runs on both \*\*STM32G030 (ARM Cortex-M0+)\*\* and \*\*ESP32 (Xtensa)\*\* architectures.

Hardware abstraction is achieved via \*\*Device Tree (DTS)\*\* and \*\*Kconfig\*\* structures.

Thus, the application layer is completely isolated from the underlying processor architecture.



\### Technical Architecture \& Achievements



\*\*1. Custom Board Support:\*\*

Custom Zephyr board definitions were created from scratch for DemeduKit hardware.

`.dts` (Device Tree Source) and `.yaml` configuration files were written for STM32 and ESP32.

Pin assignments and clock settings are defined within these files.



\*\*2. Universal Firmware:\*\*

Hardware independence is ensured using the `DT\_ALIAS` mechanism.

Logical aliases are used in the code instead of physical pin names (PA9, GPIO17, etc.).

This allows building the project on different architectures without modifying the source code.



\*\*3. Kernel Features:\*\*

The system utilizes Zephyr Kernel's Thread management.

Time-critical operations and periodic tasks (Heartbeat, LED Strobe) are managed by the kernel scheduler.

Data is mirrored to both the PC terminal and the inter-processor (MCU-to-MCU) line via a Dual-UART bridge.



\### Setup \& Build Guide



\*\*1. Development Environment:\*\*

Zephyr SDK and West tool must be installed on your computer.

This project should be located at `C:\\zephyrproject\\DEM\_ZEPHYR`.



\*\*2. Building for STM32G030 (DemeduKit STM32):\*\*

Activate the virtual environment: `.venv\\Scripts\\activate`

Run the build command:

`west build -p always -b demedukit\_stm32 -- -DBOARD\_ROOT="C:\\zephyrproject\\DEM\_ZEPHYR"`

Flash the code (via SWD using ST-Link):

`west flash --runner stm32cubeprogrammer --port swd`



\*\*3. Building for ESP32 (DemeduKit ESP32):\*\*

Run the build command:

`west build -p always -b demedukit\_esp32/esp32/procpu -- -DBOARD\_ROOT="C:\\zephyrproject\\DEM\_ZEPHYR"`

Flash the code (via UART):

`west flash`



\### Test Results (Verification)



The project has been successfully compiled and tested on both architectures.



| Parameter | STM32G030 (ARM) | ESP32 (Xtensa) |

| :--- | :--- | :--- |

| \*\*Qualifier\*\* | `demedukit\_stm32` | `demedukit\_esp32` |

| \*\*Flash Usage\*\* | 14.6 KB (22%) | 144.6 KB (3%) |

| \*\*Interface\*\* | SWD (ST-Link) | UART (esptool) |

| \*\*Baud Rate\*\* | 115200 | 115200 |

| \*\*Result\*\* | ✅ SUCCESS | ✅ SUCCESS |

