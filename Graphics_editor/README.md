## How to run project

You can start it with the following command: 
```
make run
```

## How to use editor

Look at the picture: this is what the editor looks like. The main widgets are signed on the picture. 
* File - ToDo: soon, by clicking on this button, a dialog box will open in which you can select or enter the name of the picture you want to open.
* New - clicking this button creates a new canvas.
* Help - ToDo: soon, by clicking on this button, a window will open with help and a short tour of using the editor.
* Palette - clicking this button opens a panel with colors (if it was closed or minimized).
* Thickness - clicking this button opens a panel with thickness (if it was closed or minimized).
* Interpolaton - clicking this button opens a window with splines (if it was closed or minimized).
* Canvas - clicking on this button opens a window with canvases (if it was closed or minimized).

All windows can be moved by the middle of their top bar.

<img src="https://github.com/x-ENIAC/MIPT_projects_3_sem/blob/master/Graphics_editor/examples/1.jpg" alt="drawing1" width="600"/>

Also you can see a panel called "Tools and plugins". This version of the editor supports the second version of the plugin standard that was developed by our group (you can see plugin standart [here](https://github.com/MIPTGroup/EditorPluginAPI)). Tools marked with "Pencil", "Spray" and "Negative effect" are plugins written by members of this group. The tool "Pen" is written by me.

Let's see what the spline does. Consider this example:

<img src="https://github.com/x-ENIAC/MIPT_projects_3_sem/blob/master/Graphics_editor/examples/2.jpg" alt="drawing2" width="600"/>

The old color value of the pixel (red, blue or green; values ​​from 0 to 255) is displayed horizontally, the new one is displayed vertically. Initially, in the window we see three straight lines that are directed at an angle of 45 degrees. We see only one - blue, but under it there is also red and green. Clicking on a line creates a point that can be moved. Let's create three points on three lines and move them:

| First example | Second example |
|----------------|----------------|
| <img src="https://github.com/x-ENIAC/MIPT_projects_3_sem/blob/master/Graphics_editor/examples/3.jpg" alt="drawing3" width="450"/> | <img src="https://github.com/x-ENIAC/MIPT_projects_3_sem/blob/master/Graphics_editor/examples/4.jpg" alt="drawing4" width="450"/> |

Depending on the different positions of the dots, we change the colors on the canvas. In the first example, we almost removed the blue and green colors, and in the second, we moved the blue up. See how the pictures have changed.


Finally, I will show an example of how the "Spray" plugin works:

<img src="https://github.com/x-ENIAC/MIPT_projects_3_sem/blob/master/Graphics_editor/examples/5.jpg" alt="drawing5" width="600"/>


## Further development
* Complete the slider with dimensions to the end.
* Add a beautiful palette with a gradient, add the ability to adjust color components using a slider.
* Add text fields and the ability to upload a picture that the user wants to edit.
* Add the ability to load plugins without editing the code, but using a dialog box.
* Remove binding to a specific graphics library (now it is SDL).
