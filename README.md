# Opus Framework

This framework was created initially to easily bootstrap a ChibiOS project for STM32F103 boards, later, I needed to add FreeRTOS as the OS while still using the ChibiOS HAL, now this project is the sum up of these 2 technologies. You can use FreeRTOS or ChibiOS-RT as RT. Note that it is focused on STM32F103 boards, but Cortex M0 and M3 are probably compatible(FreeRTOS kernel has been modified for these 2 architectures). Modifying it to work on other boards/CPUs are pretty easy though.

I also added [`dapboot`](https://github.com/devanlai/dapboot) support as USB DFU bootloader.

***Note:*** I'm using custom repos for [ChibiOS](https://github.com/0x3333/chibios_svn_mirror) and [FreeRTOS](https://github.com/0x3333/FreeRTOS-Kernel), in the ChibiOS I added some drivers and FreeRTOS support, and in the FreeRTOS I added support for ChibiOS OSAL.

## Concepts

While ChibiOS HAL is easy to use, you have to configure the drivers, and sometimes this can be a pain, this framework already has some of these drivers configured and ready to use.

## Already configured Drivers

* Serial
* Software Serial<sup>[1](#note1)</sup>
* USB Serial
* MFS

## Creating a project

`bash <(curl -Ss https://raw.githubusercontent.com/0x3333/opus/master/res/create)`

It will ask for a project name and which RTOS to use(FreeRTOS or ChibiOS-RT), a folder with the project name will be created.

***Note:*** As the ChibiOS and FreeRTOS repos are really big, I'm using git shallow clone to reduce the history to the last 500 revisions. You can increase depth using `git fetch --depth=DESIRED_DEPTH` or `git fetch --unshallow` to unshallow the repo.

### Folder organization

```
--+ Project
  | ---+ app
  |    | ---+ src
  |    |    | ---+ app.c
  |    | ---+ inc
  |    |    | ---+ app.h
  |    |    | ---+ appconf.h
  |    | ---+ app.mk
  | ---+ lib
  |    | ---+ chibios
  |    | ---+ dapboot
  |    | ---+ freertos
  |    | ---+ opus
  | ---+ out
  | ---+ Makefile
```

* `app` folder contains your project source code.
* `lib` folder contains all libraries used in your project, like `FreeRTOS`, `ChibiOS` and `dapboot`. They are configured using git submodules.
* `out` folder contains build generated files, including your `ELF` file.
* `app.mk` file is included in the Makefile and can be used to customize the build. Also, you can provide command-line variables to the make command to customize the build, more on [Building](#Building) section. You can change your RTOS of choice too.

### Configuration

The application drivers and stuff are configured using some defines in `appconf.h` file, it's well documented. Also, you have some options in the `app.mk` file.

### Building<sup>[2](#note2)</sup>

To build your project you need `make`. The provided `Makefile` is ready to build and flash your project.

#### Targets:

* `make` / `make all` will build your project.
* `make flash` will flash your board.
* `make erase` will erase your board.
* `make gdb` will start GDB, only available on BlackMagic Probe or STLINK.
* `make boot` will build and flash the `dapboot` bootloader(Flash will use the already defined programmer).

### Flashing

The included `Makefile` can upload your code using 3 probes, [BlackMagic Probe](https://github.com/blacksphere/blackmagic)(great tool!), which includes a GDB server to debug your code, an OOCD/STLINK probe or a USB DFU Bootloader.

You must provide an `env` variable `PROGRAMMER` to specify the programmer you want to use(See sections below to know which value to use).

#### Black Magic Probe

The BMP programmer/debugger can be used by exporting `PROGRAMMER=BMP`. You also need to export the BMP port to use, like `BMP_PORT=/dev/cu.usbmodemXXXXXXXXX`.

#### OOCD/STLINK

To use the STLINK probe you must export `PROGRAMMER=STLINK` and provide the OOCD folder with `OOCD_HOME=/home/user/gnu-mcu-eclipse/openocd/latest`. You also have to configure the interface and the target, these two can be configured exporting `OOCD_INTERFACE` and `OOCD_TARGET`, they already have default values on `app.mk` file.

#### USB DFU Bootloader

Opus Framework includes the `dapboot` USB DFU bootloader. You can upload firmware using it instead of an external programer or JTAG probe.

To use the bootloader, export `PROGRAMMER=BOOTLOADER`.

To keep make the bootloader wait after powering up, the easiest way is to configure an I/O as a `BUTTON`, then you can easily upload your code.

To build the bootloader, use the `make boot`. Options you can provide(See `app.mk` for examples):

* `BL_DEFS`: Some defines to be passed to the bootloader build, like enabling button.
* `BL_APP_BASE_ADDRESS`: This is the base address of your application.

### Erasing

You can erase your board using the `erase` target of Makefile.

## Facilities

### Macros

You have some macros available to help with some common tasks.

#### Strings

* `STRINGIFY`: Resolve a define to a quoted string. (If undefined, the name of the define.).
* `NL`: Will append `\n\r` to the provided parameter, ie. `DEBUG(NL("Thread started..."));`
* `FORCE_INLINE`: Will force function to be inlined.
* `UNUSED`: To avoid warnings about unused parameters while compiling.

#### Debug

You can debug your code using a BMP probe using Visual Studio Code. The project already has a configuration for this purpose.

You can also debug using serial port using these macros:

* `DEBUG(fmt, va_args)`: Same as printf signature.
* `DEBUG_FUNC()`: Will print the file, line, and function name.
* `DEBUG_BYTE(prefix, bit, suffix)`: Will print every bit in the provided byte(8 bits).
* `DEBUG_WORD(prefix, bit, suffix)`: Will print every bit in the provided word(16 bits).
* `DEBUG_DWORD(prefix, bit, suffix)`: Will print every bit in the provided byte(32 bits).
* `FIX_FOR_RELEASE(stmt)`: Accept a statement as parameter and will print an error when building for release(`OP_DEBUG` not defined), ie. `FIX_FOR_RELEASE(TIMER->SR = 0);`.
---

Notes:

* <a name="note1"><sup>1</sup></a>: Software Serial driver is implemented in my custom ChibiOS mirror, the original driver has not been merged in the ChibiOS repo.
* <a name="note2"><sup>2</sup></a>: Export `MAKEFLAGS=-jX`, where `X` is the number of CPUs you have to build faster.
