# Stickman Fighter

A browser-playable Raylib/WebAssembly fighting game where a red stickman battles a white AI opponent. Move, double jump, punch, and kick your way through a one-on-one arena fight with animated sprites, health bars, hit effects, sound effects, background music, and restart/fullscreen controls.

## Gameplay

You play as the red fighter against a white AI-controlled opponent. Both fighters have 100 health. Punches are faster and safer, while kicks do more damage and knockback but leave you committed for longer.

## Controls

- `A` / `D`: Move
- `W` or `Space`: Jump / double jump
- `J`: Punch
- `K`: Kick
- `R`: Restart after a match
- `F11`: Toggle fullscreen

## Strategy Tips

- Use punches when the opponent is close because they recover faster.
- Use kicks to push the opponent away or finish a low-health fight.
- Double jump to dodge an incoming attack, then land close enough to counter.
- Back up after landing a hit so the AI has to walk back into your range.
- Watch the health bars and take fewer risks when you are ahead.

## Build and Setup

### POP Environment

The project is designed for the POP Raylib/WebAssembly setup. The source files used by the game are:

- `src/main.c`
- `src/game.c`
- `src/fighter.c`
- `src/rendering.c`
- `src/effects.c`
- `src/assets.c`

Build the WASM version with:

```bash
/opt/pop/bin/build-wasm.sh src/main.c
```

This generates the `out` directory with the browser build.

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

### GitHub Actions

Every push and pull request runs an automated WebAssembly build in GitHub Actions. The workflow:

- Checks that `rendering.c`, `effects.c`, and `assets.c` are tracked in git.
- Builds raylib for the web target with Emscripten.
- Compiles all game source files into a browser build.
- Uploads the generated files as the `stickman-fighter-web` artifact.

The generated artifact contains `index.html`, JavaScript glue code, WASM, and packed resources.
