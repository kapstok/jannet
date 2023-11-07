# JanNet

Dit is een programma om met sockets allerlei zaken te doen.

Ik compileer het als een programma dat op elk platform werkt.

## Notities

https://github.com/jart/cosmopolitan/issues/839

## Building

Om het programma te bouwen gebruik ik dit commando:

```bash
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
