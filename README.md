```
    _____                   __    __            __
   |     \                 |  \  |  \          |  \
    \▓▓▓▓▓ ______  _______ | ▓▓\ | ▓▓ ______  _| ▓▓_
      | ▓▓|      \|       \| ▓▓▓\| ▓▓/      \|   ▓▓ \
 __   | ▓▓ \▓▓▓▓▓▓\ ▓▓▓▓▓▓▓\ ▓▓▓▓\ ▓▓  ▓▓▓▓▓▓\\▓▓▓▓▓▓
|  \  | ▓▓/      ▓▓ ▓▓  | ▓▓ ▓▓\▓▓ ▓▓ ▓▓    ▓▓ | ▓▓ __
| ▓▓__| ▓▓  ▓▓▓▓▓▓▓ ▓▓  | ▓▓ ▓▓ \▓▓▓▓ ▓▓▓▓▓▓▓▓ | ▓▓|  \
 \▓▓    ▓▓\▓▓    ▓▓ ▓▓  | ▓▓ ▓▓  \▓▓▓\▓▓     \  \▓▓  ▓▓
  \▓▓▓▓▓▓  \▓▓▓▓▓▓▓\▓▓   \▓▓\▓▓   \▓▓ \▓▓▓▓▓▓▓   \▓▓▓▓
```

Dit is een programma om met sockets via TCP en HTTP te communiceren.

Ik compileer het als een programma dat op elk platform werkt.

## Building

Om het programma te bouwen gebruik ik dit commando:

```bash
./init-cosmocc # Optioneel
cosmocc -o jannet.bin main.c
```

## Troubleshooting

Als je op een Linux computer zit en Wine begint op te starten zodra je dit
programma start, voer dan dit commando uit:

```bash
sudo sh -c 'echo -1 >/proc/sys/fs/binfmt_misc/status'
```

## Zie ook

Mijn [blogpost](http://allersma.be/ape.html).
