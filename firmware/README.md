# Pipe Dream Firmware

Pipe Dream firmware uses Zephyr RTOS through a local west manifest. The
checked-in files describe how to recreate the Zephyr workspace; the Zephyr
source tree, modules, build outputs, and Python virtual environment are local
developer artifacts and are intentionally ignored.

## Setup

From this directory:

```sh
python3 -m venv .venv
source .venv/bin/activate
pip install -r requirements.txt
west init -l manifest
west update
pip install -r zephyr/scripts/requirements.txt
```

Install the Zephyr SDK separately using the upstream Zephyr getting started
guide. One supported path is:

```sh
west sdk install
```

The SDK can be installed to a custom location when prompted. If the install
partially succeeds but fails while setting up host dependencies, run the SDK's
`setup.sh` script from the installed SDK directory, then rerun
`west sdk install`. The second run may report that there is nothing left to
install if the SDK files were already downloaded.

On Linux, also install the udev rules for the target debug probe. For the TI
CC1352R1 LaunchPad/XDS110 flow, missing udev rules can cause OpenOCD to fail
with `XDS110: failed to connect`.

## Useful Commands

Build Zephyr's blinky sample for the TI CC1352R1 LaunchPad:

```sh
west build -b cc1352r1_launchxl zephyr/samples/basic/blinky
```

Build the Pipe Dream application for the TI CC1352R1 LaunchPad:
- `BOARD` variable is set in `app/CMakeLists.txt`

```sh
west build
```

Build the scratch application:

```sh
west build -s scratch -d build/scratch
```

Listen for output:

```sh
screen <tty_device> 115200
```

Flash the board:

```sh
west flash
```

Flash the scratch application
```sh
west flash -d build/scratch
```

To start fresh, remove the generated workspace directories and run setup again:

```sh
rm -rf .west zephyr modules bootloader tools build .venv
```

## Relevant Documentation
- [Zephyr Project documentation for the CC1352R2 LaunchXL](https://docs.zephyrproject.org/latest/boards/ti/cc1352r1_launchxl/doc/index.html#cc1352r1_launchxl)
- [Servo Motor (SG90)](https://docs.sunfounder.com/projects/umsk/en/latest/01_components_basic/33-component_servo.html#servo-motor-sg90)
  - [Servo Motor (SG90) Datasheet](http://www.ee.ic.ac.uk/pcheung/teaching/DE1_EE/stores/sg90_datasheet.pdf)
