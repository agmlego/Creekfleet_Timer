LONG_HORN = 750
LONG_HORN_SPACE = LONG_HORN/2
SHORT_HORN = 400
SHORT_HORN_SPACE = SHORT_HORN/2

sequences = {
    'CreekFleet': {
        # Three long horns immediately (three minutes to start)
        0: 'LLL',
        # Two long horns a minute later (two minutes to start)
        60000: 'LL',
        # One short, three long horns 30s later (one minute 30s to start)
        90000: 'LSSS',
        # One long horn 30s later (one minute to start)
        120000: 'L',
        # Three short horns 30s later (30s to start)
        150000: 'SSS',
        160000: 'SS',                # Two short horns 10s later (20s to start)
        170000: 'S',                 # One short horn 10s later (10s to start)
        175000: 'S',                 # One short horn 5s later (5s to start)
        176000: 'S',                 # One short horn 1s later (4s to start)
        177000: 'S',                 # One short horn 1s later (3s to start)
        178000: 'S',                 # One short horn 1s later (2s to start)
        179000: 'S',                 # One short horn 1s later (1s to start)
        180000: 'L'                 # One long horn 1s later (START!)
    },
    'ISAF': {
        # One short horn immediately (five minutes to start)
        0: 'S',
        # One short horn a minute later (four minutes to start)
        60000: 'S',
        # One long horn 3m later (one minute to start)
        240000: 'L',
        # One short horn 1m later (START!)
        300000: 'S'
    }
}


with open('firmware\\CreekFleet_Timer\\src\\horn.h', 'w') as f:
    for option, sequence in sequences.items():
        print(option)
        HORN_TIMES = []
        HORN_COMMANDS = []
        for horn, blasts in sequence.items():
            stepTime = horn
            for blast in blasts:
                HORN_TIMES.append(stepTime)
                HORN_COMMANDS.append(True)
                if blast == 'L':
                    stepTime += LONG_HORN
                    HORN_TIMES.append(stepTime)
                    HORN_COMMANDS.append(False)
                    stepTime += LONG_HORN_SPACE
                if blast == 'S':
                    stepTime += SHORT_HORN
                    HORN_TIMES.append(stepTime)
                    HORN_COMMANDS.append(False)
                    stepTime += SHORT_HORN_SPACE
        f.write(
            f'uint8_t {option.upper()}_NUM_HORNS = {len(HORN_TIMES)};\n')
        f.write(f'uint64_t {option.upper()}_HORN_TIMES[] = {{\n')
        f.write(
            ',\n'.join([f'\t{time:.0f}' for time in HORN_TIMES])
            + '\n')
        f.write(f'}};\nbool {option.upper()}_HORN_COMMANDS[] = {{\n')
        f.write(
            ',\n'.join(
                [f'\t{("false","true")[command]}' for command in HORN_COMMANDS])
            + '\n')
        f.write('};\n')
        print(list(zip(HORN_TIMES, HORN_COMMANDS)))
