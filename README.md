# Stickman Fighter

A browser-playable Raylib/WebAssembly fighting game where a red stickman battles a white AI opponent. Move, double jump, punch, and kick your way through a one-on-one arena fight with animated sprites, health bars, hit effects, sound effects, background music, and restart/fullscreen controls.

## Controls

- `A` / `D`: Move
- `W` or `Space`: Jump / double jump
- `J`: Punch
- `K`: Kick
- `R`: Restart after a match
- `F11`: Toggle fullscreen

## Building

Build the WASM version with:

```bash
/opt/pop/bin/build-wasm.sh src/main.c
```

This generates the `out` directory with the browser build.

## Running

Allocate a POP port once:

```bash
/opt/pop/bin/allocate_port.sh
```

Then run the WASM server:

```bash
/opt/pop/bin/run-wasm.sh
```

Open the forwarded local address in your browser:

```bash
localhost:XXXXX
```

Replace `XXXXX` with the allocated port number.
