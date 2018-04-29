-------------------------------------
	COMPUTER GRAPHICS
    -- Art Gallery Project --

Completed with OpenGL 3.3
-------------------------------------
// Screenshots \\
Screenshots provided in the Screenshots folder for your convenience.


// COMPILATION \\
If you use Visual Studio 2015 v140 then it should compile easily when you open the solution file.

If you use Visual Studio 2013 v120, 
First:
	- Rename folder "Group371/opengl" to "Group371/opengl_vs2015"
	- Rename folder "Group371/opengl_vs2013" to "Group371/opengl"
Then:
    - Right click the project in the Solution Explorer on the right
    - Go to properties
    - Go to Configuration Properties
    - Go into the General section
    - Change platform toolset to v120
    - Then build in the toolset

Or follow instructions here
https://msdn.microsoft.com/en-CA/library/ff770576.aspx


// CONTROLS \\
The controls for this OpenGL Art Gallery are very simple, as outlined below:

W: Move forward. Can press and hold.
A: Move left. Can press and hold.
S: Move back. Can press and hold.
D: Move right. Can press and hold.
R: Fly up. Can press and hold.
F: Fly down. Can press and hold.

Any of the above controls will incur collision where applicable, and stop your movement.
If you wish to ignore all collisions, and essentially activate "Game Master" mode, press and hold the CTRL key while moving.

B: Toggle Debug Grid and XYZ axes.
