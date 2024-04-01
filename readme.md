# Silicon Labs Thunderboard Reach Demo

## Project Information
This project is provided by the team at i3 Product Development to serve as a simple example of a Silicon Labs-based IoT device enabled with Cygnus Reach support.  It uses the limited I/O on the Thunderboard to demonstrate the major services Reach offers.

##  Using the Pre-Built Demo
To run the demo without building the project in its entirity, all that is necessary is a [Silicon Labs Thunderboard](https://www.silabs.com/development-tools/thunderboard/thunderboard-bg22-kit?tab=overview), a phone with the Cygnus Reach app installed, and a micro-USB cable which can be plugged into your computer.  To program the Thunderboard, either install [Simplicity Studio 5](https://www.silabs.com/developers/simplicity-studio) (if intending to build the source code eventually) or the standalone [Simplicity Commander](https://www.silabs.com/developers/mcu-programming-options) programmer.  Download the `reach-silabs-v<version>.hex` file from this repository's latest release.  Run Simplicity Commander (If using Simplicity Studio, this is found under the `Tools` menu in the `Launcher` tab), select the Thunderboard (which should appear as a USB kit), go to the `Flash` page, select the downloaded .hex file, and hit `Flash`.  Once the board has successfully been programmed, pressing the button at the corner of the Thunderboard (labelled BTN0) should cause the amber LED to blink once per second.  For testing the OTA update process, download the `reach-silabs-boot.hex` file and program this as well.  This bootloader only needs to be programmed once.

## Demo Features

### Physical UI
The user interface provided by the Thunderboard is very basic.  The button labelled BTN0 enables or disables the "identify" feature, which blinks the amber LED.  Unlike the [nRF Connect demo](https://github.com/cygnus-technology/reach-nrfc), the Thunderboard does not have an RGB LED to indicate its BLE connection status.

### Virtual COM Port
The demo supports a virtual COM port connection via USB, which appears with the name `JLink CDC UART Port`.  This serial port runs at 115200 baud, with 8-bit data, no parity, and 1 stop bit.  Using a program such as [Tera Term](https://teratermproject.github.io/index-en.html), connect to this port to see debug printouts and access the CLI.  Type `help` or `?` and hit enter to see the available commands.

### Reach Features

#### CLI Service
The CLI service through Reach mirrors what is available through the virtual COM port.

#### Parameter Repository Service
The parameters implemented in the demo are intended to demonstrate the common data types defined by Reach (booleans, integers, floating-point values, bitfields, enumerations, strings, and bytearrays), as well as the metadata associated with parameters.  Most of the parameters should be self-explanatory, but a few are slightly more complicated.

The `User Device Name` parameter can be used to modify the advertised name of the dongle.  When blank, the board will advertise as `Reach Thunderboard`.  Writing a new string to this will make the device advertise this new name in future.  Rewriting this to be blank will make the board revert to advertising as `Reach Thunderboard`.

The `Timezone Enabled` and `Timezone Offset` parameters both relate to the Time service, and are covered in that section.

The other parameters reflect some basic system information, the readings from the on-board sensors, as well as allowing the user to remotely enable the identification LED, change the rate at which the identification LED blinks, and modify the color of the text printed out by the command line interface.  Of these settings, only the `Identify Interval` persists across reboots.  The two `CLI Text` parameters are used to demonstrate bitfields and enumerations, and can be used to set the text color for most CLI responses (though this will not affect debug printouts not initiated by the user).  The `CLI Text RGB State` parameter shows exactly which RGB colors are used, and the `CLI Text Color` parameter translates this into more user-friendly descriptions.  Writing either parameter will change the CLI text color and both parameters.  The `Disabled` color option will cause the CLI to use its default color.  Be aware that setting the color to `White` or other colors (depending on the color of the background) may make the text difficult to read.

By default, the Thunderboard does not watch for changes to parameters so that they can be updated in the app or web portal.  The refresh button in both will re-read all of the parameters.  To get live updates on a parameter, notifications must be set up for it.  Here, there are options for minimum and maximum notification intervals, as well as a value change trigger.  The minimum notification interval determines how much time must elapse between two notifications of the parameter changing, even if the parameter is changing more quickly than this.  Enabling the maximum notification interval will require a notification to be generated after that time elapses, even if the value has not changed.  The value change trigger determines how much the parameter value must change compared to the last notification to generate a new notification.  To see how notifications behave in action, the `Button Pressed` and sensor-related parameters are good test cases.

#### File Service
The file service includes simple examples of read-only and read/write files.  `cygnus-reach-logo.png` is a hardcoded image of the Reach logo.  `io.txt` is stored in persistent memory, and can be any file up to 2048 bytes.  By default, it contains the lyrics to "The Well" by The Crane Wives.

#### Commands Service
The `Reset Defaults` command will reset all user-controlled parameters to their default values.  Additionally, it will reset `io.txt` to its default contents.  The `Click for Wisdom` command is used to demonstrate Reach's error reporting capabilities.

#### Time Service
The time service allows the Thunderboard to report its internal time, and for the app/web portal to align the Thunderboard to the correct time.  The time service is designed to support both devices which keep track of only the time and date, and devices which also keep track of their timezone (often relevant for devices with battery-backed real-time clocks).  Typically, a device would be one or the other, but the `Timezone Enabled` parameter has been provided to show how the app and web portal behave with either mode.  The `Timezone Offset` parameter shows the current timezone offset, which can be set manually as well as through the time service.  Setting it manually and then getting the time from the device should show the device time with the new offset.

The Thunderboard does not have a real-time clock, just a real-time counter which does not persist between reboots.  When the demo starts, its UTC time will be initialized to January 1st, 1970 (a Unix timestamp of 0).
	
### OTA Updates
OTA updates may be done using the EFR Connect app, with the general process being described [here](https://docs.silabs.com/bluetooth/3.2/general/firmware-upgrade/using-efr-connect-mobile-app-for-ota-dfu). Steps 1-6 under “First Steps” describe how to generate the OTA file, which can be ignored. To do an OTA update, use the release's `reach-silabs-v<version>.gbl` file. There have been some UI changes since that tutorial was created, so now after the update finishes uploading, hit “End” to complete the update process.

## Building the Project

### Project Setup
1) Install [Simplicity Studio 5](https://www.silabs.com/developers/simplicity-studio)
2) Clone the repository from Github
3) In Simplicity Studio, hit `File->Import...`, select the repository folder (typically reach-silabs), and pick the `Simplicity Studio (.sls)` file.  No changes should need to be made on the next page, but on the third page, uncheck `Use default location` and replace this path with the repository folder to prevent Simplicity Studio from creating another copy of the project.  Hit `Finish` to complete the setup process.
4) Hit the `Build` icon (typically in the upper left).  As of v4.0.0, 1 warning (related to the use of `strnlen`) is expected for a clean build.
5) Once built successfully, the Thunderboard may be programmed by opening the project's `Binaries` folder under `Project Explorer`, right-clicking on one of the files (typically the .bin or .s37), selecting `Flash to Device...`, and then hitting `Program`.  If no device is found when the Thunderboard is plugged in, try restarting Simplicity Studio and pray that this fixes it.  Simplicity Studio is known for being a Definitely 100% Bug-Free Program™.

To generate the files needed for OTA updates, run one of the `create_bl_files.bat/.py/.sh` scripts, which should generate the `output_gbl/application.gbl` file required.

### Modifying the Project
The layout of the demo is intended to be fairly basic.  `app.c` contains the initialization code, handles LED and button interactions, calls outside functions periodically in `app_process_action(void)`, and handles BLE events in `sl_bt_on_event(sl_bt_msg_t *evt)`.  `include/definitions.h` and `src/definitions.c` are typically auto-generated with a Python script based on a definition .xlsx file, and define the Reach services implemented in the demo, as well as non-application-specific implementations of functions needed for these services.  Application-specific implementations of Reach service functions may be found in `src/cli.c`, `src/commands.c`, `src/files.c`, and `src/param_repo.c`.  `src/param_repo.c` also includes functions related to the Time service, and `src/cli.c` also handles the virtual COM port.  `include/reach-server.h` contains a number of Reach configuration options, and `Integrations/SiliconLabs/reach_silabs.h` shows the available platform-specific configuration options. 

Code in `reach-c-stack` should not be modified unless absolutely necessary, as this is shared among all Reach device projects written in C.  See [reach-c-stack](https://github.com/cygnus-technology/reach-c-stack) for information about contributing to this repository.  Code in `Integrations/SiliconLabs` is intended to be shared among multiple Silicon Labs-based projects, though it is not part of a shared repository.

To learn how to regnerate the `definitions.c` and `definitions.h` files, see `reach-util/c-gen/README.md`.

## Contributing
To contribute, create an issue in the repository, and the team at i3 Product Development will respond as quickly as possible.

## Additional Information

### Project References

 - [Cygnus Reach Documentation](https://docs.cygnustechnology.com/)
 - [Thunderboard SLTB010A Product Page](https://www.silabs.com/development-tools/thunderboard/thunderboard-bg22-kit?tab=overview)

### Firmware Resources

 - [Silicon Labs Bluetooth API Reference Guide](https://docs.silabs.com/bluetooth/6.1.0/bluetooth-stack-api/) [TODO: confirm this is the correct version]
 - [Cygnus Reach C SDK Repository](https://github.com/cygnus-technology/reach-c-stack)
 - [Cygnus Reach Utilities Repository](https://github.com/cygnus-technology/reach-util)
 - [Cygnus Reach Protobuf Repository](https://github.com/cygnus-technology/reach-protobuf)