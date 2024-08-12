# cub3d
Version: 10

# To-do
### General
- [ ] End the game in a clean way
- [ ] Norm
- [ ] Refactor to organize better the functions
- [ ] Choose sprites?
- [ ] The speed variable needs to be adjusted
- [ ] The resolution may be adjusted as well

### Rendering
- [ ] Study Raycasting
- [ ] Player initializing looking to the right position (NO, SO, EA, WE)
- x] Celing and Floor color are hardcoded now, need to get the parsed colors and make them usable in the `my_mlx_pixel_put()` function context

### Movements
- [ ] I don't know if it is lacking something

### Parser
- [x?] Remove memory leaks
- [ ] Current map can't parse correctly colors formatting (detect if a color has been passed with less channels like `255, 150,` or `255,150,:`). Need to validate this cases.
- [ ] Test weird map scenarios:
    - [ ] No player
    - [ ] Two or more players
    - [ ] Player located on the wall?
    - [ ] Test all initial directions in all weird scenarios
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
- [ ] Minimap
    - [ ] Fix minimap bug where player dot is being duplicated sometimes
    - [ ] Minimap will be weird when map is too big I guess, solve it with some scale based solution (shorten square size based on map width and height)
- [ ] Sprite Animation
- [ ] Camera movements with mouse
- [ ] Doorks which can open and close
