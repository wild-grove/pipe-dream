# Pipe Dream

This is an open-source hardware project for building a custom, retrofit irrigation valve that can physically actuate an existing outdoor spigot or hose bib. The system is intended to automate basic garden watering while preserving compatibility with required plumbing safety components, such as backflow preventers. Over time, this may expand to support manual override, weather-aware watering logic, soil moisture inputs, and integration with the broader Wild Grove software ecosystem.

## Background

This started as a practical solution to an everyday garden problem: remembering to water consistently. For Wild Grove, reliable plant care is foundational to supporting future plant trials, conservation experiments, and citizen science projects. Rather than relying on generic hose timers or proprietary irrigation controllers, Pipe Dream explores a more open, adaptable, and affordable path toward small-scale irrigation automation.

## Firmware

Firmware setup notes live in [firmware/README.md](firmware/README.md). The
Zephyr RTOS workspace is recreated from
[firmware/manifest/west.yml](firmware/manifest/west.yml) instead of being
committed directly.

## Project Log

#### 05-28-2026
- General project creation: updated readme, added multi-license

## Next Steps

## Licensing

Pipe Dream uses separate licenses for different parts of the project:

- Hardware design files, CAD, schematics, PCB files, BOMs, mechanical drawings, and enclosure files are licensed under **CERN-OHL-S-2.0**.
- Firmware and software are licensed under **GPL-3.0-or-later**.
- Documentation, build guides, diagrams, and written educational material are licensed under **CC BY-SA 4.0**.
- The Wild Grove name, Pipe Dream name, logos, icons, and other brand assets are **not licensed for reuse** without permission.
