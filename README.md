# PA2: SPOOKY-QUEST
This project is based on the OpenFrameworks Spooky-Quest videogame example.
 This repository is part of a Programming Assignment for the Advanced Programming Course.
 The purpose of this project is to help the student create practical programming skills by implementing
 changes to the base code that require strong understanding of the concepts discussed in class.
 
<h3>How to use</h3>

<p><b><i>USE MASTER BRANCH</b></i></p>

<p>- Walking Patterns: Changed walking patterns of the enemies from rectangles to triangle. </p>
<p>- Pressing <code>"ESC"</code> triggers a new state that inherits from the State class that pauses the game in the OverWorld and BattleState. </p>

<img src="bin/screenShots/PAUSED.png" width="400" height="300">

<p>- Displayed a HUD on the screen that tells the player his current life, number of enemies alive, and area name. Pressing <code>"k"</code> displays information hidden to the player (Number of enemies dead, player's position). </p>

<img src="bin/screenShots/MoreInfo.png" width="400" height="300">

<p>- Pressing <code>"t"</code> shows collision texture for debug</p>

<img src="bin/screenShots/collisionByTexture.png" width="400" height="300">

<p>- Player has multiple attacks in the battle state</p>
<img src="bin/screenShots/attacks.png" width="400" height="300">


<p>- Pressing <code>"B"</code> spawns the boss of that area (for debug)</p>
<img src="bin/screenShots/PressingB.png" width="400" height="300">

<p>- Pressing <code>"r"</code> Re-spawns all enemies of that area (for debug)</p>

<p>- Pressing <code>"h"</code> Re-generates player's health back to 100% (for debug)</p>

<p>- You can collect a potion oh healing from friend by pressing <code>space</code></p>
<p>- and if you press <code>"u"</code> you can use the current potion of healing from the player's inventory</p>
<img src="bin/screenShots/Wizzard_potion.png" width="400" height="300">

<p>- Every enemy/boss in the game has an attack animation for displaying attacks</p>
<img src="bin/screenShots/BattleAnimation.png" width="400" height="300">

<p>- Some enemies have special and different attacks. Some uses projectiles as main attack, others just use melee attack</p>
<img src="bin/screenShots/rangeAttack.png" width="400" height="300">

<p>- The game has a new area, "The cave". This new area has a "darkness" effect and has different obstacles in it. If you step on lava you will lose x2 your health</p>
<p> if youn step on water, you will lose x1 your health, but if you step on the void, you instantly die.</p>
<img src="bin/screenShots/lava.png" width="400" height="300">

by:
Alfredo D. Soto Vélez; Email: alfredo.soto2@upr.edu
Diego A. Perez Gandarillas; Email: diego.perez16@upr.edu


