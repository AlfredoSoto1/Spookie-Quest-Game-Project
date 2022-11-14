# PA2: SPOOKY-QUEST
This project is based on the OpenFrameworks Spooky-Quest videogame example.
 This repository is part of a Programming Assignment for the Advanced Programming Course.
 The purpose of this project is to help the student create practical programming skills by implementing
 changes to the base code that require strong understanding of the concepts discussed in class.
 
<h3>How to use</h3>

<p><b><i>USE MASTER BRANCH</b></i></p>

<p>- Walking Patterns: Changed walking patterns of the enemies from rectangles to triangle. </p>
<p>- Pressing <code>"ESC"</code> triggers a new state that inherits from the State class that pauses the game in the OverWorld and BattleState. </p>

![github-small](bin/screenShots/PAUSED.png)

<p>- Displayed a HUD on the screen that tells the player his current life, number of enemies alive, and area name. Pressing <code>"k"</code> displays information hidden to the player (Number of enemies dead, player's position). </p>

<b>Phase 2 Explanation</b>
<p>- By left clicking in the screen and dragging the mouse, you can select a portion of the screen in which any particle that enters it will be magnified by x3. </p>
<p>- You can undo this selection by right clicking inside the rectangle. </p>

<b>Phase 3 Explanation</b>
<details> <summary>Details about implementation in this phase</summary>
<ol>
<li>This was designed using a class, implemented by <i>(Partner A).</i></li>
<li><i>(Partner B)</i> Implemented the built functions from this class to the main proyect to record the keys.</li>
</ol>
</details>
<p>- You can record the keys that were pressed by pressing <code>"r"</code>. An indicator will appear letting you know that you are recording the keys.</p>
<p>- You can stop the recording by pressing again <code>"r"</code>. The indicator will disapear when you stop recording.</p>
<p>- Pressing <code>"p"</code> will replay the leatest record you did.</p>
<p>- Pressing <code>"c"</code> will cancel the replay.</p>
<p>- An indicator will also appear for when you are replaying.</p>


<b>Bonus Explanation</b>
<p>- You can enable the <code>"drag magnifier"</code> by pressing <code>"l"</code> to activate the movement of the magnifier box.If you left click inside the area of the rectangle, you can drag it anywhere inside the screen.<i> (Partner A)</i></p>


by:

