# Roadmap

### Title screen

Basic title screen displaying a logo, version number and stuff.

- [x] Display Logo
  - [x] Draw logo 
  - [ ] (Animate logo)
- [ ] Display BG
  - [ ] Draw BG
  - [ ] (Animate BG)
- [x] Display version number and stuff
- [ ] (Select toggles language?)

Pressing `A` or `start` leads to next screen.
(Pressing `select` toggles language?)
(Maybe show the number of times the game has been started (stored in the save memory)?)

### Animation screen

Basic intro animation is shown, after that it goes automatically to the next screen.

- [x] Find a way to create an animation
- [x] Draw animation
- [x] Add sound

### Age confirmation screen

Prompts an age confirmation (popup on previous screen?).
Two buttons (yes/no) with description are show. The user need to long press them using `A` or `start`. `pad` or `L/R` allow toggling which button is selected.
If the "no" button is selected, it goes to the other games screen

- [ ] Decide overall scene look
- [ ] Draw the assets
  - [ ] Popup prompt
  - [ ] Buttons look
  - [ ] Loading bar around a button showing long press timer
- [ ] Play a warning sound when entering scene
- [ ] Add user interactions

### Other games screen

Screen saying you're too young for playing this game, proposing other games to play. These are video-related websites (YouTube, ArteTV,...)

- [x] Assets
  - [x] Find and draw four (or more) websites or video-related platforms cartridges
    - [x] YouTube
    - [x] ArteTV
    - [x] ???
    - [x] ???
  - [x] Draw BG
- [x] Show the objects
  - [x] (Animate the cartridges? Like small translations/rotations)

### Loading screen

A screen displaying a website slowly loading, like if there was internet issues. It will go from very pixellated to almost clear. A loading bar is displayed at the bottom. When almost done, it goes to the next screen.

- [ ] Find a sfw image to use as a BG
- [ ] Implement a loading bar
  - [ ] (Potentially draw assets for it?)

### Final screen

A screen showing the PH version of *La Liberté guidant le peuple*, by Eugène Delacroix with the infamous text explaining why PH has been banned in the country.

- [x] Pixel art the painting for the GBA
- [ ] Find an overall look
  - Is the text controlled by the `pad` and is sliding above the painting, allowing the BG to scroll a bit vertically (more interesting?),
  - Is the painting fixed on the screen, and a textbox is shown at the bottom of the screen, pressing `A` shows the lines, three by three (less visually interesting?)
- [x] Find the text in French
  - [ ] (Find the text other languages? English at least.)
- [ ] Implement it