# cub3d
Version: 10

### General
- [ ] End the game in a clean way
- [ ] Norm
- [ ] Refactor to organize better the functions
- [ ] Choose sprites?

### Rendering
- [ ] Study Raycasting
- [ ] Player initializing looking to the right position

### Movements

### Parser
- [ ] Remove memory leaks
- [ ] Test weird map scenarios:
    - [ ] No player
    - [ ] Two or more players
    - [ ] Player located on the wall?
    - [ ] 
- [ ] Test Weird information scenarios (message bust be `Error\n` followed by explicit message about the error in all scenarios):
    - [ ] Missing NO texture in map file
    - [ ] Missing SO texture in map file
    - [ ] Missing WE texture in map file
    - [ ] Missing EA texture in map file
    - [ ] Missing more than one of the above (some permutations)
    - [ ] Wrong path in NO texture
    - [ ] Wrong path in SO texture
    - [ ] Wrong path in WE texture
    - [ ] Wrong path in EA texture
    - [ ] Missing F color
    - [ ] Missing C color
    - [ ] Missing both
    - [ ] F color missing a number
    - [ ] C color missing a number
    - [ ] F color with extra number
    - [ ] C color with extra number
    - [ ] F color with number out of range (0, 255)
    - [ ] C color with number out of range (0, 255)


### Bonus (Let's not do it please)
- [ ] Wall colision (Find if there is still some bug with collision)
- [ ] Fix minimap bug where player dot is being duplicated sometimes
- [ ] Sprite Animation
- [ ] Camera movements with mouse
- [ ] Doorks which can open and close
