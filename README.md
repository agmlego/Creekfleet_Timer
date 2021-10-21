Creekfleet Timer
================

Automated start sequencer for the [Creekfleet](https://creekfleet.org) sailing group.

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

Also has a mode selectable during idle operation for the ISAF Rule 26 start:

| Horns             | Time to start |
| ----------------- | ------------- |
| 1 short           | 5:00          |
| 1 short           | 4:00          |
| 1 long            | 1:00          |
| 1 short           | START         |

## Pins

| Function      | Arduino Pin          |
| ------------- | -------------------- |
| Horn          | D12                  |
| Compressor    | D11                  |
| Pressure Gauge| D35 (A16)            |
| UP.LED        | D24                  |
| UP.Switch     | D25 (active low)     |
| DOWN.LED      | D26                  |
| DOWN.Switch   | D27 (active low)     |
| SELECT.LED    | D28                  |
| SELECT.Switch | D29 (active low)     |
| BACK.LED      | D30                  |
| BACK.Switch   | D31 (active low)     |
| LCD.VO        | A22 (DAC1)           |
| LCD.RS        | D13                  |
| LCD.RW        | D14                  |
| LCD.E         | D15                  |
| LCD.DB0       | D16                  |
| LCD.DB1       | D17                  |
| LCD.DB2       | D18                  |
| LCD.DB3       | D19                  |
| LCD.DB4       | D20                  |
| LCD.DB5       | D21                  |
| LCD.DB6       | D22                  |
| LCD.DB7       | D23                  |
| LCD.Red BL    | D36 (PWM)            |
| LCD.Green BL  | D38 (PWM)            |
| LCD.Blue BL   | D37 (PWM)            |
