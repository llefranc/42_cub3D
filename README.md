# cub3d

Cub3d game (based on Wolfenstein 3D game). Made by Lucas Lefrancq.


This game is using raycasting render to create a 3D illusion.
It will first check the arguments (only one / or two are allowed :
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

(main.c file is in "srcs_parsing" directory)