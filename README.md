Creekfleet Timer
================

Automated start sequencer for the Creekfleet sailing group.

By default, runs the following sequence for each of the number of requested starts:

| Horns             | Time to start |
| ----------------- | ------------- |
| 3 long            | 3:00          |
| 2 long            | 2:00          |
| 1 long, 3 short   | 1:30          |
| 1 long            | 1:00          |
| 3 short           | 0:30          |
| 2 short           | 0:20          |
| 1 short           | 0:10          |
| 1 short           | 0:05          |
| 1 short           | 0:04          |
| 1 short           | 0:03          |
| 1 short           | 0:02          |
| 1 short           | 0:01          |
| 1 long            | START         |

## Pins

### Remote

| Function      | Arduino Pin |
| ------------- | ----------- |
| Horn          | D13         |
| Compressor    | D14         |
| Pressure Gauge| D2 (A0 soon)|
| Flag0.PWM     | D3          |
| Flag0.UP      | D7  (irq)   |
| Flag0.DOWN    | D8  (irq)   |
| Flag1.PWM     | D4          |
| Flag1.UP      | D11 (irq)   |
| Flag1.DOWN    | D12 (irq)   |
| Flag2.PWM     | D5          |
| Flag2.UP      | D16 (irq)   |
| Flag2.DOWN    | D17 (irq)   |
| Flag3.PWM     | D6          |
| Flag3.UP      | D18 (irq)   |
| Flag3.DOWN    | D19 (irq)   |
| Flag4.PWM     | D9          |
| Flag4.UP      | D20 (irq)   |
| Flag4.DOWN    | D21 (irq)   |