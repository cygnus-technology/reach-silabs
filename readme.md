# README

The reach-silabs project is provided by the team at i3 Product Development to serve as the basis of a Silicon Labs based IoT device enabled with Cygnus Reach support.

### History

This project continues development from the earlier **reach-firmware** project ([GitHub - cygnus-technology/reach-firmware: Firmware example for Reach enabled IoT devices](https://github.com/cygnus-technology/reach-firmware)).  This repository was created new from its predecessor when the directory structure was refactored and the C stack was split into a submodule.  If you need to look at the history you can go back to the earlier repository.

### What is this repository for?

* This project can be rebuilt to run on the Silicon Labs "Thunderboard" to demonstrate the integration of the Cygnus Reach functionality.
* This project can easily be forked and ported to meet the specific needs of a project that is using the Reach functionality.  
* Porting to another Silicon Labs part should be straight forward.
* The project is factored to facilitate the porting to other SoC's supporting BLE.

### How do I get set up?

* Refer to more detailed documentation in the docs folder.
* Clone or fork this project.
* Populate the reach-c-stack submodule:  "git submodule init"
* Install and use Silicon Labs' Simplicity Studio.  This project is built with version 5.3 and gecko 4.4.0.
* To run on a different SiLabs board, refer to the Programmers Introduction document.  You will need to copy in the reach-c-stack and configure the GATT database to expose the Reach service and characteristic amoung other details.
* If you wish to run on a non-SiLabs part, other reference designs are available.

### Contribution guidelines

* Feel free to create an issue.  The team at i3 Product Development will respond as quickly as possible.
  
  