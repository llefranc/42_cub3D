# cub3D (@42Paris)

My first RayCaster with miniLibX

![Alt text](https://github.com/lucaslefrancq/42-02_cub3d/blob/master/cub3D_example.png)

## About

Cub3D is the 4th project of the mandatory part of the cursus.
It's only made in C and the main goal was to recreate the first FPS, [Wolfenstein 3D][1].
This game is using raycasting render to create a 3D illusion.

It will first check the arguments (only one / or two are allowed) :
- The first one is the map file with all the config informations (mandatory)
- The second one is '--save' if you want to save as a BMP file the first
  rendered image with raycasting.

The program will then parse the config file, initiate several structures with
player's informations and load textures / sprites. Then it will refresh continually
the screen thanks to a raycasting algorithm, creating a different image each time
the player is moving / rotating / shooting...

The game handles the following events :
- Level choiche (1/2/3 keys, not numeric touchpad)
- Player movements (with WASD keys)
- Player rotation (with arrow keys OR mouse if M key is pressed)
- Shooting (spacebar key)
- Doors interaction (when E key is pressed near a door / secret door)
- Textures rendering or not (when T key is pressed)
- Exit (when ESC key is pressed)

Player can gains life with health items, loses life when ennemy shoots at him.
The differents difficulty levels will change ennemy damages. If the player lost
his 3 lifes, gameover will occur and he will need to quit the game with ESC key.

- Here is the [subject][2]

`This project was code for MACOS`

### Building and running the program

1. Download/Clone this repo

        git clone https://github.com/lucaslefrancq/42-02_cub3d

2. `cd` into the root directory, and run `make`

        cd 42-06_minishell
        make

3.  Run `./cub3d map.cub` to launch the game.
	You can run `./cub3d map.cub --save` if you want to save the first image rendered by the game as BMP.
    
## Sources

- [Understanding how a raycasting algorithm works][3]

[3]: https://permadi.com/1996/05/ray-casting-tutorial-table-of-contents/