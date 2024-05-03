# isokey

![isokey](https://blog.asterix.cloud/images/isokey10.png)

The Isokey is a keyboard with straight keys!
What are “straight” keys?
Straight keys mean a keyboard where the keys are aligned and not offset like common commercial keyboards.

* Keyboard Maintainer: [Daniele Basile <asterix24@gmail.com>](https://github.com/asterix24)
* Hardware Supported: *Custom PCB*, baed on [WeAct Black Pill V1.2](https://stm32-base.org/boards/STM32F401CCU6-WeAct-Black-Pill-V1.2.html) with STM32F401CCU6.
* Hardware Availability: https://blog.asterix.cloud/en/isokey/

Make example for this keyboard (after setting up your build environment):

    make isokey:default

Flashing example for this keyboard:

    make isokey:default:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

The keyboard is based on [WeAct Black Pill V1.2](https://stm32-base.org/boards/STM32F401CCU6-WeAct-Black-Pill-V1.2.html) with STM32F401CCU6, and to flash use stm32-dfu.

