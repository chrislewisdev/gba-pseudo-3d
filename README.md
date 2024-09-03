# sp3d

This repo is a demo that illustrates a method for creating pseudo-3d graphics on the GBA. It uses [Butano](https://github.com/GValiente/butano) which handles most of the low-level business.

This code is largely based off of my team's [GBA Jam 2024](https://itch.io/jam/gbajam24) entry, [Sleep Paradox](https://staticlinkage.itch.io/sleep-paradox) - hence the name.

## Re: math

3D math is not my strongest point, and as such there are probably some mistakes/kludges in this code. Most notably is that the camera calculations only ever really work when it is positioned 1 unit away from its target using pitch/heading values. If you try to place the camera in an arbitrary position and have it track its target, the whole thing breaks.

## How it works

For an in-depth explanation of how this graphics style works, I'll defer to the excellent blog series that helped me figure the darn thing out in the first place: [Sonic Battle (GBA) Renderer Series](https://fouramgames.com/blog/sonic-battle-renderer) by 4AM Games. He also has a demo written for PC/web: https://github.com/Ohmnivore/battle.