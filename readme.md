# README

The reach-silabs project is provided by the team at i3 Product Development to serve as an example of a Silicon Labs based IoT device enabled with Cygnus Reach support.
The latest documentation is available at this link: https://cygnus-technology.github.io/reach-documentation/
A release note is available in the docs folder of this project.

### History

This project continues development from the earlier **reach-firmware** project.  This repository was created new from its predecessor when the directory structure was refactored and the C stack was split into a submodule.  If you need to look at the history you can go back to the earlier repository, still available on the cygnus-technology github page.

### What is this repository for?

* This project can be rebuilt to run on the Silicon Labs "Thunderboard" to demonstrate the integration of the Cygnus Reach functionality.
* This project can easily be forked and ported to meet the specific needs of a project that is using the Reach functionality.  
* Porting to another Silicon Labs part should be straight forward.
* The project is factored to facilitate the porting to other SoC's supporting BLE.  Other examples are also available.

### How do I get set up?

* Refer to the "Getting Started" document: https://cygnus-technology.github.io/reach-documentation/Getting%20Started/index.html.
* Clone or fork this project.
* Populate the reach-c-stack submodule:  "git submodule init"
* Install and use Silicon Labs' Simplicity Studio.  This project is built with version 5.8 and gecko 4.4.0.
* To run on a different SiLabs board, refer to the Programmers Introduction document.  You will need to copy in the reach-c-stack and configure the GATT database to expose the Reach service and characteristic amoung other details.
* If you wish to run on a non-SiLabs part, other reference designs are available.

### Contribution guidelines

* Feel free to create an issue.  The team at i3 Product Development will respond as quickly as possible.
  
  
