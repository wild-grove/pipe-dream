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
guide. On Linux, also install the udev rules for the target debug probe. For
the TI CC1352R1 LaunchPad/XDS110 flow, missing udev rules can cause OpenOCD to
fail with `XDS110: failed to connect`.

## Useful Commands

Build Zephyr's blinky sample for the TI CC1352R1 LaunchPad:

```sh
west build -b cc1352r1_launchxl zephyr/samples/basic/blinky
```

Flash the board:

```sh
west flash
```

To start fresh, remove the generated workspace directories and run setup again:

```sh
rm -rf .west zephyr modules bootloader tools build .venv
```
